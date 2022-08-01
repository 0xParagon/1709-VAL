#pragma once
#include "sdk.hpp"
#include <iostream>

using namespace Globals;
using namespace camera;

typedef struct _FNlEntity {
	uint64_t Actor;
	uint64_t MeshComponent;
}FNlEntity;
std::vector<FNlEntity> entityList;

int LocalUID;
DWORD_PTR PlayerState, RootComponent, LocalPawn;


auto CACHETHREAD() -> void
{
	while (true)
	{
		std::vector<FNlEntity> tmpList;

		auto Uworld = decryptWorld(image_base);

		auto GameInstance = Read<DWORD_PTR>(Uworld + offsets::GameInstance);
		auto PersistentLevel = Read<uintptr_t>(Uworld + offsets::PersistentLevel);

		auto LocalPlayerArray = Read<DWORD_PTR>(GameInstance + offsets::LocalPlayerArray);
		auto LocalPlayer = Read<DWORD_PTR>(LocalPlayerArray);

		PlayerController = Read<DWORD_PTR>(LocalPlayer + offsets::PlayerController);
		PlayerCameraManager = Read<DWORD_PTR>(PlayerController + offsets::PlayerCameraManager);

		LocalPawn = Read<DWORD_PTR>(PlayerController + offsets::AcknowledgedPawn);

		if (LocalPawn != 0)
		{
			LocalUID = Read<int>(LocalPawn + offsets::UniqueID);
			PlayerState = Read<DWORD_PTR>(LocalPawn + offsets::PlayerState);
			RootComponent = Read<DWORD_PTR>(LocalPawn + offsets::RootComponent);
		}

		auto ActorArray = Read<uintptr_t>(PersistentLevel + offsets::ActorArray);
		int ActorCount = Read<int>(PersistentLevel + offsets::ActorCount);

		for (int i = 0; i < ActorCount; i++)
		{
			auto CurrentActor = Read<DWORD_PTR>(ActorArray + (i * 0x8));
			if (CurrentActor == 0) continue;

			auto ActorUID = Read<int>(CurrentActor + offsets::UniqueID);
			if (LocalUID != ActorUID) continue;

			auto MeshComponent = Read<uint64_t>(CurrentActor + offsets::MeshComponent);
			if (MeshComponent == 0) continue;

			auto BoneCount = Read<int>(MeshComponent + offsets::BoneCount);
			if (BoneCount < 90) continue;

			FNlEntity fnlEntity{ };
			fnlEntity.Actor = CurrentActor;
			fnlEntity.MeshComponent = MeshComponent;
			tmpList.push_back(fnlEntity);
		}
		entityList.clear();
		entityList = tmpList;
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}

auto HACK() -> void
{
	float closestDistance = FLT_MAX;
	DWORD_PTR closestPawn = NULL;

	if (settings::aimbot::drawfov) 
		DrawCircle(ScreenCenterX, ScreenCenterY, settings::aimbot::fov, &Col.white, 10000);
	
	if (settings::aimbot::sqrefov) 
		ImGui::GetOverlayDrawList()->AddRect(ImVec2(ScreenCenterX - settings::aimbot::fov, ScreenCenterY - settings::aimbot::fov), ImVec2(ScreenCenterX + settings::aimbot::fov, ScreenCenterY + settings::aimbot::fov + settings::aimbot::thickness), ImGui::GetColorU32({ 255, 255, 255, 255 }), 1);
	
	if (settings::aimbot::hcgnfov)
		DrawCircle(ScreenCenterX, ScreenCenterY, settings::aimbot::fov, &Col.white, 10);

	auto entityListCopy = entityList;

	for (int i = 0; i < entityListCopy.size(); ++i)
	{
		FNlEntity entity = entityListCopy.at(i);

		auto ActorRootComponent = Read<uintptr_t>(entity.Actor + offsets::RootComponent);
		auto RelativeLocation = Read<Vector3>(ActorRootComponent + offsets::RelativeLocation);

		auto LocalRootComponent = Read<uintptr_t>(LocalPawn + offsets::RootComponent);
		auto LocalRelativeLocation = Read<Vector3>(LocalRootComponent + offsets::RelativeLocation);

		auto MeshComponent = Read<uint64_t>(entity.Actor + offsets::MeshComponent);

		Vector3 vBaseBone = GetBone(MeshComponent, 0);
		Vector3 vBaseBoneOut = ProjectWorldToScreen(vBaseBone);
		Vector3 vBaseBoneOut2 = ProjectWorldToScreen(Vector3(vBaseBone.x, vBaseBone.y, vBaseBone.z - 15));
		Vector3 vHeadBone = GetBone(MeshComponent, 8);
		Vector3 vHeadBoneOut = ProjectWorldToScreen(Vector3(vHeadBone.x, vHeadBone.y, vHeadBone.z));
		Vector3 vHeadBoneOut2 = ProjectWorldToScreen(Vector3(vHeadBone.x, vHeadBone.y, vHeadBone.z + 15));

		auto distance = LocalRelativeLocation.Distance(RelativeLocation);

		float BoxHeight = abs(vHeadBoneOut2.y - vBaseBoneOut.y);
		float BoxWidth = BoxHeight * 0.55;

		float width = BoxWidth / 10; if (width < 2.f) width = 2.; if (width > 3) width = 3.;

		auto IsVisible = isVisible(MeshComponent);

		ImColor ESPColor; 
		if (IsVisible) 
		{ 
			ESPColor = ImColor(0, 255, 0);
		}
		else
		{
			ESPColor = ImColor(255, 0, 0);
		}

		auto ActorPlayerState = Read<DWORD_PTR>(entity.Actor + offsets::PlayerState);
		uintptr_t ActorTeamComponent = Read<uintptr_t>(ActorPlayerState + offsets::TeamComponent);
		auto ActorTeamID = Read<int>(ActorTeamComponent + offsets::TeamID);

		uintptr_t LocalTeamComponent = Read<uintptr_t>(PlayerState + offsets::TeamComponent);
		int LocalTeamID = Read<int>(LocalTeamComponent + offsets::TeamID);

		bool dormant = Read<bool>(entity.Actor + offsets::bIsDormant);
		auto dmgh = Read<uintptr_t>(entity.Actor + offsets::DamageHandler);
		auto Health = Read<float>(dmgh + offsets::Health);
		auto BoneCount = Read<int>(MeshComponent + offsets::BoneCount);

		if (Health <= 0) continue;
		if (!dormant) continue;

		if (ActorTeamID != LocalTeamID || BoneCount == 103)
		{
			if (distance < 150)
			{
				if (settings::visuals::snapline)
				{
					DrawLine(ImVec2(Width / 2, Height), ImVec2(vBaseBoneOut.x, vBaseBoneOut.y), ESPColor, 0.5f);
				}

				if (settings::visuals::box)
				{
					DrawNormalBox(vBaseBoneOut.x - (BoxWidth / 2), vHeadBoneOut2.y, BoxWidth, BoxHeight, 1, ESPColor);
				}

				if (settings::visuals::cornerbox)
				{
					DrawCorneredBox(vHeadBoneOut2.x - (BoxWidth / 2), vHeadBoneOut2.y, BoxWidth, BoxHeight, ESPColor, 1.5);
				}

				if (settings::visuals::health)
				{
					DrawHealthBar(vHeadBoneOut.x - (BoxWidth / 2) - 8, vHeadBoneOut.y, width, vBaseBoneOut.y - vHeadBoneOut.y, Health, true);
				}
			}

			if (settings::visuals::distance)
			{
				char dist[64];
				sprintf_s(dist, "%.fm", distance);
				std::string Out = dist;
				ImVec2 TextSize = ImGui::CalcTextSize(Out.c_str());

				ImGui::GetOverlayDrawList()->AddText(ImVec2(vBaseBoneOut2.x - TextSize.x / 2, vBaseBoneOut2.y - TextSize.y / 2), ImGui::GetColorU32({ 255, 255, 255, 255 }), Out.c_str());
			}

			auto dx = vHeadBoneOut.x - (Width / 2);
			auto dy = vHeadBoneOut.y - (Height / 2);
			auto dist = sqrtf(dx * dx + dy * dy);

			if (dist < settings::aimbot::fov && dist < closestDistance)
			{
				if (settings::aimbot::vischeck)
				{
					if (IsVisible)
					{
						closestDistance = dist;
						closestPawn = entity.Actor;
					}
				}
				else
				{
					closestDistance = dist;
					closestPawn = entity.Actor;
				}
			}
		}
	}
	if (settings::aimbot::aimbot)
	{
		if (closestPawn && GetAsyncKeyState(hotkeys::aimkey) < 0)
		{
			CallAimbot(closestPawn);
		}
	}
}