#include "TraceLoggingHelper.h"
#include "../Contracts/Contracts.h"

using namespace ApplicationInsights::core;

//#include <TraceLoggingProvider.h>  
//#include <TraceLoggingActivity.h>  

#ifdef __cplusplus  
extern "C" {
#endif  
	TRACELOGGING_DECLARE_PROVIDER(g_hAppInsightsProvider);
#ifdef __cplusplus  
}
#endif  

#define TraceLoggingOptionMicrosoftTelemetry() \
TraceLoggingOptionGroup(0x0d943590, 0xb235, 0x5bdb, 0xf8, 0x54, 0x89, 0x52, 0x0f, 0x32, 0xfc, 0x0b)  //{0d943590-b235-5bdb-f854-8952-0f32fc0b}

#define MICROSOFT_KEYWORD_TELEMETRY     0x0000200000000000 

TRACELOGGING_DEFINE_PROVIDER(
	g_hAppInsightsProvider,
	"ApplicationInsightsProvider",
	(0x1FFB0DCF, 0x15A6, 0x42FA, 0x83, 0x9B, 0x1F, 0xB1, 0x83, 0xAF, 0x7B, 0x0A),// {1FFB0DCF-15A6-42FA-839B-1FB183AF7B0A}
	TraceLoggingOptionMicrosoftTelemetry());

TraceLoggingHelper::TraceLoggingHelper()
{
	HRESULT hResult = TraceLoggingRegister(g_hAppInsightsProvider);
}

TraceLoggingHelper::~TraceLoggingHelper()
{
	TraceLoggingUnregister(g_hAppInsightsProvider);
}

bool TraceLoggingHelper::IsLoggingEnabled()
{
	return TraceLoggingProviderEnabled(g_hAppInsightsProvider, 0, 0);
}

void TraceLoggingHelper::LogPartBData(Domain &data)
{

	TraceLoggingWrite(
		g_hAppInsightsProvider,
		"TEST",
		TraceLoggingKeyword(MICROSOFT_KEYWORD_TELEMETRY),
		TraceLoggingWideString(L"TESTING", "Test Message")
		);

	std::wstring baseType = data.GetBaseType();
	if (baseType == L"MetricData")
	{
		LogMetric((MetricData*)&data);
	}
	else if (baseType == L"EventData")
	{
		LogEvent((EventData*)&data);
	}
	else if (baseType == L"PageViewData")
	{
		LogPageView((PageViewData*)&data);
	}
	else if (baseType == L"PageViewPerfData")
	{
		LogPageViewPerf((PageViewPerfData*)&data);
	}
	else if (baseType == L"MessageData")
	{
		LogMessage((MessageData*)&data);
	}
	/*else if (baseType == L"ExceptionData")
	{
	LogException((ExceptionData*)&data);
	}*/
}

void TraceLoggingHelper::Add(std::vector<BYTE>& buffer, ExceptionDetails *details) // ExceptionDetails
{
	//TODO
	//int cbStackFrameData = (int)exceptionData.Get().size();
	//AddArray(pbStackFrameData, cbStackFrameData, exceptionData.GetExceptions());
}

void TraceLoggingHelper::Add(std::vector<BYTE>& buffer, DataPoint *metric) // dataPoint
{
	Add(buffer, metric->GetName().c_str());  //name	
	Add(buffer, (INT32)metric->GetKind());  //kind	
	Add(buffer, (DOUBLE)metric->GetValue());  //value

	if (metric->GetCount().HasValue())
	{
		Add(buffer, (INT32)metric->GetCount().GetValue());  //count	
	}
	else
	{
		Add(buffer, (INT32)0);  //count default value
	}

	if (metric->GetMin().HasValue())
	{
		Add(buffer, (DOUBLE)metric->GetMin().GetValue());  //min	
	}
	else
	{
		Add(buffer, (DOUBLE)0);  //min default value
	}

	if (metric->GetMax().HasValue())
	{
		Add(buffer, (DOUBLE)metric->GetMax().GetValue());  //max	
	}
	else
	{
		Add(buffer, (DOUBLE)0);  //max default value
	}

	if (metric->GetStdDev().HasValue())
	{
		Add(buffer, (DOUBLE)metric->GetStdDev().GetValue());  //std dev	
	}
	else
	{
		Add(buffer, (DOUBLE)0);  //std dev default value
	}
}

void TraceLoggingHelper::Add(std::vector<BYTE>& buffer, INT32 value) // int
{
	__number Int;
	Int.i = value;

	for (int i = 3; i >= 0; i--)
	{
		buffer.push_back(Int.bytes[i]);  //Last byte
	}

}

