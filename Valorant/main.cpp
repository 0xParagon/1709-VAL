#include <Windows.h>
#include <iostream>
#include <thread>
#include <string>

#include "driver/driver.h"

#include "overlay/render.hpp"
#include "overlay/menu.hpp"

#include "game/cheat.hpp"

#include "print.h"

#include <Urlmon.h>
#include <filesystem>
#include <tchar.h>

#include <TlHelp32.h>
#include <string>
#include "../Includes/Auth/auth.hpp"

#pragma comment(lib, "urlmon.lib")

using namespace std;
using namespace KeyAuth;

std::string name = XorStr("Astreal-Valorant").c_str();
std::string ownerid = XorStr("qpJx77bL2P").c_str();
std::string secret = XorStr("e29fcb5920c623b83138558c921a55333704f74273483354e72b137b13a39ab6").c_str();
std::string version = XorStr("1.0").c_str();
std::string url = XorStr("https://keyauth.win/api/1.1/").c_str();
std::string sslPin = XorStr("ssl pin key (optional)").c_str();
api KeyAuthApp(name, ownerid, secret, version, url, sslPin);


void rndmTitle() {
	constexpr int length = 15;
	const auto characters = TEXT("abcdefghi9182345jklmnopqrstuv211935960473wxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890");
	TCHAR title[length + 1]{};

	for (int j = 0; j != length; j++)
	{
		title[j] += characters[rand() % 55 + 1];
	}

	SetConsoleTitle(title);
}

// Displays Windows Box Message after Menu is Downloaded.
int Successful()
{
	int msgboxID = MessageBoxA(NULL, (LPCSTR)"Success", (LPCSTR)rndmTitle, MB_ICONINFORMATION | MB_DEFBUTTON2);

	switch (msgboxID)
	{
	case IDCONTINUE:
		// TODO: add code
		break;
	}

	return msgboxID;
}

std::wstring s2ws(const std::string& str) {
	int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
	std::wstring wstrTo(size_needed, 0);
	MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], size_needed);
	return wstrTo;
}

int retreiveValProcessId()
{
	BYTE target_name[] = { 'V','A','L','O','R','A','N','T','-','W','i','n','6','4','-','S','h','i','p','p','i','n','g','.','e','x','e', 0 };
	std::wstring process_name = s2ws(std::string((char*)target_name));
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0); 
	PROCESSENTRY32W entry;
	entry.dwSize = sizeof(entry);

	if (!Process32First(snapshot, &entry)) {
		return 0;
	}

	while (Process32Next(snapshot, &entry)) {
		if (std::wstring(entry.szExeFile) == process_name) {
			return entry.th32ProcessID;
		}
	}

	return 0;
}

#include "../../Includes/Mapper/Kdmapper/kdmapper.hpp"

HANDLE iqvw64e_device_handle;

LONG WINAPI SimplestCrashHandler(EXCEPTION_POINTERS* ExceptionInfo)
{
	std::cout << "[+] Driver Error at 0x" << ExceptionInfo->ExceptionRecord->ExceptionAddress << " by 0x" << std::hex << ExceptionInfo->ExceptionRecord->ExceptionCode << std::endl;

	if (iqvw64e_device_handle)
		intel_driver::Unload(iqvw64e_device_handle);

	return EXCEPTION_EXECUTE_HANDLER;
}

int load_driver()
{
	SetUnhandledExceptionFilter(SimplestCrashHandler);
	if (intel_driver::IsRunning())
	{
		std::cout << "[+] Restart PC!" << std::endl;
		Sleep(500);
	}
	iqvw64e_device_handle = intel_driver::Load();

	NTSTATUS exitCode = 0;
	if (!kdmapper::MapDriver(iqvw64e_device_handle, 0, 0, false, true, 0, 0, 0, &exitCode)) {
		{
			std::cout << "[+] Failed to map the driver!" << std::endl;
			intel_driver::Unload(iqvw64e_device_handle);
			Sleep(500);
			exit(0);
		}
	}
	intel_driver::Unload(iqvw64e_device_handle);

	Sleep(500);
}

