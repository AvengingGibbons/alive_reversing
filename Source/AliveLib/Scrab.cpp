#include "stdafx.h"
#include "Scrab.hpp"
#include "Function.hpp"
#include "Game.hpp"
#include "Map.hpp"
#include "stdlib.hpp"
#include "Shadow.hpp"
#include "MusicController.hpp"
#include "Abe.hpp"
#include "ObjectIds.hpp"
#include "PlatformBase.hpp"
#include "Events.hpp"
#include "DDCheat.hpp"
#include "Particle.hpp"
#include "Sfx.hpp"
#include "Midi.hpp"
#include "GameSpeak.hpp"
#include "SwitchStates.hpp"
#include "SlamDoor.hpp"
#include "LiftPoint.hpp"
#include "Slurg.hpp"

TintEntry stru_560260[15] =
{
    { 1u, 127u, 127u, 127u },
    { 2u, 137u, 137u, 137u },
    { 3u, 127u, 127u, 127u },
    { 4u, 127u, 127u, 127u },
    { 5u, 127u, 127u, 127u },
    { 6u, 127u, 127u, 127u },
    { 7u, 127u, 127u, 127u },
    { 8u, 127u, 127u, 127u },
    { 9u, 127u, 127u, 127u },
    { 10u, 127u, 127u, 127u },
    { 11u, 127u, 127u, 127u },
    { 12u, 127u, 127u, 127u },
    { 13u, 127u, 127u, 127u },
    { 14u, 127u, 127u, 127u },
    { -1, 127u, 127u, 127u }
};

const SfxDefinition sScrabSfx_560330[10] =
{
    { 0u, 4u, 60u, 55u, 0, 0 },
    { 0u, 4u, 61u, 70u, 0, 0 },
    { 0u, 4u, 62u, 80u, 0, 0 },
    { 0u, 4u, 63u, 80u, 0, 0 },
    { 0u, 4u, 64u, 60u, -127, 127 },
    { 0u, 4u, 66u, 90u, 0, 0 },
    { 0u, 4u, 67u, 50u, -511, 0 },
    { 0u, 4u, 67u, 50u, 0, 511 },
    { 0u, 4u, 68u, 110u, -1791, -1791 },
    { 0u, 0u, 0u, 0u, 0, 0 }
};

#define MAKE_FN(VAR) &Scrab::VAR,

const TScrabMotionFn sScrab_motion_table_560120[40] =
{
    SCRAB_MOTIONS_ENUM(MAKE_FN)
};

const TScrabAIFn sScrab_ai_table_56029C[6] =
{
    &Scrab::AI_Patrol_0_4AA630,
    &Scrab::AI_ChasingEnemy_1_4A6470,
    &Scrab::AI_Fighting_2_4A5840,
    &Scrab::AI_Death_3_4A62B0,
    &Scrab::AI_ShrinkDeath_4_4A6420,
    &Scrab::AI_Possessed_5_4A6180
};


const static AIFunctionData<TScrabAIFn> sScrabAITable[6] =
{
    { &Scrab::AI_Patrol_0_4AA630,  0x404070, "AI_Patrol_0", },
    { &Scrab::AI_ChasingEnemy_1_4A6470,  0x403B98, "AI_ChasingEnemy_1", },
    { &Scrab::AI_Fighting_2_4A5840,  0x403E4F, "AI_Fighting_2", },
    { &Scrab::AI_Death_3_4A62B0,  0x4039C2, "AI_Death_3", },
    { &Scrab::AI_ShrinkDeath_4_4A6420,  0x4036B1, "AI_ShrinkDeath_4", },
    { &Scrab::AI_Possessed_5_4A6180,  0x4021F3, "AI_Possessed_5", },
};

void Scrab::SetBrain(TScrabAIFn fn)
{
    ::SetBrain(fn, field_118_brain_state, sScrabAITable);
}

bool Scrab::BrainIs(TScrabAIFn fn)
{
    return ::BrainIs(fn, field_118_brain_state, sScrabAITable);
}

Scrab* Scrab::ctor_4A3C40(Path_Scrab* pTlv, int tlvInfo, __int16 spawnedScale)
{
    ctor_408240(14);
    field_190 = 0;
    field_17C_last_event = -1;
    field_192 = -1;

    SetVTable(this, 0x546DD0);

    field_4_typeId = Types::eScrab_112;

    if (tlvInfo != 0xFFFF)
    {
        field_C_objectId = tlvInfo;
    }

    field_124_fight_target_obj_id = -1;
    field_120_obj_id = -1;

    field_10_resources_array.SetAt(0,  ResourceManager::GetLoadedResource_49C2A0(ResourceManager::Resource_Animation, 700, 1, 0));
    field_10_resources_array.SetAt(11, ResourceManager::GetLoadedResource_49C2A0(ResourceManager::Resource_Animation, 711, 1, 0));
    field_10_resources_array.SetAt(6,  ResourceManager::GetLoadedResource_49C2A0(ResourceManager::Resource_Animation, 706, 1, 0));
    field_10_resources_array.SetAt(8,  ResourceManager::GetLoadedResource_49C2A0(ResourceManager::Resource_Animation, 708, 1, 0));
    field_10_resources_array.SetAt(1,  ResourceManager::GetLoadedResource_49C2A0(ResourceManager::Resource_Animation, 701, 1, 0));
    field_10_resources_array.SetAt(10, ResourceManager::GetLoadedResource_49C2A0(ResourceManager::Resource_Animation, 710, 1, 0));
    field_10_resources_array.SetAt(5,  ResourceManager::GetLoadedResource_49C2A0(ResourceManager::Resource_Animation, 705, 1, 0));
    field_10_resources_array.SetAt(2,  ResourceManager::GetLoadedResource_49C2A0(ResourceManager::Resource_Animation, 702, 1, 0));
    field_10_resources_array.SetAt(9,  ResourceManager::GetLoadedResource_49C2A0(ResourceManager::Resource_Animation, 709, 1, 0));
    field_10_resources_array.SetAt(3,  ResourceManager::GetLoadedResource_49C2A0(ResourceManager::Resource_Animation, 703, 1, 0));
    field_10_resources_array.SetAt(4,  ResourceManager::GetLoadedResource_49C2A0(ResourceManager::Resource_Animation, 704, 1, 0));
    field_10_resources_array.SetAt(13, ResourceManager::GetLoadedResource_49C2A0(ResourceManager::Resource_Animation, 713, 1, 0));
    
    Animation_Init_424E10(224764, 156, 69, field_10_resources_array.ItemAt(0), 1, 1);

    field_140 = 0;
    field_12C = 0;
    field_108_next_motion = eScrabMotions::M_Stand_0_4A8220;
    field_110_id = -1;
    field_106_current_motion = eScrabMotions::M_Stand_0_4A8220;
    field_11E = 0;

    field_1AA_flags.Clear(Flags_1AA::eBit1);
    field_1AA_flags.Clear(Flags_1AA::eBit4);

    field_114_flags.Set(Flags_114::e114_Bit3_Can_Be_Possessed);
    field_114_flags.Set(Flags_114::e114_Bit6_SetOffExplosives);
    field_114_flags.Clear(Flags_114::e114_Bit9);

    field_164 = 0;
    field_16C = 0;
    field_170 = sGnFrame_5C1B84;
    field_1A2 = 0;
    field_1A4 = 0;
    field_1A6 = 25;
    field_178 = 0;
    field_154 = 0;

    field_B8_xpos = FP_FromInteger(pTlv->field_8_top_left.field_0_x + 12);
    field_BC_ypos = FP_FromInteger(pTlv->field_8_top_left.field_2_y);

    if (pTlv->field_10_scale == 1)
    {
        field_CC_sprite_scale = FP_FromDouble(0.5);
        field_20_animation.field_C_render_layer = 8;
        field_D6_scale = 0;
    }
    else if (pTlv->field_10_scale == 0)
    {
        field_CC_sprite_scale = FP_FromInteger(1);
        field_20_animation.field_C_render_layer = 27;
        field_D6_scale = 1;
    }

    if (spawnedScale == 1)
    {
        field_B8_xpos -= ScaleToGridSize_4498B0(field_CC_sprite_scale);
    }
    else if (spawnedScale == 2)
    {
        field_B8_xpos += ScaleToGridSize_4498B0(field_CC_sprite_scale);
    }

    field_128_attack_delay = pTlv->field_12_attack_delay;
    field_12A_patrol_type = pTlv->field_14_patrol_type;
    field_158_left_min_delay = pTlv->field_16_left_min_delay;
    field_15A_left_max_delay = pTlv->field_18_left_max_delay;
    field_15C = pTlv->field_1A_right_min_delay;
    field_15E_right_max_delay = pTlv->field_1C_right_max_delay;
    field_148_attack_duration = pTlv->field_1E_attack_duration;
    field_174_whirl_attack_duration = pTlv->field_26_whirl_attack_duration;
    field_176_whirl_attack_recharge = pTlv->field_28_whirl_attack_recharge;
    field_1A8_kill_close_fleech = pTlv->field_2A_kill_close_fleech;

    field_1A0 = 3;

    field_1AA_flags.Set(Flags_1AA::eBit5_roar_randomly, pTlv->field_22_roar_randomly & 1);
    field_1AA_flags.Set(Flags_1AA::eBit6_persistant, pTlv->field_24_persistant & 1);
    field_1AA_flags.Clear(Flags_1AA::eBit3);

    if (!OnFloor_4A41E0())
    {
        field_106_current_motion = eScrabMotions::M_JumpToFall_8_4A9220;
        vUpdateAnim_4A34F0();
        field_1C_update_delay = 30;
    }

    SetTint_425600(&stru_560260[0], gMap_5C3030.sCurrentLevelId_5C3030);
    
    field_DC_bApplyShadows |= 2u;

    field_14C = 0;
    field_150 = 0;
    field_144_tlvInfo = tlvInfo;
    field_11C_sub_state = 0;

    ToPatrol_4AA600();

    field_E0_pShadow = alive_new<Shadow>();
    if (field_E0_pShadow)
    {
        field_E0_pShadow->ctor_4AC990();
    }

    return this;
}

BaseGameObject* Scrab::VDestructor(signed int flags)
{
    return vdtor_4A41B0(flags);
}

void Scrab::VUpdate()
{
    vUpdate_4A3530();
}


const int sScrabFrameTableOffsets_5601C0[40] =
{
    224764,
    224668,
    224796,
    224860,
    224916,
    224964,
    224988,
    225028,
    225112,
    225052,
    225072,
    225092,
    224988,
    225028,
    225132,
    225112,
    225168,
    225188,
    225208,
    225280,
    225028,
    24480,
    24480,
    1340,
    1340,
    11228,
    17260,
    17328,
    17260,
    17328,
    11532,
    31648,
    31704,
    35180,
    35248,
    20840,
    20896,
    8356,
    14508,
    15600
};

int CC Scrab::CreateFromSaveState_4A70A0(const BYTE* pBuffer)
{
    auto pState = reinterpret_cast<const Scrab_State*>(pBuffer);

    auto pTlv = static_cast<Path_Scrab*>(sPath_dword_BB47C0->TLV_From_Offset_Lvl_Cam_4DB770(pState->field_44_tlvInfo));

    if (!ResourceManager::GetLoadedResource_49C2A0(ResourceManager::Resource_Animation, ResourceID::kArsbasicResID, FALSE, FALSE))
    {
        ResourceManager::LoadResourceFile_49C170("SCRAB.BND", nullptr);
    }

    auto pScrab = alive_new<Scrab>();
    pScrab->ctor_4A3C40(pTlv, pState->field_44_tlvInfo, 0);
    pScrab->field_C_objectId = pState->field_4_obj_id;

    if (pState->field_40_bIsControlled)
    {
        sControlledCharacter_5C1B8C = pScrab;
    }

    pScrab->field_FC_pPathTLV = nullptr;
    pScrab->field_100_pCollisionLine = nullptr;

    pScrab->field_B8_xpos = pState->field_8_xpos;
    pScrab->field_BC_ypos = pState->field_C_ypos;
    pScrab->field_C4_velx = pState->field_10_velx;
    pScrab->field_C8_vely = pState->field_14_vely;

    pScrab->field_134 = pState->field_64;
    pScrab->field_C0_path_number = pState->field_18_path_number;
    pScrab->field_C2_lvl_number = pState->field_1A_lvl_number;
    pScrab->field_CC_sprite_scale = pState->field_1C_sprite_scale;
    pScrab->field_D0_r = pState->field_20_r;
    pScrab->field_D2_g = pState->field_22_g;
    pScrab->field_D4_b = pState->field_24_b;
    pScrab->field_106_current_motion = pState->field_28_current_motion;

    BYTE** ppRes = pScrab->ResBlockForMotion_4A43E0(pState->field_28_current_motion);
    pScrab->field_20_animation.Set_Animation_Data_409C80(sScrabFrameTableOffsets_5601C0[pScrab->field_106_current_motion], ppRes);
    pScrab->field_20_animation.field_92_current_frame = pState->field_2A_current_frame;
    pScrab->field_20_animation.field_E_frame_change_counter = pState->field_2C_frame_change_counter;

    pScrab->field_6_flags.Set(BaseGameObject::eDrawable, pState->field_2F_bDrawable & 1);

    pScrab->field_20_animation.field_4_flags.Set(AnimFlags::eBit5_FlipX, pState->field_26_bAnimFlipX & 1);
    pScrab->field_20_animation.field_4_flags.Set(AnimFlags::eBit3_Render, pState->field_2E_bAnimRender & 1);

    if (IsLastFrame(&pScrab->field_20_animation))
    {
        pScrab->field_20_animation.field_4_flags.Set(AnimFlags::eBit18_IsLastFrame);
    }

    pScrab->field_10C_health = pState->field_30_health;
    pScrab->field_106_current_motion = pState->field_34_current_motion;
    pScrab->field_108_next_motion = pState->field_36_next_motion;
    pScrab->field_F8_LastLineYPos = FP_FromInteger(pState->field_38);
    pScrab->field_130 = pState->field_60;
    pScrab->field_114_flags.Set(Flags_114::e114_Bit9);
    pScrab->field_12C = pState->field_5C;
    pScrab->field_104_collision_line_type = pState->field_3A_line_type;
    pScrab->field_144_tlvInfo = pState->field_44_tlvInfo;
    
    pScrab->SetBrain(sScrab_ai_table_56029C[pState->field_48_ai_idx]);

    pScrab->field_11C_sub_state = pState->field_50_sub_state;
    pScrab->field_120_obj_id = pState->field_54_obj_id;
    pScrab->field_124_fight_target_obj_id = pState->field_58_target_obj_id;

    pScrab->field_140 = pState->field_68;
    pScrab->field_14C = pState->field_6C;
    pScrab->field_150 = pState->field_70;
    pScrab->field_154 = pState->field_74;
    pScrab->field_160 = pState->field_78;
    pScrab->field_164 = pState->field_7C;

    pScrab->field_166_level = pState->field_7E_level;
    pScrab->field_168_path = pState->field_80_path;
    pScrab->field_16A_camera = pState->field_82_camera;
    pScrab->field_16C = InputObject::Command_To_Raw_45EE40(pState->field_84_input);
    pScrab->field_170 = pState->field_88;
    pScrab->field_178 = pState->field_8C;
    pScrab->field_194 = pState->field_8E;
    pScrab->field_198 = pState->field_90;
    pScrab->field_19C = pState->field_94;
    pScrab->field_1A2 = pState->field_98;
    pScrab->field_1A4 = pState->field_9A;
    pScrab->field_1A6 = pState->field_9C;

    pScrab->field_1AA_flags.Set(Flags_1AA::eBit1, pState->field_9E.Get(Scrab_State::eBit1));
    pScrab->field_1AA_flags.Set(Flags_1AA::eBit2, pState->field_9E.Get(Scrab_State::eBit2));
    pScrab->field_1AA_flags.Set(Flags_1AA::eBit3, pState->field_9E.Get(Scrab_State::eBit3));
    pScrab->field_1AA_flags.Set(Flags_1AA::eBit4, pState->field_9E.Get(Scrab_State::eBit4));
    pScrab->field_1AA_flags.Set(Flags_1AA::eBit5_roar_randomly, pState->field_9E.Get(Scrab_State::eBit5));
    pScrab->field_1AA_flags.Set(Flags_1AA::eBit6_persistant, pState->field_9E.Get(Scrab_State::eBit6));

    return sizeof(Scrab_State);
}

int Scrab::vGetSaveState_4AB020(Scrab_State* pState)
{
    if (field_114_flags.Get(Flags_114::e114_Bit7_Electrocuted))
    {
        return 0;
    }

    pState->field_0_type = Types::eScrab_112;
    pState->field_4_obj_id = field_C_objectId;

    pState->field_8_xpos = field_B8_xpos;
    pState->field_C_ypos = field_BC_ypos;
    pState->field_10_velx = field_C4_velx;
    pState->field_14_vely = field_C8_vely;

    pState->field_64 = field_134;

    pState->field_18_path_number = field_C0_path_number;
    pState->field_1A_lvl_number = field_C2_lvl_number;
    pState->field_1C_sprite_scale = field_CC_sprite_scale;

    pState->field_20_r = field_D0_r;
    pState->field_22_g = field_D2_g;
    pState->field_24_b = field_D4_b;

    pState->field_26_bAnimFlipX = field_20_animation.field_4_flags.Get(AnimFlags::eBit5_FlipX);
    pState->field_28_current_motion = field_106_current_motion;
    pState->field_2A_current_frame = field_20_animation.field_92_current_frame;
    pState->field_2C_frame_change_counter = field_20_animation.field_E_frame_change_counter;
    pState->field_2F_bDrawable = field_6_flags.Get(BaseGameObject::eDrawable);
    pState->field_2E_bAnimRender = field_20_animation.field_4_flags.Get(AnimFlags::eBit3_Render);
    pState->field_30_health = field_10C_health;
    pState->field_34_current_motion = field_106_current_motion;
    pState->field_36_next_motion = field_108_next_motion;
    pState->field_3A_line_type = -1;
    
    // TODO: Check correctness
    pState->field_38 = FP_GetExponent(field_F8_LastLineYPos);
    if (field_100_pCollisionLine)
    {
        pState->field_3A_line_type = field_100_pCollisionLine->field_8_type;
    }

    pState->field_40_bIsControlled = (this == sControlledCharacter_5C1B8C);
    pState->field_60 = field_130;
    pState->field_5C = field_12C;
    pState->field_44_tlvInfo = field_144_tlvInfo;
    pState->field_48_ai_idx = 0;

    int idx = 0;
    for (const auto& fn : sScrab_ai_table_56029C)
    {
        if (BrainIs(fn))
        {
            pState->field_48_ai_idx = idx;
        }
        idx++;
    }

    pState->field_54_obj_id = -1;
    pState->field_50_sub_state = field_11C_sub_state;

    if (field_120_obj_id != -1)
    {
        BaseGameObject* pObj = sObjectIds_5C1B70.Find_449CF0(field_120_obj_id);
        if (pObj)
        {
            pState->field_54_obj_id = pObj->field_C_objectId;
        }
    }

    pState->field_58_target_obj_id = -1;
    if (field_124_fight_target_obj_id != -1)
    {
        BaseGameObject* pObj = sObjectIds_5C1B70.Find_449CF0(field_124_fight_target_obj_id);
        if (pObj)
        {
            pState->field_58_target_obj_id = pObj->field_C_objectId;
        }
    }

    pState->field_68 = field_140;
    pState->field_6C = field_14C;
    pState->field_70 = field_150;
    pState->field_74 = field_154;
    pState->field_78 = field_160;
    pState->field_7C = field_164;
    pState->field_7E_level = field_166_level;
    pState->field_80_path = field_168_path;
    pState->field_82_camera = field_16A_camera;
    pState->field_84_input = InputObject::Raw_To_Command_45EF70(field_16C);
    pState->field_88 = field_170;
    pState->field_8C = field_178;
    pState->field_8E = field_194;
    pState->field_90 = field_198;
    pState->field_94 = field_19C;
    pState->field_98 = field_1A2;
    pState->field_9A = field_1A4;
    pState->field_9C = field_1A6;

    pState->field_9E.Set(Scrab_State::eBit1, field_1AA_flags.Get(Flags_1AA::eBit1));
    pState->field_9E.Set(Scrab_State::eBit2, field_1AA_flags.Get(Flags_1AA::eBit2));
    pState->field_9E.Set(Scrab_State::eBit3, field_1AA_flags.Get(Flags_1AA::eBit3));
    pState->field_9E.Set(Scrab_State::eBit4, field_1AA_flags.Get(Flags_1AA::eBit4));
    pState->field_9E.Set(Scrab_State::eBit5, field_1AA_flags.Get(Flags_1AA::eBit5_roar_randomly));
    pState->field_9E.Set(Scrab_State::eBit6, field_1AA_flags.Get(Flags_1AA::eBit6_persistant));

    return sizeof(Scrab_State);
}

