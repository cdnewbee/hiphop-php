/*
   +----------------------------------------------------------------------+
   | HipHop for PHP                                                       |
   +----------------------------------------------------------------------+
   | Copyright (c) 2010- Facebook, Inc. (http://www.facebook.com)         |
   | Copyright (c) 1997-2010 The PHP Group                                |
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

#include <runtime/ext/ext_datetime.h>

namespace HPHP {
IMPLEMENT_DEFAULT_EXTENSION(date);
///////////////////////////////////////////////////////////////////////////////
// constants

const StaticString q_DateTime___ATOM(LITSTR_INIT("Y-m-d\\TH:i:sP"));
const StaticString q_DateTime___COOKIE(LITSTR_INIT("l, d-M-y H:i:s T"));
const StaticString q_DateTime___ISO8601(LITSTR_INIT("Y-m-d\\TH:i:sO"));
const StaticString q_DateTime___RFC822(LITSTR_INIT("D, d M y H:i:s O"));
const StaticString q_DateTime___RFC850(LITSTR_INIT("l, d-M-y H:i:s T"));
const StaticString q_DateTime___RFC1036(LITSTR_INIT("D, d M y H:i:s O"));
const StaticString q_DateTime___RFC1123(LITSTR_INIT("D, d M Y H:i:s O"));
const StaticString q_DateTime___RFC2822(LITSTR_INIT("D, d M Y H:i:s O"));
const StaticString q_DateTime___RFC3339(LITSTR_INIT("Y-m-d\\TH:i:sP"));
const StaticString q_DateTime___RSS(LITSTR_INIT("D, d M Y H:i:s O"));
const StaticString q_DateTime___W3C(LITSTR_INIT("Y-m-d\\TH:i:sP"));

const int64 q_DateTimeZone___AFRICA = 1;
const int64 q_DateTimeZone___AMERICA = 2;
const int64 q_DateTimeZone___ANTARCTICA = 4;
const int64 q_DateTimeZone___ARCTIC = 8;
const int64 q_DateTimeZone___ASIA = 16;
const int64 q_DateTimeZone___ATLANTIC = 32;
const int64 q_DateTimeZone___AUSTRALIA = 64;
const int64 q_DateTimeZone___EUROPE = 128;
const int64 q_DateTimeZone___INDIAN = 256;
const int64 q_DateTimeZone___PACIFIC = 512;
const int64 q_DateTimeZone___UTC = 1024;
const int64 q_DateTimeZone___ALL = 2047;
const int64 q_DateTimeZone___ALL_WITH_BC = 4095;
const int64 q_DateTimeZone___PER_COUNTRY = 4096;

///////////////////////////////////////////////////////////////////////////////
// methods

c_DateTime::c_DateTime(const ObjectStaticCallbacks *cb) : ExtObjectData(cb) {
}

c_DateTime::~c_DateTime() {
}

void c_DateTime::t___construct(CStrRef time /*= "now"*/,
                               CObjRef timezone /*= null_object*/) {
  INSTANCE_METHOD_INJECTION_BUILTIN(DateTime, DateTime::__construct);
  m_dt = NEWOBJ(DateTime)(TimeStamp::Current());
  if (!time.empty()) {
    m_dt->fromString(time, c_DateTimeZone::unwrap(timezone));
  }
}

String c_DateTime::t_format(CStrRef format) {
  INSTANCE_METHOD_INJECTION_BUILTIN(DateTime, DateTime::format);
  return m_dt->toString(format, false);
}

int64 c_DateTime::t_getoffset() {
  INSTANCE_METHOD_INJECTION_BUILTIN(DateTime, DateTime::getoffset);
  return m_dt->offset();
}

Variant c_DateTime::t_gettimezone() {
  INSTANCE_METHOD_INJECTION_BUILTIN(DateTime, DateTime::gettimezone);
  SmartObject<TimeZone> tz = m_dt->timezone();
  if (tz->isValid()) {
    return c_DateTimeZone::wrap(tz);
  }
  return false;
}

Object c_DateTime::t_modify(CStrRef modify) {
  INSTANCE_METHOD_INJECTION_BUILTIN(DateTime, DateTime::modify);
  m_dt->modify(modify);
  return this;
}

