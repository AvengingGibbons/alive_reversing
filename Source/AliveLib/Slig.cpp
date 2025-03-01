#include "stdafx.h"
#include "Slig.hpp"
#include "Function.hpp"
#include "Collisions.hpp"
#include "Shadow.hpp"
#include "ShadowZone.hpp"
#include "stdlib.hpp"
#include "Map.hpp"
#include "PathData.hpp"
#include "Abe.hpp"
#include "MusicController.hpp"
#include "DDCheat.hpp"
#include "BaseGameObject.hpp"
#include "NakedSlig.hpp" // TODO: SFX playing only
#include "SnoozeParticle.hpp"
#include "Events.hpp"
#include "Sfx.hpp"
#include "Blood.hpp"
#include "Gibs.hpp"
#include "Particle.hpp"
#include "Midi.hpp"
#include "ObjectIds.hpp"
#include "PlatformBase.hpp"
#include "ScreenShake.hpp"
#include "ScreenManager.hpp"
#include "LiftPoint.hpp"
#include "Switch.hpp"
#include "SwitchStates.hpp"
#include "Bullet.hpp"
#include "Dove.hpp"
#include "BulletShell.hpp"
#include "GameSpeak.hpp"
#include "Sound.hpp"
#include "VRam.hpp"
#include "Electrocute.hpp"

int CC Animation_OnFrame_Slig_4C0600(void* pObj, signed __int16* pData)
{
    auto pSlig = reinterpret_cast<Slig*>(pObj);
    auto pPoints = reinterpret_cast<PSX_Point*>(pData);

    if (pSlig->field_1C_update_delay)
    {
        return 1;
    }

    BulletType bulletType = BulletType::Type_0;
    if (pSlig->field_114_flags.Get(Flags_114::e114_Bit4_bPossesed) || pSlig->vUnderGlukkonCommand_4B1760())
    {
        bulletType = BulletType::Type_0;
    }
    else
    {
        bulletType = BulletType::Type_2;
    }

    const FP xOff = (pSlig->field_CC_sprite_scale * FP_FromInteger(pPoints->field_0_x));
    const FP yOff = (pSlig->field_CC_sprite_scale * FP_FromInteger(pPoints->field_2_y));

    Bullet* pBullet = nullptr;
    if (pSlig->field_20_animation.field_4_flags.Get(AnimFlags::eBit5_FlipX))
    {
        pBullet = alive_new<Bullet>();
        if (pBullet)
        {
            pBullet->ctor_414540(pSlig, bulletType, pSlig->field_B8_xpos, yOff + pSlig->field_BC_ypos, FP_FromInteger(-640), 0, pSlig->field_CC_sprite_scale, 0);
        }

        New_Particle_426890(pSlig->field_B8_xpos - xOff, yOff + pSlig->field_BC_ypos, 1, pSlig->field_CC_sprite_scale);

        if (pSlig->field_CC_sprite_scale == FP_FromDouble(0.5))
        {
            SFX_Play_46FA90(5u, 85);
        }
        else
        {
            auto pShell = alive_new<BulletShell>();
            if (pShell)
            {
                pShell->ctor_4AD340(pSlig->field_B8_xpos, yOff + pSlig->field_BC_ypos, 0, pSlig->field_CC_sprite_scale);
            }
            SFX_Play_46FA90(5u, 0);
        }
    }
    else
    {
        pBullet = alive_new<Bullet>();
        if (pBullet)
        {
            pBullet->ctor_414540(pSlig, bulletType, pSlig->field_B8_xpos, yOff + pSlig->field_BC_ypos, FP_FromInteger(640), 0, pSlig->field_CC_sprite_scale, 0);
        }

        New_Particle_426890(xOff + pSlig->field_B8_xpos, yOff + pSlig->field_BC_ypos, 0, pSlig->field_CC_sprite_scale);

        if (pSlig->field_CC_sprite_scale == FP_FromDouble(0.5))
        {
            SFX_Play_46FA90(5u, 85);
        }
        else
        {
            auto pShell = alive_new<BulletShell>();
            if (pShell)
            {
                pShell->ctor_4AD340(pSlig->field_B8_xpos, yOff + pSlig->field_BC_ypos, 1, pSlig->field_CC_sprite_scale);
            }
            SFX_Play_46FA90(5u, 0);
        }
    }

    Event_Broadcast_422BC0(kEventShooting, pSlig);
    Event_Broadcast_422BC0(kEventLoudNoise, pSlig);

    pBullet->field_1C_update_delay = 1;
    
    Dove::All_FlyAway_41FA60(0);
    return 1;
}

TintEntry stru_560570[15] =
{
    { 1u, 102u, 127u, 118u },
    { 2u, 102u, 127u, 118u },
    { 3u, 102u, 127u, 118u },
    { 4u, 102u, 127u, 118u },
    { 5u, 102u, 127u, 118u },
    { 6u, 102u, 127u, 118u },
    { 7u, 102u, 127u, 118u },
    { 8u, 102u, 127u, 118u },
    { 9u, 102u, 127u, 118u },
    { 10u, 102u, 127u, 118u },
    { 11u, 102u, 127u, 118u },
    { 12u, 102u, 127u, 118u },
    { 13u, 102u, 127u, 118u },
    { 14u, 102u, 127u, 118u },
    { -1, 102u, 127u, 118u }
};

ALIVE_VAR(1, 0xBAF7E4, int, dword_BAF7E4, 0);
ALIVE_VAR(1, 0xBAF7E8, short, sSligsUnderControlCount_BAF7E8, 0);

const int sSligFrameTables_547318[52] =
{
    135512,
    135804,
    135360,
    135824,
    135440,
    136088,
    135544,
    135512,
    135696,
    135576,
    135916,
    135632,
    135652,
    135768,
    135844,
    135876,
    135512,
    135788,
    135896,
    135936,
    136048,
    135976,
    136132,
    136012,
    136048,
    135976,
    136132,
    136012,
    136048,
    135976,
    136132,
    136012,
    33552,
    33448,
    33184,
    33228,
    33348,
    33348,
    30560,
    30592,
    30628,
    9204,
    9208,
    9260,
    13016,
    12612,
    23048,
    23072,
    23200,
    23148,
    23096,
    12660
};

const TSligMotionFn sSlig_motion_table_5604A0[52] =
{
    &Slig::M_StandIdle_0_4B4EC0,
    &Slig::M_StandToWalk_1_4B5F70,
    &Slig::M_Walking_2_4B5BC0,
    &Slig::M_StandToRun_3_4B62F0,
    &Slig::M_Running_4_4B6000,
    &Slig::M_TurnAroundStanding_5_4B6390,
    &Slig::M_Shoot_6_4B55A0,
    &Slig::M_Falling_7_4B42D0,
    &Slig::M_SlidingToStand_8_4B6520,
    &Slig::M_SlidingTurn_9_4B6680,
    &Slig::M_SlidingTurnToWalk_10_4B6800,
    &Slig::M_SlidingTurnToRun_11_4B6850,
    &Slig::M_ReloadGun_12_4B5530,
    &Slig::M_ShootToStand_13_4B5580,
    &Slig::M_SteppingToStand_14_4B8480,
    &Slig::M_StandingToStep_15_4B83B0,
    &Slig::M_DepossessingAbort_16_4B8250,
    &Slig::M_GameSpeak_17_4B5290,
    &Slig::M_WalkToStand_18_4B5FC0,
    &Slig::M_Recoil_19_4B8270,
    &Slig::M_SpeakHereBoy_20_4B5330,
    &Slig::M_SpeakHi_21_4B53D0,
    &Slig::M_SpeakFreeze_22_4B53F0,
    &Slig::M_SpeakGitIm_23_4B5410,
    &Slig::M_SpeakLaugh_24_4B5430,
    &Slig::M_SpeakBullShit1_25_4B5450,
    &Slig::M_SpeakLookOut_26_4B5470,
    &Slig::M_SpeakBullShit2_27_4B5490,
    &Slig::M_SpeakPanic_28_4B54B0,
    &Slig::M_SpeakWhat_29_4B54D0,
    &Slig::M_SpeakAIFreeze_30_4B54F0,
    &Slig::M_Blurgh_31_4B5510,
    &Slig::M_Sleeping_32_4B89A0,
    &Slig::M_SleepingToStand_33_4B8C50,
    &Slig::M_Knockback_34_4B68A0,
    &Slig::M_KnockbackToStand_35_4B6A30,
    &Slig::M_Depossessing_36_4B7F30,
    &Slig::M_Possess_37_4B72C0,
    &Slig::M_OutToFall_38_4B4570,
    &Slig::M_FallingInitiate_39_4B4640,
    &Slig::M_LandingSoft_40_4B4530,
    &Slig::M_LandingFatal_41_4B4680,
    &Slig::M_ShootZ_42_4B7560,
    &Slig::M_ShootZtoStand_43_4B77E0,
    &Slig::M_Smash_44_4B6B90,
    &Slig::M_PullLever_45_4B8950,
    &Slig::M_LiftGrip_46_4B3700,
    &Slig::M_LiftUngrip_47_4B3820,
    &Slig::M_LiftGripping_48_4B3850,
    &Slig::M_LiftUp_49_4B3930,
    &Slig::M_LiftDown_50_4B3960,
    &Slig::M_Beat_51_4B6C00
};

const TSligAIFn sSlig_ai_table_5605AC[36] =
{
    &Slig::AI_Death_0_4BBFB0,
    &Slig::AI_ReturnControlToAbeAndDie_1_4BC410,
    &Slig::AI_Possessed_2_4BBCF0,
    &Slig::AI_DeathDropDeath_3_4BC1E0,
    &Slig::AI_ListeningToGlukkon_4_4B9D20,
    &Slig::AI_Empty_5_4B3220,
    &Slig::AI_Empty_6_4B3420,
    &Slig::AI_SpottedEnemy_7_4B3240,
    &Slig::AI_Empty_8_4B3120,
    &Slig::AI_Empty_9_4B3440,
    &Slig::AI_EnemyDead_10_4B3460,
    &Slig::AI_KilledEnemy_10_4B35C0,
    &Slig::AI_PanicTurning_12_4BC490,
    &Slig::AI_PanicRunning_13_4BC780,
    &Slig::AI_PanicYelling_14_4BCA70,
    &Slig::AI_Idle_15_4BD800,
    &Slig::AI_StopChasing_16_4BCE30,
    &Slig::AI_Chasing2_17_4BCBD0,
    &Slig::AI_Chasing1_18_4BCEB0,
    &Slig::AI_Turning_19_4BDDD0,
    &Slig::AI_StoppingNextToMudokon_20_4BF1E0,
    &Slig::AI_Walking_21_4BE0C0,
    &Slig::AI_GetAlertedTurn_22_4BE990,
    &Slig::AI_GetAlerted_23_4BEC40,
    &Slig::AI_BeatingUp_24_4BF2B0,
    &Slig::AI_DiscussionWhat_25_4BF380,
    &Slig::AI_Empty_26_4BF620,
    &Slig::AI_Empty_27_4BF600,
    &Slig::AI_ShootingFromBackground_28_4BFA70,
    &Slig::AI_Shooting_29_4BF750,
    &Slig::AI_SpottedEnemyFromBackground_30_4BFA30,
    &Slig::AI_WakingUp_31_4B9390,
    &Slig::AI_Inactive_32_4B9430,
    &Slig::AI_Paused_33_4B8DD0,
    &Slig::AI_Sleeping_34_4B9170,
    &Slig::AI_GameEnder_35_4BF640
};

static AIFunctionData<TSligAIFn> sSligAITable[36] =
{
    { &Slig::AI_Death_0_4BBFB0,  0x40128F, "AI_Death_0", },
    { &Slig::AI_ReturnControlToAbeAndDie_1_4BC410,  0x40371F, "AI_ReturnControlToAbeAndDie_1", },
    { &Slig::AI_Possessed_2_4BBCF0,  0x40458E, "AI_Possessed_2", },
    { &Slig::AI_DeathDropDeath_3_4BC1E0,  0x401EC9, "AI_DeathDropDeath_3", },
    { &Slig::AI_ListeningToGlukkon_4_4B9D20,  0x4015A0, "AI_ListeningToGlukkon_4", },
    { &Slig::AI_Empty_5_4B3220,  0x4B3220, "AI_Empty_5", },
    { &Slig::AI_Empty_6_4B3420,  0x4B3420, "AI_Empty_6", },
    { &Slig::AI_SpottedEnemy_7_4B3240,  0x4032AB, "AI_SpottedEnemy_7", },
    { &Slig::AI_Empty_8_4B3120,  0x4B3120, "AI_Empty_8", },
    { &Slig::AI_Empty_9_4B3440,  0x4B3440, "AI_Empty_9", },
    { &Slig::AI_EnemyDead_10_4B3460, 0x401E60, "AI_EnemyDead_10", },
    { &Slig::AI_KilledEnemy_10_4B35C0, 0x40120D, "AI_KilledEnemy_10", },
    { &Slig::AI_PanicTurning_12_4BC490, 0x40479B, "AI_PanicTurning_12", },
    { &Slig::AI_PanicRunning_13_4BC780, 0x40144C, "AI_PanicRunning_13", },
    { &Slig::AI_PanicYelling_14_4BCA70, 0x403364, "AI_PanicYelling_14", },
    { &Slig::AI_Idle_15_4BD800, 0x403F85, "AI_Idle_15", },
    { &Slig::AI_StopChasing_16_4BCE30, 0x4021B2, "AI_StopChasing_16", },
    { &Slig::AI_Chasing2_17_4BCBD0, 0x403BCA, "AI_Chasing2_17", },
    { &Slig::AI_Chasing1_18_4BCEB0, 0x403E36, "AI_Chasing1_18", },
    { &Slig::AI_Turning_19_4BDDD0, 0x403ABC, "AI_Turning_19", },
    { &Slig::AI_StoppingNextToMudokon_20_4BF1E0, 0x4020C2, "AI_StoppingNextToMudokon_20", },
    { &Slig::AI_Walking_21_4BE0C0, 0x402A59, "AI_Walking_21", },
    { &Slig::AI_GetAlertedTurn_22_4BE990, 0x40266C, "AI_GetAlertedTurn_22", },
    { &Slig::AI_GetAlerted_23_4BEC40, 0x4020D1, "AI_GetAlerted_23", },
    { &Slig::AI_BeatingUp_24_4BF2B0, 0x403B25, "AI_BeatingUp_24", },
    { &Slig::AI_DiscussionWhat_25_4BF380, 0x403CE2, "AI_DiscussionWhat_25", },
    { &Slig::AI_Empty_26_4BF620, 0x4BF620, "AI_Empty_26", },
    { &Slig::AI_Empty_27_4BF600, 0x4BF600, "AI_Empty_27", },
    { &Slig::AI_ShootingFromBackground_28_4BFA70, 0x4025B3, "AI_ShootingFromBackground_28", },
    { &Slig::AI_Shooting_29_4BF750, 0x40308F, "AI_Shooting_29", },
    { &Slig::AI_SpottedEnemyFromBackground_30_4BFA30, 0x403215, "AI_SpottedEnemyFromBackground_30", },
    { &Slig::AI_WakingUp_31_4B9390, 0x403E0E, "AI_WakingUp_31", },
    { &Slig::AI_Inactive_32_4B9430, 0x4038CD, "AI_Inactive_32", },
    { &Slig::AI_Paused_33_4B8DD0, 0x40346D, "AI_Paused_33", },
    { &Slig::AI_Sleeping_34_4B9170, 0x402B17, "AI_Sleeping_34", },
    { &Slig::AI_GameEnder_35_4BF640, 0x4022B1, "AI_GameEnder_35" },
};

void Slig::SetBrain(TSligAIFn fn)
{
    ::SetBrain(fn, field_154_brain_state, sSligAITable);
}

bool Slig::BrainIs(TSligAIFn fn)
{
    return ::BrainIs(fn, field_154_brain_state, sSligAITable);
}

Slig* Slig::ctor_4B1370(Path_Slig* pTlv, int tlvInfo)
{
    ctor_408240(17);

    field_160 = -1;
    field_176 = -1;
    field_174 = 0;
    
    SetVTable(this, 0x547460);

    if (tlvInfo != 0xFFFF)
    {
        field_C_objectId = tlvInfo;
    }

    field_10_resources_array.SetAt(0, ResourceManager::GetLoadedResource_49C2A0(ResourceManager::Resource_Animation, 412, 1, 0));
    Animation_Init_424E10(135512, 160, 68, field_10_resources_array.ItemAt(0), 1, 1);

    field_4_typeId = Types::eSlig_125;

    field_114_flags.Clear(Flags_114::e114_Bit4_bPossesed);
    field_114_flags.Clear(Flags_114::e114_Bit9);
    field_114_flags.Set(Flags_114::e114_Bit3_Can_Be_Possessed);
    field_114_flags.Set(Flags_114::e114_Bit6_SetOffExplosives);

    field_292 &= ~1u;

    dword_BAF7E4 = 0;

    field_216.Clear(Flags_216::eBit1_FollowGlukkon);
    field_216.Clear(Flags_216::eBit3);
    field_216.Clear(Flags_216::eBit4_HeardGlukkon);


    field_120_timer = 0;
    field_11E = 45 * (Math_NextRandom() % 5 - 2);
    field_108_next_motion = eSligMotions::M_StandIdle_0_4B4EC0;
    field_124 = 0;
    field_150 = 0;
    field_14C = 0;
    field_FC_pPathTLV = pTlv;
    
    field_218_tlv_data = *pTlv;

    field_110_id = -1;
    
    field_106_current_motion = eSligMotions::M_Falling_7_4B42D0;

    field_124 = 0;
    field_B8_xpos = FP_FromInteger(pTlv->field_8_top_left.field_0_x);
    field_BC_ypos = FP_FromInteger(pTlv->field_8_top_left.field_2_y);
    field_130 = FP_FromInteger(0);
    field_118_tlvInfo = tlvInfo;
    field_128_input = 0;
    field_158 = 0;
    field_15A = 0;
    field_15C = 0;
    field_136_shot_motion = -1;
    field_208_glukkon_obj_id = 0;
    field_20C_state_after_speak = -1;
    field_20E = 0;
    field_210 = 0;
    field_134_res_idx = 0;

    field_20_animation.field_1C_fn_ptr_array = kSlig_Anim_Frame_Fns_55EFAC;

    if (pTlv->field_10_scale)
    {
        if (pTlv->field_10_scale == 1)
        {
            field_CC_sprite_scale = FP_FromDouble(0.5);
            field_20_animation.field_C_render_layer = 14;
            field_D6_scale = 0;
        }
    }
    else
    {
        field_CC_sprite_scale = FP_FromInteger(1);
        field_20_animation.field_C_render_layer = 33;
        field_D6_scale = 1;
    }

    SetBaseAnimPaletteTint_425690(&stru_560570[0], gMap_5C3030.sCurrentLevelId_5C3030, 412);

    FP hitX = {};
    FP hitY = {};
    if (sCollisions_DArray_5C1128->Raycast_417A60(
        field_B8_xpos,
        field_BC_ypos,
        field_B8_xpos,
        field_BC_ypos + FP_FromInteger(24),
        &field_100_pCollisionLine,
        &hitX,
        &hitY,
        field_D6_scale != 0 ? 1 : 16) == 1)
    {
        field_106_current_motion = eSligMotions::M_StandIdle_0_4B4EC0;
        field_BC_ypos = hitY;
    }

    MapFollowMe_408D10(TRUE);
    
    Init_4BB0D0();
    
    vStackOnObjectsOfType_425840(Types::eSlig_125);
    
    if (gMap_5C3030.sCurrentLevelId_5C3030 == LevelIds::eBonewerkz_8 && gMap_5C3030.sCurrentPathId_5C3032 == 2 && gMap_5C3030.sCurrentCamId_5C3034 == 5)
    {
        field_DA_xOffset = 0;
    }

    field_DC_bApplyShadows |= 2u;
    field_142 = 0;
    field_140 = 0;

    field_E0_pShadow = alive_new<Shadow>();
    if (field_E0_pShadow)
    {
        field_E0_pShadow->ctor_4AC990();
    }

    return this;
}

BaseGameObject* Slig::VDestructor(signed int flags)
{
    return vdtor_4B1790(flags);
}

void Slig::VUpdate()
{
    vUpdate_4B17C0();
}


void renderWithGlowingEyes(int** ot, BaseAliveGameObject* actor, __int16* pPalAlloc, __int16 palSize, PSX_RECT* palRect,
                            __int16& r, __int16& g, __int16& b,
                            const __int16* eyeColourIndices, __int16 eyeColourIndicesSize)
{
    if (actor->field_20_animation.field_4_flags.Get(AnimFlags::eBit3_Render))
    {
        if (gMap_5C3030.sCurrentPathId_5C3032 == actor->field_C0_path_number &&
            gMap_5C3030.sCurrentLevelId_5C3030 == actor->field_C2_lvl_number &&
            actor->Is_In_Current_Camera_424A70() == CameraPos::eCamCurrent_0)
        {
            actor->field_20_animation.field_14_scale = actor->field_CC_sprite_scale;

            PSX_RECT boundingRect = {};
            actor->vGetBoundingRect_424FD0(&boundingRect, 1);
            __int16 rMod = actor->field_D0_r;
            __int16 gMod = actor->field_D2_g;
            __int16 bMod = actor->field_D4_b;
            ShadowZone::ShadowZones_Calculate_Colour_463CE0(
                FP_GetExponent(actor->field_B8_xpos),
                ( boundingRect.h + boundingRect.y ) / 2,
                actor->field_D6_scale,
                &rMod,
                &gMod,
                &bMod
            );
            if (!actor->field_114_flags.Get(Flags_114::e114_Bit7_Electrocuted))
            {
                if (rMod != r || gMod != g || bMod != b)
                {
                    r = rMod;
                    g = gMod;
                    b = bMod;

                    const FrameInfoHeader *pFrameInfoHeader = actor->field_20_animation.Get_FrameHeader_40B730(0);
                    const BYTE* pAnimData = *actor->field_20_animation.field_20_ppBlock;
                    const DWORD clut_offset = *reinterpret_cast< const DWORD* >( &( pAnimData )[pFrameInfoHeader->field_0_frame_header_offset] );
                    const WORD* pAnimDataWithOffset = reinterpret_cast< const WORD* >( &pAnimData[clut_offset + 4] );
                    for (int i = 0; i < palSize; i++)
                    {
                        __int32 auxPalValue = pAnimDataWithOffset[i] & 0x1F;
                        unsigned __int16 resultR = static_cast< __int16 >( auxPalValue * r ) >> 7;
                        if (resultR > 31)
                        {
                            resultR = 31;
                        }

                        auxPalValue = ( pAnimDataWithOffset[i] >> 5 ) & 0x1F;
                        unsigned __int16 resultG = static_cast< __int16 >( auxPalValue * g ) >> 7;
                        if (resultG > 31)
                        {
                            resultG = 31;
                        }

                        auxPalValue = ( pAnimDataWithOffset[i] >> 10 ) & 0x1F;
                        unsigned __int16 resultB = static_cast< __int16 >( auxPalValue * b ) >> 7;
                        if (resultB > 31)
                        {
                            resultB = 31;
                        }

                        int resultMixed = ( pAnimDataWithOffset[i] & 0x8000 ) | ( ( resultR & 31 ) + 32 * ( resultG & 31 ) + 32 * 32 * ( resultB & 31 ) );
                        if (resultMixed <= 0 && pAnimDataWithOffset[i])
                        {
                            resultMixed = 1;
                        }
                        pPalAlloc[i] = static_cast< WORD >( resultMixed );
                    }
                    for (int i = 0; i < eyeColourIndicesSize; i++)
                    {
                        pPalAlloc[eyeColourIndices[i]] = pAnimDataWithOffset[eyeColourIndices[i]];
                    }
                    Pal_Set_483510(
                        actor->field_20_animation.field_8C_pal_vram_xy,
                        actor->field_20_animation.field_90_pal_depth,
                        reinterpret_cast< const BYTE* >( pPalAlloc ),
                        palRect
                    );
                }
                actor->field_20_animation.field_8_r = 127;
                actor->field_20_animation.field_9_g = 127;
                actor->field_20_animation.field_A_b = 127;
            }

            actor->field_20_animation.vRender_40B820(
                FP_GetExponent(FP_FromInteger(actor->field_DA_xOffset) + actor->field_B8_xpos - pScreenManager_5BB5F4->field_20_pCamPos->field_0_x),
                FP_GetExponent(FP_FromInteger(actor->field_D8_yOffset) + actor->field_BC_ypos - pScreenManager_5BB5F4->field_20_pCamPos->field_4_y),
                ot,
                0,
                0
            );

            PSX_RECT rectToInvalidate = {};
            actor->field_20_animation.Get_Frame_Rect_409E10(&rectToInvalidate);
            pScreenManager_5BB5F4->InvalidateRect_40EC90(
                rectToInvalidate.x,
                rectToInvalidate.y,
                rectToInvalidate.w,
                rectToInvalidate.h, pScreenManager_5BB5F4->field_3A_idx
            );

            if (actor->field_E0_pShadow)
            {
                actor->field_E0_pShadow->Calculate_Position_4ACA50(actor->field_B8_xpos, actor->field_BC_ypos, &rectToInvalidate, actor->field_CC_sprite_scale, actor->field_D6_scale);
                actor->field_E0_pShadow->Render_4ACE60(ot);
            }
        }
    }
}

void Slig::VRender(int** pOrderingTable)
{
    vRender_4B1F80(pOrderingTable);
}

void Slig::vRender_4B1F80(int** ot)
{
    const __int16 eyeIndices[] = { 61, 62 };
    renderWithGlowingEyes(ot, this, &field_178_pPalAlloc[0], ALIVE_COUNTOF(field_178_pPalAlloc),
                        &field_1F8, field_200_red, field_202_green, field_204_blue, &eyeIndices[0], ALIVE_COUNTOF(eyeIndices));
}

void Slig::VScreenChanged()
{
    vScreenChanged_4B1E20();
}

void Slig::VPossessed_408F70()
{
    vPossessed_4B2F10();
}

void Slig::VUnPosses_408F90()
{
    vUnPosses_4B3050();
}

void Slig::VOn_TLV_Collision_4087F0(Path_TLV* pTlv)
{
    vOnTlvCollision_4B2FB0(pTlv);
}

void Slig::VOnTrapDoorOpen()
{
    vOnTrapDoorOpen_4B3690();
}

__int16 Slig::VTakeDamage_408730(BaseGameObject* pFrom)
{
    return vTakeDamage_4B2470(pFrom);
}

__int16 Slig::vIsFacingMe_4254A0(BaseAnimatedWithPhysicsGameObject* pOther)
{
    return vIsFacingMe_4B23D0(pOther);
}

__int16 Slig::vOnSameYLevel_425520(BaseAnimatedWithPhysicsGameObject* pOther)
{
    return vOnSameYLevel_4BB6C0(pOther);
}

int Slig::VGetSaveState(BYTE* pSaveBuffer)
{
    return vGetSaveState_4BFB10(reinterpret_cast<Slig_State*>(pSaveBuffer));
}

int CC Slig::CreateFromSaveState_4B3B50(const BYTE* pBuffer)
{
    auto pState = reinterpret_cast<const Slig_State*>(pBuffer);
    auto pTlv = static_cast<Path_Slig*>(sPath_dword_BB47C0->TLV_From_Offset_Lvl_Cam_4DB770(pState->field_5C_tlvInfo));

    const __int16 disabledResources = pTlv->field_48_disable_resources;

    if (!(disabledResources & 1) && !ResourceManager::GetLoadedResource_49C2A0(ResourceManager::Resource_Animation, kSlgleverResID, 0, 0))
    {
        ResourceManager::LoadResourceFile_49C170("SLGLEVER.BAN", nullptr);
    }

    if (!(disabledResources & 2) && !ResourceManager::GetLoadedResource_49C2A0(ResourceManager::Resource_Animation, kSlgliftResID, 0, 0))
    {
        ResourceManager::LoadResourceFile_49C170("SLGLIFT.BAN", nullptr);
    }

    if (!(disabledResources & 0x40) && !ResourceManager::GetLoadedResource_49C2A0(ResourceManager::Resource_Animation, kSlgsleepResID, 0, 0))
    {
        ResourceManager::LoadResourceFile_49C170("SLGSLEEP.BAN", nullptr);
    }

    if ((disabledResources & 0x80u) == 0 && !ResourceManager::GetLoadedResource_49C2A0(ResourceManager::Resource_Animation, kSlgknfdResID, 0, 0))
    {
        ResourceManager::LoadResourceFile_49C170("SLGKNFD.BAN", nullptr);
    }

    if (!(disabledResources & 0x100) && !ResourceManager::GetLoadedResource_49C2A0(ResourceManager::Resource_Animation, kSlgedgeResID, 0, 0))
    {
        ResourceManager::LoadResourceFile_49C170("SLGEDGE.BAN", nullptr);
    }

    if (!(disabledResources & 0x200) && !ResourceManager::GetLoadedResource_49C2A0(ResourceManager::Resource_Animation, kSlgsmashResID, 0, 0))
    {
        ResourceManager::LoadResourceFile_49C170("SLGSMASH.BAN", nullptr);
    }

    if (!(disabledResources & 0x400) && !ResourceManager::GetLoadedResource_49C2A0(ResourceManager::Resource_Animation, kSlgbeatResID, 0, 0))
    {
        ResourceManager::LoadResourceFile_49C170("SLGBEAT.BAN", nullptr);
    }

    if (!(disabledResources & 4) && !ResourceManager::GetLoadedResource_49C2A0(ResourceManager::Resource_Animation, kSlgzshotResID, 0, 0))
    {
        ResourceManager::LoadResourceFile_49C170("SLIGZ.BND", nullptr);
    }

    if (!ResourceManager::GetLoadedResource_49C2A0(ResourceManager::Resource_Animation, kSlgbasicResID, 0, 0))
    {
        ResourceManager::LoadResourceFile_49C170("SLIG.BND", nullptr);
    }

    if (!ResourceManager::GetLoadedResource_49C2A0(ResourceManager::Resource_Animation, kSligBlowResID, 0, 0))
    {
        ResourceManager::LoadResourceFile_49C170("SLGBLOW.BAN", nullptr);
    }

    if (!ResourceManager::GetLoadedResource_49C2A0(ResourceManager::Resource_Animation, kRockShadowResID, 0, 0))
    {
        ResourceManager::LoadResourceFile_49C170("SHADOW.BAN", nullptr);
    }

    auto pSlig = alive_new<Slig>();
    pSlig->ctor_4B1370(pTlv, pState->field_5C_tlvInfo);

    if (pState->field_40_bActiveChar)
    {
        sControlledCharacter_5C1B8C = pSlig;
        pSlig->field_114_flags.Set(Flags_114::e114_Bit4_bPossesed);
    }

    pSlig->field_FC_pPathTLV = nullptr;
    pSlig->field_100_pCollisionLine = nullptr;
    pSlig->field_B8_xpos = pState->field_4_xpos;
    pSlig->field_BC_ypos = pState->field_8_ypos;
    pSlig->field_C4_velx = pState->field_C_velx;
    pSlig->field_C8_vely = pState->field_10_vely;
    pSlig->field_C0_path_number = pState->field_14_path_number;
    pSlig->field_C2_lvl_number = pState->field_16_lvl_number;
    pSlig->field_CC_sprite_scale = pState->field_18_sprite_scale;

    if (pSlig->field_CC_sprite_scale == FP_FromInteger(1))
    {
        pSlig->field_20_animation.field_C_render_layer = 33;
    }
    else
    {
        pSlig->field_20_animation.field_C_render_layer = 14;
    }

    pSlig->field_D6_scale = pState->field_1C_scale;

    pSlig->field_200_red = pState->field_1E_r;
    pSlig->field_D0_r = pState->field_1E_r;
    pSlig->field_202_green = pState->field_20_g;
    pSlig->field_D2_g = pState->field_20_g;
    pSlig->field_204_blue = pState->field_22_b;
    pSlig->field_D4_b = pState->field_22_b;

    pSlig->field_106_current_motion = pState->field_26;
    BYTE** ppRes = pSlig->ResForMotion_4B1E90(pSlig->field_106_current_motion);
    pSlig->field_20_animation.Set_Animation_Data_409C80(sSligFrameTables_547318[pSlig->field_106_current_motion], ppRes);

    pSlig->field_20_animation.field_92_current_frame = pState->field_28;
    pSlig->field_20_animation.field_E_frame_change_counter = pState->field_2A;

    pSlig->field_6_flags.Set(BaseGameObject::eDrawable, pState->field_2D_bDrawable & 1);

    pSlig->field_20_animation.field_4_flags.Set(AnimFlags::eBit5_FlipX, pState->field_24_bFlipX & 1);
    pSlig->field_20_animation.field_4_flags.Set(AnimFlags::eBit3_Render, pState->field_2C_bRender & 1);

    if (IsLastFrame(&pSlig->field_20_animation))
    {
        pSlig->field_20_animation.field_4_flags.Set(AnimFlags::eBit18_IsLastFrame);
    }

    pSlig->field_10C_health = pState->field_30_health;
    pSlig->field_106_current_motion = pState->field_34_current_motion;
    pSlig->field_108_next_motion = pState->field_36_next_motion;
    pSlig->field_F8_LastLineYPos = FP_FromInteger(pState->field_38_last_line_ypos);

    pSlig->field_114_flags.Set(Flags_114::e114_Bit9);

    pSlig->field_104_collision_line_type = pState->field_3A_collision_line_type;
    pSlig->field_11C_ai_sub_state = pState->field_42;
    pSlig->field_11E = pState->field_44;
    pSlig->field_120_timer = pState->field_48_timer;
    pSlig->field_124 = pState->field_4C;
    pSlig->field_126 = pState->field_4E;

    pSlig->field_128_input = InputObject::Command_To_Raw_45EE40(pState->field_50_input);

    pSlig->field_12C = pState->field_54;
    pSlig->field_130 = pState->field_58;
    pSlig->field_118_tlvInfo = pState->field_5C_tlvInfo;
    pSlig->field_134_res_idx = pState->field_60_res_idx;
    pSlig->field_136_shot_motion = pState->field_62;
    
    pSlig->field_138_zone_rect = pState->field_64_zone_rect;

    pSlig->field_140 = pState->field_6C;
    pSlig->field_142 = pState->field_6E;
    pSlig->field_144 = pState->field_70;

    pSlig->field_146_level = pState->field_72_level;
    pSlig->field_148_path = pState->field_74_path;
    pSlig->field_14A_camera = pState->field_76_camera;

    pSlig->field_14C = pState->field_78;
    pSlig->field_150 = pState->field_7C;
    
    pSlig->SetBrain(sSlig_ai_table_5605AC[pState->field_80_brain_state_idx]);
    
    dword_BAF7E4 = pState->field_88;

    pSlig->field_158 = static_cast<short>(pState->field_8C); // TODO: Wrong type ??
    pSlig->field_15C = pState->field_90;
    pSlig->field_15E = pState->field_92;
    pSlig->field_208_glukkon_obj_id = pState->field_94_glukkon_id;
    pSlig->field_20C_state_after_speak = pState->field_98;
    pSlig->field_20E = pState->field_9A;

    pSlig->field_210 = pState->field_9C;
    pSlig->field_212_next_command_arg1 = pState->field_9E;

    pSlig->field_214_cmd_idx = pState->field_A0;

    pSlig->field_216.Set(Flags_216::eBit1_FollowGlukkon, pState->field_A2.Get(Slig_State::eBit2));
    pSlig->field_216.Set(Flags_216::eBit2, pState->field_A2.Get(Slig_State::eBit3));
    pSlig->field_216.Set(Flags_216::eBit3, pState->field_A2.Get(Slig_State::eBit4));
    pSlig->field_216.Set(Flags_216::eBit4_HeardGlukkon, pState->field_A2.Get(Slig_State::eBit5));

    sSligsUnderControlCount_BAF7E8 = 0;
    return sizeof(Slig_State);
}