Scrab* Scrab::vdtor_4A41B0(signed int flags)
{
    dtor_4A42B0();
    if (flags & 1)
    {
        Mem_Free_495540(this);
    }
    return this;
}

void Scrab::dtor_4A42B0()
{
    SetVTable(this, 0x546DD0);

    field_120_obj_id = -1;
    field_124_fight_target_obj_id = -1;

    vOnTrapDoorOpen_4A7ED0();

    if (field_10C_health <= FP_FromInteger(0))
    {
        Path::TLV_Reset_4DB8E0(field_144_tlvInfo, -1, 0, 1);
    }
    else
    {
        Path::TLV_Reset_4DB8E0(field_144_tlvInfo, -1, 0, 0);
    }

    MusicController::sub_47FD60(0, this, 0, 0);

    if (sControlledCharacter_5C1B8C == this)
    {
        sControlledCharacter_5C1B8C = sActiveHero_5C1B68;
        if (gMap_5C3030.field_A_5C303A_levelId != LevelIds::eMenu_0)
        {
            gMap_5C3030.SetActiveCam_480D30(
                field_166_level,
                field_168_path,
                field_16A_camera,
                CameraSwapEffects::eEffect0_InstantChange,
                0,
                0);
        }
    }
    dtor_4080B0();
}

void Scrab::vOnTrapDoorOpen_4A7ED0()
{
    auto pPlatform = static_cast<PlatformBase*>(sObjectIds_5C1B70.Find_449CF0(field_110_id));
    if (pPlatform)
    {
        pPlatform->VRemove(this);
        field_1AA_flags.Set(Flags_1AA::eBit4);
        field_110_id = -1;
        field_106_current_motion = 15;
    }
}

void Scrab::vUpdateAnim_4A34F0()
{
    field_20_animation.Set_Animation_Data_409C80(
        sScrabFrameTableOffsets_5601C0[field_106_current_motion], 
        ResBlockForMotion_4A43E0(field_106_current_motion));
}

__int16 Scrab::OnFloor_4A41E0()
{
    FP hitX = {};
    FP hitY = {};
    if (sCollisions_DArray_5C1128->Raycast_417A60(
        field_B8_xpos,
        field_BC_ypos,
        field_B8_xpos,
        field_BC_ypos + FP_FromInteger(30),
        &field_100_pCollisionLine,
        &hitX,
        &hitY,
        field_D6_scale != 0 ? 1 : 16))
    {
        field_BC_ypos = hitY;
        ToStand_4A75A0();
        if (field_100_pCollisionLine->field_8_type == 32 || field_100_pCollisionLine->field_8_type == 36)
        {
            PlatformCollide_4A7E50();
        }
        return TRUE;

    }
    return FALSE;
}

const FP dword_546D84[8] = 
{
    FP_FromInteger(4),
    FP_FromInteger(4),
    FP_FromInteger(0),
    FP_FromInteger(-4),
    FP_FromInteger(-4),
    FP_FromInteger(-4),
    FP_FromInteger(0),
    FP_FromInteger(4)
};

const FP dword_546DA4[11] = 
{
    FP_FromInteger(0),
    FP_FromInteger(-4),
    FP_FromInteger(-4),
    FP_FromInteger(-4),
    FP_FromInteger(0),
    FP_FromInteger(4),
    FP_FromInteger(4),
    FP_FromInteger(4),
    FP_FromInteger(0),
    FP_FromInteger(0),
    FP_FromInteger(0)
};


void Scrab::vUpdate_4A3530()
{
    if (field_114_flags.Get(Flags_114::e114_Bit9))
    {
        field_114_flags.Clear(Flags_114::e114_Bit9);
        if (field_104_collision_line_type == -1)
        {
            field_100_pCollisionLine = nullptr;
        }
        else
        {
            sCollisions_DArray_5C1128->Raycast_417A60(
                field_B8_xpos,
                field_BC_ypos - FP_FromInteger(20),
                field_B8_xpos,
                field_BC_ypos + FP_FromInteger(20),
                &field_100_pCollisionLine,
                &field_B8_xpos,
                &field_BC_ypos,
                1 << field_104_collision_line_type);
        }
        field_104_collision_line_type = 0;
        field_120_obj_id = BaseGameObject::Find_Flags_4DC170(field_120_obj_id);
        field_124_fight_target_obj_id = BaseGameObject::Find_Flags_4DC170(field_124_fight_target_obj_id);
    }

    if (Event_Get_422C00(kEventDeathReset))
    {
        field_6_flags.Set(BaseGameObject::eDead);
        return;
    }

    const FP xDelta = FP_Abs(field_B8_xpos - sControlledCharacter_5C1B8C->field_B8_xpos);
    if (xDelta <= FP_FromInteger(750))
    {
        const FP yDelta = FP_Abs(field_BC_ypos - sControlledCharacter_5C1B8C->field_BC_ypos);
        if (yDelta <= FP_FromInteger(520))
        {
            if (field_10C_health > FP_FromInteger(0))
            {
                field_20_animation.field_4_flags.Set(AnimFlags::eBit2_Animate);
                field_20_animation.field_4_flags.Set(AnimFlags::eBit3_Render);
            }

            if (!Input_IsChanting_45F260())
            {
                field_164 = 0;
            }

            if (sDDCheat_FlyingEnabled_5C2C08 && sControlledCharacter_5C1B8C == this)
            {
                // Handle DDCheat mode

                // TODO: InputCommand constants
                field_100_pCollisionLine = nullptr;
                if (sInputObject_5BD4E0.field_0_pads[sCurrentControllerIndex_5C1BBE].field_0_pressed & 0xF)
                {
                    field_C4_velx = dword_546D84[sInputObject_5BD4E0.field_0_pads[sCurrentControllerIndex_5C1BBE].field_4_dir >> 5];
                    field_C8_vely = dword_546DA4[sInputObject_5BD4E0.field_0_pads[sCurrentControllerIndex_5C1BBE].field_4_dir >> 5];

                    if (sInputObject_5BD4E0.field_0_pads[sCurrentControllerIndex_5C1BBE].field_0_pressed & 0x10)
                    {
                        field_C4_velx += dword_546D84[sInputObject_5BD4E0.field_0_pads[sCurrentControllerIndex_5C1BBE].field_4_dir >> 5];
                        field_C4_velx += dword_546D84[sInputObject_5BD4E0.field_0_pads[sCurrentControllerIndex_5C1BBE].field_4_dir >> 5];
                        field_C8_vely += dword_546DA4[sInputObject_5BD4E0.field_0_pads[sCurrentControllerIndex_5C1BBE].field_4_dir >> 5];
                    }

                    field_B8_xpos += field_C4_velx;
                    field_BC_ypos += field_C8_vely;

                    // Keep in map bounds
                    PSX_Point point = {};
                    gMap_5C3030.Get_map_size_480640(&point);
                    if (field_B8_xpos < FP_FromInteger(0))
                    {
                        field_B8_xpos = FP_FromInteger(0);
                    }

                    if (field_B8_xpos >= FP_FromInteger(point.field_0_x))
                    {
                        field_B8_xpos = FP_FromInteger(point.field_0_x) - FP_FromInteger(1);
                    }

                    if (field_BC_ypos < FP_FromInteger(0))
                    {
                        field_BC_ypos = FP_FromInteger(0);
                    }

                    if (field_BC_ypos >= FP_FromInteger(point.field_2_y))
                    {
                        field_BC_ypos = FP_FromInteger(point.field_2_y) - FP_FromInteger(1);
                    }
                }
                else
                {
                    field_C4_velx = FP_FromInteger(0);
                    field_C8_vely = FP_FromInteger(0);
                }
                
                sub_408C40();
                field_F8_LastLineYPos = field_BC_ypos;
                return;
            }

            if (!gMap_5C3030.Is_Point_In_Current_Camera_4810D0(
                field_C2_lvl_number,
                field_C0_path_number,
                field_B8_xpos,
                field_BC_ypos,
                1))
            {
                field_1A2 = 0;
            }

            const auto oldMotion = field_106_current_motion;
            const auto oldBrain = field_118_brain_state;
            const auto oldBrainRet = field_11C_sub_state;

            field_11C_sub_state = (this->*field_118_brain_state)();

            if (sDDCheat_ShowAI_Info_5C1BD8)
            {
                DDCheat::DebugStr_4F5560(
                    "Scrab %d %d %d %d\n",
                    field_11C_sub_state,
                    field_12C,
                    field_106_current_motion,
                    field_108_next_motion);
            }

            field_19C = field_BC_ypos;
            field_198 = field_B8_xpos;

            (this->*sScrab_motion_table_560120[field_106_current_motion])();

            if (field_198 != field_B8_xpos || field_19C != field_BC_ypos)
            {
                field_FC_pPathTLV = sPath_dword_BB47C0->TLV_Get_At_4DB290(
                    nullptr,
                    field_B8_xpos,
                    field_BC_ypos,
                    field_B8_xpos,
                    field_BC_ypos);
                VOn_TLV_Collision_4087F0(field_FC_pPathTLV);
            }

            // TODO: This is extra debug logging to figure out the motion names
            if (oldBrain != field_118_brain_state)
            {
                LOG_INFO("Scrab: Old brain = " << GetOriginalFn(oldBrain, sScrabAITable).fnName << " new brain = " << GetOriginalFn(field_118_brain_state, sScrabAITable).fnName);
            }
            else
            {
                if (oldBrainRet != field_11C_sub_state)
                {
                    LOG_INFO("Scrab: Brain state = " << GetOriginalFn(field_118_brain_state, sScrabAITable).fnName << " State change from " << oldBrainRet << " to " << field_11C_sub_state);
                }
            }

            if (oldMotion != field_106_current_motion || field_1AA_flags.Get(Flags_1AA::eBit4))
            {
                field_1AA_flags.Clear(Flags_1AA::eBit4);
                vUpdateAnim_4A34F0();
            }
            else if (field_11E)
            {
                field_106_current_motion = field_F4;
                vUpdateAnim_4A34F0();
                field_20_animation.SetFrame_409D50(field_F6_anim_frame);
                field_11E = 0;
            }
            
            Update_Slurg_Step_Watch_Points_4A5780();
            
            if (field_178)
            {
                if (sControlledCharacter_5C1B8C != this)
                {
                    field_13C = field_BC_ypos;
                    return;
                }

                if (field_10C_health > FP_FromInteger(0) && !(static_cast<int>(sGnFrame_5C1B84) % 4))
                {
                    short v21 = Math_RandomRange_496AB0(40, 50);
                    const short v22 = Math_RandomRange_496AB0(45, 55);
                    FP v23 = (FP_FromInteger(-7) * field_CC_sprite_scale);
                    FP v24 = (FP_FromDouble(0.3) * field_CC_sprite_scale);
                    FP point2 = v24;

                    if (Math_NextRandom() & 1)
                    {
                        v23 = -v23;
                        v21 = -v21;
                    }

                    if (Math_NextRandom() & 1)
                    {
                        point2 = -v24;
                    }

                    const FP v26 = field_BC_ypos - (field_CC_sprite_scale * FP_FromInteger(v22));
                    const FP v27 = (field_CC_sprite_scale * FP_FromInteger(v21));

                    New_Particle_426AA0(
                        v27 + field_B8_xpos,
                        v26,
                        v23,
                        point2,
                        field_CC_sprite_scale,
                        0,
                        255,
                        0,
                        0);
                }
            }

            if (sControlledCharacter_5C1B8C == this && field_110_id != -1)
            {
                field_C8_vely = field_BC_ypos - field_13C;
                sub_408C40();
            }
            field_13C = field_BC_ypos;
            return;
        }
    }

    if (field_1AA_flags.Get(Flags_1AA::eBit6_persistant))
    {
        field_20_animation.field_4_flags.Clear(AnimFlags::eBit2_Animate);
        field_20_animation.field_4_flags.Clear(AnimFlags::eBit3_Render);
    }
    else
    {
        field_6_flags.Set(BaseGameObject::eDead);
    }
}

void Scrab::Update_Slurg_Step_Watch_Points_4A5780()
{
    if (field_106_current_motion == eScrabMotions::M_Walk_1_4A84D0 ||
        field_106_current_motion == eScrabMotions::M_Run_2_4A89C0 ||
        field_106_current_motion == eScrabMotions::M_Stamp_21_4A9CC0 ||
        field_106_current_motion == eScrabMotions::M_AttackSpin_32_4A8DC0)
    {
        if (sGnFrame_5C1B84 & 1)
        {
            const char count = sSlurg_Step_Watch_Points_Count_5BD4DC[sSlurg_Step_Watch_Points_Idx_5C1C08];
            if (count < 5)
            {
                Slurg_Step_Watch_Points* pPoints = &sSlurg_Step_Watch_Points_5C1B28[sSlurg_Step_Watch_Points_Idx_5C1C08];
                pPoints->field_0_points[count].field_0_xPos = FP_GetExponent(field_B8_xpos);
                pPoints->field_0_points[count].field_2_yPos = field_100_pCollisionLine->field_0_rect.y - 5;
                sSlurg_Step_Watch_Points_Count_5BD4DC[sSlurg_Step_Watch_Points_Idx_5C1C08] = count + 1;
            }
        }
    }

}

enum AI_Patrol
{
    eState0_ToMoving_0 = 0,
    eState0_Moving_1 = 1,
    eState0_Turning_2 = 2,
    eState0_Idle_3 = 3,
    eState0_Howling_4 = 4,
    eState0_Shriek_5 = 5,
    eState0_UNKNOWN_6 = 6,
    eState0_UNKNOWN_7 = 7,
    eState0_UNKNOWN_8 = 8,
    eState0_UsingInvisibility_9 = 9,
    eState0_PostInvisibilitySmash_10 = 10,
    eState0_BeingSpawned_11 = 11,
};

enum AI_ChasingEnemy
{
    eState1_Inactive_0 = 0,
    eState1_Idle_1 = 1,
    eState1_Running_2 = 2,
    eState1_Turning_3 = 3,
    eState1_Panic_4 = 4,
    eState1_Falling_5 = 5,
    eState1_UNKNOWN_6 = 6,
    eState1_Jumping_7 = 7,
    eState1_Attacking_8 = 8,
    eState1_Walking_9 = 9,
    eState1_EnemyDead_10 = 10,
    eState1_SmashingEnemy_11 = 11,
    eState1_Eating_12 = 12,
    eState1_UNKNOWN_13 = 13,
    eState1_Shriek_14 = 14,
    eState1_UNKNOWN_15 = 15,
    eState1_KilledPossessedScrab_16 = 16
};

enum AI_Fighting
{
    eState2_LookingForOpponent_0 = 0,
    eState2_SpottedOpponent_1 = 1,
    eState2_Turning_2 = 2,
    eState2_Walking_3 = 3,
    eState2_SetInPosition_4 = 4, 
    eState2_Idle_5 = 5,
    eState2_Yelling_6 = 6,
    eState2_Shriek_7 = 7,
    eState2_ToRun_8 = 8,
    eState2_Running_9 = 9,
    eState2_Battling_10 = 10,
    eState2_Victorious_11 = 11,
    eState2_SmashingOpponent_12 = 12, 
    eState2_VictoryYell_13 = 13,
    eState2_InterruptVictoryStates_14 = 14,
    eState2_WaitingForBattle_15 = 15
};

const int dword_546FD8[6] = { 256, 192, 128, 64, 0, 0 };

