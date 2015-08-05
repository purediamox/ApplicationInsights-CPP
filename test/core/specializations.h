#ifndef SPECIALIZATIONS_H
#define SPECIALIZATIONS_H

#include "CppUnitTest.h"
#include "Contracts/Contracts.h"
#include "TelemetryClient.h"
#include "common/JsonWriter.hpp"
#include "common/StringWriter.hpp"

using namespace ApplicationInsights::core;
namespace Microsoft{ namespace VisualStudio { namespace CppUnitTestFramework {
	template<> inline std::wstring ToString<TelemetryClient>						(TelemetryClient* t)								{ RETURN_WIDE_STRING(t); }
    template<> inline std::wstring ToString<CrashDataHeaders>                       (CrashDataHeaders* t)		                        { RETURN_WIDE_STRING(t); }
    template<> inline std::wstring ToString<Base>                                   (Base* t)           		                        { RETURN_WIDE_STRING(t); }
    template<> inline std::wstring ToString<DependencySourceType>                   (const DependencySourceType& t)                     { RETURN_WIDE_STRING(t); }
    template<> inline std::wstring ToString<DataPointType>                          (const DataPointType& t)                            { RETURN_WIDE_STRING(t); }
    template<> inline std::wstring ToString<DependencyKind>                         (const DependencyKind& t)                           { RETURN_WIDE_STRING(t); }
    template<> inline std::wstring ToString<SessionState>                           (const SessionState& t)                             { RETURN_WIDE_STRING(t); }
    template<> inline std::wstring ToString<std::map<std::wstring, std::wstring>>   (const std::map<std::wstring, std::wstring>& t)     { RETURN_WIDE_STRING("dictionary"); }
    template<> inline std::wstring ToString<std::map<std::wstring, double>>         (const std::map<std::wstring, double>& t)           { RETURN_WIDE_STRING("dictionary"); }
    template<> inline std::wstring ToString<std::vector<StackFrame*>>               (const std::vector<StackFrame*>& t)                 { RETURN_WIDE_STRING("vector"); }
    template<> inline std::wstring ToString<std::vector<ExceptionDetails*>>         (const std::vector<ExceptionDetails*>& t)           { RETURN_WIDE_STRING("vector"); }
    template<> inline std::wstring ToString<std::vector<DataPoint*>>                (const std::vector<DataPoint*>& t)                  { RETURN_WIDE_STRING("vector"); }
    template<> inline std::wstring ToString<std::vector<CrashDataThreadFrame*>>     (const std::vector<CrashDataThreadFrame*>& t)       { RETURN_WIDE_STRING("vector"); }
    template<> inline std::wstring ToString<std::vector<CrashDataThread*>>          (const std::vector<CrashDataThread*>& t)            { RETURN_WIDE_STRING("vector"); }
    template<> inline std::wstring ToString<std::vector<CrashDataBinary*>>          (const std::vector<CrashDataBinary*>& t)            { RETURN_WIDE_STRING("vector"); }
    template<> inline std::wstring ToString<Nullable<int>>                          (const Nullable<int>& t)                            { RETURN_WIDE_STRING("nullable"); }
    template<> inline std::wstring ToString<Nullable<double>>                       (const Nullable<double>& t)                         { RETURN_WIDE_STRING("nullable"); }
    template<> inline std::wstring ToString<Nullable<bool>>                         (const Nullable<bool>& t)                           { RETURN_WIDE_STRING("nullable"); }
    template<> inline std::wstring ToString<Nullable<std::wstring>>                 (const Nullable<std::wstring>& t)                   { RETURN_WIDE_STRING("nullable"); }
    template<> inline std::wstring ToString<Nullable<SeverityLevel>>                (const Nullable<SeverityLevel>& t)                  { RETURN_WIDE_STRING("nullable"); }
}}};

#endif