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

#ifndef __INSIDE_HPHP_COMPLEX_TYPES_H__
#error Directly including 'type_array.h' is prohibited. \
       Include 'complex_types.h' instead.
#endif

#ifndef __HPHP_ARRAY_H__
#define __HPHP_ARRAY_H__

#include <runtime/base/util/smart_ptr.h>
#include <runtime/base/types.h>
#include <runtime/base/array/array_data.h>
#include <runtime/base/array/array_iterator.h>
#include <runtime/base/type_string.h>
#include <runtime/base/hphp_value.h>

namespace HPHP {
///////////////////////////////////////////////////////////////////////////////

// forward declaration
CVarRef ref(CVarRef v);

/**
 * Array type wrapping around 2 types of ArrayData to implement reference
 * counting, copy-on-write and ArrayData escalation.
 *
 * "Escalation" happens when an underlying ArrayData cannot handle an operation
 * and instead it needs to "upgrade" itself to be a more general (but slower)
 * type of ArrayData to accomplish the task. This "upgrade" is called
 * escalation. This describes all possible escalation paths:
 *
 *   SmallArray --> ZendArray
 *
 * SmallArray escalates to ZendArray when the capacity of the SmallArray is
 * exceeded.
 */
class Array : public SmartPtr<ArrayData> {
 public:
  /**
   * Create an empty array or an array with one element. Note these are
   * different than those copying constructors that also take one value.
   */
  static Array Create() { return ArrayData::Create();}
  static Array Create(CVarRef value) { return ArrayData::Create(value);}
  static Array Create(CVarRef key, CVarRef value);

 public:
  Array() {}

  /**
   * Constructors. Those that take "arr" or "var" are copy constructors, taking
   * array value from the parameter, and they are NOT constructing an array
   * with that single value (then one should use Array::Create() functions).
   */
  Array(ArrayData *data);
  Array(CArrRef arr);

  /**
   * Informational
   */
  bool empty() const {
    return m_px == NULL || m_px->empty();
  }
  ssize_t size() const {
    return m_px ? m_px->size() : 0;
  }
  ssize_t length() const {
    return m_px ? m_px->size() : 0;
  }
  bool isNull() const {
    return m_px == NULL;
  }
  bool valueExists(CVarRef search_value, bool strict = false) const;
  Variant key(CVarRef search_value, bool strict = false) const;
  Array keys(CVarRef search_value = null_variant, bool strict = false) const;
  Array values() const;

  /**
   * Operators
   */
  Array &operator =  (ArrayData *data);
  Array &operator =  (CArrRef v);
  Array &operator =  (CVarRef v);
  Array  operator +  (ArrayData *data) const;
  Array  operator +  (CArrRef v) const;
  Array  operator +  (CVarRef v) const;
  Array &operator += (ArrayData *data);
  Array &operator += (CArrRef v);
  Array &operator += (CVarRef v);

  /**
   * Returns the entries that have keys and/or values that are not present in
   * specified array. Keys and values can be compared by user supplied
   * functions and key_data or value_data will be passed into PFUNC_CMP as
   * "data" parameter. Otherwise, equal() will be called for comparisons. If
   * both by_key and by_value, both keys and values have to match to be
   * excluded.
   */
  typedef int (*PFUNC_CMP)(CVarRef v1, CVarRef v2, const void *data);
  Array diff(CArrRef array, bool by_key, bool by_value,
             PFUNC_CMP key_cmp_function = NULL,
             const void *key_data = NULL,
             PFUNC_CMP value_cmp_function = NULL,
             const void *value_data = NULL) const;

  /**
   * Returns the entries that have keys and/or values that are present in
   * specified array. Keys and values can be compared by user supplied
   * functions and key_data or value_data will be passed into PFUNC_CMP as
   * "data" parameter. Otherwise, equal() will be called for comparisons. If
   * both by_key and by_value, both keys and values have to match to be
   * included.
   */
  Array intersect(CArrRef array, bool by_key, bool by_value,
                  PFUNC_CMP key_cmp_function = NULL,
                  const void *key_data = NULL,
                  PFUNC_CMP value_cmp_function = NULL,
                  const void *value_data = NULL) const;

