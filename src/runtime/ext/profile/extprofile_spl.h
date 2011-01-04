/*
   +----------------------------------------------------------------------+
   | HipHop for PHP                                                       |
   +----------------------------------------------------------------------+
   | Copyright (c) 2010 Facebook, Inc. (http://www.facebook.com)          |
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

#ifndef __EXTPROFILE_SPL_H__
#define __EXTPROFILE_SPL_H__

// >>>>>> Generated by idl.php. Do NOT modify. <<<<<<

#include <runtime/ext/ext_spl.h>

namespace HPHP {
///////////////////////////////////////////////////////////////////////////////

inline Array x_spl_classes() {
  FUNCTION_INJECTION_BUILTIN(spl_classes);
  TAINT_OBSERVER(TAINT_BIT_NONE, TAINT_BIT_NONE);
  return f_spl_classes();
}

inline String x_spl_object_hash(CObjRef obj) {
  FUNCTION_INJECTION_BUILTIN(spl_object_hash);
  TAINT_OBSERVER(TAINT_BIT_NONE, TAINT_BIT_NONE);
  return f_spl_object_hash(obj);
}

inline int64 x_hphp_object_pointer(CObjRef obj) {
  TAINT_OBSERVER(TAINT_BIT_NONE, TAINT_BIT_NONE);
  return f_hphp_object_pointer(obj);
}

inline Variant x_hphp_get_this() {
  TAINT_OBSERVER(TAINT_BIT_NONE, TAINT_BIT_NONE);
  return f_hphp_get_this();
}

inline Variant x_class_implements(CVarRef obj, bool autoload = true) {
  FUNCTION_INJECTION_BUILTIN(class_implements);
  TAINT_OBSERVER(TAINT_BIT_NONE, TAINT_BIT_NONE);
  return f_class_implements(obj, autoload);
}

inline Variant x_class_parents(CVarRef obj, bool autoload = true) {
  FUNCTION_INJECTION_BUILTIN(class_parents);
  TAINT_OBSERVER(TAINT_BIT_NONE, TAINT_BIT_NONE);
  return f_class_parents(obj, autoload);
}

inline Variant x_iterator_apply(CVarRef obj, CVarRef func, CArrRef params = null_array) {
  FUNCTION_INJECTION_BUILTIN(iterator_apply);
  TAINT_OBSERVER(TAINT_BIT_NONE, TAINT_BIT_NONE);
  return f_iterator_apply(obj, func, params);
}

inline Variant x_iterator_count(CVarRef obj) {
  FUNCTION_INJECTION_BUILTIN(iterator_count);
  TAINT_OBSERVER(TAINT_BIT_NONE, TAINT_BIT_NONE);
  return f_iterator_count(obj);
}

inline Variant x_iterator_to_array(CVarRef obj, bool use_keys = true) {
  FUNCTION_INJECTION_BUILTIN(iterator_to_array);
  TAINT_OBSERVER(TAINT_BIT_NONE, TAINT_BIT_NONE);
  return f_iterator_to_array(obj, use_keys);
}

inline void x_spl_autoload_call(CStrRef class_name) {
  FUNCTION_INJECTION_BUILTIN(spl_autoload_call);
  TAINT_OBSERVER(TAINT_BIT_NONE, TAINT_BIT_NONE);
  f_spl_autoload_call(class_name);
}

inline String x_spl_autoload_extensions(CStrRef file_extensions = null_string) {
  FUNCTION_INJECTION_BUILTIN(spl_autoload_extensions);
  TAINT_OBSERVER(TAINT_BIT_NONE, TAINT_BIT_NONE);
  return f_spl_autoload_extensions(file_extensions);
}

inline Variant x_spl_autoload_functions() {
  FUNCTION_INJECTION_BUILTIN(spl_autoload_functions);
  TAINT_OBSERVER(TAINT_BIT_NONE, TAINT_BIT_NONE);
  return f_spl_autoload_functions();
}

inline bool x_spl_autoload_register(CVarRef autoload_function = null_variant, bool throws = true, bool prepend = false) {
  FUNCTION_INJECTION_BUILTIN(spl_autoload_register);
  TAINT_OBSERVER(TAINT_BIT_NONE, TAINT_BIT_NONE);
  return f_spl_autoload_register(autoload_function, throws, prepend);
}

inline bool x_spl_autoload_unregister(CVarRef autoload_function) {
  FUNCTION_INJECTION_BUILTIN(spl_autoload_unregister);
  TAINT_OBSERVER(TAINT_BIT_NONE, TAINT_BIT_NONE);
  return f_spl_autoload_unregister(autoload_function);
}

inline void x_spl_autoload(CStrRef class_name, CStrRef file_extensions = null_string) {
  FUNCTION_INJECTION_BUILTIN(spl_autoload);
  TAINT_OBSERVER(TAINT_BIT_NONE, TAINT_BIT_NONE);
  f_spl_autoload(class_name, file_extensions);
}


///////////////////////////////////////////////////////////////////////////////
}

#endif // __EXTPROFILE_SPL_H__
