// ***********************************************************************
// Filename         : ScopeExitGuard.h
// Author           : LIZHENG
// Created          : 2014-10-01
// Description      : RAII�࣬������Դ�ͷš�����
//
// Last Modified By : LIZHENG
// Last Modified On : 2015-01-11
//
// Copyright (c) lizhenghn@gmail.com. All rights reserved.
// ***********************************************************************
#ifndef ZL_SCOPEEXITGUARD_H
#define ZL_SCOPEEXITGUARD_H
#include <functional>

#define SCOPEGUARD_LINENAME_CAT(name, line) name##line
#define SCOPEGUARD_LINENAME(name, line)     SCOPEGUARD_LINENAME_CAT(name, line)

#define ON_SCOPE_EXIT(callback) zl::base::ScopeExitGuard SCOPEGUARD_LINENAME(EXIT, __LINE__)(callback)

namespace zl
{
namespace base
{

class ScopeExitGuard
{
public:
    explicit ScopeExitGuard(std::function<void ()> onExitCallback)
        : onExitCb_(onExitCallback), dismissed_(false)
    {
    }

    ~ScopeExitGuard()
    {
        if(!dismissed_)
        {
            onExitCb_();
        }
    }

    void dismiss()
    {
        dismissed_ = true;
    }

private:
    std::function<void()> onExitCb_;
    bool dismissed_;

private:
    ScopeExitGuard(ScopeExitGuard const&);
    ScopeExitGuard& operator=(ScopeExitGuard const&);
};

}
}
#endif  /* ZL_SCOPEEXITGUARD_H */