void Slig::M_StandIdle_0_4B4EC0()
{
    FP xOff = {};
    if (field_20_animation.field_4_flags.Get(AnimFlags::eBit5_FlipX))
    {
        xOff = FP_FromInteger(10) * field_CC_sprite_scale;
    }
    else
    {
        xOff = FP_FromInteger(-10) * field_CC_sprite_scale;
    }

    PathLine* pLine = nullptr;
    FP hitX = {};
    FP hitY = {};
    if (!sCollisions_DArray_5C1128->Raycast_417A60(
        xOff + field_B8_xpos,
        field_BC_ypos - FP_FromInteger(10),
        xOff + field_B8_xpos,
        field_BC_ypos + FP_FromInteger(10),
        &pLine,
        &hitX,
        &hitY,
        field_D6_scale != 0 ? 1 : 16))
    {
        VOnTrapDoorOpen();
        field_106_current_motion = eSligMotions::M_FallingInitiate_39_4B4640;
        field_F8_LastLineYPos = field_BC_ypos;
        field_130 = FP_FromDouble(0.3);
        return;
    }

    if (!MainMovement_4B4720())
    {
        if (sControlledCharacter_5C1B8C == this && field_10C_health > FP_FromInteger(0))
        {
            if (Input_IsChanting_45F260())
            {
                if (!(field_292 & 1))
                {
                    field_106_current_motion = eSligMotions::M_Depossessing_36_4B7F30;
                    field_12C = sGnFrame_5C1B84 + 30;
                    SFX_Play_46FA90(17, 0);
                    return;
                }
            }
            else
            {
                const auto inputHeld = sInputObject_5BD4E0.field_0_pads[sCurrentControllerIndex_5C1BBE].field_C_held;
                const auto gameSpeakCmds =
                    InputCommands::eChant |
                    InputCommands::eGameSpeak8 |
                    InputCommands::eGameSpeak7 |
                    InputCommands::eGameSpeak6 |
                    InputCommands::eGameSpeak5 |
                    InputCommands::eGameSpeak4 |
                    InputCommands::eGameSpeak3 |
                    InputCommands::eGameSpeak2 |
                    InputCommands::eGameSpeak1;

                if (inputHeld & gameSpeakCmds)
                {
                    field_128_input = inputHeld;
                    field_106_current_motion = eSligMotions::M_GameSpeak_17_4B5290;
                    return;
                }
            }
        }

        if (static_cast<int>(sGnFrame_5C1B84) >= field_12C)
        {
            field_106_current_motion = eSligMotions::M_ReloadGun_12_4B5530;
        }
    }
}

void Slig::M_StandToWalk_1_4B5F70()
{
    field_128_input |= sInputObject_5BD4E0.field_0_pads[sCurrentControllerIndex_5C1BBE].field_C_held;
    if (field_20_animation.field_4_flags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        field_106_current_motion = eSligMotions::M_Walking_2_4B5BC0;
    }
    MoveOnLine_4B4C40();
}

void Slig::M_Walking_2_4B5BC0()
{
    if (gMap_5C3030.GetDirection_4811A0(
        field_C2_lvl_number,
        field_C0_path_number,
        field_B8_xpos,
        field_BC_ypos) >= CameraPos::eCamCurrent_0 && MusicController::sub_47FDA0(0, 0, 0) <= 4)
    {
        MusicController::sub_47FD60(4, this, 0, 0);
    }

    field_128_input |= sInputObject_5BD4E0.field_0_pads[sCurrentControllerIndex_5C1BBE].field_C_held;

    if (field_20_animation.field_4_flags.Get(AnimFlags::eBit5_FlipX))
    {
        field_C4_velx = -(ScaleToGridSize_4498B0(field_CC_sprite_scale) / FP_FromInteger(9));
    }
    else
    {
        field_C4_velx = (ScaleToGridSize_4498B0(field_CC_sprite_scale) / FP_FromInteger(9));
    }

    if (WallHit_408750(field_CC_sprite_scale * FP_FromInteger(45), field_C4_velx * FP_FromInteger(2)))
    {
        ToStand_4B4A20();
        return;
    }
    
    MoveOnLine_4B4C40();

    if (field_106_current_motion == eSligMotions::M_Walking_2_4B5BC0)
    {
        if (field_20_animation.field_92_current_frame == 5 || field_20_animation.field_92_current_frame == 14)
        {
            Slig_SoundEffect_4BFFE0(2, this);

            if (!field_126)
            {
                field_126 = 1;
                MapFollowMe_408D10(TRUE);
            }

            if (sControlledCharacter_5C1B8C == this && field_10C_health > FP_FromInteger(0))
            {
                if (sInputKey_Run_5550E8 & sInputObject_5BD4E0.field_0_pads[sCurrentControllerIndex_5C1BBE].field_0_pressed)
                {
                    field_124 = 1;
                    field_F4 = 4;
                    field_F6_anim_frame = (field_20_animation.field_92_current_frame - 5) != 0 ? 13 : 5;
                    if (field_20_animation.field_4_flags.Get(AnimFlags::eBit5_FlipX))
                    {
                        field_128_input = 0;
                        field_C4_velx = -(ScaleToGridSize_4498B0(field_CC_sprite_scale) / FP_FromInteger(4));
                        return;
                    }
                    field_C4_velx = ScaleToGridSize_4498B0(field_CC_sprite_scale) / FP_FromInteger(4);
                }
                field_128_input = 0;
            }
        }
        else if (field_20_animation.field_92_current_frame == 11)
        {
            FP gridSize = {};
            if (field_20_animation.field_4_flags.Get(AnimFlags::eBit5_FlipX))
            {
                gridSize = -ScaleToGridSize_4498B0(field_CC_sprite_scale);
            }
            else
            {
                gridSize = ScaleToGridSize_4498B0(field_CC_sprite_scale);
            }

            if (WallHit_408750(field_CC_sprite_scale * FP_FromInteger(45), gridSize * FP_FromInteger(2)))
            {
                field_106_current_motion = eSligMotions::M_WalkToStand_18_4B5FC0;
            }
            else if (sControlledCharacter_5C1B8C == this && field_10C_health > FP_FromInteger(0))
            {
                PlayerControlStopWalkingIfRequired_4B8540();
            }
            else
            {
                if (field_108_next_motion == eSligMotions::M_Shoot_6_4B55A0)
                {
                    field_106_current_motion = eSligMotions::M_WalkToStand_18_4B5FC0;
                    field_12C = sGnFrame_5C1B84 + 60;
                }
                else if (field_108_next_motion != -1)
                {
                    field_106_current_motion = eSligMotions::M_WalkToStand_18_4B5FC0;
                }
            }
        }
        else
        {
            field_126 = 0;
        }
    }
}

void Slig::M_StandToRun_3_4B62F0()
{
    field_128_input |= sInputObject_5BD4E0.field_0_pads[sCurrentControllerIndex_5C1BBE].field_C_held;
    if (field_20_animation.field_4_flags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        field_106_current_motion = eSligMotions::M_Running_4_4B6000;
    }

    Event_Broadcast_422BC0(kEventNoise, this);

    if (WallHit_408750(field_CC_sprite_scale * FP_FromInteger(45), field_C4_velx))
    {
        FallKnockBackOrSmash_4B4A90();
    }
    else
    {
        MoveOnLine_4B4C40();
    }
}

void Slig::M_Running_4_4B6000()
{
    if (field_20_animation.field_4_flags.Get(AnimFlags::eBit5_FlipX))
    {
        field_C4_velx = -(ScaleToGridSize_4498B0(field_CC_sprite_scale) / FP_FromInteger(4));
    }
    else
    {
        field_C4_velx = (ScaleToGridSize_4498B0(field_CC_sprite_scale) / FP_FromInteger(4));
    }

    if (gMap_5C3030.GetDirection_4811A0(field_C2_lvl_number, field_C0_path_number, field_B8_xpos, field_BC_ypos) >= CameraPos::eCamCurrent_0 && 
        MusicController::sub_47FDA0(0, 0, 0) != 9)
    {
        MusicController::sub_47FD60(8, this, 0, 0);
    }
    
    field_128_input |= sInputObject_5BD4E0.field_0_pads[sCurrentControllerIndex_5C1BBE].field_C_held;

    Event_Broadcast_422BC0(kEventNoise, this);

    if (WallHit_408750(field_CC_sprite_scale * FP_FromInteger(45), field_C4_velx))
    {
        FallKnockBackOrSmash_4B4A90();
    }
    else
    {
        MoveOnLine_4B4C40();

        if (field_106_current_motion == eSligMotions::M_Running_4_4B6000)
        {
            if (field_20_animation.field_92_current_frame == 4 || field_20_animation.field_92_current_frame == 12)
            {

                Slig_SoundEffect_4BFFE0(3, this);

                if (field_126 == 0)
                {
                    field_126 = 1;
                    MapFollowMe_408D10(TRUE);
                }

                if (sControlledCharacter_5C1B8C == this && field_10C_health > FP_FromInteger(0))
                {
                    if (field_20_animation.field_92_current_frame == 4)
                    {
                        PlayerControlRunningSlideStopOrTurn1_4B85D0();
                    }
                    else
                    {
                        PlayerControlRunningSlideStopOrTurn1_4B8790();
                    }
                }
                else
                {
                    if (field_108_next_motion == eSligMotions::M_Walking_2_4B5BC0)
                    {
                        field_106_current_motion = eSligMotions::M_Walking_2_4B5BC0;
                        field_108_next_motion = -1;
                        if (field_20_animation.field_4_flags.Get(AnimFlags::eBit5_FlipX))
                        {
                            field_C4_velx = -(ScaleToGridSize_4498B0(field_CC_sprite_scale) / FP_FromInteger(9));
                        }
                        else
                        {
                            field_C4_velx = (ScaleToGridSize_4498B0(field_CC_sprite_scale) / FP_FromInteger(9));
                        }
                    }
                    else if (field_108_next_motion == eSligMotions::M_Shoot_6_4B55A0)
                    {
                        field_106_current_motion = eSligMotions::M_Shoot_6_4B55A0;
                        field_108_next_motion = -1;
                        field_12C = sGnFrame_5C1B84 + 60;
                    }
                    else if (field_108_next_motion != -1)
                    {
                        if (field_C4_velx >= FP_FromInteger(0))
                        {
                            field_C4_velx = (field_CC_sprite_scale * FP_FromDouble(13.2));
                        }
                        else
                        {
                            field_C4_velx = (field_CC_sprite_scale * FP_FromDouble(-13.2));
                        }

                        field_106_current_motion = eSligMotions::M_SlidingToStand_8_4B6520;
                    }
                }
            }
            else
            {
                field_126 = 0;
            }
        }
    }
}

void Slig::M_TurnAroundStanding_5_4B6390()
{
    if (gMap_5C3030.GetDirection_4811A0(
        field_C2_lvl_number,
        field_C0_path_number,
        field_B8_xpos,
        field_BC_ypos) >= CameraPos::eCamCurrent_0 && MusicController::sub_47FDA0(0, 0, 0) <= 4)
    {
        MusicController::sub_47FD60(4, this, 0, 0);
    }

    Slig_SoundEffect_4BFFE0(1, this);

    if (field_20_animation.field_4_flags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        field_20_animation.field_4_flags.Toggle(AnimFlags::eBit5_FlipX);
        ToStand_4B4A20();
    }
}

void Slig::M_Shoot_6_4B55A0()
{
    if (field_20_animation.field_4_flags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        if (sControlledCharacter_5C1B8C == this && field_10C_health > FP_FromInteger(0))
        {
            if (sInputObject_5BD4E0.isPressed(sInputKey_ThrowItem_5550F4))
            {
                const FP k45Scaled = field_CC_sprite_scale * FP_FromInteger(45);
                const FP kGridSize = ScaleToGridSize_4498B0(field_CC_sprite_scale);
                const FP k8 = FP_FromInteger(8);

                // Recoil right
                if (field_20_animation.field_4_flags.Get(AnimFlags::eBit5_FlipX) && sInputObject_5BD4E0.isPressed(sInputKey_Right_5550D0))
                {
                    PathLine* pLine = nullptr;
                    FP hitX = {};
                    FP hitY = {};
                    if (sCollisions_DArray_5C1128->Raycast_417A60(
                            field_B8_xpos,
                            field_BC_ypos,
                            field_B8_xpos + (k8 *  (kGridSize / k8)),
                            field_BC_ypos,
                            &pLine,
                            &hitX,
                            &hitY,
                            field_D6_scale != 0 ? 6 : 96) ||
                        sCollisions_DArray_5C1128->Raycast_417A60(
                            field_B8_xpos, 
                            field_BC_ypos - k45Scaled, 
                            field_B8_xpos + (k8 * (kGridSize / k8)), 
                            field_BC_ypos - k45Scaled, 
                            &pLine,
                            &hitX, 
                            &hitY, 
                            field_D6_scale != 0 ? 6 : 96))
                    {
                        return;
                    }
                    field_C4_velx = (kGridSize / k8);
                    field_106_current_motion = eSligMotions::M_Recoil_19_4B8270;
                    return;
                }

                // Recoil left
                if (!field_20_animation.field_4_flags.Get(AnimFlags::eBit5_FlipX) && sInputObject_5BD4E0.isPressed(sInputKey_Left_5550D4))
                {
                    PathLine* pLine = nullptr;
                    FP hitX = {};
                    FP hitY = {};
                    if (sCollisions_DArray_5C1128->Raycast_417A60(
                            field_B8_xpos,
                            field_BC_ypos,
                            field_B8_xpos - (k8 * (kGridSize / k8)),
                            field_BC_ypos,
                            &pLine,
                            &hitX,
                            &hitY,
                            field_D6_scale != 0 ? 6 : 0x60) ||
                        sCollisions_DArray_5C1128->Raycast_417A60(
                            field_B8_xpos, 
                            field_BC_ypos - k45Scaled, 
                            field_B8_xpos - (k8 * (kGridSize / k8)),
                            field_BC_ypos - k45Scaled,
                            &pLine,
                            &hitX,
                            &hitY, 
                            field_D6_scale != 0 ? 6 : 96))
                    {
                        return;
                    }
                    field_C4_velx = -(kGridSize / k8);
                    field_106_current_motion = eSligMotions::M_Recoil_19_4B8270;
                    return;
                }

                // General recoil
                if (!sInputObject_5BD4E0.isPressed(sInputKey_Down_5550DC) || field_CC_sprite_scale != FP_FromDouble(0.5))
                {
                    if (field_12C > static_cast<int>(sGnFrame_5C1B84))
                    {
                        return;
                    }

                    if (field_20_animation.field_4_flags.Get(AnimFlags::eBit5_FlipX))
                    {
                        field_C4_velx = (kGridSize / k8);
                    }
                    else
                    {
                        field_C4_velx = -(kGridSize / k8);
                    }

                    PathLine* pLine = nullptr;
                    FP hitX = {};
                    FP hitY = {};
                    if (sCollisions_DArray_5C1128->Raycast_417A60(
                            field_B8_xpos,
                            field_BC_ypos,
                            field_B8_xpos + (k8 * field_C4_velx),
                            field_BC_ypos,
                            &pLine,
                            &hitX,
                            &hitY,
                            field_D6_scale != 0 ? 6 : 96) ||
                        sCollisions_DArray_5C1128->Raycast_417A60(
                            field_B8_xpos, field_BC_ypos - k45Scaled, 
                            field_B8_xpos + (k8 * field_C4_velx), 
                            field_BC_ypos - k45Scaled, 
                            &pLine, 
                            &hitX, 
                            &hitY, 
                            field_D6_scale != 0 ? 6 : 96))
                    {
                        field_C4_velx = FP_FromInteger(0);
                    }
                    else
                    {
                        field_106_current_motion = eSligMotions::M_Recoil_19_4B8270;
                    }
                    return;
                }
            }
            else
            {
                SND_SEQ_PlaySeq_4CA960(SeqId::HitBottomOfDeathPit_9, 1, 1);
                field_106_current_motion = eSligMotions::M_ShootToStand_13_4B5580;
                return;
            }
        }

        if (field_108_next_motion == eSligMotions::M_StandIdle_0_4B4EC0)
        {
            SND_SEQ_PlaySeq_4CA960(SeqId::HitBottomOfDeathPit_9, 1, 1);
            field_106_current_motion = eSligMotions::M_ShootToStand_13_4B5580;
            field_108_next_motion = -1;
            return;
        }

        if (field_108_next_motion != -1 && field_108_next_motion != eSligMotions::M_Shoot_6_4B55A0)
        {
            SND_SEQ_PlaySeq_4CA960(SeqId::HitBottomOfDeathPit_9, 1, 1);
            field_106_current_motion = eSligMotions::M_ShootToStand_13_4B5580;
            return;
        }
    }
}

void Slig::M_Falling_7_4B42D0()
{
    if (field_C4_velx <= FP_FromInteger(0))
    {
        if (field_C4_velx < FP_FromInteger(0))
        {
            field_C4_velx += (field_CC_sprite_scale * field_130);
            if (field_C4_velx < (ScaleToGridSize_4498B0(field_CC_sprite_scale) / FP_FromInteger(4)))
            {
                field_C4_velx = -(ScaleToGridSize_4498B0(field_CC_sprite_scale) / FP_FromInteger(4));
            }

            if (field_C4_velx > FP_FromInteger(0))
            {
                field_C4_velx = FP_FromInteger(0);
            }
        }
    }
    else
    {
        field_C4_velx -= (field_CC_sprite_scale * field_130);
        if (field_C4_velx > (ScaleToGridSize_4498B0(field_CC_sprite_scale) / FP_FromInteger(4)))
        {
            field_C4_velx = (ScaleToGridSize_4498B0(field_CC_sprite_scale) / FP_FromInteger(4));
        }

        if (field_C4_velx < FP_FromInteger(0))
        {
            field_C4_velx = FP_FromInteger(0);
        }
    }

    PathLine* ppPathLine = nullptr;
    FP hitX = {};
    FP hitY = {};
    const auto bCollision = InAirCollision_408810(&ppPathLine, &hitX, &hitY, FP_FromDouble(1.8));
    sub_408C40();
    if (bCollision)
    {
        switch (ppPathLine->field_8_type)
        {
        case 0u:
        case 4u:
        case 32u:
        case 36u:
            field_100_pCollisionLine = ppPathLine;
            field_BC_ypos = hitY;
            field_B8_xpos = hitX;
            MapFollowMe_408D10(TRUE);
            ToStand_4B4A20();
            PlatformCollide_4B4E00();
            field_106_current_motion = eSligMotions::M_LandingSoft_40_4B4530;
            break;
        case 1u:
        case 2u:
        case 5u:
        case 6u:
            field_B8_xpos = hitX;
            field_BC_ypos = hitY;
            FallKnockBackOrSmash_4B4A90();
            break;
        default:
            return;
        }
    }
}

void Slig::M_SlidingToStand_8_4B6520()
{
    Event_Broadcast_422BC0(kEventNoise, this);
    if (WallHit_408750(field_CC_sprite_scale * FP_FromInteger(45), field_C4_velx))
    {
        FallKnockBackOrSmash_4B4A90();
    }
    else
    {
        SlowDown_4B6450(FP_FromDouble(2.125));
        if (field_106_current_motion == eSligMotions::M_SlidingToStand_8_4B6520)
        {
            if (field_20_animation.field_92_current_frame < 6 && sControlledCharacter_5C1B8C == this && field_10C_health > FP_FromInteger(0))
            {
				if ((field_20_animation.field_4_flags.Get(AnimFlags::eBit5_FlipX) && sInputObject_5BD4E0.isPressed(sInputKey_Right_5550D0)) ||
					((!(field_20_animation.field_4_flags.Get(AnimFlags::eBit5_FlipX)) && sInputObject_5BD4E0.isPressed(sInputKey_Left_5550D4))))
                {
                    field_F6_anim_frame = field_20_animation.field_92_current_frame;
                    field_F4 = 9;
                    field_124 = 1;
                }
            }
            else if (field_20_animation.field_4_flags.Get(AnimFlags::eBit18_IsLastFrame))
            {
                Abe_SFX_2_457A40(0, 0, 0x7FFF, this);
                MapFollowMe_408D10(TRUE);
                MainMovement_4B4720();
            }
        }
    }

}

void Slig::M_SlidingTurn_9_4B6680()
{
    Event_Broadcast_422BC0(kEventNoise, this);

    if (WallHit_408750(field_CC_sprite_scale * FP_FromInteger(45), field_C4_velx))
    {
        FallKnockBackOrSmash_4B4A90();
    }
    else
    {
        SlowDown_4B6450(FP_FromDouble(2.125));

        if (field_106_current_motion == eSligMotions::M_SlidingTurn_9_4B6680)
        {
            if (field_20_animation.field_4_flags.Get(AnimFlags::eBit18_IsLastFrame))
            {
                MapFollowMe_408D10(TRUE);

                if (sControlledCharacter_5C1B8C == this && field_10C_health > FP_FromInteger(0))
                {
                    if (sInputObject_5BD4E0.isPressed(sInputKey_Run_5550E8))
                    {
                        field_108_next_motion = eSligMotions::M_Running_4_4B6000;
                    }
                    else
                    {
                        field_108_next_motion = eSligMotions::M_Walking_2_4B5BC0;
                    }
                }

                if (field_108_next_motion == eSligMotions::M_Running_4_4B6000)
                {
                    field_C4_velx = -(ScaleToGridSize_4498B0(field_CC_sprite_scale) / FP_FromInteger(4));
                    field_106_current_motion = eSligMotions::M_SlidingTurnToRun_11_4B6850;
                }
                else
                {
                    field_C4_velx = -(ScaleToGridSize_4498B0(field_CC_sprite_scale) / FP_FromInteger(9));
                    field_106_current_motion = eSligMotions::M_SlidingTurnToWalk_10_4B6800;
                }

                if (field_20_animation.field_4_flags.Get(AnimFlags::eBit5_FlipX))
                {
                    field_C4_velx = -field_C4_velx;
                }
            }
        }
    }

}

void Slig::M_SlidingTurnToWalk_10_4B6800()
{
    Event_Broadcast_422BC0(kEventNoise, this);
    MoveOnLine_4B4C40();

    if (field_20_animation.field_4_flags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        field_20_animation.field_4_flags.Toggle(AnimFlags::eBit5_FlipX);
        field_106_current_motion = eSligMotions::M_Walking_2_4B5BC0;
    }
}

void Slig::M_SlidingTurnToRun_11_4B6850()
{
    Event_Broadcast_422BC0(kEventNoise, this);
    MoveOnLine_4B4C40();

    if (field_20_animation.field_4_flags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        field_20_animation.field_4_flags.Toggle(AnimFlags::eBit5_FlipX);
        field_106_current_motion = eSligMotions::M_Running_4_4B6000;
    }
}

void Slig::M_ReloadGun_12_4B5530()
{
    if (field_20_animation.field_92_current_frame == 1)
    {
        Slig_SoundEffect_4BFFE0(6, this);
    }
    else if (field_20_animation.field_92_current_frame == 4)
    {
        Slig_SoundEffect_4BFFE0(7, this);
    }

    if (field_20_animation.field_4_flags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        ToStand_4B4A20();
    }
}

void Slig::M_ShootToStand_13_4B5580()
{
    if (field_20_animation.field_4_flags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        MainMovement_4B4720();
    }
}

void Slig::M_SteppingToStand_14_4B8480()
{
    if (!field_20_animation.field_92_current_frame)
    {
        Slig_SoundEffect_4BFFE0(2, this);
    }

    if (WallHit_408750(field_CC_sprite_scale * FP_FromInteger(45), field_C4_velx))
    {
        FallKnockBackOrSmash_4B4A90();
    }
    else
    {
        MoveOnLine_4B4C40();
        if (field_106_current_motion == eSligMotions::M_SteppingToStand_14_4B8480)
        {
            if (field_20_animation.field_4_flags.Get(AnimFlags::eBit18_IsLastFrame))
            {
                MapFollowMe_408D10(TRUE);
                ToStand_4B4A20();
            }
        }
    }
}

void Slig::M_StandingToStep_15_4B83B0()
{
    if (field_20_animation.field_4_flags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        if (sInputObject_5BD4E0.isPressed(sInputKey_Left_5550D4 | sInputKey_Right_5550D0))
        {
            field_106_current_motion = eSligMotions::M_StandToWalk_1_4B5F70;
        }
        else if (field_20_animation.field_4_flags.Get(AnimFlags::eBit5_FlipX))
        {
            field_106_current_motion = eSligMotions::M_SteppingToStand_14_4B8480;
            field_C4_velx = -(ScaleToGridSize_4498B0(field_CC_sprite_scale) / FP_FromInteger(6));
        }
        else
        {
            field_C4_velx = (ScaleToGridSize_4498B0(field_CC_sprite_scale) / FP_FromInteger(6));
            field_106_current_motion = eSligMotions::M_SteppingToStand_14_4B8480;
        }
    }
}

void Slig::M_DepossessingAbort_16_4B8250()
{
    if (field_20_animation.field_4_flags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        ToStand_4B4A20();
    }
}

void Slig::M_GameSpeak_17_4B5290()
{
    field_128_input |= sInputObject_5BD4E0.field_0_pads[sCurrentControllerIndex_5C1BBE].field_C_held;
    if (field_20_animation.field_4_flags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        field_106_current_motion = GetNextMotionIncGameSpeak_4B5080(field_128_input);
        if (field_106_current_motion == -1)
        {
            ToStand_4B4A20();
            field_128_input = 0;
        }
        else
        {
            if (!BrainIs(&Slig::AI_ListeningToGlukkon_4_4B9D20))
            {
                Event_Broadcast_422BC0(kEventSpeaking, this);
            }
            field_128_input = 0;
        }
    }
}

void Slig::M_WalkToStand_18_4B5FC0()
{
    MoveOnLine_4B4C40();

    if (field_20_animation.field_4_flags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        MapFollowMe_408D10(TRUE);
        if (!Slig::MainMovement_4B4720())
        {
            ToStand_4B4A20();
        }
    }
}

void Slig::M_Recoil_19_4B8270()
{
    MoveOnLine_4B4C40();

    if (field_106_current_motion == eSligMotions::M_Recoil_19_4B8270)
    {
        if (field_20_animation.field_4_flags.Get(AnimFlags::eBit18_IsLastFrame))
        {
            MapFollowMe_408D10(TRUE);
            if (sControlledCharacter_5C1B8C == this && field_10C_health > FP_FromInteger(0))
            {
                if (sInputObject_5BD4E0.isPressed(sInputKey_ThrowItem_5550F4))
                {
                    field_C4_velx = FP_FromInteger(0);
                    field_F4 = 6;
                    field_12C = sGnFrame_5C1B84 + 60;
                    field_F6_anim_frame = 2;
                    field_124 = 1;
                }
                else
                {
                    SND_SEQ_PlaySeq_4CA960(SeqId::HitBottomOfDeathPit_9, 1, 1);
                    field_106_current_motion = eSligMotions::M_ShootToStand_13_4B5580;
                }
            }
            else if (field_108_next_motion != -1)
            {
                SND_SEQ_PlaySeq_4CA960(SeqId::HitBottomOfDeathPit_9, 1, 1);
                field_106_current_motion = eSligMotions::M_ShootToStand_13_4B5580;
                field_108_next_motion = -1;
            }
        }
    }
    else if (field_CC_sprite_scale == FP_FromDouble(0.5))
    {
        SFX_Play_46FA90(5u, 85);
    }
    else
    {
        SFX_Play_46FA90(5u, 0);
    }
}

void Slig::M_SpeakHereBoy_20_4B5330()
{
    field_128_input |= sInputObject_5BD4E0.field_0_pads[sCurrentControllerIndex_5C1BBE].field_C_held;
    if (field_20_animation.field_4_flags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        field_106_current_motion = GetNextMotionIncGameSpeak_4B5080(field_128_input);
        if (field_106_current_motion == -1)
        {
            ToStand_4B4A20();
            field_128_input = 0;
        }
        else
        {
            if (!BrainIs(&Slig::AI_ListeningToGlukkon_4_4B9D20))
            {
                Event_Broadcast_422BC0(kEventSpeaking, this);
            }
            field_128_input = 0;
        }
    }
}

void Slig::M_SpeakHi_21_4B53D0()
{
    M_SpeakHereBoy_20_4B5330();
}

void Slig::M_SpeakFreeze_22_4B53F0()
{
    M_SpeakHereBoy_20_4B5330();
}

void Slig::M_SpeakGitIm_23_4B5410()
{
    M_SpeakHereBoy_20_4B5330();
}

void Slig::M_SpeakLaugh_24_4B5430()
{
    M_SpeakHereBoy_20_4B5330();
}

void Slig::M_SpeakBullShit1_25_4B5450()
{
    M_SpeakHereBoy_20_4B5330();
}

void Slig::M_SpeakLookOut_26_4B5470()
{
    M_SpeakHereBoy_20_4B5330();
}

void Slig::M_SpeakBullShit2_27_4B5490()
{
    M_SpeakHereBoy_20_4B5330();
}

void Slig::M_SpeakPanic_28_4B54B0()
{
    M_SpeakHereBoy_20_4B5330();
}

void Slig::M_SpeakWhat_29_4B54D0()
{
    M_SpeakHereBoy_20_4B5330();
}

void Slig::M_SpeakAIFreeze_30_4B54F0()
{
    M_SpeakHereBoy_20_4B5330();
}

void Slig::M_Blurgh_31_4B5510()
{
    M_SpeakHereBoy_20_4B5330();
}

void Slig::M_Sleeping_32_4B89A0()
{
    if (field_108_next_motion == eSligMotions::M_SleepingToStand_33_4B8C50)
    {
        // Out of sleep
        field_106_current_motion = eSligMotions::M_SleepingToStand_33_4B8C50;
        field_108_next_motion = -1;
    }
    else if (static_cast<int>(sGnFrame_5C1B84 % 60))
    {
        if (!(static_cast<int>(sGnFrame_5C1B84 - 20) % 60))
        {
            Slig_SoundEffect_4BFFE0(5, this);
            if (gMap_5C3030.Is_Point_In_Current_Camera_4810D0(field_C2_lvl_number, field_C0_path_number, field_B8_xpos, field_BC_ypos, 0))
            {
                auto pSnoozeParticle = alive_new<SnoozeParticle>();
                if (pSnoozeParticle)
                {
                    FP xOff = {};
                    if (field_20_animation.field_4_flags.Get(AnimFlags::eBit5_FlipX))
                    {
                        xOff = -(field_CC_sprite_scale * FP_FromInteger(-20));
                    }
                    else
                    {
                        xOff = (field_CC_sprite_scale * FP_FromInteger(-20));
                    }
                    pSnoozeParticle->ctor_4B06F0(
                        xOff + field_B8_xpos,
                        field_BC_ypos + (field_CC_sprite_scale * FP_FromInteger(-10)),
                        field_20_animation.field_C_render_layer,
                        field_20_animation.field_14_scale);
                }
            }
        }
    }
    else
    {
        Slig_SoundEffect_4BFFE0(4, this);

        if (gMap_5C3030.Is_Point_In_Current_Camera_4810D0(
            field_C2_lvl_number,
            field_C0_path_number,
            field_B8_xpos,
            field_BC_ypos,
            0))
        {
            auto pSnoozeParticle = alive_new<SnoozeParticle>();
            if (pSnoozeParticle)
            {
                FP xOff = {};
                if (field_20_animation.field_4_flags.Get(AnimFlags::eBit5_FlipX))
                {
                    xOff = -(field_CC_sprite_scale * FP_FromInteger(-20));
                }
                else
                {
                    xOff = (field_CC_sprite_scale * FP_FromInteger(-20));
                }

                pSnoozeParticle->ctor_4B06F0(
                    xOff + field_B8_xpos,
                    field_BC_ypos + (field_CC_sprite_scale * FP_FromInteger(-10)),
                    field_20_animation.field_C_render_layer,
                    field_20_animation.field_14_scale);
            }
        }
    }
}

void Slig::M_SleepingToStand_33_4B8C50()
{
    // OWI hack - kill all particles, even if they're not ours!
    for (int i = 0; i < gBaseGameObject_list_BB47C4->Size(); i++)
    {
        auto pObj = gBaseGameObject_list_BB47C4->ItemAt(i);
        if (!pObj)
        {
            break;
        }

        if (pObj->field_4_typeId == Types::eSnoozParticle_124)
        {
            static_cast<SnoozeParticle*>(pObj)->field_1E4_state = SnoozeParticle::SnoozeParticleState::BlowingUp_2;
        }
    }

    if (field_20_animation.field_92_current_frame >= 2 && field_20_animation.field_92_current_frame <= 10)
    {
        Slig_SoundEffect_4BFFE0(0, this);
    }

    if (field_20_animation.field_92_current_frame == 9)
    {
        Slig_SoundEffect_4BFFE0(2, this);
    }

    switch (field_20_animation.field_92_current_frame)
    {
    case 9:
        if (field_20_animation.field_4_flags.Get(AnimFlags::eBit5_FlipX))
        {
            field_B8_xpos -= (field_CC_sprite_scale * FP_FromInteger(7));
            return;
        }
        else
        {
            field_B8_xpos += (field_CC_sprite_scale * FP_FromInteger(7));
            return;
        }
        break;

    case 10:
        if (field_20_animation.field_4_flags.Get(AnimFlags::eBit5_FlipX))
        {
            field_B8_xpos -= (field_CC_sprite_scale * FP_FromInteger(12));
            return;
        }
        else
        {
            field_B8_xpos += (field_CC_sprite_scale * FP_FromInteger(12));
            return;
        }
        break;

    case 11:
        if (field_20_animation.field_4_flags.Get(AnimFlags::eBit5_FlipX))
        {
            field_B8_xpos -= (field_CC_sprite_scale * FP_FromInteger(6));
            return;
        }
        else
        {
            field_B8_xpos += (field_CC_sprite_scale * FP_FromInteger(6));
            return;
        }
        break;

    default:
        if (field_20_animation.field_4_flags.Get(AnimFlags::eBit18_IsLastFrame))
        {
            MusicController::sub_47FD60(4, this, 0, 0);
            MainMovement_4B4720();
        }
        break;
    }
}

void Slig::M_Knockback_34_4B68A0()
{
    if (field_100_pCollisionLine)
    {
        SlowDown_4B6450(FP_FromDouble(0.39));
    }
    else
    {
        M_Falling_7_4B42D0();

        if (field_106_current_motion == eSligMotions::M_LandingSoft_40_4B4530)
        {
            field_106_current_motion = eSligMotions::M_Knockback_34_4B68A0;
            field_12C = sGnFrame_5C1B84 + 10;
            if (field_BC_ypos - field_F8_LastLineYPos > FP_FromInteger(180)
                && !sPath_dword_BB47C0->TLV_Get_At_4DB4B0(
                    FP_GetExponent(field_B8_xpos),
                    FP_GetExponent(field_BC_ypos),
                    FP_GetExponent(field_B8_xpos),
                    FP_GetExponent(field_BC_ypos),
                    TlvTypes::SoftLanding_75))
            {
                field_106_current_motion = eSligMotions::M_LandingFatal_41_4B4680;
                field_12C = sGnFrame_5C1B84 + 30;
                field_10C_health = FP_FromInteger(0);
                Event_Broadcast_422BC0(kEventMudokonComfort, this);
            }
        }
    }

    Event_Broadcast_422BC0(kEventNoise, this);
    if (field_20_animation.field_92_current_frame == 4)
    {
        Abe_SFX_2_457A40(6, 80, -200, this);
    }

    if (field_20_animation.field_4_flags.Get(AnimFlags::eBit12_ForwardLoopCompleted))
    {
        if (field_100_pCollisionLine)
        {
            field_C4_velx = FP_FromInteger(0);

            if (field_10C_health > FP_FromInteger(0) && 
                field_12C <= static_cast<int>(sGnFrame_5C1B84) &&
                sActiveHero_5C1B68->field_10C_health > FP_FromInteger(0))
            {
                field_106_current_motion = eSligMotions::M_KnockbackToStand_35_4B6A30;
            }
        }
    }
}

