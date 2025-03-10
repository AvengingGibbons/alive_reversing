#pragma once

#include "FunctionFwd.hpp"
#include "bmp.hpp"
#include "FixedPoint.hpp"

void Psx_ForceLink();

struct PSX_RECT
{
    short x, y, w, h;
};
ALIVE_ASSERT_SIZEOF(PSX_RECT, 8);

struct FP_RECT
{
    FP x, y, w, h;
};
ALIVE_ASSERT_SIZEOF(FP_RECT, 4*4);

inline bool operator == (const PSX_RECT& lhs, const PSX_RECT& rhs)
{
    return 
        (lhs.x == rhs.x) && 
        (lhs.y == rhs.y) && 
        (lhs.w == rhs.w) && 
        (lhs.h == rhs.h);
}

inline bool RectsOverlap(const PSX_RECT& r1, const PSX_RECT& r2)
{
   return !(r2.x > r1.w ||
            r2.w < r1.x ||
            r2.y > r1.h ||
            r2.h < r1.y);
}

struct PSX_Point
{
    short field_0_x;
    short field_2_y;
};
ALIVE_ASSERT_SIZEOF(PSX_Point, 4);

struct PSX_DISPENV
{
    PSX_RECT disp;
    PSX_RECT screen;
    char isinter;
    char isrgb24;
    char pad0;
    char pad1;
};
// TODO: Size

struct PSX_DR_ENV
{
    int field_0_tag;
    int field_4_code[15];
};
// TODO: Size

struct PSX_DRAWENV
{
    PSX_RECT field_0_clip;
    __int16 field_8_ofs[2];
    PSX_RECT field_C_tw;
    unsigned __int16 field_14_tpage;
    char field_16_dtd;
    char field_17_dfe;
    char field_18_isbg;
    char field_19_r0;
    char field_1A_g0;
    char field_1B_b0;
    PSX_DR_ENV field_1C_dr_env;
};
// TODO: Size

using TPsxEmuCallBack = std::add_pointer<int(DWORD)>::type;

EXPORT void CC PSX_DispEnv_Set_4ED960(int mode);
EXPORT int CC PSX_VSync_4F6170(int mode);
EXPORT int CC PSX_DrawSync_4F6280(int mode);
EXPORT bool CC PSX_Rect_IsInFrameBuffer_4FA050(const PSX_RECT* pRect);
EXPORT int CC PSX_SetDispMask_4F89F0(int mode);
EXPORT int CC PSX_SetVideoMode_4FA8F0();
EXPORT int CC PSX_ResetGraph_4F8800(int);
EXPORT int CC PSX_SetGraphDebug_4F8A10(int);
EXPORT void CC PSX_SetDefDrawEnv_4F5AA0(PSX_DRAWENV* pDrawEnv, __int16 x, __int16 y, __int16 w, __int16 h);
EXPORT void CC PSX_SetDefDispEnv_4F55A0(PSX_DISPENV* pOutEnv, __int16 x, __int16 y, __int16 w, __int16 h);
EXPORT void CC PSX_PutDrawEnv_4F5980(const PSX_DRAWENV* pDrawEnv);
EXPORT void CC PSX_PutDispEnv_4F5890(PSX_DISPENV* pDispEnv);
EXPORT void CC PSX_PutDispEnv_4F58E0(const PSX_DISPENV* pDispEnv);
EXPORT void CC PSX_EMU_VideoDeAlloc_4FA010();
EXPORT int CC PSX_ResetCallBack_4FAA20();
EXPORT int CC PSX_CdInit_4FB2C0();
EXPORT int CC PSX_CdSetDebug_4FB330(int mode);
EXPORT int CC PSX_CdControlB_4FB320(int, int, int);
EXPORT int CC PSX_StopCallBack_4FAA30();
EXPORT int CC PSX_EMU_VideoAlloc_4F9D70();
EXPORT void CC Init_VGA_AndPsxVram_494690();
EXPORT void CC PSX_EMU_Init_4F9CD0(bool bShowVRam);
EXPORT void CC PSX_EMU_SetCallBack_4F9430(int callBackType, TPsxEmuCallBack fnPtr);
EXPORT signed int CC PSX_EMU_Set_Cd_Emulation_Paths_4FAA70(const char* pPath1, const char* pPath2, const char* pPath3);
EXPORT void CC PSX_EMU_Set_screen_mode_4F9420(char mode);
EXPORT signed int CC PSX_MoveImage_4F5D50(const PSX_RECT* pRect, int xpos, int ypos);
EXPORT int CC PSX_LoadImage16_4F5E20(const PSX_RECT* pRect, const BYTE* pData);
EXPORT int CC PSX_LoadImage_4F5FB0(const PSX_RECT* pRect, const BYTE* pData);
EXPORT signed int CC PSX_StoreImage_4F5E90(const PSX_RECT* rect, WORD* pData);