auto main() -> NTSTATUS
{
	rndmTitle();
	Sleep(2000);
	system(XorStr("cls").c_str());
	rndmTitle();
	std::wcout << R"(
		 ________  ________  _________  ________  _______   ________  ___          
		|\   __  \|\   ____\|\___   ___\\   __  \|\  ___ \ |\   __  \|\  \         
		\ \  \|\  \ \  \___|\|___ \  \_\ \  \|\  \ \   __/|\ \  \|\  \ \  \        
		 \ \   __  \ \_____  \   \ \  \ \ \   _  _\ \  \_|/_\ \   __  \ \  \       
		  \ \  \ \  \|____|\  \   \ \  \ \ \  \\  \\ \  \_|\ \ \  \ \  \ \  \____  
		   \ \__\ \__\____\_\  \   \ \__\ \ \__\\ _\\ \_______\ \__\ \__\ \_______\
		    \|__|\|__|\_________\   \|__|  \|__|\|__|\|_______|\|__|\|__|\|_______|
		             \|_________|                                               
)" << '\n';
	Printa.Announcement(XorStr("Spoofer has been disabled for testing! Please just press [1] and continue!").c_str());
	std::cout << XorStr("\n").c_str();
	Printa.Info("");
	Printa.Version("");
	Printa.Status("");
	std::cout << XorStr("\n").c_str();
	Printa.EnInfo("");
	Printa.Comp("");
	Printa.Win("");
	std::cout << XorStr("\n").c_str();
	Sleep(3500);
	KeyAuthApp.init();

	// API Success
	if (!KeyAuthApp.data.success)
	{
		Sleep(1000);
		exit(0);
	}

	rndmTitle();
	Sleep(2000);
	system(XorStr("cls").c_str());
	rndmTitle();
	std::wcout << R"(
		 ________  ________  _________  ________  _______   ________  ___          
		|\   __  \|\   ____\|\___   ___\\   __  \|\  ___ \ |\   __  \|\  \         
		\ \  \|\  \ \  \___|\|___ \  \_\ \  \|\  \ \   __/|\ \  \|\  \ \  \        
		 \ \   __  \ \_____  \   \ \  \ \ \   _  _\ \  \_|/_\ \   __  \ \  \       
		  \ \  \ \  \|____|\  \   \ \  \ \ \  \\  \\ \  \_|\ \ \  \ \  \ \  \____  
		   \ \__\ \__\____\_\  \   \ \__\ \ \__\\ _\\ \_______\ \__\ \__\ \_______\
		    \|__|\|__|\_________\   \|__|  \|__|\|__|\|_______|\|__|\|__|\|_______|
		             \|_________|                                                  
)" << '\n';
	Printa.Announcement(XorStr("Spoofer has been disabled for testing! Please just press [1] and continue!").c_str());
	std::cout << XorStr("\n").c_str();
	Printa.Info("");
	Printa.Version("");
	Printa.Status("");
	std::cout << XorStr("\n").c_str();
	Printa.EnInfo("");
	Printa.Comp("");
	Printa.Win("");
	std::cout << XorStr("\n").c_str();
	Sleep(2000);
	KeyAuthApp.check();

	if (std::filesystem::exists(XorStr("C:\\ProgramData\\").c_str() + name))
	{
		Sleep(1000);
		Printa.OK(XorStr("License Key Found! Please wait...").c_str());
		Sleep(1500);
		goto Load;
	}

	KeyAuthApp.check();