void Slig::M_KnockbackToStand_35_4B6A30()
{
    Event_Broadcast_422BC0(kEventNoise, this);

    if (field_20_animation.field_92_current_frame >= 2 && field_20_animation.field_92_current_frame <= 10)
    {
        Slig_SoundEffect_4BFFE0(0, this);
    }

    if (field_20_animation.field_92_current_frame == 9)
    {
        Slig_SoundEffect_4BFFE0(2, this);
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

    if (!WallHit_408750(field_CC_sprite_scale * FP_FromInteger(45), gridSize))
    {
        int xOff = 0;
        switch (field_20_animation.field_92_current_frame)
        {
        case 9:
            xOff = 3;
            break;
        case 10:
            xOff = 13;
            break;
        case 11:
            xOff = 9;
            break;
        }

        if (field_20_animation.field_4_flags.Get(AnimFlags::eBit5_FlipX))
        {
            xOff = -xOff;
        }

        field_B8_xpos += (field_CC_sprite_scale * field_CC_sprite_scale) * FP_FromInteger(xOff);
    }

    if (field_20_animation.field_4_flags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        ToStand_4B4A20();
    }
}

void Slig::M_Depossessing_36_4B7F30()
{
    if (sControlledCharacter_5C1B8C == this)
    {
        if (field_20_animation.field_4_flags.Get(AnimFlags::eBit18_IsLastFrame))
        {
            if (!Input_IsChanting_45F260())
            {
                field_106_current_motion = eSligMotions::M_DepossessingAbort_16_4B8250;
            }
        }

        if (!(static_cast<int>(sGnFrame_5C1B84) % 4))
        {
            const FP xRand = FP_FromInteger(Math_RandomRange_496AB0(-20, 20));
            const FP yRand = FP_FromInteger(Math_RandomRange_496AB0(20, 50));
            New_Chant_Particle_426BE0(
                (field_CC_sprite_scale * xRand) + field_B8_xpos,
                field_BC_ypos - (field_CC_sprite_scale * yRand),
                field_CC_sprite_scale,
                0);
        }

        if (static_cast<int>(sGnFrame_5C1B84) > field_12C)
        {
            BlowUp_4B8020();
        }
    }
}

void Slig::M_Possess_37_4B72C0()
{
    if (!field_100_pCollisionLine)
    {
        M_Falling_7_4B42D0();
        if (field_106_current_motion != eSligMotions::M_Possess_37_4B72C0)
        {
            field_106_current_motion = eSligMotions::M_Possess_37_4B72C0;
        }
    }

    if (static_cast<int>(sGnFrame_5C1B84) >= field_150)
    {
        if (field_20_animation.field_4_flags.Get(AnimFlags::eBit3_Render))
        {
            FP xOff = (FP_FromInteger(20) * field_CC_sprite_scale);
            if (field_C4_velx < FP_FromInteger(0))
            {
                xOff = -xOff;
            }

            auto pGibs = alive_new<Gibs>();
            if (pGibs)
            {
                pGibs->ctor_40FB40(
                    1,
                    field_B8_xpos,
                    field_BC_ypos,
                    xOff,
                    FP_FromInteger(0),
                    field_CC_sprite_scale,
                    0);
            }
            New_Particles_426C70(
                field_B8_xpos,
                field_BC_ypos - (FP_FromInteger(30) * field_CC_sprite_scale),
                field_CC_sprite_scale,
                3,
                0x80u,
                0x80u,
                0x80u);

            if (field_CC_sprite_scale == FP_FromDouble(0.5))
            {
                SFX_Play_46FA90(64u, 80);
                SFX_Play_46FA90(47u, 60);
            }
            else
            {
                SFX_Play_46FA90(64u, 127);
                SFX_Play_46FA90(47u, 90);
            }

            field_20_animation.field_4_flags.Clear(AnimFlags::eBit3_Render);
            field_106_current_motion = eSligMotions::M_StandIdle_0_4B4EC0;
            field_C8_vely = FP_FromInteger(0);
            field_C4_velx = FP_FromInteger(0);
            field_10C_health = FP_FromInteger(0);
            MusicController::sub_47FD60(0, this, 0, 0);
            field_1C_update_delay = 40;
            field_120_timer = sGnFrame_5C1B84 + 60;
            SetBrain(&Slig::AI_Death_0_4BBFB0);
        }
    }

    if (static_cast<int>(sGnFrame_5C1B84) > field_14C)
    {
        if (field_C4_velx >= FP_FromInteger(0))
        {
            if (field_20_animation.field_4_flags.Get(AnimFlags::eBit5_FlipX))
            {
                field_106_current_motion = eSligMotions::M_Knockback_34_4B68A0;
            }
        }
        else if (!field_20_animation.field_4_flags.Get(AnimFlags::eBit5_FlipX))
        {
            field_106_current_motion = eSligMotions::M_Knockback_34_4B68A0;
        }
        field_106_current_motion = eSligMotions::M_Smash_44_4B6B90;
    }
}

// When slig is "air walking" in a death fall
void Slig::M_OutToFall_38_4B4570()
{
    M_Falling_7_4B42D0();

    const FP fallDepth = field_BC_ypos - field_F8_LastLineYPos;
    if (fallDepth > FP_FromInteger(16 * 640))
    {
        field_6_flags.Set(BaseGameObject::eDead);
    }

    if (field_106_current_motion == eSligMotions::M_LandingSoft_40_4B4530 && fallDepth > FP_FromInteger(180) &&
        !sPath_dword_BB47C0->TLV_Get_At_4DB4B0(
            FP_GetExponent(field_B8_xpos),
            FP_GetExponent(field_BC_ypos),
            FP_GetExponent(field_B8_xpos),
            FP_GetExponent(field_BC_ypos),
            TlvTypes::SoftLanding_75))
    {
        field_106_current_motion = eSligMotions::M_LandingFatal_41_4B4680;
        field_12C = sGnFrame_5C1B84 + 30;
        field_10C_health = FP_FromInteger(0);
        Event_Broadcast_422BC0(kEventMudokonComfort, this);
    }
}

void Slig::M_FallingInitiate_39_4B4640()
{
    Event_Broadcast_422BC0(kEventNoise, this);

    if (field_20_animation.field_4_flags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        field_106_current_motion = eSligMotions::M_OutToFall_38_4B4570;
    }

    M_Falling_7_4B42D0();
}

void Slig::M_LandingSoft_40_4B4530()
{
    if (field_20_animation.field_92_current_frame == 0)
    {
        Abe_SFX_2_457A40(6, 0, 0x7FFF, 0);
    }

    if (field_20_animation.field_4_flags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        ToStand_4B4A20();
    }
}

void Slig::M_LandingFatal_41_4B4680()
{
    if (field_20_animation.field_92_current_frame == 0)
    {
        SND_SEQ_Play_4CAB10(SeqId::HitBottomOfDeathPit_9, 1, 65, 65);
        SFX_Play_46FA90(64u, 80);
    }

    if (field_20_animation.field_4_flags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        if (static_cast<int>(sGnFrame_5C1B84) >= field_12C && !BrainIs(&Slig::AI_Death_0_4BBFB0))
        {
            field_10C_health = FP_FromInteger(0);
            SetBrain(&Slig::AI_Death_0_4BBFB0);
            field_120_timer = sGnFrame_5C1B84 + 60;
        }
    }
}

void Slig::M_ShootZ_42_4B7560()
{
    if (field_20_animation.field_4_flags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        // Controlled by player and no longer pressing down or shoot
        if (sControlledCharacter_5C1B8C == this && (!sInputObject_5BD4E0.isPressed(sInputKey_ThrowItem_5550F4) || !sInputObject_5BD4E0.isPressed(sInputKey_Down_5550DC)))
        {
            SND_SEQ_PlaySeq_4CA960(SeqId::HitBottomOfDeathPit_9, 1, 1);
            field_106_current_motion = eSligMotions::M_ShootZtoStand_43_4B77E0;
        }
        // Controlled by AI and need to leave Z-shoot motion
        else if (field_108_next_motion != -1)
        {
            SND_SEQ_PlaySeq_4CA960(SeqId::HitBottomOfDeathPit_9, 1, 1);
            field_108_next_motion = -1;
            field_106_current_motion = eSligMotions::M_ShootZtoStand_43_4B77E0;
        }
    }
    else if (field_20_animation.field_92_current_frame == 7)
    {
        if (sControlledCharacter_5C1B8C == this)
        {
            auto pBullet = alive_new<Bullet>();
            if (pBullet)
            {
                pBullet->ctor_414540(
                    this,
                    BulletType::Type_1,
                    field_B8_xpos,
                    field_BC_ypos - FP_FromInteger(12),
                    FP_FromInteger(640),
                    0,
                    field_CC_sprite_scale,
                    field_218_tlv_data.field_22_num_times_to_shoot - field_158 - 1);
            }
        }
        else
        {
            auto pBullet = alive_new<Bullet>();
            if (pBullet)
            {
                pBullet->ctor_414540(
                    this,
                    BulletType::ZBullet_3,
                    field_B8_xpos,
                    field_BC_ypos - FP_FromInteger(12),
                    FP_FromInteger(640),
                    0,
                    field_CC_sprite_scale,
                    field_218_tlv_data.field_22_num_times_to_shoot - field_158 - 1);
            }
        }

        New_Particle_4269B0(field_B8_xpos, field_BC_ypos - FP_FromInteger(12), field_CC_sprite_scale);

        if (field_CC_sprite_scale == FP_FromDouble(0.5))
        {
            SFX_Play_46FA90(5u, 85);
        }
        else
        {
            SFX_Play_46FA90(5u, 0);
        }

        // The doves don't like bullets
        Dove::All_FlyAway_41FA60(0);

        Event_Broadcast_422BC0(kEventShooting, this);
        Event_Broadcast_422BC0(kEventLoudNoise, this);
    }
}

void Slig::M_ShootZtoStand_43_4B77E0()
{
    if (field_20_animation.field_4_flags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        ToStand_4B4A20();
    }
}

void Slig::M_Smash_44_4B6B90()
{
    if (field_100_pCollisionLine)
    {
        if (field_20_animation.field_92_current_frame == 4)
        {
            Abe_SFX_2_457A40(6, 80, -200, this);
        }
    }
    else
    {
        M_Falling_7_4B42D0();

        if (field_106_current_motion != eSligMotions::M_Smash_44_4B6B90)
        {
            field_106_current_motion = eSligMotions::M_Smash_44_4B6B90;
        }
    }
}

void Slig::M_PullLever_45_4B8950()
{
    if (field_20_animation.field_4_flags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        if (field_114_flags.Get(Flags_114::e114_Bit10))
        {
            Sfx_Slig_GameSpeak_4C04F0(SligSpeak::Blurg_11, 0, field_11E, this);
            field_106_current_motion = eSligMotions::M_Blurgh_31_4B5510;
        }
        else
        {
            ToStand_4B4A20();
        }
    }
}

void Slig::M_LiftGrip_46_4B3700()
{
    auto pLiftPoint = static_cast<LiftPoint*>(sObjectIds_5C1B70.Find_449CF0(field_110_id));
    if (pLiftPoint)
    {
        pLiftPoint->vMove_4626A0(FP_FromInteger(0), FP_FromInteger(0), 0);
        field_C8_vely = FP_FromInteger(0);
        if (field_20_animation.field_4_flags.Get(AnimFlags::eBit18_IsLastFrame))
        {
            if (sControlledCharacter_5C1B8C == this)
            {
                if (sInputObject_5BD4E0.isPressed(sInputKey_Up_5550D8))
                {
                    if (pLiftPoint->vOnTopFloor_461890())
                    {
                        field_106_current_motion = eSligMotions::M_LiftGripping_48_4B3850;
                    }
                    else
                    {
                        field_106_current_motion = eSligMotions::M_LiftUp_49_4B3930;
                    }
                    return;
                }

                if (sInputObject_5BD4E0.isPressed(sInputKey_Down_5550DC))
                {
                    if (pLiftPoint->vOnBottomFloor_4618F0())
                    {
                        field_106_current_motion = eSligMotions::M_LiftGripping_48_4B3850;
                    }
                    else
                    {
                        field_106_current_motion = eSligMotions::M_LiftDown_50_4B3960;
                    }
                    return;
                }

                field_106_current_motion = eSligMotions::M_LiftGripping_48_4B3850;
            }
            else
            {
                if (pLiftPoint->vOnTopFloor_461890())
                {
                    field_106_current_motion = eSligMotions::M_LiftDown_50_4B3960;
                }

                if (pLiftPoint->vOnBottomFloor_4618F0())
                {
                    field_106_current_motion = eSligMotions::M_LiftUp_49_4B3930;
                }
            }
        }
    }
}

void Slig::M_LiftUngrip_47_4B3820()
{
    field_C8_vely = FP_FromInteger(0);

    if (field_20_animation.field_4_flags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        ToStand_4B4A20();
    }
}

void Slig::M_LiftGripping_48_4B3850()
{
    auto pLiftPoint = static_cast<LiftPoint*>(sObjectIds_5C1B70.Find_449CF0(field_110_id));
    if (pLiftPoint)
    {
        CheckPlatformVanished_4B3640();

        pLiftPoint->vMove_4626A0(FP_FromInteger(0), FP_FromInteger(0), 0);
        field_C8_vely = FP_FromInteger(0);

        if (sInputObject_5BD4E0.isPressed(sInputKey_Up_5550D8))
        {
            if (!pLiftPoint->vOnTopFloor_461890())
            {
                field_106_current_motion = eSligMotions::M_LiftUp_49_4B3930;
            }
        }
        else if (sInputObject_5BD4E0.isPressed(sInputKey_Down_5550DC))
        {
            if (!pLiftPoint->vOnBottomFloor_4618F0())
            {
                field_106_current_motion = eSligMotions::M_LiftDown_50_4B3960;
            }
        }
        else if (pLiftPoint->vOnAnyFloor_461920())
        {
            field_106_current_motion = eSligMotions::M_LiftUngrip_47_4B3820;
        }
    }
}

void Slig::M_LiftUp_49_4B3930()
{
    field_106_current_motion = MoveLift_4B3990(FP_FromInteger(-4));
}

void Slig::M_LiftDown_50_4B3960()
{
    field_106_current_motion = MoveLift_4B3990(FP_FromInteger(4));
}

void Slig::M_Beat_51_4B6C00()
{
    if (field_20_animation.field_92_current_frame == 5)
    {
        SFX_Play_46FBA0(0x17u, 90, -300);
    }

    if (field_20_animation.field_92_current_frame == 8)
    {
        const FP kGridSize = ScaleToGridSize_4498B0(field_CC_sprite_scale);
        const FP k0Scaled = FP_FromInteger(0) * kGridSize;
        const FP k1Scaled = FP_FromInteger(1) * kGridSize;
        const FP k2Scaled = FP_FromInteger(2) * kGridSize;

        PSX_RECT hitRect = {};

        if (field_20_animation.field_4_flags.Get(AnimFlags::eBit5_FlipX))
        {
            hitRect.x = FP_GetExponent(std::min(field_B8_xpos - k1Scaled, field_B8_xpos - k0Scaled));
            hitRect.y = FP_GetExponent(std::min(field_BC_ypos, (field_BC_ypos - k2Scaled)));
            hitRect.w = FP_GetExponent(std::max(field_B8_xpos - k1Scaled, field_B8_xpos - k0Scaled));
            hitRect.h = FP_GetExponent(std::max(field_BC_ypos, (field_BC_ypos - k2Scaled)));
        }
        else
        {
            hitRect.x = FP_GetExponent(std::min(field_B8_xpos + k1Scaled, field_B8_xpos - k0Scaled));
            hitRect.y = FP_GetExponent(std::min(field_BC_ypos, (field_BC_ypos - k2Scaled)));
            hitRect.w = FP_GetExponent(std::max(field_B8_xpos + k1Scaled, field_B8_xpos - k0Scaled));
            hitRect.h = FP_GetExponent(std::max(field_BC_ypos, (field_BC_ypos - k2Scaled)));
        }

        for (int i=0; i<gBaseAliveGameObjects_5C1B7C->Size(); i++)
        {
            BaseAliveGameObject* pObj = gBaseAliveGameObjects_5C1B7C->ItemAt(i);
            if (!pObj)
            {
                break;
            }

            if (pObj != this)
            {
                if (pObj->field_4_typeId == Types::eMudokon_110 || pObj->field_4_typeId == Types::eCrawlingSlig_26)
                {
                    PSX_RECT bRect = {};
                    pObj->vGetBoundingRect_424FD0(&bRect, 1);

                    if (pObj->field_10C_health > FP_FromInteger(0) && 
                        pObj->field_D6_scale == field_D6_scale &&
                        PSX_Rects_overlap_no_adjustment(&hitRect, &bRect))
                    {
                        pObj->VTakeDamage_408730(this);
                        Event_Broadcast_422BC0(kEventNoise, this);
                        SFX_Play_46FA90(47u, 60);
                        return;
                    }
                }
            }
        }
    }

    if (field_20_animation.field_4_flags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        field_106_current_motion = eSligMotions::M_StandIdle_0_4B4EC0;
    }
}

enum AI_Possessed
{
    eState2_StartPossession_0 = 0,
    eState2_PossessionShaking_1 = 1,
    eState2_PossessionInactive_2 = 2,
    eState2_PossessionSpeak_3 = 3,
    eState2_ControlledByPlayer_4 = 4
};

enum AI_GameEnder
{
    eState35_UNKNOWN_0 = 0,
    eState35_UNKNOWN_1 = 1,
    eState35_UNKNOWN_2 = 2
};

__int16 Slig::AI_Death_0_4BBFB0()
{
    if (field_20_animation.field_4_flags.Get(AnimFlags::eBit3_Render) && field_120_timer < (static_cast<int>(sGnFrame_5C1B84) + 30))
    {
        field_CC_sprite_scale -= FP_FromDouble(0.01);
        field_D0_r -= 2;
        field_D2_g -= 2;
        field_D4_b -= 2;
        if (field_CC_sprite_scale >= FP_FromDouble(0.3) && !(static_cast<int>(sGnFrame_5C1B84) % 5))
        {
            const FP xOff = (FP_FromInteger(Math_RandomRange_496AB0(-24, 24)) * field_CC_sprite_scale);
            New_Particles_426C70(xOff + field_B8_xpos, (field_BC_ypos - FP_FromInteger(6)), (field_CC_sprite_scale / FP_FromInteger(2)), 2, 128u, 128u, 128u);
            const FP sndPitch = (FP_FromInteger(2200) * field_CC_sprite_scale);
            SFX_Play_46FBA0(79u, 25, FP_GetExponent(sndPitch));
        }
    }
    else if (!field_20_animation.field_4_flags.Get(AnimFlags::eBit3_Render))
    {
        field_6_flags.Set(BaseGameObject::eDead);
    }

    if (sControlledCharacter_5C1B8C == this)
    {
        if (field_120_timer < static_cast<int>(sGnFrame_5C1B84))
        {
            sControlledCharacter_5C1B8C = sActiveHero_5C1B68;
            MusicController::sub_47FD60(0, this, 0, 0);
            gMap_5C3030.SetActiveCam_480D30(field_146_level, field_148_path, field_14A_camera, CameraSwapEffects::eEffect0_InstantChange, 0, 0);
        }
    }

    if (sControlledCharacter_5C1B8C != this)
    {
        if (!gMap_5C3030.Is_Point_In_Current_Camera_4810D0(
            field_C2_lvl_number,
            field_C0_path_number,
            field_B8_xpos,
            field_BC_ypos,
            0))
        {
            field_6_flags.Set(BaseGameObject::eDead);
        }
    }

    if (field_CC_sprite_scale < FP_FromInteger(0))
    {
        field_6_flags.Set(BaseGameObject::eDead);
    }

    return 116;
}

__int16 Slig::AI_ReturnControlToAbeAndDie_1_4BC410()
{
    if (sControlledCharacter_5C1B8C == this)
    {
        sControlledCharacter_5C1B8C = sActiveHero_5C1B68;
        MusicController::sub_47FD60(0, this, 0, 0);
        gMap_5C3030.SetActiveCam_480D30(field_146_level, field_148_path, field_14A_camera, CameraSwapEffects::eEffect0_InstantChange, 0, 0);
    }

    field_6_flags.Set(BaseGameObject::eDead);
    return 117;
}

__int16 Slig::AI_Possessed_2_4BBCF0()
{
    switch (field_11C_ai_sub_state)
    {
    case AI_Possessed::eState2_StartPossession_0:
        Sfx_Slig_GameSpeak_4C04F0(SligSpeak::Help_10, 0, field_11E, this);
        field_11C_ai_sub_state = 1;
        field_10C_health = FP_FromInteger(0);
        field_106_current_motion = eSligMotions::M_Possess_37_4B72C0;
        field_120_timer = sGnFrame_5C1B84 + 30;
        field_150 = sGnFrame_5C1B84 + 1000;
        if (field_14C == 0)
        {
            field_14C = sGnFrame_5C1B84 + 1000;
        }
        return field_11C_ai_sub_state;

    case AI_Possessed::eState2_PossessionShaking_1:
        if (static_cast<int>(sGnFrame_5C1B84) >= field_120_timer)
        {
            field_11C_ai_sub_state = AI_Possessed::eState2_PossessionInactive_2;
            field_120_timer = sGnFrame_5C1B84 + 20;
            field_106_current_motion = eSligMotions::M_StandIdle_0_4B4EC0;
            return field_11C_ai_sub_state;
        }
        break;

    case AI_Possessed::eState2_PossessionInactive_2:
        if (static_cast<int>(sGnFrame_5C1B84) >= field_120_timer)
        {
            if (Math_NextRandom() & 1)
            {
                field_120_timer = sGnFrame_5C1B84 + 20;
                field_106_current_motion = eSligMotions::M_SpeakHi_21_4B53D0;
                Sfx_Slig_GameSpeak_4C04F0(SligSpeak::Hi_0, 0, field_11E, this);
            }
            else
            {
                field_120_timer = sGnFrame_5C1B84 + 20;
                field_106_current_motion = eSligMotions::M_SpeakLaugh_24_4B5430;
                Sfx_Slig_GameSpeak_4C04F0(SligSpeak::Laugh_3, 0, field_11E, this);
            }
            field_11C_ai_sub_state = AI_Possessed::eState2_PossessionSpeak_3;
            return field_11C_ai_sub_state;
        }
        break;

    case AI_Possessed::eState2_PossessionSpeak_3:
        if (Event_Get_422C00(kEventDeathReset))
        {
            if (sControlledCharacter_5C1B8C != this)
            {
                field_6_flags.Set(BaseGameObject::eDead);
            }
        }

        if (static_cast<int>(sGnFrame_5C1B84) >= field_120_timer)
        {
            field_11C_ai_sub_state = AI_Possessed::eState2_ControlledByPlayer_4;
            field_10C_health = FP_FromInteger(1);
            return field_11C_ai_sub_state;
        }
        break;

    case AI_Possessed::eState2_ControlledByPlayer_4:
        if (Event_Get_422C00(kEventDeathReset))
        {
            if (sControlledCharacter_5C1B8C != this)
            {
                field_6_flags.Set(BaseGameObject::eDead);
            }
        }
        if (field_10C_health <= FP_FromInteger(0))
        {
            SetBrain(&Slig::AI_Death_0_4BBFB0);
            field_120_timer = sGnFrame_5C1B84 + 60;
            return field_11C_ai_sub_state;
        }
        break;

    default:
        return field_11C_ai_sub_state;
    }

    if (static_cast<int>(sGnFrame_5C1B84) < field_120_timer)
    {
        if (field_114_flags.Get(Flags_114::e114_Bit1_bShot))
        {
            BlowUp_4B8020();
        }
    }

    return field_11C_ai_sub_state;
}

__int16 Slig::AI_DeathDropDeath_3_4BC1E0()
{
    if (field_11C_ai_sub_state == 0)
    {
        Sfx_Slig_GameSpeak_4C04F0(SligSpeak::Help_10, 0, field_11E, this);
        field_120_timer = sGnFrame_5C1B84 + 60;
        return 1;
    }

    // TODO: Detangle compiler mashed up switch/case
    const auto v3 = field_11C_ai_sub_state - 1;
    if (v3)
    {
        if (v3 != 1 || static_cast<int>(sGnFrame_5C1B84) <= field_120_timer)
        {
            return field_11C_ai_sub_state;
        }

        if (sControlledCharacter_5C1B8C == this)
        {
            MusicController::sub_47FD60(0, this, 0, 0);
            sControlledCharacter_5C1B8C = sActiveHero_5C1B68;
            gMap_5C3030.SetActiveCam_480D30(field_146_level, field_148_path, field_14A_camera, CameraSwapEffects::eEffect0_InstantChange, 0, 0);
        }

        field_6_flags.Set(BaseGameObject::eDead);
        return field_11C_ai_sub_state;
    }

    if (static_cast<int>(sGnFrame_5C1B84) < field_120_timer)
    {
        if (!((field_120_timer - sGnFrame_5C1B84) % 15))
        {
            Sfx_Slig_GameSpeak_4C04F0(
                SligSpeak::Help_10,
                static_cast<short>(2 * ((field_120_timer & 0xFFFF) - sGnFrame_5C1B84)),
                field_11E,
                this);
        }

        if (static_cast<int>(sGnFrame_5C1B84) == field_120_timer - 6)
        {
            SND_SEQ_Play_4CAB10(SeqId::HitBottomOfDeathPit_9, 1, 65, 65);
        }

        return field_11C_ai_sub_state;
    }

    Abe_SFX_2_457A40(15, 0, 0x7FFF, this);

    auto pScreenShake = alive_new<ScreenShake>();
    if (pScreenShake)
    {
        pScreenShake->ctor_4ACF70(0, 0);
    }

    field_120_timer = sGnFrame_5C1B84 + 30;
    return 2;
}

const __int16 sGlukkonResponseTable_560768[8][6] =
{
    { eSligMotions::M_StandIdle_0_4B4EC0, eSligMotions::M_SpeakHi_21_4B53D0, -1, 0, 0, 0 },
    { eSligMotions::M_StandIdle_0_4B4EC0, eSligMotions::M_SpeakWhat_29_4B54D0, -1, 0, 0, 0 },
    { eSligMotions::M_StandIdle_0_4B4EC0, eSligMotions::M_SpeakBullShit1_25_4B5450, -1, 0, 0, 0 },
    { eSligMotions::M_StandIdle_0_4B4EC0, eSligMotions::M_SpeakBullShit2_27_4B5490, -1, 0, 0, 0 },
    { eSligMotions::M_Walking_2_4B5BC0, -1, 0, 0, 0, 0 },
    { eSligMotions::M_Running_4_4B6000, -1, 0, 0, 0, 0 },
    { eSligMotions::M_StandIdle_0_4B4EC0, eSligMotions::M_SpeakLaugh_24_4B5430, -1, 0, 0, 0 },
    { eSligMotions::M_StandIdle_0_4B4EC0, eSligMotions::M_ReloadGun_12_4B5530, eSligMotions::M_ReloadGun_12_4B5530, eSligMotions::M_ReloadGun_12_4B5530, eSligMotions::M_ReloadGun_12_4B5530, -1 }
};


enum AI_ListeningToGlukkon_States
{
    GettingAttention_0 = 0,
    IdleListening_1 = 1,
    Moving_2 = 2,
    NextToLeverThroughComeHere_3 = 3,
    Speaking_4 = 4,
    StoppingNextToLever_5 = 5,
    PullingLever_6 = 6,
    StoppingOnLift_7 = 7,
    Shooting_8 = 8,
    LostAttention_9 = 9,
};

enum AI_ListeningToGlukkon_GlukkonCommands
{
    HeyOrAllYa_0 = 0,
    What_1 = 1,
    Stay_2 = 2,
    Bs_3 = 3,
    Walk_4 = 4,
    Run_5 = 5,
    AfterShootOrLaugh_6 = 6,
    DoitGunReload_7 = 7,
};

__int16 Slig::AI_ListeningToGlukkon_4_4B9D20()
{
    auto pGlukkonObj = static_cast<BaseAliveGameObject*>(sObjectIds_5C1B70.Find_449CF0(field_208_glukkon_obj_id));
    auto pPlatformObj = static_cast<LiftPoint*>(sObjectIds_5C1B70.Find_449CF0(field_110_id));

    field_216.Clear(Flags_216::eBit4_HeardGlukkon);

    if (!pGlukkonObj || !pGlukkonObj->field_6_flags.Get(BaseGameObject::eDrawable))
    {
        PauseALittle_4BDD00();
        field_108_next_motion = eSligMotions::M_SpeakLaugh_24_4B5430;
        field_216.Clear(Flags_216::eBit1_FollowGlukkon);
        --sSligsUnderControlCount_BAF7E8;
        return AI_ListeningToGlukkon_States::GettingAttention_0;
    }

    switch (field_11C_ai_sub_state)
    {
    case AI_ListeningToGlukkon_States::GettingAttention_0:           return AI_ListenToGlukkon_GettingAttention(pGlukkonObj);
    case AI_ListeningToGlukkon_States::IdleListening_1:              return AI_ListenToGlukkon_IdleListen(pGlukkonObj, pPlatformObj);
    case AI_ListeningToGlukkon_States::Moving_2:                     return AI_ListenToGlukkon_Moving(pGlukkonObj);
    case AI_ListeningToGlukkon_States::NextToLeverThroughComeHere_3: return AI_ListenToGlukkon_NextLever(pGlukkonObj);
    case AI_ListeningToGlukkon_States::Speaking_4:                   return AI_ListenToGlukkon_Speaking();
    case AI_ListeningToGlukkon_States::StoppingNextToLever_5:        return AI_ListenToGlukkon_StoppingNextToLever();
    case AI_ListeningToGlukkon_States::PullingLever_6:               return AI_ListeningToGlukkon_PullingLever();
    case AI_ListeningToGlukkon_States::StoppingOnLift_7:             return AI_ListeningToGlukkon_StoppingOnLift(pPlatformObj);
    case AI_ListeningToGlukkon_States::Shooting_8:                   return AI_ListeningToGlukkon_Shooting();
    case AI_ListeningToGlukkon_States::LostAttention_9:              return AI_ListeningToGlukkon_LostAttention();
    default:
        field_11C_ai_sub_state = AI_ListeningToGlukkon_States::GettingAttention_0;
        return field_11C_ai_sub_state;
    }
}

__int16 Slig::AI_ListeningToGlukkon_LostAttention()
{
    SetBrain(&Slig::AI_Paused_33_4B8DD0);
    return field_11C_ai_sub_state;
}

__int16 Slig::AI_ListeningToGlukkon_Shooting()
{
    LastGlukkonSpeak_4B3090();
    if (static_cast<int>(sGnFrame_5C1B84) == field_120_timer - 15)
    {
        field_108_next_motion = eSligMotions::M_Shoot_6_4B55A0;
    }

    if (static_cast<int>(sGnFrame_5C1B84) <= field_120_timer)
    {
        return field_11C_ai_sub_state;
    }
    NextCommand_4B9A00(AI_ListeningToGlukkon_GlukkonCommands::AfterShootOrLaugh_6, AI_ListeningToGlukkon_States::IdleListening_1);
    return AI_ListeningToGlukkon_States::Speaking_4;
}

__int16 Slig::AI_ListeningToGlukkon_StoppingOnLift(LiftPoint* pPlatformObj)
{
    const FP gridSize = ScaleToGridSize_4498B0(field_CC_sprite_scale);

    if (field_106_current_motion == eSligMotions::M_Knockback_34_4B68A0)
    {
        field_108_next_motion = eSligMotions::M_StandIdle_0_4B4EC0;
        return AI_ListeningToGlukkon_States::IdleListening_1;
    }

    if (field_106_current_motion != eSligMotions::M_StandIdle_0_4B4EC0)
    {
        return field_11C_ai_sub_state;
    }

    if (field_20_animation.field_4_flags.Get(AnimFlags::eBit5_FlipX))
    {
        if (!pPlatformObj)
        {
            return AI_ListeningToGlukkon_States::IdleListening_1;
        }

        if (pPlatformObj->field_4_typeId != Types::eLiftPoint_78)
        {
            return AI_ListeningToGlukkon_States::IdleListening_1;
        }

        const FP v82 = (gridSize / FP_FromInteger(2));
        const FP v84 = field_B8_xpos - gridSize -
            FP_FromInteger((field_100_pCollisionLine->field_0_rect.x + field_100_pCollisionLine->field_0_rect.w) / 2) >= FP_FromInteger(0) ?
            field_B8_xpos - gridSize -
            FP_FromInteger((field_100_pCollisionLine->field_0_rect.x + field_100_pCollisionLine->field_0_rect.w) / 2) :
            FP_FromInteger((field_100_pCollisionLine->field_0_rect.x + field_100_pCollisionLine->field_0_rect.w) / 2) -
            (field_B8_xpos - gridSize);
        if (v84 >= v82)
        {
            return AI_ListeningToGlukkon_States::IdleListening_1;
        }
        field_108_next_motion = eSligMotions::M_SteppingToStand_14_4B8480;
        field_C4_velx = -(gridSize / FP_FromInteger(6));
        return field_11C_ai_sub_state;
    }

    if (!pPlatformObj)
    {
        return AI_ListeningToGlukkon_States::IdleListening_1;
    }

    if (pPlatformObj->field_4_typeId != Types::eLiftPoint_78)
    {
        return AI_ListeningToGlukkon_States::IdleListening_1;
    }

    const FP v90 = field_B8_xpos + gridSize - FP_FromInteger((field_100_pCollisionLine->field_0_rect.x + field_100_pCollisionLine->field_0_rect.w) / 2) >= FP_FromInteger(0) ?
        field_B8_xpos + gridSize
        - FP_FromInteger((field_100_pCollisionLine->field_0_rect.x + field_100_pCollisionLine->field_0_rect.w) / 2) :
        FP_FromInteger((field_100_pCollisionLine->field_0_rect.x + field_100_pCollisionLine->field_0_rect.w) / 2)
        - (field_B8_xpos + gridSize);
    if (v90 >= gridSize / FP_FromInteger(2))
    {
        return AI_ListeningToGlukkon_States::IdleListening_1;
    }
    field_C4_velx = (gridSize / FP_FromInteger(6));
    field_108_next_motion = eSligMotions::M_SteppingToStand_14_4B8480;
    return field_11C_ai_sub_state;
}

__int16 Slig::AI_ListeningToGlukkon_PullingLever()
{
    const FP gridSize = ScaleToGridSize_4498B0(field_CC_sprite_scale);

    Switch* pLever = nullptr;
    if (field_20_animation.field_4_flags.Get(AnimFlags::eBit5_FlipX))
    {
        pLever = static_cast<Switch*>(FindObjectOfType_425180(Types::eLever_139, field_B8_xpos - gridSize, field_BC_ypos - FP_FromInteger(5)));
    }
    else
    {
        pLever = static_cast<Switch*>(FindObjectOfType_425180(Types::eLever_139, field_B8_xpos + gridSize, field_BC_ypos - FP_FromInteger(5)));
    }

    if (pLever)
    {
        if (field_106_current_motion == eSligMotions::M_PullLever_45_4B8950)
        {
            pLever->Vsub_4D6050(field_B8_xpos < pLever->field_B8_xpos);
            field_108_next_motion = eSligMotions::M_StandIdle_0_4B4EC0;
            return AI_ListeningToGlukkon_States::IdleListening_1;
        }
        else
        {
            field_108_next_motion = eSligMotions::M_PullLever_45_4B8950;
            return field_11C_ai_sub_state;
        }
    }
    else
    {
        field_108_next_motion = eSligMotions::M_TurnAroundStanding_5_4B6390;
        return field_11C_ai_sub_state;
    }
}

__int16 Slig::AI_ListenToGlukkon_StoppingNextToLever()
{
    const FP gridSize = ScaleToGridSize_4498B0(field_CC_sprite_scale);

    if (field_106_current_motion == eSligMotions::M_Knockback_34_4B68A0)
    {
        field_108_next_motion = eSligMotions::M_StandIdle_0_4B4EC0;
        return AI_ListeningToGlukkon_States::IdleListening_1;
    }

    if (field_106_current_motion != eSligMotions::M_StandIdle_0_4B4EC0)
    {
        return field_11C_ai_sub_state;
    }

    if (!FindObjectOfType_425180(Types::eLever_139, gridSize + field_B8_xpos, field_BC_ypos - FP_FromInteger(5)))
    {
        if (!FindObjectOfType_425180(Types::eLever_139, field_B8_xpos - gridSize, field_BC_ypos - FP_FromInteger(5)))
        {
            if (field_20_animation.field_4_flags.Get(AnimFlags::eBit5_FlipX))
            {
                field_108_next_motion = eSligMotions::M_SteppingToStand_14_4B8480;
                field_C4_velx = -(ScaleToGridSize_4498B0(field_CC_sprite_scale) / FP_FromInteger(6));
                return field_11C_ai_sub_state;
            }
            field_C4_velx = (gridSize / FP_FromInteger(6));
            field_108_next_motion = eSligMotions::M_SteppingToStand_14_4B8480;
            return field_11C_ai_sub_state;
        }
    }

    if ((!FindObjectOfType_425180(Types::eLever_139, gridSize + field_B8_xpos, field_BC_ypos - FP_FromInteger(5)) || !(field_20_animation.field_4_flags.Get(AnimFlags::eBit5_FlipX))) &&
        (!FindObjectOfType_425180(Types::eLever_139, field_B8_xpos - gridSize, field_BC_ypos - FP_FromInteger(5)) || field_20_animation.field_4_flags.Get(AnimFlags::eBit5_FlipX)))
    {
        return AI_ListeningToGlukkon_States::IdleListening_1;
    }

    field_108_next_motion = eSligMotions::M_TurnAroundStanding_5_4B6390;
    return field_11C_ai_sub_state;
}

__int16 Slig::AI_ListenToGlukkon_Speaking()
{
    if (static_cast<int>(sGnFrame_5C1B84) <= field_120_timer)
    {
        return field_11C_ai_sub_state;
    }

    if (field_108_next_motion == eSligMotions::M_TurnAroundStanding_5_4B6390)
    {
        return field_11C_ai_sub_state;
    }

    field_120_timer = sGnFrame_5C1B84 + 8;

    field_108_next_motion = sGlukkonResponseTable_560768[field_212_next_command_arg1][field_214_cmd_idx];

    // keeps going till it hits -1
    field_214_cmd_idx++;

    if (sGlukkonResponseTable_560768[field_212_next_command_arg1][field_214_cmd_idx] != -1)
    {
        return field_11C_ai_sub_state;
    }

    return field_20C_state_after_speak;
}

__int16 Slig::AI_ListenToGlukkon_NextLever(BaseAliveGameObject* pGlukkonObj)
{
    if (!vIsFacingMe_4254A0(pGlukkonObj))
    {
        field_108_next_motion = eSligMotions::M_TurnAroundStanding_5_4B6390;
        return field_11C_ai_sub_state;
    }

    if (field_106_current_motion != eSligMotions::M_StandIdle_0_4B4EC0)
    {
        return field_11C_ai_sub_state;
    }

    if (field_20_animation.field_4_flags.Get(AnimFlags::eBit5_FlipX))
    {
        field_C4_velx = -(ScaleToGridSize_4498B0(field_CC_sprite_scale) / FP_FromInteger(6));
    }
    else
    {
        field_C4_velx = (ScaleToGridSize_4498B0(field_CC_sprite_scale) / FP_FromInteger(6));
    }

    field_108_next_motion = eSligMotions::M_SteppingToStand_14_4B8480;
    return AI_ListeningToGlukkon_States::IdleListening_1;
}

__int16 Slig::AI_ListenToGlukkon_Moving(BaseAliveGameObject* pGlukkonObj)
{
    FP v46 = (ScaleToGridSize_4498B0(field_CC_sprite_scale) * FP_FromInteger(field_106_current_motion != eSligMotions::M_Running_4_4B6000 ? 1 : 3));
    if (field_20_animation.field_4_flags.Get(AnimFlags::eBit5_FlipX))
    {
        v46 = -v46;
    }

    if (WallHit_408750(field_CC_sprite_scale * FP_FromInteger(45), v46))
    {
        field_108_next_motion = eSligMotions::M_StandIdle_0_4B4EC0;
        return AI_ListeningToGlukkon_States::IdleListening_1;
    }

    if (field_106_current_motion == eSligMotions::M_StandIdle_0_4B4EC0)
    {
        if (field_108_next_motion != eSligMotions::M_Walking_2_4B5BC0 && field_108_next_motion != eSligMotions::M_Running_4_4B6000)
        {
            return AI_ListeningToGlukkon_States::IdleListening_1;
        }
    }

    if (field_106_current_motion == eSligMotions::M_Knockback_34_4B68A0)
    {
        field_108_next_motion = eSligMotions::M_StandIdle_0_4B4EC0;
        return AI_ListeningToGlukkon_States::IdleListening_1;
    }

    if (field_106_current_motion != eSligMotions::M_Walking_2_4B5BC0 && field_106_current_motion != eSligMotions::M_Running_4_4B6000)
    {
        return field_11C_ai_sub_state;
    }

    if (field_106_current_motion != eSligMotions::M_Running_4_4B6000 && FindSwitch_4B9A50())
    {
        field_108_next_motion = eSligMotions::M_StandIdle_0_4B4EC0;
        field_216.Clear(Flags_216::eBit1_FollowGlukkon);
        field_216.Set(Flags_216::eBit2);
        return AI_ListeningToGlukkon_States::StoppingNextToLever_5;
    }

    if (field_106_current_motion != eSligMotions::M_Running_4_4B6000 && FindLiftPoint_4B9B40())
    {
        field_108_next_motion = eSligMotions::M_StandIdle_0_4B4EC0;
        field_216.Clear(Flags_216::eBit1_FollowGlukkon);
        field_216.Set(Flags_216::eBit2);
        return AI_ListeningToGlukkon_States::StoppingOnLift_7;
    }

    if (!vIsFacingMe_4254A0(pGlukkonObj))
    {
        field_108_next_motion = eSligMotions::M_StandIdle_0_4B4EC0;
        return AI_ListeningToGlukkon_States::IdleListening_1;
    }

    if (vIsObjNearby_4253B0(ScaleToGridSize_4498B0(field_CC_sprite_scale), pGlukkonObj))
    {
        field_108_next_motion = eSligMotions::M_StandIdle_0_4B4EC0;
        return AI_ListeningToGlukkon_States::IdleListening_1;
    }

    if (field_160 != pEventSystem_5BC11C->field_28_last_event_index)
    {
        field_160 = pEventSystem_5BC11C->field_28_last_event_index;
        if (pEventSystem_5BC11C->field_20_last_event == GameSpeakEvents::Glukkon_StayHere_38 &&
            gMap_5C3030.Is_Point_In_Current_Camera_4810D0(field_C2_lvl_number, field_C0_path_number, field_B8_xpos, field_BC_ypos, 0))
        {
            field_216.Clear(Flags_216::eBit1_FollowGlukkon);
            NextCommand_4B9A00(AI_ListeningToGlukkon_GlukkonCommands::Stay_2, AI_ListeningToGlukkon_States::IdleListening_1);
            return AI_ListeningToGlukkon_States::Speaking_4;
        }
    }

    if (!vIsObjNearby_4253B0(ScaleToGridSize_4498B0(field_CC_sprite_scale) * FP_FromInteger(5), pGlukkonObj))
    {
        if (field_106_current_motion == eSligMotions::M_Walking_2_4B5BC0)
        {
            field_108_next_motion = eSligMotions::M_Running_4_4B6000;
            return AI_ListeningToGlukkon_States::Moving_2;
        }
    }

    if (!vIsObjNearby_4253B0(ScaleToGridSize_4498B0(field_CC_sprite_scale) * FP_FromInteger(5), pGlukkonObj) || field_106_current_motion != eSligMotions::M_Running_4_4B6000)
    {
        return field_11C_ai_sub_state;
    }

    field_108_next_motion = eSligMotions::M_Walking_2_4B5BC0;
    return AI_ListeningToGlukkon_States::Moving_2;
}

__int16 Slig::AI_ListenToGlukkon_IdleListen(BaseAliveGameObject* pGlukkonObj, LiftPoint* pPlatformObj)
{
    if (field_106_current_motion != eSligMotions::M_StandIdle_0_4B4EC0)
    {
        field_20E = 0;
        return field_11C_ai_sub_state;
    }

    if (field_216.Get(Flags_216::eBit1_FollowGlukkon))
    {
        field_20E++;
    }

    field_216.Clear(Flags_216::eBit2);

    FP directedGridSize = {};
    if (field_20_animation.field_4_flags.Get(AnimFlags::eBit5_FlipX))
    {
        directedGridSize = -ScaleToGridSize_4498B0(field_CC_sprite_scale);
    }
    else
    {
        directedGridSize = ScaleToGridSize_4498B0(field_CC_sprite_scale);
    }

    const FP gridSize = ScaleToGridSize_4498B0(field_CC_sprite_scale);

    const int bWallHit = WallHit_408750(field_CC_sprite_scale * FP_FromInteger(45), directedGridSize);
    if (field_20E <= 450 &&
        (gMap_5C3030.Is_Point_In_Current_Camera_4810D0(field_C2_lvl_number, field_C0_path_number, field_B8_xpos, field_BC_ypos, 1) || field_216.Get(Flags_216::eBit1_FollowGlukkon)))
    {
        if (field_216.Get(Flags_216::eBit1_FollowGlukkon))
        {
            if (!vIsObjNearby_4253B0(gridSize, pGlukkonObj))
            {
                if (!vIsFacingMe_4254A0(pGlukkonObj))
                {
                    field_108_next_motion = eSligMotions::M_TurnAroundStanding_5_4B6390;
                    return field_11C_ai_sub_state;
                }

                if (vIsObjNearby_4253B0(gridSize * FP_FromInteger(5), pGlukkonObj) &&
                    pGlukkonObj->field_106_current_motion != eSligMotions::M_Running_4_4B6000)
                {
                    if (!bWallHit)
                    {
                        if (FindLiftPoint_4B9B40())
                        {
                            field_216.Clear(Flags_216::eBit1_FollowGlukkon);
                            return AI_ListeningToGlukkon_States::StoppingOnLift_7;
                        }
                        else
                        {
                            NextCommand_4B9A00(AI_ListeningToGlukkon_GlukkonCommands::Walk_4, AI_ListeningToGlukkon_States::Moving_2);
                            return AI_ListeningToGlukkon_States::Speaking_4;
                        }
                    }
                }
                else
                {
                    if (field_20_animation.field_4_flags.Get(AnimFlags::eBit5_FlipX))
                    {
                        directedGridSize = -ScaleToGridSize_4498B0(field_CC_sprite_scale);
                    }
                    else
                    {
                        directedGridSize = ScaleToGridSize_4498B0(field_CC_sprite_scale);
                    }

                    if (!WallHit_408750(field_CC_sprite_scale * FP_FromInteger(45), directedGridSize * FP_FromInteger(3)))
                    {
                        NextCommand_4B9A00(AI_ListeningToGlukkon_GlukkonCommands::Run_5, AI_ListeningToGlukkon_States::Moving_2);
                        return AI_ListeningToGlukkon_States::Speaking_4;
                    }
                }
            }

            if (sSligsUnderControlCount_BAF7E8 > 1)
            {
                auto pOtherSlig = static_cast<Slig*>(FindObjectOfType_425180(Types::eSlig_125, field_B8_xpos, field_BC_ypos - FP_FromInteger(5)));
                if (pOtherSlig)
                {
                    if (pOtherSlig != this && !vIsFacingMe_4254A0(pOtherSlig) && pOtherSlig->field_106_current_motion != eSligMotions::M_TurnAroundStanding_5_4B6390)
                    {
                        field_108_next_motion = eSligMotions::M_TurnAroundStanding_5_4B6390;
                        return field_11C_ai_sub_state;
                    }
                }
            }
        }

        const GameSpeakEvents glukkonSpeak = LastGlukkonSpeak_4B3090();
        if (glukkonSpeak == GameSpeakEvents::eNone_m1 || glukkonSpeak == GameSpeakEvents::eSameAsLast_m2)
        {
            return field_11C_ai_sub_state;
        }

        if (glukkonSpeak == GameSpeakEvents::Glukkon_AllOYa_40)
        {
            NextCommand_4B9A00(AI_ListeningToGlukkon_GlukkonCommands::HeyOrAllYa_0, AI_ListeningToGlukkon_States::IdleListening_1);
        }
        else
        {
            if (glukkonSpeak == GameSpeakEvents::Glukkon_Laugh_43)
            {
                NextCommand_4B9A00(AI_ListeningToGlukkon_GlukkonCommands::AfterShootOrLaugh_6, AI_ListeningToGlukkon_States::IdleListening_1);
            }
            else
            {
                if (!field_216.Get(Flags_216::eBit3) || glukkonSpeak == GameSpeakEvents::Glukkon_Hey_36)
                {
                    if (!HeardGlukkonToListenTo_4B9690(glukkonSpeak))
                    {
                        field_216.Set(Flags_216::eBit3, glukkonSpeak == GameSpeakEvents::Glukkon_AllOYa_40);
                        return field_11C_ai_sub_state;
                    }
                }

                switch (glukkonSpeak)
                {
                case GameSpeakEvents::Glukkon_Hey_36:
                    if (!vIsFacingMe_4254A0(pGlukkonObj))
                    {
                        field_108_next_motion = eSligMotions::M_TurnAroundStanding_5_4B6390;
                    }
                    NextCommand_4B9A00(AI_ListeningToGlukkon_GlukkonCommands::HeyOrAllYa_0, AI_ListeningToGlukkon_States::IdleListening_1);
                    break;

                case GameSpeakEvents::Glukkon_DoIt_37:
                    if (pPlatformObj && pPlatformObj->field_4_typeId == Types::eLiftPoint_78)
                    {
                        const FP scaled_2 = (ScaleToGridSize_4498B0(field_CC_sprite_scale) / FP_FromInteger(2));
                        const FP lineMidX = FP_FromInteger((field_100_pCollisionLine->field_0_rect.x + field_100_pCollisionLine->field_0_rect.w) / 2);
                        const FP v33 = field_B8_xpos - lineMidX >= FP_FromInteger(0) ? field_B8_xpos - lineMidX : lineMidX - field_B8_xpos;
                        if (v33 < scaled_2 && (pPlatformObj->vOnTopFloor_461890() || pPlatformObj->vOnBottomFloor_4618F0()))
                        {
                            field_108_next_motion = eSligMotions::M_LiftGrip_46_4B3700;

                            for (int i = 0; i < gBaseAliveGameObjects_5C1B7C->Size(); i++)
                            {
                                BaseAliveGameObject* pFoundSlig = gBaseAliveGameObjects_5C1B7C->ItemAt(i);
                                if (!pFoundSlig)
                                {
                                    break;
                                }

                                if (pFoundSlig->field_4_typeId == Types::eSlig_125 && pFoundSlig != this && pFoundSlig->field_108_next_motion == eSligMotions::M_LiftGrip_46_4B3700)
                                {
                                    field_108_next_motion = eSligMotions::M_StandIdle_0_4B4EC0;
                                }
                            }

                            field_11C_ai_sub_state = AI_ListeningToGlukkon_States::IdleListening_1;
                            field_216.Set(Flags_216::eBit3, glukkonSpeak == GameSpeakEvents::Glukkon_AllOYa_40);
                            return field_11C_ai_sub_state;
                        }
                    }

                    if (FindObjectOfType_425180(Types::eLever_139, ScaleToGridSize_4498B0(field_CC_sprite_scale) + field_B8_xpos, field_BC_ypos - FP_FromInteger(5)) ||
                        FindObjectOfType_425180(Types::eLever_139, field_B8_xpos - ScaleToGridSize_4498B0(field_CC_sprite_scale), field_BC_ypos - FP_FromInteger(5)))
                    {
                        field_11C_ai_sub_state = AI_ListeningToGlukkon_States::PullingLever_6;
                        field_216.Set(Flags_216::eBit3, glukkonSpeak == GameSpeakEvents::Glukkon_AllOYa_40);
                        return field_11C_ai_sub_state;
                    }
                    
                    if (!FindObjectOfType_425180(Types::eMudokon_110, field_B8_xpos, field_BC_ypos - FP_FromInteger(5)))
                    {
                        const FP v42 = field_20_animation.field_4_flags.Get(AnimFlags::eBit5_FlipX) ?
                            -ScaleToGridSize_4498B0(field_CC_sprite_scale) :
                            ScaleToGridSize_4498B0(field_CC_sprite_scale);
                    
                        if (!FindObjectOfType_425180(Types::eMudokon_110, v42 + field_B8_xpos, field_BC_ypos - FP_FromInteger(5)))
                        {
                            NextCommand_4B9A00(AI_ListeningToGlukkon_GlukkonCommands::DoitGunReload_7, AI_ListeningToGlukkon_States::LostAttention_9);
                            field_11C_ai_sub_state = AI_ListeningToGlukkon_States::Speaking_4;
                            --sSligsUnderControlCount_BAF7E8;
                            field_216.Set(Flags_216::eBit3, glukkonSpeak == GameSpeakEvents::Glukkon_AllOYa_40);
                            return field_11C_ai_sub_state;
                        }
                    }

                    field_108_next_motion = eSligMotions::M_Beat_51_4B6C00;
                    
                    field_11C_ai_sub_state = AI_ListeningToGlukkon_States::IdleListening_1;
                    field_216.Set(Flags_216::eBit3, glukkonSpeak == GameSpeakEvents::Glukkon_AllOYa_40);
                    return field_11C_ai_sub_state;

                case GameSpeakEvents::Glukkon_StayHere_38:
                    field_216.Clear(Flags_216::eBit1_FollowGlukkon);
                    NextCommand_4B9A00(AI_ListeningToGlukkon_GlukkonCommands::Stay_2, AI_ListeningToGlukkon_States::IdleListening_1);
                    break;

                case GameSpeakEvents::Glukkon_Commere_39:
                    field_216.Set(Flags_216::eBit1_FollowGlukkon);
                    if (vIsObjNearby_4253B0(gridSize, pGlukkonObj))
                    {
                        if (!vIsObjNearby_4253B0(gridSize * FP_FromDouble(0.5), pGlukkonObj))
                        {
                            field_11C_ai_sub_state = AI_ListeningToGlukkon_States::NextToLeverThroughComeHere_3;
                            field_216.Set(Flags_216::eBit3, glukkonSpeak == GameSpeakEvents::Glukkon_AllOYa_40);
                            return field_11C_ai_sub_state;
                        }
                    }

                    if (FindLiftPoint_4B9B40())
                    {
                        field_216.Clear(Flags_216::eBit1_FollowGlukkon);
                        field_11C_ai_sub_state = AI_ListeningToGlukkon_States::StoppingOnLift_7;
                        field_216.Set(Flags_216::eBit3, glukkonSpeak == GameSpeakEvents::Glukkon_AllOYa_40);
                        return field_11C_ai_sub_state;
                    }

                    if (bWallHit)
                    {
                        NextCommand_4B9A00(AI_ListeningToGlukkon_GlukkonCommands::Bs_3, AI_ListeningToGlukkon_States::IdleListening_1);
                    }
                    else
                    {
                        if (!vIsFacingMe_4254A0(pGlukkonObj))
                        {
                            field_108_next_motion = eSligMotions::M_TurnAroundStanding_5_4B6390;
                        }
                        NextCommand_4B9A00(AI_ListeningToGlukkon_GlukkonCommands::Stay_2, AI_ListeningToGlukkon_States::IdleListening_1);
                    }
                    break;

                case GameSpeakEvents::Glukkon_KillEm_44:
                    field_11C_ai_sub_state = AI_ListeningToGlukkon_States::Shooting_8;
                    field_120_timer = sGnFrame_5C1B84 + 25;
                    field_216.Set(Flags_216::eBit3, glukkonSpeak == GameSpeakEvents::Glukkon_AllOYa_40);
                    return field_11C_ai_sub_state;

                default:
                    field_216.Set(Flags_216::eBit3, glukkonSpeak == GameSpeakEvents::Glukkon_AllOYa_40);
                    return field_11C_ai_sub_state;
                }
            }
        }
        field_11C_ai_sub_state = AI_ListeningToGlukkon_States::Speaking_4;
        field_216.Set(Flags_216::eBit3, glukkonSpeak == GameSpeakEvents::Glukkon_AllOYa_40);
        return field_11C_ai_sub_state;
    }

    PauseALittle_4BDD00();
    field_216.Clear(Flags_216::eBit1_FollowGlukkon);
    --sSligsUnderControlCount_BAF7E8;
    return AI_ListeningToGlukkon_States::GettingAttention_0;
}

__int16 Slig::AI_ListenToGlukkon_GettingAttention(BaseAliveGameObject* pGlukkonObj)
{
    field_108_next_motion = eSligMotions::M_StandIdle_0_4B4EC0;
    field_20E = 0;
    field_216.Clear(Flags_216::eBit1_FollowGlukkon);
    field_216.Clear(Flags_216::eBit2);
    if (!vIsFacingMe_4254A0(pGlukkonObj))
    {
        field_108_next_motion = eSligMotions::M_TurnAroundStanding_5_4B6390;
    }
    NextCommand_4B9A00(AI_ListeningToGlukkon_GlukkonCommands::HeyOrAllYa_0, AI_ListeningToGlukkon_States::IdleListening_1);
    return AI_ListeningToGlukkon_States::Speaking_4;
}

__int16 Slig::AI_Empty_5_4B3220()
{
    NOT_IMPLEMENTED();
    return 0;
}

__int16 Slig::AI_Empty_6_4B3420()
{
    NOT_IMPLEMENTED();
    return 0;
}

__int16 Slig::AI_SpottedEnemy_7_4B3240()
{
    if (gMap_5C3030.Is_Point_In_Current_Camera_4810D0(field_C2_lvl_number, field_C0_path_number, field_B8_xpos, field_BC_ypos, 0) ||
        !field_218_tlv_data.field_2A_chase_abe)
    {
        if (vOnSameYLevel_425520(sControlledCharacter_5C1B8C) &&
            vIsObj_GettingNear_425420(sControlledCharacter_5C1B8C) && 
            vIsObjNearby_4253B0(ScaleToGridSize_4498B0(field_CC_sprite_scale) * FP_FromInteger(3), sControlledCharacter_5C1B8C) &&
            !Event_Get_422C00(kEventResetting) &&
            !sControlledCharacter_5C1B8C->field_114_flags.Get(Flags_114::e114_Bit8_bInvisible))
        {
            ToShoot_4BF9A0();
        }
        else if (
            vOnSameYLevel_425520(sControlledCharacter_5C1B8C) &&
            Event_Get_422C00(kEventAbeOhm) && 
            vIsFacingMe_4254A0(sControlledCharacter_5C1B8C))
        {
            ToShoot_4BF9A0();
        }
        else if (field_120_timer > static_cast<int>(sGnFrame_5C1B84))
        {
            if (sActiveHero_5C1B68->field_10C_health <= FP_FromInteger(0))
            {
                ToAbeDead_4B3580();
            }
            else
            {
                ShouldStilBeAlive_4BBC00();
            }
        }
        else if (vIsFacingMe_4254A0(sControlledCharacter_5C1B8C) && !sControlledCharacter_5C1B8C->field_114_flags.Get(Flags_114::e114_Bit8_bInvisible))
        {
            ToShoot_4BF9A0();
        }
        else
        {
            ToTurn_4BE090();
        }
    }
    else
    {
        ToChase_4BCFF0();
    }

    return 302;
}

__int16 Slig::AI_Empty_8_4B3120()
{
    NOT_IMPLEMENTED();
    return 0;
}

__int16 Slig::AI_Empty_9_4B3440()
{
    NOT_IMPLEMENTED();
    return 0;
}

__int16 Slig::AI_EnemyDead_10_4B3460()
{
    if (Event_Get_422C00(kEventDeathReset) && !gMap_5C3030.Is_Point_In_Current_Camera_4810D0(
            field_C2_lvl_number,
            field_C0_path_number,
            field_B8_xpos,
            field_BC_ypos,
            0))
    {
        field_6_flags.Set(BaseGameObject::eDead);
        return 113;
    }

    if (field_120_timer >= static_cast<int>(sGnFrame_5C1B84))
    {
        ShouldStilBeAlive_4BBC00();
    }
    else
    {
        const auto rnd = Math_NextRandom();
        
        // Say this often
        if (rnd < 25)
        {
            field_108_next_motion = eSligMotions::M_SpeakBullShit1_25_4B5450;
            field_120_timer = sGnFrame_5C1B84 + 15;
            return 113;
        }

        // Say this less often
        if (rnd < 50)
        {
            field_108_next_motion = eSligMotions::M_SpeakBullShit2_27_4B5490;
            field_120_timer = sGnFrame_5C1B84 + 15;
            return 113;
        }

        // And turn even less often
        if (sActiveHero_5C1B68->field_10C_health > FP_FromInteger(0))
        {
            TurnOrWalk_4BD6A0(0);
        }
    }
    return 113;

}

__int16 Slig::AI_KilledEnemy_10_4B35C0()
{
    if (field_120_timer > static_cast<int>(sGnFrame_5C1B84))
    {
        ShouldStilBeAlive_4BBC00();
    }
    else
    {
        ToAbeDead_4B3580();
    }
    return 114;
}

__int16 Slig::AI_PanicTurning_12_4BC490()
{
    if (Event_Get_422C00(kEventDeathReset) && 
        !gMap_5C3030.Is_Point_In_Current_Camera_4810D0(field_C2_lvl_number, field_C0_path_number, field_B8_xpos, field_BC_ypos, 0))
    {
        field_6_flags.Set(BaseGameObject::eDead);
        return 107;
    }

    if (ListenToGlukkonCommands_4B95D0())
    {
        ToUnderGlukkonCommand_4B9660();
        return 107;
    }

    bool checkForTurn = false;
    if (field_106_current_motion != eSligMotions::M_TurnAroundStanding_5_4B6390)
    {
        if (field_20_animation.field_4_flags.Get(AnimFlags::eBit18_IsLastFrame))
        {
            field_108_next_motion = eSligMotions::M_TurnAroundStanding_5_4B6390;
            return 107;
        }
        checkForTurn = true;
    }

    if (!field_20_animation.field_4_flags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        checkForTurn = true;
    }

    if (checkForTurn)
    {
        if (field_20_animation.field_92_current_frame == 4)
        {
            if (field_20_animation.field_4_flags.Get(AnimFlags::eBit5_FlipX))
            {
                if (sControlledCharacter_5C1B8C->field_C4_velx >= FP_FromInteger(0) &&
                    (sControlledCharacter_5C1B8C->field_C4_velx > FP_FromInteger(0) || sControlledCharacter_5C1B8C->field_B8_xpos >= field_B8_xpos))
                {
                    ShouldStilBeAlive_4BBC00();
                    return 107;
                }
            }
            else
            {
                if (sControlledCharacter_5C1B8C->field_C4_velx <= FP_FromInteger(0) &&
                    (sControlledCharacter_5C1B8C->field_C4_velx > FP_FromInteger(0) || sControlledCharacter_5C1B8C->field_B8_xpos <= field_B8_xpos))
                {
                    ShouldStilBeAlive_4BBC00();
                    return 107;
                }
            }

            PSX_RECT bRect = {};
            vGetBoundingRect_424FD0(&bRect, 1);

            PSX_RECT charRect = {};
            sControlledCharacter_5C1B8C->vGetBoundingRect_424FD0(&charRect, 1);

            if (sControlledCharacter_5C1B8C->field_4_typeId != Types::eGlukkon_67 &&
                sControlledCharacter_5C1B8C->field_4_typeId != Types::eSlig_125 &&
                !IsInInvisibleZone_425710(sControlledCharacter_5C1B8C) &&
                !sControlledCharacter_5C1B8C->field_114_flags.Get(Flags_114::e114_Bit8_bInvisible))
            {
                if (charRect.x <= bRect.w &&
                    charRect.w >= bRect.x &&
                    charRect.h >= bRect.y &&
                    charRect.y <= bRect.h)
                {
                    field_20_animation.field_4_flags.Toggle(AnimFlags::eBit5_FlipX);
                    return 107;
                }
            }
        }
        ShouldStilBeAlive_4BBC00();
        return 107;
    }

    if (field_120_timer > static_cast<int>(sGnFrame_5C1B84))
    {
        ToPanicRunning_4BCA30();
    }
    else
    {
        WaitOrWalk_4BE870();
    }
    return 107;
}

__int16 Slig::AI_PanicRunning_13_4BC780()
{
    if (field_C4_velx > FP_FromInteger(4) && ((ScaleToGridSize_4498B0(field_CC_sprite_scale) * FP_FromInteger(4)) + field_B8_xpos) > FP_FromInteger(field_138_zone_rect.w)) 
    {
        ToPanicTurn_4BC750();
    }
    else if (field_C4_velx < FP_FromInteger(-4) && (field_B8_xpos - (ScaleToGridSize_4498B0(field_CC_sprite_scale) * FP_FromInteger(4))) < FP_FromInteger(field_138_zone_rect.x))
    {
        ToPanicTurn_4BC750();
    }
    else if (HandleEnemyStopper_4BBA00(4))
    {
        ToPanicTurn_4BC750();
    }
    else if (ListenToGlukkonCommands_4B95D0())
    {
        ToUnderGlukkonCommand_4B9660();
    }
    else if (!field_106_current_motion && field_108_next_motion == -1)
    {
        ToPanicRunning_4BCA30();
    }
    else if (vOnSameYLevel_425520(sControlledCharacter_5C1B8C) && 
        sControlledCharacter_5C1B8C->field_4_typeId != Types::eGlukkon_67 &&
        vIsFacingMe_4254A0(sControlledCharacter_5C1B8C) &&
        !IsInInvisibleZone_425710(sControlledCharacter_5C1B8C) &&
        !sControlledCharacter_5C1B8C->field_114_flags.Get(Flags_114::e114_Bit8_bInvisible) &&
        !IsWallBetween_4BB8B0(this, sControlledCharacter_5C1B8C) &&
        gMap_5C3030.Is_Point_In_Current_Camera_4810D0(field_C2_lvl_number, field_C0_path_number, field_B8_xpos, field_BC_ypos, 0) &&
        gMap_5C3030.Is_Point_In_Current_Camera_4810D0(field_C2_lvl_number, field_C0_path_number, field_B8_xpos, field_BC_ypos, 0) &&
        !Event_Get_422C00(kEventResetting))
    {
        ToShoot_4BF9A0();
    }
    else if (sActiveHero_5C1B68->field_10C_health <= FP_FromInteger(0))
    {
        ToAbeDead_4B3580();
    }
    else
    {
        if (field_120_timer <= static_cast<int>(sGnFrame_5C1B84))
        {
            WaitOrWalk_4BE870();
        }
        else
        {
            ShouldStilBeAlive_4BBC00();
        }
    }
    return 109;
}

__int16 Slig::AI_PanicYelling_14_4BCA70()
{
    if (ListenToGlukkonCommands_4B95D0())
    {
        ToUnderGlukkonCommand_4B9660();
    }

    if (field_106_current_motion != eSligMotions::M_SpeakPanic_28_4B54B0)
    {
        if (field_108_next_motion != eSligMotions::M_SpeakPanic_28_4B54B0)
        {
            field_108_next_motion = eSligMotions::M_SpeakPanic_28_4B54B0;
        }

        if (field_106_current_motion != eSligMotions::M_SpeakPanic_28_4B54B0)
        {
            ShouldStilBeAlive_4BBC00();
            return 115;
        }
    }

    if (field_20_animation.field_4_flags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        Event_Broadcast_422BC0(kEventAlarm, this);

        const bool kFlipX = field_20_animation.field_4_flags.Get(AnimFlags::eBit5_FlipX);
        field_120_timer = sGnFrame_5C1B84 + field_218_tlv_data.field_2E_panic_timeout;
        if ((!kFlipX || field_B8_xpos >= FP_FromInteger((field_138_zone_rect.x + field_138_zone_rect.w) / 2)) && 
             (kFlipX || field_B8_xpos <= FP_FromInteger((field_138_zone_rect.x + field_138_zone_rect.w) / 2)))
        {
            ToPanicRunning_4BCA30();
        }
        else
        {
            ToPanicTurn_4BC750();
        }
    }
    else
    {
        ShouldStilBeAlive_4BBC00();
    }
    return 115;
}

__int16 Slig::AI_Idle_15_4BD800()
{
    if ((Event_Get_422C00(kEventAbeOhm) || Event_Get_422C00(kEventAlarm)) && !Event_Get_422C00(kEventResetting) && field_218_tlv_data.field_2E_panic_timeout)
    {
        ToPanicYelling_4BCBA0();
        return 104;
    }

    if (ListenToGlukkonCommands_4B95D0())
    {
        ToUnderGlukkonCommand_4B9660();
        return 104;
    }

    if (vOnSameYLevel_425520(sControlledCharacter_5C1B8C) &&
        vIsFacingMe_4254A0(sControlledCharacter_5C1B8C)  && 
        !IsInInvisibleZone_425710(sControlledCharacter_5C1B8C) &&
        !sControlledCharacter_5C1B8C->field_114_flags.Get(Flags_114::e114_Bit8_bInvisible) &&
        !IsWallBetween_4BB8B0(this, sControlledCharacter_5C1B8C) && 
        (!field_15E || sControlledCharacter_5C1B8C->field_4_typeId != Types::eSlig_125) &&
        !IsAbeEnteringDoor_4BB990(sControlledCharacter_5C1B8C) &&
        !Event_Get_422C00(kEventResetting) && 
        gMap_5C3030.Is_Point_In_Current_Camera_4810D0(field_C2_lvl_number, field_C0_path_number, field_B8_xpos, field_BC_ypos, 0) && 
        sControlledCharacter_5C1B8C->field_4_typeId != Types::eGlukkon_67)
    {
        ShootTurnTowardsOrKillSound_4B3140();
        return 104;
    }

    if (sActiveHero_5C1B68->field_10C_health <= FP_FromInteger(0))
    {
        ToAbeDead_4B3580();
        return 104;
    }

    auto pShooter = static_cast<BaseAliveGameObject*>(Event_Get_422C00(kEventShooting));
    if (pShooter && 
        pShooter->field_CC_sprite_scale == field_CC_sprite_scale &&
        gMap_5C3030.Is_Point_In_Current_Camera_4810D0(pShooter->field_C2_lvl_number, pShooter->field_C0_path_number, pShooter->field_B8_xpos, pShooter->field_BC_ypos, 0) &&
        pShooter == sControlledCharacter_5C1B8C &&
        gMap_5C3030.Is_Point_In_Current_Camera_4810D0(field_C2_lvl_number, field_C0_path_number, field_B8_xpos, field_BC_ypos, 0) &&
        !Event_Get_422C00(kEventResetting))
    {
        if (vIsFacingMe_4254A0(pShooter))
        {
            ShootTurnTowardsOrKillSound_4B3140();
            return 104;
        }
        else
        {
            ToTurn_4BE090();
            return 104;
        }
    }

    auto pNoiseOrSpeaking = static_cast<BaseAliveGameObject*>(Event_Get_422C00(kEventSuspiciousNoise));
    if (!pNoiseOrSpeaking)
    {
        pNoiseOrSpeaking = static_cast<BaseAliveGameObject*>(Event_Get_422C00(kEventSpeaking));
    }

    if (pNoiseOrSpeaking && 
        pNoiseOrSpeaking->field_CC_sprite_scale == field_CC_sprite_scale &&
        gMap_5C3030.Is_Point_In_Current_Camera_4810D0(pNoiseOrSpeaking->field_C2_lvl_number, pNoiseOrSpeaking->field_C0_path_number, pNoiseOrSpeaking->field_B8_xpos, pNoiseOrSpeaking->field_BC_ypos, 0) &&
        pNoiseOrSpeaking != this &&
        gMap_5C3030.Is_Point_In_Current_Camera_4810D0(field_C2_lvl_number, field_C0_path_number, field_B8_xpos, field_BC_ypos, 0) &&
        !Event_Get_422C00(kEventResetting))
    {
        if (pNoiseOrSpeaking != sControlledCharacter_5C1B8C)
        {
            if (Math_NextRandom() >= 192u)
            {
                return 104;
            }
        }

        if (vIsFacingMe_4254A0(sControlledCharacter_5C1B8C))
        {
            GoAlertedOrSayWhat_4BF140();
        }
        else
        {
            TurnOrSayWhat_4BEBC0();
        }
        return 104;
    }
    else
    {
        if (sControlledCharacter_5C1B8C->field_CC_sprite_scale > field_CC_sprite_scale &&
            vIsFacingMe_4254A0(sControlledCharacter_5C1B8C) &&
            !IsInInvisibleZone_425710(sControlledCharacter_5C1B8C) &&
            !sControlledCharacter_5C1B8C->field_114_flags.Get(Flags_114::e114_Bit8_bInvisible) &&
            gMap_5C3030.Is_Point_In_Current_Camera_4810D0(field_C2_lvl_number, field_C0_path_number, field_B8_xpos, field_BC_ypos, 0) &&
            !InZCover_4BB7C0(sControlledCharacter_5C1B8C) &&
            !InZCover_4BB7C0(this) &&
            !Event_Get_422C00(kEventResetting))
        {
            ToZShoot_4BF9E0();
            return 104;
        }

        if (field_106_current_motion == eSligMotions::M_StandIdle_0_4B4EC0 && field_120_timer <= static_cast<int>(sGnFrame_5C1B84))
        {
            ToTurn_4BE090();
            return 104;
        }
        else
        {
            ShouldStilBeAlive_4BBC00();
            return 104;
        }
    }
}

__int16 Slig::AI_StopChasing_16_4BCE30()
{
    if (field_120_timer > static_cast<int>(sGnFrame_5C1B84))
    {
        if (HandleEnemyStopper_4BBA00(4))
        {
            field_108_next_motion = eSligMotions::M_StandIdle_0_4B4EC0;
            SetBrain(&Slig::AI_Idle_15_4BD800);
            field_120_timer = sGnFrame_5C1B84 + 1;
        }
    }
    else
    {
        field_15C = 0;
        ToTurn_4BE090();
    }
    return 119;

}

__int16 Slig::AI_Chasing2_17_4BCBD0()
{
    if (gMap_5C3030.Is_Point_In_Current_Camera_4810D0(field_C2_lvl_number, field_C0_path_number, field_B8_xpos, field_BC_ypos, 0) &&
        vOnSameYLevel_425520(sControlledCharacter_5C1B8C) &&
        vIsFacingMe_4254A0(sControlledCharacter_5C1B8C) &&
        !IsInInvisibleZone_425710(sControlledCharacter_5C1B8C) &&
        !sControlledCharacter_5C1B8C->field_114_flags.Get(Flags_114::e114_Bit8_bInvisible) &&
        !IsWallBetween_4BB8B0(this, sControlledCharacter_5C1B8C) &&
        !RenderLayerIs_4BBBC0(sControlledCharacter_5C1B8C) &&
        !Event_Get_422C00(kEventResetting) &&
        sControlledCharacter_5C1B8C->field_4_typeId != Types::eGlukkon_67)
    {
        field_15C = 0;
        ShootTurnTowardsOrKillSound_4B3140();
        return 118;
    }

    if (HandleEnemyStopper_4BBA00(4))
    {
        field_108_next_motion = eSligMotions::M_StandIdle_0_4B4EC0;
        SetBrain(&Slig::AI_Idle_15_4BD800);
        field_120_timer = sGnFrame_5C1B84 + 1;
        return 118;
    }

    if (field_C0_path_number != gMap_5C3030.sCurrentPathId_5C3032 ||
        field_C2_lvl_number != gMap_5C3030.sCurrentLevelId_5C3030 || 
        Event_Get_422C00(kEventDeathReset) && 
        !gMap_5C3030.Is_Point_In_Current_Camera_4810D0(field_C2_lvl_number, field_C0_path_number, field_B8_xpos, field_BC_ypos, 0))
    {
        field_6_flags.Set(BaseGameObject::eDead);
    }
    else if (gMap_5C3030.Is_Point_In_Current_Camera_4810D0(field_C2_lvl_number, field_C0_path_number, field_B8_xpos, field_BC_ypos, 0))
    {
        SetBrain(&Slig::AI_StopChasing_16_4BCE30);
        field_120_timer = sGnFrame_5C1B84 + field_218_tlv_data.field_34_stop_chase_delay;
        return 118;
    }
    return 118;
}

__int16 Slig::AI_Chasing1_18_4BCEB0()
{
    if (field_120_timer > static_cast<int>(sGnFrame_5C1B84))
    {
        if (gMap_5C3030.Is_Point_In_Current_Camera_4810D0(
            field_C2_lvl_number,
            field_C0_path_number,
            field_B8_xpos,
            field_BC_ypos,
            0) && 
            !sControlledCharacter_5C1B8C->field_114_flags.Get(Flags_114::e114_Bit8_bInvisible) && 
            sControlledCharacter_5C1B8C->field_4_typeId != Types::eGlukkon_67)
        {
            field_15C = 0;
            ToShoot_4BF9A0();
        }
    }
    else
    {
        if (field_C0_path_number != gMap_5C3030.sCurrentPathId_5C3032 || field_C2_lvl_number != gMap_5C3030.sCurrentLevelId_5C3030)
        {
            field_6_flags.Set(BaseGameObject::eDead);
        }

        if (!vIsFacingMe_4254A0(sControlledCharacter_5C1B8C))
        {
            field_20_animation.field_4_flags.Toggle(AnimFlags::eBit5_FlipX);
        }

        field_15C = 1;
        field_108_next_motion = eSligMotions::M_Running_4_4B6000;
        SetBrain(&Slig::AI_Chasing2_17_4BCBD0);
        field_120_timer = field_218_tlv_data.field_14_pause_time;
    }
    return 122;
}

__int16 Slig::AI_Turning_19_4BDDD0()
{
    if (Event_Get_422C00(kEventDeathReset) && !gMap_5C3030.Is_Point_In_Current_Camera_4810D0(field_C2_lvl_number, field_C0_path_number, field_B8_xpos, field_BC_ypos, 0))
    {
        field_6_flags.Set(BaseGameObject::eDead);
        return 106;
    }

    if (ListenToGlukkonCommands_4B95D0())
    {
        ToUnderGlukkonCommand_4B9660();
        return 106;
    }
    
    if (field_106_current_motion == eSligMotions::M_TurnAroundStanding_5_4B6390 && 
        field_20_animation.field_4_flags.Get(AnimFlags::eBit18_IsLastFrame) || 
        field_106_current_motion == eSligMotions::M_StandIdle_0_4B4EC0 && 
        field_108_next_motion == -1)
    {
        WaitOrWalk_4BE870();
        return 106;
    }
    
    if (field_20_animation.field_92_current_frame != 4)
    {
        ShouldStilBeAlive_4BBC00();
        return 106;
    }
    
    if (field_20_animation.field_4_flags.Get(AnimFlags::eBit5_FlipX))
    {
        if (sControlledCharacter_5C1B8C->field_C4_velx >= FP_FromInteger(0) && 
           (sControlledCharacter_5C1B8C->field_C4_velx > FP_FromInteger(0) || sControlledCharacter_5C1B8C->field_B8_xpos >= field_B8_xpos))
        {
            ShouldStilBeAlive_4BBC00();
            return 106;
        }
    }
    else
    {
        if (sControlledCharacter_5C1B8C->field_C4_velx <= FP_FromInteger(0) && 
           (sControlledCharacter_5C1B8C->field_C4_velx > FP_FromInteger(0) || sControlledCharacter_5C1B8C->field_B8_xpos <= field_B8_xpos))
        {
            ShouldStilBeAlive_4BBC00();
            return 106;
        }
    }

    PSX_RECT bRect = {};
    vGetBoundingRect_424FD0(&bRect, 1);

    PSX_RECT charRect = {};
    sControlledCharacter_5C1B8C->vGetBoundingRect_424FD0(&charRect, 1);


    if (sControlledCharacter_5C1B8C->field_4_typeId == Types::eGlukkon_67 ||
        sControlledCharacter_5C1B8C->field_D6_scale != field_D6_scale ||
        IsInInvisibleZone_425710(sControlledCharacter_5C1B8C) ||
        sControlledCharacter_5C1B8C->field_114_flags.Get(Flags_114::e114_Bit8_bInvisible) ||
        IsWallBetween_4BB8B0(this, sControlledCharacter_5C1B8C) ||
        charRect.x > bRect.w || // TODO: Inverted rect check ??
        charRect.w < bRect.x ||
        charRect.h < bRect.y ||
        charRect.y > bRect.h ||
        sControlledCharacter_5C1B8C->field_4_typeId == Types::eSlig_125)
    {
        ShouldStilBeAlive_4BBC00();
        return 106;
    }

    field_20_animation.field_4_flags.Toggle(AnimFlags::eBit5_FlipX);
    return 106;
}

__int16 Slig::AI_StoppingNextToMudokon_20_4BF1E0()
{
    if (field_106_current_motion)
    {
        return 128;
    }

    BaseAliveGameObject* pBeatTarget = FindBeatTarget_4BD070(81, 1);
    if (!pBeatTarget || pBeatTarget->field_10C_health <= FP_FromInteger(0))
    {
        WaitOrWalk_4BE870();
        return 128;
    }

    if (Math_NextRandom() >= 100)
    {
        if (Math_NextRandom() & 1)
        {
            field_108_next_motion = eSligMotions::M_SpeakBullShit1_25_4B5450;
        }
        else
        {
            field_108_next_motion = eSligMotions::M_SpeakBullShit2_27_4B5490;
        }
    }
    else
    {
        field_108_next_motion = eSligMotions::M_Beat_51_4B6C00;
        SetBrain(&Slig::AI_BeatingUp_24_4BF2B0);
    }

    return 128;
}

__int16 Slig::AI_Walking_21_4BE0C0()
{
    if (dword_BAF7E4)
    {
        ToPanicRunning_4BCA30();
        return 108;
    }

    if (Event_Get_422C00(kEventAlarm) && field_218_tlv_data.field_2E_panic_timeout)
    {
        ToPanicYelling_4BCBA0();
        return 108;
    }

    if (field_C4_velx > FP_FromInteger(0))
    {
        if ((ScaleToGridSize_4498B0(field_CC_sprite_scale) * FP_FromInteger(2) + field_B8_xpos) >= FP_FromInteger(field_138_zone_rect.w))
        {
            PauseALittle_4BDD00();
            return 108;
        }
    }

    if (field_C4_velx < FP_FromInteger(0))
    {
        if ((field_B8_xpos - (ScaleToGridSize_4498B0(field_CC_sprite_scale) * FP_FromInteger(2))) <= FP_FromInteger(field_138_zone_rect.x))
        {
            PauseALittle_4BDD00();
            return 108;
        }
    }

    if (field_C4_velx == FP_FromInteger(0) && field_106_current_motion == eSligMotions::M_StandIdle_0_4B4EC0 && field_108_next_motion != eSligMotions::M_Walking_2_4B5BC0)
    {
        PauseALittle_4BDD00();
    }
    else if (HandleEnemyStopper_4BBA00(2))
    {
        PauseALittle_4BDD00();
    }
    else if (ListenToGlukkonCommands_4B95D0())
    {
        ToUnderGlukkonCommand_4B9660();
    }
    else if (vOnSameYLevel_425520(sControlledCharacter_5C1B8C) &&
        vIsFacingMe_4254A0(sControlledCharacter_5C1B8C) &&
        !IsInInvisibleZone_425710(sControlledCharacter_5C1B8C) &&
        !sControlledCharacter_5C1B8C->field_114_flags.Get(Flags_114::e114_Bit8_bInvisible) &&
        !IsWallBetween_4BB8B0(this, sControlledCharacter_5C1B8C) &&
        gMap_5C3030.Is_Point_In_Current_Camera_4810D0(field_C2_lvl_number, field_C0_path_number, field_B8_xpos, field_BC_ypos, 0) &&
        gMap_5C3030.Is_Point_In_Current_Camera_4810D0(field_C2_lvl_number, field_C0_path_number, field_B8_xpos, field_BC_ypos, 0) &&
        (!field_15E || sControlledCharacter_5C1B8C->field_4_typeId != Types::eSlig_125) &&
        !IsAbeEnteringDoor_4BB990(sControlledCharacter_5C1B8C) &&
        !Event_Get_422C00(kEventResetting) && 
        sControlledCharacter_5C1B8C->field_4_typeId != Types::eGlukkon_67)
    {
        ShootTurnTowardsOrKillSound_4B3140();
    }
    else
    {
        auto pShooter = static_cast<BaseAliveGameObject*>(Event_Get_422C00(kEventShooting));
        if (pShooter &&
            pShooter->field_CC_sprite_scale == field_CC_sprite_scale &&
            gMap_5C3030.Is_Point_In_Current_Camera_4810D0(pShooter->field_C2_lvl_number, pShooter->field_C0_path_number, pShooter->field_B8_xpos, pShooter->field_BC_ypos, 0) &&
            pShooter == sControlledCharacter_5C1B8C &&
            gMap_5C3030.Is_Point_In_Current_Camera_4810D0(field_C2_lvl_number, field_C0_path_number, field_B8_xpos, field_BC_ypos, 0) &&
            !Event_Get_422C00(kEventResetting))
        {
            if (vIsFacingMe_4254A0(pShooter))
            {
                ShootTurnTowardsOrKillSound_4B3140();
            }
            else
            {
                ToTurn_4BE090();
            }
        }
        else if (vOnSameYLevel_425520(sControlledCharacter_5C1B8C) &&
            vIsFacingMe_4254A0(sControlledCharacter_5C1B8C) &&
            !IsWallBetween_4BB8B0(this, sControlledCharacter_5C1B8C) &&
            Event_Get_422C00(kEventAbeOhm) &&
            gMap_5C3030.Is_Point_In_Current_Camera_4810D0(field_C2_lvl_number, field_C0_path_number, field_B8_xpos, field_BC_ypos, 0) &&
            gMap_5C3030.Is_Point_In_Current_Camera_4810D0(field_C2_lvl_number, field_C0_path_number, field_B8_xpos, field_BC_ypos, 0) &&
            !Event_Get_422C00(kEventResetting))
        {
            ToShoot_4BF9A0();
        }
        else if (Event_Get_422C00(kEventAbeOhm) && !Event_Get_422C00(kEventResetting) && field_218_tlv_data.field_2E_panic_timeout)
        {
            ToPanicYelling_4BCBA0();
        }
        else if (sActiveHero_5C1B68->field_10C_health <= FP_FromInteger(0))
        {
            ToAbeDead_4B3580();
        }
        else
        {
            auto pNoiseOrSpeaker = static_cast<BaseAliveGameObject*>(Event_Get_422C00(kEventSuspiciousNoise));
            if (!pNoiseOrSpeaker)
            {
                pNoiseOrSpeaker = static_cast<BaseAliveGameObject*>(Event_Get_422C00(kEventSpeaking));
            }

            if (pNoiseOrSpeaker && 
                pNoiseOrSpeaker->field_CC_sprite_scale == field_CC_sprite_scale &&
                gMap_5C3030.Is_Point_In_Current_Camera_4810D0(pNoiseOrSpeaker->field_C2_lvl_number, pNoiseOrSpeaker->field_C0_path_number, pNoiseOrSpeaker->field_B8_xpos, pNoiseOrSpeaker->field_BC_ypos, 0) &&
                pNoiseOrSpeaker != this &&
                gMap_5C3030.Is_Point_In_Current_Camera_4810D0(field_C2_lvl_number, field_C0_path_number, field_B8_xpos, field_BC_ypos, 0) &&
                !Event_Get_422C00(kEventResetting))
            {
                if (vIsFacingMe_4254A0(sControlledCharacter_5C1B8C))
                {
                    GoAlertedOrSayWhat_4BF140();
                }
                else
                {
                    TurnOrSayWhat_4BEBC0();
                }
            }
            else if (sControlledCharacter_5C1B8C->field_CC_sprite_scale > field_CC_sprite_scale &&
                vIsFacingMe_4254A0(sControlledCharacter_5C1B8C) &&
                !IsInInvisibleZone_425710(sControlledCharacter_5C1B8C) &&
                !sControlledCharacter_5C1B8C->field_114_flags.Get(Flags_114::e114_Bit8_bInvisible) &&
                gMap_5C3030.Is_Point_In_Current_Camera_4810D0(field_C2_lvl_number, field_C0_path_number, field_B8_xpos, field_BC_ypos, 0) &&
                !InZCover_4BB7C0(sControlledCharacter_5C1B8C) &&
                !InZCover_4BB7C0(this) &&
                !Event_Get_422C00(kEventResetting))
            {
                ToZShoot_4BF9E0();
            }
            else
            {
                if (Math_NextRandom() <  field_218_tlv_data.field_3E_percent_beat_mud && FindBeatTarget_4BD070(81, 2) && field_106_current_motion)
                {
                    field_108_next_motion = eSligMotions::M_StandIdle_0_4B4EC0;
                    SetBrain(&Slig::AI_StoppingNextToMudokon_20_4BF1E0);
                    field_120_timer =  sGnFrame_5C1B84 + 30;
                }
                else
                {
                    ShouldStilBeAlive_4BBC00();
                }
            }
        }
    }
    return 108;
}

__int16 Slig::AI_GetAlertedTurn_22_4BE990()
{
    if (field_106_current_motion == eSligMotions::M_TurnAroundStanding_5_4B6390 && field_20_animation.field_4_flags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        GoAlertedOrSayWhat_4BF140();
        return 123;
    }

    if (ListenToGlukkonCommands_4B95D0())
    {
        ToUnderGlukkonCommand_4B9660();
        return 123;
    }

    if (field_20_animation.field_92_current_frame == 4)
    {
        bool tryTurningToPlayer = true;
        if (field_20_animation.field_4_flags.Get(AnimFlags::eBit5_FlipX))
        {
            if (sControlledCharacter_5C1B8C->field_C4_velx >= FP_FromInteger(0) &&
                (sControlledCharacter_5C1B8C->field_C4_velx > FP_FromInteger(0) || sControlledCharacter_5C1B8C->field_B8_xpos >= field_B8_xpos))
            {
                tryTurningToPlayer = false;
            }
        }
        else if (sControlledCharacter_5C1B8C->field_C4_velx <= FP_FromInteger(0) &&
            (sControlledCharacter_5C1B8C->field_C4_velx > FP_FromInteger(0) || sControlledCharacter_5C1B8C->field_B8_xpos <= field_B8_xpos))
        {
            tryTurningToPlayer = false;
        }

        if (tryTurningToPlayer)
        {
            if (sControlledCharacter_5C1B8C->field_4_typeId != Types::eGlukkon_67 &&
                !IsInInvisibleZone_425710(sControlledCharacter_5C1B8C) &&
                !sControlledCharacter_5C1B8C->field_114_flags.Get(Flags_114::e114_Bit8_bInvisible))
            {
                PSX_RECT bRect = {};
                vGetBoundingRect_424FD0(&bRect, 1);

                PSX_RECT bRectChar = {};
                sControlledCharacter_5C1B8C->vGetBoundingRect_424FD0(&bRectChar, 1);

                if (PSX_Rects_overlap_no_adjustment(&bRectChar, &bRect))
                {
                    field_20_animation.field_4_flags.Toggle(AnimFlags::eBit5_FlipX);
                    return 123;
                }
            }
        }
    }

    if (field_106_current_motion != eSligMotions::M_StandIdle_0_4B4EC0)
    {
        ShouldStilBeAlive_4BBC00();
    }
    else
    {
        field_108_next_motion = eSligMotions::M_TurnAroundStanding_5_4B6390;
    }
    return 123;
}

__int16 Slig::AI_GetAlerted_23_4BEC40()
{
    if (field_120_timer != (field_218_tlv_data.field_3A_listen_time + static_cast<int>(sGnFrame_5C1B84) - 2) || 
        Math_RandomRange_496AB0(0, 100) >= field_218_tlv_data.field_3C_percent_say_what)
    {
        if (ListenToGlukkonCommands_4B95D0())
        {
            ToUnderGlukkonCommand_4B9660();
        }
    }
    else
    {
        field_108_next_motion = eSligMotions::M_SpeakWhat_29_4B54D0;
    }

    // Check if we should be killing Abe
    if (vOnSameYLevel_425520(sControlledCharacter_5C1B8C) &&
        vIsFacingMe_4254A0(sControlledCharacter_5C1B8C) &&
        !IsInInvisibleZone_425710(sControlledCharacter_5C1B8C) &&
        !sControlledCharacter_5C1B8C->field_114_flags.Get(Flags_114::e114_Bit8_bInvisible) &&
        !IsWallBetween_4BB8B0(this, sControlledCharacter_5C1B8C) &&
        gMap_5C3030.Is_Point_In_Current_Camera_4810D0(field_C2_lvl_number, field_C0_path_number, field_B8_xpos, field_BC_ypos, 0) &&
        (sControlledCharacter_5C1B8C->field_4_typeId != Types::eSlig_125 && !field_15E) &&
        !IsAbeEnteringDoor_4BB990(sControlledCharacter_5C1B8C) &&
        !Event_Get_422C00(kEventResetting) &&
        sControlledCharacter_5C1B8C->field_4_typeId != Types::eGlukkon_67)
    {
        ShootTurnTowardsOrKillSound_4B3140();
    }
    // Panic?
    else if ((Event_Get_422C00(kEventAbeOhm) || Event_Get_422C00(kEventAlarm)) && !Event_Get_422C00(kEventResetting) && field_218_tlv_data.field_2E_panic_timeout)
    {
        ToPanicYelling_4BCBA0();
    }
    else
    {
        // If some fool is trying to shoot us then shoot back
        auto pShootingSlig = static_cast<BaseAliveGameObject*>(Event_Get_422C00(kEventShooting));
        if (pShootingSlig &&
            pShootingSlig->field_CC_sprite_scale == field_CC_sprite_scale &&
            gMap_5C3030.Is_Point_In_Current_Camera_4810D0(pShootingSlig->field_C2_lvl_number, pShootingSlig->field_C0_path_number, pShootingSlig->field_B8_xpos, pShootingSlig->field_BC_ypos, 0) &&
            pShootingSlig == sControlledCharacter_5C1B8C &&
            gMap_5C3030.Is_Point_In_Current_Camera_4810D0(field_C2_lvl_number, field_C0_path_number, field_B8_xpos, field_BC_ypos, 0) &&
            !Event_Get_422C00(kEventResetting))
        {
            if (vIsFacingMe_4254A0(pShootingSlig))
            {
                ShootTurnTowardsOrKillSound_4B3140();
            }
            else
            {
                ToTurn_4BE090();
            }
        }
        else
        {
            // Is a mud being noisy?
            auto pNoisyMud = static_cast<BaseAliveGameObject*>(Event_Get_422C00(kEventSuspiciousNoise));
            if (!pNoisyMud)
            {
                pNoisyMud = static_cast<BaseAliveGameObject*>(Event_Get_422C00(kEventSpeaking));
            }

            // Then kill them
            if (pNoisyMud &&
                gMap_5C3030.Is_Point_In_Current_Camera_4810D0(pNoisyMud->field_C2_lvl_number, pNoisyMud->field_C0_path_number, pNoisyMud->field_B8_xpos, pNoisyMud->field_BC_ypos, 0) &&
                (pNoisyMud == sControlledCharacter_5C1B8C || pNoisyMud->field_4_typeId == Types::eMudokon_110) &&
                vOnSameYLevel_425520(pNoisyMud) &&
                vIsFacingMe_4254A0(pNoisyMud) &&
                (pNoisyMud != sControlledCharacter_5C1B8C || !sControlledCharacter_5C1B8C->field_114_flags.Get(Flags_114::e114_Bit8_bInvisible) &&
                    gMap_5C3030.Is_Point_In_Current_Camera_4810D0(field_C2_lvl_number, field_C0_path_number, field_B8_xpos, field_BC_ypos, 0) &&
                    !Event_Get_422C00(kEventResetting)))
            {
                ToShoot_4BF9A0();
            }
            else
            {
                // Is a slig being noisy?
                auto pNoisySlig = static_cast<BaseAliveGameObject*>(Event_Get_422C00(kEventSuspiciousNoise));
                if (!pNoisySlig)
                {
                    pNoisySlig = static_cast<BaseAliveGameObject*>(Event_Get_422C00(kEventSpeaking));
                }

                // Then say what, stop walking to respond or try to kill them.
                if (pNoisySlig &&
                    gMap_5C3030.Is_Point_In_Current_Camera_4810D0(pNoisySlig->field_C2_lvl_number, pNoisySlig->field_C0_path_number, pNoisySlig->field_B8_xpos, pNoisySlig->field_BC_ypos, 0) &&
                    (pNoisySlig == sControlledCharacter_5C1B8C || pNoisySlig->field_4_typeId != Types::eSlig_125) &&
                    !vIsFacingMe_4254A0(pNoisySlig) &&
                    gMap_5C3030.Is_Point_In_Current_Camera_4810D0(field_C2_lvl_number, field_C0_path_number, field_B8_xpos, field_BC_ypos, 0) &&
                    !Event_Get_422C00(kEventResetting))
                {
                    TurnOrSayWhat_4BEBC0();
                }
                else
                {
                    if (field_120_timer > static_cast<int>(sGnFrame_5C1B84))
                    {
                        ShouldStilBeAlive_4BBC00();
                    }
                    else
                    {
                        WaitOrWalk_4BE870();
                    }
                }
            }
        }
    }
    return 124;
}

__int16 Slig::AI_BeatingUp_24_4BF2B0()
{
    if (field_106_current_motion || field_120_timer >= static_cast<int>(sGnFrame_5C1B84))
    {
        return 129;
    }

    if (Math_NextRandom() < 100)
    {
        field_108_next_motion = eSligMotions::M_Beat_51_4B6C00;
        return 129;
    }

    if (Math_NextRandom()< 64)
    {
        field_108_next_motion = eSligMotions::M_SpeakBullShit1_25_4B5450;
        return 129;
    }

    if (Math_NextRandom() < 64)
    {
        field_108_next_motion = eSligMotions::M_SpeakBullShit2_27_4B5490;
        return 129;
    }

    WaitOrWalk_4BE870();
    return 129;
}

__int16 Slig::AI_DiscussionWhat_25_4BF380()
{
    if (ListenToGlukkonCommands_4B95D0())
    {
        ToUnderGlukkonCommand_4B9660();
    }

    if (field_106_current_motion == eSligMotions::M_StandIdle_0_4B4EC0 && field_120_timer == static_cast<int>(sGnFrame_5C1B84))
    {
        field_108_next_motion = static_cast<short>(field_294);
    }

    if (field_120_timer < static_cast<int>(sGnFrame_5C1B84 - 5))
    {
        WaitOrWalk_4BE870();
    }

    return 128;
}

__int16 Slig::AI_Empty_26_4BF620()
{
    NOT_IMPLEMENTED();
    return 0;
}

__int16 Slig::AI_Empty_27_4BF600()
{
    NOT_IMPLEMENTED();
    return 0;
}

__int16 Slig::AI_ShootingFromBackground_28_4BFA70()
{
    if (field_106_current_motion != eSligMotions::M_ShootZ_42_4B7560 ||
        !field_20_animation.field_4_flags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        ShouldStilBeAlive_4BBC00();
        return 127;
    }

    field_158++;

    if (field_158 < field_218_tlv_data.field_22_num_times_to_shoot)
    {
        return 127;
    }

    field_158 = 0;

    if (sActiveHero_5C1B68->field_10C_health <= FP_FromInteger(0))
    {
        ToAbeDead_4B3580();
    }
    else
    {
        if (sControlledCharacter_5C1B8C->field_10C_health > FP_FromInteger(0))
        {
            WaitOrWalk_4BE870();
        }
        else
        {
            ToKilledAbe_4B3600();
        }
    }
    return 127;
}

__int16 Slig::AI_Shooting_29_4BF750()
{
    if (field_106_current_motion == 6 && field_20_animation.field_4_flags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        field_158++;

        if (field_158 < field_218_tlv_data.field_22_num_times_to_shoot)
        {
            field_108_next_motion = eSligMotions::M_Shoot_6_4B55A0;
            return 111;
        }

        if (sActiveHero_5C1B68->field_10C_health <= FP_FromInteger(0))
        {
            ToKilledAbe_4B3600();
            return 111;
        }

        if (sControlledCharacter_5C1B8C->field_10C_health <= FP_FromInteger(0))
        {
            ToKilledAbe_4B3600();
            return 111;
        }
        if (!vOnSameYLevel_425520(sControlledCharacter_5C1B8C) ||
            !vIsFacingMe_4254A0(sControlledCharacter_5C1B8C) ||
            IsInInvisibleZone_425710(sControlledCharacter_5C1B8C) ||
            sControlledCharacter_5C1B8C->field_114_flags.Get(Flags_114::e114_Bit8_bInvisible) ||
            IsWallBetween_4BB8B0(this, sControlledCharacter_5C1B8C) ||
            !gMap_5C3030.Is_Point_In_Current_Camera_4810D0(field_C2_lvl_number, field_C0_path_number, field_B8_xpos, field_BC_ypos, 0) ||
            !gMap_5C3030.Is_Point_In_Current_Camera_4810D0(field_C2_lvl_number, field_C0_path_number, field_B8_xpos, field_BC_ypos, 0) || 
            Event_Get_422C00(kEventResetting))
        {
            PauseALittle_4BDD00();
            return 111;
        }

        if (!vIsFacingMe_4254A0(sControlledCharacter_5C1B8C))
        {
            ToTurn_4BE090();
            return 111;
        }

        if (!gMap_5C3030.Is_Point_In_Current_Camera_4810D0(field_C2_lvl_number, field_C0_path_number, field_B8_xpos, field_BC_ypos, 0) && 
            field_218_tlv_data.field_2A_chase_abe)
        {
            ToChase_4BCFF0();
            return 111;
        }
    }

    ShouldStilBeAlive_4BBC00();
    return 111;
}

__int16 Slig::AI_SpottedEnemyFromBackground_30_4BFA30()
{
    if (field_120_timer > static_cast<int>(sGnFrame_5C1B84))
    {
        return 126;
    }
    field_108_next_motion = eSligMotions::M_ShootZ_42_4B7560;
    SetBrain(&Slig::AI_ShootingFromBackground_28_4BFA70);
    return 126;

}

__int16 Slig::AI_WakingUp_31_4B9390()
{
    if (field_20_animation.field_4_flags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        WaitOrWalk_4BE870();
    }
    return 0;
}

__int16 Slig::AI_Inactive_32_4B9430()
{
    if (ListenToGlukkonCommands_4B95D0())
    {
        ToUnderGlukkonCommand_4B9660();
    }
    else if (field_120_timer > static_cast<int>(sGnFrame_5C1B84))
    {
        if (sActiveHero_5C1B68->field_10C_health <= FP_FromInteger(0))
        {
            ToAbeDead_4B3580();
        }
        else if (vOnSameYLevel_425520(sControlledCharacter_5C1B8C) &&
                 vIsFacingMe_4254A0(sControlledCharacter_5C1B8C) &&
                 vIsObjNearby_4253B0(ScaleToGridSize_4498B0(field_CC_sprite_scale) * FP_FromInteger(1), sControlledCharacter_5C1B8C) &&
                 !IsInInvisibleZone_425710(sControlledCharacter_5C1B8C) && 
                 !sControlledCharacter_5C1B8C->field_114_flags.Get(Flags_114::e114_Bit8_bInvisible) &&
                 !IsWallBetween_4BB8B0(this, sControlledCharacter_5C1B8C) &&
                 !Event_Get_422C00(kEventResetting) && 
                 sControlledCharacter_5C1B8C->field_4_typeId != Types::eGlukkon_67)
        {
            ToShoot_4BF9A0();
        }
        else
        {
            ShouldStilBeAlive_4BBC00();
        }
    }
    else
    {
        WaitOrWalk_4BE870();
    }
    return 103;
}

__int16 Slig::AI_Paused_33_4B8DD0()
{
    if (ListenToGlukkonCommands_4B95D0())
    {
        ToUnderGlukkonCommand_4B9660();
        return 101;
    }

    if (vOnSameYLevel_425520(sControlledCharacter_5C1B8C) &&
        vIsFacingMe_4254A0(sControlledCharacter_5C1B8C) &&
        !IsInInvisibleZone_425710(sControlledCharacter_5C1B8C) && 
        !sControlledCharacter_5C1B8C->field_114_flags.Get(Flags_114::e114_Bit8_bInvisible) &&
        !IsWallBetween_4BB8B0(this, sControlledCharacter_5C1B8C) &&
        gMap_5C3030.Is_Point_In_Current_Camera_4810D0(field_C2_lvl_number, field_C0_path_number, field_B8_xpos, field_BC_ypos, 0) &&
        (!field_15E || sControlledCharacter_5C1B8C->field_4_typeId != Types::eSlig_125) &&
        !Event_Get_422C00(kEventResetting) && 
        sControlledCharacter_5C1B8C->field_4_typeId != Types::eGlukkon_67
        )
    {
        ShootTurnTowardsOrKillSound_4B3140();
        return 101;
    }

    if (vOnSameYLevel_425520(sControlledCharacter_5C1B8C) &&
        vIsFacingMe_4254A0(sControlledCharacter_5C1B8C) &&
        !IsInInvisibleZone_425710(sControlledCharacter_5C1B8C) &&
        !sControlledCharacter_5C1B8C->field_114_flags.Get(Flags_114::e114_Bit8_bInvisible) &&
        !IsWallBetween_4BB8B0(this, sControlledCharacter_5C1B8C) &&
        gMap_5C3030.Is_Point_In_Current_Camera_4810D0(field_C2_lvl_number, field_C0_path_number, field_B8_xpos, field_BC_ypos, 0) &&
        !Event_Get_422C00(kEventResetting) &&
        sControlledCharacter_5C1B8C->field_4_typeId != Types::eGlukkon_67)
    {
        ToShoot_4BF9A0();
    }
    else if (sActiveHero_5C1B68->field_10C_health <= FP_FromInteger(0))
    {
        ToAbeDead_4B3580();
    }
    else
    {
        auto pNoiseOrSpeaking = static_cast<BaseAliveGameObject*>(Event_Get_422C00(kEventSuspiciousNoise));
        if (!pNoiseOrSpeaking)
        {
            pNoiseOrSpeaking = static_cast<BaseAliveGameObject*>(Event_Get_422C00(kEventSpeaking));
        }

        if (pNoiseOrSpeaking &&
            pNoiseOrSpeaking->field_CC_sprite_scale == field_CC_sprite_scale && 
            pNoiseOrSpeaking != this && field_120_timer <= static_cast<int>(sGnFrame_5C1B84) && 
            !Event_Get_422C00(kEventResetting))
        {
            ToTurn_4BE090();
        }
        else if (sControlledCharacter_5C1B8C->field_CC_sprite_scale > field_CC_sprite_scale && 
            vIsFacingMe_4254A0(sControlledCharacter_5C1B8C) &&
            !IsInInvisibleZone_425710(sControlledCharacter_5C1B8C) &&
            !sControlledCharacter_5C1B8C->field_114_flags.Get(Flags_114::e114_Bit8_bInvisible) &&
            gMap_5C3030.Is_Point_In_Current_Camera_4810D0(field_C2_lvl_number, field_C0_path_number, field_B8_xpos, field_BC_ypos, 0) &&
            !InZCover_4BB7C0(sControlledCharacter_5C1B8C) &&
            !InZCover_4BB7C0(this) &&
            !Event_Get_422C00(kEventResetting))
        {
            ToZShoot_4BF9E0();
        }
        else
        {
            ShouldStilBeAlive_4BBC00();
        }
    }
    return 101;
}

__int16 Slig::AI_Sleeping_34_4B9170()
{
    auto pEvent = Event_Is_Event_In_Range_422C30(kEventSuspiciousNoise, field_B8_xpos, field_BC_ypos, field_D6_scale);
    if (pEvent)
    {
        auto pNoise = Event_Is_Event_In_Range_422C30(kEventNoise, field_B8_xpos, field_BC_ypos, field_D6_scale);
        if (pNoise)
        {
            pEvent = pNoise;
        }

        const FP wakeUpDistance = ScaleToGridSize_4498B0(field_CC_sprite_scale) * FP_FromInteger(field_218_tlv_data.field_4A_noise_wake_up_distance);
        if (vIsObjNearby_4253B0(wakeUpDistance, pEvent) &&
            field_120_timer <= static_cast<int>(sGnFrame_5C1B84) &&
            gMap_5C3030.Is_Point_In_Current_Camera_4810D0(field_C2_lvl_number, field_C0_path_number, field_B8_xpos, field_BC_ypos, 0) &&
            !Event_Get_422C00(kEventResetting))
        {
            WakeUp_4B93B0();
            return 102;
        }
    }

    if (Event_Get_422C00(kEventSpeaking) || Event_Get_422C00(kEventLoudNoise))
    {
        if (pEvent != this  &&
            field_120_timer <= static_cast<int>(sGnFrame_5C1B84) &&
            gMap_5C3030.Is_Point_In_Current_Camera_4810D0(field_C2_lvl_number, field_C0_path_number, field_B8_xpos, field_BC_ypos, 0) &&
            !Event_Get_422C00(kEventResetting))
        {
            WakeUp_4B93B0();
            return 102;
        }
    }

    if (Event_Get_422C00(kEventAlarm) && !Event_Get_422C00(kEventResetting))
    {
        WakeUp_4B93B0();
        return 102;
    }

    ShouldStilBeAlive_4BBC00();

    if (field_6_flags.Get(BaseGameObject::eDead))
    {
        const CameraPos direction = gMap_5C3030.GetDirection_4811A0(field_C2_lvl_number, field_C0_path_number, field_B8_xpos, field_BC_ypos);
        Start_Slig_sounds_4CB980(direction, 0);
    }
    return 102;
}

__int16 Slig::AI_GameEnder_35_4BF640()
{
    if (Event_Get_422C00(kEventDeathReset))
    {
        field_6_flags.Set(BaseGameObject::eDead);
    }

    if (field_11C_ai_sub_state == AI_GameEnder::eState35_UNKNOWN_0)
    {
        if (sNum_CamSwappers_5C1B66 > 0 || sActiveHero_5C1B68->field_1AC_flags.Get(Abe::e1AC_Bit5_bShrivel))
        {
            return field_11C_ai_sub_state;
        }

        field_106_current_motion = eSligMotions::M_StandIdle_0_4B4EC0;
        field_120_timer = sGnFrame_5C1B84 + field_218_tlv_data.field_14_pause_time;
        return AI_GameEnder::eState35_UNKNOWN_1;
    }
    else if (field_11C_ai_sub_state == AI_GameEnder::eState35_UNKNOWN_1)
    {
        if (static_cast<int>(sGnFrame_5C1B84) < field_120_timer)
        {
            return field_11C_ai_sub_state;
        }

        field_108_next_motion = eSligMotions::M_Running_4_4B6000;
        return AI_GameEnder::eState35_UNKNOWN_2;
    }
    else
    {
        if (field_11C_ai_sub_state == AI_GameEnder::eState35_UNKNOWN_2 && gMap_5C3030.Is_Point_In_Current_Camera_4810D0(field_C2_lvl_number, field_C0_path_number, field_B8_xpos, field_BC_ypos, 0))
        {
            return field_11C_ai_sub_state;
        }
        field_6_flags.Set(BaseGameObject::eDead);
        field_10C_health = FP_FromInteger(0);
        return field_11C_ai_sub_state;
    }
}

void Slig::Init_4BB0D0()
{
    field_10_resources_array.SetAt(10, ResourceManager::GetLoadedResource_49C2A0(ResourceManager::Resource_Animation, 319, 1, 0));
    field_10_resources_array.SetAt(11, ResourceManager::GetLoadedResource_49C2A0(ResourceManager::Resource_Animation, 423, 1, 0));
    field_10_resources_array.SetAt(12, ResourceManager::GetLoadedResource_49C2A0(ResourceManager::Resource_Animation, 360, 1, 0));
    field_10_resources_array.SetAt(2, ResourceManager::GetLoadedResource_49C2A0(ResourceManager::Resource_Animation,  414, 1, 0));
    field_10_resources_array.SetAt(16, ResourceManager::GetLoadedResource_49C2A0(ResourceManager::Resource_Animation, 354, 1, 0));
    
    if (!(field_218_tlv_data.field_48_disable_resources & 0x80))
    {
        field_10_resources_array.SetAt(6, ResourceManager::GetLoadedResource_49C2A0(ResourceManager::Resource_Animation, 418, 1, 0));
    }

    if (!(field_218_tlv_data.field_48_disable_resources & 0x100))
    {
        field_10_resources_array.SetAt(3, ResourceManager::GetLoadedResource_49C2A0(ResourceManager::Resource_Animation, 415, 1, 0));
    }
    
    if (!(field_218_tlv_data.field_48_disable_resources & 1))
    {
        field_10_resources_array.SetAt(7, ResourceManager::GetLoadedResource_49C2A0(ResourceManager::Resource_Animation, 419, 1, 0));
    }
    
    if (!(field_218_tlv_data.field_48_disable_resources & 2))
    {
        field_10_resources_array.SetAt(8, ResourceManager::GetLoadedResource_49C2A0(ResourceManager::Resource_Animation, 420, 1, 0));
    }
    
    if (!(field_218_tlv_data.field_48_disable_resources & 0x200))
    {
        field_10_resources_array.SetAt(4, ResourceManager::GetLoadedResource_49C2A0(ResourceManager::Resource_Animation, 416, 1, 0));
    }
    
    if (!(field_218_tlv_data.field_48_disable_resources & 0x400))
    {
        field_10_resources_array.SetAt(9, ResourceManager::GetLoadedResource_49C2A0(ResourceManager::Resource_Animation, 426, 1, 0));
    }
    
    if (!(field_218_tlv_data.field_48_disable_resources & 4))
    {
        field_10_resources_array.SetAt(5, ResourceManager::GetLoadedResource_49C2A0(ResourceManager::Resource_Animation, 417, 1, 0));
    }
    
    if (!(field_218_tlv_data.field_48_disable_resources & 0x40))
    {
        field_10_resources_array.SetAt(1, ResourceManager::GetLoadedResource_49C2A0(ResourceManager::Resource_Animation, 413, 1, 0));
    }
    
    if (!(field_218_tlv_data.field_48_disable_resources & 8))
    {
        field_10_resources_array.SetAt(13, ResourceManager::GetLoadedResource_49C2A0(ResourceManager::Resource_Animation, 344, 1, 0));
    }
    
    if (!(field_218_tlv_data.field_48_disable_resources & 0x10))
    {
        field_10_resources_array.SetAt(15, ResourceManager::GetLoadedResource_49C2A0(ResourceManager::Resource_Animation, 28, 1, 0));
    }

    field_15E = 0;
    field_120_timer = field_218_tlv_data.field_14_pause_time + sGnFrame_5C1B84;

    switch (field_218_tlv_data.field_12_start_state)
    {
    case Path_Slig::StartState::Paused_1:
        SetBrain(&Slig::AI_Inactive_32_4B9430);
        break;

    case Path_Slig::StartState::Sleeping_2:
        if (field_218_tlv_data.field_1_unknown && field_218_tlv_data.field_46_stay_awake)
        {
            SetBrain(&Slig::AI_Inactive_32_4B9430);
        }
        else
        {
            SetBrain(&Slig::AI_Sleeping_34_4B9170);
            field_106_current_motion = eSligMotions::M_Sleeping_32_4B89A0;
            vUpdateAnim_4B1320();
        }
        break;

    case Path_Slig::StartState::Chase_3:
        SetBrain(&Slig::AI_Chasing1_18_4BCEB0);
        field_120_timer = sGnFrame_5C1B84 + field_218_tlv_data.field_36_time_to_wait_before_chase;
        break;

    case Path_Slig::StartState::RunOffScreen_4:
        SetBrain(&Slig::AI_GameEnder_35_4BF640);
        field_120_timer = sGnFrame_5C1B84 + field_218_tlv_data.field_14_pause_time;
        break;

    case Path_Slig::StartState::GameEnder_5:
        break;

    case Path_Slig::StartState::Unknown_6:
        for (int i=0; i<gBaseGameObject_list_BB47C4->Size(); i++)
        {
            BaseGameObject* pObj = gBaseGameObject_list_BB47C4->ItemAt(i);
            if (!pObj)
            {
                break;
            }

            if (pObj->field_4_typeId == Types::eGlukkon_67)
            {
                auto pGlukkon = static_cast<BaseAliveGameObject*>(pObj);
                if (gMap_5C3030.Is_Point_In_Current_Camera_4810D0(
                    pGlukkon->field_C2_lvl_number,
                    pGlukkon->field_C0_path_number,
                    pGlukkon->field_B8_xpos,
                    pGlukkon->field_BC_ypos,
                    0))
                {
                    field_208_glukkon_obj_id = pGlukkon->field_8_object_id;
                    sSligsUnderControlCount_BAF7E8++;
                    field_216.Set(Flags_216::eBit1_FollowGlukkon);
                    SetBrain(&Slig::AI_ListeningToGlukkon_4_4B9D20);
                    field_11C_ai_sub_state = AI_ListeningToGlukkon_States::IdleListening_1;
                    break;
                }
            }
        }

        if (!field_208_glukkon_obj_id)
        {
            SetBrain(&Slig::AI_Inactive_32_4B9430);
        }
        break;

    default:
        SetBrain(&Slig::AI_Paused_33_4B8DD0);
        break;
    }

    if (!field_218_tlv_data.field_2C_start_direction)
    {
        field_20_animation.field_4_flags.Set(AnimFlags::eBit5_FlipX);
    }
   
    field_290_points_count = 0;

    field_268_points[field_290_points_count].field_0_x = FP_GetExponent(field_B8_xpos);
    field_268_points[field_290_points_count].field_2_y = FP_GetExponent(field_BC_ypos);
    field_290_points_count++;

    for (short yCam = -3; yCam < 4; yCam++)
    {
        for (short xCam = -3; xCam < 4; xCam++)
        {
            Path_TLV* pTlvIter = sPath_dword_BB47C0->Get_First_TLV_For_Offsetted_Camera_4DB610(xCam, yCam);
            while (pTlvIter)
            {
                bool addPoint = false;
                if (pTlvIter->field_4_type == TlvTypes::SligBoundLeft_32)
                {
                    if (static_cast<Path_Slig_LeftBound*>(pTlvIter)->field_10_slig_id == field_218_tlv_data.field_38_slig_id)
                    {
                        field_138_zone_rect.x = pTlvIter->field_8_top_left.field_0_x;
                        addPoint = true;
                    }
                }
                else if (pTlvIter->field_4_type == TlvTypes::SligBoundRight_45)
                {
                    if (static_cast<Path_Slig_RightBound*>(pTlvIter)->field_10_slig_id == field_218_tlv_data.field_38_slig_id)
                    {
                        field_138_zone_rect.w = pTlvIter->field_8_top_left.field_0_x;
                        addPoint = true;
                    }
                }
                else if (pTlvIter->field_4_type == TlvTypes::SligPersist_46)
                {
                    if (static_cast<Path_Slig_Persist*>(pTlvIter)->field_10_slig_id == field_218_tlv_data.field_38_slig_id)
                    {
                        addPoint = true;
                    }
                }

                if (addPoint)
                {
                    if (field_290_points_count < ALIVE_COUNTOF(field_268_points))
                    {
                        field_268_points[field_290_points_count].field_0_x = pTlvIter->field_8_top_left.field_0_x;
                        field_268_points[field_290_points_count].field_2_y = pTlvIter->field_8_top_left.field_2_y;
                        field_290_points_count++;
                    }
                }

                pTlvIter = Path::Next_TLV_4DB6A0(pTlvIter);
            }
        }
    }
}

void Slig::dtor_4B1CF0()
{
    SetVTable(this, 0x547460);

    if (sControlledCharacter_5C1B8C == this)
    {
        sControlledCharacter_5C1B8C = sActiveHero_5C1B68;
        
        MusicController::sub_47FD60(0, this, 0, 0);

        if (gMap_5C3030.field_A_5C303A_levelId != LevelIds::eMenu_0)
        {
            gMap_5C3030.SetActiveCam_480D30(
                field_146_level,
                field_148_path,
                field_14A_camera,
                CameraSwapEffects::eEffect0_InstantChange,
                0,
                0);
        }
    }

    Path_TLV* pTlv = sPath_dword_BB47C0->TLV_From_Offset_Lvl_Cam_4DB770(field_118_tlvInfo);
    if (pTlv)
    {
        if (pTlv->field_4_type != SligGetPants_104 && pTlv->field_4_type != SligSpawner_37)
        {
            if (field_10C_health <= FP_FromInteger(0))
            {
                pTlv->field_0_flags.Clear(TLV_Flags::eBit1_Created);
                pTlv->field_0_flags.Set(TLV_Flags::eBit2_Unknown);
                pTlv->field_1_unknown = 0;
            }
            else
            {
                pTlv->field_0_flags.Clear(TLV_Flags::eBit1_Created);
                pTlv->field_0_flags.Clear(TLV_Flags::eBit2_Unknown);
                pTlv->field_1_unknown = 0;
            }
        }
    }

    dtor_4080B0();
}

Slig* Slig::vdtor_4B1790(signed int flags)
{
    dtor_4B1CF0();
    if (flags & 1)
    {
        Mem_Free_495540(this);
    }
    return this;
}

const FP dword_5473E8[8] =
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

// TODO: Size 8 ??
const FP dword_547408[22] =
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

void Slig::vUpdate_4B17C0()
{
    if (field_114_flags.Get(Flags_114::e114_Bit9))
    {
        if (field_104_collision_line_type != -1)
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

            if (field_100_pCollisionLine)
            {
                if (field_100_pCollisionLine->field_8_type == 32 || field_100_pCollisionLine->field_8_type == 36)
                {
                    PSX_RECT bRect = {};
                    vGetBoundingRect_424FD0(&bRect, 1);
                    vOnCollisionWith_424EE0(
                        { bRect.x, static_cast<short>(bRect.y + 5) },
                        { bRect.w, static_cast<short>(bRect.h + 5) },
                        ObjList_5C1B78,
                        1,
                        (TCollisionCallBack)&BaseAliveGameObject::OnTrapDoorIntersection_408BA0);
                }
            }
        }
        field_208_glukkon_obj_id = BaseGameObject::Find_Flags_4DC170(field_208_glukkon_obj_id);
        if (BrainIs(&Slig::AI_ListeningToGlukkon_4_4B9D20))
        {
            sSligsUnderControlCount_BAF7E8++;
        }
        field_114_flags.Clear(Flags_114::e114_Bit9);
        field_104_collision_line_type = 0;
    }

    if (!Input_IsChanting_45F260())
    {
        field_292 &= ~1u;
    }

    if (sControlledCharacter_5C1B8C == this && field_10C_health > FP_FromInteger(0))
    {
        MusicController::sub_47FD60(9, this, 0, 0);
    }

    if (sDDCheat_FlyingEnabled_5C2C08 && sControlledCharacter_5C1B8C == this)
    {
        field_100_pCollisionLine = nullptr;

        // TODO: InputCommand constants
        if (sInputObject_5BD4E0.field_0_pads[sCurrentControllerIndex_5C1BBE].field_0_pressed & 0xF)
        {
            field_C4_velx = dword_5473E8[sInputObject_5BD4E0.field_0_pads[sCurrentControllerIndex_5C1BBE].field_4_dir >> 5];
            field_C8_vely = dword_547408[sInputObject_5BD4E0.field_0_pads[sCurrentControllerIndex_5C1BBE].field_4_dir >> 5];
            
            if (sInputObject_5BD4E0.field_0_pads[sCurrentControllerIndex_5C1BBE].field_0_pressed & 0x10)
            {
                field_C4_velx += dword_5473E8[sInputObject_5BD4E0.field_0_pads[sCurrentControllerIndex_5C1BBE].field_4_dir >> 5];
                field_C4_velx += dword_5473E8[sInputObject_5BD4E0.field_0_pads[sCurrentControllerIndex_5C1BBE].field_4_dir >> 5];
                field_C8_vely += dword_547408[sInputObject_5BD4E0.field_0_pads[sCurrentControllerIndex_5C1BBE].field_4_dir >> 5];
            }

            field_B8_xpos += field_C4_velx;
            field_BC_ypos += field_C8_vely;

            // Keep in the map bounds
            PSX_Point mapBounds = {};
            gMap_5C3030.Get_map_size_480640(&mapBounds);

            if (field_B8_xpos < FP_FromInteger(0))
            {
                field_B8_xpos = FP_FromInteger(0);
            }

            if (field_B8_xpos >= FP_FromInteger(mapBounds.field_0_x))
            {
                field_B8_xpos = FP_FromInteger(mapBounds.field_0_x) - FP_FromInteger(1);
            }

            if (field_BC_ypos < FP_FromInteger(0))
            {
                field_BC_ypos = FP_FromInteger(0);
            }

            if (field_BC_ypos >= FP_FromInteger(mapBounds.field_2_y))
            {
                field_BC_ypos = FP_FromInteger(mapBounds.field_2_y) - FP_FromInteger(1);
            }
        }
        else
        {
            field_C4_velx = FP_FromInteger(0);
            field_C8_vely = FP_FromInteger(0);
        }

        sub_408C40();

        field_F8_LastLineYPos = field_BC_ypos;
    }
    else
    {
        const auto oldMotion = field_106_current_motion;
        const auto oldBrain = field_154_brain_state;
        const auto oldBrainRet = field_11C_ai_sub_state;
        field_11C_ai_sub_state = (this->*field_154_brain_state)();

        if (field_114_flags.Get(Flags_114::e114_Bit1_bShot))
        {
            vShot_4B2EA0();
        }

        if (sDDCheat_ShowAI_Info_5C1BD8)
        {
            DDCheat::DebugStr_4F5560("Slig %d %d %d %d\n", field_11C_ai_sub_state, field_120_timer, field_106_current_motion, field_108_next_motion);
        }

        const FP oldXPos = field_B8_xpos;
        const FP oldYPos = field_BC_ypos;

        (this->*sSlig_motion_table_5604A0[field_106_current_motion])();

        if (oldXPos != field_B8_xpos || oldYPos != field_BC_ypos)
        {
            field_FC_pPathTLV = sPath_dword_BB47C0->TLV_Get_At_4DB290(
                nullptr,
                field_B8_xpos,
                field_BC_ypos,
                field_B8_xpos,
                field_BC_ypos);
            VOn_TLV_Collision_4087F0(field_FC_pPathTLV);
        }

        if (oldBrain != field_154_brain_state)
        {
            LOG_INFO("Slig: Old brain = " << GetOriginalFn(oldBrain, sSligAITable).fnName << " new brain = " << GetOriginalFn(field_154_brain_state, sSligAITable).fnName);
        }
        else
        {
            if (oldBrainRet != field_11C_ai_sub_state)
            {
                LOG_INFO("Slig: Brain state = " << GetOriginalFn(field_154_brain_state, sSligAITable).fnName << " State change from " << oldBrainRet << " to " << field_11C_ai_sub_state);
            }
        }

        if (oldMotion != field_106_current_motion || field_114_flags.Get(Flags_114::e114_MotionChanged_Bit2))
        {
            field_114_flags.Clear(Flags_114::e114_MotionChanged_Bit2);
            vUpdateAnim_4B1320();
        }
        else if (field_124)
        {
            field_106_current_motion = field_F4;
            vUpdateAnim_4B1320();
            field_20_animation.SetFrame_409D50(field_F6_anim_frame);
            field_124 = 0;
        }
    }
}

