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
    
    if (!ProcessMgr.ReadMemory<DWORD64>(GameSceneNode + Offset::Pawn.BoneArray, BoneArrayAddress)) {
        return false;
    }
    // Entity origin, used to validate bone positions
    Vec3 Origin;
    if (!ProcessMgr.ReadMemory<Vec3>(GameSceneNode + Offset::CGameSceneNode.m_vecOrigin, Origin)) {
        return false;
    }
    constexpr size_t NUM_BONES = 30;
    // Real skeleton bones are always within ~110 units of the entity origin;
    // IK/attachment entries in the bone table can be far away and must be filtered out
    constexpr float MAX_BONE_DIST = 150.f;
    BoneJointData BoneArray[NUM_BONES]{};
    if (!ProcessMgr.ReadMemory(BoneArrayAddress, BoneArray, NUM_BONES * sizeof(BoneJointData))) {
        return false;
    }

    BonePosList.clear();

    for (const auto& bone : BoneArray) {
        Vec2 ScreenPos;
        bool IsVisible = false;

        // NaN / far-away positions are rejected here
        float DX = bone.Pos.x - Origin.x;
        float DY = bone.Pos.y - Origin.y;
        float DZ = bone.Pos.z - Origin.z;
        if (DX * DX + DY * DY + DZ * DZ <= MAX_BONE_DIST * MAX_BONE_DIST && gGame.View.WorldToScreen(bone.Pos, ScreenPos)) {
            IsVisible = true;
        }

        this->BonePosList.push_back({ bone.Pos, ScreenPos, IsVisible });
    }

    return !BonePosList.empty();
}
