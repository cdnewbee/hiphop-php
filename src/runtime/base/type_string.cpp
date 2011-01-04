/*
   +----------------------------------------------------------------------+
   | HipHop for PHP                                                       |
   +----------------------------------------------------------------------+
   | Copyright (c) 2010 Facebook, Inc. (http://www.facebook.com)          |
   +----------------------------------------------------------------------+
   | This source file is subject to version 3.01 of the PHP license,      |
   | that is bundled with this package in the file LICENSE, and is        |
   | available through the world-wide-web at the following url:           |
   | http://www.php.net/license/3_01.txt                                  |
   | If you did not receive a copy of the PHP license and are unable to   |
   | obtain it through the world-wide-web, please send a note to          |
   | license@php.net so we can mail you a copy immediately.               |
   +----------------------------------------------------------------------+
*/

#include <runtime/base/complex_types.h>
#include <runtime/base/string_offset.h>
#include <runtime/base/type_conversions.h>
#include <runtime/base/builtin_functions.h>
#include <runtime/base/comparisons.h>
#include <runtime/base/variable_serializer.h>
#include <runtime/base/zend/zend_functions.h>
#include <runtime/base/zend/zend_string.h>
#include <runtime/base/zend/zend_printf.h>
#include <runtime/base/tainted_metadata.h>

