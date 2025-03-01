#pragma once

#include "FunctionFwd.hpp"

void SwitchStates_ForceLink();

EXPORT void CC SwitchStates_SetRange_465FA0(unsigned __int16 start, unsigned __int16 end);
EXPORT void CC SwitchStates_Set_465FF0(unsigned __int16 idx, char value);
EXPORT int CC SwitchStates_Get_466020(unsigned __int16 idx);
EXPORT void CC SwitchStates_Add_466060(unsigned __int16 idx, char value);

enum class SwitchOp : __int16
{
    eSetTrue_0 = 0,
    eSetFalse_1 = 1,
    eToggle_2 = 2,
    eIncrement_3 = 3,
    eDecrement_4 = 4,
};

EXPORT void CC SwitchStates_Do_Operation_465F00(signed __int16 idx, SwitchOp operation);

struct SwitchStates
{
    char mData[256];
};

ALIVE_VAR_EXTERN(SwitchStates, sSwitchStates_5C1A28);