void Slig::vScreenChanged_4B1E20()
{
    if (gMap_5C3030.sCurrentLevelId_5C3030 != gMap_5C3030.field_A_5C303A_levelId || 
        gMap_5C3030.field_22 != gMap_5C3030.Get_Path_Unknown_480710() ||
        gMap_5C3030.sCurrentPathId_5C3032 != gMap_5C3030.field_C_5C303C_pathId && this != sControlledCharacter_5C1B8C)
    {
        field_6_flags.Set(BaseGameObject::eDead);
    }
}

void Slig::vPossessed_4B2F10()
{
    field_114_flags.Set(Flags_114::e114_Bit4_bPossesed);
    field_292 |= 1u;
    if (field_108_next_motion != eSligMotions::M_KnockbackToStand_35_4B6A30 && field_108_next_motion != eSligMotions::M_Knockback_34_4B68A0)
    {
        field_108_next_motion = eSligMotions::M_StandIdle_0_4B4EC0;
    }
    SetBrain(&Slig::AI_Possessed_2_4BBCF0);
    field_11C_ai_sub_state = AI_Possessed::eState2_StartPossession_0;

    field_146_level = gMap_5C3030.sCurrentLevelId_5C3030;
    field_148_path = gMap_5C3030.sCurrentPathId_5C3032;
    field_14A_camera = gMap_5C3030.sCurrentCamId_5C3034;

    MusicController::sub_47FD60(9, this, 1, 0);
}