__int16 Scrab::AI_Patrol_0_4AA630()
{
    Scrab* pFighter = FindScrabToFight_4A4E20();
    if (pFighter)
    {
        SetBrain(&Scrab::AI_Fighting_2_4A5840);
        field_124_fight_target_obj_id = pFighter->field_8_object_id;
        field_108_next_motion = eScrabMotions::M_Stand_0_4A8220;
        return 0;
    }

    if (FindAbeOrMud_4A4FD0())
    {
        auto v5 = static_cast<BaseAliveGameObject*>(sObjectIds_5C1B70.Find_449CF0(field_120_obj_id));
        SetBrain(&Scrab::AI_ChasingEnemy_1_4A6470);
        if (v5->field_4_typeId == Types::eScrab_112 && v5->field_114_flags.Get(Flags_114::e114_Bit4_bPossesed))
        {
            field_108_next_motion = eScrabMotions::M_HowlBegin_26_4A9DA0;
            field_150 = sGnFrame_5C1B84 + 90;
            return 1;
        }

        field_108_next_motion = eScrabMotions::M_Stand_0_4A8220;
        return 0;
    }

    if (Event_Is_Event_In_Range_422C30(kEventAbeOhm, field_B8_xpos, field_BC_ypos, -1) &&
        !sActiveHero_5C1B68->field_114_flags.Get(Flags_114::e114_Bit8_bInvisible) && field_11C_sub_state != 26)
    {
        field_108_next_motion = eScrabMotions::M_HowlBegin_26_4A9DA0;
        return 4;
    }

    auto pSwitch = static_cast<PlatformBase*>(sObjectIds_5C1B70.Find_449CF0(field_110_id));
    if (pSwitch && pSwitch->field_4_typeId == Types::eLiftPoint_78 && !(static_cast<LiftPoint*>(pSwitch)->vOnAnyFloor_461920() && field_11C_sub_state != 6))
    {
        field_108_next_motion = eScrabMotions::M_Stand_0_4A8220;
        return 6;
    }

    if (gMap_5C3030.GetDirection_4811A0(field_C2_lvl_number, field_C0_path_number, field_B8_xpos, field_BC_ypos) >= CameraPos::eCamCurrent_0)
    {
        MusicController::sub_47FD60(4, this, 0, 0);
    }

    if (field_106_current_motion == eScrabMotions::M_JumpToFall_8_4A9220 && field_11C_sub_state != AI_Patrol::eState0_BeingSpawned_11)
    {
        field_11C_sub_state = AI_Patrol::eState0_BeingSpawned_11;
    }

    switch (field_11C_sub_state)
    {
    case AI_Patrol::eState0_ToMoving_0:
        if (!field_106_current_motion)
        {
            field_194 = LastSpeak_4A56F0();
            if (field_1A2 < field_1A0 && (field_194 == GameSpeakEvents::eUnknown_53 || field_194 == GameSpeakEvents::eUnknown_54))
            {
                return 8;
            }
        }

        if (Check_IsOnEndOfLine_408E90(
            field_20_animation.field_4_flags.Get(AnimFlags::eBit5_FlipX),
            field_106_current_motion != eScrabMotions::M_Run_2_4A89C0 ? 1 : 3) ||
            Handle_SlamDoor_or_EnemyStopper_4A4830(field_C4_velx, 1))
        {
            field_108_next_motion = eScrabMotions::M_Turn_3_4A91A0;
            return 2;
        }

        if (Math_NextRandom() >= dword_546FD8[field_12A_patrol_type])
        {
            field_108_next_motion = eScrabMotions::M_Run_2_4A89C0;
        }
        else
        {
            field_108_next_motion = eScrabMotions::M_Walk_1_4A84D0;
        }
        return 1;

    case AI_Patrol::eState0_Moving_1:
        field_194 = Scrab::LastSpeak_4A56F0();
        if (field_1A2 >= field_1A0 || field_194 != GameSpeakEvents::eUnknown_53 && field_194 != GameSpeakEvents::eUnknown_54)
        {
            if (Find_Fleech_4A4C90())
            {
                field_108_next_motion = eScrabMotions::M_LegKick_38_4AA120;
                return 7;
            }
            else
            {
                if (Check_IsOnEndOfLine_408E90(
                    field_20_animation.field_4_flags.Get(AnimFlags::eBit5_FlipX),
                    field_106_current_motion != eScrabMotions::M_Run_2_4A89C0 ? 1 : 3) || // TODO: check order is correct
                    Handle_SlamDoor_or_EnemyStopper_4A4830(field_C4_velx, 1))
                {
                    field_108_next_motion = eScrabMotions::M_Turn_3_4A91A0;
                    return 2;
                }
                else
                {
                    if (Math_NextRandom() >= 3u || static_cast<int>(sGnFrame_5C1B84 - field_154) <= 150)
                    {
                        return field_11C_sub_state;
                    }
                    field_108_next_motion = eScrabMotions::M_Shriek_30_4A9EA0;
                    field_154 = sGnFrame_5C1B84;
                    return 5;
                }
            }
        }
        else
        {
            field_108_next_motion = eScrabMotions::M_Stand_0_4A8220;
            return 8;
        }
        break;

    case AI_Patrol::eState0_Turning_2:
    {
        if (field_106_current_motion != eScrabMotions::M_Turn_3_4A91A0 || !field_20_animation.field_4_flags.Get(AnimFlags::eBit18_IsLastFrame))
        {
            return field_11C_sub_state;
        }

        field_108_next_motion = eScrabMotions::M_Stand_0_4A8220;

        short maxTimer = 0;
        short minTimer = 0;
        if (field_20_animation.field_4_flags.Get(AnimFlags::eBit5_FlipX))
        {
            maxTimer = field_15A_left_max_delay;
            minTimer = field_158_left_min_delay;
        }
        else
        {
            maxTimer = field_15E_right_max_delay;
            minTimer = field_15C;
        }
        field_12C = sGnFrame_5C1B84 + Math_RandomRange_496AB0(minTimer, maxTimer);
        return 3;
    }

    case AI_Patrol::eState0_Idle_3:
        field_194 = LastSpeak_4A56F0();
        if (field_1A2 >= field_1A0 || field_194 != GameSpeakEvents::eUnknown_53 && field_194 != GameSpeakEvents::eUnknown_54)
        {
            if (Find_Fleech_4A4C90())
            {
                field_108_next_motion = eScrabMotions::M_LegKick_38_4AA120;
                return 7;
            }
            else
            {
                if (static_cast<int>(sGnFrame_5C1B84) <= field_12C)
                {
                    return field_11C_sub_state;
                }

                if (Math_NextRandom() >= 30u || static_cast<int>(sGnFrame_5C1B84 - field_154) <= 150)
                {
                    return 0;
                }
                field_108_next_motion = eScrabMotions::M_HowlBegin_26_4A9DA0;
                field_154 = sGnFrame_5C1B84;
                return 4;
            }
        }
        else
        {
            field_108_next_motion = eScrabMotions::M_Stand_0_4A8220;
            return 8;
        }
        break;

    case AI_Patrol::eState0_Howling_4:
        if (Event_Is_Event_In_Range_422C30(kEventAbeOhm, field_B8_xpos, field_BC_ypos, -1))
        {
            return field_11C_sub_state;
        }
        if (field_106_current_motion == eScrabMotions::M_HowlBegin_26_4A9DA0 && field_20_animation.field_4_flags.Get(AnimFlags::eBit18_IsLastFrame))
        {
            field_108_next_motion = eScrabMotions::M_Stand_0_4A8220;
            return 0;
        }
        return field_11C_sub_state;

    case AI_Patrol::eState0_Shriek_5:
        if (field_106_current_motion == eScrabMotions::M_Shriek_30_4A9EA0 && field_20_animation.field_4_flags.Get(AnimFlags::eBit18_IsLastFrame))
        {
            field_108_next_motion = eScrabMotions::M_Stand_0_4A8220;
            return 0;
        }
        return field_11C_sub_state;

    case AI_Patrol::eState0_UNKNOWN_6:
        if (pSwitch)
        {
            // TODO: What is this 11 argument ??
            //if (!pSwitch->vsub_461920(11))
            if (!static_cast<LiftPoint*>(pSwitch)->vOnAnyFloor_461920())
            {
                return field_11C_sub_state;
            }
            return 0;
        }
        else
        {
            field_110_id = -1;
            return 0;
        }
        break;

    case AI_Patrol::eState0_UNKNOWN_7:
        if (field_106_current_motion == eScrabMotions::M_LegKick_38_4AA120 && field_20_animation.field_4_flags.Get(AnimFlags::eBit18_IsLastFrame))
        {
            field_108_next_motion = eScrabMotions::M_Stand_0_4A8220;
            return 0;
        }
        return field_11C_sub_state;


    case AI_Patrol::eState0_UNKNOWN_8:
        if (field_106_current_motion != eScrabMotions::M_Stand_0_4A8220)
        {
            return field_11C_sub_state;
        }

        field_1A2++;

        if (field_194 == GameSpeakEvents::eUnknown_54)
        {
            field_108_next_motion = 30;
            field_154 = sGnFrame_5C1B84;
            return 5;
        }
        else if (field_194 == GameSpeakEvents::eUnknown_53)
        {
            field_108_next_motion = eScrabMotions::M_HowlBegin_26_4A9DA0;
            return 4;
        }
        else
        {
            return field_11C_sub_state;
        }
        break;

    case AI_Patrol::eState0_UsingInvisibility_9:
        if (field_106_current_motion != eScrabMotions::M_HowlBegin_26_4A9DA0 || !(field_20_animation.field_4_flags.Get(AnimFlags::eBit18_IsLastFrame)))
        {
            return field_11C_sub_state;
        }
        field_108_next_motion = eScrabMotions::M_Stamp_21_4A9CC0;
        field_12C = sGnFrame_5C1B84 + 30;
        return AI_Patrol::eState0_PostInvisibilitySmash_10;

    case AI_Patrol::eState0_PostInvisibilitySmash_10:
        if (field_20_animation.field_4_flags.Get(AnimFlags::eBit18_IsLastFrame) && static_cast<int>(sGnFrame_5C1B84) > field_12C)
        {
            field_108_next_motion = eScrabMotions::M_Stand_0_4A8220;
            return 0;
        }
        return field_11C_sub_state;

    case AI_Patrol::eState0_BeingSpawned_11:
        if (field_106_current_motion != eScrabMotions::M_Stand_0_4A8220)
        {
            return field_11C_sub_state;
        }
        return AI_Patrol::eState0_ToMoving_0;

    default:
        return field_11C_sub_state;
    }
}

__int16 Scrab::AI_ChasingEnemy_1_4A6470()
{
    Scrab *pScrabToFight = FindScrabToFight_4A4E20();
    if (pScrabToFight)
    {
        SetBrain(&Scrab::AI_Fighting_2_4A5840);
        field_124_fight_target_obj_id = pScrabToFight->field_8_object_id;
        field_108_next_motion = eScrabMotions::M_Stand_0_4A8220;
        return AI_Fighting::eState2_LookingForOpponent_0;
    }
    auto pObj = static_cast<BaseAliveGameObject*>(sObjectIds_5C1B70.Find_449CF0(field_120_obj_id));
    if (!pObj || field_6_flags.Get(BaseGameObject::eDead) || static_cast<int>(sGnFrame_5C1B84) > field_14C && !CanSeeAbe_4A51A0(pObj))
    {
        field_120_obj_id = -1;
        field_108_next_motion = eScrabMotions::M_Stand_0_4A8220;
        ToPatrol_4AA600();
        return AI_Patrol::eState0_ToMoving_0;
    }
    if (pObj->field_114_flags.Get(Flags_114::e114_Bit8_bInvisible))
    {
        field_120_obj_id = -1;
        field_108_next_motion = eScrabMotions::M_HowlBegin_26_4A9DA0;
        ToPatrol_4AA600();
        return AI_Patrol::eState0_UsingInvisibility_9;
    }
    if (CanSeeAbe_4A51A0(pObj))
    {
        field_14C = sGnFrame_5C1B84 + field_148_attack_duration;
    }
    if (Event_Is_Event_In_Range_422C30(kEventAbeOhm, field_B8_xpos, field_BC_ypos, -1) && field_11C_sub_state != 26)
    {
        field_108_next_motion = eScrabMotions::M_HowlBegin_26_4A9DA0;
        return AI_ChasingEnemy::eState1_Panic_4;
    }
    LiftPoint* pLiftPoint = static_cast<LiftPoint*>(pObj);
    if (pLiftPoint && pLiftPoint->field_4_typeId == Types::eLiftPoint_78 && !pLiftPoint->vOnAnyFloor_461920() && field_11C_sub_state != 4)
    {
        field_108_next_motion = eScrabMotions::M_Stand_0_4A8220;
        return AI_ChasingEnemy::eState1_Panic_4;
    }
    if (gMap_5C3030.GetDirection_4811A0(
        field_C2_lvl_number,
        field_C0_path_number,
        field_B8_xpos,
        field_BC_ypos) >= CameraPos::eCamCurrent_0)
    {
        MusicController::sub_47FD60(8, this, 0, 0);
    }
    switch (field_11C_sub_state)
    {
    case AI_ChasingEnemy::eState1_Inactive_0:
        field_150 = sGnFrame_5C1B84 + field_128_attack_delay;
        return AI_ChasingEnemy::eState1_Idle_1;
    case AI_ChasingEnemy::eState1_Idle_1:
        if (!field_106_current_motion)
        {
            field_194 = LastSpeak_4A56F0();
            if (field_1A2 < field_1A0
                && LastSpeak_4A56F0() == GameSpeakEvents::eUnknown_53
                || LastSpeak_4A56F0() == GameSpeakEvents::eUnknown_54)
            {
                return AI_ChasingEnemy::eState1_UNKNOWN_15;
            }
        }
        if (!vIsFacingMe_4254A0(pObj))
        {
            if (gMap_5C3030.Is_Point_In_Current_Camera_4810D0(field_C2_lvl_number, field_C0_path_number, field_B8_xpos, field_BC_ypos, 0))
            {
                field_108_next_motion = eScrabMotions::M_Turn_3_4A91A0;
            }
            else
            {
                field_106_current_motion = eScrabMotions::M_Turn_3_4A91A0;
                field_108_next_motion = -1;
                MapFollowMe_408D10(TRUE);
            }
            return AI_ChasingEnemy::eState1_Turning_3;
        }
        if (vIsObjNearby_4253B0(ScaleToGridSize_4498B0(field_CC_sprite_scale) / FP_FromInteger(5), pObj)
            && vOnSameYLevel_425520(pObj))
        {
            if (!vIsObjNearby_4253B0(ScaleToGridSize_4498B0(field_CC_sprite_scale), pObj))
            {
                field_108_next_motion = eScrabMotions::M_AttackLunge_37_4AA0B0;
                return AI_ChasingEnemy::eState1_Attacking_8;
            }
            field_108_next_motion = eScrabMotions::M_LegKick_38_4AA120;
            return AI_ChasingEnemy::eState1_Attacking_8;
        }
        else if (CanSeeAbe_4A51A0(pObj) && static_cast<int>(sGnFrame_5C1B84) >= field_150)
        {
            if (Handle_SlamDoor_or_EnemyStopper_4A4830(field_C4_velx, 0))
            {
                return field_11C_sub_state;
            }
            field_108_next_motion = eScrabMotions::M_Run_2_4A89C0;
            return AI_ChasingEnemy::eState1_Running_2;
        }
        else
        {
            if (Math_NextRandom() >= 16u || static_cast<int>(sGnFrame_5C1B84 - field_154) <= 60)
            {
                return AI_ChasingEnemy::eState1_Idle_1;
            }
            field_108_next_motion = eScrabMotions::M_Shriek_30_4A9EA0;
            field_154 = sGnFrame_5C1B84;
            return AI_ChasingEnemy::eState1_Shriek_14;
        }
    case AI_ChasingEnemy::eState1_Running_2:
        return AI_ChasingEnemy_State_2(pObj);

    case AI_ChasingEnemy::eState1_Turning_3:
        if (field_106_current_motion == eScrabMotions::M_Turn_3_4A91A0)
        {
            if (!field_20_animation.field_4_flags.Get(AnimFlags::eBit18_IsLastFrame))
            {
                return field_11C_sub_state;
            }
            field_108_next_motion = eScrabMotions::M_Stand_0_4A8220;
            return AI_ChasingEnemy::eState1_Idle_1;
        }
        if (field_108_next_motion != eScrabMotions::M_Turn_3_4A91A0)
        {
            field_108_next_motion = eScrabMotions::M_Turn_3_4A91A0;
        }
        if (field_106_current_motion != eScrabMotions::M_Shriek_30_4A9EA0)
        {
            return field_11C_sub_state;
        }
        if (!field_20_animation.field_4_flags.Get(AnimFlags::eBit18_IsLastFrame))
        {
            return field_11C_sub_state;
        }
        field_108_next_motion = eScrabMotions::M_Stand_0_4A8220;
        return AI_ChasingEnemy::eState1_Idle_1;
    case AI_ChasingEnemy::eState1_Panic_4:
        if (vIsObjNearby_4253B0(ScaleToGridSize_4498B0(field_CC_sprite_scale), pObj)
            && vOnSameYLevel_425520(pObj))
        {
            field_108_next_motion = eScrabMotions::M_LegKick_38_4AA120;
            return AI_ChasingEnemy::eState1_Attacking_8;
        }
        if (pObj)
        {
            if (pLiftPoint->vOnAnyFloor_461920())
            {
                return field_11C_sub_state;
            }
            return AI_ChasingEnemy::eState1_Idle_1;
        }
        else
        {
            field_110_id = -1;
            return AI_ChasingEnemy::eState1_Idle_1;
        }
    case AI_ChasingEnemy::eState1_Falling_5:
    case AI_ChasingEnemy::eState1_UNKNOWN_6:
        if (field_106_current_motion)
        {
            return field_11C_sub_state;
        }
        return AI_ChasingEnemy::eState1_Idle_1;
    case AI_ChasingEnemy::eState1_Jumping_7:
        if (field_106_current_motion != eScrabMotions::M_RunJumpEnd_13_4A9BE0)
        {
            return field_11C_sub_state;
        }
        return AI_ChasingEnemy::eState1_Idle_1;
    case AI_ChasingEnemy::eState1_Attacking_8:
        if (field_106_current_motion != eScrabMotions::M_AttackLunge_37_4AA0B0
            && field_106_current_motion != eScrabMotions::M_LegKick_38_4AA120
            || !field_20_animation.field_4_flags.Get(AnimFlags::eBit18_IsLastFrame))
        {
            return field_11C_sub_state;
        }
        if (pObj->field_10C_health > FP_FromInteger(0))
        {
            return AI_ChasingEnemy::eState1_Idle_1;
            break;
        }
        if (vIsFacingMe_4254A0(pObj))
        {
            if (!vIsObjNearby_4253B0(ScaleToGridSize_4498B0(field_CC_sprite_scale), pObj))
            {
                if (!vIsObjNearby_4253B0(ScaleToGridSize_4498B0(field_CC_sprite_scale), pObj))
                {
                    field_108_next_motion = eScrabMotions::M_Walk_1_4A84D0;
                }
            }
            return AI_ChasingEnemy::eState1_Walking_9;
        }
        else
        {
            field_108_next_motion = eScrabMotions::M_Turn_3_4A91A0;
            return AI_ChasingEnemy::eState1_EnemyDead_10;
        }
    case AI_ChasingEnemy::eState1_Walking_9:
        if (!vIsObjNearby_4253B0(ScaleToGridSize_4498B0(field_CC_sprite_scale), pObj))
        {
            return field_11C_sub_state;
        }
        field_108_next_motion = eScrabMotions::M_Stamp_21_4A9CC0;
        field_12C = sGnFrame_5C1B84 + 30;
        return AI_ChasingEnemy::eState1_SmashingEnemy_11;
    case AI_ChasingEnemy::eState1_EnemyDead_10:
        if (field_106_current_motion != eScrabMotions::M_Turn_3_4A91A0 || !field_20_animation.field_4_flags.Get(AnimFlags::eBit18_IsLastFrame))
        {
            return field_11C_sub_state;
        }
        if (!vIsObjNearby_4253B0(ScaleToGridSize_4498B0(field_CC_sprite_scale), pObj))
        {
            field_108_next_motion = eScrabMotions::M_Walk_1_4A84D0;
        }
        return AI_ChasingEnemy::eState1_Walking_9;
    case AI_ChasingEnemy::eState1_SmashingEnemy_11:
        if (static_cast<int>(sGnFrame_5C1B84) <= field_12C)
        {
            return field_11C_sub_state;
        }
        if (pObj->field_BC_ypos - field_BC_ypos < FP_FromInteger(0))
        {
            pObj->field_BC_ypos - field_BC_ypos = -(pObj->field_BC_ypos - field_BC_ypos);
        }
        if (pObj->field_BC_ypos - field_BC_ypos >= FP_FromInteger(5))
        {
            field_108_next_motion = eScrabMotions::M_Shriek_30_4A9EA0;
            return AI_ChasingEnemy::eState1_Shriek_14;
        }
        else
        {
            field_108_next_motion = eScrabMotions::M_StandToFeed_35_4AA010;
            return AI_ChasingEnemy::eState1_Eating_12;
        }
    case AI_ChasingEnemy::eState1_Eating_12:
        if (field_106_current_motion == eScrabMotions::M_FeedToGulp_33_4A9FA0)
        {
            if (!field_20_animation.field_4_flags.Get(AnimFlags::eBit18_IsLastFrame))
            {
                field_108_next_motion = eScrabMotions::M_StandToFeed_35_4AA010;
            }
        }
        return field_11C_sub_state;
    case AI_ChasingEnemy::eState1_UNKNOWN_13:
        if (Event_Is_Event_In_Range_422C30(kEventAbeOhm, field_B8_xpos, field_BC_ypos, -1))
        {
            return field_11C_sub_state;
        }
        field_106_current_motion = eScrabMotions::M_HowlBegin_26_4A9DA0;
        if (field_106_current_motion != eScrabMotions::M_Shriek_30_4A9EA0)
        {
            return field_11C_sub_state;
        }
        if (!field_20_animation.field_4_flags.Get(AnimFlags::eBit18_IsLastFrame))
        {
            return field_11C_sub_state;
        }
        field_108_next_motion = eScrabMotions::M_Stand_0_4A8220;
        return AI_ChasingEnemy::eState1_Idle_1;
    case AI_ChasingEnemy::eState1_Shriek_14:
        if (field_106_current_motion != eScrabMotions::M_Shriek_30_4A9EA0)
        {
            return field_11C_sub_state;
        }
        if (!field_20_animation.field_4_flags.Get(AnimFlags::eBit18_IsLastFrame))
        {
            return field_11C_sub_state;
        }
        field_108_next_motion = eScrabMotions::M_Stand_0_4A8220;
        return AI_ChasingEnemy::eState1_Idle_1;
    case AI_ChasingEnemy::eState1_UNKNOWN_15:
        if (field_106_current_motion)
        {
            return field_11C_sub_state;
        }
        ++field_1A2;
        if (field_194 == GameSpeakEvents::eUnknown_54)
        {
            field_108_next_motion = eScrabMotions::M_Shriek_30_4A9EA0;
            field_154 = sGnFrame_5C1B84;
            return AI_ChasingEnemy::eState1_Shriek_14;
        }
        if (field_194 != GameSpeakEvents::eUnknown_53)
        {
            return field_11C_sub_state;
        }
        field_108_next_motion = eScrabMotions::M_HowlBegin_26_4A9DA0;
        return AI_ChasingEnemy::eState1_UNKNOWN_13;
    case AI_ChasingEnemy::eState1_KilledPossessedScrab_16:
        if (field_106_current_motion == eScrabMotions::M_JumpToFall_8_4A9220)
        {
            return AI_ChasingEnemy::eState1_Falling_5;
        }
        else if (field_106_current_motion == eScrabMotions::M_AttackSpin_32_4A8DC0)
        {
            return field_11C_sub_state;
        }
        else
        {
            return AI_ChasingEnemy::eState1_Idle_1;
        }
    default:
        return field_11C_sub_state;
    }
}