  /**
   * Iterator functions. See array_iterator.h for end() and next().
   */
  ArrayIter begin(CStrRef context = null_string) const { return m_px;}

  void escalate(bool mutableIteration = false);

  /**
   * Manipulations
   *
   * Merge: This is different from operator "+", where existing key's values
   * are NOT modified. This function will actually override with new values.
   * When merging a vector with a vector, new elements are always appended, and
   * this is also different from operator "+", where existing numeric indices
   * are not modified.
   *
   * Slice: Taking a slice. When "preserve_keys" is true, a vector will turn
   * into numerically keyed map.
   */
  Array &merge(CArrRef arr);
  Array slice(int offset, int length, bool preserve_keys) const;

  /**
   * Sorting.
   */
  static int SortRegularAscending(CVarRef v1, CVarRef v2, const void *data);
  static int SortNumericAscending(CVarRef v1, CVarRef v2, const void *data);
  static int SortStringAscending(CVarRef v1, CVarRef v2, const void *data);
  static int SortLocaleStringAscending(CVarRef v1, CVarRef v2,
                                       const void *data);

  static int SortRegularDescending(CVarRef v1, CVarRef v2, const void *data);
  static int SortNumericDescending(CVarRef v1, CVarRef v2, const void *data);
  static int SortStringDescending(CVarRef v1, CVarRef v2, const void *data);
  static int SortLocaleStringDescending(CVarRef v1, CVarRef v2,
                                        const void *data);

  static int SortNatural(CVarRef v1, CVarRef v2, const void *data);
  static int SortNaturalCase(CVarRef v1, CVarRef v2, const void *data);

  void sort(PFUNC_CMP cmp_func, bool by_key, bool renumber,
            const void *data = NULL);

  /**
   * Sort multiple arrays at once similar to how ORDER BY clause works in SQL.
   */
  struct SortData {
    Variant    *original;
    const Array      *array;
    bool        by_key;
    PFUNC_CMP   cmp_func;
    const void *data;
    std::vector<ssize_t> positions;
  };
  static bool MultiSort(std::vector<SortData> &data, bool renumber);

  /**
   * Type conversions
   */
  bool   toBoolean() const { return  m_px && !m_px->empty();}
  char   toByte   () const { return (m_px && !m_px->empty()) ? 1 : 0;}
  short  toInt16  () const { return (m_px && !m_px->empty()) ? 1 : 0;}
  int    toInt32  () const { return (m_px && !m_px->empty()) ? 1 : 0;}
  int64  toInt64  () const { return (m_px && !m_px->empty()) ? 1 : 0;}
  double toDouble () const { return (m_px && !m_px->empty()) ? 1.0 : 0.0;}
  String toString () const { return m_px ? "Array" : "";}
  Object toObject () const;

  /**
   * Comparisons
   */
  bool same (CArrRef v2) const;
  bool same (CObjRef v2) const;
  bool equal(CArrRef v2) const;
  bool equal(CObjRef v2) const;
  bool less (CArrRef v2, bool flip = false) const;
  bool less (CObjRef v2) const;
  bool less (CVarRef v2) const;
  bool more (CArrRef v2, bool flip = true) const;
  bool more (CObjRef v2) const;
  bool more (CVarRef v2) const;

  /**
   * Offset
   */
  Variant rvalAt(bool key, bool error = false) const;
  Variant rvalAt(char key, bool error = false) const;
  Variant rvalAt(short key, bool error = false) const;
  Variant rvalAt(int key, bool error = false) const;
  Variant rvalAt(int64 key, bool error = false) const;
  Variant rvalAt(double key, bool error = false) const;
  Variant rvalAt(litstr key, bool error = false, bool isString = false) const;
  Variant rvalAt(CStrRef key, bool error = false, bool isString = false) const;
  Variant rvalAt(CVarRef key, bool error = false) const;