void Slig::vUnPosses_4B3050()
{
    field_108_next_motion = eSligMotions::M_StandIdle_0_4B4EC0;
    field_120_timer = sGnFrame_5C1B84 + 180;
    MusicController::sub_47FD60(0, this, 0, 0);
}

void Slig::vOnTlvCollision_4B2FB0(Path_TLV* pTlv)
{
    while (pTlv)
    {
        if (pTlv->field_4_type == TlvTypes::DeathDrop_4)
        {
            if (field_10C_health > FP_FromInteger(0))
            {
                field_10C_health = FP_FromInteger(0);
                field_11C_ai_sub_state = 0;
                SetBrain(&Slig::AI_DeathDropDeath_3_4BC1E0);
                field_C8_vely = FP_FromInteger(0);
                field_C4_velx = FP_FromInteger(0);
                VSetMotion_4081C0(eSligMotions::M_Falling_7_4B42D0);
                Event_Broadcast_422BC0(kEventMudokonComfort, this);
            }
        }
        pTlv = sPath_dword_BB47C0->TLV_Get_At_4DB290(pTlv, field_B8_xpos, field_BC_ypos, field_B8_xpos, field_BC_ypos);
    }
}

void Slig::vShot_4B2EA0()
{
    if (field_136_shot_motion != -1)
    {
        field_106_current_motion = field_136_shot_motion;
    }

    field_114_flags.Clear(Flags_114::e114_Bit1_bShot);
    field_108_next_motion = -1;
    field_136_shot_motion = -1;
    SetBrain(&Slig::AI_Death_0_4BBFB0);
    field_120_timer = sGnFrame_5C1B84 + 60;
}