Load:

	std::string key;

	if (std::filesystem::exists(XorStr("C:\\ProgramData\\").c_str() + name))
	{
		std::ifstream InFile(XorStr("C:\\ProgramData\\").c_str() + name, std::ios::in);
		std::getline(InFile, key);

		KeyAuthApp.license(key);

		if (!KeyAuthApp.data.success)
		{
			std::string del = XorStr("C:\\ProgramData\\").c_str() + name;
			remove(del.c_str());
			goto A;
		}

	}
	else
	{
	A:
		std::cout << XorStr("\nEnter Astreal License Key : ").c_str();
		bool authed = false;
		while (authed == false)
		{
			std::cin >> key;
			KeyAuthApp.license(key);

			if (KeyAuthApp.data.success)
			{
				std::ofstream OutFile(XorStr("C:\\ProgramData\\").c_str() + name, std::ios::out);
				OutFile << key;
				OutFile.close();
				authed = true;
			}
			else {
				Sleep(2500);
				system(XorStr("cls").c_str());
				goto A;
			}
		}
	}

	if (!KeyAuthApp.data.success)
	{
		Sleep(1500);
		exit(0);
	}

	else
	{
		PVOID OldValue = nullptr;
		Wow64DisableWow64FsRedirection(&OldValue);

		rndmTitle();
		system(XorStr("cls").c_str());
		Sleep(2000);
		std::wcout << R"(
		 ________  ________  ________  ________  ________ _______   ________     
		|\   ____\|\   __  \|\   __  \|\   __  \|\  _____\\  ___ \ |\   __  \    
		\ \  \___|\ \  \|\  \ \  \|\  \ \  \|\  \ \  \__/\ \   __/|\ \  \|\  \   
		 \ \_____  \ \   ____\ \  \\\  \ \  \\\  \ \   __\\ \  \_|/_\ \   _  _\  
		  \|____|\  \ \  \___|\ \  \\\  \ \  \\\  \ \  \_| \ \  \_|\ \ \  \\  \| 
		    ____\_\  \ \__\    \ \_______\ \_______\ \__\   \ \_______\ \__\\ _\ 
		   |\_________\|__|     \|_______|\|_______|\|__|    \|_______|\|__|\|__|
		   \|_________|                                                          
                                                                 
)" << '\n';
		Printa.Announcement(XorStr("Spoofer has been disabled for testing! Please just press [1] and continue!").c_str());
		std::cout << XorStr("\n").c_str();
		Printa.Info("");
		Printa.Version("");
		Printa.Status("");
		std::cout << XorStr("\n").c_str();
		Printa.EnInfo("");
		Printa.Comp("");
		Printa.Win("");
		std::cout << XorStr("\n").c_str();

		//Printa.Disclaimer(" This is a permanent spoofer, this function can not be reversed!");
		Printa.Instructions("Select your option!");

		std::cout << "\n[1]: Start Valorant Engine\n";
		//std::cout << "[2]: Start Spoofer & Start Valorant Engine\n\n";

		int input = 0;

		std::cout << "-> ";
		cin >> input;

		/*if (input == 2)
		{
			URLDownloadToFileA(NULL, downloadCWZM.c_str(), savePathCWZM.c_str(), 0, NULL);

			Successful();
			ShellExecute(NULL, _T("open"), _T("C:\\Program Files\\check.exe"), NULL, NULL, SW_SHOWDEFAULT);

			std::this_thread::sleep_for(std::chrono::seconds(5));

			//UPDATE - CHECK.EXE KEEPS RUNNING SO HAVE TO CHANGE FROM THE MAIN WOOF SOURCE TO EXIT FULLY TO BE ABLE TO DELETE THE FILE.
			/*SHELLEXECUTEINFO lpExecInfo{};
			lpExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
			lpExecInfo.lpFile = L"check.exe";
			lpExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
			lpExecInfo.hwnd = NULL;
			lpExecInfo.lpVerb = NULL;
			lpExecInfo.lpParameters = NULL;
			lpExecInfo.lpDirectory = NULL;
			lpExecInfo.nShow = SW_SHOWNORMAL;
			ShellExecuteEx(&lpExecInfo);

			Sleep(3000);
			if (lpExecInfo.hProcess)
			{
				TerminateProcess(lpExecInfo.hProcess, 0);
				CloseHandle(lpExecInfo.hProcess);
			}

			char filename[] = "C:\\Program Files\\check.exe"; // bs
			int result = remove(filename);

			cout << result;
			goto START;
		}*/
		if (input == 1)
		{
			Printa.Connected("Starting Valorant Engine... Please Wait!\n");
			std::this_thread::sleep_for(std::chrono::seconds(5));

			goto START;
		}
		else
		{
			Printa.Warning("Invalid Selection. Please Try Again!");
		}

	START:

		if (GlobalFindAtomA(XorStr("DriverAlreadyLoadedx").c_str()) == 0)
		{
			load_driver();
			system(XorStr("cls").c_str());
			GlobalAddAtomA(XorStr("DriverAlreadyLoadedx").c_str());
		}

		bool status = InitDriver(GetCurrentProcessId());
		ULONG size = 0;
		DWORD64 baseAddress = GetModuleInfo(L"kernel32.dll", &size);
		//printf("Module address: 0x%llx Size: %lu\n", baseAddress, size);

		Close();

		HWND Entryhwnd = NULL;

		while (Entryhwnd == NULL)
		{
			printf(XorStr("Waiting for Valorant...\r").c_str());
			Sleep(1);
			process_id = retreiveValProcessId();;
			Entryhwnd = get_process_wnd(process_id);
			Sleep(1);
		}

		system(XorStr("cls").c_str());

		setup_window();
		init_wndparams(MyWnd);

		InitDriver(process_id);

		image_base = GetModuleInfo(L"VALORANT-Win64-Shipping.exe", nullptr); if (!image_base) printf(XorStr("Failed to get Base Address!\n").c_str());

		//printf("ValorantBase: 0x%llx\n", image_base);

		// Connection Success
		system(XorStr("cls").c_str());
		rndmTitle();
		Printa.Info("");
		Printa.Status("");
		std::cout << XorStr("\n").c_str();
		Printa.Connected(XorStr("Astreal Software - Valorant PID Found!").c_str());
		Printa.Disclaimer(" Do not close this window!");
		std::cout << XorStr("\nEngine Expiration Date: ").c_str() << tm_to_readable_time(timet_to_tm(string_to_timet(KeyAuthApp.data.expiry)));

		std::thread(CACHETHREAD).detach();
		while (true) main_loop();
	}
	exit(0);
}

