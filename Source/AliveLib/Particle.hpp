#pragma once

#include "BaseAnimatedWithPhysicsGameObject.hpp"

class Particle : public BaseAnimatedWithPhysicsGameObject
{
public:
    EXPORT Particle* ctor_4CC4C0(FP xpos, FP ypos, int animFrameTableOffset, int maxW, int maxH, BYTE** ppAnimData);
    EXPORT void vUpdate_4CC620();
    EXPORT BaseGameObject* vdtor_4CC5D0(signed int flags);

    virtual void VUpdate() override;
    virtual BaseGameObject* VDestructor(signed int flags) override;
public:
    FP field_F4_scale_amount;
};
ALIVE_ASSERT_SIZEOF(Particle, 0xF8);

EXPORT Particle* CC New_Particle_426F40(FP xpos, FP ypos, FP scale);
EXPORT Particle* CC New_Particle_426AA0(FP xpos, FP ypos, FP velY, FP velX, FP scale, __int16 layer, BYTE r, BYTE b, BYTE g);
EXPORT Particle* CC New_Chant_Particle_426BE0(FP xpos, FP ypos, FP scale, __int16 layer);
EXPORT void CC New_Particles_426C70(FP xpos, FP ypos, FP scale, __int16 count, BYTE r, BYTE g, BYTE b);
EXPORT void New_Particle_45BC70(class BaseAliveGameObject* pObj);
EXPORT Particle* CC New_Particle_426C30(FP xpos, FP ypos, FP scale, __int16 layer);
EXPORT void CC New_Particle_4269B0(FP xpos, FP ypos, FP scale);
EXPORT void CC New_Particle_426890(FP xpos, FP ypos, char direction, FP scale);