void Slig::vUpdateAnim_4B1320()
{
    BYTE** ppRes = ResForMotion_4B1E90(field_106_current_motion);
    if (!ppRes)
    {
        field_106_current_motion = eSligMotions::M_StandIdle_0_4B4EC0;
        ppRes = ResForMotion_4B1E90(field_106_current_motion);
    }
    field_20_animation.Set_Animation_Data_409C80(sSligFrameTables_547318[field_106_current_motion], ppRes);
}

BOOL Slig::vUnderGlukkonCommand_4B1760()
{
    return BrainIs(&Slig::AI_ListeningToGlukkon_4_4B9D20);
}

void Slig::WakeUp_4B93B0()
{
    field_108_next_motion = eSligMotions::M_SleepingToStand_33_4B8C50;
    SetBrain(&Slig::AI_WakingUp_31_4B9390);

    MusicController::sub_47FD60(4, this, 0, 0);
    Path_TLV* pTlv = sPath_dword_BB47C0->TLV_Get_At_4DB4B0(
        field_218_tlv_data.field_8_top_left.field_0_x,
        field_218_tlv_data.field_8_top_left.field_2_y,
        field_218_tlv_data.field_8_top_left.field_0_x,
        field_218_tlv_data.field_8_top_left.field_2_y,
        TlvTypes::Slig_15);
    if (pTlv)
    {
        pTlv->field_1_unknown = 1; // TODO: Keep track of these, 1 must keep slig awake ??
    }
}

void Slig::ShouldStilBeAlive_4BBC00()
{
    if (!field_15C)
    {
        // Check not falling and not in the current screen
        if (field_106_current_motion != eSligMotions::M_Falling_7_4B42D0
            && field_106_current_motion != eSligMotions::M_OutToFall_38_4B4570
            && !gMap_5C3030.Is_Point_In_Current_Camera_4810D0(
                field_C2_lvl_number,
                field_C0_path_number,
                field_B8_xpos,
                field_BC_ypos,
                0))
        {
            if (field_290_points_count <= 0)
            {
                // No patrol points, die
                field_6_flags.Set(BaseGameObject::eDead);
            }
            else
            {
                int i = 0;
                while (!gMap_5C3030.Is_Point_In_Current_Camera_4810D0(
                    field_C2_lvl_number,
                    field_C0_path_number,
                    FP_FromInteger(field_268_points[i].field_0_x),
                    FP_FromInteger(field_268_points[i].field_2_y),
                    0))
                {
                    if (i >= field_290_points_count)
                    {
                        // No within any out our patrol points, die
                        field_6_flags.Set(BaseGameObject::eDead);
                        break;
                    }
                    i++;
                }
            }
        }
    }
}

BYTE** Slig::ResForMotion_4B1E90(__int16 motion)
{
    __int16 resIdx = 0;
    if (motion < eSligMotions::M_Sleeping_32_4B89A0)
    {
        resIdx = 0;
    }
    else if (motion < eSligMotions::M_Knockback_34_4B68A0)
    {
        resIdx = 1;
    }
    else if (motion < eSligMotions::M_OutToFall_38_4B4570)
    {
        resIdx = 2;
    }
    else if (motion < eSligMotions::M_LandingFatal_41_4B4680)
    {
        resIdx = 3;
    }
    else if (motion < eSligMotions::M_ShootZ_42_4B7560)
    {
        resIdx = 4;
    }
    else if (motion < eSligMotions::M_Smash_44_4B6B90)
    {
        resIdx = 5;
    }
    else if (motion < eSligMotions::M_PullLever_45_4B8950)
    {
        resIdx = 6;
    }
    else if (motion < eSligMotions::M_LiftGrip_46_4B3700)
    {
        resIdx = 7;
    }
    else if (motion < eSligMotions::M_Beat_51_4B6C00)
    {
        resIdx = eSligMotions::M_SlidingToStand_8_4B6520;
    }
    else
    {
        resIdx = motion >= 52 ? 0 : 9;
    }

    field_134_res_idx = resIdx;

    return field_10_resources_array.ItemAt(field_134_res_idx);
}

void Slig::ToTurn_4BE090()
{
    field_108_next_motion = eSligMotions::M_TurnAroundStanding_5_4B6390;
    SetBrain(&Slig::AI_Turning_19_4BDDD0);
}

void Slig::RespondWithWhat_4BF400()
{
    field_120_timer = sGnFrame_5C1B84 + 20;
    if (vIsFacingMe_4254A0(sControlledCharacter_5C1B8C))
    {
        field_108_next_motion = eSligMotions::M_StandIdle_0_4B4EC0;
    }
    else
    {
        field_108_next_motion = eSligMotions::M_TurnAroundStanding_5_4B6390;
    }
    SetBrain(&Slig::AI_DiscussionWhat_25_4BF380);
}

void Slig::ToShoot_4BF9A0()
{
    field_108_next_motion = eSligMotions::M_Shoot_6_4B55A0;
    SetBrain(&Slig::AI_Shooting_29_4BF750);
    field_158 = 0;
    field_15A = 0;
    MusicController::sub_47FD60(8, this, 0, 0);
}

void Slig::ToZShoot_4BF9E0()
{
    field_108_next_motion = eSligMotions::M_StandIdle_0_4B4EC0;
    field_120_timer = sGnFrame_5C1B84 + field_218_tlv_data.field_44_Z_shoot_delay;
    SetBrain(&Slig::AI_SpottedEnemyFromBackground_30_4BFA30);
    MusicController::sub_47FD60(8, this, 0, 0);
}

void Slig::PauseALittle_4BDD00()
{
    if (field_20_animation.field_4_flags.Get(AnimFlags::eBit5_FlipX))
    {
        field_120_timer = field_218_tlv_data.field_16_pause_left_min + sGnFrame_5C1B84;
        if (field_218_tlv_data.field_18_pause_left_max > field_218_tlv_data.field_16_pause_left_min)
        {
            field_120_timer += Math_NextRandom() % (field_218_tlv_data.field_18_pause_left_max - field_218_tlv_data.field_16_pause_left_min);
        }
    }
    else
    {
        field_120_timer = field_218_tlv_data.field_1A_pause_right_min + sGnFrame_5C1B84;
        if (field_218_tlv_data.field_1C_pause_right_max > field_218_tlv_data.field_1A_pause_right_min)
        {
            field_120_timer += Math_NextRandom() % (field_218_tlv_data.field_1C_pause_right_max - field_218_tlv_data.field_1A_pause_right_min);
        }
    }
    field_108_next_motion = eSligMotions::M_StandIdle_0_4B4EC0;
    SetBrain(&Slig::AI_Idle_15_4BD800);
}

void Slig::ToStand_4B4A20()
{
    field_130 = FP_FromInteger(0);
    field_C4_velx = FP_FromInteger(0);
    field_C8_vely = FP_FromInteger(0);
    field_106_current_motion = eSligMotions::M_StandIdle_0_4B4EC0;
    field_128_input = 0;
    field_12C = Math_RandomRange_496AB0(0, 60) + sGnFrame_5C1B84 + 120;
    MapFollowMe_408D10(TRUE);
}

void Slig::BlowUp_4B8020()
{
    auto pGibs = alive_new<Gibs>();
    if (pGibs)
    {
        pGibs->ctor_40FB40(
            1,
            field_B8_xpos,
            field_BC_ypos,
            field_C4_velx,
            field_C8_vely,
            field_CC_sprite_scale,
            0);
    }

    auto pBlood = alive_new<Blood>();
    if (pBlood)
    {
        pBlood->ctor_40F0B0(
            field_B8_xpos,
            field_BC_ypos - (FP_FromInteger(30) * field_CC_sprite_scale),
            FP_FromInteger(0),
            FP_FromInteger(0),
            field_CC_sprite_scale,
            20);
    }

    New_Particles_426C70(
        field_B8_xpos,
        field_BC_ypos - (FP_FromInteger(30) * field_CC_sprite_scale),
        field_CC_sprite_scale,
        3,
        128,
        128,
        128);

    if (field_CC_sprite_scale == FP_FromDouble(0.5))
    {
        SFX_Play_46FA90(64u, 80);
        SFX_Play_46FA90(47u, 60);
    }
    else
    {
        SFX_Play_46FA90(64u, 127);
        SFX_Play_46FA90(47u, 90);
    }

    field_20_animation.field_4_flags.Clear(AnimFlags::eBit3_Render);

    field_106_current_motion = eSligMotions::M_StandIdle_0_4B4EC0;
    field_C8_vely = FP_FromInteger(0);
    field_C4_velx = FP_FromInteger(0);
    field_10C_health = FP_FromInteger(0);
    MusicController::sub_47FD60(0, this, 0, 0);
    field_120_timer = sGnFrame_5C1B84 + 60;
    field_1C_update_delay = 40;
    SetBrain(&Slig::AI_Death_0_4BBFB0);
    Event_Broadcast_422BC0(kEventMudokonComfort, this);
}

__int16 Slig::MainMovement_4B4720()
{
    if (sControlledCharacter_5C1B8C == this && field_10C_health > FP_FromInteger(0))
    {
        return HandlePlayerControlled_4B7800();
    }

    if (field_108_next_motion == eSligMotions::M_TurnAroundStanding_5_4B6390)
    {
        field_106_current_motion = eSligMotions::M_TurnAroundStanding_5_4B6390;
        field_108_next_motion = -1;
        return 1;
    }

    if (field_108_next_motion != eSligMotions::M_Walking_2_4B5BC0)
    {
        if (field_108_next_motion == eSligMotions::M_Running_4_4B6000)
        {
            if (field_20_animation.field_4_flags.Get(AnimFlags::eBit5_FlipX))
            {
                field_C4_velx = -(ScaleToGridSize_4498B0(field_CC_sprite_scale) / FP_FromInteger(4));
            }
            else
            {
                field_C4_velx = (ScaleToGridSize_4498B0(field_CC_sprite_scale) / FP_FromInteger(4));
            }
            field_106_current_motion = eSligMotions::M_StandToRun_3_4B62F0;
            field_108_next_motion = -1;
            return 1;
        }

        if (field_108_next_motion == eSligMotions::M_Shoot_6_4B55A0 || field_108_next_motion == eSligMotions::M_ShootZ_42_4B7560)
        {
            field_106_current_motion = field_108_next_motion;
            field_108_next_motion = -1;
            field_12C = sGnFrame_5C1B84 + 60;
            field_130 = FP_FromInteger(0);
            field_C4_velx = FP_FromInteger(0);
            field_C8_vely = FP_FromInteger(0);
        }
        else
        {
            if (field_108_next_motion < eSligMotions::M_SpeakHereBoy_20_4B5330 || field_108_next_motion > eSligMotions::M_Blurgh_31_4B5510)
            {
                if (field_108_next_motion == eSligMotions::M_ReloadGun_12_4B5530 ||
                    field_108_next_motion == eSligMotions::M_PullLever_45_4B8950 ||
                    field_108_next_motion == eSligMotions::M_SteppingToStand_14_4B8480 ||
                    field_108_next_motion == eSligMotions::M_LiftGrip_46_4B3700 ||
                    field_108_next_motion == eSligMotions::M_Beat_51_4B6C00)
                {
                    field_106_current_motion = field_108_next_motion;
                    field_108_next_motion = -1;
                    return 1;
                }
                else
                {
                    ToStand_4B4A20();
                    return 0;
                }
            }

            field_106_current_motion = GetNextMotionIncGameSpeak_4B5080(0);
            if (field_106_current_motion == -1)
            {
                ToStand_4B4A20();
                return 0;
            }

            if (!BrainIs(&Slig::AI_ListeningToGlukkon_4_4B9D20))
            {
                Event_Broadcast_422BC0(kEventSpeaking, this);
                return 1;
            }
        }
        return 1;
    }

    if (field_20_animation.field_4_flags.Get(AnimFlags::eBit5_FlipX))
    {
        if (WallHit_408750(field_CC_sprite_scale * FP_FromInteger(45), -ScaleToGridSize_4498B0(field_CC_sprite_scale)))
        {
            return 0;
        }
        field_C4_velx = -(ScaleToGridSize_4498B0(field_CC_sprite_scale) / FP_FromInteger(9));
    }
    else
    {
        if (WallHit_408750(field_CC_sprite_scale * FP_FromInteger(45), ScaleToGridSize_4498B0(field_CC_sprite_scale)))
        {
            return 0;
        }
        field_C4_velx = (ScaleToGridSize_4498B0(field_CC_sprite_scale) / FP_FromInteger(9));
    }

    field_106_current_motion = eSligMotions::M_StandToWalk_1_4B5F70;
    field_108_next_motion = -1;

    return 1;
}

