#include "Misc.h"
#include "..\Resources\Language.h"
#include <iostream>
#include <Shellapi.h>
#include "../Utils/XorStr.h"
#include <mutex>

namespace Misc
{
	Hitmarker hitmarker;

	bool aKeyPressed = false;
	bool dKeyPressed = false;
	bool wKeyPressed = false;
	bool sKeyPressed = false;

	void Watermark(const CEntity& LocalPlayer) noexcept
	{
		if (!MiscCFG::WaterMark)
			return;

		//	globalvars GV;
		ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize;
		ImVec4 default_bg_color = ImGui::GetStyleColorVec4(ImGuiCol_WindowBg);
		default_bg_color.w = 0.5f;
		ImGui::PushStyleColor(ImGuiCol_WindowBg, default_bg_color);
		//ImGui::SetNextWindowBgAlpha(0.5f);
		ImGui::Begin(XorStr("Watermark"), nullptr, windowFlags);

		// Current Time
		struct tm ptm;
		getCurrentTime(&ptm);

		// Player Ping
		int playerPing = MenuConfig::Ping;

		// Player Pos
		Vec3 Pos = LocalPlayer.Pawn.Pos;

		// Player Angle
		Vec2 Angle = LocalPlayer.Pawn.ViewAngle;

		ImGui::Text(XorStr("AimStar"));
		ImGui::Text(XorStr("%d FPS | %d ms | %02d:%02d:%02d"),
			MenuConfig::FPS,
			playerPing,
			ptm.tm_hour, ptm.tm_min, ptm.tm_sec);
		ImGui::Text(XorStr("Pos: %.2f, %.2f, %.2f"), Pos.x, Pos.y, Pos.z);
		ImGui::Text(XorStr("Angle: %.2f, %.2f"), Angle.x, Angle.y);
		ImGui::Text(XorStr("Vel: %.2f"), LocalPlayer.Pawn.Speed);
		ImGui::PopStyleColor();
		ImGui::End();
	}

