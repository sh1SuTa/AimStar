#pragma once
#include <chrono>
#include <iostream>
#include <utility>
#include <sstream>
#include <ctime>
#include <string>
#include "..\Entity.h"
#include "..\MenuConfig.hpp"
namespace hash {
	int runtime(const std::string& str) {
		int hash = 0;
		for (char c : str) {
			hash = hash * 31 + c;
		}
		return hash;
	}
}

#define HASH(str) hash::runtime(str)
namespace bmb
{

	// Idea from Tokinaa
	int getBombSite(bool Planted)
	{
		if (Planted)
		{
			int site;
			uintptr_t cPlantedC4;
			ProcessMgr.ReadMemory(gGame.GetClientDLLAddress() + Offset::PlantedC4, cPlantedC4);
			if (!ProcessMgr.ReadMemory<uintptr_t>(gGame.GetClientDLLAddress() + Offset::PlantedC4, cPlantedC4))
				return 0;
			if (!ProcessMgr.ReadMemory<uintptr_t>(cPlantedC4, cPlantedC4))
				return 0;

			if (!ProcessMgr.ReadMemory<int>(cPlantedC4 + Offset::C_PlantedC4.m_nBombSite, site))
				return 0;
			return site;
		}
		
	}
	bool getBombDefusing(bool Planted)
	{
		if (Planted)
		{
			int Defusing = false;
			uintptr_t cPlantedC4;
			ProcessMgr.ReadMemory(gGame.GetClientDLLAddress() + Offset::PlantedC4, cPlantedC4);
			if (!ProcessMgr.ReadMemory<uintptr_t>(gGame.GetClientDLLAddress() + Offset::PlantedC4, cPlantedC4))
				return Defusing;
			if (!ProcessMgr.ReadMemory<uintptr_t>(cPlantedC4, cPlantedC4))
				return Defusing;

			if (!ProcessMgr.ReadMemory(cPlantedC4 + Offset::C_PlantedC4.m_bBeingDefused, Defusing))
				return Defusing;
			return Defusing;
		}
	}
	float getBombDefuseTime(bool Planted)
	{
		if (Planted)
		{
			float DefuseTime = false;
			uintptr_t cPlantedC4;
			ProcessMgr.ReadMemory(gGame.GetClientDLLAddress() + Offset::PlantedC4, cPlantedC4);
			if (!ProcessMgr.ReadMemory<uintptr_t>(gGame.GetClientDLLAddress() + Offset::PlantedC4, cPlantedC4))
				return DefuseTime;
			if (!ProcessMgr.ReadMemory<uintptr_t>(cPlantedC4, cPlantedC4))
				return DefuseTime;

			if (!ProcessMgr.ReadMemory(cPlantedC4 + Offset::C_PlantedC4.m_flDefuseCountDown, DefuseTime))
				return DefuseTime;
			return DefuseTime;
		}
	}
	float getBombBoomTime(bool Planted)
	{
		if (Planted)
		{
			float BoomTime = false;
			uintptr_t cPlantedC4;
			ProcessMgr.ReadMemory(gGame.GetClientDLLAddress() + Offset::PlantedC4, cPlantedC4);
			if (!ProcessMgr.ReadMemory<uintptr_t>(gGame.GetClientDLLAddress() + Offset::PlantedC4, cPlantedC4))
				return BoomTime;
			if (!ProcessMgr.ReadMemory<uintptr_t>(cPlantedC4, cPlantedC4))
				return BoomTime;

			if (!ProcessMgr.ReadMemory(cPlantedC4 + Offset::C_PlantedC4.m_flC4Blow, BoomTime))
				return BoomTime;
			return BoomTime;
		}
	}
	bool getBombPlanted()
	{
		int Planted = false;
		uintptr_t cPlantedC4;
		ProcessMgr.ReadMemory(gGame.GetClientDLLAddress() + Offset::PlantedC4, cPlantedC4);
		if (!ProcessMgr.ReadMemory<uintptr_t>(gGame.GetClientDLLAddress() + Offset::PlantedC4, cPlantedC4))
			return Planted;
		if (!ProcessMgr.ReadMemory<uintptr_t>(cPlantedC4, cPlantedC4))
			return Planted;

		if (!ProcessMgr.ReadMemory(cPlantedC4 + Offset::C_PlantedC4.m_bC4Activated, Planted))
			return Planted;
		return Planted;
	}
	Vec3 getBombPos(bool Planted)
	{
		if (Planted)
		{
			int site;
			uintptr_t cPlantedC4;
			uintptr_t node;
			Vec3 c4origin;
			ProcessMgr.ReadMemory(gGame.GetClientDLLAddress() + Offset::PlantedC4, cPlantedC4);
			if (!ProcessMgr.ReadMemory<uintptr_t>(gGame.GetClientDLLAddress() + Offset::PlantedC4, cPlantedC4))
				return { 0,0,0 };
			if (!ProcessMgr.ReadMemory<uintptr_t>(cPlantedC4, cPlantedC4))
				return { 0,0,0 };

			if (!ProcessMgr.ReadMemory<uintptr_t>(cPlantedC4 +Offset::C_BaseEntity.m_pGameSceneNode, node))
				return { 0,0,0 };
			ProcessMgr.ReadMemory<Vec3>(node + Offset::CGameSceneNode.m_vecOrigin, c4origin);
			return c4origin;
		}

	}
	std::pair<int, int> get_bomb_calculations_by_map(const std::string& map) {
		int map_hash = hash::runtime(map);
		if (map_hash == hash::runtime("de_dust2")) {
			return { 500, 1750 };
		}
		else if (map_hash == hash::runtime("de_ancient")) {
			return { 650, 2275 };
		}
		else if (map_hash == hash::runtime("de_anubis")) {
			return { 450, 1575 };
		}
		else if (map_hash == hash::runtime("de_inferno")) {
			return { 620, 2170 };
		}
		else if (map_hash == hash::runtime("de_mirage")) {
			return { 650, 2275 };
		}
		else if (map_hash == hash::runtime("de_nuke")) {
			return { 650, 2275 };
		}
		else if (map_hash == hash::runtime("de_overpass")) {
			return { 650, 2275 };
		}
		else if (map_hash == hash::runtime("de_vertigo")) {
			return { 500, 1750 };
		}
		else if (map_hash == hash::runtime("de_assembly")) {
			return { 500, 1750 };
		}
		else if (map_hash == hash::runtime("de_memento")) {
			return { 500, 1750 };
		}
		else if (map_hash == hash::runtime("de_thera")) {
			return { 500, 1750 };
		}
		else if (map_hash == hash::runtime("de_mills")) {
			return { 500, 1750 };
		}
		else {
			return { 500, 1750 };
		}
	}
	float armor_modifier(float damage, int armor) {
		if (armor > 0) {
			const float armor_ratio = 0.5f;
			const float armor_bonus = 0.5f;
			float armor_ratio_multiply = damage * armor_ratio;
			float actual = (damage - armor_ratio_multiply) * armor_bonus;

			if (actual > static_cast<float>(armor)) {
				actual = static_cast<float>(armor) * (1.f / armor_bonus);
				armor_ratio_multiply = damage - actual;
			}

			damage = armor_ratio_multiply;
		}
		return damage;
	}

