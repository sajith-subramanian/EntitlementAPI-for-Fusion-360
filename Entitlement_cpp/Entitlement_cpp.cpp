
#include <Core/CoreAll.h>
#include <Fusion/FusionAll.h>
#include <CAM/CAMAll.h>

#include <restclient-cpp/restclient.h>
#include <json/json.h>


using namespace adsk::core;
using namespace adsk::fusion;
using namespace adsk::cam;
using namespace std;
Ptr<Application> app;
Ptr<UserInterface> ui;


extern "C" XI_EXPORT bool run(const char* context)
{

	try
	{
		app = Application::get();
		if (!app)
			return false;

		ui = app->userInterface();
		if (!ui)
			return false;

		string userId = app->userId();
		string appId = "4611814297957846949";//"8699194120463301363";//
		string url = "https://apps.exchange.autodesk.com/webservices/checkentitlement" + string("?userid=") + userId + string("&appid=") + appId;
		RestClient::Response response = RestClient::get(url);

		Json::Reader reader;
		Json::Value root;

		bool isparseSuccessful = reader.parse(response.body, root);
		if (!isparseSuccessful)
		{
			ui->messageBox("Error parsing the string");
		}

		if ((root["IsValid"].asString()) == "true")
		{
			ui->messageBox("IsValid is True");
		}
		else
		{
			ui->messageBox("IsValid is False");
		}
	}
	catch (exception ex)
	{

	}
	return true;
}

#ifdef XI_WIN

#include <windows.h>

BOOL APIENTRY DllMain(HMODULE hmodule, DWORD reason, LPVOID reserved)
{
	switch (reason)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

#endif // XI_WIN
