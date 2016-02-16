// sample.cpp : Defines the entry point for the console application.
//
#include <iostream>
#include "../src/core/TelemetryClient.h"

using namespace ApplicationInsights::core;

#define INSTRUMENTATION_KEY L"2a9cc982-9128-495f-b12f-e352e5cd5298"


int main()
{
	std::wstring  key = INSTRUMENTATION_KEY;

	wprintf(L"instrumentation key %ls\n", key.c_str());  

	TelemetryClient* pClient = new TelemetryClient(key);
	wprintf(L"Client created\n");

	pClient->TrackEvent(L"AppInsightsCPP Event");
	wprintf(L"TrackEvent\n");

	wstring_wstring_map properties;
	properties[L"prop1"] = L"value1";
	properties[L"prop2"] = L"value2";

	pClient->TrackEvent(L"AppInsightsCPP Event Prop", properties);
	wprintf(L"TrackEvent with properties\n");

	pClient->TrackMetric(L"AppInsightsCPP Metric", 3.14);
	wprintf(L"TrackMetric\n");

	pClient->TrackMetric(L"AppInsightsCPP Metric Prop", 2.71, properties);  // TODO Base implementation doesn't have properties
	wprintf(L"TrackMetric with Properties\n");



	pClient->TrackTrace(L"AppInsightsCPP Trace");
	wprintf(L"TrackTrace\n");



	pClient->Flush();
	wprintf(L"Flush\n");

	delete pClient;
	
	
	return 0;
}