__int16 Scrab::AI_ChasingEnemy_State_2(BaseAliveGameObject* pObj)
{
    field_194 = LastSpeak_4A56F0();
    if (field_1A2 >= field_1A0
        || LastSpeak_4A56F0() != GameSpeakEvents::eUnknown_53
        && LastSpeak_4A56F0() != GameSpeakEvents::eUnknown_54)
    {
        if (Handle_SlamDoor_or_EnemyStopper_4A4830(field_C4_velx, 0))
        {
            field_108_next_motion = eScrabMotions::M_Stand_0_4A8220;
            return AI_ChasingEnemy::eState1_Idle_1;
        }
        int v20;
        if (FP_GetExponent(field_B8_xpos) - SnapToXGrid_449930(field_CC_sprite_scale, FP_GetExponent(field_B8_xpos)) >= 0)
        {
            v20 = FP_GetExponent(field_B8_xpos) - SnapToXGrid_449930(field_CC_sprite_scale, FP_GetExponent(field_B8_xpos));
        }
        else
        {
            v20 = SnapToXGrid_449930(field_CC_sprite_scale, FP_GetExponent(field_B8_xpos)) - FP_GetExponent(field_B8_xpos);
        }
        FP v23;
        if (v20 < 6
            && Check_IsOnEndOfLine_408E90(field_C4_velx < FP_FromInteger(0), 1)
            && ((pObj->field_BC_ypos - field_BC_ypos < FP_FromInteger(5))
                || ((field_C4_velx >= FP_FromInteger(0)) ? (v23 = ScaleToGridSize_4498B0(field_CC_sprite_scale)) : (v23 = -ScaleToGridSize_4498B0(field_CC_sprite_scale)),
                    sPath_dword_BB47C0->TLV_Get_At_4DB4B0(
                        FP_GetExponent(field_B8_xpos + v23),
                        FP_GetExponent(field_BC_ypos + FP_FromInteger(10)),
                        FP_GetExponent(field_B8_xpos + v23),
                        FP_GetExponent(field_BC_ypos + FP_FromInteger(10)),
                        TlvTypes::ElectricWall_38)))
            && !Check_IsOnEndOfLine_408E90(field_C4_velx < FP_FromInteger(0), 3))
        {
            ToJump_4A75E0();
            field_108_next_motion = -1;
            return AI_ChasingEnemy::eState1_Jumping_7;
        }
        else if (vIsFacingMe_4254A0(pObj))
        {
            if (!vIsObjNearby_4253B0(ScaleToGridSize_4498B0(field_CC_sprite_scale) / FP_FromInteger(7), pObj)
                || !pObj->field_114_flags.Get(Flags_114::e114_Bit8_bInvisible)
                || pObj->field_4_typeId != Types::eScrab_112)
            {
                if (vIsObjNearby_4253B0(ScaleToGridSize_4498B0(field_CC_sprite_scale) * FP_FromInteger(3), pObj)
                    && field_106_current_motion == eScrabMotions::M_Run_2_4A89C0
                    && vOnSameYLevel_425520(pObj))
                {
                    if (WallHit_408750(field_CC_sprite_scale * FP_FromInteger(45), pObj->field_B8_xpos - field_B8_xpos))
                    {
                        field_108_next_motion = eScrabMotions::M_Stand_0_4A8220;
                        return AI_ChasingEnemy::eState1_Idle_1;
                    }
                    else
                    {
                        field_108_next_motion = eScrabMotions::M_AttackLunge_37_4AA0B0;
                        return AI_ChasingEnemy::eState1_Attacking_8;
                    }
                }
                else
                {
                    if (field_106_current_motion != eScrabMotions::M_JumpToFall_8_4A9220)
                    {
                        return field_11C_sub_state;
                    }
                    return AI_ChasingEnemy::eState1_Falling_5;
                }
            }
            if (!field_178)
            {
                field_108_next_motion = eScrabMotions::M_HowlBegin_26_4A9DA0;
                return AI_ChasingEnemy::eState1_UNKNOWN_13;
            }
            if (!Math_NextRandom())
            {
                field_108_next_motion = eScrabMotions::M_AttackSpin_32_4A8DC0;
                return AI_ChasingEnemy::eState1_KilledPossessedScrab_16;
            }
            else
            {
                if (vIsObjNearby_4253B0(ScaleToGridSize_4498B0(field_CC_sprite_scale) * FP_FromInteger(3), pObj)
                    && field_106_current_motion == eScrabMotions::M_Run_2_4A89C0
                    && vOnSameYLevel_425520(pObj))
                {
                    if (WallHit_408750(field_CC_sprite_scale * FP_FromInteger(45), pObj->field_B8_xpos - field_B8_xpos))
                    {
                        field_108_next_motion = eScrabMotions::M_Stand_0_4A8220;
                        return AI_ChasingEnemy::eState1_Idle_1;
                    }
                    else
                    {
                        field_108_next_motion = eScrabMotions::M_AttackLunge_37_4AA0B0;
                        return AI_ChasingEnemy::eState1_Attacking_8;
                    }
                }
                else
                {
                    if (field_106_current_motion != eScrabMotions::M_JumpToFall_8_4A9220)
                    {
                        return field_11C_sub_state;
                    }
                    return AI_ChasingEnemy::eState1_Falling_5;
                }
            }
        }
        else
        {
            if (gMap_5C3030.Is_Point_In_Current_Camera_4810D0(field_C2_lvl_number, field_C0_path_number, field_B8_xpos, field_BC_ypos, 0))
            {
                field_108_next_motion = eScrabMotions::M_Turn_3_4A91A0;
            }
            else
            {
                field_106_current_motion = eScrabMotions::M_Turn_3_4A91A0;
                field_108_next_motion = -1;
                MapFollowMe_408D10(TRUE);
            }
            return AI_ChasingEnemy::eState1_Turning_3;
        }
    }
    else
    {
        field_108_next_motion = eScrabMotions::M_Stand_0_4A8220;
        return AI_ChasingEnemy::eState1_UNKNOWN_15;
    }
}

__int16 Scrab::AI_Fighting_2_4A5840()
{
    auto pTarget = static_cast<Scrab*>(sObjectIds_5C1B70.Find_449CF0(field_124_fight_target_obj_id));
    if (field_11C_sub_state != 10 &&
        field_11C_sub_state != 11 &&
        field_11C_sub_state != 12 &&
        field_11C_sub_state != 13 &&
        (!pTarget||
         pTarget->field_6_flags.Get(BaseGameObject::eDead) ||
         (WallHit_408750(field_CC_sprite_scale * FP_FromInteger(45), pTarget->field_B8_xpos - field_B8_xpos)) ||
         !vOnSameYLevel_425520(pTarget)))
    {
        field_108_next_motion = eScrabMotions::M_Stand_0_4A8220;
        ToPatrol_4AA600();
        return AI_Patrol::eState0_ToMoving_0;
    }

    if (pTarget && pTarget->field_114_flags.Get(Flags_114::e114_Bit4_bPossesed) &&
        field_10C_health > FP_FromInteger(0) &&
        pTarget->field_10C_health > FP_FromInteger(0))
    {
        field_120_obj_id = field_124_fight_target_obj_id;
        field_124_fight_target_obj_id = -1;
        SetBrain(&Scrab::AI_ChasingEnemy_1_4A6470);
        field_150 = sGnFrame_5C1B84 + 90;
        field_108_next_motion = eScrabMotions::M_HowlBegin_26_4A9DA0;
        return 1;
    }

    if (Event_Get_422C00(kEventAbeOhm))
    {
        if (field_11C_sub_state != 9 && field_11C_sub_state != 10)
        {
            if (field_11C_sub_state != 11 && field_11C_sub_state != 12 && field_11C_sub_state != 13)
            {
                field_108_next_motion = eScrabMotions::M_HowlBegin_26_4A9DA0;
                ToPatrol_4AA600();
                return AI_Patrol::eState0_Howling_4;
            }

            if (pTarget->field_11C_sub_state != 9 && field_108_next_motion == -1)
            {
                field_11C_sub_state = 14;
                field_108_next_motion = eScrabMotions::M_HowlBegin_26_4A9DA0;
            }
        }
    }

    if (gMap_5C3030.GetDirection_4811A0(field_C2_lvl_number, field_C0_path_number, field_B8_xpos, field_BC_ypos) >= CameraPos::eCamCurrent_0)
    {
        MusicController::sub_47FD60(8, this, 0, 0);
    }

    switch (field_11C_sub_state)
    {
    case AI_Fighting::eState2_LookingForOpponent_0:
        if (field_106_current_motion)
        {
            if (field_108_next_motion != eScrabMotions::M_Stand_0_4A8220)
            {
                field_108_next_motion = eScrabMotions::M_Stand_0_4A8220;
            }
            return AI_Fighting::eState2_LookingForOpponent_0;
        }
        else
        {
            field_1AA_flags.Clear(Flags_1AA::eBit1);
            field_108_next_motion = -1;
            if (pTarget->field_124_fight_target_obj_id == -1 || pTarget->field_124_fight_target_obj_id == field_8_object_id)
            {
                if (vIsFacingMe_4254A0(pTarget))
                {
                    if (!vIsObjNearby_4253B0(ScaleToGridSize_4498B0(field_CC_sprite_scale) * FP_FromInteger(8), pTarget))
                    {
                        if (pTarget->field_106_current_motion == eScrabMotions::M_HowlBegin_26_4A9DA0)
                        {
                            return field_11C_sub_state;
                        }
                        field_108_next_motion = eScrabMotions::M_HowlBegin_26_4A9DA0;
                        return AI_Fighting::eState2_Yelling_6;
                    }
                    field_108_next_motion = eScrabMotions::M_Turn_3_4A91A0;
                    return AI_Fighting::eState2_Turning_2;
                }
                else
                {
                    field_108_next_motion = eScrabMotions::M_Turn_3_4A91A0;
                    return AI_Fighting::eState2_SpottedOpponent_1;
                }
            }
            else
            {
                field_124_fight_target_obj_id = -1;
                field_108_next_motion = eScrabMotions::M_HowlBegin_26_4A9DA0;
                return AI_Fighting::eState2_WaitingForBattle_15;
            }
        }
        break;

    case AI_Fighting::eState2_SpottedOpponent_1:
        if (field_106_current_motion != eScrabMotions::M_Turn_3_4A91A0 || !field_20_animation.field_4_flags.Get(AnimFlags::eBit18_IsLastFrame))
        {
            return field_11C_sub_state;
        }

        if (vIsObjNearby_4253B0(ScaleToGridSize_4498B0(field_CC_sprite_scale) * FP_FromInteger(8), pTarget))
        {
            field_108_next_motion = eScrabMotions::M_Turn_3_4A91A0;
            return AI_Fighting::eState2_Turning_2;
        }
        else
        {
            field_108_next_motion = eScrabMotions::M_HowlBegin_26_4A9DA0;
            return AI_Fighting::eState2_Yelling_6;
        }
        break;

    case AI_Fighting::eState2_Turning_2:
        if (field_106_current_motion != eScrabMotions::M_Turn_3_4A91A0 || !field_20_animation.field_4_flags.Get(AnimFlags::eBit18_IsLastFrame))
        {
            return field_11C_sub_state;
        }
        field_108_next_motion = eScrabMotions::M_Walk_1_4A84D0;
        return AI_Fighting::eState2_Walking_3;

    case AI_Fighting::eState2_Walking_3:
        if (field_20_animation.field_4_flags.Get(AnimFlags::eBit5_FlipX))
        {
            if (Handle_SlamDoor_or_EnemyStopper_4A4830(field_C4_velx, 0) && 
                Check_IsOnEndOfLine_408E90(1, 2) &&
                !vIsObjNearby_4253B0(ScaleToGridSize_4498B0(field_CC_sprite_scale) * FP_FromInteger(10), pTarget))
            {
                if (gMap_5C3030.Is_Point_In_Current_Camera_4810D0(field_C2_lvl_number, field_C0_path_number, field_B8_xpos - FP_FromInteger(50), field_BC_ypos, 0))
                {
                    return field_11C_sub_state;
                }
            }
        }
        else
        {
            if (Handle_SlamDoor_or_EnemyStopper_4A4830(field_C4_velx, 0) &&
                Check_IsOnEndOfLine_408E90(0, 2) &&
                !vIsObjNearby_4253B0(ScaleToGridSize_4498B0(field_CC_sprite_scale) * FP_FromInteger(10), pTarget))
            {
                if (gMap_5C3030.Is_Point_In_Current_Camera_4810D0(field_C2_lvl_number, field_C0_path_number, field_B8_xpos + FP_FromInteger(50), field_BC_ypos, 0))
                {
                    return field_11C_sub_state;
                }
            }
        }
        field_108_next_motion = eScrabMotions::M_Turn_3_4A91A0;
        return AI_Fighting::eState2_SetInPosition_4;

    case AI_Fighting::eState2_SetInPosition_4:
        if (field_106_current_motion != eScrabMotions::M_Turn_3_4A91A0)
        {
            return field_11C_sub_state;
        }
        if (!field_20_animation.field_4_flags.Get(AnimFlags::eBit18_IsLastFrame))
        {
            return field_11C_sub_state;
        }
        field_108_next_motion = eScrabMotions::M_HowlBegin_26_4A9DA0;
        return AI_Fighting::eState2_Yelling_6;

    case AI_Fighting::eState2_Idle_5:
        if (static_cast<int>(sGnFrame_5C1B84) <= field_12C)
        {
            return field_11C_sub_state;
        }
        field_108_next_motion = eScrabMotions::M_Shriek_30_4A9EA0;
        return AI_Fighting::eState2_Shriek_7;

    case AI_Fighting::eState2_Yelling_6:
        if (field_106_current_motion != eScrabMotions::M_HowlBegin_26_4A9DA0 || !field_20_animation.field_4_flags.Get(AnimFlags::eBit18_IsLastFrame))
        {
            return field_11C_sub_state;
        }
        field_108_next_motion = eScrabMotions::M_Stand_0_4A8220;
        field_12C = sGnFrame_5C1B84 + 20;
        return AI_Fighting::eState2_Idle_5;

    case AI_Fighting::eState2_Shriek_7:
        if (field_106_current_motion != eScrabMotions::M_Shriek_30_4A9EA0 || !field_20_animation.field_4_flags.Get(AnimFlags::eBit18_IsLastFrame))
        {
            return field_11C_sub_state;
        }
        field_1AA_flags.Set(Flags_1AA::eBit1);
        field_108_next_motion = eScrabMotions::M_Stand_0_4A8220;
        return AI_Fighting::eState2_ToRun_8;

    case AI_Fighting::eState2_ToRun_8:
        if (!pTarget->field_1AA_flags.Get(Flags_1AA::eBit1))
        {
            return field_11C_sub_state;
        }
        field_108_next_motion = eScrabMotions::M_Run_2_4A89C0;
        return AI_Fighting::eState2_Running_9;

    case AI_Fighting::eState2_Running_9:
        if (!vIsObjNearby_4253B0(ScaleToGridSize_4498B0(field_CC_sprite_scale), pTarget) || !field_100_pCollisionLine || !pTarget->field_100_pCollisionLine)
        {
            return field_11C_sub_state;
        }

        if (pTarget->field_20_animation.field_4_flags.Get(AnimFlags::eBit3_Render))
        {
            field_20_animation.field_4_flags.Clear(AnimFlags::eBit3_Render);
            field_10C_health = FP_FromInteger(0);
        }

        MapFollowMe_408D10(TRUE);
        field_106_current_motion = 31;
        field_12C = sGnFrame_5C1B84 + 40;
        return AI_Fighting::eState2_Battling_10;

    case AI_Fighting::eState2_Battling_10:
        if (static_cast<int>(sGnFrame_5C1B84) <= field_12C)
        {
            return field_11C_sub_state;
        }

        SND_Stop_Channels_Mask_4CA810(field_160);
        field_160 = 0;
        Sound_4AADB0(ScrabSound::Unknown_1, 0, -1571, 1);
        Sound_4AADB0(ScrabSound::Unknown_8, 0, -1571, 1);
        Abe_SFX_2_457A40(6, 0, -383, 0);

        if (!field_20_animation.field_4_flags.Get(AnimFlags::eBit3_Render))
        {
            SetBrain(&Scrab::AI_Death_3_4A62B0);
            field_B8_xpos = pTarget->field_B8_xpos;
            field_106_current_motion = eScrabMotions::M_DeathBegin_39_4AA190;
            field_20_animation.field_4_flags.Set(AnimFlags::eBit3_Render);
            field_12C = sGnFrame_5C1B84 + 90;
            return field_11C_sub_state;
        }
        field_106_current_motion = eScrabMotions::M_Stand_0_4A8220;
        field_12C = sGnFrame_5C1B84 + 5;
        return AI_Fighting::eState2_Victorious_11;

    case AI_Fighting::eState2_Victorious_11:
        if (static_cast<int>(sGnFrame_5C1B84) <= field_12C)
        {
            return field_11C_sub_state;
        }
        field_12C = 5;
        field_108_next_motion = eScrabMotions::M_Stamp_21_4A9CC0;
        return AI_Fighting::eState2_SmashingOpponent_12;

    case AI_Fighting::eState2_SmashingOpponent_12:
        if (field_106_current_motion != eScrabMotions::M_Stamp_21_4A9CC0)
        {
            return field_11C_sub_state;
        }

        if (!field_20_animation.field_4_flags.Get(AnimFlags::eBit18_IsLastFrame))
        {
            return field_11C_sub_state;
        }

        field_12C--;
        if (field_12C > 0)
        {
            return field_11C_sub_state;
        }
        field_108_next_motion = eScrabMotions::M_HowlBegin_26_4A9DA0;
        return AI_Fighting::eState2_VictoryYell_13;

    case AI_Fighting::eState2_VictoryYell_13:
        if (field_106_current_motion != eScrabMotions::M_HowlBegin_26_4A9DA0 || !field_20_animation.field_4_flags.Get(AnimFlags::eBit18_IsLastFrame))
        {
            return field_11C_sub_state;
        }
        field_124_fight_target_obj_id = -1;
        field_108_next_motion = eScrabMotions::M_Stand_0_4A8220;
        ToPatrol_4AA600();
        return AI_Patrol::eState0_ToMoving_0;

    case AI_Fighting::eState2_InterruptVictoryStates_14:
        if (Event_Get_422C00(kEventAbeOhm))
        {
            return field_11C_sub_state;
        }
        field_108_next_motion = eScrabMotions::M_Stand_0_4A8220;
        return AI_Fighting::eState2_LookingForOpponent_0;

    case AI_Fighting::eState2_WaitingForBattle_15:
    {
        if (field_106_current_motion != eScrabMotions::M_HowlBegin_26_4A9DA0)
        {
            return field_11C_sub_state;
        }
        if (!field_20_animation.field_4_flags.Get(AnimFlags::eBit18_IsLastFrame))
        {
            return field_11C_sub_state;
        }

        auto pFoundTarget = FindScrabToFight_4A4E20();
        if (!pFoundTarget)
        {
            return field_11C_sub_state;
        }
        field_108_next_motion = eScrabMotions::M_Stand_0_4A8220;
        field_124_fight_target_obj_id = pFoundTarget->field_8_object_id;
        return AI_Fighting::eState2_LookingForOpponent_0;
    }

    default:
        return field_11C_sub_state;
    }
}

__int16 Scrab::AI_Death_3_4A62B0()
{
    if (field_12C < static_cast<int>((sGnFrame_5C1B84 + 80)))
    {
        field_CC_sprite_scale -= FP_FromDouble(0.008);
        field_D0_r -= 2;
        field_D2_g -= 2;
        field_D4_b -= 2;
    }

    if (static_cast<int>(sGnFrame_5C1B84) < field_12C - 24 && !(sGnFrame_5C1B84 % 5))
    {
        New_Particles_426C70(
            (FP_FromInteger(Math_RandomRange_496AB0(-24, 24)) * field_CC_sprite_scale) + field_B8_xpos, 
            field_BC_ypos - FP_FromInteger(6), 
            field_CC_sprite_scale / FP_FromInteger(2), 
            2, 
            128u, 128u, 128u);
        SFX_Play_46FBA0(79u, 25, FP_GetExponent(FP_FromInteger(2200) * field_CC_sprite_scale));
    }

    if (field_12C < static_cast<int>(sGnFrame_5C1B84))
    {
        field_6_flags.Set(BaseGameObject::eDead);
    }

    return 0;
}

__int16 Scrab::AI_ShrinkDeath_4_4A6420()
{
    if (field_D6_scale == 1)
    {
        field_CC_sprite_scale -= FP_FromDouble(0.06);
    }
    else
    {
        field_CC_sprite_scale -= FP_FromDouble(0.03);
    }

    if (field_12C < static_cast<int>(sGnFrame_5C1B84))
    {
        field_6_flags.Set(BaseGameObject::eDead);
    }

    return 0;
}