	void HitManager(const CEntity& aLocalPlayer, int& PreviousTotalHits) noexcept
	{
		if (MiscCFG::HitMarker || MiscCFG::HitSound)
		{
			uintptr_t pBulletServices;
			int totalHits;
			ProcessMgr.ReadMemory(aLocalPlayer.Pawn.Address + Offset::C_CSPlayerPawn.m_pBulletServices, pBulletServices);
			ProcessMgr.ReadMemory(pBulletServices + Offset::CCSPlayer_BulletServices.m_totalHitsOnServer, totalHits);

			if (totalHits != PreviousTotalHits) {
				if (totalHits == 0 && PreviousTotalHits != 0)
				{
					// `totalHits` changed from non-zero to zero, do nothing
				}
				else
				{
					// Hit Marker
					if (MiscCFG::HitMarker)
					{
						hitmarker.alpha = 255.f;
						hitmarker.startTime = std::chrono::steady_clock::now();
					}

					// Hit Sound
					switch (MiscCFG::HitSound)
					{
					case 1:
						PlaySoundA(reinterpret_cast<char*>(neverlose_sound), NULL, SND_ASYNC | SND_MEMORY);
						break;
					case 2:
						PlaySoundA(reinterpret_cast<char*>(skeet_sound), NULL, SND_ASYNC | SND_MEMORY);
						break;
					case 3:
						PlaySoundA(reinterpret_cast<char*>(Fuck), NULL, SND_ASYNC | SND_MEMORY);
						break;
					case 4:
						PlaySoundA(reinterpret_cast<char*>(Senpai), NULL, SND_ASYNC | SND_MEMORY);
						break;
					default:
						break;
					}

				}
			}
			PreviousTotalHits = totalHits;
		}

		// Update Hit Marker
		if (hitmarker.alpha > 0.f)
		{
			// std::cout << hitmarker.alpha << std::endl;
			auto now = std::chrono::steady_clock::now();
			auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - hitmarker.startTime).count();
			if (duration >= 500.f)
				hitmarker.alpha = 0;
			else
				hitmarker.alpha = 1.f - duration / 500.f;
		}
	}

	void HitMarker(float Size, float Gap)
	{
		std::lock_guard<std::mutex> lock(std::mutex);
		ImGuiIO& io = ImGui::GetIO();
		ImVec2 center = ImVec2(Gui.Window.Size.x / 2, Gui.Window.Size.y / 2);

		if (hitmarker.alpha > 0.f)
		{
			ImColor col = ImColor(255.f, 255.f, 255.f, hitmarker.alpha);

			ImGui::GetBackgroundDrawList()->AddLine(ImVec2(center.x - Size, center.y - Size), ImVec2(center.x - Gap, center.y - Gap), col & IM_COL32_A_MASK, 2.4f);
			ImGui::GetBackgroundDrawList()->AddLine(ImVec2(center.x - Size, center.y + Size), ImVec2(center.x - Gap, center.y + Gap), col & IM_COL32_A_MASK, 2.4f);
			ImGui::GetBackgroundDrawList()->AddLine(ImVec2(center.x + Size, center.y - Size), ImVec2(center.x + Gap, center.y - Gap), col & IM_COL32_A_MASK, 2.4f);
			ImGui::GetBackgroundDrawList()->AddLine(ImVec2(center.x + Size, center.y + Size), ImVec2(center.x + Gap, center.y + Gap), col & IM_COL32_A_MASK, 2.4f);
			ImGui::GetBackgroundDrawList()->AddLine(ImVec2(center.x - Size, center.y - Size), ImVec2(center.x - Gap, center.y - Gap), col, 1.4f);
			ImGui::GetBackgroundDrawList()->AddLine(ImVec2(center.x - Size, center.y + Size), ImVec2(center.x - Gap, center.y + Gap), col, 1.4f);
			ImGui::GetBackgroundDrawList()->AddLine(ImVec2(center.x + Size, center.y - Size), ImVec2(center.x + Gap, center.y - Gap), col, 1.4f);
			ImGui::GetBackgroundDrawList()->AddLine(ImVec2(center.x + Size, center.y + Size), ImVec2(center.x + Gap, center.y + Gap), col, 1.4f);
		}
	}

	void FlashImmunity(const CEntity& aLocalPlayer) noexcept
	{
		if (MiscCFG::FlashImmunity == 0)
			return;
		float MaxAlpha = 255.f - MiscCFG::FlashImmunity;
		ProcessMgr.WriteMemory(aLocalPlayer.Pawn.Address + Offset::C_CSPlayerPawnBase.m_flFlashMaxAlpha, MaxAlpha);
	}

	void FastStop(const CEntity& aLocalPlayer) noexcept
	{
		if (!MiscCFG::FastStop)
			return;
		const float Trigger_Value = 24.f;//��ͣ��ֹ�ٶ�
		if (!(GetAsyncKeyState('W') || GetAsyncKeyState('A') || GetAsyncKeyState('S') || GetAsyncKeyState('D') || GetAsyncKeyState(VK_SPACE) || GetAsyncKeyState(VK_LSHIFT)) && aLocalPlayer.Pawn.Speed > Trigger_Value && AirCheck(aLocalPlayer))
		{
				const auto LocalVel = aLocalPlayer.Pawn.Velocity;
				const auto LocalYaw = aLocalPlayer.Pawn.ViewAngle.y;
				const auto X = (LocalVel.x * cos(LocalYaw / 180 * 3.1415926) + LocalVel.y * sin(LocalYaw / 180 * 3.1415926));
				const auto Y = (LocalVel.y * cos(LocalYaw / 180 * 3.1415926) - LocalVel.x * sin(LocalYaw / 180 * 3.1415926));
				if (X > Trigger_Value) { keybd_event('S', MapVirtualKey('S', 0), KEYEVENTF_SCANCODE, 0); std::this_thread::sleep_for(std::chrono::milliseconds(1)); keybd_event('S', MapVirtualKey('S', 0), KEYEVENTF_KEYUP, 0);}
				else if (X < -Trigger_Value) { keybd_event('W', MapVirtualKey('W', 0), KEYEVENTF_SCANCODE, 0); std::this_thread::sleep_for(std::chrono::milliseconds(1)); keybd_event('W', MapVirtualKey('W', 0), KEYEVENTF_KEYUP, 0); }
				if (Y > Trigger_Value) { keybd_event('D', MapVirtualKey('D', 0), KEYEVENTF_SCANCODE, 0); std::this_thread::sleep_for(std::chrono::milliseconds(1)); keybd_event('D', MapVirtualKey('D', 0), KEYEVENTF_KEYUP, 0); }
				else if (Y < -Trigger_Value) { keybd_event('A', MapVirtualKey('A', 0), KEYEVENTF_SCANCODE, 0); std::this_thread::sleep_for(std::chrono::milliseconds(1)); keybd_event('A', MapVirtualKey('A', 0), KEYEVENTF_KEYUP, 0); }
		}

		/*
		// Disable when bhopping
		if (GetAsyncKeyState(VK_SPACE) & 0x8000)
			return;
		// Disable when slow walking
		if (GetAsyncKeyState(VK_LSHIFT) & 0x8000)
			return;

		Misc::StopKeyEvent('A', &aKeyPressed, 'D', 50.f);
		Misc::StopKeyEvent('D', &dKeyPressed, 'A', 50.f);
		Misc::StopKeyEvent('W', &wKeyPressed, 'S', 50.f);
		Misc::StopKeyEvent('S', &sKeyPressed, 'W', 50.f);
		*/
	}
	/*
	// This feature was removed temporarily from Cheats.hpp, because it may crash the game
	void NadeManager(CGame Game) noexcept
	{
		if (MenuConfig::SafeMode)
			return;

		std::vector<std::string> EntityNames = {
		XorStr("smokegrenade_projectile"), XorStr("weapon_glock"), XorStr("weapon_smokegrenade"), XorStr("basemodelentity"),
		XorStr("c_cs_player_for_precache"), XorStr("info_particle_system"), XorStr("prop_dynamic"), XorStr("post_processing_volume"),
		XorStr("env_player_visibility"), XorStr("team_intro_terrorist"), XorStr("c_cs_observer_for_precache"),
		XorStr("team_intro_counterterrorist"), XorStr("point_camera"), XorStr("sky_camera"), XorStr("env_sky"), XorStr("team_select_terrorist"),
		XorStr("team_select_counterterrorist"), XorStr("point_camera"), XorStr("func_bomb_target"), XorStr("env_cubemap_fog"),
		XorStr("csgo_viewmodel"), XorStr("cs_minimap_boundary"), XorStr("cs_gamerules"), XorStr("cs_player_manager"), XorStr("vote_controller"),
		XorStr("weapon_incgrenade"), XorStr("molotov_projectile")
		};

		if (!MiscCFG::NoSmoke && !MiscCFG::SmokeColored)
			return;

		for (int i_smoke = 64; i_smoke < 1024; i_smoke++) {
			uintptr_t SmokeEntity = GetSmokeEntity(i_smoke, Game.GetEntityListEntry());

			uintptr_t ent_base, addr;
			ProcessMgr.ReadMemory<uintptr_t>(SmokeEntity, ent_base);

			// No Smoke
			if (MiscCFG::NoSmoke)
			{
				bool begin = false;
				int uf = 0;

				ProcessMgr.WriteMemory<bool>(ent_base + Offset::SmokeGrenadeProjectile.bDidSmokeEffect, begin);
				ProcessMgr.WriteMemory<bool>(ent_base + Offset::SmokeGrenadeProjectile.bSmokeEffectSpawned, begin);
				ProcessMgr.WriteMemory<int>(ent_base + Offset::SmokeGrenadeProjectile.nSmokeEffectTickBegin, uf);
			}

			// Smoke Color
			if (MiscCFG::SmokeColored || MiscCFG::FireColored)
			{
				char toread[32];
				std::string classname;
				Vector3 COLOR = { MiscCFG::SmokeColor.Value.x, MiscCFG::SmokeColor.Value.y ,MiscCFG::SmokeColor.Value.z };
				ProcessMgr.ReadMemory<uintptr_t>(ent_base + 0x10, addr);
				ProcessMgr.ReadMemory<uintptr_t>(addr + 0x20, addr);
				ProcessMgr.ReadMemory<char[32]>(addr, toread);
				classname = toread;

				
				// Filter id to find id
				if (std::find(EntityNames.begin(), EntityNames.end(), classname) == EntityNames.end())
					std::cout << classname << std::endl;
				

				if (classname == XorStr("smokegrenade_projectile"))
				{
					if (MiscCFG::SmokeColored)
						ProcessMgr.WriteMemory<Vector3>(ent_base + Offset::SmokeGrenadeProjectile.vSmokeColor, COLOR);
				}
				 Disabled
				if (classname == "molotov_projectile")
				{
					Vector3 FireColor = { 0,0,0 };
					ProcessMgr.ReadMemory<Vector3>(ent_base + 0x112C, FireColor);
					std::cout << FireColor.x << ", " << FireColor.y << ", " << FireColor.z << std::endl;
						
				}
			}
		}
	}
	*/
	void RadarHack(const CEntity& EntityList) noexcept
	{
		if (!MiscCFG::RadarHack)
			return;

		bool SpottedStatus = true;
		ProcessMgr.WriteMemory(EntityList.Pawn.Address + Offset::C_CSPlayerPawn.m_bSpottedByMask, SpottedStatus);
	}

	void FovChanger(const CEntity& aLocalPlayer) noexcept
	{
		if (MiscCFG::Fov == 90)
			return;
		DWORD64 CameraServices = 0;
		if (Zoom)
			return;

		if (!ProcessMgr.ReadMemory<DWORD64>(aLocalPlayer.Pawn.Address + Offset::C_BasePlayerPawn.m_pCameraServices, CameraServices))
			return;

		UINT Desiredfov = static_cast<UINT>(MiscCFG::Fov);
		ProcessMgr.WriteMemory<UINT>(aLocalPlayer.Controller.Address + Offset::CBasePlayerController.m_iDesiredFOV, Desiredfov);

	}

	void MoneyService(const CEntity& EntityList) noexcept
	{
		if (!MiscCFG::MoneyService)
			return;

		ImGuiWindowFlags flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize;

		ImGui::Begin(XorStr("Money Services"), nullptr, flags);
		{
			if (ImGui::TreeNode(EntityList.Controller.PlayerName.c_str()))
			{
				std::stringstream ss;
				ss << XorStr("Account: $") << EntityList.Controller.Money;
				ImGui::TextColored(ImColor(0, 255, 0, 255), ss.str().c_str());
				if (MiscCFG::ShowCashSpent)
				{
					std::stringstream sss;
					sss << XorStr("ThisRound/Total: ") << EntityList.Controller.CashSpent << XorStr("/") << EntityList.Controller.CashSpentTotal;
					ImGui::TextColored(ImColor(255, 0, 0, 255), sss.str().c_str());
				}

				ImGui::TreePop();
			}
		}
	}

	void BunnyHop(const CEntity& Local) noexcept
	{
		if (!MiscCFG::BunnyHop)
			return;
		HWND hwnd_cs2 = FindWindowA(NULL, "Counter-Strike 2");
		HWND hwnd_perfectworld = FindWindowA(NULL, "\u53cd\u6050\u7cbe\u82f1\uff1a\u5168\u7403\u653b\u52bf");

		if (hwnd_cs2 == NULL) {
			hwnd_cs2 = hwnd_perfectworld;
		}
		int ForceJump;
		bool spacePressed = GetAsyncKeyState(VK_SPACE);
		bool isInAir = AirCheck(Local);
		gGame.GetForceJump(ForceJump);

		if (spacePressed && isInAir) // AirCheck = 1, is on ground
		{
			// As of the latest update (11/8/2023) bhop doesn't work at all with sendinput,
			// if +jump is sent on the same tick that you land on the ground, the jump won't register.
			// But you can add 15ms of delay right before your sendinput to fix this problem temporarily
			std::this_thread::sleep_for(std::chrono::microseconds(15626));
			// Refer to -> https://www.unknowncheats.me/forum/counter-strike-2-a/609480-sendinput-bhop-inconsistency.html
			//gGame.SetForceJump(65537);
			SendMessage(hwnd_cs2, WM_KEYDOWN, VK_SPACE, 0);
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
			SendMessage(hwnd_cs2, WM_KEYUP, VK_SPACE, 0);

		}
		else if (spacePressed && !isInAir) // AirCheck = 0, isn't on ground
		{
			//gGame.SetForceJump(256);
			SendMessage(hwnd_cs2, WM_KEYUP, VK_SPACE, 0);
		}
		else if (!spacePressed /* && ForceJump == 65537*/)
		{
			//gGame.SetForceJump(256);
			SendMessage(hwnd_cs2, WM_KEYUP, VK_SPACE, 0);
		}
	}

	std::string OldWeaponCache;
	void ForceScope(const CEntity& aLocalPlayer) noexcept
	{
		if (!MiscCFG::ForceScope)
			return;

		// When player switching weapon, cancel Scope
		const std::string PlayerWeapon = aLocalPlayer.Pawn.WeaponName;
		if (OldWeaponCache != PlayerWeapon)
		{
			Zoom = false;
			OldWeaponCache = PlayerWeapon;
		}

		// When players hold these weapons, don't Scope
		std::vector<std::string> WeaponNames = {
		XorStr("smokegrenade"), XorStr("flashbang"), XorStr("hegrenade"), XorStr("molotov"), XorStr("decoy"), XorStr("incgrenade"),
		XorStr("awp"), XorStr("ssg08"), XorStr("aug"), XorStr("sg556"),
		XorStr("knife"), XorStr("c4")
		};
		if (std::find(WeaponNames.begin(), WeaponNames.end(), PlayerWeapon) != WeaponNames.end())
			return;

		// When player reloading their weapon, cancel Scope
		DWORD64 WeaponService;
		bool inReload;
		ProcessMgr.ReadMemory(aLocalPlayer.Pawn.Address + Offset::C_CSPlayerPawnBase.m_pClippingWeapon, WeaponService);
		ProcessMgr.ReadMemory(WeaponService + Offset::WeaponBaseData.inReload, inReload);
		if (inReload)
		{
			Zoom = false;
		}

		// Avoid scope loop
		static DWORD lastTick = 0;
		DWORD currentTick = GetTickCount();
		if (!MenuConfig::ShowMenu)
		{
			if ((GetAsyncKeyState(VK_RBUTTON) & 0x8000) && currentTick - lastTick >= 500)
			{
				Zoom = !Zoom;
				lastTick = currentTick;
			}
		}

		if (Zoom)
		{
			UINT Scopefov = 45;
			ProcessMgr.WriteMemory<UINT>(aLocalPlayer.Controller.Address + Offset::CBasePlayerController.m_iDesiredFOV, Scopefov);
		}
			
	}

	// @Phillip
	void NightMode() noexcept
	{
		if (!MiscCFG::NightMode)
			return;

		ImGui::SetNextWindowPos({ 0, 0 }, ImGuiCond_Always);
		ImGui::SetNextWindowSize({ Gui.Window.Size.x, Gui.Window.Size.y }, ImGuiCond_Always);
		ImGui::SetNextWindowBgAlpha(0.f);
		ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0, 0, 0, 0));
		ImGui::Begin(XorStr("##background"), nullptr, ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoDecoration);

		ImVec2 windowPos = ImGui::GetWindowPos();
		ImVec2 windowSize = ImGui::GetWindowSize();
		ImGui::TextColored(ImColor(255, 255, 255, 200), XorStr("Night Mode Overlay"));

		if (MiscCFG::NightModeAlpha)
		{
			ImGui::GetBackgroundDrawList()->
				AddRectFilled(windowPos, ImVec2(windowPos.x + windowSize.x, windowPos.y + windowSize.y), IM_COL32(0, 0, 0, MiscCFG::NightModeAlpha));
		}

		ImGui::End();
		ImGui::PopStyleColor();
			
	}

	void JumpThrow(const CEntity& Local) noexcept
	{
		if (!MiscCFG::jumpthrow)
			return;

		std::string PlayerWeapon = Local.Pawn.WeaponName;
		if (std::find(Nades.begin(), Nades.end(), PlayerWeapon) == Nades.end())
			return;

		bool isOnGround = AirCheck(Local);
		if (!isOnGround)
		{
			Vec3 Velocity = Local.Pawn.Velocity;

			if (Velocity.z > 250.f || Velocity.z < 200.f)
				return;

			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
	}
	DWORD64 GethPawn(uint64_t Target)
	{
		DWORD64 EntityPawnListEntry = 0;
		DWORD64 EntityPawnAddress = 0;

		if (!ProcessMgr.ReadMemory<DWORD64>(gGame.GetEntityListAddress(), EntityPawnListEntry))
			return 0;

		if (!ProcessMgr.ReadMemory<DWORD64>(EntityPawnListEntry + 0x10 + 8 * ((Target & 0x7FFF) >> 9), EntityPawnListEntry))
			return 0;

		if (!ProcessMgr.ReadMemory<DWORD64>(EntityPawnListEntry + 0x78 * (Target & 0x1FF), EntityPawnAddress))
			return 0;

		return EntityPawnAddress;
	}
	void SpectatorList(const CEntity& Local) {
		if (!MiscCFG::SpecList)
			return;

		//render method de tkkr by ukia
		ImGui::SetNextWindowSizeConstraints(ImVec2(200, 100), ImGui::GetIO().DisplaySize);
		ImGui::Begin(XorStr("Spectators"), nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_::ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_::ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_::ImGuiWindowFlags_NoNav);
		{
			ImGui::SetCursorPosY(22);
			if (!MenuConfig::ValidEntity.empty())
			{
				int count = 0;
				for (int index = 0; index < MenuConfig::ValidEntity.size(); index++)//traverse again.
				{
					
					CEntity Entity = MenuConfig::ValidEntity[index].first;
					DWORD64 EntityAddress = MenuConfig::ValidEntity[index].second;
					auto pPlayer = Entity.Controller;
					
					/*
					if (!Entity.UpdatePawn(Entity.Pawn.Address))
						continue;
					*/

					//jakebooom idea + tokikiri stuff
					uintptr_t obsServices;
					if (!ProcessMgr.ReadMemory(Entity.Pawn.Address + Offset::C_BasePlayerPawn.m_pObserverServices, obsServices))
						continue;

					uint64_t obsTarget;
					if (!ProcessMgr.ReadMemory(obsServices + Offset::CPlayer_ObserverServices.m_hObserverTarget, obsTarget))
						continue;
					uintptr_t obsPawn = GethPawn(obsTarget);

					if (obsPawn != Local.Pawn.Address)
						continue;

					std::string Name = pPlayer.PlayerName;
					ImGui::BulletText(Name.c_str());
				}
			}
		}

		ImGui::End();

	}

}