namespace HPHP {

#define SERIALIZE_MAX_SIZE (64*1024*1024)

const String null_string = String();
const StaticString empty_string("");

///////////////////////////////////////////////////////////////////////////////
// statics

String String::FromChar(char ch) {
  char tmpbuf[2];
  tmpbuf[0] = ch;
  tmpbuf[1] = 0;
  return String(tmpbuf, CopyString);
}

///////////////////////////////////////////////////////////////////////////////
// constructors

String::String(int n) {
  char tmpbuf[12];
  char *p;
  int is_negative;
  int len;
  char *buf;

  tmpbuf[11] = '\0';
  p = conv_10(n, &is_negative, &tmpbuf[11], &len);

  buf = (char*)malloc(len + 1);
  memcpy(buf, p, len + 1); // including the null terminator.
  SmartPtr<StringData>::operator=(NEW(StringData)(buf, len, AttachString));
}

String::String(int64 n) {
  char tmpbuf[21];
  char *p;
  int is_negative;
  int len;
  char *buf;

  tmpbuf[20] = '\0';
  p = conv_10(n, &is_negative, &tmpbuf[20], &len);

  buf = (char*)malloc(len + 1);
  memcpy(buf, p, len + 1); // including the null terminator.
  m_px = NEW(StringData)(buf, len, AttachString);
  m_px->incRefCount();
}

String::String(double n) {
  char *buf;
  if (n == 0.0) n = 0.0; // so to avoid "-0" output
  vspprintf(&buf, 0, "%.*G", 14, n);
  m_px = NEW(StringData)(buf, AttachString);
  m_px->incRefCount();
}

String::String(const AtomicString &s) {
  m_px = s.get();
}

void String::assign(const char *data, StringDataMode mode) {
  if (data) {
    SmartPtr<StringData>::operator=(NEW(StringData)(data, mode));
  } else {
    reset();
  }
}

void String::assign(const char *data, int len, StringDataMode mode) {
  if (data) {
    SmartPtr<StringData>::operator=(NEW(StringData)(data, len, mode));
  } else {
    reset();
  }
}

///////////////////////////////////////////////////////////////////////////////
// informational

String String::substr(int start, int length /* = 0x7FFFFFFF */,
                      bool nullable /* = false */) const {
  int len = size();
  char *ret = string_substr(data(), len, start, length, nullable);
  if (ret) {
    return String(ret, len, AttachString);
  }
  return String();
}

String String::lastToken(char delimiter) {
  int pos = rfind(delimiter);
  if (pos >= 0) {
    return substr(pos + 1);
  }
  return *this;
}

int String::find(char ch, int pos /* = 0 */,
                 bool caseSensitive /* = true */) const {
  if (empty()) return -1;
  return string_find(m_px->data(), m_px->size(), ch, pos, caseSensitive);
}

int String::find(const char *s, int pos /* = 0 */,
                 bool caseSensitive /* = true */) const {
  ASSERT(s);
  if (empty()) return -1;
  if (*s && *(s+1) == 0) {
    return find(*s, pos, caseSensitive);
  }
  return string_find(m_px->data(), m_px->size(), s, strlen(s),
                     pos, caseSensitive);
}

int String::find(CStrRef s, int pos /* = 0 */,
                 bool caseSensitive /* = true */) const {
  if (empty()) return -1;
  if (s.size() == 1) {
    return find(*s.data(), pos, caseSensitive);
  }
  return string_find(m_px->data(), m_px->size(), s.data(), s.size(),
                     pos, caseSensitive);
}

int String::rfind(char ch, int pos /* = -1 */,
                  bool caseSensitive /* = true */) const {
  if (empty()) return -1;
  return string_rfind(m_px->data(), m_px->size(), ch, pos, caseSensitive);
}

int String::rfind(const char *s, int pos /* = -1 */,
                  bool caseSensitive /* = true */) const {
  ASSERT(s);
  if (empty()) return -1;
  if (*s && *(s+1) == 0) {
    return rfind(*s, pos, caseSensitive);
  }
  return string_rfind(m_px->data(), m_px->size(), s, strlen(s),
                      pos, caseSensitive);
}

int String::rfind(CStrRef s, int pos /* = -1 */,
                  bool caseSensitive /* = true */) const {
  if (empty()) return -1;
  if (s.size() == 1) {
    return rfind(*s.data(), pos, caseSensitive);
  }
  return string_rfind(m_px->data(), m_px->size(), s.data(), s.size(),
                      pos, caseSensitive);
}

String String::replace(int start, int length, CStrRef replacement) const {
  int len = size();
  char *ret = string_replace(data(), len, start, length, replacement.data(),
                             replacement.size());
  return String(ret, len, AttachString);
}

String String::replace(CStrRef search, CStrRef replacement) const {
  int count;
  return replace(search, replacement, count, true);
}

String String::replace(CStrRef search, CStrRef replacement, int &count,
                       bool caseSensitive) const {
  count = 0;
  if (!search.empty() && !empty()) {
    int len = m_px->size();
    char *ret = string_replace(m_px->data(), len, search.data(), search.size(),
                               replacement.data(), replacement.size(), count,
                               caseSensitive);
    if (ret) {
      return String(ret, len, AttachString);
    }
  }
  return *this;
}

///////////////////////////////////////////////////////////////////////////////
// offset functions: cannot inline these due to dependencies

String String::rvalAt(CArrRef key) const {
  return rvalAtImpl(key.toInt32());
}

String String::rvalAt(CObjRef key) const {
  return rvalAtImpl(key.toInt32());
}

String String::rvalAt(CVarRef key) const {
  return rvalAtImpl(key.toInt32());
}

StringOffset String::lvalAt(CArrRef key) {
  return lvalAtImpl(key.toInt32());
}

StringOffset String::lvalAt(CObjRef key) {
  return lvalAtImpl(key.toInt32());
}

StringOffset String::lvalAt(CVarRef key) {
  return lvalAtImpl(key.toInt32());
}

char String::charAt(int pos) const {
  ASSERT(pos >= 0 && pos <= size());
  const char *s = data();
  return s[pos];
}

///////////////////////////////////////////////////////////////////////////////
// assignments

String &String::operator=(litstr s) {
  if (s) {
    SmartPtr<StringData>::operator=(NEW(StringData)(s, AttachLiteral));
  } else {
    reset();
  }
  return *this;
}

String &String::operator=(StringData *data) {
  SmartPtr<StringData>::operator=(data);
  return *this;
}

String &String::operator=(const std::string & s) {
  SmartPtr<StringData>::operator=(
    NEW(StringData)(s.c_str(), s.size(), CopyString));
  return *this;
}

String &String::operator=(CStrRef str) {
  SmartPtr<StringData>::operator=(str.m_px);
  return *this;
}

String &String::operator=(CVarRef var) {
  return operator=(var.toString());
}

String &String::operator=(const AtomicString &s) {
  return operator=(s.get());
}

///////////////////////////////////////////////////////////////////////////////
// concatenation and increments

String &String::operator+=(litstr s) {
  if (s && *s) {
    if (empty()) {
      SmartPtr<StringData>::operator=(NEW(StringData)(s, AttachLiteral));
    } else if (m_px->getCount() == 1) {
      int len = strlen(s);
      m_px->append(s, len);
    } else {
      int len;
      char *ret = string_concat(data(), size(), s, strlen(s), len);
      SmartPtr<StringData>::operator=(NEW(StringData)(ret, len, AttachString));
    }
  }
  return *this;
}

String &String::operator+=(CStrRef str) {
  if (!str.empty()) {
    if (empty()) {
      SmartPtr<StringData>::operator=(str.m_px);
    } else if (m_px->getCount() == 1) {
      m_px->append(str.data(), str.size());
    } else {
      int len;
      char *ret = string_concat(data(), size(), str.data(), str.size(), len);
      SmartPtr<StringData>::operator=(NEW(StringData)(ret, len, AttachString));
    }
  }
  return *this;
}

String String::operator+(litstr str) const {
  if (empty()) return str;

  if (!str || !*str) return *this;

  int len;
  char *ret = string_concat(data(), size(), str, strlen(str), len);
  return NEW(StringData)(ret, len, AttachString);
}

String String::operator+(CStrRef str) const {
  if (empty()) return str;

  if (str.empty()) return *this;

  int len;
  char *ret = string_concat(data(), size(), str.data(), str.size(), len);
  return NEW(StringData)(ret, len, AttachString);
}

String String::operator~() const {
  String ret(NEW(StringData)(data(), size(), CopyString));
  ret->negate();
  return ret;
}

String String::operator|(CStrRef v) const {
  return String(m_px).operator|=(v);
}

String String::operator&(CStrRef v) const {
  return String(m_px).operator&=(v);
}

String String::operator^(CStrRef v) const {
  return String(m_px).operator^=(v);
}

String &String::operator|=(CStrRef v) {
  const char *s1 = data();
  const char *s2 = v.data();
  int len1 = size();
  int len2 = v.size();
  char *copy = NULL;
  if (len2 > len1) {
    copy = string_duplicate(s2, len2);
    for (int i = 0; i < len1; i++) copy[i] |= s1[i];
    SmartPtr<StringData>::operator=(NEW(StringData)(copy, len2, AttachString));
  } else {
    copy = string_duplicate(s1, len1);
    for (int i = 0; i < len2; i++) copy[i] |= s2[i];
    SmartPtr<StringData>::operator=(NEW(StringData)(copy, len1, AttachString));
  }
  return *this;
}

String &String::operator&=(CStrRef v) {
  const char *s1 = data();
  const char *s2 = v.data();
  int len1 = size();
  int len2 = v.size();
  char *copy = NULL;
  if (len2 < len1) {
    copy = string_duplicate(s2, len2);
    for (int i = 0; i < len2; i++) copy[i] &= s1[i];
    SmartPtr<StringData>::operator=(NEW(StringData)(copy, len2, AttachString));
  } else {
    copy = string_duplicate(s1, len1);
    for (int i = 0; i < len1; i++) copy[i] &= s2[i];
    SmartPtr<StringData>::operator=(NEW(StringData)(copy, len1, AttachString));
  }
  return *this;
}

String &String::operator^=(CStrRef v) {
  const char *s1 = data();
  const char *s2 = v.data();
  int len1 = size();
  int len2 = v.size();
  char *copy = NULL;
  if (len2 < len1) {
    copy = string_duplicate(s2, len2);
    for (int i = 0; i < len2; i++) copy[i] ^= s1[i];
    SmartPtr<StringData>::operator=(NEW(StringData)(copy, len2, AttachString));
  } else {
    copy = string_duplicate(s1, len1);
    for (int i = 0; i < len1; i++) copy[i] ^= s2[i];
    SmartPtr<StringData>::operator=(NEW(StringData)(copy, len1, AttachString));
  }
  return *this;
}

///////////////////////////////////////////////////////////////////////////////
// conversions

VarNR String::toKey() const {
  if (!m_px) return empty_string;
  int64 n = 0;
  if (m_px->isStrictlyInteger(n)) {
    return n;
  } else {
    return m_px;
  }
}

///////////////////////////////////////////////////////////////////////////////
// comparisons

bool String::same(litstr v2) const {
  return HPHP::same(m_px, v2);
}

bool String::same(const StringData *v2) const {
  return HPHP::same(m_px, v2);
}

bool String::same(CStrRef v2) const {
  return HPHP::same(m_px, v2);
}

bool String::same(CArrRef v2) const {
  return HPHP::same(m_px, v2);
}

bool String::same(CObjRef v2) const {
  return HPHP::same(m_px, v2);
}

bool String::equal(litstr v2) const {
  return HPHP::equal(m_px, v2);
}

bool String::equal(const StringData *v2) const {
  return HPHP::equal(m_px, v2);
}

bool String::equal(CStrRef v2) const {
  return HPHP::equal(m_px, v2);
}

bool String::equal(CArrRef v2) const {
  return HPHP::equal(m_px, v2);
}

bool String::equal(CObjRef v2) const {
  return HPHP::equal(m_px, v2);
}

bool String::less(litstr v2) const {
  return HPHP::less(m_px, v2);
}

bool String::less(const StringData *v2) const {
  return HPHP::less(m_px, v2);
}

bool String::less(CStrRef v2) const {
  return HPHP::less(m_px, v2);
}

bool String::less(CArrRef v2) const {
  return HPHP::less(m_px, v2);
}

bool String::less(CObjRef v2) const {
  return HPHP::less(m_px, v2);
}

bool String::more(litstr v2) const {
  return HPHP::more(m_px, v2);
}

bool String::more(const StringData *v2) const {
  return HPHP::more(m_px, v2);
}

bool String::more(CStrRef v2) const {
  return HPHP::more(m_px, v2);
}

bool String::more(CArrRef v2) const {
  return HPHP::more(m_px, v2);
}

bool String::more(CObjRef v2) const {
  return HPHP::more(m_px, v2);
}

///////////////////////////////////////////////////////////////////////////////
// comparison operators

bool String::operator==(litstr v) const {
  return HPHP::equal(m_px, v);
}

bool String::operator!=(litstr v) const {
  return !HPHP::equal(m_px, v);
}

bool String::operator>=(litstr v) const {
  return not_less(m_px, v);
}

bool String::operator<=(litstr v) const {
  return not_more(m_px, v);
}

bool String::operator>(litstr v) const {
  return HPHP::more(m_px, v);
}

bool String::operator<(litstr v) const {
  return HPHP::less(m_px, v);
}

bool String::operator==(CStrRef v) const {
  return HPHP::equal(m_px, v);
}

bool String::operator!=(CStrRef v) const {
  return !HPHP::equal(m_px, v);
}

bool String::operator>=(CStrRef v) const {
  return not_less(m_px, v);
}

bool String::operator<=(CStrRef v) const {
  return not_more(m_px, v);
}

bool String::operator>(CStrRef v) const {
  return HPHP::more(m_px, v);
}

bool String::operator<(CStrRef v) const {
  return HPHP::less(m_px, v);
}

bool String::operator==(CVarRef v) const {
  return HPHP::equal(m_px, v);
}

bool String::operator!=(CVarRef v) const {
  return !HPHP::equal(m_px, v);
}

bool String::operator>=(CVarRef v) const {
  return not_less(m_px, v);
}

bool String::operator<=(CVarRef v) const {
  return not_more(m_px, v);
}

bool String::operator>(CVarRef v) const {
  return HPHP::more(m_px, v);
}

bool String::operator<(CVarRef v) const {
  return HPHP::less(m_px, v);
}

///////////////////////////////////////////////////////////////////////////////
// input/output

void String::serialize(VariableSerializer *serializer) const {
  if (m_px) {
    serializer->write(m_px->data(), m_px->size());
  } else {
    serializer->writeNull();
  }
}

void String::unserialize(VariableUnserializer *uns,
                         char delimiter0 /* = '"' */,
                         char delimiter1 /* = '"' */) {
  int size = uns->readInt();
  if (size >= SERIALIZE_MAX_SIZE) {
    throw Exception("Size of serialized string (%d) exceeds max", size);
  }

  char ch = uns->readChar();
  if (ch != ':') {
    throw Exception("Expected ':' but got '%c'", ch);
  }
  ch = uns->readChar();
  if (ch != delimiter0) {
    throw Exception("Expected '%c' but got '%c'", delimiter0, ch);
  }

  char *buf = (char*)malloc(size + 1);
  uns->read(buf, size);
  buf[size] = '\0';
  SmartPtr<StringData>::operator=(NEW(StringData)(buf, size, AttachString));

  ch = uns->readChar();
  if (ch != delimiter1) {
    throw Exception("Expected '%c' but got '%c'", delimiter1, ch);
  }

  checkStatic();
}

bool String::checkStatic() {
  ASSERT(m_px);
  StringDataSet &set = StaticString::TheStaticStringSet();
  if (!set.empty()) {
    // no need to upgrade when the initialization is done.
    StringDataSet::iterator it = set.find(m_px);
    if (it != set.end()) {
      SmartPtr<StringData>::operator=(*it);
      return true;
    }
  }
  return false;
}

String String::fiberCopy() const {
  if (m_px) {
    return m_px->copy();
  }
  return String();
}

///////////////////////////////////////////////////////////////////////////////
// debugging

void String::dump() const {
  if (m_px) {
    m_px->dump();
  } else {
    printf("(null)\n");
  }
}

