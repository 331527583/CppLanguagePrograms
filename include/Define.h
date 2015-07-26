// ***********************************************************************
// Filename         : Define.h
// Author           : LIZHENG
// Created          : 2014-07-01
// Description      :
//
// Copyright (c) lizhenghn@gmail.com. All rights reserved.
// ***********************************************************************
#ifndef ZL_STDDEFINE_H
#define ZL_STDDEFINE_H
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>
#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include <functional>
#include <iterator>
#include <numeric>
#include <stdint.h>
#define __STDC_FORMAT_MACROS
//#include <inttypes.h>           // printf("%"PRId64"\n", (int64_t)value);  
#undef __STDC_FORMAT_MACROS
#include "OsDefine.h"
#include "base/SmartAssert.h"
#ifdef OS_WINDOWS
#define  _WINSOCKAPI_
#include <Windows.h>
#endif
using std::string;
using std::vector;
using std::list;
using std::queue;
using std::map;
using std::set;
using std::multimap;
using std::multiset;

#if defined(__GXX_EXPERIMENTAL_CXX0X__) || __cplusplus > 199711L || __cplusplus == 201103L
#define ZL_CXX11_ENABLED 1
#endif

#define NAMESPACE_ZL_START        namespace zl {
#define NAMESPACE_ZL_END          }  /* namespace zl */

#define NAMESPACE_ZL_BASE_START   NAMESPACE_ZL_START namespace base {
#define NAMESPACE_ZL_BASE_END     } }  /* namespace zl::base */

#define NAMESPACE_ZL_THREAD_START NAMESPACE_ZL_START namespace thread {
#define NAMESPACE_ZL_THREAD_END   } }  /* namespace zl::thread */

#define NAMESPACE_ZL_NET_START    NAMESPACE_ZL_START namespace net {
#define NAMESPACE_ZL_NET_END      } }  /* namespace zl::net */

#define NAMESPACE_ZL_UTIL_START   NAMESPACE_ZL_START namespace util {
#define NAMESPACE_ZL_UTIL_END     } }  /* namespace zl::util */


#ifdef OS_WINDOWS
#define ZL_SNPRINTF  _snprintf
#else
#define ZL_SNPRINTF  snprintf
#endif

#define ZL_UNUSED(statement)    ((void)(statement))     /** just disable some warnings of compliers */

#define Safe_Delete(p)        do { delete p; p = NULL; } while (0)
#define Safe_Delete_Array(p)  do { delete[] p; p = NULL; } while (0)

#ifdef ZL_CXX11_ENABLED
#define DISALLOW_COPY_AND_ASSIGN(TypeName)            \
        TypeName(const TypeName&) = delete;           \
        TypeName& operator=(const TypeName&) = delete
#else
#define DISALLOW_COPY_AND_ASSIGN(TypeName)            \
        private:                                      \
            TypeName(const TypeName&);                \
            TypeName& operator=(const TypeName&)      
#endif

#define USE_TRY_CATCH
#ifdef  USE_TRY_CATCH
#define ZL_TRY_BEGIN  try {
#define ZL_CATCH(x)   } catch (x) {
#define ZL_CATCH_ALL  } catch (...) {
#define ZL_CATCH_END  }

#define ZL_RAISE(x)   throw (x)
#define ZL_RERAISE    throw
#define ZL_THROWS(x)  throw (x)

#else    // USE_TRY_CATCH
#define ZL_TRY_BEGIN  {{
#define ZL_CATCH(x)   } if (0) {
#define ZL_CATCH_ALL  } if (0) {
#define ZL_CATCH_END  }}

#define ZL_RAISE(x)   
#define ZL_RERAISE    
#define ZL_THROWS(x)  
#endif    // USE_TRY_CATCH

#endif /* ZL_STDDEFINE_H */
