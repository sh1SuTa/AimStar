#include "Entity.h"


std::map<int, std::string> CEntity::weaponNames = {
	{1, "deagle"},
	{2, "elite"},
	{3, "fiveseven"},
	{4, "glock"},
	{7, "ak47"},
	{8, "aug"},
	{9, "awp"},
	{10, "famas"},
	{11, "g3Sg1"},
	{13, "galilar"},
	{14, "m249"},
	{17, "mac10"},
	{19, "p90"},
	{23, "mp5sd"},
	{24, "ump45"},
	{25, "xm1014"},
	{26, "bizon"},
	{27, "mag7"},
	{28, "negev"},
	{29, "sawedoff"},
	{30, "tec9"},
	{31, "zeus"},
	{32, "p2000"},
	{33, "mp7"},
	{34, "mp9"},
	{35, "nova"},
	{36, "p250"},
	{38, "scar20"},
	{39, "sg556"},
	{40, "ssg08"},
	{42, "ct_knife"},
	{43, "flashbang"},
	{44, "hegrenade"},
	{45, "smokegrenade"},
	{46, "molotov"},
	{47, "decoy"},
	{48, "incgrenade"},
	{49, "c4"},
	{16, "m4a1"},
	{61, "usp"},
	{60, "m4a1_silencer"},
	{63, "cz75a"},
	{64, "revolver"},
	{59, "t_knife"}
};

inline std::string CEntity::GetWeaponName(int weaponID) {
	auto it = weaponNames.find(weaponID);
	if (it != weaponNames.end()) {
		return it->second;
	}
	return "Weapon_None";
}

bool CEntity::UpdateController(const DWORD64& PlayerControllerAddress)
{
	if (PlayerControllerAddress == 0)
		return false;
	this->Controller.Address = PlayerControllerAddress;
	if (!this->Controller.GetHealth())
		return false;
	if (!this->Controller.GetIsAlive())
		return false;
	if (!this->Controller.GetIsCtrlBot())
		return false; 
	if (!this->Controller.GetConnected())
		return false; 
	if (!this->Controller.GetHasHelmet())
		return false;
	if (!this->Controller.GetTeamID())
		return false;
	if (!this->Controller.GetPlayerSteamID())
		return false;
	if (!this->Controller.GetPlayerName())
		return false;
	if (!this->Controller.GetMoney())
		return false;

	this->Pawn.Address = this->Controller.GetPlayerhPawnAddress();//this->Controller.GetPlayerPawnAddress();
	return true;
}

bool CEntity::UpdatePawn(const DWORD64& PlayerPawnAddress)
{
	if (PlayerPawnAddress == 0)
		return false;
	this->Pawn.Address = PlayerPawnAddress;

	if (!this->Pawn.GetCameraPos())
		return false;
	if (!this->Pawn.GetPos())
		return false;
	if (!this->Pawn.GetViewAngle())
		return false;
	if (!this->Pawn.GetWeaponName())
		return false;
	if (!this->Pawn.GetAimPunchAngle())
		return false;
	if (!this->Pawn.GetShotsFired())
		return false;
	if (!this->Pawn.GetHealth())
		return false;
	if (!this->Pawn.GetAmmo())
		return false;
	if (!this->Pawn.GetMaxAmmo())
		return false;
	if (!this->Pawn.GetArmor())
		return false;
	if (!this->Pawn.GetTeamID())
		return false;
	if (!this->Pawn.GetFov())
		return false;
	if (!this->Pawn.GetSpotted())
		return false;
	if (!this->Pawn.GetFFlags())
		return false;
	if (!this->Pawn.GetDefusing())
		return false;
	if (!this->Pawn.GetFlashDuration())
		return false;
	if (!this->Pawn.GetVelocity())
		return false;
	if (!this->Pawn.GetAimPunchCache())
		return false;
	if (!this->Pawn.BoneData.UpdateAllBoneData(PlayerPawnAddress))
		return false;

	return true;
}