BOOL CC PSX_Rects_overlap_no_adjustment(const PSX_RECT* pRect1, const PSX_RECT* pRect2);

EXPORT BOOL CC PSX_Rects_overlap_4FA0B0(const PSX_RECT* pRect1, const PSX_RECT* pRect2);
EXPORT void CC PSX_SetDrawEnv_Impl_4FE420(int x, int y, int w, int h, int unknown, BYTE* pBuffer);

EXPORT void CC PSX_CD_Normalize_FileName_4FAD90(char* pNormalized, const char* pFileName);
EXPORT int CC PSX_CD_OpenFile_4FAE80(const char* pFileName, int bTryAllPaths);

EXPORT void CC sub_4945B0();

struct CdlLOC
{
    unsigned __int8 field_0_minute;
    unsigned __int8 field_1_second;
    unsigned __int8 field_2_sector;
    char field_3_track;
};
ALIVE_ASSERT_SIZEOF(CdlLOC, 0x4);

EXPORT CdlLOC* CC PSX_Pos_To_CdLoc_4FADD0(int pos, CdlLOC* pLoc);
EXPORT int CC PSX_CdLoc_To_Pos_4FAE40(const CdlLOC* pLoc);
EXPORT int CC PSX_CD_File_Seek_4FB1E0(char mode, const CdlLOC* pLoc);
EXPORT int CC PSX_CD_File_Read_4FB210(int numSectors, void* pBuffer);
EXPORT int CC PSX_CD_FileIOWait_4FB260(int bASync);

ALIVE_VAR_EXTERN(Bitmap, sPsxVram_C1D160);
ALIVE_VAR_EXTERN(BYTE, byte_BD0F20);
ALIVE_VAR_EXTERN(PSX_DRAWENV, sPSX_EMU_DrawEnvState_C3D080);
ALIVE_VAR_EXTERN(BYTE, sPsxEMU_show_vram_BD1465);
ALIVE_VAR_EXTERN(Bitmap*, spBitmap_C2D038);

ALIVE_VAR_EXTERN(TPsxEmuCallBack, sPsxEmu_EndFrameFnPtr_C1D17C);
ALIVE_VAR_EXTERN(BYTE, bDontUseXYOffsetInRender_BD1464);
ALIVE_VAR_EXTERN(Bitmap, stru_C1D1A0);
ALIVE_VAR_EXTERN(int, sVGA_DisplayType_BD1468);

ALIVE_ARY_EXTERN(char, 128, sCdEmu_Path1_C14620);
ALIVE_ARY_EXTERN(char, 128, sCdEmu_Path2_C144C0);
ALIVE_ARY_EXTERN(char, 128, sCdEmu_Path3_C145A0);

ALIVE_VAR_EXTERN(int, sPsx_drawenv_clipx_BDCD40);
ALIVE_VAR_EXTERN(int, sPsx_drawenv_clipy_BDCD44);
ALIVE_VAR_EXTERN(int, sPsx_drawenv_clipw_BDCD48);
ALIVE_VAR_EXTERN(int, sPsx_drawenv_cliph_BDCD4C);


namespace Test
{
    void PsxTests();
}
