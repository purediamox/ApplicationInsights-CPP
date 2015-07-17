#ifndef PERSISTENCE_H
#define PERSISTENCE_H
#include <Windows.h>
#include <list>
#include <queue>
#include <string>
#include "../../Common/Common.hpp"
#include "HttpResponse.hpp"

namespace ApplicationInsights
{
	namespace core
	{
		typedef struct PersistConfig {
			std::wstring folderLocation;
			int uploadIntervalMins;
			std::wstring endpointUrl;
		} PERSISTCONFIG, *PPERSISTCONFIG;


		class TELEMETRYCLIENT_API Persistence
		{
		public:
			Persistence();
			virtual ~Persistence();
			bool Initialize(PPERSISTCONFIG config = NULL);
			
			void save(std::wstring jsonPayload);
			
			static PERSISTCONFIG GetDefaultConfig();
			PERSISTCONFIG GetCurrentConfig();
			
			void GetAllResponses(std::queue<HttpResponse> &resp);

		private:	
			void StopThread();
			DWORD WINAPI Upload();
			static DWORD WINAPI UploadThreadProc(LPVOID lpParam);

			PERSISTCONFIG m_currentConfig;
			HANDLE m_hThread;
			HANDLE m_hStopThread;
			HANDLE m_hRecvdResp;
			std::queue<HttpResponse> m_respQueue;
			CRITICAL_SECTION m_cs;
		};
	}
}
#endif