void TraceLoggingHelper::Add(std::vector<BYTE>& buffer, double value) // double
{
	__number Double;
	Double.d = value;

	for (int i = 7; i >= 0; i--)
	{
		buffer.push_back(Double.bytes[i]);  //Last byte
	}
}

void TraceLoggingHelper::Add(std::vector<BYTE>& buffer, std::wstring str) // wchar_t string
{
	if (str.length() > 0)
	{
		for (LPCWSTR p = str.c_str(); *p != 0; p++)
		{
			buffer.push_back((BYTE)(*p & 0xFF));
			buffer.push_back((BYTE)(*p >> 8));
		}
	}

	// add a nul-termination wchar_t
	buffer.push_back(0);
	buffer.push_back(0);
}

void TraceLoggingHelper::LogMetric(MetricData* metric)
{
	if (metric == nullptr)
	{
		return;
	}

	std::vector<BYTE> MetricData;
	std::vector<BYTE> PropData;

	AddArray(MetricData, (int)metric->GetMetrics().size(), metric->GetMetrics());
	AddArray(PropData, (int)metric->GetProperties().size(), metric->GetProperties());

	TraceLoggingWrite(
		g_hAppInsightsProvider,
		"Part B data",
		TraceLoggingKeyword(MICROSOFT_KEYWORD_TELEMETRY),
		TraceLoggingStruct(2, "Data"),
		TraceLoggingWideString(metric->GetBaseType().c_str(), "baseType"),
		TraceLoggingStruct(3, "baseData"),
		TraceLoggingInt32(metric->GetVer(), "ver"),
		TraceLoggingPackedData(&MetricData[0], MetricData.size()),		//content
			TraceLoggingPackedStructArray(7, "metrics"),
			TraceLoggingPackedMetadata(TlgInCOUNTEDSTRING, "name"),
			TraceLoggingPackedMetadata(TlgInINT32, "kind"),
			TraceLoggingPackedMetadata(TlgInDOUBLE, "value"),
			TraceLoggingPackedMetadata(TlgInINT32, "count"),
			TraceLoggingPackedMetadata(TlgInDOUBLE, "min"),
			TraceLoggingPackedMetadata(TlgInDOUBLE, "max"),
			TraceLoggingPackedMetadata(TlgInDOUBLE, "stdDev"),
		TraceLoggingPackedData(&PropData[0], PropData.size()),		//content
			TraceLoggingPackedStructArray(2, "properties"),
			TraceLoggingPackedMetadata(TlgInCOUNTEDSTRING, "key"),
			TraceLoggingPackedMetadata(TlgInCOUNTEDSTRING, "value")
		);
}

void TraceLoggingHelper::LogEvent(EventData* eventData)
{
	if (eventData == nullptr)
	{
		return;
	}

	std::vector<BYTE> pbMeasurementData;
	std::vector<BYTE> pbPropData;

	AddArray(pbMeasurementData, (int)eventData->GetMeasurements().size(), eventData->GetMeasurements());
	AddArray(pbPropData, (int)eventData->GetProperties().size(), eventData->GetProperties());

	TraceLoggingWrite(
		g_hAppInsightsProvider,
		"Part B data",
		TraceLoggingKeyword(MICROSOFT_KEYWORD_TELEMETRY),
		TraceLoggingStruct(2, "Data"),
		TraceLoggingWideString(eventData->GetBaseType().c_str(), "baseType"),
		TraceLoggingStruct(4, "baseData"),
		TraceLoggingInt32(eventData->GetVer(), "ver"),
		TraceLoggingWideString(eventData->GetName().c_str(), "name"),
		TraceLoggingPackedData(&pbPropData[0], pbPropData.size()),	//content
		TraceLoggingPackedStructArray(2, "properties"),
		TraceLoggingPackedMetadata(TlgInCOUNTEDSTRING, "key"),
		TraceLoggingPackedMetadata(TlgInCOUNTEDSTRING, "value"),
		TraceLoggingPackedData(&pbMeasurementData[0], pbMeasurementData.size()),		//content
		TraceLoggingPackedStructArray(2, "measurements"),
		TraceLoggingPackedMetadata(TlgInCOUNTEDSTRING, "key"),
		TraceLoggingPackedMetadata(TlgInDOUBLE, "value")
		);
}