  const Variant operator[](bool    key) const;
  const Variant operator[](char    key) const;
  const Variant operator[](short   key) const;
  const Variant operator[](int     key) const;
  const Variant operator[](int64   key) const;
  const Variant operator[](double  key) const;
  const Variant operator[](litstr  key) const;
  const Variant operator[](CStrRef key) const;
  const Variant operator[](CVarRef key) const;

  Variant &lval() {
    ASSERT(m_px);
    Variant *ret = NULL;
    ArrayData *escalated = m_px->lval(ret, m_px->getCount() > 1);
    if (escalated) {
      SmartPtr<ArrayData>::operator=(escalated);
    }
    ASSERT(ret);
    return *ret;
  }

  Variant &lval(int64 key) {
    ASSERT(m_px);
    Variant *ret = NULL;
    ArrayData *escalated = m_px->lval(key, ret, m_px->getCount() > 1);
    if (escalated) {
      SmartPtr<ArrayData>::operator=(escalated);
    }
    ASSERT(ret);
    return *ret;
  }

  Variant &lval(CStrRef key) {
    ASSERT(m_px);
    Variant *ret = NULL;
    ArrayData *escalated = m_px->lval(key, ret, m_px->getCount() > 1);
    if (escalated) {
      SmartPtr<ArrayData>::operator=(escalated);
    }
    ASSERT(ret);
    return *ret;
  }

  Variant *lvalPtr(CStrRef key, bool forWrite, bool create);

  Variant &lvalAt();

  Variant &lvalAt(bool    key, bool checkExist = false) {
    return lvalAtImpl(key, checkExist);
  }
  Variant &lvalAt(char    key, bool checkExist = false) {
    return lvalAtImpl(key, checkExist);
  }
  Variant &lvalAt(short   key, bool checkExist = false) {
    return lvalAtImpl(key, checkExist);
  }
  Variant &lvalAt(int     key, bool checkExist = false) {
    return lvalAtImpl(key, checkExist);
  }
  Variant &lvalAt(int64   key, bool checkExist = false) {
    return lvalAtImpl(key, checkExist);
  }
  Variant &lvalAt(double  key, bool checkExist = false) {
    return lvalAtImpl((int64)key, checkExist);
  }
  Variant &lvalAt(litstr  key, bool checkExist = false, bool isString = false);
  Variant &lvalAt(CStrRef key, bool checkExist = false, bool isString = false);
  Variant &lvalAt(CVarRef key, bool checkExist = false);

  // defined in type_variant.h
  template<typename T>
  CVarRef setImpl(const T &key, CVarRef v);

  CVarRef set(bool    key, CVarRef v) {
    return setImpl(key ? 1LL : 0LL, v);
  }
  CVarRef set(char    key, CVarRef v) {
    return setImpl((int64)key, v);
  }
  CVarRef set(short   key, CVarRef v) {
    return setImpl((int64)key, v);
  }
  CVarRef set(int     key, CVarRef v) {
    return setImpl((int64)key, v);
  }
  CVarRef set(int64   key, CVarRef v) {
    return setImpl(key, v);
  }
  CVarRef set(double  key, CVarRef v) {
    return setImpl((int64)key, v);
  }

  CVarRef set(litstr  key, CVarRef v, bool isString = false);
  CVarRef set(CStrRef key, CVarRef v, bool isString = false);

  CVarRef set(CVarRef key, CVarRef v);

  // defined in type_variant.h
  template<typename T>
  Variant refvalAt(const T &key);

  Variant refvalAt(CStrRef key, bool isString = false);

  /**
   * Membership functions.
   */
  template<typename T>
    bool existsImpl(const T &key) const {
    if (m_px) return m_px->exists(key);
    return false;
  }
  bool exists(bool    key) const {
    return existsImpl(key ? 1LL : 0LL);
  }
  bool exists(char    key) const {
    return existsImpl((int64)key);
  }
  bool exists(short   key) const {
    return existsImpl((int64)key);
  }
  bool exists(int     key) const {
    return existsImpl((int64)key);
  }
  bool exists(int64   key) const {
    return existsImpl(key);
  }
  bool exists(double  key) const {
    return existsImpl((int64)key);
  }
  bool exists(litstr  key, bool isString = false) const;
  bool exists(CStrRef key, bool isString = false) const;
  bool exists(CVarRef key) const;

