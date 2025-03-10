#pragma once

#include "Function.hpp"
#include "BaseGameObject.hpp"
#include "FixedPoint.hpp"

class Class_5480D4;

class OrbWhirlWind : public BaseGameObject
{
public:
    EXPORT OrbWhirlWind* ctor_4E3C90(FP xpos, FP ypos, FP scale, __int16 bUnknown);
    EXPORT void ToSpin_4E3FD0(FP xpos, FP ypos, FP scale, BaseGameObject* pObj);
    EXPORT void ToStop_4E4050();

    virtual BaseGameObject* VDestructor(signed int flags) override;
    virtual void VUpdate() override;
    virtual void VRender(int** pOrderingTable) override;

private:
    EXPORT void vRender_4E3F80(int** ppOt);
    EXPORT void vUpdate_4E3E20();
    EXPORT void dtor_4E3D80();
    EXPORT OrbWhirlWind* vdtor_4E3D50(signed int flags);
private:
    int field_20;
    __int16 field_24;
    __int16 field_26_bUnknown;
    __int16 field_28_obj_array_idx;
    //__int16 field_2A; // padding ?
    Class_5480D4* field_2C_objArray[16];
    FP field_6C_xpos;
    FP field_70_ypos;
    FP field_74_scale;
};
ALIVE_ASSERT_SIZEOF(OrbWhirlWind, 0x78);
