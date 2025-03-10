#include "stdafx.h"
#include "SecurityDoor.hpp"
#include "Function.hpp"
#include "Game.hpp"
#include "Abe.hpp"
#include "stdlib.hpp"
#include "Sfx.hpp"
#include "Events.hpp"
#include "GameSpeak.hpp"
#include "Midi.hpp"
#include "SwitchStates.hpp"

SecurityDoor* SecurityDoor::ctor_4ABFC0(Path_SecurityDoor* pTlv, int tlvInfo)
{
    BaseAnimatedWithPhysicsGameObject_ctor_424930(0);
    field_104_event_idx = -1;
    field_118_max_idx = 0;
    field_11A_event_idx = -1;

    SetVTable(this, 0x547028);

    BYTE** ppRes = Add_Resource_4DC130(ResourceManager::Resource_Animation, 6027);
    Animation_Init_424E10(1512, 70, 19u, ppRes, 1, 1u);

    field_20_animation.field_4_flags.Clear(AnimFlags::eBit3_Render);

    field_F4_tlvInfo = tlvInfo;

    field_20_animation.field_C_render_layer = 22;

    if (pTlv->field_10_scale == 1)
    {
        field_CC_sprite_scale = FP_FromDouble(0.5);
        field_D6_scale = 0;
    }
    else
    {
        field_CC_sprite_scale = FP_FromInteger(1);
        field_D6_scale = 1;
    }

    field_FA_id = pTlv->field_12_id;
    field_FC_code_converted = Code_Convert_4C9DF0(pTlv->field_14_code_1, pTlv->field_16_code2);
    field_100_code_len = Code_Length_4C9DB0(field_FC_code_converted);
    field_11C_top_left = pTlv->field_8_top_left;
    field_120_bottom_right = pTlv->field_C_bottom_right;
    field_B8_xpos = FP_FromInteger(pTlv->field_18_xpos);
    field_BC_ypos = FP_FromInteger(pTlv->field_1A_ypos);

    PSX_Point point = {};
    gMap_5C3030.Get_Abe_Spawn_Pos_4806D0(&point);

    if (field_B8_xpos > FP_FromInteger(0))
    {
        field_B8_xpos -= FP_FromInteger(point.field_0_x);
    }
    else
    {
        field_B8_xpos = FP_FromInteger((pTlv->field_8_top_left.field_0_x + pTlv->field_C_bottom_right.field_0_x) / 2);
    }

    if (field_BC_ypos > FP_FromInteger(0))
    {
        field_BC_ypos -= FP_FromInteger(point.field_2_y);
    }
    else
    {
        field_BC_ypos = FP_FromInteger((pTlv->field_8_top_left.field_2_y + pTlv->field_C_bottom_right.field_2_y) / 2);
    }

    if (pTlv->field_1_unknown)
    {
        field_F8_state = pTlv->field_1_unknown - 1;
    }
    else
    {
        field_F8_state = 0;
    }

    if (field_F8_state != 1)
    {
        field_124_timer = sGnFrame_5C1B84 + 10;
    }

    return this;
}

void SecurityDoor::VScreenChanged()
{
    vScreenChanged_4AC970();
}

void SecurityDoor::VUpdate()
{
    vUpdate_4AC380();
}

BaseGameObject* SecurityDoor::VDestructor(signed int flags)
{
    return vdtor_4AC230(flags);
}

void SecurityDoor::dtor_4AC260()
{
    SetVTable(this, 0x547028);
    if (field_F8_state != 1)
    {
        field_F8_state = 0;
    }
    Path::TLV_Reset_4DB8E0(field_F4_tlvInfo, field_F8_state + 1, 0, 0);
    BaseAnimatedWithPhysicsGameObject_dtor_424AD0();
}

void SecurityDoor::vScreenChanged_4AC970()
{
    field_6_flags.Set(BaseGameObject::eDead);
}

SecurityDoor* SecurityDoor::vdtor_4AC230(signed int flags)
{
    dtor_4AC260();
    if (flags & 1)
    {
        Mem_Free_495540(this);
    }
    return this;
}

__int16 SecurityDoor::IsPlayerNear_4AC300()
{
    const short xpos = FP_GetExponent(sControlledCharacter_5C1B8C->field_B8_xpos);
    const short ypos = FP_GetExponent(sControlledCharacter_5C1B8C->field_BC_ypos);

    if (xpos < field_11C_top_left.field_0_x || xpos > field_120_bottom_right.field_0_x)
    {
        return 0;
    }

    if (ypos >= field_11C_top_left.field_2_y && ypos <= field_120_bottom_right.field_2_y)
    {
        return 1;
    }

    return 0;
}