void TraceLoggingHelper::LogPageView(PageViewData* pageViewData)
{
	if (pageViewData == nullptr)
	{
		return;
	}

	std::vector<BYTE> pbMeasurementData;
	std::vector<BYTE> pbPropData;

	AddArray(pbMeasurementData, (int)pageViewData->GetMeasurements().size(), pageViewData->GetMeasurements());
	AddArray(pbPropData, (int)pageViewData->GetProperties().size(), pageViewData->GetProperties());

	TraceLoggingWrite(
		g_hAppInsightsProvider,
		"Part B data",
		TraceLoggingKeyword(MICROSOFT_KEYWORD_TELEMETRY),
		TraceLoggingStruct(2, "Data"),
		TraceLoggingWideString(pageViewData->GetBaseType().c_str(), "baseType"),
		TraceLoggingStruct(6, "baseData"),
		TraceLoggingInt32(pageViewData->GetVer(), "ver"),
		TraceLoggingWideString(pageViewData->GetName().c_str(), "name"),
		TraceLoggingWideString(pageViewData->GetUrl().c_str(), "url"),
		TraceLoggingWideString(pageViewData->GetDuration().c_str(), "duration"),
		TraceLoggingPackedData(&pbPropData[0], pbPropData.size()),		//content
		TraceLoggingPackedStructArray(2, "properties"),
		TraceLoggingPackedMetadata(TlgInCOUNTEDSTRING, "key"),
		TraceLoggingPackedMetadata(TlgInCOUNTEDSTRING, "value"),
		TraceLoggingPackedData(&pbMeasurementData, pbMeasurementData.size()),		//content
		TraceLoggingPackedStructArray(2, "measurements"),
		TraceLoggingPackedMetadata(TlgInCOUNTEDSTRING, "key"),
		TraceLoggingPackedMetadata(TlgInDOUBLE, "value")
		);
}

void TraceLoggingHelper::LogPageViewPerf(PageViewPerfData* pageViewPerfData)
{
	if (pageViewPerfData == nullptr)
	{
		return;
	}

	std::vector<BYTE> pbMeasurementData;
	std::vector<BYTE> pbPropData;

	AddArray(pbMeasurementData, (int)pageViewPerfData->GetMeasurements().size(), pageViewPerfData->GetMeasurements());
	AddArray(pbPropData, (int)pageViewPerfData->GetProperties().size(), pageViewPerfData->GetProperties());

	TraceLoggingWrite(
		g_hAppInsightsProvider,
		"Part B data",
		TraceLoggingKeyword(MICROSOFT_KEYWORD_TELEMETRY),
		TraceLoggingStruct(2, "Data"),
		TraceLoggingWideString(pageViewPerfData->GetBaseType().c_str(), "baseType"),
		TraceLoggingStruct(11, "baseData"),
		TraceLoggingInt32(pageViewPerfData->GetVer(), "ver"),
		TraceLoggingWideString(pageViewPerfData->GetName().c_str(), "name"),
		TraceLoggingWideString(pageViewPerfData->GetUrl().c_str(), "url"),
		TraceLoggingWideString(pageViewPerfData->GetDuration().c_str(), "duration"),
		TraceLoggingWideString(pageViewPerfData->GetPerfTotal().c_str(), "perfTotal"),
		TraceLoggingWideString(pageViewPerfData->GetNetworkConnect().c_str(), "networkConnect"),
		TraceLoggingWideString(pageViewPerfData->GetSentRequest().c_str(), "sentRequest"),
		TraceLoggingWideString(pageViewPerfData->GetReceivedResponse().c_str(), "receivedResponse"),
		TraceLoggingWideString(pageViewPerfData->GetDomProcessing().c_str(), "domProcessing"),
		TraceLoggingPackedData(&pbPropData[0], pbPropData.size()),		//content
		TraceLoggingPackedStructArray(2, "properties"),
		TraceLoggingPackedMetadata(TlgInCOUNTEDSTRING, "key"),
		TraceLoggingPackedMetadata(TlgInCOUNTEDSTRING, "value"),
		TraceLoggingPackedData(&pbMeasurementData[0], pbMeasurementData.size()),		//content
		TraceLoggingPackedStructArray(2, "measurements"),
		TraceLoggingPackedMetadata(TlgInCOUNTEDSTRING, "key"),
		TraceLoggingPackedMetadata(TlgInDOUBLE, "value")
		);
}

void TraceLoggingHelper::LogMessage(MessageData* messageData)
{
	if (messageData == nullptr)
	{
		return;
	}

	std::vector<BYTE> pbPropData;
	AddArray(pbPropData, (int)messageData->GetProperties().size(), messageData->GetProperties());

	int sevLevel = 0;
	if (messageData->GetSeverityLevel().HasValue())
	{
		sevLevel = messageData->GetSeverityLevel().GetValue();
	}

	TraceLoggingWrite(
		g_hAppInsightsProvider,
		"Part B data",
		TraceLoggingKeyword(MICROSOFT_KEYWORD_TELEMETRY),
		TraceLoggingStruct(2, "Data"),
		TraceLoggingWideString(messageData->GetBaseType().c_str(), "baseType"),
		TraceLoggingStruct(4, "baseData"),
		TraceLoggingInt32(messageData->GetVer(), "ver"),
		TraceLoggingWideString(messageData->GetMessage().c_str(), "message"),
		TraceLoggingInt32(sevLevel, "severityLevel"),
		TraceLoggingPackedData(&pbPropData[0], pbPropData.size()),		//content
		TraceLoggingPackedStructArray(2, "properties"),
		TraceLoggingPackedMetadata(TlgInCOUNTEDSTRING, "key"),
		TraceLoggingPackedMetadata(TlgInCOUNTEDSTRING, "value")
		);
}

