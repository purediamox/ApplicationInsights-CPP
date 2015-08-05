#ifndef PERSISTENCE_H
#define PERSISTENCE_H
#include <Windows.h>
#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP) // Win32

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
#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP) // Win32, no store, no phone
			void StopThread();
			DWORD WINAPI Upload();
			static DWORD WINAPI UploadThreadProc(LPVOID lpParam);

			HANDLE m_hThread;
			HANDLE m_hStopThread;
			HANDLE m_hRecvdResp;
			
			CRITICAL_SECTION m_cs;
#else
#endif
			std::queue<HttpResponse> m_respQueue;
			PERSISTCONFIG m_currentConfig;
		};
	}
}
#endif
#endif