  #ifdef TAINTED
  /**
   * Tainting dynamic analysis
   */
  bitstring String::getTaint() const {
    return m_px ? m_px->getTaint() : default_tainting;
    // a null pointer should be considered untainted
  }
  void String::setTaint(bitstring b) const {
    if(m_px) {
      m_px->setTaint(b);
      if(is_tainting_metadata(b)){
        getTaintedMetadata()->setTaintedOriginal(this);
        getTaintedMetadata()->setTaintedPlace();
      }
    }
  }
  void String::setTaint(bitstring b, CStrRef msg) const {
    if(m_px) {
      m_px->setTaint(b);
      if(is_tainting_metadata(b)){
        getTaintedMetadata()->setTaintedOriginal(this);
        getTaintedMetadata()->setTaintedPlace(msg.toKey());
      }
    }
  }
  void String::unsetTaint(bitstring b) const {
    if(m_px) { m_px->unsetTaint(b); }
  }
  TaintedMetadata* String::getTaintedMetadata() const {
    if(m_px) {
      return m_px->getTaintedMetadata();
    } else {
      return NULL;
    }
  }

  bitstring* String::getTaintBitString() {
    return m_px ? m_px->getTaintBitString() : NULL;
  }

  TaintedMetadata** String::getTaintMetaData() {
    return m_px ? m_px->getTaintMetaData() : NULL;
  }
  #endif


///////////////////////////////////////////////////////////////////////////////
// StaticString

StaticString::StaticString(litstr s) : m_data(s) {
  String::operator=(&m_data);
  m_px->setStatic();
  if (!checkStatic()) {
    s_stringSet->insert(m_px);
  }
}

StaticString::StaticString(litstr s, int length)
  : m_data(s, length, AttachLiteral) {
  String::operator=(&m_data);
  m_px->setStatic();
  if (!checkStatic()) {
    s_stringSet->insert(m_px);
  }
}

StaticString::StaticString(std::string s)
  : m_data(s.c_str(), s.size(), CopyString) {
  String::operator=(&m_data);
  m_px->setStatic();
  if (!checkStatic()) {
    s_stringSet->insert(m_px);
  }
}

StaticString::StaticString(const StaticString &str)
  : m_data(str.m_data.data(), str.m_data.size(), AttachLiteral) {
  String::operator=(&m_data);
  m_px->setStatic();
  if (!checkStatic()) {
    s_stringSet->insert(m_px);
  }
}

StaticString& StaticString::operator=(const StaticString &str) {
  // Assignment to a StaticString is ignored. Generated code
  // should never use a StaticString on the left-hand side of
  // assignment. A StaticString can only be initialized by a
  // StaticString constructor or StaticString::init().
  ASSERT(false);
  return *this;
}

void StaticString::init(litstr s, int length) {
  m_data.assign(s, length, AttachLiteral);
  ASSERT(!m_px);
  String::operator=(&m_data);
  m_px->setStatic();
  if (!checkStatic()) {
    s_stringSet->insert(m_px);
  }
}

StringDataSet &StaticString::TheStaticStringSet() {
  if (s_stringSet == NULL) {
    s_stringSet = new StringDataSet();
  }
  return *s_stringSet;
}

void StaticString::FinishInit() {
  // release the memory
  StringDataSet empty;
  s_stringSet->swap(empty);
}

void StaticString::ResetAll() {
  delete s_stringSet;
}

StringDataSet *StaticString::s_stringSet = NULL;

class StaticStringUninitializer {
public:
  ~StaticStringUninitializer() {
    StaticString::ResetAll();
  }
};
static StaticStringUninitializer s_static_string_uninitializer;

//////////////////////////////////////////////////////////////////////////////
// AtomicString

AtomicString::AtomicString(const char *s,
                           StringDataMode mode /* = AttachLiteral */) {
  if (s) {
    m_px = new StringData(s, mode);
    m_px->setAtomic();
    m_px->incAtomicCount();
    return;
  }
  m_px = NULL;
}

AtomicString::AtomicString(const std::string &s) {
  m_px = new StringData(s.c_str(), s.size(), CopyString);
  m_px->setAtomic();
  m_px->incAtomicCount();
}

AtomicString::AtomicString(StringData *str) {
  ASSERT(str);
  if (str->isRefCounted()) {
    m_px = new StringData(str->data(), str->size(), CopyString);
    m_px->setAtomic();
    m_px->incAtomicCount();
    return;
  }
  // atomic or static
  m_px = str;
  m_px->incAtomicCount();
}

AtomicString::AtomicString(const AtomicString &s) {
  m_px = s.get();
  if (m_px) m_px->incAtomicCount();
}

AtomicString::~AtomicString() {
  ASSERT(!m_px || m_px->isAtomic());
  if (m_px && m_px->decAtomicCount() == 0) {
    delete m_px;
  }
}

AtomicString &AtomicString::operator=(const AtomicString &s) {
  if (m_px && m_px->decAtomicCount() == 0) {
    delete m_px;
  }
  m_px = s.get();
  if (m_px) m_px->incAtomicCount();
  return *this;
}

AtomicString &AtomicString::operator=(const std::string &s) {
  if (m_px && m_px->decAtomicCount() == 0) {
    delete m_px;
  }
  m_px = new StringData(s.c_str(), s.size(), CopyString);
  m_px->setAtomic();
  m_px->incAtomicCount();
  return *this;
}

//////////////////////////////////////////////////////////////////////////////
}
