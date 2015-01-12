﻿// ***********************************************************************
// Filename         : SmartAssert.h
// Author           : LIZHENG
// Created          : 2014-09-18
// Description      : 增强版的Assert实现
// 
// Last Modified By : LIZHENG
// Last Modified On : 2015-01-11
//
// Copyright (c) lizhenghn@gmail.com. All rights reserved.
// ***********************************************************************
#ifndef ZL_SMARTASSERT_H
#define ZL_SMARTASSERT_H
#include <string>
#include <sstream>
namespace zl
{
namespace base
{

#define ENABLE_SMART_ASSERT_MODE  //enable ZL_ASSERT macro, use in Debug/Release env 

#define ABORT_IF_ASSERT_FAILED    // if assert failed, abort(), except ZL_ASSERT_LOG

class SmartAssert
{
public:
    SmartAssert(const char* expr, const char* function, int line, const char* file, bool abort = false)
        : SMART_ASSERT_A(*this),
          SMART_ASSERT_B(*this),
          abortIfExit_(abort)
    {
        if (expr && *expr)
            oss_ << "Expression Failed: " << expr << "\n";
        if(function && *function) 
            oss_ << "Failed in [func: " << function << "], [line: " << line << "], [file: " << file << "]\n";
        
    }

    ~SmartAssert()
    {
        std::cerr << oss_.str() << "\n";

        if(abortIfExit_)
        {
        #if defined(ABORT_IF_ASSERT_FAILED)
            abort();
        #endif
        }
    }

    template< typename T>
    SmartAssert& printValiable(const char* expr, const T& value)
    {
        oss_ << "ContextValiable: [" << expr << " = " << value << "]\n";
        return *this;
    }

public:
    SmartAssert& SMART_ASSERT_A;
    SmartAssert& SMART_ASSERT_B;

private:
    bool  abortIfExit_;
    std::ostringstream oss_;
};

static SmartAssert MakeAssert(const char* expr, const char* function, int line, const char* file, bool abort)
{
    return SmartAssert(expr, function, line, file, abort);
}

static SmartAssert __dont_use_this__ = MakeAssert(NULL, NULL, 0, 0, false);  //gcc: MakeAssert 定义未使用[-Wunused-function]

// run time assert
#ifndef ENABLE_SMART_ASSERT_MODE

#define ZL_ASSERT(expr)      ((void) 0)
#define ZL_ASSERTEX(expr, func, lineno , file)   ((void) 0)
#define ZL_ASSERT_LOG(expr)  ((void) 0)

#else

#define SMART_ASSERT_A(x)        SMART_ASSERT_OP(x, B)
#define SMART_ASSERT_B(x)        SMART_ASSERT_OP(x, A)
#define SMART_ASSERT_OP(x, next) SMART_ASSERT_A.printValiable(#x, (x)).SMART_ASSERT_##next

#define ZL_ASSERT(expr)          \
            if( (expr) ) ;       \
            else zl::base::MakeAssert(#expr, __FUNCTION__, __LINE__, __FILE__, true).SMART_ASSERT_A

#define ZL_ASSERTEX(expr, func, lineno , file) \
            if( (expr) ) ;                     \
            else zl::base::MakeAssert( #expr, func, lineno, file, true).SMART_ASSERT_A

#define ZL_ASSERT_LOG(expr)       \
            if( (expr) ) ;        \
            else zl::base::MakeAssert(#expr, __FUNCTION__, __LINE__, __FILE__, false).SMART_ASSERT_A

#endif

// compile time assert
#define ZL_STATIC_ASSERT(expr) ZL_STATIC_ASSERT_IMPL(expr, __FILE__, __LINE__)
#define ZL_STATIC_ASSERT_IMPL(expr, file, line)  \
                typedef char static_assert_fail_on_##file_and_##line[2 * ((expr) != 0) - 1]

}
}
#endif  /* ZL_SMARTASSERT_H */
