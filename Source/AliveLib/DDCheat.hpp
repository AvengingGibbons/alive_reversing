#pragma once

#include "FunctionFwd.hpp"
#include "BaseGameObject.hpp"
#include "Game.hpp"
#include "Input.hpp"
#include "Function.hpp"
#include "BaseAliveGameObject.hpp"

void DDCheat_ForceLink();

struct DDCheatProperty
{
    const char * Name;
    int Unknown;
    int * ValuePtr;
};
ALIVE_ASSERT_SIZEOF(DDCheatProperty, 12);

class DDCheat : public BaseGameObject
{
public:
    virtual BaseGameObject* VDestructor(signed int flags) override;
    virtual void VUpdate() override;
    virtual void VRender(int**) override { }
    virtual void VScreenChanged() override { }

    DDCheat();
    EXPORT DDCheat* ctor_4153C0();
    EXPORT void dtor_415530();
    EXPORT BaseGameObject* vdtor_415500(signed int flags);

    EXPORT static void AddPropertyEntry_004162C0(const char *text, int unknown, int *valuePtr);
    static EXPORT void CC ClearProperties_415390();
    static EXPORT void DebugStr_4F5560(const char *pFormatStr, ...);

    EXPORT void Menu_Teleport_415E20();
    EXPORT void Menu_Movies_416000();

public:
    EXPORT void Update_415780();
public:
    int field_20;
    __int16 field_24_fn_idx;
    __int16 field_26_next_fn_idx;
    int field_28;
    int field_2C;
    __int16 field_30;
    __int16 field_32;
    int field_34;
    int field_38_input_pressed;
    __int16 field_3C_flags;
    __int16 field_3E;
};
ALIVE_ASSERT_SIZEOF(DDCheat, 0x40);

ALIVE_VAR_EXTERN(bool, sDDCheat_FlyingEnabled_5C2C08);

ALIVE_VAR_EXTERN(__int16, sRescuedMudokons_5C1BC2);
ALIVE_VAR_EXTERN(__int16, sKilledMudokons_5C1BC0);

ALIVE_VAR_EXTERN(int, sTweakX_5C1BD0);
ALIVE_VAR_EXTERN(int, sTweakY_5C1BD4);

ALIVE_VAR_EXTERN(__int16, sVisitedBonewerks_5C1C02);
ALIVE_VAR_EXTERN(__int16, sVisitedBarracks_5C1C04);
ALIVE_VAR_EXTERN(__int16, sVisitedFeecoEnder_5C1C06);
ALIVE_VAR_EXTERN(bool, sDDCheat_ShowAI_Info_5C1BD8);
