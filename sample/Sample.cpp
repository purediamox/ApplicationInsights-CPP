// Sample.cpp : Defines the entry point for the console application.
//

#include "..\src\core\TelemetryClient.h"

using namespace ApplicationInsights::core;

#define INSTRUMENTATION_KEY L"2a9cc982-9128-495f-b12f-e352e5cd5298"


int main()
{
	std::wstring  key = INSTRUMENTATION_KEY;
	
	TelemetryClient* pClient = new TelemetryClient(key);
	
	pClient->TrackEvent(L"MarkC Event");
	
	pClient->Flush();
	
	delete pClient;
	
	
	return 0;
}