bool CEntity::UpdateClientData()
{
	if (!this->Client.GetSensitivity())
		return false;

	return true;
}

bool PlayerController::GetMoney()
{
	DWORD64 MoneyServices;
	if (!ProcessMgr.ReadMemory(Address + Offset::CCSPlayerController.m_pInGameMoneyServices, MoneyServices))
	{
		return false;
	}
	else {
		GetDataAddressWithOffset<int>(MoneyServices, Offset::CCSPlayerController_InGameMoneyServices.m_iAccount, this->Money);
		GetDataAddressWithOffset<int>(MoneyServices, Offset::CCSPlayerController_InGameMoneyServices.m_iTotalCashSpent, this->CashSpent);
		GetDataAddressWithOffset<int>(MoneyServices, Offset::CCSPlayerController_InGameMoneyServices.m_iCashSpentThisRound, this->CashSpentTotal);
		return true;
	}
}

bool PlayerController::GetTeamID()
{
	return GetDataAddressWithOffset<int>(Address, Offset::C_BaseEntity.m_iTeamNum, this->TeamID);
}

bool PlayerController::GetHealth()
{
	return GetDataAddressWithOffset<int>(Address, Offset::C_BaseEntity.m_iHealth, this->Health);
}

bool PlayerController::GetIsAlive()
{
	return GetDataAddressWithOffset<int>(Address, Offset::CCSPlayerController.m_bPawnIsAlive, this->AliveStatus);
}

bool PlayerController::GetIsCtrlBot()
{
	return GetDataAddressWithOffset<int>(Address, Offset::CCSPlayerController.m_bControllingBot, this->CtrlBot);
}

bool PlayerController::GetConnected()
{
	return GetDataAddressWithOffset<bool>(Address, Offset::CCSPlayerController.m_bEverPlayedOnTeam, this->Connected);
}
bool PlayerController::GetHasHelmet()
{
	return GetDataAddressWithOffset<bool>(Address, Offset::CCSPlayerController.m_bPawnHasHelmet, this->HasHelmet);
}


bool PlayerController::GetPlayerName()
{
	char Buffer[MAX_PATH]{};

	if (!ProcessMgr.ReadMemory(Address + Offset::CBasePlayerController.m_iszPlayerName, Buffer, MAX_PATH))
		return false;
	if (!this->SteamID)
		this->PlayerName = "BOT " + std::string(Buffer);
	else
		this->PlayerName = Buffer;
	if (this->PlayerName.empty())
		this->PlayerName = "Name_None";

	return true;
}

bool PlayerController::GetPlayerSteamID()
{
	return GetDataAddressWithOffset<INT64>(Address, Offset::CBasePlayerController.m_steamID, this->SteamID);
}
bool PlayerPawn::GetViewAngle()
{
	return GetDataAddressWithOffset<Vec2>(Address, Offset::C_CSPlayerPawnBase.m_angEyeAngles, this->ViewAngle);
}

bool PlayerPawn::GetCameraPos()
{
	return GetDataAddressWithOffset<Vec3>(Address, Offset::C_CSPlayerPawnBase.m_vecLastClipCameraPos, this->CameraPos);
}

bool PlayerPawn::GetSpotted()
{
	return GetDataAddressWithOffset<DWORD64>(Address, Offset::C_CSPlayerPawn.m_bSpottedByMask, this->bSpottedByMask);
}


bool PlayerPawn::GetWeaponName()
{
	DWORD64 WeaponNameAddress = 0;
	char Buffer[256]{};
	
	WeaponNameAddress = ProcessMgr.TraceAddress(this->Address + Offset::C_CSPlayerPawnBase.m_pClippingWeapon, { 0x10,0x20 ,0x0 });
	if (WeaponNameAddress == 0)
		return false;

	DWORD64 CurrentWeapon;
	short weaponIndex;
	ProcessMgr.ReadMemory(this->Address + Offset::C_CSPlayerPawnBase.m_pClippingWeapon, CurrentWeapon);
	ProcessMgr.ReadMemory(CurrentWeapon + Offset::EconEntity.AttributeManager + Offset::WeaponBaseData.Item + Offset::WeaponBaseData.ItemDefinitionIndex, weaponIndex);

	if (weaponIndex == -1)
		return false;

	WeaponName = CEntity::GetWeaponName(weaponIndex);

	return true;
}