__int16 Slig::HandlePlayerControlled_4B7800()
{
    if (sInputObject_5BD4E0.isPressed(sInputKey_Right_5550D0))
    {
        if (!(field_20_animation.field_4_flags.Get(AnimFlags::eBit5_FlipX)))
        {
            // Run right
            if (sInputObject_5BD4E0.isPressed(sInputKey_Run_5550E8))
            {
                field_C4_velx = (ScaleToGridSize_4498B0(field_CC_sprite_scale) / FP_FromInteger(4));
                field_106_current_motion = eSligMotions::M_StandToRun_3_4B62F0;
                return 1;
            }

            if (!WallHit_408750(field_CC_sprite_scale * FP_FromInteger(45), ScaleToGridSize_4498B0(field_CC_sprite_scale) * FP_FromInteger(2)))
            {
                field_C4_velx = (ScaleToGridSize_4498B0(field_CC_sprite_scale) / FP_FromInteger(9));
                field_106_current_motion = eSligMotions::M_StandingToStep_15_4B83B0;
                return 1;
            }

            if (WallHit_408750(field_CC_sprite_scale * FP_FromInteger(45), ScaleToGridSize_4498B0(field_CC_sprite_scale)))
            {
                return 0;
            }

            field_C4_velx = (ScaleToGridSize_4498B0(field_CC_sprite_scale) / FP_FromInteger(6));
            field_106_current_motion = eSligMotions::M_SteppingToStand_14_4B8480;
            return 1;
        }
        else
        {
            field_106_current_motion = eSligMotions::M_TurnAroundStanding_5_4B6390;
            return 1;
        }
    }

    if (sInputObject_5BD4E0.isPressed(sInputKey_Left_5550D4))
    {
        if (field_20_animation.field_4_flags.Get(AnimFlags::eBit5_FlipX))
        {
            // Run left
            if (sInputObject_5BD4E0.isPressed(sInputKey_Run_5550E8))
            {
                field_106_current_motion = eSligMotions::M_StandToRun_3_4B62F0;
                field_C4_velx = -(ScaleToGridSize_4498B0(field_CC_sprite_scale) / FP_FromInteger(4));
                return 1;
            }

            if (!WallHit_408750(field_CC_sprite_scale * FP_FromInteger(45), -ScaleToGridSize_4498B0(field_CC_sprite_scale) * FP_FromInteger(2)))
            {
                field_C4_velx = -(ScaleToGridSize_4498B0(field_CC_sprite_scale) / FP_FromInteger(9));
                field_106_current_motion = eSligMotions::M_StandingToStep_15_4B83B0;
                return 1;
            }

            if (WallHit_408750(field_CC_sprite_scale * FP_FromInteger(45), -ScaleToGridSize_4498B0(field_CC_sprite_scale)))
            {
                return 0;
            }
            field_106_current_motion = eSligMotions::M_SteppingToStand_14_4B8480;
            field_C4_velx = -(ScaleToGridSize_4498B0(field_CC_sprite_scale) / FP_FromInteger(6));
            return 1;
        }
        else
        {
            field_106_current_motion = eSligMotions::M_TurnAroundStanding_5_4B6390;
            return 1;
        }
    }

    if (sInputObject_5BD4E0.isHeld(sInputKey_DoAction_5550E4))
    {
        FP switchXPos = {};
        FP switchYPos = {};
        if (field_20_animation.field_4_flags.Get(AnimFlags::eBit5_FlipX))
        {
            switchXPos = field_BC_ypos - FP_FromInteger(5);
            switchYPos = field_B8_xpos - ScaleToGridSize_4498B0(field_CC_sprite_scale);
        }
        else
        {
            switchXPos = field_BC_ypos - FP_FromInteger(5);
            switchYPos = ScaleToGridSize_4498B0(field_CC_sprite_scale)  + field_B8_xpos;
        }

        auto pSwitch = static_cast<Switch*>(FindObjectOfType_425180(Types::eLever_139, switchYPos, switchXPos));
        if (pSwitch && !field_114_flags.Get(Flags_114::e114_Bit10))
        {
            pSwitch->Vsub_4D6050(field_B8_xpos < pSwitch->field_B8_xpos);
            field_106_current_motion = eSligMotions::M_PullLever_45_4B8950;
            return 1;
        }

        Sfx_Slig_GameSpeak_4C04F0(SligSpeak::What_9, 0, field_11E, this);
        field_106_current_motion = eSligMotions::M_SpeakWhat_29_4B54D0;
        return 1;
    }

    if (!sInputObject_5BD4E0.isPressed(sInputKey_ThrowItem_5550F4))
    {
        if (sInputObject_5BD4E0.isPressed(sInputKey_FartRoll_5550F0))
        {
            field_106_current_motion = eSligMotions::M_Beat_51_4B6C00;
            field_12C = sGnFrame_5C1B84 + 60;
            return 1;
        }

        if (sInputObject_5BD4E0.isPressed(sInputKey_Down_5550DC))
        {
            auto pLiftPoint2 = static_cast<LiftPoint*>(sObjectIds_5C1B70.Find_449CF0(field_110_id));
            if (pLiftPoint2)
            {
                if (pLiftPoint2->field_4_typeId == Types::eLiftPoint_78)
                {
                    const FP halfGrid = (ScaleToGridSize_4498B0(field_CC_sprite_scale) / FP_FromInteger(2));
                    const FP midSwitchX = FP_FromInteger((field_100_pCollisionLine->field_0_rect.x + field_100_pCollisionLine->field_0_rect.w) / 2);
                    const FP distToSwitchMid = (field_B8_xpos - midSwitchX) >= FP_FromInteger(0) ? field_B8_xpos - midSwitchX : midSwitchX - field_B8_xpos;
                    if (distToSwitchMid < halfGrid)
                    {
                        field_106_current_motion = eSligMotions::M_LiftGrip_46_4B3700;
                        return 1;
                    }
                }
            }

            if (sInputObject_5BD4E0.isPressed(sInputKey_ThrowItem_5550F4) && 
                field_CC_sprite_scale == FP_FromDouble(0.5) && 
                !field_114_flags.Get(Flags_114::e114_Bit10))
            {
                field_106_current_motion = eSligMotions::M_ShootZ_42_4B7560;
                field_108_next_motion = -1;
                field_12C = sGnFrame_5C1B84 + 60;
                return 1;
            }
        }
        else if (sInputObject_5BD4E0.isPressed(sInputKey_Up_5550D8))
        {
            auto pLiftPoint = static_cast<LiftPoint*>(sObjectIds_5C1B70.Find_449CF0(field_110_id));
            if (pLiftPoint)
            {
                if (pLiftPoint->field_4_typeId == Types::eLiftPoint_78)
                {
                    const FP halfGrid = ScaleToGridSize_4498B0(field_CC_sprite_scale) / FP_FromInteger(2);
                    const FP midSwitchX = FP_FromInteger((field_100_pCollisionLine->field_0_rect.x + field_100_pCollisionLine->field_0_rect.w) / 2);
                    const FP distToSwitchMid = (field_B8_xpos - midSwitchX) >= FP_FromInteger(0) ? field_B8_xpos - midSwitchX : midSwitchX - field_B8_xpos;
                    if (distToSwitchMid < halfGrid)
                    {
                        field_106_current_motion = eSligMotions::M_LiftGrip_46_4B3700;
                        return 1;
                    }
                }
            }

            if (sInputObject_5BD4E0.isHeld(sInputKey_Up_5550D8))
            {
                Sfx_Slig_GameSpeak_4C04F0(SligSpeak::What_9, 0, field_11E, this);
                field_106_current_motion = eSligMotions::M_SpeakWhat_29_4B54D0;
                return 1;
            }
        }
        else if (sInputObject_5BD4E0.isHeld(sInputKey_FartRoll_5550F0 | sInputKey_Hop_5550E0))
        {
            Sfx_Slig_GameSpeak_4C04F0(SligSpeak::Blurg_11, 0, field_11E, this);
            field_106_current_motion = eSligMotions::M_Blurgh_31_4B5510;
            return 1;
        }
        ToStand_4B4A20();
        return 0;
    }

    if (!sInputObject_5BD4E0.isPressed(sInputKey_Down_5550DC)|| 
        field_CC_sprite_scale != FP_FromDouble(0.5) || 
        field_114_flags.Get(Flags_114::e114_Bit10))
    {
        field_106_current_motion = eSligMotions::M_Shoot_6_4B55A0;
    }
    else
    {
        field_106_current_motion = eSligMotions::M_ShootZ_42_4B7560;
    }

    field_108_next_motion = -1;
    field_12C = sGnFrame_5C1B84 + 60;
    return 1;
}

__int16 Slig::GetNextMotionIncGameSpeak_4B5080(int input)
{
    if (sControlledCharacter_5C1B8C == this && field_10C_health > FP_FromInteger(0))
    {
        if (Input_IsChanting_45F260())
        {
            if (field_292 & 1)
            {
                return -1;
            }
            field_12C = sGnFrame_5C1B84 + 30;
            SFX_Play_46FA90(17u, 0);
            return eSligMotions::M_Depossessing_36_4B7F30;
        }

        if (sInputKey_GameSpeak2_5550F8 & input)
        {
            field_108_next_motion = eSligMotions::M_SpeakHereBoy_20_4B5330;
        }
        else if (input & sInputKey_GameSpeak1_555104)
        {
            field_108_next_motion = eSligMotions::M_SpeakHi_21_4B53D0;
        }
        else if (input & sInputKey_GameSpeak3_555100)
        {
            if (sInputObject_5BD4E0.Is_Demo_Playing_45F220() != 0)
            {
                field_108_next_motion = eSligMotions::M_SpeakGitIm_23_4B5410;
            }
            else
            {
                field_108_next_motion = eSligMotions::M_SpeakFreeze_22_4B53F0;
            }
        }
        else if (input & sInputKey_GameSpeak4_5550FC)
        {
            if (sInputObject_5BD4E0.Is_Demo_Playing_45F220() != 0)
            {
                field_108_next_motion = eSligMotions::M_SpeakFreeze_22_4B53F0;
            }
            else
            {
                field_108_next_motion = eSligMotions::M_SpeakGitIm_23_4B5410;
            }
        }
        else if (input & sInputKey_GameSpeak8_555110)
        {
            field_108_next_motion = eSligMotions::M_SpeakLaugh_24_4B5430;
        }
        else if (input & sInputKey_GameSpeak6_555108)
        {
            field_108_next_motion = eSligMotions::M_SpeakBullShit1_25_4B5450;
        }
        else if (input & sInputKey_GameSpeak7_555114)
        {
            field_108_next_motion = eSligMotions::M_SpeakLookOut_26_4B5470;
        }
        else if (input & sInputKey_GameSpeak5_55510C)
        {
            field_108_next_motion = eSligMotions::M_SpeakBullShit2_27_4B5490;
        }
        else
        {
            return -1;
        }

        GameSpeakEvents event = GameSpeakEvents::eNone_m1;
        switch (field_108_next_motion)
        {
        case eSligMotions::M_SpeakHereBoy_20_4B5330:    event = GameSpeakEvents::Slig_HereBoy_28;   break;
        case eSligMotions::M_SpeakHi_21_4B53D0:         event = GameSpeakEvents::Slig_Hi_27;        break;
        case eSligMotions::M_SpeakFreeze_22_4B53F0:     event = GameSpeakEvents::Slig_Freeze_31;    break;
        case eSligMotions::M_SpeakGitIm_23_4B5410:      event = GameSpeakEvents::Slig_GetEm_29;     break;
        case eSligMotions::M_SpeakLaugh_24_4B5430:      event = GameSpeakEvents::Slig_Laugh_8;      break;
        case eSligMotions::M_SpeakBullShit1_25_4B5450:  event = GameSpeakEvents::Slig_BS_5;         break;
        case eSligMotions::M_SpeakLookOut_26_4B5470:    event = GameSpeakEvents::Slig_LookOut_6;    break;
        case eSligMotions::M_SpeakBullShit2_27_4B5490:  event = GameSpeakEvents::Slig_BS2_7;        break;
        }

        pEventSystem_5BC11C->PushEvent_4218D0(event);
    }

    if (field_108_next_motion >= eSligMotions::M_SpeakHereBoy_20_4B5330 && field_108_next_motion <= eSligMotions::M_Blurgh_31_4B5510)
    {
        SligSpeak speak = SligSpeak::None;
        switch (field_108_next_motion)
        {
        case eSligMotions::M_SpeakHereBoy_20_4B5330:    speak = SligSpeak::HereBoy_1;   break;
        case eSligMotions::M_SpeakHi_21_4B53D0:         speak = SligSpeak::Hi_0;        break;
        case eSligMotions::M_SpeakFreeze_22_4B53F0:     speak = SligSpeak::Freeze_8;    break;
        case eSligMotions::M_SpeakGitIm_23_4B5410:      speak = SligSpeak::GetEm_2;     break;
        case eSligMotions::M_SpeakLaugh_24_4B5430:      speak = SligSpeak::Laugh_3;     break;
        case eSligMotions::M_SpeakBullShit1_25_4B5450:  speak = SligSpeak::Bullshit_5;  break;
        case eSligMotions::M_SpeakLookOut_26_4B5470:    speak = SligSpeak::LookOut_6;   break;
        case eSligMotions::M_SpeakBullShit2_27_4B5490:  speak = SligSpeak::Bullshit2_7; break;
        case eSligMotions::M_SpeakPanic_28_4B54B0:      speak = SligSpeak::Help_10;     break;
        case eSligMotions::M_SpeakWhat_29_4B54D0:       speak = SligSpeak::What_9;      break;
        case eSligMotions::M_SpeakAIFreeze_30_4B54F0:   speak = SligSpeak::Freeze_8;    break;
        case eSligMotions::M_Blurgh_31_4B5510:          speak = SligSpeak::Blurg_11;    break;
        }
 
        Sfx_Slig_GameSpeak_4C04F0(speak, 0, field_11E, this);
        field_106_current_motion = field_108_next_motion;
        field_108_next_motion = -1;
        return field_106_current_motion;
    }

    return -1;
}

void Slig::WaitOrWalk_4BE870()
{
    field_108_next_motion = eSligMotions::M_Walking_2_4B5BC0;
    SetBrain(&Slig::AI_Walking_21_4BE0C0);

    // Right rect bound
    if (!IsFacingEffectiveLeft_4BB780(this) && (ScaleToGridSize_4498B0(field_CC_sprite_scale) * FP_FromInteger(2)) + field_B8_xpos >= FP_FromInteger(field_138_zone_rect.w))
    {
        PauseALittle_4BDD00();
        MusicController::sub_47FD60(4, this, 0, 0);
        return;
    }

    // Left rect bound
    if (IsFacingEffectiveLeft_4BB780(this) && (field_B8_xpos - (ScaleToGridSize_4498B0(field_CC_sprite_scale) * FP_FromInteger(2))) <= FP_FromInteger(field_138_zone_rect.x))
    {
        PauseALittle_4BDD00();
        MusicController::sub_47FD60(4, this, 0, 0);
        return;
    }

    AI_Walking_21_4BE0C0();
    MusicController::sub_47FD60(4, this, 0, 0);
}

void Slig::ToAbeDead_4B3580()
{
    field_108_next_motion = eSligMotions::M_SpeakLaugh_24_4B5430;
    SetBrain(&Slig::AI_EnemyDead_10_4B3460);
    field_120_timer = sGnFrame_5C1B84 + 45;
}

void Slig::ToUnderGlukkonCommand_4B9660()
{
    SetBrain(&Slig::AI_ListeningToGlukkon_4_4B9D20);
    field_11C_ai_sub_state = AI_ListeningToGlukkon_States::GettingAttention_0;
}

void Slig::ToKilledAbe_4B3600()
{
    field_108_next_motion = eSligMotions::M_StandIdle_0_4B4EC0;
    SetBrain(&Slig::AI_KilledEnemy_10_4B35C0);
    field_120_timer = sGnFrame_5C1B84 + 15;
}

BOOL Slig::IsWallBetween_4BB8B0(BaseAliveGameObject* pLeft, BaseAliveGameObject* pRight)
{
    PSX_RECT thisBRect = {};
    vGetBoundingRect_424FD0(&thisBRect, 1);

    PSX_RECT rightBRect = {};
    pRight->vGetBoundingRect_424FD0(&rightBRect, 1);

    PathLine* pLine = nullptr;
    FP hitX = {};
    FP hitY = {};
    return sCollisions_DArray_5C1128->Raycast_417A60(
        pLeft->field_B8_xpos, 
        FP_FromInteger(thisBRect.h - 25),
        pRight->field_B8_xpos, 
        FP_FromInteger(rightBRect.h -25),
        &pLine, &hitX, &hitY, pLeft->field_D6_scale != 0 ? 6 : 0x60) == 1;
}

GameSpeakEvents Slig::LastGlukkonSpeak_4B3090()
{
    if (!gMap_5C3030.Is_Point_In_Current_Camera_4810D0(field_C2_lvl_number, field_C0_path_number, field_B8_xpos, field_BC_ypos, 1))
    {
        return GameSpeakEvents::eNone_m1;
    }

    const int last_event_idx = pEventSystem_5BC11C->field_28_last_event_index;
    if (field_160 == last_event_idx)
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

    field_160 = last_event_idx;

    return pEventSystem_5BC11C->field_20_last_event;
}

__int16 Slig::ListenToGlukkonCommands_4B95D0()
{
    const GameSpeakEvents glukkonSpeak = LastGlukkonSpeak_4B3090();
    if (sControlledCharacter_5C1B8C->field_CC_sprite_scale != field_CC_sprite_scale)
    {
        return 0;
    }

    if (glukkonSpeak == GameSpeakEvents::Glukkon_Hey_36)
    {
        if (!HeardGlukkonToListenTo_4B9690(GameSpeakEvents::Glukkon_Hey_36))
        {
            return 0;
        }
    }
    else if (glukkonSpeak != GameSpeakEvents::Glukkon_AllOYa_40)
    {
        return 0;
    }

    sSligsUnderControlCount_BAF7E8++;

    field_208_glukkon_obj_id = sControlledCharacter_5C1B8C->field_8_object_id;

    if (glukkonSpeak == GameSpeakEvents::Glukkon_AllOYa_40)
    {
        field_216.Set(Flags_216::eBit3);
    }

    return 1;
}

void Slig::PlatformCollide_4B4E00()
{
    PSX_Point xy;
    xy.field_0_x = FP_GetExponent(field_B8_xpos - FP_FromInteger(5));
    xy.field_2_y = FP_GetExponent(field_BC_ypos - FP_FromInteger(5));

    PSX_Point wh;
    wh.field_0_x = FP_GetExponent(field_B8_xpos + FP_FromInteger(5));
    wh.field_2_y = FP_GetExponent(field_BC_ypos + FP_FromInteger(5));

    vOnCollisionWith_424EE0(
        xy,
        wh,
        ObjList_5C1B78,
        1,
        (TCollisionCallBack)&BaseAliveGameObject::OnTrapDoorIntersection_408BA0);
}

void Slig::FallKnockBackOrSmash_4B4A90()
{
    Abe_SFX_2_457A40(13, 0, 0x7FFF, this);

    if (field_C4_velx > FP_FromInteger(0))
    {
        field_B8_xpos -= field_C4_velx;
    }

    if (field_100_pCollisionLine)
    {
        if (field_20_animation.field_4_flags.Get(AnimFlags::eBit5_FlipX))
        {
            if (!WallHit_408750((field_CC_sprite_scale * FP_FromInteger(45)), (ScaleToGridSize_4498B0(field_CC_sprite_scale) * FP_FromInteger(2))))
            {
                field_C4_velx = (ScaleToGridSize_4498B0(field_CC_sprite_scale) / FP_FromInteger(4));
            }
            else
            {
                field_C4_velx = FP_FromInteger(0);
            }
        }
        else
        {
            if (!WallHit_408750((field_CC_sprite_scale * FP_FromInteger(45)), (-ScaleToGridSize_4498B0(field_CC_sprite_scale) * FP_FromInteger(2))))
            {
                field_C4_velx = -(ScaleToGridSize_4498B0(field_CC_sprite_scale) / FP_FromInteger(4));
            }
            else
            {
                field_C4_velx = FP_FromInteger(0);
            }
        }
    }

    if (field_108_next_motion == eSligMotions::M_Smash_44_4B6B90)
    {
        field_C4_velx = -field_C4_velx;
    }

    MapFollowMe_408D10(TRUE);

    if (field_C8_vely < FP_FromInteger(0))
    {
        field_C8_vely = FP_FromInteger(0);
    }

    field_106_current_motion = eSligMotions::M_Knockback_34_4B68A0;
    field_12C = sGnFrame_5C1B84 + 10;
}

void Slig::TurnOrSayWhat_4BEBC0()
{
    if (Event_Get_422C00(kEventSpeaking) && 
        !IsInInvisibleZone_425710(sControlledCharacter_5C1B8C) && 
        !sControlledCharacter_5C1B8C->field_114_flags.Get(Flags_114::e114_Bit8_bInvisible))
    {
        GameSpeakResponse_4BF470();
        RespondWithWhat_4BF400();
    }
    else
    {
        field_108_next_motion = eSligMotions::M_TurnAroundStanding_5_4B6390;
        SetBrain(&Slig::AI_GetAlertedTurn_22_4BE990);
    }
}

void Slig::GameSpeakResponse_4BF470()
{
    const int lastIdx = pEventSystem_5BC11C->field_28_last_event_index;

    GameSpeakEvents speak = GameSpeakEvents::eNone_m1;

    if (field_160 == lastIdx)
    {
        if (pEventSystem_5BC11C->field_20_last_event == GameSpeakEvents::eNone_m1)
        {
            speak = GameSpeakEvents::eNone_m1;
        }
        else
        {
            speak = GameSpeakEvents::eSameAsLast_m2;
        }
    }
    else
    {
        field_160 = lastIdx;
        speak = pEventSystem_5BC11C->field_20_last_event;
    }

    switch (speak)
    {
    case GameSpeakEvents::eUnknown_1:
    case GameSpeakEvents::eUnknown_2:
        if (!(Math_NextRandom() & 4))
        {
            field_294 = eSligMotions::M_SpeakBullShit1_25_4B5450;
        }
        else
        {
            field_294 = eSligMotions::M_SpeakBullShit2_27_4B5490;
        }
        break;

    case GameSpeakEvents::eFart_3:
    case GameSpeakEvents::eUnknown_4:
    case GameSpeakEvents::Slig_Laugh_8:
    case GameSpeakEvents::eUnknown_14:
    case GameSpeakEvents::eUnknown_15:
    case GameSpeakEvents::Slig_GetEm_29:
    case GameSpeakEvents::eUnknown_34:
        field_294 = eSligMotions::M_Blurgh_31_4B5510;
        return;

    case GameSpeakEvents::Slig_BS_5:
        field_294 = eSligMotions::M_SpeakBullShit1_25_4B5450;
        break;

    case GameSpeakEvents::Slig_LookOut_6:
        if (!(Math_NextRandom() & 4))
        {
            field_294 = eSligMotions::M_SpeakWhat_29_4B54D0;
        }
        else
        {
            field_294 = eSligMotions::M_SpeakPanic_28_4B54B0;
        }
        return;

    case GameSpeakEvents::Slig_BS2_7:
        field_294 = eSligMotions::M_SpeakBullShit2_27_4B5490;
        break;

    case GameSpeakEvents::eHello_9:
    case GameSpeakEvents::Slig_Hi_27:
        field_294 = eSligMotions::M_SpeakHi_21_4B53D0;
        break;

    case GameSpeakEvents::eFollowMe_10:
    case GameSpeakEvents::eWait_12:
        if (Math_NextRandom() & 8)
        {
            field_294 = eSligMotions::M_SpeakBullShit1_25_4B5450;
        }
        else
        {
            field_294 = eSligMotions::M_SpeakBullShit2_27_4B5490;
        }
        break;

    case GameSpeakEvents::eAnger_11:
    case GameSpeakEvents::eUnknown_13:
    case GameSpeakEvents::eUnknown_16:
    case GameSpeakEvents::eUnknown_17:
    case GameSpeakEvents::eUnknown_18:
    case GameSpeakEvents::eUnknown_19:
    case GameSpeakEvents::eUnknown_20:
    case GameSpeakEvents::eUnknown_25:
    case GameSpeakEvents::eUnknown_26:
    case GameSpeakEvents::eUnknown_30:
    case GameSpeakEvents::Slig_Freeze_31:
    case GameSpeakEvents::eUnknown_32:
    case GameSpeakEvents::eUnknown_35:
        field_294 = eSligMotions::M_SpeakLaugh_24_4B5430;
        break;

    default:
        field_294 = eSligMotions::M_SpeakWhat_29_4B54D0;
        break;
    }
}

void Slig::GoAlertedOrSayWhat_4BF140()
{
    if (Event_Get_422C00(kEventSpeaking)
        && !IsInInvisibleZone_425710(sControlledCharacter_5C1B8C)
        && !sControlledCharacter_5C1B8C->field_114_flags.Get(Flags_114::e114_Bit8_bInvisible))
    {
        GameSpeakResponse_4BF470();
        RespondWithWhat_4BF400();
    }
    else
    {
        field_108_next_motion = eSligMotions::M_StandIdle_0_4B4EC0;
        field_294 = eSligMotions::M_SpeakWhat_29_4B54D0;
        SetBrain(&Slig::AI_GetAlerted_23_4BEC40);
        field_120_timer = sGnFrame_5C1B84 + field_218_tlv_data.field_3A_listen_time;
    }
}

int CCSTD Slig::IsFacingEffectiveLeft_4BB780(Slig* pSlig)
{
    int flipX = pSlig->field_20_animation.field_4_flags.Get(AnimFlags::eBit5_FlipX);
    if (pSlig->field_106_current_motion == eSligMotions::M_TurnAroundStanding_5_4B6390 && pSlig->field_20_animation.field_92_current_frame > 4)
    {
        // Flip the result
        return flipX == 0;
    }
    else
    {
        return flipX;
    }
}

void Slig::MoveOnLine_4B4C40()
{
    auto pPlatform = static_cast<PlatformBase*>(sObjectIds_5C1B70.Find_449CF0(field_110_id));

    const FP xpos = field_B8_xpos;
    if (field_100_pCollisionLine)
    {
        field_100_pCollisionLine = field_100_pCollisionLine->MoveOnLine_418260(
            &field_B8_xpos,
            &field_BC_ypos,
            field_C4_velx);
        if (field_100_pCollisionLine)
        {
            if (pPlatform)
            {
                if (field_100_pCollisionLine->field_8_type != 32 && field_100_pCollisionLine->field_8_type != 36)
                {
                    const auto curMotion = field_106_current_motion;
                    VOnTrapDoorOpen();
                    field_106_current_motion = curMotion;
                }
            }
            else if (field_100_pCollisionLine->field_8_type == 32 || field_100_pCollisionLine->field_8_type == 36)
            {
                PlatformCollide_4B4E00();
            }
        }
        else
        {
            VOnTrapDoorOpen();
            field_B8_xpos = xpos + field_C4_velx;
            field_F8_LastLineYPos = field_BC_ypos;
            field_106_current_motion = eSligMotions::M_FallingInitiate_39_4B4640;
            field_130 = FP_FromDouble(0.3);

            if (field_C4_velx > (FP_FromInteger(6) * field_CC_sprite_scale))
            {
                field_C4_velx = (FP_FromInteger(6) * field_CC_sprite_scale);
            }

            if (field_C4_velx < (-FP_FromInteger(6) * field_CC_sprite_scale))
            {
                field_C4_velx = (-FP_FromInteger(6) * field_CC_sprite_scale);
            }
        }
    }
    else
    {
        VOnTrapDoorOpen();
        field_106_current_motion = eSligMotions::M_OutToFall_38_4B4570;
        field_F8_LastLineYPos = field_BC_ypos;
    }
}

void Slig::PlayerControlStopWalkingIfRequired_4B8540()
{
    // Pressing other direction to facing or not pressing a direction at all?
    if ((field_C4_velx > FP_FromInteger(0) && sInputObject_5BD4E0.isPressed(sInputKey_Left_5550D4)) ||
        (field_C4_velx < FP_FromInteger(0) && sInputObject_5BD4E0.isPressed(sInputKey_Right_5550D0)) ||
        !sInputObject_5BD4E0.isPressed(sInputKey_Left_5550D4 | sInputKey_Right_5550D0))
    {
        // Then go to standing
        field_106_current_motion = eSligMotions::M_WalkToStand_18_4B5FC0;
    }
    field_128_input = 0;
}

void Slig::CheckPlatformVanished_4B3640()
{
    BaseGameObject* pLiftPoint = sObjectIds_5C1B70.Find_449CF0(field_110_id);
    if (pLiftPoint)
    {
        if (pLiftPoint->field_6_flags.Get(BaseGameObject::eDead))
        {
            // Platform is somehow gone, fall.
            const auto savedMotion = field_106_current_motion;
            VOnTrapDoorOpen();
            field_106_current_motion = savedMotion;
        }
        sub_408C40();
    }
}

void Slig::vOnTrapDoorOpen_4B3690()
{
    auto pPlatform = static_cast<PlatformBase*>(sObjectIds_5C1B70.Find_449CF0(field_110_id));
    if (pPlatform)
    {
        pPlatform->VRemove(this);
        field_110_id = -1;
        field_F8_LastLineYPos = field_BC_ypos;
        VSetMotion_4081C0(eSligMotions::M_OutToFall_38_4B4570);
    }
}

__int16 Slig::MoveLift_4B3990(FP ySpeed)
{
    auto pLiftPoint =  static_cast<LiftPoint*>(sObjectIds_5C1B70.Find_449CF0(field_110_id));
    if (!pLiftPoint)
    {
        return eSligMotions::M_LiftGripping_48_4B3850;
    }

    pLiftPoint->vMove_4626A0(FP_FromInteger(0), ySpeed, 0);
    CheckPlatformVanished_4B3640();
    field_C8_vely = pLiftPoint->field_C8_vely;

    if (!field_20_animation.field_4_flags.Get(AnimFlags::eBit18_IsLastFrame) && field_20_animation.field_92_current_frame != 5)
    {
        return field_106_current_motion;
    }

    if (ySpeed < FP_FromInteger(0))
    {
        if (pLiftPoint->vOnTopFloor_461890())
        {
            return eSligMotions::M_LiftGripping_48_4B3850;
        }

        if (sControlledCharacter_5C1B8C != this)
        {
            return field_106_current_motion;
        }

        if (sInputObject_5BD4E0.isPressed(sInputKey_Up_5550D8))
        {
            return eSligMotions::M_LiftUp_49_4B3930;
        }

        if (sInputObject_5BD4E0.isPressed(sInputKey_Down_5550DC))
        {
            return eSligMotions::M_LiftDown_50_4B3960;
        }
    }
    else if (ySpeed >  FP_FromInteger(0))
    {
        if (pLiftPoint->vOnBottomFloor_4618F0())
        {
            return eSligMotions::M_LiftGripping_48_4B3850;
        }

        if (sControlledCharacter_5C1B8C != this)
        {
            return field_106_current_motion;
        }

        if (sInputObject_5BD4E0.isPressed(sInputKey_Down_5550DC))
        {
            return eSligMotions::M_LiftDown_50_4B3960;
        }

        if (sInputObject_5BD4E0.isPressed(sInputKey_Up_5550D8))
        {
            return eSligMotions::M_LiftUp_49_4B3930;
        }
    }

    // Strange how this isn't "if nothing pressed and on a floor then let go ??"
    if (sInputObject_5BD4E0.field_0_pads[sCurrentControllerIndex_5C1BBE].field_0_pressed && pLiftPoint->vOnAnyFloor_461920())
    {
        return eSligMotions::M_LiftUngrip_47_4B3820;
    }

    pLiftPoint->vMove_4626A0(FP_FromInteger(0), FP_FromInteger(0), 0);
    return eSligMotions::M_LiftGripping_48_4B3850;
}

void Slig::SlowDown_4B6450(FP speed)
{
    if (FP_GetExponent(field_C4_velx))
    {
        MoveOnLine_4B4C40();

        if (field_C4_velx <= FP_FromInteger(0))
        {
            if (field_C4_velx < FP_FromInteger(0))
            {
                field_C4_velx = (field_CC_sprite_scale * speed) + field_C4_velx;
                if (field_C4_velx > FP_FromInteger(0))
                {
                    field_C4_velx = FP_FromInteger(0);
                }
            }
        }
        else
        {
            field_C4_velx = field_C4_velx - (field_CC_sprite_scale * speed);
            if (field_C4_velx < FP_FromInteger(0))
            {
                field_C4_velx = FP_FromInteger(0);
            }
        }
    }
}

void Slig::ToChase_4BCFF0()
{
    field_120_timer = sGnFrame_5C1B84 + field_218_tlv_data.field_36_time_to_wait_before_chase;

    if (!vIsFacingMe_4254A0(sControlledCharacter_5C1B8C))
    {
        field_20_animation.field_4_flags.Toggle(AnimFlags::eBit5_FlipX);
    }

    field_108_next_motion = eSligMotions::M_StandIdle_0_4B4EC0;
    SetBrain(&Slig::AI_Chasing1_18_4BCEB0);
    MusicController::sub_47FD60(8, this, 0, 0);
}

__int16 Slig::HandleEnemyStopper_4BBA00(int gridBlocks)
{
    int directedGirdBlocks = gridBlocks;
    const auto bFacingLeft = IsFacingEffectiveLeft_4BB780(this);
    if (bFacingLeft)
    {
        directedGirdBlocks = -gridBlocks;
    }

    const FP width = (ScaleToGridSize_4498B0(field_CC_sprite_scale) * FP_FromInteger(directedGirdBlocks)) + field_B8_xpos;
    auto pTlv = static_cast<Path_EnemyStopper*>(sPath_dword_BB47C0->TLV_Get_At_4DB4B0(
        FP_GetExponent(field_B8_xpos),
        FP_GetExponent(field_BC_ypos),
        FP_GetExponent(width),
        FP_GetExponent(field_BC_ypos - ScaleToGridSize_4498B0(field_CC_sprite_scale)),
        TlvTypes::EnemyStopper_47));

    if (!pTlv)
    {
        return 0;
    }

    if (!SwitchStates_Get_466020(pTlv->field_12_id))
    {
        return 0;
    }


    if (pTlv->field_10_stop_direction == Path_EnemyStopper::StopDirection::Both_2)
    {
        return 1;
    }

    if (bFacingLeft && pTlv->field_10_stop_direction == Path_EnemyStopper::StopDirection::Left_0)
    {
        return 1;
    }

    if (!bFacingLeft && pTlv->field_10_stop_direction == Path_EnemyStopper::StopDirection::Right_1)
    {
        return 1;
    }

    return 0;
}

