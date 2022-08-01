#pragma once
#include <Windows.h>


int process_id;
DWORD64 image_base;

// SPOOFER DOWNLOAD
//std::string downloadCWZM = ("");
//std::string savePathCWZM = ("C:\\Program Files\\NAME.exe");

namespace settings
{
    inline bool show_menu = TRUE;

    namespace aimbot 
    {
        inline bool aimbot = FALSE;
		inline bool vischeck = FALSE;
        inline bool drawfov = FALSE;  //circle
        inline bool sqrefov = TRUE;   //square
        inline bool hcgnfov = FALSE;  //hendecagon
		inline bool smooth = FALSE;
		inline float smoothness = 17.5f;
		inline float fov = 20;
		float thickness = 2.0f;
    }

    namespace visuals 
    {
		inline bool box = TRUE;
		inline bool cornerbox = FALSE;
        inline bool snapline = FALSE;
        inline bool distance = FALSE;
		inline bool health = TRUE;
    }
}

namespace offsets
{
    inline DWORD
        World_Key = 0x87FCD38,
        World_State = 0x87FCD00,
        GameInstance = 0x1a8,
        PersistentLevel = 0x38,
        LocalPlayerArray = 0x40,
        PlayerController = 0x38,
        PlayerCameraManager = 0x478,
        AcknowledgedPawn = 0x460,
        PlayerState = 0x3f0,
        TeamComponent = 0x5b0,
        TeamID = 0xf8,
        GameState = 0x150,
        ActorArray = 0xA0,
        ActorCount = 0xB8,
        RootComponent = 0x230,
        RelativeLocation = 0x164,
        MeshComponent = 0x430,
        DamageHandler = 0x9a8,
        bIsDormant = 0x100,
        Health = 0x1b0,
        UniqueID = 0x38,
        BoneCount = 0x560;
}

namespace hotkeys
{
	int aimkey;
	int airstuckey;
	int instares;
}

static int keystatus = 0;
static int realkey = 0;

bool GetKey(int key)
{
	realkey = key;
	return true;
}
void ChangeKey(void* blank)
{
	keystatus = 1;
	while (true)
	{
		for (int i = 0; i < 0x87; i++)
		{
			if (GetKeyState(i) & 0x8000)
			{
				hotkeys::aimkey = i;
				keystatus = 0;
				return;
			}
		}
	}
}

static const char* keyNames[] =
{
	"Keybind",
	"Left Mouse",
	"Right Mouse",
	"Cancel",
	"Middle Mouse",
	"Mouse 5",
	"Mouse 4",
	"",
	"Backspace",
	"Tab",
	"",
	"",
	"Clear",
	"Enter",
	"",
	"",
	"Shift",
	"Control",
	"Alt",
	"Pause",
	"Caps",
	"",
	"",
	"",
	"",
	"",
	"",
	"Escape",
	"",
	"",
	"",
	"",
	"Space",
	"Page Up",
	"Page Down",
	"End",
	"Home",
	"Left",
	"Up",
	"Right",
	"Down",
	"",
	"",
	"",
	"Print",
	"Insert",
	"Delete",
	"",
	"0",
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"A",
	"B",
	"C",
	"D",
	"E",
	"F",
	"G",
	"H",
	"I",
	"J",
	"K",
	"L",
	"M",
	"N",
	"O",
	"P",
	"Q",
	"R",
	"S",
	"T",
	"U",
	"V",
	"W",
	"X",
	"Y",
	"Z",
	"",
	"",
	"",
	"",
	"",
	"Numpad 0",
	"Numpad 1",
	"Numpad 2",
	"Numpad 3",
	"Numpad 4",
	"Numpad 5",
	"Numpad 6",
	"Numpad 7",
	"Numpad 8",
	"Numpad 9",
	"Multiply",
	"Add",
	"",
	"Subtract",
	"Decimal",
	"Divide",
	"F1",
	"F2",
	"F3",
	"F4",
	"F5",
	"F6",
	"F7",
	"F8",
	"F9",
	"F10",
	"F11",
	"F12",
};

static bool Items_ArrayGetter(void* data, int idx, const char** out_text)
{
	const char* const* items = (const char* const*)data;
	if (out_text)
		*out_text = items[idx];
	return true;
}
void HotkeyButton(int aimkey, void* changekey, int status)
{
	const char* preview_value = NULL;
	if (aimkey >= 0 && aimkey < IM_ARRAYSIZE(keyNames))
		Items_ArrayGetter(keyNames, aimkey, &preview_value);

	std::string aimkeys;
	if (preview_value == NULL)
		aimkeys = "Select Key";
	else
		aimkeys = preview_value;

	if (status == 1)
	{

		aimkeys = "Press the Key";
	}
	if (ImGui::Button(aimkeys.c_str(), ImVec2(125, 20)))
	{
		if (status == 0)
		{
			CreateThread(0, 0, (LPTHREAD_START_ROUTINE)changekey, nullptr, 0, nullptr);
		}
	}
}