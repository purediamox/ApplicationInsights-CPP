#include "Persistence.hpp";
using namespace ApplicationInsights::core;

const PERSISTCONFIG defaultConfig = { L"ApplicationInsights", 5, L"dc.services.visualstudio.com" };

Persistence::Persistence()
{
}

Persistence::~Persistence()
{
}

bool Persistence::Initialize(PPERSISTCONFIG config)
{
	return true;
}

void Persistence::save(std::wstring jsonPayload)
{
}

PERSISTCONFIG Persistence::GetDefaultConfig()
{
	return defaultConfig; 
}

PERSISTCONFIG Persistence::GetCurrentConfig()
{
	return m_currentConfig;
}

void Persistence::GetAllResponses(std::queue<HttpResponse> &resp)
{
}