  template<typename T>
  void removeImpl(const T &key) {
    if (m_px) {
      ArrayData *escalated =
        m_px->remove(key, (m_px->getCount() > 1));
      if (escalated) {
        SmartPtr<ArrayData>::operator=(escalated);
      }
    }
  }
  void remove(bool    key) {
    removeImpl(key ? 1LL : 0LL);
  }
  void remove(char    key) {
    removeImpl((int64)key);
  }
  void remove(short   key) {
    removeImpl((int64)key);
  }
  void remove(int     key) {
    removeImpl((int64)key);
  }
  void remove(int64   key) {
    removeImpl(key);
  }
  void remove(double  key) {
    removeImpl((int64)key);
  }
  void remove(litstr  key, bool isString = false);
  void remove(CStrRef key, bool isString = false);
  void remove(CVarRef key);

  void weakRemove(litstr  key, bool isString = false) {
    if (m_px) remove(key, isString);
  }
  void weakRemove(CStrRef key, bool isString = false) {
    if (m_px) remove(key, isString);
  }

  template<typename T>
  void weakRemove(const T &key) {
    if (m_px) remove(key);
  }

  void removeAll();
  void clear() { removeAll();}

  Variant append(CVarRef v);
  Variant appendOpEqual(int op, CVarRef v);
  Variant pop();
  Variant dequeue();
  void prepend(CVarRef v);

  /**
   * Input/Output
   */
  void serialize(VariableSerializer *serializer) const;
  void unserialize(VariableUnserializer *in);

  /**
   * Marshaling/Unmarshaling between request thread and fiber thread.
   */
  Array fiberMarshal(FiberReferenceMap &refMap) const;
  Array fiberUnmarshal(FiberReferenceMap &refMap) const;

  /**
   * Memory allocator methods.
   */
  DECLARE_SMART_ALLOCATION_NOCALLBACKS(Array);
  void dump();

  ArrayData *getArrayData() const {
    return m_px;
  }

  void setStatic() const {
    if (m_px) {
      m_px->setStatic();
      m_px->onSetStatic();
    }
  }

 private:
  // helpers
  bool compare(CArrRef v2) const;
  Array &mergeImpl(ArrayData *data, ArrayData::ArrayOp op);
  Array diffImpl(CArrRef array, bool by_key, bool by_value, bool match,
                 PFUNC_CMP key_cmp_function, const void *key_data,
                 PFUNC_CMP value_cmp_function, const void *value_data) const;

  template<typename T>
  Variant &lvalAtImpl(const T &key, bool checkExist = false) {
    if (!m_px) {
      SmartPtr<ArrayData>::operator=(ArrayData::Create());
    }
    Variant *ret = NULL;
    ArrayData *escalated =
      m_px->lval(key, ret, m_px->getCount() > 1, checkExist);
    if (escalated) {
      SmartPtr<ArrayData>::operator=(escalated);
    }
    ASSERT(ret);
    return *ret;
  }

  static void compileTimeAssertions() {
    CT_ASSERT(offsetof(Array, m_px) == offsetof(Value, m_data));
  }
};

///////////////////////////////////////////////////////////////////////////////

/**
 * A StaticArray can be co-accessed by multiple threads, therefore they are
 * not thread local, and they have to be allocated BEFORE any thread starts,
 * so that they won't be garbage collected by MemoryManager. This is used by
 * scalar arrays, so they can be pre-allocated before request handling.
 */
class StaticArray : public Array {
public:
  StaticArray() { }
  StaticArray(ArrayData *data) : Array(data) {
    m_px->setStatic();
    m_px->onSetStatic();
  }
  ~StaticArray() {
    // prevent ~SmartPtr from calling decRefCount after data is released
    m_px = NULL;
  }
};

///////////////////////////////////////////////////////////////////////////////
}

#endif // __HPHP_ARRAY_H__
