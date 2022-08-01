#pragma once
#include "../../Includes/strings.hpp"

static int Tabs = 0;

auto drawmenu() -> void
{
	if (settings::show_menu)
	{
		ImGui::Begin(XorStr("Astreal Software - Valorant [Window(s) 10 | 1709 Only]").c_str(), NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
		ImGui::SetWindowSize(XorStr("Astreal Software - Valorant [Window(s) 10 | 1709 Only]").c_str(), ImVec2(450, 450));

		if (ImGui::Button(XorStr("VISUALS").c_str(), ImVec2(140, 25))) { Tabs = 0; }ImGui::SameLine();
		if (ImGui::Button(XorStr("AIMBOT").c_str(), ImVec2(140, 25))) { Tabs = 1; }ImGui::SameLine();
		if (ImGui::Button(XorStr("CHANGELOG").c_str(), ImVec2(139, 25))) { Tabs = 2; }

		ImGui::Spacing();

		if (Tabs == 0) //Visuals
		{
			ImGui::Spacing();
			ImGui::Separator(); // DIVIDER
			ImGui::Spacing();
			ImGui::Button("EXTRA SENSORY PERCEPTION (PLAYERS)");
			ImGui::Spacing();

			ImGui::Checkbox(XorStr("Draw Bounding 2D Box").c_str(), &settings::visuals::box);
			if (settings::visuals::box) settings::visuals::cornerbox = false;

			ImGui::Spacing();

			ImGui::Checkbox(XorStr("Draw 2D Corner Box").c_str(), &settings::visuals::cornerbox);
			if (settings::visuals::cornerbox) settings::visuals::box = false;

			ImGui::Spacing();

			ImGui::Checkbox(XorStr("Draw Snaplines").c_str(), &settings::visuals::snapline);

			ImGui::Spacing();

			ImGui::Checkbox(XorStr("Draw Distance ESP").c_str(), &settings::visuals::distance);

			ImGui::Spacing();

			ImGui::Checkbox(XorStr("Draw Health Bar ").c_str(), &settings::visuals::health);
		}

		if (Tabs == 1) //Aimbot
		{
			ImGui::Spacing();
			ImGui::Separator(); // DIVIDER
			ImGui::Spacing();
			ImGui::Button("AIMBOT SETTINGS");
			ImGui::Spacing();

			ImGui::Checkbox(XorStr("Enable Aimbot").c_str(), &settings::aimbot::aimbot);
			ImGui::SameLine();
			ImGui::Text(XorStr("			Aimbot Key: ").c_str());
			ImGui::SameLine();
			HotkeyButton(hotkeys::aimkey, ChangeKey, keystatus);

			ImGui::Spacing();

			ImGui::Checkbox(XorStr("Visiblity Check").c_str(), &settings::aimbot::vischeck);
			if (settings::aimbot::aimbot)
			{
				ImGui::Checkbox(XorStr("Draw FOV Circle").c_str(), &settings::aimbot::drawfov);
				if (settings::aimbot::drawfov) {
					settings::aimbot::sqrefov = false;
					settings::aimbot::hcgnfov = false;
					DrawCircleFilled(ScreenCenterX, ScreenCenterY, settings::aimbot::fov, &Col.GlassBlue, 10000);
				}

				ImGui::Spacing();

				ImGui::Checkbox(XorStr("Draw FOV Square").c_str(), &settings::aimbot::sqrefov);
				if (settings::aimbot::sqrefov) {
					settings::aimbot::drawfov = false;
					settings::aimbot::hcgnfov = false;
				}

				ImGui::Spacing();

				ImGui::Checkbox(XorStr("Draw FOV Hendecagon").c_str(), &settings::aimbot::hcgnfov);
				if (settings::aimbot::hcgnfov) {
					settings::aimbot::drawfov = false;
					settings::aimbot::sqrefov = false;
				}
				
				ImGui::Spacing();

				ImGui::Text(XorStr("FoV: ").c_str());
				ImGui::PushItemWidth(435.f);
				ImGui::SliderFloat("    ", &settings::aimbot::fov, 10, 750);

				ImGui::Spacing();

				ImGui::Checkbox(XorStr("Enable Smoothing").c_str(), &settings::aimbot::smooth);
				if (settings::aimbot::smooth)
				{
					ImGui::Spacing();
					ImGui::Text(XorStr("Smoothing: ").c_str());
					ImGui::PushItemWidth(435.f);
					ImGui::SliderFloat("  ", &settings::aimbot::smoothness, 1, 20);
				}
			}
		}

		if (Tabs == 2) //Misc
		{
			ImGui::TextDisabled("Current Detection Status :");
			ImGui::SameLine();
			ImGui::Button("UNDETECTED");
			ImGui::SameLine();

			ImGui::Spacing();

			ImGui::TextDisabled("Current Client Build :");
			ImGui::SameLine();
			ImGui::Button("v1.0.1-RT");
			ImGui::SameLine();

			ImGui::Spacing();

			ImGui::TextDisabled("Current Driver Build :");
			ImGui::SameLine();
			ImGui::Button("v9.8.1.5a - System Generated");
			ImGui::SameLine();

			ImGui::Spacing();
			ImGui::Separator(); // DIVIDER
			ImGui::Spacing();

			ImGui::Text("CHANGELOG - v1.0.0");
			ImGui::BulletText("Added Aim-Key Selection");
			ImGui::BulletText("Optimized Code for Smoother Performance");

			ImGui::Spacing();
			ImGui::Separator(); // DIVIDER
			ImGui::Spacing();

			ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "If you run into issues, contact the developer or staff!");
		}
		ImGui::End();
	}
}