__int16 Scrab::AI_Possessed_5_4A6180()
{
    // Abe is dead, go back to patrolling
    if (sActiveHero_5C1B68->field_10C_health <= FP_FromInteger(0))
    {
        sControlledCharacter_5C1B8C = sActiveHero_5C1B68;
        field_114_flags.Clear(Flags_114::e114_Bit4_bPossesed);
        field_1A2 = 0;
        MusicController::sub_47FD60(0, this, 0, 0);
        ToPatrol_4AA600();
        field_11C_sub_state = 0;
        gMap_5C3030.SetActiveCam_480D30(field_166_level, field_168_path, field_16A_camera, CameraSwapEffects::eEffect0_InstantChange, 0, 0);
        return field_11C_sub_state;
    }

    if (field_11C_sub_state == 0)
    {
        if (static_cast<int>(sGnFrame_5C1B84) <= field_12C)
        {
            return field_11C_sub_state;
        }
        field_108_next_motion = eScrabMotions::M_Stand_0_4A8220;
        return 1;
    }
    else
    {
        if (field_11C_sub_state != 1 || gMap_5C3030.GetDirection_4811A0(field_C2_lvl_number, field_C0_path_number, field_B8_xpos, field_BC_ypos) == CameraPos::eCamInvalid_m1)
        {
            return field_11C_sub_state;
        }
        MusicController::sub_47FD60(9, this, 0, 0);
        return field_11C_sub_state;
    }
}

void Scrab::M_Stand_0_4A8220()
{
    if (BrainIs(&Scrab::AI_Possessed_5_4A6180))
    {
        if (field_11C_sub_state != 1)
        {
            return;
        }

        if (Input_IsChanting_45F260() && !field_164)
        {
            field_130 = sGnFrame_5C1B84 + 30;
            SFX_Play_46FA90(17, 0);
            field_106_current_motion = eScrabMotions::M_GetDepossessedBegin_28_4AA200;
            return;
        }

        if (sInputObject_5BD4E0.isHeld(sInputKey_GameSpeak2_5550F8))
        {
            field_106_current_motion = eScrabMotions::M_Shriek_30_4A9EA0;
            field_108_next_motion = eScrabMotions::M_Stand_0_4A8220;
            return;
        }

        if (sInputObject_5BD4E0.isHeld(sInputKey_GameSpeak1_555104))
        {
            field_106_current_motion = eScrabMotions::M_HowlBegin_26_4A9DA0;
            field_108_next_motion = eScrabMotions::M_Stand_0_4A8220;
            return;
        }

        if (sInputObject_5BD4E0.isPressed(InputCommands::eThrowItem | InputCommands::eDoAction) && field_178)
        {
            field_106_current_motion = eScrabMotions::M_AttackSpin_32_4A8DC0;
            field_108_next_motion = -1;
            field_12C = sGnFrame_5C1B84 + field_174_whirl_attack_duration;
            return;
        }

        if (sInputObject_5BD4E0.isPressed(InputCommands::eThrowItem | InputCommands::eDoAction))
        {
            field_106_current_motion = eScrabMotions::M_Stamp_21_4A9CC0;
            field_108_next_motion = -1;
            return;
        }

        if (sInputObject_5BD4E0.isPressed(sInputKey_Hop_5550E0))
        {
            const FP k45Scaled = (field_CC_sprite_scale * FP_FromInteger(45));
            const FP kGridSize = ScaleToGridSize_4498B0(field_CC_sprite_scale);

            if (field_20_animation.field_4_flags.Get(AnimFlags::eBit5_FlipX))
            {
                if (!WallHit_408750(k45Scaled, -kGridSize))
                {
                    field_106_current_motion = eScrabMotions::M_HopBegin_5_4A96C0;
                    field_108_next_motion = -1;
                    return;
                }
            }
            else
            {
                if (!WallHit_408750(k45Scaled, kGridSize))
                {
                    field_106_current_motion = eScrabMotions::M_HopBegin_5_4A96C0;
                    field_108_next_motion = -1;
                    return;
                }
            }
        }
    }
    ToNextMotion_4A7920();
}

const int sScrabWalkXVels_546E54[22] =
{
    102930,
    103419,
    99987,
    102573,
    104637,
    242098,
    259357,
    260279,
    216749,
    172338,
    142077,
    132519,
    118230,
    105285,
    173137,
    176018,
    175184,
    176362,
    91533,
    90242,
    90225,
    141864
};

void Scrab::M_Walk_1_4A84D0()
{
    field_C4_velx = field_CC_sprite_scale * FP_FromRaw(sScrabWalkXVels_546E54[field_20_animation.field_92_current_frame]);

    if (field_20_animation.field_4_flags.Get(AnimFlags::eBit5_FlipX))
    {
        field_C4_velx = -field_C4_velx;
    }
    
    MoveOnLine_4A7D20();
    
    if (field_106_current_motion != 1)
    {
        return;
    }

    FP kGridSize = {};
    if (field_20_animation.field_4_flags.Get(AnimFlags::eBit5_FlipX))
    {
        kGridSize = -ScaleToGridSize_4498B0(field_CC_sprite_scale);
    }
    else
    {
        kGridSize = ScaleToGridSize_4498B0(field_CC_sprite_scale);
    }

    if (WallHit_408750(field_CC_sprite_scale * FP_FromInteger(45), kGridSize * FP_FromDouble(0.5)))
    {
        KnockBack_4AA530();
        return;
    }

    switch (field_20_animation.field_92_current_frame)
    {
    case 3:
    case 13:
        Sound_4AADB0(ScrabSound::Unknown_6, Math_RandomRange_496AB0(40, 50), 0x7FFF, 1);
        return;

    case 5:
    case 15:
        if (WallHit_408750(field_CC_sprite_scale * FP_FromInteger(45), kGridSize * FP_FromInteger(1)))
        {
            field_106_current_motion = 11;
        }
        else if (sControlledCharacter_5C1B8C != this || field_10C_health <= FP_FromInteger(0))
        {
            if (field_108_next_motion == eScrabMotions::M_Stand_0_4A8220 ||
                field_108_next_motion == eScrabMotions::M_Turn_3_4A91A0 ||
                field_108_next_motion == eScrabMotions::M_Stamp_21_4A9CC0 ||
                field_108_next_motion == eScrabMotions::M_Empty_25_4A34D0 ||
                field_108_next_motion == eScrabMotions::M_Shriek_30_4A9EA0 ||
                field_108_next_motion == eScrabMotions::M_HowlBegin_26_4A9DA0 ||
                field_108_next_motion == eScrabMotions::M_HopMidair_6_4A9490 ||
                field_108_next_motion == eScrabMotions::M_AttackLunge_37_4AA0B0 ||
                field_108_next_motion == eScrabMotions::M_LegKick_38_4AA120)
            {
                field_106_current_motion = eScrabMotions::M_WalkToStand_11_4A8880;
            }
        }
        else
        {
            if ((field_C4_velx > FP_FromInteger(0) && sInputObject_5BD4E0.isPressed(InputCommands::eLeft)) ||
                (field_C4_velx < FP_FromInteger(0) && sInputObject_5BD4E0.isPressed(InputCommands::eRight)) ||
                !sInputObject_5BD4E0.isPressed(InputCommands::eRight | InputCommands::eLeft))
            {
                field_106_current_motion = eScrabMotions::M_WalkToStand_11_4A8880;
            }
        }
        return;

    case 7:
    case 18:
        Sound_4AADB0(ScrabSound::Unknown_6, Math_RandomRange_496AB0(40, 50), 0x7FFF, 1);
        if (sControlledCharacter_5C1B8C != this || field_10C_health <= FP_FromInteger(0))
        {
            if (field_108_next_motion != eScrabMotions::M_Run_2_4A89C0)
            {
                MapFollowMe_408D10(TRUE);
                return;
            }
            field_106_current_motion = eScrabMotions::M_WalkToRun_16_4A8D60;
            field_108_next_motion = -1;
            MapFollowMe_408D10(TRUE);
            return;
        }

        if (sInputObject_5BD4E0.isPressed(InputCommands::eThrowItem | InputCommands::eDoAction) && field_178)
        {
            field_106_current_motion = eScrabMotions::M_AttackSpin_32_4A8DC0;
            field_12C = sGnFrame_5C1B84 + field_174_whirl_attack_duration;
            field_108_next_motion = -1;
            MapFollowMe_408D10(TRUE);
            return;
        }

        if (sInputObject_5BD4E0.isPressed(InputCommands::eRun))
        {
            field_106_current_motion = eScrabMotions::M_WalkToRun_16_4A8D60;
            field_108_next_motion = -1;
            MapFollowMe_408D10(TRUE);
            return;
        }

        if (sInputObject_5BD4E0.isPressed(InputCommands::eHop))
        {
            field_106_current_motion = eScrabMotions::M_HopBegin_5_4A96C0;
            field_108_next_motion = -1;
            MapFollowMe_408D10(TRUE);
            return;
        }

        MapFollowMe_408D10(TRUE);
        return;

    default:
        return;
    }
}

const int sScrabRunVelX_546EC4[14] =
{
    622509,
    637911,
    628107,
    599066,
    596319,
    627575,
    611255,
    567207,
    346759,
    280505,
    225862,
    222655,
    249941,
    337964
};

void Scrab::M_Run_2_4A89C0()
{
    auto pTarget = static_cast<BaseAliveGameObject*>(sObjectIds_5C1B70.Find_449CF0(field_120_obj_id));
    field_C4_velx = field_CC_sprite_scale * FP_FromRaw(sScrabRunVelX_546EC4[field_20_animation.field_92_current_frame]);

    if (field_20_animation.field_4_flags.Get(AnimFlags::eBit5_FlipX))
    {
        field_C4_velx = -field_C4_velx;
    }

    FP gridSize = {};
    if (field_20_animation.field_4_flags.Get(AnimFlags::eBit5_FlipX))
    {
        gridSize = -ScaleToGridSize_4498B0(field_CC_sprite_scale);
    }
    else
    {
        gridSize = ScaleToGridSize_4498B0(field_CC_sprite_scale);
    }

    if (WallHit_408750(field_CC_sprite_scale * FP_FromInteger(45), gridSize * FP_FromDouble(0.5)))
    {
        KnockBack_4AA530();
        return;
    }
    
    MoveOnLine_4A7D20();

    if (field_106_current_motion == eScrabMotions::M_Run_2_4A89C0)
    {
        KillTarget_4A7F20(pTarget);
        switch (field_20_animation.field_92_current_frame)
        {
        case 0:
        case 5:
        case 7:
        case 12:
            Sound_4AADB0(ScrabSound::Unknown_6, Math_RandomRange_496AB0(40, 50), 0x7FFF, 1);
            return;

        case 3:
        case 10:
            if (sControlledCharacter_5C1B8C != this || field_10C_health <= FP_FromInteger(0))
            {
                if (field_108_next_motion == eScrabMotions::M_Walk_1_4A84D0)
                {
                    field_106_current_motion = eScrabMotions::M_RunToWalk_17_4A8D90;
                    field_108_next_motion = -1;
                    MapFollowMe_408D10(TRUE);
                    return;
                }

                if (field_108_next_motion != eScrabMotions::M_Stand_0_4A8220 &&
                    field_108_next_motion != eScrabMotions::M_Turn_3_4A91A0 &&
                    field_108_next_motion != eScrabMotions::M_HopMidair_6_4A9490 &&
                    field_108_next_motion != eScrabMotions::M_AttackLunge_37_4AA0B0 &&
                    field_108_next_motion != eScrabMotions::M_Empty_25_4A34D0 &&
                    field_108_next_motion != eScrabMotions::M_HowlBegin_26_4A9DA0 &&
                    field_108_next_motion != eScrabMotions::M_LegKick_38_4AA120 &&
                    field_108_next_motion != eScrabMotions::M_Shriek_30_4A9EA0)
                {
                    if (field_108_next_motion == eScrabMotions::M_AttackSpin_32_4A8DC0)
                    {
                        field_106_current_motion = eScrabMotions::M_AttackSpin_32_4A8DC0;
                        MapFollowMe_408D10(TRUE);
                        return;
                    }

                    if (field_108_next_motion == eScrabMotions::M_ScrabBattleAnim_31_4A9F30)
                    {
                        ToStand_4A75A0();
                        field_106_current_motion = eScrabMotions::M_ScrabBattleAnim_31_4A9F30;
                        field_108_next_motion = -1;
                        MapFollowMe_408D10(TRUE);
                        return;
                    }

                    MapFollowMe_408D10(TRUE);
                    return;
                }
            }
            else
            {
                if ((field_C4_velx <= FP_FromInteger(0) || !sInputObject_5BD4E0.isPressed(sInputKey_Left_5550D4)) &&
                    (field_C4_velx >= FP_FromInteger(0) || !sInputObject_5BD4E0.isPressed(sInputKey_Right_5550D0)))
                {
                    if (sInputObject_5BD4E0.isPressed(sInputKey_Left_5550D4 | sInputKey_Right_5550D0))
                    {
                        if (!sInputObject_5BD4E0.isPressed(sInputKey_Run_5550E8))
                        {
                            field_106_current_motion = eScrabMotions::M_RunToWalk_17_4A8D90;
                            MapFollowMe_408D10(TRUE);
                            return;
                        }

                        if (sInputObject_5BD4E0.isPressed(sInputKey_Hop_5550E0))
                        {
                            ToJump_4A75E0();
                            MapFollowMe_408D10(TRUE);
                            return;
                        }

                        if (sInputObject_5BD4E0.isPressed(0xA0) && field_178)
                        {
                            field_12C = sGnFrame_5C1B84 + field_174_whirl_attack_duration;
                            field_106_current_motion = eScrabMotions::M_AttackSpin_32_4A8DC0;
                            field_108_next_motion = -1;
                            MapFollowMe_408D10(TRUE);
                            return;
                        }

                        MapFollowMe_408D10(TRUE);
                        return;
                    }
                }
            }
            field_106_current_motion = eScrabMotions::M_RunToStand_4_4A90C0;
            MapFollowMe_408D10(TRUE);
            return;

        default:
            return;
        }
    }
}

void Scrab::M_Turn_3_4A91A0()
{
    if (field_20_animation.field_92_current_frame == 5 || field_20_animation.field_92_current_frame == 9 || field_20_animation.field_92_current_frame == 11)
    {
        Sound_4AADB0(ScrabSound::Unknown_6, Math_RandomRange_496AB0(40, 50), 0x7FFF, 1);
    }

    if (field_20_animation.field_4_flags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        field_20_animation.field_4_flags.Toggle(AnimFlags::eBit5_FlipX);
        TryMoveOrStand_4A7570();
    }
}

const FP dword_546EFC[10] =
{ 
    490908,
    453112,
    254902,
    155230,
    49871,
    42004,
    46393,
    50715,
    47541,
    47764
};

void Scrab::M_RunToStand_4_4A90C0()
{
    auto pTarget = static_cast<BaseAliveGameObject*>(sObjectIds_5C1B70.Find_449CF0(field_120_obj_id));
    field_C4_velx = field_CC_sprite_scale * dword_546EFC[field_20_animation.field_92_current_frame & 10]; // TODO: check size
    if (field_20_animation.field_4_flags.Get(AnimFlags::eBit5_FlipX))
    {
        field_C4_velx = -field_C4_velx;
    }

    if (WallHit_408750(field_CC_sprite_scale * FP_FromInteger(45), field_C4_velx))
    {
        KnockBack_4AA530();
    }
    else
    {
        MoveOnLine_4A7D20();

        if (field_106_current_motion == eScrabMotions::M_RunToStand_4_4A90C0)
        {
            KillTarget_4A7F20(pTarget);

            if (field_20_animation.field_4_flags.Get(AnimFlags::eBit18_IsLastFrame))
            {
                MapFollowMe_408D10(TRUE);
                TryMoveOrStand_4A7570();
            }
        }
    }
}

const int sScrabHopBeginVelX_546F24[4] =
{
    -67391,
    -120599,
    -13453,
    182100
};

void Scrab::M_HopBegin_5_4A96C0()
{
    Event_Broadcast_422BC0(kEventNoise, this);

    FP frameVelX = {};
    if (field_20_animation.field_4_flags.Get(AnimFlags::eBit5_FlipX))
    {
        frameVelX = FP_FromRaw(-sScrabHopBeginVelX_546F24[field_20_animation.field_92_current_frame]);
    }
    else
    {
        frameVelX = FP_FromRaw(sScrabHopBeginVelX_546F24[field_20_animation.field_92_current_frame]);
    }

    field_C4_velx = field_CC_sprite_scale * frameVelX;

    FP gridSize = {};
    if (field_20_animation.field_4_flags.Get(AnimFlags::eBit5_FlipX))
    {
        gridSize = -ScaleToGridSize_4498B0(field_CC_sprite_scale);
    }
    else
    {
        gridSize = ScaleToGridSize_4498B0(field_CC_sprite_scale);
    }

    if (WallHit_408750(field_CC_sprite_scale * FP_FromInteger(45), gridSize * FP_FromDouble(0.75)))
    {
        KnockBack_4AA530();
        field_106_current_motion = eScrabMotions::M_JumpToFall_8_4A9220;
    }
    else
    {
        field_B8_xpos += field_C4_velx;
        if (field_20_animation.field_4_flags.Get(AnimFlags::eBit18_IsLastFrame))
        {
            SFX_Play_46FBA0(28, 50, -800);
            field_F8_LastLineYPos = field_BC_ypos;
            if (field_20_animation.field_4_flags.Get(AnimFlags::eBit5_FlipX))
            {
                field_C4_velx = field_CC_sprite_scale * FP_FromDouble(-5.67);
            }
            else
            {
                field_C4_velx = field_CC_sprite_scale * FP_FromDouble(5.67);
            }
            field_C8_vely = field_CC_sprite_scale * FP_FromDouble(-9.8);
            field_BC_ypos += field_C8_vely;
            VOnTrapDoorOpen();
            field_106_current_motion = eScrabMotions::M_HopMidair_6_4A9490;
            field_100_pCollisionLine = nullptr;
        }
    }
}

const int sScrabHopMidAirVelX_546F34[8] =
{
    328032,
    450949,
    1035263,
    1199918,
    1015439,
    995306,
    405215,
    328032
};

void Scrab::M_HopMidair_6_4A9490()
{
    Event_Broadcast_422BC0(kEventNoise, this);

    FP frameVelX = {};
    if (field_20_animation.field_4_flags.Get(AnimFlags::eBit5_FlipX))
    {
        frameVelX = FP_FromRaw(-sScrabHopMidAirVelX_546F34[field_20_animation.field_92_current_frame]);
    }
    else
    {
        frameVelX = FP_FromRaw(sScrabHopMidAirVelX_546F34[field_20_animation.field_92_current_frame]);
    }

    field_C4_velx = field_CC_sprite_scale * frameVelX;
    
    FP kGridSize = {};
    if (field_20_animation.field_4_flags.Get(AnimFlags::eBit5_FlipX))
    {
        kGridSize = -ScaleToGridSize_4498B0(field_CC_sprite_scale);
    }
    else
    {
        kGridSize = ScaleToGridSize_4498B0(field_CC_sprite_scale);
    }

    if (WallHit_408750(field_CC_sprite_scale * FP_FromInteger(45), kGridSize * FP_FromDouble(0.75)))
    {
        KnockBack_4AA530();
    }
    else
    {
        FP hitX = {};
        FP hitY = {};
        PathLine* pLine = nullptr;
        const __int16 bCollision = InAirCollision_408810(&pLine, &hitX, &hitY, FP_FromDouble(1.8));

        if (sControlledCharacter_5C1B8C == this)
        {
            sub_408C40();
        }

        if (bCollision)
        {
            switch (pLine->field_8_type)
            {
            case 0u:
            case 4u:
            case 32u:
            case 36u:
                field_100_pCollisionLine = pLine;
                ToStand_4A75A0();
                field_106_current_motion = eScrabMotions::M_HopLand_7_4A9890;
                PlatformCollide_4A7E50();
                field_B8_xpos = hitX;
                field_BC_ypos = hitY;
                return;

            case 1u:
            case 2u:
                field_C4_velx = (-field_C4_velx / FP_FromInteger(2));
                return;
            }
        }

        if (field_BC_ypos - field_F8_LastLineYPos > FP_FromInteger(5))
        {
            field_134 = FP_FromDouble(1.25);
            field_106_current_motion = eScrabMotions::M_JumpToFall_8_4A9220;
        }
    }
}