void SecurityDoor::vUpdate_4AC380()
{
    if (Event_Get_422C00(kEventDeathReset))
    {
        field_6_flags.Set(BaseGameObject::eDead);
    }

    switch (field_F8_state)
    {
    case 0:
        if (static_cast<int>(sGnFrame_5C1B84) <= field_124_timer)
        {
            return;
        }

        if (IsPlayerNear_4AC300())
        {
            field_20_animation.field_4_flags.Set(AnimFlags::eBit3_Render);
            field_F8_state = 2;
        }
        else
        {
            field_20_animation.field_4_flags.Clear(AnimFlags::eBit3_Render);
        }
        return;

    case 1:
        if (static_cast<int>(sGnFrame_5C1B84) == field_124_timer)
        {
            SND_SEQ_Play_4CAB10(31u, 1, 127, 127);
        }
        return;

    case 2:
        Sfx_Slig_GameSpeak_4C04F0(SligSpeak::Hi_0, 127, -200, 0);
        field_20_animation.Set_Animation_Data_409C80(1528, 0);
        field_F8_state = 3;
        field_124_timer = sGnFrame_5C1B84 + 150;
        return;

    case 3:
        if (field_104_event_idx != pEventSystem_5BC11C->field_28_last_event_index)
        {
            field_104_event_idx = pEventSystem_5BC11C->field_28_last_event_index;
            if (pEventSystem_5BC11C->field_20_last_event != GameSpeakEvents::eNone_m1 && pEventSystem_5BC11C->field_20_last_event != GameSpeakEvents::eSameAsLast_m2)
            {
                if (pEventSystem_5BC11C->field_20_last_event == GameSpeakEvents::Slig_Hi_27)
                {
                    field_F8_state = 4;
                    field_124_timer = sGnFrame_5C1B84 + 30;
                    return;
                }
                else
                {
                    field_F8_state = 12;
                    field_124_timer = sGnFrame_5C1B84 + 15;
                }
            }
        }

        if (static_cast<int>(sGnFrame_5C1B84) > field_124_timer)
        {
            field_F8_state = 0;
        }
        return;

    case 4:
        if (static_cast<int>(sGnFrame_5C1B84) > field_124_timer)
        {
            field_F8_state = 5;
        }
        return;

    case 5:
        field_128_max_idx = 0;
        field_118_max_idx = static_cast<short>(GameSpeak::sub_421970(field_FC_code_converted, field_108_stru));
        field_F8_state = 6;
        return;

    case 6:
    {
        // TODO: Optimized sub switch case - refactor
        const __int16 v8 = Code_LookUp_4C9E40(field_FC_code_converted, field_128_max_idx, field_100_code_len) - 5;
        if (v8)
        {
            const __int16 v9 = v8 - 2;
            if (v9)
            {
                if (v9 == 1)
                {
                    Sfx_Slig_GameSpeak_4C04F0(SligSpeak::Laugh_3, 127, -100, 0);
                }
            }
            else
            {
                Sfx_Slig_GameSpeak_4C04F0(SligSpeak::Bullshit2_7, 127, -100, 0);
            }
        }
        else
        {
            Sfx_Slig_GameSpeak_4C04F0(SligSpeak::Bullshit_5, 127, -100, 0);
        }

        field_20_animation.Set_Animation_Data_409C80(1528, 0);
        if (++field_128_max_idx >= field_100_code_len)
        {
            field_F8_state = 9;
            field_124_timer = sGnFrame_5C1B84 + 60;
        }
        else
        {
            field_F8_state = 7;
            field_124_timer = sGnFrame_5C1B84 + 30;
        }
        return;
    }

    case 7:
        if (static_cast<int>(sGnFrame_5C1B84) > field_124_timer)
        {
            field_F8_state = 6;
        }
        return;

    case 9:
        if (static_cast<int>(sGnFrame_5C1B84) <= field_124_timer)
        {
            if (field_104_event_idx != pEventSystem_5BC11C->field_28_last_event_index)
            {
                field_104_event_idx = pEventSystem_5BC11C->field_28_last_event_index;
                if (pEventSystem_5BC11C->field_20_last_event != GameSpeakEvents::eNone_m1 && pEventSystem_5BC11C->field_20_last_event != GameSpeakEvents::eSameAsLast_m2)
                {
                    field_11A_event_idx = static_cast<short>(pEventSystem_5BC11C->field_28_last_event_index);
                    field_F8_state = 10;
                }
            }
        }
        else
        {
            field_F8_state = 12;
            field_124_timer = sGnFrame_5C1B84 + 15;
        }
        return;

    case 10:
    {
        const int v15 = pEventSystem_5BC11C->sub_4219E0(field_108_stru, field_118_max_idx, field_11A_event_idx);
        if (v15 == 1)
        {
            field_F8_state = 11;
            field_124_timer = sGnFrame_5C1B84 + 15;
        }
        else if (v15 == 0)
        {
            field_F8_state = 12;
            field_124_timer = sGnFrame_5C1B84 + 15;
        }
        else
        {
            if (field_104_event_idx == pEventSystem_5BC11C->field_28_last_event_index)
            {
                if (pEventSystem_5BC11C->field_20_last_event == GameSpeakEvents::eNone_m1)
                {
                    field_F8_state = 12;
                    field_124_timer = sGnFrame_5C1B84;
                }
            }
            else
            {
                field_104_event_idx = pEventSystem_5BC11C->field_28_last_event_index;
                if (pEventSystem_5BC11C->field_20_last_event == GameSpeakEvents::eNone_m1)
                {
                    field_F8_state = 12;
                    field_124_timer = sGnFrame_5C1B84;
                }
            }
        }
        return;
    }

    case 11:
        if (static_cast<int>(sGnFrame_5C1B84) <= field_124_timer)
        {
            return;
        }
        field_12A = 1;
        SwitchStates_Set_465FF0(field_FA_id, 1);
        field_20_animation.field_4_flags.Clear(AnimFlags::eBit3_Render);
        SFX_Play_46FBA0(88u, 127, -700);
        field_F8_state = 1;
        field_124_timer = sGnFrame_5C1B84 + 15;
        return;

    case 12:
        if (static_cast<int>(sGnFrame_5C1B84) <= field_124_timer)
        {
            return;
        }
        SFX_Play_46FBA0(38u, 60, -720);
        field_F8_state = 13;
        field_124_timer = sGnFrame_5C1B84 + 15;
        return;

    case 13:
        if (static_cast<int>(sGnFrame_5C1B84) <= field_124_timer)
        {
            return;
        }
        SFX_Play_46FBA0(87u, 127, -1000);
        field_F8_state = 0;
        field_124_timer = sGnFrame_5C1B84 + 90;
        return;

    default:
        return;
    }
}