auto render() -> void 
{
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	if (GetAsyncKeyState(VK_F1) & 1) { settings::show_menu = !settings::show_menu; }

	HACK();
	drawmenu();

	ImGui::EndFrame();
	p_Device->SetRenderState(D3DRS_ZENABLE, false);
	p_Device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	p_Device->SetRenderState(D3DRS_SCISSORTESTENABLE, false);
	p_Device->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_ARGB(0, 0, 0, 0), 1.0f, 0);

	if (p_Device->BeginScene() >= 0) 
	{
		ImGui::Render();
		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
		p_Device->EndScene();
	}

	HRESULT result = p_Device->Present(NULL, NULL, NULL, NULL);

	if (result == D3DERR_DEVICELOST && p_Device->TestCooperativeLevel() == D3DERR_DEVICENOTRESET) 
	{
		ImGui_ImplDX9_InvalidateDeviceObjects();
		p_Device->Reset(&d3dpp);
		ImGui_ImplDX9_CreateDeviceObjects();
	}
}

auto main_loop() -> WPARAM
{
	static RECT old_rc;
	ZeroMemory(&Message, sizeof(MSG));

	while (Message.message != WM_QUIT) 
	{
		if (PeekMessage(&Message, MyWnd, 0, 0, PM_REMOVE)) {
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}

		HWND hwnd_active = GetForegroundWindow();
		if (GetAsyncKeyState(0x23) & 1)
			exit(8);

		if (hwnd_active == GameWnd) {
			HWND hwndtest = GetWindow(hwnd_active, GW_HWNDPREV);
			SetWindowPos(MyWnd, hwndtest, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		}
		RECT rc;
		POINT xy;

		ZeroMemory(&rc, sizeof(RECT));
		ZeroMemory(&xy, sizeof(POINT));
		GetClientRect(GameWnd, &rc);
		ClientToScreen(GameWnd, &xy);
		rc.left = xy.x;
		rc.top = xy.y;

		ImGuiIO& io = ImGui::GetIO();
		io.ImeWindowHandle = GameWnd;
		io.DeltaTime = 1.0f / 60.0f;

		POINT p;
		GetCursorPos(&p);
		io.MousePos.x = p.x - xy.x;
		io.MousePos.y = p.y - xy.y;

		if (GetAsyncKeyState(0x1)) {
			io.MouseDown[0] = true;
			io.MouseClicked[0] = true;
			io.MouseClickedPos[0].x = io.MousePos.x;
			io.MouseClickedPos[0].x = io.MousePos.y;
		}
		else io.MouseDown[0] = false;

		if (rc.left != old_rc.left || rc.right != old_rc.right || rc.top != old_rc.top || rc.bottom != old_rc.bottom) {

			old_rc = rc;

			Width = rc.right;
			Height = rc.bottom;

			p_Params.BackBufferWidth = Width;
			p_Params.BackBufferHeight = Height;
			SetWindowPos(MyWnd, (HWND)0, xy.x, xy.y, Width, Height, SWP_NOREDRAW);
			p_Device->Reset(&p_Params);
		}
		render();
	}

	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	cleanup_d3d();
	DestroyWindow(MyWnd);

	return Message.wParam;
}