void Slig::ToPanicYelling_4BCBA0()
{
    field_108_next_motion = eSligMotions::M_SpeakPanic_28_4B54B0;
    SetBrain(&Slig::AI_PanicYelling_14_4BCA70);
}

void Slig::ToPanicTurn_4BC750()
{
    field_108_next_motion = eSligMotions::M_TurnAroundStanding_5_4B6390;
    SetBrain(&Slig::AI_PanicTurning_12_4BC490);
}

ALIVE_VAR(1, 0xBAF7EC, short, sDelayIdx_BAF7EC, 0);
const __int16 sDelayTable_56075C[6] = { 0, 6, 10, 8, 4, 12 };


__int16 CC Slig::SligStableDelay_4B99B0()
{
    // Similar to the mudokon delay stuff

    if (sSligsUnderControlCount_BAF7E8 <= 1)
    {
        return 0;
    }

    if (sDelayIdx_BAF7EC >= ALIVE_COUNTOF(sDelayTable_56075C))
    {
        sDelayIdx_BAF7EC = 0;
    }

    return sDelayTable_56075C[sDelayIdx_BAF7EC++];
}

void Slig::PlayerControlRunningSlideStopOrTurn1_4B8790()
{
    const FP curVelX = field_C4_velx;

    if (curVelX > FP_FromInteger(0) && sInputObject_5BD4E0.isPressed(sInputKey_Left_5550D4))
    {
        field_C4_velx = field_CC_sprite_scale * FP_FromDouble(13.2);
        field_106_current_motion = eSligMotions::M_SlidingTurn_9_4B6680;
        field_128_input = 0;
        return;
    }

    if (curVelX < FP_FromInteger(0) && sInputObject_5BD4E0.isPressed(sInputKey_Right_5550D0))
    {
        field_C4_velx = (field_CC_sprite_scale * -FP_FromDouble(13.2));
        field_106_current_motion = eSligMotions::M_SlidingTurn_9_4B6680;
        field_128_input = 0;
        return;
    }

    if (!sInputObject_5BD4E0.isPressed(sInputKey_Left_5550D4 | sInputKey_Right_5550D0))
    {
        if (curVelX >= FP_FromInteger(0))
        {
            field_C4_velx = field_CC_sprite_scale * FP_FromDouble(13.2);
        }
        else
        {
            field_C4_velx = (field_CC_sprite_scale * -FP_FromDouble(13.2));
        }
        field_106_current_motion = eSligMotions::M_SlidingToStand_8_4B6520;
        field_128_input = 0;
        return;
    }

    if (sInputObject_5BD4E0.isPressed(sInputKey_Run_5550E8))
    {
        field_128_input = 0;
        return;
    }

    field_F4 = 2;
    field_F6_anim_frame = 15;
    field_124 = 1;

    if (field_20_animation.field_4_flags.Get(AnimFlags::eBit5_FlipX))
    {
        field_128_input = 0;
        field_C4_velx = -(ScaleToGridSize_4498B0(field_CC_sprite_scale) / FP_FromInteger(9));
    }
    else
    {
        field_C4_velx = (ScaleToGridSize_4498B0(field_CC_sprite_scale) / FP_FromInteger(9));
        field_128_input = 0;
    }
}

void Slig::PlayerControlRunningSlideStopOrTurn1_4B85D0()
{
    const FP curVelX = field_C4_velx;
    if (curVelX > FP_FromInteger(0) && sInputObject_5BD4E0.isPressed(sInputKey_Left_5550D4))
    {
        field_C4_velx = (field_CC_sprite_scale * FP_FromDouble(13.2));
        field_106_current_motion = eSligMotions::M_SlidingTurn_9_4B6680;
        field_128_input = 0;
        return;
    }

    if (curVelX < FP_FromInteger(0) && sInputObject_5BD4E0.isPressed(sInputKey_Right_5550D0))
    {
        field_C4_velx = (field_CC_sprite_scale * -FP_FromDouble(13.2));
        field_106_current_motion = eSligMotions::M_SlidingTurn_9_4B6680;
        field_128_input = 0;
        return;
    }

    if (!sInputObject_5BD4E0.isPressed(sInputKey_Left_5550D4 | sInputKey_Right_5550D0))
    {
        if (curVelX >= FP_FromInteger(0))
        {
            field_C4_velx = field_CC_sprite_scale * FP_FromDouble(13.2);
        }
        else
        {
            field_C4_velx = (field_CC_sprite_scale * -FP_FromDouble(13.2));
        }
        field_106_current_motion = eSligMotions::M_SlidingToStand_8_4B6520;
        field_128_input = 0;
        return;
    }

    if (sInputObject_5BD4E0.isPressed(sInputKey_Run_5550E8))
    {
        field_128_input = 0;
        return;
    }

    field_F4 = 2;
    field_F6_anim_frame = 6;
    field_124 = 1;

    if (field_20_animation.field_4_flags.Get(AnimFlags::eBit5_FlipX))
    {
        field_128_input = 0;
        field_C4_velx = -(ScaleToGridSize_4498B0(field_CC_sprite_scale) / FP_FromInteger(9));
    }
    else
    {
        field_128_input = 0;
        field_C4_velx = (ScaleToGridSize_4498B0(field_CC_sprite_scale) / FP_FromInteger(9));
    }
}

// TODO: This has probably been used in other places - use this whenever a rect is made of min/max combos
inline PSX_RECT MakeRectFromFP(FP x, FP y, FP w, FP h)
{
    PSX_RECT r = {};
    r.x = FP_GetExponent(std::min(x, w));
    r.w = FP_GetExponent(std::max(w, h));
    r.y = FP_GetExponent(std::min(y, h));
    r.h = FP_GetExponent(std::max(h, y));
    return r;
}

BaseAliveGameObject* Slig::FindBeatTarget_4BD070(int /*a2*/, int gridBlocks)
{
    const FP kGridSize = ScaleToGridSize_4498B0(field_CC_sprite_scale);
    const FP k2Scaled = FP_FromInteger(2) * kGridSize;
    const FP kGridBlocksScaled = FP_FromInteger(gridBlocks) * kGridSize;

    const FP rectX = field_20_animation.field_4_flags.Get(AnimFlags::eBit5_FlipX) ? field_B8_xpos - kGridBlocksScaled : field_B8_xpos + kGridBlocksScaled;

    const PSX_RECT hitRect = MakeRectFromFP(
        rectX,
        field_BC_ypos,
        rectX,
        field_BC_ypos - k2Scaled
    );

    // TODO: Explicit Abs'ing of Y?

    for (int i = 0; i < gBaseAliveGameObjects_5C1B7C->Size(); i++)
    {
        BaseAliveGameObject* pObj = gBaseAliveGameObjects_5C1B7C->ItemAt(i);
        if (!pObj)
        {
            break;
        }

        if (pObj != this && pObj->field_4_typeId == Types::eMudokon_110)
        {
            PSX_RECT bRect = {};
            pObj->vGetBoundingRect_424FD0(&bRect, 1);

            if (pObj->field_10C_health > FP_FromInteger(0) &&
                pObj->field_D6_scale == field_D6_scale &&
                !IsInInvisibleZone_425710(pObj) &&
                !pObj->field_114_flags.Get(Flags_114::e114_Bit8_bInvisible) &&
                PSX_Rects_overlap_no_adjustment(&hitRect, &bRect))
            {
                return pObj;
            }
        }
    }
    return nullptr;
}

void Slig::TurnOrWalk_4BD6A0(int a2)
{
    if (a2 == 1)
    {
        if (field_20_animation.field_4_flags.Get(AnimFlags::eBit5_FlipX))
        {
            if (field_B8_xpos > FP_FromInteger(field_138_zone_rect.x) + (ScaleToGridSize_4498B0(field_CC_sprite_scale) * FP_FromInteger(4)))
            {
                ToTurn_4BE090();
                return;
            }
        }
        else
        {
            if (field_B8_xpos < FP_FromInteger(field_138_zone_rect.w) - (ScaleToGridSize_4498B0(field_CC_sprite_scale) * FP_FromInteger(4)))
            {
                ToTurn_4BE090();
                return;
            }
        }
    }

    if (!(field_20_animation.field_4_flags.Get(AnimFlags::eBit5_FlipX)))
    {
        if (field_B8_xpos > FP_FromInteger(field_138_zone_rect.w) - (ScaleToGridSize_4498B0(field_CC_sprite_scale) * FP_FromInteger(4)))
        {
            ToTurn_4BE090();
            return;
        }
    }
    else
    {
        if (field_B8_xpos < FP_FromInteger(field_138_zone_rect.x) + (ScaleToGridSize_4498B0(field_CC_sprite_scale) * FP_FromInteger(4)))
        {
            ToTurn_4BE090();
            return;
        }
    }

    WaitOrWalk_4BE870(); 
}

void Slig::ToPanicRunning_4BCA30()
{
    field_108_next_motion = eSligMotions::M_Running_4_4B6000;
    SetBrain(&Slig::AI_PanicRunning_13_4BC780);
    AI_PanicRunning_13_4BC780();
    MusicController::sub_47FD60(8, this, 0, 0);
}

void Slig::ShootTurnTowardsOrKillSound_4B3140()
{
    field_144 = 0;

    if (field_218_tlv_data.field_20_chal_timer || sControlledCharacter_5C1B8C->field_114_flags.Get(Flags_114::e114_Bit8_bInvisible))
    {
        if (sControlledCharacter_5C1B8C->field_4_typeId != Types::eSlig_125 || field_218_tlv_data.field_1E_chal_number != 3)
        {
            SetBrain(&Slig::AI_SpottedEnemy_7_4B3240);
            field_108_next_motion = eSligMotions::M_SpeakAIFreeze_30_4B54F0;
            field_120_timer = sGnFrame_5C1B84 + field_218_tlv_data.field_20_chal_timer;
        }
        else
        {
            field_15E = 1;
            TurnOrWalk_4BD6A0(0);
        }
    }
    else if (vIsFacingMe_4254A0(sControlledCharacter_5C1B8C))
    {
        if (field_CC_sprite_scale == sControlledCharacter_5C1B8C->field_CC_sprite_scale)
        {
            ToShoot_4BF9A0();
        }
        else
        {
            ToZShoot_4BF9E0();
        }
    }
    else
    {
        ToTurn_4BE090();
    }
}

__int16 CCSTD Slig::IsAbeEnteringDoor_4BB990(BaseAliveGameObject* pThis)
{
    if ((pThis->field_4_typeId == Types::eAbe_69) && 
        (pThis->field_106_current_motion == eAbeStates::State_114_DoorEnter_459470 && pThis->field_20_animation.field_92_current_frame > 7) ||
        (pThis->field_106_current_motion == eAbeStates::State_115_DoorExit_459A40 && pThis->field_20_animation.field_92_current_frame < 4))
    {
        return 1;
    }
    return 0;
}

int Slig::vGetSaveState_4BFB10(Slig_State* pState)
{
    if (field_114_flags.Get(Flags_114::e114_Bit7_Electrocuted))
    {
        return 0;
    }

    pState->field_0_type = Types::eSlig_125;

    pState->field_4_xpos = field_B8_xpos;
    pState->field_8_ypos = field_BC_ypos;

    pState->field_C_velx = field_C4_velx;
    pState->field_10_vely = field_C8_vely;

    pState->field_58 = field_130;

    pState->field_14_path_number = field_C0_path_number;
    pState->field_16_lvl_number = field_C2_lvl_number;
    pState->field_18_sprite_scale = field_CC_sprite_scale;

    pState->field_1C_scale = field_D6_scale;

    pState->field_1E_r = field_D0_r;
    pState->field_20_g = field_D2_g;
    pState->field_22_b = field_D4_b;

    if (field_114_flags.Get(Flags_114::e114_Bit11))
    {
        for (int i = 0; i < gBaseGameObject_list_BB47C4->Size(); i++)
        {
            BaseGameObject* pObj = gBaseGameObject_list_BB47C4->ItemAt(i);
            if (!pObj)
            {
                break;
            }

            if (pObj->field_4_typeId == Types::eElectrocute_150)
            {
                auto pElectrocute = static_cast<Electrocute*>(pObj);
                if (pElectrocute->field_20_target_obj_id == field_8_object_id)
                {
                    pState->field_1E_r = pElectrocute->field_24_r;
                    pState->field_20_g = pElectrocute->field_26_g;
                    pState->field_22_b = pElectrocute->field_28_b;
                    break;
                }
            }
        }
    }
    pState->field_24_bFlipX = field_20_animation.field_4_flags.Get(AnimFlags::eBit5_FlipX);
    pState->field_26 = field_106_current_motion;
    pState->field_28 = field_20_animation.field_92_current_frame;
    pState->field_2A = field_20_animation.field_E_frame_change_counter;
    pState->field_2D_bDrawable = field_6_flags.Get(BaseGameObject::eDrawable);
    pState->field_2C_bRender = field_20_animation.field_4_flags.Get(AnimFlags::eBit3_Render);
    pState->field_30_health = field_10C_health;
    pState->field_34_current_motion = field_106_current_motion;
    pState->field_36_next_motion = field_108_next_motion;
    pState->field_38_last_line_ypos = FP_GetExponent(field_F8_LastLineYPos);
    pState->field_3A_collision_line_type = -1;

    if (field_100_pCollisionLine)
    {
        pState->field_3A_collision_line_type = field_100_pCollisionLine->field_8_type;
    }

    pState->field_40_bActiveChar = this == sControlledCharacter_5C1B8C;
    pState->field_42 = field_11C_ai_sub_state;
    pState->field_44 = field_11E;
    pState->field_48_timer = field_120_timer;
    pState->field_4C = field_124;
    pState->field_4E = field_126;
    pState->field_50_input = InputObject::Raw_To_Command_45EF70(field_128_input);
    pState->field_54 = field_12C;
    pState->field_58 = field_130;
    pState->field_5C_tlvInfo = field_118_tlvInfo;
    pState->field_60_res_idx = field_134_res_idx;
    pState->field_62 = field_136_shot_motion;
    pState->field_64_zone_rect = field_138_zone_rect;
    pState->field_6C = field_140;
    pState->field_6E = field_142;
    pState->field_70 = field_144;
    pState->field_72_level = field_146_level;
    pState->field_74_path = field_148_path;
    pState->field_76_camera = field_14A_camera;
    pState->field_78 = field_14C;
    pState->field_7C = field_150;
    pState->field_80_brain_state_idx = 0;

    int idx = 0;
    for (const auto& fn : sSlig_ai_table_5605AC)
    {
        if (BrainIs(fn))
        {
            pState->field_80_brain_state_idx = idx;
        }
        idx++;
    }

    pState->field_88 = dword_BAF7E4;
    pState->field_8C = field_158;
    pState->field_90 = field_15C;
    pState->field_92 = field_15E;
    pState->field_94_glukkon_id = -1;

    if (field_208_glukkon_obj_id != -1)
    {
        BaseGameObject* pGlukkon = sObjectIds_5C1B70.Find_449CF0(field_208_glukkon_obj_id);
        if (pGlukkon)
        {
            pState->field_94_glukkon_id = pGlukkon->field_C_objectId;
        }
    }
    pState->field_98 = field_20C_state_after_speak;
    pState->field_9A = field_20E;

    pState->field_9C = field_210;

    pState->field_9E = field_212_next_command_arg1;
    pState->field_A0 = field_214_cmd_idx;

    pState->field_A2.Set(Slig_State::eBit2, field_216.Get(Flags_216::eBit1_FollowGlukkon));
    pState->field_A2.Set(Slig_State::eBit3, field_216.Get(Flags_216::eBit2));
    pState->field_A2.Set(Slig_State::eBit4, field_216.Get(Flags_216::eBit3));
    pState->field_A2.Set(Slig_State::eBit5, field_216.Get(Flags_216::eBit4_HeardGlukkon));

    return sizeof(Slig_State);
}

__int16 Slig::FindSwitch_4B9A50()
{
    const short yPos = FP_GetExponent(field_BC_ypos - FP_FromInteger(5));
    if (sPath_dword_BB47C0->TLV_Get_At_4DB4B0(FP_GetExponent(field_B8_xpos), yPos, FP_GetExponent(field_B8_xpos), yPos, TlvTypes::Switch_17))
    {
        return 0;
    }

    FP xOff = ScaleToGridSize_4498B0(field_CC_sprite_scale);
    if (field_20_animation.field_4_flags.Get(AnimFlags::eBit5_FlipX))
    {
        xOff = -xOff;
    }

    return sPath_dword_BB47C0->TLV_Get_At_4DB4B0(
        FP_GetExponent(FP_Abs(field_B8_xpos) + xOff),
        yPos,
        FP_GetExponent(FP_Abs(field_B8_xpos) + xOff),
        yPos,
        TlvTypes::Switch_17) != 0;
}

__int16 Slig::NearOrFacingActiveChar_4B9930(BaseAliveGameObject* pObj)
{
    if (pObj->vIsObjNearby_4253B0(ScaleToGridSize_4498B0(field_CC_sprite_scale) * FP_FromDouble(0.5), sControlledCharacter_5C1B8C) || 
        sControlledCharacter_5C1B8C->vIsFacingMe_4254A0(pObj))
    {
        return 1;
    }

    return 0;
}

static __int16 IsInZCover(Path_TLV* pTlv, PSX_RECT* pRect)
{
    if (pTlv->field_4_type == TlvTypes::ZSligCover_50)
    {
        if (pRect->x >= pTlv->field_8_top_left.field_0_x &&
            pRect->x <= pTlv->field_C_bottom_right.field_0_x &&

            pRect->y >= pTlv->field_8_top_left.field_2_y &&
            pRect->y <= pTlv->field_C_bottom_right.field_2_y &&

            pRect->w >= pTlv->field_8_top_left.field_0_x &&
            pRect->w <= pTlv->field_C_bottom_right.field_0_x &&

            pRect->h >= pTlv->field_8_top_left.field_2_y &&
            pRect->h <= pTlv->field_C_bottom_right.field_2_y)
        {
            return TRUE;
        }

    }
    return FALSE;
}

__int16 CCSTD Slig::InZCover_4BB7C0(BaseAliveGameObject* pObj)
{
    PSX_RECT rect = {};
    pObj->vGetBoundingRect_424FD0(&rect, 1);

    Path_TLV* pTlvIter = nullptr;
    for (;;)
    {
        pTlvIter = sPath_dword_BB47C0->TLV_Get_At_4DB290(pTlvIter, pObj->field_B8_xpos, FP_FromInteger(rect.y), pObj->field_B8_xpos, FP_FromInteger(rect.y));
        if (!pTlvIter)
        {
            break;
        }

        if (IsInZCover(pTlvIter, &rect))
        {
            return TRUE;
        }
    }
    return FALSE;
}

BOOL CCSTD Slig::RenderLayerIs_4BBBC0(BaseAliveGameObject* pThis)
{
    return pThis->field_20_animation.field_C_render_layer == 3 || pThis->field_20_animation.field_C_render_layer == 22;
}

void Slig::NextCommand_4B9A00(__int16 speakTableIndex, __int16 responseState)
{
    field_212_next_command_arg1 = speakTableIndex;
    field_214_cmd_idx = 0;
    field_120_timer = sGnFrame_5C1B84 + SligStableDelay_4B99B0();
    field_20C_state_after_speak = responseState;
}

__int16 Slig::HeardGlukkonToListenTo_4B9690(GameSpeakEvents glukkonSpeak)
{
    const int distToPlayer = Math_Distance_496EB0(
        FP_GetExponent(sControlledCharacter_5C1B8C->field_B8_xpos),
        FP_GetExponent(sControlledCharacter_5C1B8C->field_BC_ypos),
        FP_GetExponent(field_B8_xpos),
        FP_GetExponent(field_BC_ypos));
    
    if (!NearOrFacingActiveChar_4B9930(this))
    {
        return 0;
    }

    for (int i = 0; i < gBaseAliveGameObjects_5C1B7C->Size(); i++)
    {
        BaseAliveGameObject*pObj = gBaseAliveGameObjects_5C1B7C->ItemAt(i);
        if (!pObj)
        {
            break;
        }

        if (pObj != this && pObj->field_4_typeId == Types::eSlig_125)
        {
            auto* pOtherSlig = static_cast<Slig*>(pObj);
            if (pOtherSlig->field_CC_sprite_scale == sControlledCharacter_5C1B8C->field_CC_sprite_scale && 
                gMap_5C3030.Is_Point_In_Current_Camera_4810D0(
                    pOtherSlig->field_C2_lvl_number,
                    pOtherSlig->field_C0_path_number,
                    pOtherSlig->field_B8_xpos,
                    pOtherSlig->field_BC_ypos, 0) &&
                NearOrFacingActiveChar_4B9930(pOtherSlig) &&
                (glukkonSpeak == GameSpeakEvents::Glukkon_Hey_36 || pOtherSlig->BrainIs(&Slig::AI_ListeningToGlukkon_4_4B9D20)))
            {
                if (vIsObjNearby_4253B0(ScaleToGridSize_4498B0(field_CC_sprite_scale) * FP_FromDouble(0.5), pOtherSlig))
                {
                    if ((pOtherSlig->vIsFacingMe_4254A0(sControlledCharacter_5C1B8C) && !vIsFacingMe_4254A0(sControlledCharacter_5C1B8C)) || pOtherSlig->field_216.Get(Flags_216::eBit4_HeardGlukkon))
                    {
                        return 0;
                    }
                }
                else if (distToPlayer > Math_Distance_496EB0(
                    FP_GetExponent(sControlledCharacter_5C1B8C->field_B8_xpos),
                    FP_GetExponent(sControlledCharacter_5C1B8C->field_BC_ypos),
                    FP_GetExponent(pOtherSlig->field_B8_xpos),
                    FP_GetExponent(pOtherSlig->field_BC_ypos)))
                {
                    return 0;
                }
            }
        }
    }

    field_216.Set(Flags_216::eBit4_HeardGlukkon);
    return 1;
}

__int16 Slig::vTakeDamage_4B2470(BaseGameObject* pFrom)
{
    if (field_114_flags.Get(Flags_114::e114_Bit10))
    {
        return 0;
    }

    switch (pFrom->field_4_typeId)
    {
    case Types::eBullet_15:
    {
        if (field_10C_health <= FP_FromInteger(0) && sControlledCharacter_5C1B8C != this)
        {
            return 0;
        }

        auto pBullet = static_cast<Bullet*>(pFrom);
        switch (pBullet->field_20_type)
        {
        case BulletType::Type_0:
        case BulletType::Type_2:
        {
            auto pBlood1 = alive_new<Blood>();
            if (pBlood1)
            {
                const FP yOff = FP_FromInteger(Math_NextRandom() % 16) - FP_FromInteger(8);
                const FP xOff = ((pBullet->field_30 <= FP_FromInteger(0) ? FP_FromInteger(-1) : FP_FromInteger(1)) * FP_FromInteger(Math_NextRandom() & 15)) + FP_FromInteger(16);
                const FP yPos = field_BC_ypos - (FP_FromInteger(25) * field_CC_sprite_scale);
                const FP xPos = field_CC_sprite_scale * (pBullet->field_30 <= FP_FromInteger(0) ? FP_FromInteger(-6) : FP_FromInteger(6));
                pBlood1->ctor_40F0B0(xPos + field_B8_xpos, yPos, xOff, yOff, field_CC_sprite_scale, 12);
            }

            auto pBlood2 = alive_new<Blood>();
            if (pBlood2)
            {
                const FP xOff = pBullet->field_30 <= FP_FromInteger(0) ? FP_FromInteger(-6) : FP_FromInteger(6);
                const FP yPos = field_BC_ypos - (FP_FromInteger(25) * field_CC_sprite_scale);
                const FP xPos = field_CC_sprite_scale * (pBullet->field_30 <= FP_FromInteger(0) ? FP_FromInteger(-12) : FP_FromInteger(12));
                pBlood2->ctor_40F0B0(xPos + field_B8_xpos, yPos, xOff, FP_FromInteger(0), field_CC_sprite_scale, 8);
            }
            break;
        }

        case BulletType::Type_1:
        case BulletType::ZBullet_3:
        {
            PSX_RECT myRect = {};
            vGetBoundingRect_424FD0(&myRect, 1);
            const FP rectY = FP_FromInteger(myRect.y);

            Path_TLV* pTlvIter = nullptr;
            for (;;)
            {
                pTlvIter = sPath_dword_BB47C0->TLV_Get_At_4DB290(pTlvIter, field_B8_xpos, rectY, field_B8_xpos, rectY);
                if (!pTlvIter)
                {
                    break;
                }

                if (IsInZCover(pTlvIter, &myRect))
                {
                    field_114_flags.Clear(Flags_114::e114_Bit1_bShot);
                    field_10C_health = FP_FromInteger(1);
                    return 0;
                }
            }

            if (!gMap_5C3030.Is_Point_In_Current_Camera_4810D0(field_C2_lvl_number, field_C0_path_number, field_B8_xpos, rectY, 0))
            {
                field_114_flags.Clear(Flags_114::e114_Bit1_bShot);
                field_10C_health = FP_FromInteger(1);
                return 0;
            }

            auto pBlood = alive_new<Blood>();
            if (pBlood)
            {
                pBlood->ctor_40F0B0(field_B8_xpos, field_BC_ypos - (FP_FromInteger(25) * field_CC_sprite_scale), FP_FromInteger(0), FP_FromInteger(0), field_CC_sprite_scale, 25);
            }
        }

        default:
            break;
        }

        field_114_flags.Set(Flags_114::e114_Bit1_bShot);
        SetBrain(&Slig::AI_Death_0_4BBFB0);

        field_14C = sGnFrame_5C1B84 + 5;
        if (field_106_current_motion != eSligMotions::M_Possess_37_4B72C0)
        {
            if (field_150 > static_cast<int>(sGnFrame_5C1B84) + 20)
            {
                field_150 = sGnFrame_5C1B84 + 20;
            }

            if (field_106_current_motion != eSligMotions::M_Possess_37_4B72C0 &&
                field_106_current_motion != eSligMotions::M_Smash_44_4B6B90 &&
                field_106_current_motion != eSligMotions::M_Knockback_34_4B68A0)
            {
                field_108_next_motion = eSligMotions::M_Possess_37_4B72C0;
                field_136_shot_motion = eSligMotions::M_Possess_37_4B72C0;
                field_150 = sGnFrame_5C1B84 + 20;
                vShot_4B2EA0();
                field_114_flags.Set(Flags_114::e114_MotionChanged_Bit2);
                if (static_cast<Bullet*>(pFrom)->field_30 < FP_FromInteger(0))
                {
                    field_C4_velx = FP_FromDouble(-0.001);
                    field_10C_health = FP_FromInteger(0);
                    Event_Broadcast_422BC0(kEventMudokonComfort, this);
                    return 1;
                }
                field_C4_velx = FP_FromDouble(0.001);
            }
        }

        field_10C_health = FP_FromInteger(0);
        Event_Broadcast_422BC0(kEventMudokonComfort, this);
        return 1;
    }

    case Types::eGrinder_30:
    case Types::eBaseBomb_46:
    case Types::eExplosion_109:
    {
        if (!field_20_animation.field_4_flags.Get(AnimFlags::eBit3_Render))
        {
            return 1;
        }

        auto pGibs = alive_new<Gibs>();
        if (pGibs)
        {
            pGibs->ctor_40FB40(1, field_B8_xpos, field_BC_ypos, field_C4_velx, field_C8_vely, field_CC_sprite_scale, 0);
        }
        field_10C_health = FP_FromInteger(0);
        SFX_Play_46FA90(0x2Fu, 90);
        field_20_animation.field_4_flags.Clear(AnimFlags::eBit2_Animate);
        field_20_animation.field_4_flags.Clear(AnimFlags::eBit3_Render);
        field_1C_update_delay = 40;
        SetBrain(&Slig::AI_ReturnControlToAbeAndDie_1_4BC410);
        field_106_current_motion = eSligMotions::M_StandIdle_0_4B4EC0;
        vUpdateAnim_4B1320();
        Event_Broadcast_422BC0(kEventMudokonComfort, this);
        return 1;
    }

    case Types::eElectricWall_39:
        Sfx_Slig_GameSpeak_4C04F0(SligSpeak::Help_10, 0, field_11E, this);
        return 1;

    case Types::eAbe_69:
    {
        if (field_10C_health <= FP_FromInteger(0))
        {
            return 1;
        }

        if (field_106_current_motion == eSligMotions::M_Knockback_34_4B68A0 ||
            field_106_current_motion == eSligMotions::M_Smash_44_4B6B90 ||
            field_106_current_motion == eSligMotions::M_KnockbackToStand_35_4B6A30)
        {
            return 1;
        }

        if (!vIsFacingMe_4254A0(sActiveHero_5C1B68) ||
            IsInInvisibleZone_425710(sActiveHero_5C1B68) ||
            sActiveHero_5C1B68->field_114_flags.Get(Flags_114::e114_Bit8_bInvisible) ||
            IsAbeEnteringDoor_4BB990(sControlledCharacter_5C1B8C))
        {
            GoAlertedOrSayWhat_4BF140();
        }
        else
        {
            ShootTurnTowardsOrKillSound_4B3140();
        }

        field_114_flags.Set(Flags_114::e114_MotionChanged_Bit2);

        if (field_20_animation.field_4_flags.Get(AnimFlags::eBit5_FlipX))
        {
            field_B8_xpos = ScaleToGridSize_4498B0(field_CC_sprite_scale) + field_B8_xpos;
        }
        else
        {
            field_B8_xpos = field_B8_xpos - ScaleToGridSize_4498B0(field_CC_sprite_scale);
        }
        FallKnockBackOrSmash_4B4A90();
        field_C4_velx = FP_FromInteger(0);
        return 1;
    }

    case Types::eType_104:
        return 1;

    case Types::eSlog_126:
    {
        if (field_10C_health <= FP_FromInteger(0) &&
            (field_106_current_motion == eSligMotions::M_Knockback_34_4B68A0 || field_106_current_motion == eSligMotions::M_Smash_44_4B6B90))
        {
            return 1;
        }

        field_114_flags.Set(Flags_114::e114_Bit1_bShot);
        field_10C_health = FP_FromInteger(0);

        SetBrain(&Slig::AI_Death_0_4BBFB0);

        Abe_SFX_2_457A40(13, 0, 0x7FFF, this);

        Event_Broadcast_422BC0(kEventMudokonComfort, this);

        if (vIsFacingMe_4254A0(static_cast<BaseAliveGameObject*>(pFrom)))
        {
            if (field_20_animation.field_4_flags.Get(AnimFlags::eBit5_FlipX))
            {
                field_C4_velx = (ScaleToGridSize_4498B0(field_CC_sprite_scale) / FP_FromInteger(4));
            }
            else
            {
                field_C4_velx = -(ScaleToGridSize_4498B0(field_CC_sprite_scale) / FP_FromInteger(4));
            }

            field_114_flags.Set(Flags_114::e114_MotionChanged_Bit2);
            field_12C = sGnFrame_5C1B84 + 10;
            field_106_current_motion = eSligMotions::M_Knockback_34_4B68A0;
            field_108_next_motion = eSligMotions::M_Knockback_34_4B68A0;
            field_136_shot_motion = eSligMotions::M_Knockback_34_4B68A0;
        }
        else
        {
            field_108_next_motion = eSligMotions::M_Smash_44_4B6B90;
            field_136_shot_motion = eSligMotions::M_Smash_44_4B6B90;
        }
        return 1;
    }

    case Types::eElectrocute_150:
        if (field_10C_health <= FP_FromInteger(0))
        {
            return 1;
        }
        field_6_flags.Set(BaseGameObject::eDead);
        field_10C_health = FP_FromInteger(0);
        Event_Broadcast_422BC0(kEventMudokonComfort, this);
        return 1;

    case Types::eType_8:
        break;

    default:
        if (field_10C_health <= FP_FromInteger(0))
        {
            return 1;
        }
        SFX_Play_46FA90(0x40u, 127);
        SFX_Play_46FA90(0x2Fu, 90);
        break;
    }

    if (field_10C_health <= FP_FromInteger(0))
    {
        return 1;
    }

    field_114_flags.Set(Flags_114::e114_Bit1_bShot);
    field_10C_health = FP_FromInteger(0);
    field_108_next_motion = eSligMotions::M_Smash_44_4B6B90;
    field_136_shot_motion = eSligMotions::M_Smash_44_4B6B90;
    Event_Broadcast_422BC0(kEventMudokonComfort, this);
    return 1;
}

__int16 Slig::vIsFacingMe_4B23D0(BaseAnimatedWithPhysicsGameObject* pWho)
{
    if (field_106_current_motion != eSligMotions::M_TurnAroundStanding_5_4B6390 || 
        field_20_animation.field_92_current_frame < 6)
    {
        if (pWho->field_B8_xpos <= field_B8_xpos && 
            field_20_animation.field_4_flags.Get(AnimFlags::eBit5_FlipX))
        {
            return 1;
        }

        if (pWho->field_B8_xpos >= field_B8_xpos &&
            !field_20_animation.field_4_flags.Get(AnimFlags::eBit5_FlipX))
        {
            return 1;
        }
    }
    else
    {
        if (pWho->field_B8_xpos <= field_B8_xpos &&
            !field_20_animation.field_4_flags.Get(AnimFlags::eBit5_FlipX))
        {
            return 1;
        }

        if (pWho->field_B8_xpos >= field_B8_xpos &&
            field_20_animation.field_4_flags.Get(AnimFlags::eBit5_FlipX))
        {
            return 1;
        }
    }
    return 0;
}

__int16 Slig::vOnSameYLevel_4BB6C0(BaseAnimatedWithPhysicsGameObject* pOther)
{
    PSX_RECT bOurRect = {};
    vGetBoundingRect_424FD0(&bOurRect, 1);

    PSX_RECT bTheirRect = {};
    pOther->vGetBoundingRect_424FD0(&bTheirRect, 1);

    return ((bTheirRect.h + bTheirRect.y) / 2) <= bOurRect.h && bTheirRect.h >= bOurRect.y && field_D6_scale == pOther->field_D6_scale;
}

__int16 Slig::FindLiftPoint_4B9B40()
{
    const FP k2Scaled = ScaleToGridSize_4498B0(field_CC_sprite_scale) * FP_FromInteger(2);

    PlatformBase* pLift = nullptr;
    if (field_20_animation.field_4_flags.Get(AnimFlags::eBit5_FlipX))
    {
        pLift = static_cast<PlatformBase*>(FindObjectOfType_425180(Types::eLiftPoint_78, field_B8_xpos - k2Scaled, field_BC_ypos + FP_FromInteger(5)));
    }
    else
    {
        pLift = static_cast<PlatformBase*>(FindObjectOfType_425180(Types::eLiftPoint_78, k2Scaled + field_B8_xpos, field_BC_ypos + FP_FromInteger(5)));
    }

    if (pLift)
    {
        PSX_RECT rect = {};
        pLift->vGetBoundingRect_424FD0(&rect, 1);

        const FP liftMidXPos = FP_FromInteger((rect.x + rect.w) / 2);
        return FP_Abs(field_B8_xpos - liftMidXPos) < k2Scaled;
    }

    return FALSE;
}
