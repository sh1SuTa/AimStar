#pragma once
#include <vector>
#include "Game.h"
#include <list>

// animgraph_2_beta update (2026-04): root_motion bone inserted at index 0,
// all old indices shifted by +1, weapon bones now occupy 22-27
enum BONEINDEX : DWORD
{
	head=7,
	neck_0=6,
	spine_1=3,
	spine_2=4,
	pelvis=1,
	clavicle_L=8,
	arm_upper_L=9,
	arm_lower_L=10,
	hand_L=11,
	clavicle_R=12,
	arm_upper_R=13,
	arm_lower_R=14,
	hand_R=15,
	leg_upper_L=16,
	leg_lower_L=17,
	ankle_L=18,
	leg_upper_R=19,
	leg_lower_R=20,
	ankle_R=21,
};

struct BoneJointData
{
	Vec3 Pos;
    float Scale;
	char pad[0x10];
};

struct BoneJointPos
{
	Vec3 Pos;
	Vec2 ScreenPos;
	bool IsVisible = false;
};

class CBone
{
private:
	DWORD64 EntityPawnAddress = 0;
public:
	std::vector<BoneJointPos> BonePosList;

	bool UpdateAllBoneData(const DWORD64& EntityPawnAddress);
};

namespace BoneJointList
{
	// ¼¹¹Ç
	inline std::list<DWORD> Trunk = { neck_0,spine_2, pelvis};
	// ×ó±Û
	inline std::list<DWORD> LeftArm = { neck_0,  arm_upper_L, arm_lower_L, hand_L };
	// ÓÒ±Û
	inline std::list<DWORD> RightArm = { neck_0, arm_upper_R,arm_lower_R, hand_R };
	// ×óÍÈ	
	inline std::list<DWORD> LeftLeg = { pelvis, leg_upper_L , leg_lower_L, ankle_L };
	// ÓÒÍÈ
	inline std::list<DWORD> RightLeg = { pelvis, leg_upper_R , leg_lower_R, ankle_R };
	// ×ÜÁÐ±í
	inline std::vector<std::list<DWORD>> List = { Trunk, LeftArm, RightArm, LeftLeg, RightLeg };
}
