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
// @generated by HipHop Compiler

#ifndef __GENERATED_cls_BadMethodCallException_h__
#define __GENERATED_cls_BadMethodCallException_h__

#include <cls/BadFunctionCallException.h>

namespace HPHP {
///////////////////////////////////////////////////////////////////////////////

/* SRC: classes/exception.php line 175 */
class c_BadMethodCallException : public c_BadFunctionCallException {
  public:

  // Properties

  // Class Map
  BEGIN_CLASS_MAP(BadMethodCallException)
    PARENT_CLASS(BadFunctionCallException)
    PARENT_CLASS(Exception)
    PARENT_CLASS(LogicException)
  END_CLASS_MAP(BadMethodCallException)
  DECLARE_CLASS_COMMON(BadMethodCallException, BadMethodCallException)
  DECLARE_INVOKE_EX(BadMethodCallException, BadMethodCallException, BadFunctionCallException)

  // DECLARE_STATIC_PROP_OPS
  public:
  #define OMIT_JUMP_TABLE_CLASS_STATIC_GETINIT_BadMethodCallException 1
  #define OMIT_JUMP_TABLE_CLASS_STATIC_GET_BadMethodCallException 1
  #define OMIT_JUMP_TABLE_CLASS_STATIC_LVAL_BadMethodCallException 1
  #define OMIT_JUMP_TABLE_CLASS_CONSTANT_BadMethodCallException 1

  // DECLARE_INSTANCE_PROP_OPS
  public:
  #define OMIT_JUMP_TABLE_CLASS_GETARRAY_BadMethodCallException 1
  #define OMIT_JUMP_TABLE_CLASS_SETARRAY_BadMethodCallException 1
  #define OMIT_JUMP_TABLE_CLASS_realProp_BadMethodCallException 1
  #define OMIT_JUMP_TABLE_CLASS_realProp_PRIVATE_BadMethodCallException 1

  // DECLARE_INSTANCE_PUBLIC_PROP_OPS
  public:
  #define OMIT_JUMP_TABLE_CLASS_realProp_PUBLIC_BadMethodCallException 1

  // DECLARE_COMMON_INVOKE
  static bool os_get_call_info(MethodCallPackage &mcp, int64 hash = -1);
  #define OMIT_JUMP_TABLE_CLASS_STATIC_INVOKE_BadMethodCallException 1
  virtual bool o_get_call_info(MethodCallPackage &mcp, int64 hash = -1);

  public:
  DECLARE_INVOKES_FROM_EVAL
  void init();
};
extern struct ObjectStaticCallbacks cw_BadMethodCallException;

///////////////////////////////////////////////////////////////////////////////
}

#endif // __GENERATED_cls_BadMethodCallException_h__
