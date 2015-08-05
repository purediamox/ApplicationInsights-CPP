#ifndef SPECIALIZATIONS_H
#define SPECIALIZATIONS_H

#include "CppUnitTest.h"
#include <regex>

typedef std::wregex wre;
#define wre_match(input, wregex) std::regex_match(input, wregex)

using namespace ApplicationInsights::CX;
namespace Microsoft{ namespace VisualStudio { namespace CppUnitTestFramework {
	
}}};

#endif