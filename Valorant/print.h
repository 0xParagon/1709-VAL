#pragma once
// Icon Solution for Includes
#include <Windows.h>
#include <iostream>
#include <thread>
#include <string>

// Extra Includes
#include <string>

HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
int k;

std::string tm_to_readable_time(tm ctx) {
	char buffer[80];

	strftime(buffer, sizeof(buffer), "%m/%d/%y", &ctx);

	return std::string(buffer);
}

static std::time_t string_to_timet(std::string timestamp) {
	auto cv = strtol(timestamp.c_str(), NULL, 10); // long

	return (time_t)cv;
}

static std::tm timet_to_tm(time_t timestamp) {
	std::tm context;

	localtime_s(&context, &timestamp);

	return context;
}

void slow_print(const std::string& str, int delay_time)
{
	for (size_t i = 0; i != str.size(); ++i)
	{
		std::cout << str[i];
		Sleep(delay_time);
	}
}


enum Colors
{
	BLACK,
	BLUE,
	GREEN,
	CYAN,
	RED,
	MAGENTA,
	BROWN,
	LIGHTGRAY,
	DARKGRAY,
	LIGHTBLUE,
	LIGHTGREEN,
	LIGHTCYAN,
	LIGHTRED,
	PURPLE,
	YELLOW,
	WHITE
};

class Printa
{
public:
	const char* SetWhite()
	{
		SetConsoleTextAttribute(h, 15);
		return "";
	}
	const char* SetGreen()
	{
		SetConsoleTextAttribute(h, 10);
		return "";
	}
	const char* SetBlue()
	{
		SetConsoleTextAttribute(h, 9);
		return "";
	}
	const char* SetPurple()
	{
		SetConsoleTextAttribute(h, 13);
		return "";
	}
	const char* SetRed()
	{
		SetConsoleTextAttribute(h, 4);
		return "";
	}
	const char* SetYellow()
	{
		SetConsoleTextAttribute(h, 14);
		return "";
	}
	const char* SetDark()
	{
		SetConsoleTextAttribute(h, 8);
		return "";
	}