const int sScrabHopLandVelX_546F54[4] =
{
    182100,
    61799,
    28801,
    25454
};

void Scrab::M_HopLand_7_4A9890()
{
    if (field_20_animation.field_92_current_frame == 0)
    {
        Abe_SFX_2_457A40(6, 80, 400, this);
        Sound_4AADB0(ScrabSound::Unknown_4, 0, 0x7FFF, 1);
    }
    
    Event_Broadcast_422BC0(kEventNoise, this);

    FP frameVelX = {};
    if (field_20_animation.field_4_flags.Get(AnimFlags::eBit5_FlipX))
    {
        frameVelX = FP_FromRaw(-sScrabHopLandVelX_546F54[field_20_animation.field_92_current_frame]);
    }
    else
    {
        frameVelX = FP_FromRaw(sScrabHopLandVelX_546F54[field_20_animation.field_92_current_frame]);
    }
    field_C4_velx = (field_CC_sprite_scale * frameVelX);

    FP gridSize = {};
    if (field_20_animation.field_4_flags.Get(AnimFlags::eBit5_FlipX))
    {
        gridSize = -ScaleToGridSize_4498B0(field_CC_sprite_scale);
    }
    else
    {
        gridSize = ScaleToGridSize_4498B0(field_CC_sprite_scale);
    }

    if (WallHit_408750(field_CC_sprite_scale * FP_FromInteger(45), gridSize * FP_FromDouble(0.75)))
    {
        KnockBack_4AA530();
    }
    else
    {
        MoveOnLine_4A7D20();
        if (field_20_animation.field_4_flags.Get(AnimFlags::eBit18_IsLastFrame))
        {
            ToStand_4A75A0();
        }
    }
}

void Scrab::M_JumpToFall_8_4A9220()
{
    if (field_C4_velx > FP_FromInteger(0))
    {
        field_C4_velx = field_C4_velx - (field_CC_sprite_scale * field_134);
        if (field_C4_velx < FP_FromInteger(0))
        {
            field_C4_velx = FP_FromInteger(0);
        }
    }
    else if (field_C4_velx < FP_FromInteger(0))
    {
        field_C4_velx = (field_CC_sprite_scale * field_134) + field_C4_velx;
        if (field_C4_velx > FP_FromInteger(0))
        {
            field_C4_velx = FP_FromInteger(0);
        }
    }

    PathLine* pLine = nullptr;
    FP hitX = {};
    FP hitY = {};
    const __int16 bHit = InAirCollision_408810(&pLine, &hitX, &hitY, FP_FromDouble(1.8));
    if (sControlledCharacter_5C1B8C == this)
    {
        sub_408C40();
    }

    if (bHit)
    {
        switch (pLine->field_8_type)
        {
        case 0u:
        case 4u:
        case 32u:
        case 36u:
            field_100_pCollisionLine = pLine;
            field_106_current_motion = eScrabMotions::M_Fall_20_4A93E0;
            PlatformCollide_4A7E50();
            field_BC_ypos = hitY;
            field_B8_xpos = hitX;
            MapFollowMe_408D10(TRUE);
            break;
        case 1u:
        case 2u:
            field_C4_velx = (-field_C4_velx / FP_FromInteger(2));
            break;
        default:
            return;
        }
    }
}

const FP sStandToWalkVels_546E48[3] =
{ 
    FP_FromDouble(1.12),
    FP_FromDouble(2.37),
    FP_FromDouble(3.20)
};

void Scrab::M_StandToWalk_9_4A8450()
{
    field_C4_velx = (field_CC_sprite_scale * sStandToWalkVels_546E48[field_20_animation.field_92_current_frame & 3]); // TODO: Check size of 3 is correct
    if (field_20_animation.field_4_flags.Get(AnimFlags::eBit5_FlipX))
    {
        field_C4_velx = -field_C4_velx;
    }
    
    MoveOnLine_4A7D20();
    
    if (field_106_current_motion == eScrabMotions::M_StandToWalk_9_4A8450)
    {
        if (field_20_animation.field_4_flags.Get(AnimFlags::eBit18_IsLastFrame))
        {
            field_106_current_motion = 1;
        }
    }
}

const FP sStandToRunVels_546EB8[3] =
{
    FP_FromDouble(2.29),
    FP_FromDouble(2.69),
    FP_FromDouble(3.88)
};

void Scrab::M_StandToRun_10_4A8900()
{
    field_C4_velx = field_CC_sprite_scale * sStandToRunVels_546EB8[field_20_animation.field_92_current_frame & 3]; // TODO: Check size of 3 is correct
    if (field_20_animation.field_4_flags.Get(AnimFlags::eBit5_FlipX))
    {
        field_C4_velx = -field_C4_velx;
    }

    if (WallHit_408750(field_CC_sprite_scale * FP_FromInteger(45), field_C4_velx))
    {
        KnockBack_4AA530();
    }
    else
    {
        MoveOnLine_4A7D20();

        if (field_106_current_motion == eScrabMotions::M_StandToRun_10_4A8900)
        {
            if (field_20_animation.field_4_flags.Get(AnimFlags::eBit18_IsLastFrame))
            {
                field_106_current_motion = eScrabMotions::M_Run_2_4A89C0;
            }
        }
    }
}

const FP sWalkToStandVels_546EAC[3] =
{ 
    FP_FromDouble(1.04),
    FP_FromDouble(3.29),
    FP_FromDouble(2.86)
};

void Scrab::M_WalkToStand_11_4A8880()
{
    field_C4_velx = (field_CC_sprite_scale * sWalkToStandVels_546EAC[field_20_animation.field_92_current_frame & 3]); // TODO: Check size of 3 is correct
    if (field_20_animation.field_4_flags.Get(AnimFlags::eBit5_FlipX))
    {
        field_C4_velx = -field_C4_velx;
    }
    
    MoveOnLine_4A7D20();
    
    if (field_106_current_motion == eScrabMotions::M_WalkToStand_11_4A8880)
    {
        if (field_20_animation.field_4_flags.Get(AnimFlags::eBit18_IsLastFrame))
        {
            TryMoveOrStand_4A7570();
        }
    }
}

const FP dword_546F64[8] =
{
    FP_FromDouble(11.25),
    FP_FromDouble(10.49),
    FP_FromDouble(9.67),
    FP_FromDouble(9.01),
    FP_FromDouble(7.47),
    FP_FromDouble(7.03),
    FP_FromDouble(6.69),
    FP_FromDouble(6.44)
};

void Scrab::M_RunJumpBegin_12_4A99C0()
{
    if (field_20_animation.field_92_current_frame == 1)
    {
        SFX_Play_46FBA0(0x1Cu, 50, -800);
    }
    
    Event_Broadcast_422BC0(kEventNoise, this);

    FP velX = {};
    if (field_20_animation.field_4_flags.Get(AnimFlags::eBit5_FlipX))
    {
        velX = -dword_546F64[field_20_animation.field_92_current_frame & 8]; // TODO: Check size
    }
    else
    {
        velX = dword_546F64[field_20_animation.field_92_current_frame & 8]; // TODO: Check size
    }

    field_C4_velx = field_CC_sprite_scale * velX;

    if (WallHit_408750(field_CC_sprite_scale * FP_FromInteger(45), field_C4_velx))
    {
        KnockBack_4AA530();
    }
    else
    {
        FP hitX = {};
        FP hitY = {};
        PathLine* pLine = nullptr;
        const __int16 bHit = InAirCollision_408810(&pLine, &hitX, &hitY, FP_FromDouble(1.8));
        if (sControlledCharacter_5C1B8C == this)
        {
            sub_408C40();
        }

        if (bHit)
        {
            switch (pLine->field_8_type)
            {
            case 0u:
            case 4u:
            case 32u:
            case 36u:
                field_100_pCollisionLine = pLine;
                ToStand_4A75A0();
                field_106_current_motion = eScrabMotions::M_RunJumpEnd_13_4A9BE0;
                PlatformCollide_4A7E50();
                field_B8_xpos = hitX;
                field_BC_ypos = hitY;
                return;

            case 1u:
            case 2u:
                field_C4_velx = (-field_C4_velx / FP_FromInteger(2));
                return;
            default:
                break;
            }
        }
        
        if (field_BC_ypos - field_F8_LastLineYPos > FP_FromInteger(5))
        {
            field_134 = FP_FromDouble(1.25);
            field_106_current_motion = eScrabMotions::M_JumpToFall_8_4A9220;
        }
    }
}

const FP sEndRunJumpVels_546F84[21] =
{
    FP_FromDouble(2.68),
    FP_FromDouble(2.65),
    FP_FromDouble(2.72),
    FP_FromDouble(2.89),
    FP_FromInteger(0),
    FP_FromInteger(0),
    FP_FromInteger(0),
    FP_FromInteger(0),
    FP_FromInteger(0),
    FP_FromInteger(0),
    FP_FromInteger(0),
    FP_FromInteger(0),
    FP_FromInteger(0),
    FP_FromInteger(0),
    FP_FromInteger(0),
    FP_FromInteger(0),
    FP_FromInteger(0),
    FP_FromInteger(0),
    FP_FromInteger(0),
    FP_FromInteger(0),
    FP_FromInteger(0)
};


void Scrab::M_RunJumpEnd_13_4A9BE0()
{
    Event_Broadcast_422BC0(kEventNoise, this);
    field_C4_velx = (field_CC_sprite_scale * sEndRunJumpVels_546F84[field_20_animation.field_92_current_frame & 21]); // TODO: Check size
    if (field_20_animation.field_4_flags.Get(AnimFlags::eBit5_FlipX))
    {
        field_C4_velx = -field_C4_velx;
    }

    if (WallHit_408750(field_CC_sprite_scale * FP_FromInteger(45), field_C4_velx))
    {
        KnockBack_4AA530();
    }
    else
    {
        MoveOnLine_4A7D20();
        if (field_20_animation.field_4_flags.Get(AnimFlags::eBit18_IsLastFrame))
        {
            Sound_4AADB0(ScrabSound::Unknown_4, 0, 0x7FFF, 1);
            if (!ToNextMotion_4A7920())
            {
                ToStand_4A75A0();
            }
        }
    }
}

void Scrab::M_WalkToFall_14_4A9460()
{
    M_JumpToFall_8_4A9220();
    if (field_106_current_motion == eScrabMotions::M_Stand_0_4A8220)
    {
        field_106_current_motion = eScrabMotions::M_HopLand_7_4A9890;
    }
}

void Scrab::M_RunToFall_15_4A9430()
{
    M_JumpToFall_8_4A9220();
    if (field_106_current_motion == eScrabMotions::M_Stand_0_4A8220)
    {
        field_106_current_motion = eScrabMotions::M_HopLand_7_4A9890;
    }
}

void Scrab::M_WalkToRun_16_4A8D60()
{
    if (field_20_animation.field_4_flags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        field_106_current_motion = eScrabMotions::M_Run_2_4A89C0;
        field_108_next_motion = -1;
    }
}

void Scrab::M_RunToWalk_17_4A8D90()
{
    if (field_20_animation.field_4_flags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        field_106_current_motion = eScrabMotions::M_Walk_1_4A84D0;
        field_108_next_motion = -1;
    }
}

void Scrab::M_Knockback_18_4AA490()
{
    if (field_100_pCollisionLine)
    {
        MoveOnLine_4A7D20();
    }
    else
    {
        M_JumpToFall_8_4A9220();
    }

    if (field_20_animation.field_92_current_frame == 0)
    {
        Abe_SFX_2_457A40(6, 80, 400, this);
    }

    else if (field_20_animation.field_92_current_frame == 2)
    {
        Sound_4AADB0(ScrabSound::Unknown_4, 0, 0x7FFF, 1);
    }

    if (field_20_animation.field_4_flags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        if (field_100_pCollisionLine)
        {
            ToStand_4A75A0();
        }
        else
        {
            field_106_current_motion = eScrabMotions::M_JumpToFall_8_4A9220;
        }
    }
}

void Scrab::M_GetEaten_19_4AA3E0()
{
    if (field_20_animation.field_92_current_frame == 3)
    {
        SFX_Play_46FBA0(28u, 120, -1000);
    }
}

void Scrab::M_Fall_20_4A93E0()
{
    if (field_20_animation.field_4_flags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        Abe_SFX_2_457A40(6, 80, 400, this);
        Sound_4AADB0(ScrabSound::Unknown_4, 0, 0x7FFF, 1);
        ToStand_4A75A0();
        field_108_next_motion = -1;
    }
}

void Scrab::M_Stamp_21_4A9CC0()
{
    if (field_20_animation.field_92_current_frame == 9)
    {
        if (BrainIs(&Scrab::AI_Possessed_5_4A6180))
        {
            KillTarget_4A7F20(nullptr);
        }

        Sound_4AADB0(ScrabSound::Unknown_4, 0, 0x7FFF, 1);
        SFX_Play_46FBA0(64, 60, Math_RandomRange_496AB0(-255, 255));
    }

    if (field_20_animation.field_4_flags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        Sound_4AADB0(ScrabSound::Unknown_0, 60, 511, 1);

        if (BrainIs(&Scrab::AI_Possessed_5_4A6180))
        {
            ToStand_4A75A0();
        }
        else
        {
            ToNextMotion_4A7920();
        }
    }
}

void Scrab::M_GetPossessed_22_4AA420()
{
    if (field_20_animation.field_92_current_frame == 9)
    {
        Sound_4AADB0(ScrabSound::Unknown_4, 0, 0x7FFF, 1);
    }

    if (field_20_animation.field_4_flags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        if (field_108_next_motion)
        {
            field_1AA_flags.Set(Flags_1AA::eBit4);
            field_106_current_motion = eScrabMotions::M_GetPossessed_22_4AA420;
        }
        else
        {
            ToStand_4A75A0();
        }
    }
}

void Scrab::M_Empty_23_4A9D80()
{
    NOT_IMPLEMENTED();
}

void Scrab::M_DeathEnd_24_4AA140()
{
    if (!field_100_pCollisionLine)
    {
        field_C4_velx = FP_FromInteger(0);
        M_JumpToFall_8_4A9220();
        if (field_106_current_motion != eScrabMotions::M_DeathEnd_24_4AA140)
        {
            field_106_current_motion = eScrabMotions::M_DeathEnd_24_4AA140;
        }
    }
}

void Scrab::M_Empty_25_4A34D0()
{
    NOT_IMPLEMENTED();
}

void Scrab::M_HowlBegin_26_4A9DA0()
{
    if (field_20_animation.field_92_current_frame == 2)
    {
        if (sGnFrame_5C1B84 & 1)
        {
            Event_Broadcast_422BC0(kEventLoudNoise, this);
            Sound_4AADB0(ScrabSound::Unknown_8, 0, Math_RandomRange_496AB0(-1600, -900), 1);
            if (BrainIs(&Scrab::AI_Possessed_5_4A6180))
            {
                pEventSystem_5BC11C->PushEvent_4218D0(GameSpeakEvents::eUnknown_53);
            }
        }
    }

    if (field_20_animation.field_4_flags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        field_178 = 1;

        if (field_108_next_motion == -1)
        {
            ToStand_4A75A0();
        }
        else
        {
            field_106_current_motion = eScrabMotions::M_HowlEnd_27_4A9E60;
        }
    }
}

void Scrab::M_HowlEnd_27_4A9E60()
{
    if (field_20_animation.field_4_flags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        if (BrainIs(&Scrab::AI_Possessed_5_4A6180))
        {
            if (!ToNextMotion_4A7920())
            {
                ToStand_4A75A0();
            }
        }
        else
        {
            ToNextMotion_4A7920();
        }
    }
}

void Scrab::M_GetDepossessedBegin_28_4AA200()
{
    field_178 = 0;

    if (sControlledCharacter_5C1B8C == this)
    {
        if (field_20_animation.field_92_current_frame == 2)
        {
            Sound_4AADB0(ScrabSound::Unknown_8, 0, Math_RandomRange_496AB0(-1600, -900), 1);
        }

        if (field_20_animation.field_4_flags.Get(AnimFlags::eBit18_IsLastFrame))
        {
            if (!Input_IsChanting_45F260())
            {
                field_106_current_motion = eScrabMotions::M_GetDepossessedEnd_29_4AA3C0;
            }
        }

        if (!(static_cast<int>(sGnFrame_5C1B84) % 4))
        {
            const FP xRnd = FP_FromInteger(Math_RandomRange_496AB0(-20, 20));
            const FP yRnd = FP_FromInteger(Math_RandomRange_496AB0(20, 50));
            const FP ypos = field_BC_ypos - (field_CC_sprite_scale * yRnd);
            const FP xpos = (field_CC_sprite_scale * xRnd) + field_B8_xpos;
            New_Chant_Particle_426BE0(xpos, ypos, field_CC_sprite_scale, 0);
        }

        if (static_cast<int>(sGnFrame_5C1B84) > field_130 || sActiveHero_5C1B68->field_10C_health <= FP_FromInteger(0))
        {
            sControlledCharacter_5C1B8C = sActiveHero_5C1B68;
            field_114_flags.Clear(Flags_114::e114_Bit4_bPossesed);
            field_1A2 = 0;
            MusicController::sub_47FD60(0, this, 0, 0);
            field_106_current_motion = eScrabMotions::M_GetDepossessedEnd_29_4AA3C0;
            ToPatrol_4AA600();
            field_11C_sub_state = 0;
            gMap_5C3030.SetActiveCam_480D30(field_166_level, field_168_path, field_16A_camera, CameraSwapEffects::eEffect0_InstantChange, 0, 0);
        }
    }
}

void Scrab::M_GetDepossessedEnd_29_4AA3C0()
{
    if (field_20_animation.field_4_flags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        ToStand_4A75A0();
    }
}

void Scrab::M_Shriek_30_4A9EA0()
{
    if (field_20_animation.field_92_current_frame == 4)
    {
        if (sGnFrame_5C1B84 & 1)
        {
            Event_Broadcast_422BC0(kEventLoudNoise, this);
            Sound_4AADB0(ScrabSound::Unknown_0, 0, 0x7FFF, 1);
            if (BrainIs(&Scrab::AI_Possessed_5_4A6180))
            {
                pEventSystem_5BC11C->PushEvent_4218D0(GameSpeakEvents::eUnknown_54);
            }
        }
    }

    if (field_20_animation.field_4_flags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        if (!ToNextMotion_4A7920())
        {
            ToStand_4A75A0();
        }
    }
}

void Scrab::M_ScrabBattleAnim_31_4A9F30()
{
    if (field_20_animation.field_92_current_frame == 0)
    {
        field_160 = Sound_4AADB0(ScrabSound::Unknown_5, 100, Math_RandomRange_496AB0(-600, 200), 1);
    }

    if (field_20_animation.field_4_flags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        ToNextMotion_4A7920();
    }
}

