#ifndef TRACELOGGINGHELPER_H
#define TRACELOGGINGHELPER_H
#include <windows.h>
#include "../Common/Common.h"
#include "../Common/TraceLoggingProvider.h"
//#include <TraceLoggingProvider.h>
#include <TraceLoggingActivity.h>  
#include "../Contracts/Contracts.h"

namespace ApplicationInsights
{
	namespace core
	{
		//typedef unsigned char BYTE;
		//typedef int32 INT32;
		//typedef double DOUBLE;
		//typedef wchar_t const* LPCWSTR;

		union __number
		{
			BYTE bytes[8];
			DOUBLE d;
			INT32 i;
		};


		class TELEMETRYCLIENT_API TraceLoggingHelper
		{
		public:
			TraceLoggingHelper();

			~TraceLoggingHelper();

			void LogPartBData(std::wstring iKey, wstring_wstring_map tags, Domain &data);

			bool IsLoggingEnabled();

			template<class T>
			void AddArray(std::vector<BYTE>& buffer, int count, _In_count_(count) const std::vector<T*> items)
			{
				// Add the array count
				buffer.push_back(count & 0xFF);
				buffer.push_back(count >> 8);

				for (unsigned i = 0; i != count; i++)
				{
					Add(buffer, items[i]);
				}
			}

			template<class T>
			void AddArray(std::vector<BYTE>& buffer, int count, _In_count_(count) const std::map<std::wstring, T> items)
			{
				// Add the array count
				buffer.push_back(count & 0xFF);
				buffer.push_back(count >> 8);

				for (auto i = items.begin(); i != items.end(); i++)
				{
					Add(buffer, i->first);
					Add(buffer, i->second);
				}
			}

			void Add(std::vector<BYTE>& buffer, ExceptionDetails *details); // ExceptionDetails			
			void Add(std::vector<BYTE>& buffer, DataPoint *metric); // dataPoint			
			void Add(std::vector<BYTE>& buffer, INT32 value); // int			
			void Add(std::vector<BYTE>& buffer, double value); // double			
			void Add(std::vector<BYTE>& buffer, std::wstring str); // wchar_t string

			void LogMetric(std::wstring iKey, wstring_wstring_map tags, MetricData* metric);
			void LogEvent(std::wstring iKey, wstring_wstring_map tags, EventData* eventData);
			void LogPageView(std::wstring iKey, wstring_wstring_map tags, PageViewData* pageViewData);
			void LogPageViewPerf(std::wstring iKey, wstring_wstring_map tags, PageViewPerfData* pageViewPerfData);
			void LogMessage(std::wstring iKey, wstring_wstring_map tags, MessageData* messageData);
			void LogException(std::wstring iKey, wstring_wstring_map tags, ExceptionData* exceptionData);
		};
	}
}
#endif