	void Title(const std::string& str, int delay_time)
	{
		SetRed();
		for (size_t i = 0; i != str.size(); ++i)
		{
			std::cout << str[i];
			Sleep(delay_time);
		}
	}
	void OK(const char* text)
	{
		SetGreen();
		std::cout << ">> ";
		SetWhite();
		std::cout << text << std::endl;
		SetWhite();
	}
	void Connected(const char* text)
	{
		SetGreen();
		std::cout << ">> ";
		SetWhite();
		std::cout << text << std::endl;
	}
	void DLLFail(const char* text)
	{
		SetRed();
		std::cout << ">> ";
		SetWhite();
		std::cout << text << std::endl;
	}
	void Status(const char* text)
	{
		SetBlue();
		std::cout << ">> ";
		SetWhite();
		std::cout << "Current Status : ";
		SetGreen();
		std::cout << "ONLINE";
		std::cout << text << std::endl;
		SetWhite();
	}
	void Version(const char* text)
	{
		SetBlue();
		std::cout << ">> ";
		SetWhite();
		std::cout << "Astreal Valorant Build : ";
		SetWhite();
		std::cout << "v1.0.0";
		std::cout << text << std::endl;
		SetWhite();
	}
	void Comp(const char* text)
	{
		SetBlue();
		std::cout << ">> ";
		SetWhite();
		std::cout << "Supported Anti-Cheat(s) : ";
		SetYellow();
		std::cout << "Vanguard";
		std::cout << text << std::endl;
		SetWhite();
	}
	void Win(const char* text)
	{
		SetBlue();
		std::cout << ">> ";
		SetWhite();
		std::cout << "Supported Windows Version(s) : ";
		SetYellow();
		std::cout << "Window(s) 10 [1709] ";
		std::cout << text << std::endl;
		SetWhite();
	}
	void Driver(const char* text)
	{
		SetGreen();
		std::cout << ">> ";
		SetWhite();
		std::cout << "Driver Initiated! Please wait for driver to start...";
		std::cout << text << std::endl;
	}
	void Start(const char* text)
	{
		SetWhite();
		std::cout << "[ ";
		SetGreen();
		std::cout << "INSTRUCTIONS";
		SetWhite();
		std::cout << " ] ";
		std::cout << text << std::endl;
	}
	void Info(const char* text)
	{
		SetWhite();
		std::cout << "[ ";
		SetDark();;
		std::cout << "SYSTEM";
		SetWhite();
		std::cout << " ] ";
		std::cout << text << std::endl;
	}
	void Key(const char* text)
	{
		SetBlue();
		std::cout << ">> ";
		SetWhite();
		std::cout << text << std::endl;
	}
	void EnInfo(const char* text)
	{
		SetWhite();
		std::cout << "[ ";
		SetDark();
		std::cout << "ENGINE-INFORMATION";
		SetWhite();
		std::cout << " ]";
		std::cout << text << std::endl;
	}
	void EnInfo2(const char* text)
	{
		SetWhite();
		std::cout << "[ ";
		SetDark();
		std::cout << "EXTRA-INFORMATION";
		SetWhite();
		std::cout << " ]";
		std::cout << text << std::endl;
	}
	void Disclaimer(const char* text)
	{
		SetWhite();
		std::cout << "[ ";
		SetPurple();
		std::cout << "DISCLAIMER";
		SetWhite();
		std::cout << " ]";
		std::cout << text << std::endl;
	}
	void Instructions(const char* text)
	{
		SetWhite();
		std::cout << "[ ";
		SetYellow();
		std::cout << "PENDING STEP";
		SetWhite();
		std::cout << " ] ";
		std::cout << text << std::endl;
	}
	void Warning(const char* text)
	{
		SetWhite();
		std::cout << "[ ";
		SetRed();
		std::cout << "WARNING";
		SetWhite();
		std::cout << " ]";
		std::cout << text << std::endl;
	}
	void Announcement(const char* text)
	{
		SetWhite();
		std::cout << "[ ";
		SetBlue();
		std::cout << "ANNOUNCEMENT";
		SetWhite();
		std::cout << " ] ";
		std::cout << text << std::endl;
	}
	void Input(const char* text)
	{
		SetBlue();
		std::cout << "-> ";
		SetYellow();
		std::cout << text << std::endl;
	}
	void License(const char* text)
	{
		SetWhite();
		std::cout << "[ ";
		SetBlue();
		std::cout << "ENTER LICENSE BELOW";
		SetWhite();
		std::cout << " ]";
		SetYellow();
		std::cout << text << std::endl;

	}
	void Feature1(const char* text)
	{
		SetWhite();
		std::cout << "[";
		SetGreen();
		std::cout << "+";
		SetWhite();
		std::cout << "] ";
		SetYellow();
		std::cout << text << std::endl;
	}
	void Loading(const char* text)
	{
		SetPurple();
		std::cout << ">> ";
		SetWhite();
		std::cout << text << std::endl;
		SetWhite();
	}
	void Fail(const char* text)
	{
		SetRed();
		std::cout << ">> ";
		SetWhite();
		std::cout << text << std::endl;
		SetWhite();
	}

	void Print(const char* text)
	{
		std::cout << text << std::endl;
	}
	void PrintCol(const char* text, int color)
	{
		SetConsoleTextAttribute(h, color);
		std::cout << text << std::endl;
	}
	void Custom(std::string symbol, int symbolColor, const char* text, int textColor)
	{
		SetWhite();
		std::cout << " [ ";
		SetConsoleTextAttribute(h, symbolColor);
		std::cout << symbol;
		SetWhite();
		std::cout << " ] ";
		SetConsoleTextAttribute(h, textColor);
		std::cout << text << std::endl;
	}
	void Rainbow(std::string text)
	{
		for (int i = 0; i < text.length(); i++)
		{
			k > 14 ? k = 1 : k++;
			SetConsoleTextAttribute(h, k);
			std::cout << text.at(i);
		}

	}

	void Endl()
	{
		std::cout << std::endl;
	}
}Printa;