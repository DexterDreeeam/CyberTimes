#pragma once

#define NS_BEG  namespace ct {
#define NS_END  }

#define ExMsg(m) __FILE__##", "##__FUNC__##m

#define AppNameStr  "CyberTimes"
#define AppTitleStr "Cyber Times"

typedef   unsigned long long   u64;
typedef            long long   s64;
typedef   unsigned      long   u32;
typedef                 long   s32;
typedef   unsigned      short  u16;
typedef                 short  s16;
typedef   unsigned      char   u8;
typedef                 char   s8;

#include "cpp_std.hpp"
#include "exception.hpp"
#include "InsBase.hpp"
#include "SystemConfig.hpp"
