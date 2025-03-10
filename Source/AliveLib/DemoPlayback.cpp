#include "stdafx.h"
#include "DemoPlayback.hpp"
#include "Input.hpp"
#include "ResourceManager.hpp"
#include "Events.hpp"
#include "Map.hpp"
#include "PathData.hpp"
#include "stdlib.hpp"
#include "Function.hpp"

ALIVE_VAR(1, 0x5D1E20, DemoPlayback*, sDemoObj_dword_5D1E20, nullptr);
ALIVE_VAR(1, 0x5C1B9C, short, word_5C1B9C, 0);

void DemoPlayback::ctor()
{
    BaseGameObject_ctor_4DBFA0(TRUE, 0);
    SetVTable(this, 0x54690C);
    field_4_typeId = Types::eDemoPlayback_98;

    //nullsub_31(j_nullsub_31);

    if (sDemoObj_dword_5D1E20)
    {
        field_6_flags.Set(BaseGameObject::eDead);
    }
    else
    {
        field_6_flags.Set(BaseGameObject::eSurviveDeathReset);

        DWORD** ppRes = reinterpret_cast<DWORD**>(Add_Resource_4DC130(ResourceManager::Resource_Demo, 1));
        field_1C_update_delay = 1;
        sInputObject_5BD4E0.SetDemoResource_45F1E0(ppRes);

        //nullsub_31(j_nullsub_31);
    }
}

BaseGameObject* DemoPlayback::VDestructor(signed int flags)
{
    return vdtor_497880(flags);
}

void DemoPlayback::VUpdate()
{
    vUpdate_4978E0();
}

void DemoPlayback::VScreenChanged()
{
    // Keep alive
}

void DemoPlayback::dtor_4978B0()
{
    SetVTable(this, 0x54690C);
    if (sDemoObj_dword_5D1E20 == this)
    {
        sDemoObj_dword_5D1E20 = nullptr;
    }
    BaseGameObject_dtor_4DBEC0();
}

DemoPlayback* DemoPlayback::vdtor_497880(signed int flags)
{
    dtor_4978B0();
    if (flags & 1)
    {
        Mem_Free_495540(this);
    }
    return this;
}

void DemoPlayback::vUpdate_4978E0()
{
    if (Event_Get_422C00(kEventDeathReset))
    {
        sInputObject_5BD4E0.UnsetDemoPlaying_45F240();
    }

    if (!sInputObject_5BD4E0.Is_Demo_Playing_45F220())
    {
        if (word_5C1B9C)
        {
            gMap_5C3030.SetActiveCam_480D30(LevelIds::eMenu_0, 1, 30, CameraSwapEffects::eEffect0_InstantChange, 0, 0);
        }
        else
        {
            gMap_5C3030.SetActiveCam_480D30(LevelIds::eMenu_0, 1, 1, CameraSwapEffects::eEffect0_InstantChange, 0, 0);
        }

        gMap_5C3030.field_CE_free_all_anim_and_palts = 1;
        field_6_flags.Set(BaseGameObject::eDead);
    }
}