void Scrab::M_AttackSpin_32_4A8DC0()
{
    auto pObj = static_cast<BaseAliveGameObject*>(sObjectIds_5C1B70.Find_449CF0(field_120_obj_id));

    field_178 = 0;

    if (static_cast<int>(sGnFrame_5C1B84) > field_12C)
    {
        field_106_current_motion = 2;
        return;
    }

    if (field_20_animation.field_92_current_frame == 0)
    {
        field_160 = Sound_4AADB0(ScrabSound::Unknown_5, 100, Math_RandomRange_496AB0(-600, 200), 1);
    }

    const FP kGridSize = ScaleToGridSize_4498B0(field_CC_sprite_scale);
    if (sControlledCharacter_5C1B8C != this)
    {
        if (pObj)
        {
            if (pObj->field_B8_xpos <= field_B8_xpos)
            {
                field_C4_velx = -(kGridSize / FP_FromDouble(3.5));
            }
            else
            {
                field_C4_velx = (kGridSize / FP_FromDouble(3.5));
            }
        }
        else
        {
            field_C4_velx = FP_FromInteger(0);
        }
    }
    else
    {
        if (sInputObject_5BD4E0.isPressed(eThrowItem | eDoAction))
        {
            if (!sInputObject_5BD4E0.isPressed(sInputKey_Left_5550D4 | sInputKey_Right_5550D0))
            {
                field_C4_velx = FP_FromInteger(0);
            }

            if (sInputObject_5BD4E0.isPressed(sInputKey_Run_5550E8))
            {
                if (sInputObject_5BD4E0.isPressed(sInputKey_Left_5550D4))
                {
                    field_C4_velx = -(kGridSize / FP_FromDouble(3.5));
                }

                if (sInputObject_5BD4E0.isPressed(sInputKey_Right_5550D0))
                {
                    field_C4_velx = (kGridSize / FP_FromDouble(3.5));
                }
            }
            else
            {
                if (sInputObject_5BD4E0.isPressed(sInputKey_Left_5550D4))
                {
                    field_C4_velx = -(kGridSize / FP_FromInteger(7));
                }

                if (sInputObject_5BD4E0.isPressed(sInputKey_Right_5550D0))
                {
                    field_C4_velx = (kGridSize / FP_FromInteger(7));
                }
            }
        }
        else
        {
            field_106_current_motion = eScrabMotions::M_Run_2_4A89C0;
        }
    }

    MapFollowMe_408D10(0);

    if (WallHit_408750(field_CC_sprite_scale * FP_FromInteger(45), field_C4_velx))
    {
        field_C4_velx = (-field_C4_velx / FP_FromInteger(2));
    }
    else
    {
        MoveOnLine_4A7D20();
        if (field_106_current_motion == eScrabMotions::M_AttackSpin_32_4A8DC0)
        {
            KillTarget_4A7F20(pObj);
        }
    }
}

void Scrab::M_FeedToGulp_33_4A9FA0()
{
    if (field_20_animation.field_4_flags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        if (field_108_next_motion == eScrabMotions::M_StandToFeed_35_4AA010)
        {
            field_106_current_motion = eScrabMotions::M_StandToFeed_35_4AA010;
        }
        else
        {
            field_106_current_motion = eScrabMotions::M_GulpToStand_34_4A9FF0;
        }
        field_108_next_motion = -1;
    }
}

void Scrab::M_GulpToStand_34_4A9FF0()
{
    if (field_20_animation.field_4_flags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        ToStand_4A75A0();
    }
}

void Scrab::M_StandToFeed_35_4AA010()
{
    if (field_20_animation.field_4_flags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        field_106_current_motion = eScrabMotions::M_Feed_36_4AA030;
    }
}

void Scrab::M_Feed_36_4AA030()
{
    if (field_20_animation.field_92_current_frame)
    {
        if (field_20_animation.field_4_flags.Get(AnimFlags::eBit18_IsLastFrame))
        {
            field_106_current_motion = eScrabMotions::M_FeedToGulp_33_4A9FA0;
        }
    }
    else
    {
        SFX_Play_46FA90((Math_NextRandom() & 1) ? 66 : 65, 0);
    }
}

void Scrab::M_AttackLunge_37_4AA0B0()
{
    auto pTarget = static_cast<BaseAliveGameObject*>(sObjectIds_5C1B70.Find_449CF0(field_120_obj_id));
    KillTarget_4A7F20(pTarget);

    if (field_20_animation.field_92_current_frame == 4)
    {
        Sound_4AADB0(ScrabSound::Unknown_0, 0, 0x7FFF, 1);
    }
    else if (field_20_animation.field_4_flags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        ToStand_4A75A0();
    }

}

void Scrab::M_LegKick_38_4AA120()
{
    M_AttackLunge_37_4AA0B0();
}

void Scrab::M_DeathBegin_39_4AA190()
{
    if (!field_100_pCollisionLine)
    {
        field_C4_velx = FP_FromInteger(0);
        M_JumpToFall_8_4A9220();
        if (field_106_current_motion != eScrabMotions::M_DeathBegin_39_4AA190)
        {
            field_106_current_motion = eScrabMotions::M_DeathBegin_39_4AA190;
        }
    }
    if (field_20_animation.field_4_flags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        field_106_current_motion = eScrabMotions::M_DeathEnd_24_4AA140;
    }
}

