#include "Bone.h"

bool CBone::UpdateAllBoneData(const DWORD64& EntityPawnAddress) {
    if (EntityPawnAddress == 0) {
        return false;
    }
    this->EntityPawnAddress = EntityPawnAddress;

    DWORD64 GameSceneNode = 0;
    DWORD64 BoneArrayAddress = 0;
    if (!ProcessMgr.ReadMemory<DWORD64>(EntityPawnAddress + Offset::C_BaseEntity.m_pGameSceneNode, GameSceneNode)) {
        return false;
    }
    uintptr_t pModelState = 0;
	ProcessMgr.ReadMemory(GameSceneNode + 0x140, pModelState);
	ProcessMgr.ReadMemory(pModelState + 0x80, BoneArrayAddress);
    constexpr size_t NUM_BONES = 30;
    BoneJointData BoneArray[NUM_BONES]{};
    if (!ProcessMgr.ReadMemory(BoneArrayAddress, BoneArray, NUM_BONES * sizeof(BoneJointData))) {
        return false;
    }

    BonePosList.clear();

    for (const auto& bone : BoneArray) {
        Vec2 ScreenPos;
        bool IsVisible = false;

        if (gGame.View.WorldToScreen(bone.Pos, ScreenPos)) {
            IsVisible = true;
        }

        this->BonePosList.push_back({ bone.Pos, ScreenPos, IsVisible });
    }

    return !BonePosList.empty();
}
