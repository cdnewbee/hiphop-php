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

#ifndef __EXT_MEMCACHEPOOL_H__
#define __EXT_MEMCACHEPOOL_H__

// >>>>>> Generated by idl.php. Do NOT modify. <<<<<<

#include <runtime/base/base_includes.h>
#include <libmemcached/memcached.h>
namespace HPHP {
///////////////////////////////////////////////////////////////////////////////

extern const int64 k_MEMCACHE_COMPRESSED;
extern const int64 k_MEMCACHE_SERIALIZED;

///////////////////////////////////////////////////////////////////////////////
// class MemcachePool

FORWARD_DECLARE_CLASS_BUILTIN(MemcachePool);
class c_MemcachePool : public ExtObjectData, public Sweepable {
 public:
  DECLARE_CLASS(MemcachePool, MemcachePool, ObjectData)

  // need to implement
  public: c_MemcachePool(const ObjectStaticCallbacks *cb = &cw_MemcachePool);
  public: ~c_MemcachePool();
  public: void t___construct();
  DECLARE_METHOD_INVOKE_HELPERS(__construct);
  public: static Object ti_getstoragememcache(const char* cls , int storage_id, int timestamp, VRefParam empty, bool persistent = false);
  public: static Object t_getstoragememcache(int storage_id, int timestamp, VRefParam empty, bool persistent = false) {
    return ti_getstoragememcache("memcachepool", storage_id, timestamp, empty, persistent);
  }
  DECLARE_METHOD_INVOKE_HELPERS(getstoragememcache);
  public: bool t_connect(CStrRef host, int port = 0, int timeout = 0, int timeoutms = 0);
  DECLARE_METHOD_INVOKE_HELPERS(connect);
  public: bool t_pconnect(CStrRef host, int port = 0, int timeout = 0, int timeoutms = 0);
  DECLARE_METHOD_INVOKE_HELPERS(pconnect);
  public: bool t_add(CStrRef key, CVarRef var, int flag = 0, int expire = 0);
  DECLARE_METHOD_INVOKE_HELPERS(add);
  public: bool t_cas(CStrRef key, CVarRef var, int flag, int expire, double cas_token);
  DECLARE_METHOD_INVOKE_HELPERS(cas);
  public: bool t_set(CStrRef key, CVarRef var, int flag = 0, int expire = 0);
  DECLARE_METHOD_INVOKE_HELPERS(set);
  public: bool t_replace(CStrRef key, CVarRef var, int flag = 0, int expire = 0);
  DECLARE_METHOD_INVOKE_HELPERS(replace);
  public: Variant t_get(CVarRef key, VRefParam flags = null, VRefParam cas = null);
  DECLARE_METHOD_INVOKE_HELPERS(get);
  public: bool t_delete(CStrRef key, int expire = 0);
  DECLARE_METHOD_INVOKE_HELPERS(delete);
  public: Variant t_increment(CStrRef key, int offset = 1);
  DECLARE_METHOD_INVOKE_HELPERS(increment);
  public: Variant t_decrement(CStrRef key, int offset = 1);
  DECLARE_METHOD_INVOKE_HELPERS(decrement);
  public: Variant t_getversion();
  DECLARE_METHOD_INVOKE_HELPERS(getversion);
  public: bool t_flush(int expire = 0);
  DECLARE_METHOD_INVOKE_HELPERS(flush);
  public: bool t_setoptimeout(int64 timeoutms);
  DECLARE_METHOD_INVOKE_HELPERS(setoptimeout);
  public: bool t_close();
  DECLARE_METHOD_INVOKE_HELPERS(close);
  public: int t_getserverstatus(CStrRef host, int port = 0);
  DECLARE_METHOD_INVOKE_HELPERS(getserverstatus);
  public: bool t_setcompressthreshold(int threshold, double min_savings = 0.2);
  DECLARE_METHOD_INVOKE_HELPERS(setcompressthreshold);
  public: Array t_getstats(CStrRef type = null_string, int slabid = 0, int limit = 100);
  DECLARE_METHOD_INVOKE_HELPERS(getstats);
  public: Array t_getextendedstats(CStrRef type = null_string, int slabid = 0, int limit = 100);
  DECLARE_METHOD_INVOKE_HELPERS(getextendedstats);
  public: bool t_setserverparams(CStrRef host, int port = 11211, int timeout = 0, int retry_interval = 0, bool status = true);
  DECLARE_METHOD_INVOKE_HELPERS(setserverparams);
  public: bool t_setfailurecallback(CVarRef failure_callback = null_variant);
  DECLARE_METHOD_INVOKE_HELPERS(setfailurecallback);
  public: bool t_addserver(CStrRef host, int tcp_port = 11211, int udp_port = 11211, bool persistent = false, int weight = 0, int timeout = 0, int retry_interval = 0, bool status = true);
  DECLARE_METHOD_INVOKE_HELPERS(addserver);
  public: Variant t___destruct();
  DECLARE_METHOD_INVOKE_HELPERS(__destruct);

  // implemented by HPHP
  public: c_MemcachePool *create();
  private: 
    bool check_memcache_return(memcached_st * st, memcached_return_t ret, 
                               String key = "", char *default_msg = "");
    void exec_failure_callback(const char * hostname, int tcp_port, int udp_port,
                               memcached_return_t ret, const char * error, Array backtrace);
};

///////////////////////////////////////////////////////////////////////////////
}

#endif // __EXT_MEMCACHEPOOL_H__