	int calculate_bomb_damage(Vec3 player, Vec3 bomb, int armor) {

		const std::pair<int, int> bomb_calculations = get_bomb_calculations_by_map(MenuConfig::CurMap);
		const int bomb_damage = bomb_calculations.first;
		const int bomb_radius = bomb_calculations.second;

		const double c = bomb_radius / 3;
		const float damage = bomb_damage* std::exp(-std::pow(sqrt(pow(player.x - bomb.x, 2) +
			pow(player.y - bomb.y, 2) +
			pow(player.z - bomb.z, 2)), 2) / (2 * std::pow(c, 2)));
		const float damage_armor = armor_modifier(damage, armor);

		return static_cast<int>(std::ceil(damage_armor));//if wanna more accurte, use std::round, ceil is to estim max damage to avoid unexpected death
	}

	void RenderWindow(CEntity Local)
	{
		if (!MiscCFG::bmbTimer)
			return;

		bool isBombPlanted = getBombPlanted();
		static float boomTime = 0;

		if (!isBombPlanted)
			boomTime = 0;
		else if (boomTime == 0)
			boomTime = getBombBoomTime(isBombPlanted);

		bool IsBeingDefused = getBombDefusing(isBombPlanted);
		static float DefuseTime = 0;

		if (IsBeingDefused && DefuseTime == 0)
			DefuseTime = getBombDefuseTime(isBombPlanted);
		else if (!IsBeingDefused)
			DefuseTime = 0;
		static float windowWidth = 200.0f;
		ImGuiWindowFlags flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize;
		//ImGui::SetNextWindowPos({ (ImGui::GetIO().DisplaySize.x - 200.0f) / 2.0f, 80.0f }, ImGuiCond_Once);
		//ImGui::SetNextWindowSize({ windowWidth, 0 });
		//if (!MenuConfig::ShowMenu)
			//ImGui::SetNextWindowBgAlpha(0.5f);
		ImVec4 default_bg_color = ImGui::GetStyleColorVec4(ImGuiCol_WindowBg);
		default_bg_color.w = 0.5f;
		ImGui::PushStyleColor(ImGuiCol_WindowBg, default_bg_color);
		ImGui::Begin(XorStr("Bomb Timer"), nullptr, flags);

		float remaining = boomTime - MenuConfig::CurTime;

		/*
		if (remaining > 10 || remaining < 0 || !isPlanted)
		{
			ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(0, 196, 0, 255));
		}
		else if (remaining > 5)
		{
			ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 155, 0, 255));
		}
		else {
			ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(242, 93, 93, 255));
		}*/

		ImGui::SetCursorPosX((ImGui::GetWindowSize().x - 180) * 0.5f);
		float barLength = remaining <= 0.0f ? 0.0f : remaining >= 40 ? 1.0f : (remaining / 40.0f);
		if (isBombPlanted && remaining >= 0)
		{
			int damage = calculate_bomb_damage(Local.Pawn.Pos, getBombPos(isBombPlanted), Local.Pawn.Armor);
			std::ostringstream ss,sv;
			ss.precision(3);
			ss << XorStr("Bomb on ") << (!getBombSite(isBombPlanted) ? "A" : "B") << ": " << std::fixed << remaining << " s";
			sv << XorStr("Estim Damage : ") << damage;
			Gui.MyText(std::move(ss).str().c_str(), true);
			Gui.MyProgressBar(barLength, { 185, 15 }, "", MiscCFG::BombTimerCol);
			Gui.MyText(std::move(sv).str().c_str(), true);
		}
		else 
		{
			barLength = 0.0f;
			Gui.MyText(XorStr("C4 not planted"), true);
			Gui.MyProgressBar(0, { 187, 15 }, "", MiscCFG::BombTimerCol);
			Gui.MyText(XorStr("Estim Damage : 0"), true);
		}

		ImGui::PopStyleColor();
		ImGui::End();
	}
}