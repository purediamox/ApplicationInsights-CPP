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

	pClient->TrackEvent(L"MarkC Event");
	wprintf(L"TrackEvent\n");

	pClient->TrackMetric(L"MarkC Metric", 3.14);
	wprintf(L"TrackMetric\n");

	pClient->Flush();
	wprintf(L"Flush\n");

	delete pClient;
	
	
	return 0;
}