void TraceLoggingHelper::LogException(ExceptionData* exceptionData)
{
	if (exceptionData == nullptr)
	{
		return;
	}

	std::vector<BYTE> pbMeasurementData;
	std::vector<BYTE> pbPropData;
	std::vector<BYTE> pbExceptionDetailsData;

	AddArray(pbExceptionDetailsData, (int)exceptionData->GetExceptions().size(), exceptionData->GetExceptions());
	AddArray(pbMeasurementData, (int)exceptionData->GetMeasurements().size(), exceptionData->GetMeasurements());
	AddArray(pbPropData, (int)exceptionData->GetProperties().size(), exceptionData->GetProperties());

	int sevLevel = 0;

	if (exceptionData->GetSeverityLevel().HasValue())
	{
		sevLevel = exceptionData->GetSeverityLevel().GetValue();
	}

	//TraceLoggingWrite(
	//	g_hAppInsightsProvider,
	//	"Part B data",
	//	TraceLoggingKeyword(MICROSOFT_KEYWORD_TELEMETRY),
	//	TraceLoggingStruct(2, "Data"),
	//	TraceLoggingWideString(exceptionData.GetBaseType().c_str(), "baseType"),
	//	TraceLoggingStruct(8, "baseData"),
	//	TraceLoggingInt32(exceptionData.GetVer(), "ver"),
	//	TraceLoggingWideString(exceptionData.GetHandledAt().c_str(), "handledAt"),
	//	TraceLoggingPackedData(&cbExceptionDetailsData, sizeof(UINT16)),  //count
	//	TraceLoggingPackedData(&pbExceptionDetailsData, pbExceptionDetailsData.size()),		//content
	//		TraceLoggingPackedStructArray(7, "exceptionDetails"),
	//		TraceLoggingPackedMetadata(TlgInINT32, "id"),
	//		TraceLoggingPackedMetadata(TlgInINT32, "outerId"),
	//		TraceLoggingPackedMetadata(TlgInCOUNTEDSTRING, "typeName")
	//		TraceLoggingPackedMetadata(TlgInCOUNTEDSTRING, "message")
	//		TraceLoggingPackedMetadata(TlgInBOOL32, "hasFullStack")
	//		TraceLoggingPackedMetadata(TlgInCOUNTEDSTRING, "stack"),
	//		TraceLoggingPackedStructArray(5, "parsedStack"),
	//			TraceLoggingPackedMetadata(TlgInINT32, "level"),
	//			TraceLoggingPackedMetadata(TlgInCOUNTEDSTRING, "method"),
	//			TraceLoggingPackedMetadata(TlgInCOUNTEDSTRING, "assembly"),
	//			TraceLoggingPackedMetadata(TlgInCOUNTEDSTRING, "fileName"),
	//			TraceLoggingPackedMetadata(TlgInINT32, "line"),
	//	TraceLoggingInt32(sevLevel, "severityLevel"),
	//	TraceLoggingWideString(exceptionData.GetProblemId().c_str(), "problemId"),
	//	TraceLoggingInt32(exceptionData.GetCrashThreadId(), "crashThreadId"),
	//	TraceLoggingPackedData(&cbPropData, sizeof(UINT16)),  //count
	//	TraceLoggingPackedData(&pbPropData, pbPropData.size()),		//content
	//		TraceLoggingPackedStructArray(2, "properties"),
	//		TraceLoggingPackedMetadata(TlgInCOUNTEDSTRING, "key"),
	//		TraceLoggingPackedMetadata(TlgInCOUNTEDSTRING, "value"),
	//	TraceLoggingPackedData(&cbMeasurementData, sizeof(UINT16)),  //count
	//	TraceLoggingPackedData(&pbMeasurementData, pbMeasurementData.size()),		//content
	//		TraceLoggingPackedStructArray(2, "measurements"),
	//		TraceLoggingPackedMetadata(TlgInCOUNTEDSTRING, "key"),
	//		TraceLoggingPackedMetadata(TlgInDOUBLE, "value")
	//	);
}