__int16 Scrab::vOnSameYLevel_4A5400(BaseAnimatedWithPhysicsGameObject* pOther)
{
    PSX_RECT ourRect = {};
    vGetBoundingRect_424FD0(&ourRect, 1);

    PSX_RECT otherRect = {};
    pOther->vGetBoundingRect_424FD0(&otherRect, 1);

    const FP k10Scaled = (FP_FromInteger(10) * field_CC_sprite_scale);
    if (FP_FromInteger(ourRect.y) <= (FP_FromInteger(otherRect.h) - k10Scaled) && ourRect.y >= otherRect.y)
    {
        return TRUE;
    }

    if (ourRect.h <= otherRect.h)
    {
        if (FP_FromInteger(ourRect.h) >= (k10Scaled + FP_FromInteger(otherRect.y)))
        {
            return TRUE;
        }
    }

    if (ourRect.y >= otherRect.y)
    {
        if (ourRect.h <= otherRect.h)
        {
            return TRUE;
        }

        if (ourRect.y > otherRect.y)
        {
            return FALSE;
        }
    }

    if (ourRect.h < otherRect.h)
    {
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}

void Scrab::ToPatrol_4AA600()
{
    SetBrain(&Scrab::AI_Patrol_0_4AA630);
    field_138 = field_B8_xpos;
}

void Scrab::ToStand_4A75A0()
{
    field_134 = FP_FromInteger(0);
    field_C4_velx = FP_FromInteger(0);
    field_C8_vely = FP_FromInteger(0);
    field_106_current_motion = eScrabMotions::M_Stand_0_4A8220;
    MapFollowMe_408D10(TRUE);
}

void Scrab::MoveOnLine_4A7D20()
{
    BaseGameObject* pObj = sObjectIds_5C1B70.Find_449CF0(field_110_id);
    const FP oldXPos = field_B8_xpos;
    if (field_100_pCollisionLine)
    {
        field_100_pCollisionLine = field_100_pCollisionLine->MoveOnLine_418260(&field_B8_xpos, &field_BC_ypos, field_C4_velx);
        if (field_100_pCollisionLine)
        {
            if (pObj)
            {
                if (field_100_pCollisionLine->field_8_type != 32 && field_100_pCollisionLine->field_8_type != 36)
                {
                    const auto oldMotion = field_106_current_motion;
                    VOnTrapDoorOpen();
                    field_106_current_motion = oldMotion;
                }
            }
            else if (field_100_pCollisionLine->field_8_type == 32 || field_100_pCollisionLine->field_8_type == 36)
            {
                PlatformCollide_4A7E50();
            }
        }
        else
        {
            VOnTrapDoorOpen();
            field_F8_LastLineYPos = field_BC_ypos;
            field_134 = FP_FromInteger(1);
            field_B8_xpos = oldXPos + field_C4_velx;
            if (field_106_current_motion == eScrabMotions::M_Walk_1_4A84D0)
            {
                field_106_current_motion = eScrabMotions::M_WalkToFall_14_4A9460;
            }
            else
            {
                field_106_current_motion = eScrabMotions::M_RunToFall_15_4A9430;
            }
        }
    }
    else
    {
        field_106_current_motion = eScrabMotions::M_JumpToFall_8_4A9220;
        field_F8_LastLineYPos = field_BC_ypos;
    }
}

void Scrab::PlatformCollide_4A7E50()
{
    PSX_RECT bRect = {};
    vGetBoundingRect_424FD0(&bRect, 1);

    const PSX_Point xy = { bRect.x, static_cast<short>(bRect.y + 5) };
    const PSX_Point wh = { bRect.w, static_cast<short>(bRect.h + 5) };
    vOnCollisionWith_424EE0(xy, wh, ObjList_5C1B78, 1, (TCollisionCallBack)&BaseAliveGameObject::OnTrapDoorIntersection_408BA0);
}

BaseAliveGameObject* Scrab::Find_Fleech_4A4C90()
{
    for (int i=0; i<gBaseGameObject_list_BB47C4->Size(); i++)
    {
        auto pObj = gBaseGameObject_list_BB47C4->ItemAt(i);
        if (!pObj)
        {
            break;
        }

        if (pObj->field_4_typeId == Types::eFleech_50)
        {
            auto pAliveObj = static_cast<BaseAliveGameObject*>(pObj);
            if (pAliveObj->field_10C_health > FP_FromInteger(0))
            {
                if (pAliveObj->vOnSameYLevel_425520(pAliveObj))
                {
                    if (pAliveObj->vIsObjNearby_4253B0(ScaleToGridSize_4498B0(field_CC_sprite_scale) * FP_FromInteger(3), pAliveObj))
                    {
                        if (pAliveObj->vIsFacingMe_4254A0(pAliveObj))
                        {
                            if (!WallHit_408750(field_CC_sprite_scale * FP_FromInteger(45), pAliveObj->field_B8_xpos - field_B8_xpos) &&
                                gMap_5C3030.Is_Point_In_Current_Camera_4810D0(
                                    pAliveObj->field_C2_lvl_number,
                                    pAliveObj->field_C0_path_number,
                                    pAliveObj->field_B8_xpos,
                                    pAliveObj->field_BC_ypos,
                                    0) &&
                                gMap_5C3030.Is_Point_In_Current_Camera_4810D0(
                                    field_C2_lvl_number,
                                    field_C0_path_number,
                                    field_B8_xpos,
                                    field_BC_ypos,
                                    0))
                            {
                                return pAliveObj;
                            }
                        }
                    }
                }
            }
        }
    }
    return nullptr;
}

void Scrab::vPossesed_4A5620()
{
    field_114_flags.Set(Flags_114::e114_Bit4_bPossesed);
    field_164 = 1;
    field_178 = 0;
    field_106_current_motion = 22;
    field_108_next_motion = -1;
    vUpdateAnim_4A34F0();
    SetBrain(&Scrab::AI_Possessed_5_4A6180);
    field_11C_sub_state = 0;
    field_120_obj_id = -1;
    field_124_fight_target_obj_id = -1;
    field_12C = sGnFrame_5C1B84 + 35;
    field_166_level = gMap_5C3030.sCurrentLevelId_5C3030;
    field_168_path = gMap_5C3030.sCurrentPathId_5C3032;
    field_16A_camera = gMap_5C3030.sCurrentCamId_5C3034;
}

BYTE** Scrab::ResBlockForMotion_4A43E0(__int16 motion)
{
    if (motion < eScrabMotions::M_Stamp_21_4A9CC0)
    {
        field_140 = 0;
    }
    else if (motion < eScrabMotions::M_Empty_23_4A9D80)
    {
        field_140 = 6;
    }
    else if (motion < eScrabMotions::M_Empty_25_4A34D0)
    {
        field_140 = 8;
    }
    else if (motion < eScrabMotions::M_HowlBegin_26_4A9DA0)
    {
        field_140 = 10;
    }
    else if (motion < eScrabMotions::M_Shriek_30_4A9EA0)
    {
        field_140 = 5;
    }
    else if (motion < eScrabMotions::M_ScrabBattleAnim_31_4A9F30)
    {
        field_140 = 9;
    }
    else if (motion < eScrabMotions::M_FeedToGulp_33_4A9FA0)
    {
        field_140 = 4;
    }
    else if (motion < eScrabMotions::M_StandToFeed_35_4AA010)
    {
        field_140 = 11;
    }
    else if (motion < eScrabMotions::M_AttackLunge_37_4AA0B0)
    {
        field_140 = 1;
    }
    else if (motion < eScrabMotions::M_LegKick_38_4AA120)
    {
        field_140 = 2;
    }
    else if (motion >= eScrabMotions::M_DeathBegin_39_4AA190)
    {
        field_140 = motion >= 40 ? 0 : 13; // 40 == max motions ??
    }
    else
    {
        field_140 = 3;
    }
    return field_10_resources_array.ItemAt(field_140);
}

void Scrab::vScreenChanged_4A5560()
{
    BaseGameObject* pChaseTarget = sObjectIds_5C1B70.Find_449CF0(field_120_obj_id);

    if (gMap_5C3030.sCurrentLevelId_5C3030 != gMap_5C3030.field_A_5C303A_levelId || 
        gMap_5C3030.sCurrentPathId_5C3032 != gMap_5C3030.field_C_5C303C_pathId || 
        gMap_5C3030.field_22 != gMap_5C3030.Get_Path_Unknown_480710())
    {
        field_6_flags.Set(BaseGameObject::eDead);
    }
    else if (pChaseTarget)
    {
        if (pChaseTarget->field_6_flags.Get(BaseGameObject::eDead))
        {
            field_120_obj_id = -1;
            field_108_next_motion = eScrabMotions::M_Stand_0_4A8220;
            ToPatrol_4AA600();
            field_11C_sub_state = 0;
        }
    }
}

void Scrab::vRender_4A45B0(int** ot)
{
    if (field_1C_update_delay == 0)
    {
        BaseAnimatedWithPhysicsGameObject::VRender(ot);
    }
}

void Scrab::TryMoveOrStand_4A7570()
{
    if (!ToNextMotion_4A7920())
    {
        ToStand_4A75A0();
    }
}

__int16 Scrab::ToNextMotion_4A7920()
{
    MapFollowMe_408D10(TRUE);

    if (sControlledCharacter_5C1B8C == this && field_10C_health > FP_FromInteger(0) && field_11C_sub_state != 0)
    {
        return PlayerControlled_4A76A0();
    }

    if (field_108_next_motion == eScrabMotions::M_Turn_3_4A91A0 ||
        field_108_next_motion == eScrabMotions::M_Stamp_21_4A9CC0 ||
        field_108_next_motion == eScrabMotions::M_Empty_25_4A34D0 ||
        field_108_next_motion == eScrabMotions::M_HowlBegin_26_4A9DA0 ||
        field_108_next_motion == eScrabMotions::M_Shriek_30_4A9EA0 ||
        field_108_next_motion == eScrabMotions::M_ScrabBattleAnim_31_4A9F30 ||
        field_108_next_motion == eScrabMotions::M_AttackLunge_37_4AA0B0 ||
        field_108_next_motion == eScrabMotions::M_LegKick_38_4AA120 ||
        field_108_next_motion == eScrabMotions::M_StandToFeed_35_4AA010)
    {
        field_106_current_motion = field_108_next_motion;
        field_108_next_motion = -1;
        return 1;
    }

    const FP k45Scaled = (field_CC_sprite_scale * FP_FromInteger(45));
    const FP kGridSize = ScaleToGridSize_4498B0(field_CC_sprite_scale);

    // Check if going to run into a wall.
    if (field_108_next_motion == eScrabMotions::M_Run_2_4A89C0)
    {
        if (field_20_animation.field_4_flags.Get(AnimFlags::eBit5_FlipX))
        {
            if (WallHit_408750(k45Scaled, -kGridSize))
            {
                return 0;
            }
            else
            {
                field_C4_velx = -(kGridSize / FP_FromDouble(3.5));
                field_106_current_motion = eScrabMotions::M_StandToRun_10_4A8900;
                field_108_next_motion = -1;
                return 1;
            }
        }
        else
        {
            if (WallHit_408750(k45Scaled, kGridSize))
            {
                return 0;
            }
            else
            {
                field_C4_velx = (kGridSize / FP_FromDouble(3.5));
                field_106_current_motion = eScrabMotions::M_StandToRun_10_4A8900;
                field_108_next_motion = -1;
                return 1;
            }
        }
    }

    if (field_108_next_motion != 1)
    {
        if (field_108_next_motion == eScrabMotions::M_Stand_0_4A8220)
        {
            ToStand_4A75A0();
            return 1;
        }

        if (field_108_next_motion != eScrabMotions::M_HopMidair_6_4A9490)
        {
            return 0;
        }

        if (field_20_animation.field_4_flags.Get(AnimFlags::eBit5_FlipX))
        {
            if (WallHit_408750(k45Scaled, -kGridSize))
            {
                return 0;
            }
            else
            {
                field_106_current_motion = eScrabMotions::M_HopBegin_5_4A96C0;
                field_108_next_motion = -1;
                return 1;
            }
        }
        else
        {
            if (WallHit_408750(k45Scaled, kGridSize))
            {
                return 0;
            }
            else
            {
                field_106_current_motion = eScrabMotions::M_HopBegin_5_4A96C0;
                field_108_next_motion = -1;
                return 1;
            }
        }
    }
    else
    {
        if (field_20_animation.field_4_flags.Get(AnimFlags::eBit5_FlipX))
        {
            if (WallHit_408750(k45Scaled, -kGridSize))
            {
                return 0;
            }
            else
            {
                field_106_current_motion = eScrabMotions::M_StandToWalk_9_4A8450;
                field_C4_velx = -(kGridSize / FP_FromInteger(7));
                field_108_next_motion = -1;
                return 1;
            }
        }
        else
        {
            if (WallHit_408750(k45Scaled, kGridSize))
            {
                return 0;
            }
            else
            {
                field_106_current_motion = eScrabMotions::M_StandToWalk_9_4A8450;
                field_C4_velx = (kGridSize / FP_FromInteger(7));
                field_108_next_motion = -1;
                return 1;
            }
        }
    }
}

__int16 Scrab::PlayerControlled_4A76A0()
{
    const FP kGridSize = ScaleToGridSize_4498B0(field_CC_sprite_scale);
    const FP k45Scaled = (field_CC_sprite_scale * FP_FromInteger(45));

    if (sInputObject_5BD4E0.isPressed(sInputKey_Right_5550D0))
    {
        if (field_20_animation.field_4_flags.Get(AnimFlags::eBit5_FlipX))
        {
            field_106_current_motion = eScrabMotions::M_Turn_3_4A91A0;
            return 1;
        }
        else
        {
            if (WallHit_408750(k45Scaled, kGridSize))
            {
                return 0;
            }

            if (sInputObject_5BD4E0.isPressed(sInputKey_Run_5550E8))
            {
                field_C4_velx = (kGridSize / FP_FromDouble(3.5));
                field_106_current_motion = eScrabMotions::M_StandToRun_10_4A8900;
                return 1;

            }
            else
            {
                field_C4_velx = (kGridSize / FP_FromInteger(7));
                field_106_current_motion = eScrabMotions::M_StandToWalk_9_4A8450;
                return 1;
            }
        }
    }
    else if (sInputObject_5BD4E0.isPressed(sInputKey_Left_5550D4))
    {
        if (!field_20_animation.field_4_flags.Get(AnimFlags::eBit5_FlipX))
        {
            field_106_current_motion = eScrabMotions::M_Turn_3_4A91A0;
            return 1;
        }
        else
        {
            if (WallHit_408750(k45Scaled, -kGridSize))
            {
                return 0;
            }

            if (sInputObject_5BD4E0.isPressed(sInputKey_Run_5550E8))
            {
                field_C4_velx = -(kGridSize / FP_FromDouble(3.5));
                field_106_current_motion = eScrabMotions::M_StandToRun_10_4A8900;
                return 1;

            }
            else
            {
                field_C4_velx = -(kGridSize / FP_FromInteger(7));
                field_106_current_motion = eScrabMotions::M_StandToWalk_9_4A8450;
                return 1;
            }
        }
    }
    else
    {
        if (sInputObject_5BD4E0.isPressed(sInputKey_Up_5550D8))
        {
            field_106_current_motion = eScrabMotions::M_StandToFeed_35_4AA010;
            return 1;
        }

        if (sInputObject_5BD4E0.isPressed(sInputKey_Down_5550DC))
        {
            field_106_current_motion = eScrabMotions::M_Stamp_21_4A9CC0;
            return 1;
        }

        return 0;
    }
}

void Scrab::ToJump_4A75E0()
{
    field_F8_LastLineYPos = field_BC_ypos;

    if (field_20_animation.field_4_flags.Get(AnimFlags::eBit5_FlipX))
    {
        field_C4_velx = field_CC_sprite_scale * -FP_FromDouble(-5.67);
    }
    else
    {
        field_C4_velx = field_CC_sprite_scale * -FP_FromDouble(5.67);
    }

    field_C8_vely = field_CC_sprite_scale * FP_FromDouble(-9.6);
    field_BC_ypos += field_C8_vely;
    
    VOnTrapDoorOpen();

    field_106_current_motion = eScrabMotions::M_RunJumpBegin_12_4A99C0;
    field_100_pCollisionLine = nullptr;
}

__int16 Scrab::vTakeDamage_4A45E0(BaseGameObject* pFrom)
{
    if (field_10C_health <= FP_FromInteger(0))
    {
        return 0;
    }

    switch (pFrom->field_4_typeId)
    {
    case Types::eFleech_50:
        field_10C_health = field_10C_health - FP_FromDouble(0.13);
        if (field_10C_health < FP_FromInteger(0))
        {
            field_10C_health = FP_FromInteger(0);
        }

        if (field_10C_health > FP_FromInteger(0))
        {
            return 1;
        }

        if (static_cast<BaseAliveGameObject*>(pFrom)->field_B8_xpos >= field_B8_xpos)
        {
            field_20_animation.field_4_flags.Clear(AnimFlags::eBit5_FlipX);
        }
        else
        {
            field_20_animation.field_4_flags.Set(AnimFlags::eBit5_FlipX);
        }

        Event_Broadcast_422BC0(kEventMudokonComfort | kEventSpeaking, this);
        SetBrain(&Scrab::AI_ShrinkDeath_4_4A6420);
        field_106_current_motion = eScrabMotions::M_GetEaten_19_4AA3E0;
        field_12C = sGnFrame_5C1B84 + 90;
        vUpdateAnim_4A34F0();
        if (sControlledCharacter_5C1B8C == this)
        {
            SND_SEQ_Play_4CAB10(SeqId::DeathDrums_29, 1, 127, 127);
        }
        return 0;

    case Types::eType_104:
        return 0;

    case Types::eBullet_15:
    case Types::eType_107:
    case Types::eScrab_112:
        break;

    default:
        SFX_Play_46FA90(64u, 127);
        SFX_Play_46FA90(47u, 90);
        break;
    }

    Event_Broadcast_422BC0(kEventMudokonComfort | kEventSpeaking, this);
    field_10C_health = FP_FromInteger(0);
    SetBrain(&Scrab::AI_Death_3_4A62B0);
    field_12C = sGnFrame_5C1B84 + 90;
    field_106_current_motion = eScrabMotions::M_DeathBegin_39_4AA190;
    vUpdateAnim_4A34F0();
    
    if (sControlledCharacter_5C1B8C == this)
    {
        SND_SEQ_Play_4CAB10(SeqId::DeathDrums_29, 1, 127, 127);
    }

    return 1;
}

void Scrab::KnockBack_4AA530()
{
    field_134 = FP_FromDouble(0.35);

    const FP kGridSize = ScaleToGridSize_4498B0(field_CC_sprite_scale);

    FP v4 = {};
    if (field_20_animation.field_4_flags.Get(AnimFlags::eBit5_FlipX))
    {
        v4 = (kGridSize / FP_FromDouble(3.5));
    }
    else
    {
        v4 = -(kGridSize / FP_FromDouble(3.5));
    }
    field_C4_velx = (v4 / FP_FromInteger(2));
    
    MapFollowMe_408D10(TRUE);

    if (field_C8_vely < FP_FromInteger(0))
    {
        field_C8_vely = FP_FromInteger(0);
    }

    field_106_current_motion = eScrabMotions::M_Knockback_18_4AA490;
    field_130 = sGnFrame_5C1B84 + 10;
}

const SfxDefinition getSfxDef(ScrabSound effectId)
{
    return sScrabSfx_560330[static_cast<int>(effectId)];
}

int Scrab::Sound_4AADB0(ScrabSound soundId, int vol, int pitch, __int16 applyDirection)
{
    LOG_INFO("ScrabSound id:");
    LOG_INFO((int) soundId);
    __int16 volumeLeft = 0;
    __int16 volumeRight = 0;
    const CameraPos direction = gMap_5C3030.GetDirection_4811A0(
        field_C2_lvl_number,
        field_C0_path_number,
        field_B8_xpos,
        field_BC_ypos
    );

    const SfxDefinition effectDef = getSfxDef(soundId);
    const __int16 defaultSndIdxVol = effectDef.field_3_default_volume;

    volumeRight = static_cast<__int16>(vol);
    if (vol <= 0)
    {
        volumeRight = defaultSndIdxVol;
    }

    if (field_CC_sprite_scale == FP_FromDouble(0.5))
    {
        volumeRight /= 2;
    }

    if (applyDirection)
    {
        PSX_RECT pRect = {};
        gMap_5C3030.Get_Camera_World_Rect_481410(direction, &pRect);
        switch (direction)
        {
            case CameraPos::eCamCurrent_0:
                volumeLeft = volumeRight;
                break;
            case CameraPos::eCamTop_1:
            case CameraPos::eCamBottom_2:
            {
                volumeLeft = FP_GetExponent(FP_FromInteger(defaultSndIdxVol * 2) / FP_FromInteger(3));
                volumeRight = volumeLeft;
            }
                break;
            case CameraPos::eCamLeft_3:
            {
                const FP percentHowFar = (FP_FromInteger(pRect.w) - field_B8_xpos) / FP_FromInteger(368);
                volumeLeft = volumeRight - FP_GetExponent(percentHowFar * FP_FromInteger(volumeRight - (volumeRight / 3)));
                volumeRight = volumeRight - FP_GetExponent(percentHowFar * FP_FromInteger(volumeRight));
            }
                break;
            case CameraPos::eCamRight_4:
            {
                const FP percentHowFar = (field_B8_xpos - FP_FromInteger(pRect.x)) / FP_FromInteger(368);
                volumeLeft = volumeRight - FP_GetExponent(percentHowFar * FP_FromInteger(volumeRight));
                volumeRight = volumeRight - FP_GetExponent(percentHowFar * FP_FromInteger(volumeRight - (volumeRight / 3)));
            }
                break;
            default:
                return 0;
        }
    }
    else
    {
        volumeLeft = volumeRight;
    }

    return SFX_SfxDefinition_Play_4CA700(
        &effectDef,
        volumeLeft,
        volumeRight,
        static_cast<__int16>(pitch),
        static_cast<__int16>(pitch)
    );
}

void Scrab::KillTarget_4A7F20(BaseAliveGameObject* pTarget)
{
    bool bKilledTarget = false;
    bool bKillSpecific = false;

    if (Is_In_Current_Camera_424A70() == CameraPos::eCamCurrent_0)
    {
        if (!BrainIs(&Scrab::AI_Fighting_2_4A5840))
        {
            if (!BrainIs(&Scrab::AI_Possessed_5_4A6180) ||
                field_106_current_motion == eScrabMotions::M_LegKick_38_4AA120 ||
                field_106_current_motion == eScrabMotions::M_Stamp_21_4A9CC0 ||
                field_106_current_motion == eScrabMotions::M_AttackSpin_32_4A8DC0)
            {
                PSX_RECT bOurRect = {};
                vGetBoundingRect_424FD0(&bOurRect, 1);
                BaseAliveGameObject* pObj = pTarget;

                int list_idx = 0;
                if (pTarget)
                {
                    bKillSpecific = true;
                }
                else if (gBaseAliveGameObjects_5C1B7C->field_4_used_size > 0)
                {
                    list_idx = 1;
                    pObj = gBaseAliveGameObjects_5C1B7C->ItemAt(0);
                }
                else
                {
                    pObj = nullptr;
                }

                do
                {
                    if (pObj->field_6_flags.Get(BaseGameObject::eIsBaseAliveGameObject))
                    {
                        if (pObj != this)
                        {
                            if ((pObj->field_4_typeId == Types::eAbe_69 ||
                                pObj->field_4_typeId == Types::eMudokon2_81 ||
                                pObj->field_4_typeId == Types::eMudokon_110 ||
                                pObj->field_4_typeId == Types::eType_127 ||
                                pObj->field_4_typeId == Types::eFleech_50 ||
                                pObj->field_4_typeId == Types::eScrab_112) &&
                                field_D6_scale == pObj->field_D6_scale && pObj->field_10C_health > FP_FromInteger(0))
                            {
                                const FP xDist = pObj->field_B8_xpos - field_B8_xpos;
                                if (!WallHit_408750(field_CC_sprite_scale * FP_FromInteger(45), xDist))
                                {
                                    if (!pObj->field_114_flags.Get(Flags_114::e114_Bit8_bInvisible))
                                    {
                                        if (pObj->field_4_typeId != Types::eScrab_112 || !pObj->field_114_flags.Get(Flags_114::e114_Bit4_bPossesed) ||
                                            pObj->field_106_current_motion != eScrabMotions::M_AttackSpin_32_4A8DC0 &&
                                            (pObj->field_4_typeId != Types::eFleech_50 || BrainIs(&Scrab::AI_Possessed_5_4A6180) || field_1A8_kill_close_fleech))

                                        {
                                            PSX_RECT objRect = {};
                                            pObj->vGetBoundingRect_424FD0(&objRect, 1);

                                            if (PSX_Rects_overlap_no_adjustment(&objRect, &bOurRect))
                                            {
                                                if (pObj->VTakeDamage_408730(this))
                                                {
                                                    bKilledTarget = true;
                                                    SFX_Play_46FA90(64u, 0);
                                                    if (pObj->field_4_typeId == Types::eAbe_69)
                                                    {
                                                        Abe_SFX_457EC0(9u, 0, 0, sActiveHero_5C1B68);
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }

                    if (bKillSpecific)
                    {
                        break;
                    }

                    if (bKilledTarget)
                    {
                        break;
                    }

                    if (list_idx >= gBaseAliveGameObjects_5C1B7C->Size())
                    {
                        break;
                    }

                    pObj = gBaseAliveGameObjects_5C1B7C->ItemAt(list_idx++);
                } while (pObj);
            }
        }
    }
}

__int16 Scrab::FindAbeOrMud_4A4FD0()
{
    if (CanSeeAbe_4A51A0(sActiveHero_5C1B68) && 
        sActiveHero_5C1B68->field_10C_health > FP_FromInteger(0) && 
        sActiveHero_5C1B68->field_CC_sprite_scale == field_CC_sprite_scale && 
        !sActiveHero_5C1B68->field_114_flags.Get(Flags_114::e114_Bit8_bInvisible))
    {
        if (!WallHit_408750(field_CC_sprite_scale * FP_FromInteger(45), sActiveHero_5C1B68->field_B8_xpos - field_B8_xpos))
        {
            field_120_obj_id = sActiveHero_5C1B68->field_8_object_id;
            return TRUE;
        }
    }

    for (int i = 0; i < gBaseGameObject_list_BB47C4->Size(); i++)
    {
        BaseGameObject* pObj = gBaseGameObject_list_BB47C4->ItemAt(i);
        if (!pObj)
        {
            break;
        }

        if (pObj->field_6_flags.Get(BaseGameObject::eIsBaseAliveGameObject))
        {
            auto pAliveObj = static_cast<BaseAliveGameObject*>(pObj);
            if ((pAliveObj->field_4_typeId == Types::eMudokon2_81 ||
                pAliveObj->field_4_typeId == Types::eMudokon_110 ||
                pAliveObj->field_4_typeId == Types::eType_127 ||
                pAliveObj->field_4_typeId == Types::eScrab_112)  &&
                (pAliveObj->field_4_typeId != Types::eScrab_112 || pAliveObj->field_114_flags.Get(Flags_114::e114_Bit4_bPossesed)) &&
                CanSeeAbe_4A51A0(pAliveObj) &&
                pAliveObj->field_10C_health > FP_FromInteger(0) &&
                pAliveObj->field_CC_sprite_scale == field_CC_sprite_scale)
            {
                if (!WallHit_408750(field_CC_sprite_scale * FP_FromInteger(45), pAliveObj->field_B8_xpos - field_B8_xpos))
                {
                    field_120_obj_id = pAliveObj->field_8_object_id;
                    return TRUE;
                }
            }
        }
    }
    return FALSE;
}

__int16 Scrab::CanSeeAbe_4A51A0(BaseAliveGameObject* pObj)
{
    if (pObj->field_CC_sprite_scale != field_CC_sprite_scale)
    {
        return 0;
    }

    if (pObj == sActiveHero_5C1B68)
    {
        if (sActiveHero_5C1B68->field_106_current_motion == eAbeStates::State_67_LedgeHang_454E20 || 
            sActiveHero_5C1B68->field_106_current_motion == eAbeStates::State_69_LedgeHangWobble_454EF0)
        {
            return vOnSameYLevel_425520(pObj);
        }
    }

    if (pObj->field_BC_ypos <= (field_BC_ypos - (field_CC_sprite_scale * FP_FromInteger(45))) || !LineOfSightTo_4A52D0(this, pObj))
    {
        return 0;
    }

    if (vOnSameYLevel_425520(pObj))
    {
        FP offX = {};
        if (field_20_animation.field_4_flags.Get(AnimFlags::eBit5_FlipX))
        {
            offX = -ScaleToGridSize_4498B0(field_CC_sprite_scale);
        }
        else
        {
            offX = ScaleToGridSize_4498B0(field_CC_sprite_scale);
        }

        if (WallHit_408750(field_CC_sprite_scale * FP_FromInteger(45), offX))
        {
            return 0;
        }
    }

    return 1;
}


BOOL Scrab::LineOfSightTo_4A52D0(Scrab* pThis, BaseAliveGameObject* pObj)
{
    PSX_RECT objRect = {};
    pObj->vGetBoundingRect_424FD0(&objRect, 1);
   
    PSX_RECT bRect = {};
    pThis->vGetBoundingRect_424FD0(&bRect, 1);

    PathLine* pLine = nullptr;
    FP hitX = {};
    FP hitY = {};
    return sCollisions_DArray_5C1128->Raycast_417A60(
        pThis->field_B8_xpos,
        FP_FromInteger((bRect.y + bRect.h) / 2),
        pObj->field_B8_xpos,
        FP_FromInteger((objRect.y + objRect.h) / 2),
        &pLine,
        &hitX,
        &hitY,
        (pThis->field_D6_scale != 0 ? 1 : 16) | (pThis->field_D6_scale != 0 ? 6 : 0x60) | (pThis->field_D6_scale != 0 ? 8 : 0x80)) != 1;
}


Scrab* Scrab::FindScrabToFight_4A4E20()
{
    Scrab* pScrabIAmFightingAlready = nullptr;
    Scrab* pScrabNotInAFight = nullptr;
    Scrab* pScrabInFightWithSomeoneElse = nullptr;

    for (int i = 0; i < gBaseGameObject_list_BB47C4->Size(); i++)
    {
        BaseGameObject* pObj = gBaseGameObject_list_BB47C4->ItemAt(i);
        if (!pObj)
        {
            break;
        }

        if (pObj->field_4_typeId == Types::eScrab_112)
        {
            auto pScrab = static_cast<Scrab*>(pObj);

            if (pScrab != this &&
                !pScrab->field_114_flags.Get(Flags_114::e114_Bit4_bPossesed) && 
                !BrainIs(&Scrab::AI_Death_3_4A62B0))
            {
                if (vOnSameYLevel_425520(pScrab))
                {
                    if (!WallHit_408750(field_CC_sprite_scale * FP_FromInteger(45), pScrab->field_B8_xpos - field_B8_xpos) &&
                        gMap_5C3030.Is_Point_In_Current_Camera_4810D0(
                            pScrab->field_C2_lvl_number,
                            pScrab->field_C0_path_number,
                            pScrab->field_B8_xpos,
                            pScrab->field_BC_ypos, 0) &&
                        gMap_5C3030.Is_Point_In_Current_Camera_4810D0(
                            field_C2_lvl_number,
                            field_C0_path_number,
                            field_B8_xpos,
                            field_BC_ypos, 0))
                    {
                        if (pScrab->field_124_fight_target_obj_id == -1)
                        {
                            pScrabNotInAFight = pScrab;
                        }
                        else
                        {
                            if (pScrab->field_124_fight_target_obj_id == field_8_object_id)
                            {
                                pScrabIAmFightingAlready = pScrab;
                            }
                            else
                            {
                                pScrabInFightWithSomeoneElse = pScrab;
                            }
                        }
                    }
                }
            }
        }
    }

    if (pScrabIAmFightingAlready)
    {
        return pScrabIAmFightingAlready;
    }

    if (pScrabNotInAFight)
    {
        return pScrabNotInAFight;
    }

    // This can be nullptr
    return pScrabInFightWithSomeoneElse;
}

__int16 Scrab::Handle_SlamDoor_or_EnemyStopper_4A4830(FP velX, __int16 bCheckLeftRightBounds)
{
    if (velX < FP_FromInteger(0))
    {
        velX = -velX;
    }

    FP gridSize = ScaleToGridSize_4498B0(field_CC_sprite_scale);
    if (velX > FP_FromInteger(5))
    {
        gridSize = (gridSize * FP_FromInteger(2));
    }

    short objectType = 0;
    Path_EnemyStopper::StopDirection stopDirection = Path_EnemyStopper::StopDirection::Both_2;
    if (field_20_animation.field_4_flags.Get(AnimFlags::eBit5_FlipX))
    {
        objectType = TlvTypes::ScrabLeftBound_43;
        stopDirection = Path_EnemyStopper::StopDirection::Left_0;
        gridSize = -gridSize;
    }
    else
    {
        objectType = TlvTypes::ScrabRightBound_44;
        stopDirection = Path_EnemyStopper::StopDirection::Right_1;
    }

    if (WallHit_408750(field_CC_sprite_scale * FP_FromInteger(45), gridSize * FP_FromInteger(1)))
    {
        return 1;
    }

    field_FC_pPathTLV = sPath_dword_BB47C0->TLV_Get_At_4DB4B0(
        FP_GetExponent(field_B8_xpos),
        FP_GetExponent(FP_Abs(field_BC_ypos)),
        FP_GetExponent(field_B8_xpos + gridSize),
        FP_GetExponent(field_BC_ypos - ScaleToGridSize_4498B0(field_CC_sprite_scale)),
        TlvTypes::SlamDoor_85);

    auto pSlamDoorTlv = static_cast<Path_SlamDoor*>(field_FC_pPathTLV);
    if (pSlamDoorTlv && (pSlamDoorTlv->field_10_starts_shut == 1 && !SwitchStates_Get_466020(pSlamDoorTlv->field_14_id) || 
        !pSlamDoorTlv->field_10_starts_shut && 
        SwitchStates_Get_466020(pSlamDoorTlv->field_14_id)))
    {
        return 1;
    }

    field_FC_pPathTLV = sPath_dword_BB47C0->TLV_Get_At_4DB4B0(
        FP_GetExponent(field_B8_xpos),
        FP_GetExponent(field_BC_ypos),
        FP_GetExponent(field_B8_xpos + gridSize),
        FP_GetExponent(field_BC_ypos - ScaleToGridSize_4498B0(field_CC_sprite_scale)),
        TlvTypes::EnemyStopper_47);

    auto pPathEnemyStopper = static_cast<Path_EnemyStopper*>(field_FC_pPathTLV);
    if (pPathEnemyStopper && 
        (pPathEnemyStopper->field_10_stop_direction == stopDirection || pPathEnemyStopper->field_10_stop_direction == Path_EnemyStopper::StopDirection::Both_2) && 
        SwitchStates_Get_466020(pPathEnemyStopper->field_12_id))
    {
        return 1;
    }

    if (bCheckLeftRightBounds)
    {
        if (sPath_dword_BB47C0->TLV_Get_At_4DB4B0(
            FP_GetExponent(field_B8_xpos),
            FP_GetExponent(FP_Abs(field_BC_ypos)),
            FP_GetExponent(field_B8_xpos + gridSize),
            FP_GetExponent(field_BC_ypos - ScaleToGridSize_4498B0(field_CC_sprite_scale)),
            objectType))
        {
            return 1;
        }
    }
    return 0;
}

GameSpeakEvents Scrab::LastSpeak_4A56F0()
{
    if (!gMap_5C3030.Is_Point_In_Current_Camera_4810D0(field_C2_lvl_number, field_C0_path_number, field_B8_xpos, field_BC_ypos, 1))
    {
        return GameSpeakEvents::eNone_m1;
    }

    if (field_17C_last_event == pEventSystem_5BC11C->field_28_last_event_index)
    {
        if (pEventSystem_5BC11C->field_20_last_event == GameSpeakEvents::eNone_m1)
        {
            return GameSpeakEvents::eNone_m1;
        }
        else
        {
            return GameSpeakEvents::eSameAsLast_m2;
        }
    }
    else
    {
        field_17C_last_event = pEventSystem_5BC11C->field_28_last_event_index;
        return pEventSystem_5BC11C->field_20_last_event;
    }
}