bool PlayerPawn::GetShotsFired()
{
	return GetDataAddressWithOffset<DWORD>(Address, Offset::C_CSPlayerPawn.m_iShotsFired, this->ShotsFired);
}

bool PlayerPawn::GetAimPunchAngle()
{
	return GetDataAddressWithOffset<Vec2>(Address, Offset::C_CSPlayerPawn.m_aimPunchAngle, this->AimPunchAngle);
}

bool PlayerPawn::GetTeamID()
{
	return GetDataAddressWithOffset<int>(Address, Offset::C_BaseEntity.m_iTeamNum, this->TeamID);
}

bool PlayerPawn::GetAimPunchCache()
{
	return GetDataAddressWithOffset<C_UTL_VECTOR>(Address, Offset::C_CSPlayerPawn.m_aimPunchCache, this->AimPunchCache);
}

DWORD64 PlayerController::GetPlayerPawnAddress()
{
	DWORD64 EntityPawnListEntry = 0;
	DWORD64 EntityPawnAddress = 0;

	if (!GetDataAddressWithOffset<DWORD>(Address, Offset::CCSPlayerController.m_hPlayerPawn, this->Pawn))
		return 0;

	if (!ProcessMgr.ReadMemory<DWORD64>(gGame.GetEntityListAddress(), EntityPawnListEntry))
		return 0;

	if (!ProcessMgr.ReadMemory<DWORD64>(EntityPawnListEntry + 0x10 + 8 * ((Pawn & 0x7FFF) >> 9), EntityPawnListEntry))
		return 0;

	if (!ProcessMgr.ReadMemory<DWORD64>(EntityPawnListEntry + 0x78 * (Pawn & 0x1FF), EntityPawnAddress))
		return 0;

	return EntityPawnAddress;
}


DWORD64 PlayerController::GetPlayerhPawnAddress()
{
	DWORD64 EntityPawnListEntry = 0;
	DWORD64 EntityPawnAddress = 0;

	if (!GetDataAddressWithOffset<DWORD>(Address, Offset::CBasePlayerController.m_hPawn, this->Pawn))
		return 0;

	if (!ProcessMgr.ReadMemory<DWORD64>(gGame.GetEntityListAddress(), EntityPawnListEntry))
		return 0;

	if (!ProcessMgr.ReadMemory<DWORD64>(EntityPawnListEntry + 0x10 + 8 * ((Pawn & 0x7FFF) >> 9), EntityPawnListEntry))
		return 0;

	if (!ProcessMgr.ReadMemory<DWORD64>(EntityPawnListEntry + 0x78 * (Pawn & 0x1FF), EntityPawnAddress))
		return 0;

	return EntityPawnAddress;
}



bool PlayerPawn::GetPos()
{
	DWORD64 GameSceneNode;
	if (!ProcessMgr.ReadMemory<uintptr_t>(Address + Offset::C_BaseEntity.m_pGameSceneNode, GameSceneNode))
		return false;
	
	return ProcessMgr.ReadMemory<Vec3>(GameSceneNode + Offset::CGameSceneNode.m_vecOrigin, this->Pos);
	//return GetDataAddressWithOffset<Vec3>(Address, Offset::C_BasePlayerPawn.m_vOldOrigin, this->Pos);
}

bool PlayerPawn::GetHealth()
{
	return GetDataAddressWithOffset<int>(Address, Offset::C_BaseEntity.m_iHealth, this->Health);
}

