#pragma once

#include "BaseGameObject.hpp"
#include "Path.hpp"
#include "FunctionFwd.hpp"

class Electrocute;

class Teleporter : public BaseGameObject
{
public:
    EXPORT Teleporter* ctor_4DC1E0(Path_Teleporter* pTlv, DWORD tlvInfo);
    virtual BaseGameObject* VDestructor(signed int flags) override;
    virtual void VUpdate() override;
    virtual void VScreenChanged() override;
private:
    EXPORT Teleporter* vdtor_4DC350(signed int flags);
    EXPORT void dtor_4DC380();
    EXPORT void vScreenChanged_4DCE80();
    EXPORT void vUpdate_4DC400();
private:
    EXPORT static Electrocute* CC Create_ElectrocuteEffect_4DCEB0();
    void SpawnRingSparks(Path_Teleporter_Data* pTlvData);

    int field_20_tlvInfo;
    __int16 field_24_global_y1;
    __int16 field_26_global_x1;
    __int16 field_28_global_y2;
    __int16 field_2A_global_x2;
    int field_2C_switch_state;
   // __int16 field_2E;
    enum class States : char
    {
        eState_WaitForSwitchOn_0 = 0,
        eState_Into_Teleporter_1 = 1,
        eState_Teleporting_2 = 2,
        eState_Out_of_teleporter_4 = 4,
    };
    States field_30_state;
    char field_31;
    __int16 field_32_bDestroySelf;
    Path_Teleporter_Data field_34_mTlvData;
    __int16 field_4A;
    Path_Teleporter* field_4C_pTlv;
    int field_50_objId;
    __int16 field_54_effect_created;
    __int16 field_56;
};
ALIVE_ASSERT_SIZEOF(Teleporter, 0x58);