Object c_DateTime::t_setdate(int64 year, int64 month, int64 day) {
  INSTANCE_METHOD_INJECTION_BUILTIN(DateTime, DateTime::setdate);
  m_dt->setDate(year, month, day);
  return this;
}

Object c_DateTime::t_setisodate(int64 year, int64 week, int64 day /*= 1*/) {
  INSTANCE_METHOD_INJECTION_BUILTIN(DateTime, DateTime::setisodate);
  m_dt->setISODate(year, week, day);
  return this;
}

Object c_DateTime::t_settime(int64 hour, int64 minute, int64 second /*= 0*/) {
  INSTANCE_METHOD_INJECTION_BUILTIN(DateTime, DateTime::settime);
  m_dt->setTime(hour, minute, second);
  return this;
}

Object c_DateTime::t_settimezone(CObjRef timezone) {
  INSTANCE_METHOD_INJECTION_BUILTIN(DateTime, DateTime::settimezone);
  m_dt->setTimezone(c_DateTimeZone::unwrap(timezone));
  return this;
}

int64 c_DateTime::t_gettimestamp() {
  INSTANCE_METHOD_INJECTION_BUILTIN(DateTime, DateTime::gettimestamp);
  bool error;
  return m_dt->toTimeStamp(error);
}

Object c_DateTime::t_settimestamp(int64 timestamp) {
  INSTANCE_METHOD_INJECTION_BUILTIN(DateTime, DateTime::settimestamp);
  m_dt->fromTimeStamp(timestamp);
  return this;
}

Variant c_DateTime::t___destruct() {
  INSTANCE_METHOD_INJECTION_BUILTIN(DateTime, DateTime::__destruct);
  return null;
}

ObjectData *c_DateTime::clone() {
  ObjectData *obj = ObjectData::clone();
  c_DateTime *dt = static_cast<c_DateTime*>(obj);
  dt->m_dt = m_dt->cloneDateTime();
  return obj;
}

c_DateTimeZone::c_DateTimeZone(const ObjectStaticCallbacks *cb) :
    ExtObjectData(cb) {
}

c_DateTimeZone::~c_DateTimeZone() {
}

void c_DateTimeZone::t___construct(CStrRef timezone) {
  INSTANCE_METHOD_INJECTION_BUILTIN(DateTimeZone, DateTimeZone::__construct);
  m_tz = NEWOBJ(TimeZone)(timezone);
  if (!m_tz->isValid()) {
    raise_error("DateTimeZone::__construct(): Unknown or bad timezone (%s)",
                timezone.data());
  }
}

String c_DateTimeZone::t_getname() {
  INSTANCE_METHOD_INJECTION_BUILTIN(DateTimeZone, DateTimeZone::getname);
  return m_tz->name();
}

int64 c_DateTimeZone::t_getoffset(CObjRef datetime) {
  INSTANCE_METHOD_INJECTION_BUILTIN(DateTimeZone, DateTimeZone::getoffset);
  bool error;
  int64 ts = c_DateTime::unwrap(datetime)->toTimeStamp(error);
  return m_tz->offset(ts);
}

Array c_DateTimeZone::t_gettransitions() {
  INSTANCE_METHOD_INJECTION_BUILTIN(DateTimeZone, DateTimeZone::gettransitions);
  return m_tz->transitions();
}

Array c_DateTimeZone::ti_listabbreviations(const char* cls) {
  STATIC_METHOD_INJECTION_BUILTIN(DateTimeZone, DateTimeZone::listabbreviations);
  return TimeZone::GetAbbreviations();
}

Array c_DateTimeZone::ti_listidentifiers(const char* cls) {
  STATIC_METHOD_INJECTION_BUILTIN(DateTimeZone, DateTimeZone::listidentifiers);
  return TimeZone::GetNames();
}

Variant c_DateTimeZone::t___destruct() {
  INSTANCE_METHOD_INJECTION_BUILTIN(DateTimeZone, DateTimeZone::__destruct);
  return null;
}

ObjectData *c_DateTimeZone::clone() {
  ObjectData *obj = ObjectData::clone();
  c_DateTimeZone *dtz = static_cast<c_DateTimeZone*>(obj);
  dtz->m_tz = m_tz->cloneTimeZone();
  return obj;
}

///////////////////////////////////////////////////////////////////////////////
}