bool PlayerPawn::GetArmor()
{
	return GetDataAddressWithOffset<int>(Address, Offset::C_CSPlayerPawn.m_ArmorValue, this->Armor);
}



bool PlayerPawn::GetAmmo()
{
	DWORD64 ClippingWeapon = 0;
	if (!ProcessMgr.ReadMemory<DWORD64>(Address + Offset::C_CSPlayerPawnBase.m_pClippingWeapon, ClippingWeapon))
		return false;

	return GetDataAddressWithOffset<int>(ClippingWeapon, Offset::WeaponBaseData.Clip1, this->Ammo);
}
bool PlayerPawn::GetBullet()
{
	DWORD64 ClippingWeapon = 0;
	if (!ProcessMgr.ReadMemory<DWORD64>(Address + Offset::C_CSPlayerPawnBase.m_pClippingWeapon, ClippingWeapon))
		return false;

	return GetDataAddressWithOffset<int>(ClippingWeapon, Offset::WeaponBaseData.Clip1, this->Bullet);
}
bool PlayerPawn::GetMaxAmmo()
{
	DWORD64 ClippingWeapon = 0;
	DWORD64 WeaponData = 0;
	if (!ProcessMgr.ReadMemory<DWORD64>(Address + Offset::C_CSPlayerPawnBase.m_pClippingWeapon, ClippingWeapon))
		return false;
	if (!ProcessMgr.ReadMemory<DWORD64>(ClippingWeapon + Offset::WeaponBaseData.WeaponDataPTR, WeaponData))
		return false;

	return GetDataAddressWithOffset<int>(WeaponData, Offset::WeaponBaseData.MaxClip, this->MaxAmmo);
}

bool PlayerPawn::GetFov()
{
	DWORD64 CameraServices = 0;
	if (!ProcessMgr.ReadMemory<DWORD64>(Address + Offset::C_BasePlayerPawn.m_pCameraServices, CameraServices))
		return false;
	return GetDataAddressWithOffset<int>(CameraServices, Offset::CCSPlayerBase_CameraServices.m_iFOVStart, this->Fov);
}

bool PlayerPawn::GetFFlags()
{
	return GetDataAddressWithOffset<int>(Address, Offset::C_BaseEntity.m_fFlags, this->fFlags);
}

bool PlayerPawn::GetDefusing()
{
	return ProcessMgr.ReadMemory(Address + Offset::C_PlantedC4.m_bBeingDefused, this->isDefusing);
}

bool PlayerPawn::GetFlashDuration()
{
	return ProcessMgr.ReadMemory(Address + Offset::C_CSPlayerPawnBase.m_flFlashDuration, this->FlashDuration);
}

bool PlayerPawn::GetVelocity()
{
	if (!ProcessMgr.ReadMemory(Address + Offset::C_BaseEntity.m_vecAbsVelocity, this->Velocity))
		return false;
	this->Speed = sqrt(this->Velocity.x * this->Velocity.x + this->Velocity.y * this->Velocity.y);
	return true;
}

bool CEntity::IsAlive()
{
	return (this->Controller.AliveStatus == 1 || this->Controller.CtrlBot == 1) && this->Pawn.Health > 0;
}

bool CEntity::ESPAlive()
{
	return this->Pawn.Health > 0;
}

bool CEntity::IsInScreen()
{
	return gGame.View.WorldToScreen(this->Pawn.Pos, this->Pawn.ScreenPos);
}

CBone CEntity::GetBone() const
{
	if (this->Pawn.Address == 0)
		return CBone{};
	return this->Pawn.BoneData;
}

bool Client::GetSensitivity()
{
	DWORD64 dwSensitivity;
	float flSensitivity;
	ProcessMgr.ReadMemory(gGame.GetClientDLLAddress() + Offset::Sensitivity, dwSensitivity);
	if (ProcessMgr.ReadMemory(dwSensitivity + 0x40, flSensitivity))
	{
		this->Sensitivity = flSensitivity;
		return true;
	}
	else
		return false;
}
