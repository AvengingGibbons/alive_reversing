#include "stdafx.h"
#include "Psx.hpp"
#include "Function.hpp"
#include "Error.hpp"
#include "bmp.hpp"
#include "Midi.hpp"
#include "PsxDisplay.hpp"
#include "VGA.hpp"
#include "stdlib.hpp"
#include "Io.hpp"
#include "Game.hpp" // sIOSyncReads_BD2A5C, sCdRomDrives_5CA488
#include "PsxRender.hpp"
#include "Sys.hpp"
#include "PsxRender.hpp"
#include <gmock/gmock.h>

void Psx_ForceLink() {}

ALIVE_VAR(1, 0x578325, char, sVSync_Unused_578325, 0);
ALIVE_VAR(1, 0xBD0F2C, int, sVSyncLastMillisecond_BD0F2C, 0);
ALIVE_VAR(1, 0xBD0F24, int, sLastFrameTimestampMilliseconds_BD0F24, 0);

ALIVE_VAR(1, 0xC3D080, PSX_DRAWENV, sPSX_EMU_DrawEnvState_C3D080, {});
ALIVE_VAR(1, 0x578E88, int, sConst_1000_578E88, 1000);
ALIVE_VAR(1, 0xBD1464, BYTE, bDontUseXYOffsetInRender_BD1464, 0);

ALIVE_VAR(1, 0xBDCD40, int, sPsx_drawenv_clipx_BDCD40, 0);
ALIVE_VAR(1, 0xBDCD44, int, sPsx_drawenv_clipy_BDCD44, 0);
ALIVE_VAR(1, 0xBDCD48, int, sPsx_drawenv_clipw_BDCD48, 0);
ALIVE_VAR(1, 0xBDCD4C, int, sPsx_drawenv_cliph_BDCD4C, 0);
ALIVE_VAR(1, 0xBDCD50, int, sPsx_drawenv_k500_BDCD50, 0);
ALIVE_VAR(1, 0xBDCD54, BYTE*, sPsx_drawenv_buffer_BDCD54, nullptr);
ALIVE_VAR(1, 0xBD1465, BYTE, sPsxEMU_show_vram_BD1465, 0);

ALIVE_VAR(1, 0xC1D160, Bitmap, sPsxVram_C1D160, {});
ALIVE_VAR(1, 0xC1D1A0, Bitmap, stru_C1D1A0, {}); // Note: never used?

ALIVE_VAR(1, 0xC2D060, PSX_DISPENV, sLastDispEnv_C2D060, {});
ALIVE_VAR(1, 0xBD146D, BYTE, sScreenMode_BD146D, 0);
ALIVE_VAR(1, 0xBD0F20, BYTE, byte_BD0F20, 0);
ALIVE_VAR(1, 0x578324, BYTE, byte_578324, 1);


ALIVE_ARY(1, 0xC14620, char, 128, sCdEmu_Path1_C14620, {});
ALIVE_ARY(1, 0xC144C0, char, 128, sCdEmu_Path2_C144C0, {});
ALIVE_ARY(1, 0xC145A0, char, 128, sCdEmu_Path3_C145A0, {});

ALIVE_VAR(1, 0xBD1CC4, IO_Handle*, sCdFileHandle_BD1CC4, nullptr);
ALIVE_VAR(1, 0xBD1894, int, sCdReadPos_BD1894, 0);

EXPORT int CC PSX_CD_OpenFile_4FAE80(const char* pFileName, int bTryAllPaths)
{
    static char sLastOpenedFileName_BD1898[1024] = {};

    char pNormalizedName[256] = {};
    char fullFilePath[1024] = {};

    if (_strcmpi(sLastOpenedFileName_BD1898, pFileName) != 0)
    {
        PSX_CD_Normalize_FileName_4FAD90(pNormalizedName, (*pFileName == '\\') ? pFileName + 1 : pFileName);
        //dword_578D5C = -1; // Note: Never read
        sCdReadPos_BD1894 = 0;

        int openMode = 1;
        if (!sIOSyncReads_BD2A5C)
        {
            openMode = 5;
        }

        strcpy(fullFilePath, sCdEmu_Path1_C14620);
        strcat(fullFilePath, pNormalizedName);
        if (bTryAllPaths)
        {
            // Close any existing open file
            if (sCdFileHandle_BD1CC4)
            {
                IO_fclose_4F24E0(sCdFileHandle_BD1CC4);
                sLastOpenedFileName_BD1898[0] = 0;
            }

            // Try to open from path 1
            sCdFileHandle_BD1CC4 = IO_Open_4F2320(fullFilePath, openMode);
            if (!sCdFileHandle_BD1CC4)
            {
                // Failed, try path 2
                strcpy(fullFilePath, sCdEmu_Path2_C144C0);
                strcat(fullFilePath, pNormalizedName);
                sCdFileHandle_BD1CC4 = IO_Open_4F2320(fullFilePath, openMode);
                if (!sCdFileHandle_BD1CC4)
                {
                    // Failed try path 3 - each CD drive in the system
                    strcpy(fullFilePath, sCdEmu_Path3_C145A0);
                    strcat(fullFilePath, pNormalizedName);

                    // Oops, we don't have any CD-ROM drives
                    if (!sCdRomDrives_5CA488[0])
                    {
                        return 0;
                    }

                    char* pCdRomDrivesIter = sCdRomDrives_5CA488;
                    while (*pCdRomDrivesIter)
                    {
                        fullFilePath[0] = *pCdRomDrivesIter;
                        if (*pCdRomDrivesIter != sCdEmu_Path2_C144C0[0])
                        {
                            sCdFileHandle_BD1CC4 = IO_Open_4F2320(fullFilePath, openMode);
                            if (sCdFileHandle_BD1CC4)
                            {
                                // Update the default CD-ROM to try
                                sCdEmu_Path2_C144C0[0] = fullFilePath[0];
                                strcpy(sLastOpenedFileName_BD1898, pFileName);
                                return 1;
                            }
                        }
                        pCdRomDrivesIter++;
                    }
                    return 0;
                }
            }
        }
        else
        {
            // Open the file
            IO_Handle* hFile = IO_Open_4F2320(fullFilePath, openMode);
            if (!hFile)
            {
                return 0;
            }

            // Close the old file and set the current file as the new one
            if (sCdFileHandle_BD1CC4)
            {
                IO_fclose_4F24E0(sCdFileHandle_BD1CC4);
                sLastOpenedFileName_BD1898[0] = 0;
            }
            sCdFileHandle_BD1CC4 = hFile;
        }
        strcpy(sLastOpenedFileName_BD1898, pFileName);
    }
    return 1;
}

EXPORT CdlLOC* CC PSX_Pos_To_CdLoc_4FADD0(int pos, CdlLOC* pLoc)
{
    pLoc->field_3_track = 0;
    pLoc->field_0_minute = static_cast<BYTE>(pos / 75 / 60 + 2);
    pLoc->field_1_second = pos / 75 % 60;
    pLoc->field_2_sector = static_cast<BYTE>(pos + 108 * (pos / 75 / 60) - 75 * (pos / 75 % 60));
    return pLoc;
}

EXPORT int CC PSX_CdLoc_To_Pos_4FAE40(const CdlLOC* pLoc)
{
    int min = pLoc->field_0_minute;
    if (min < 2)
    {
        min = 2;
    }
    return pLoc->field_2_sector + 75 * (pLoc->field_1_second + 20 * (3 * min - 6));
}

EXPORT int CC PSX_CD_File_Seek_4FB1E0(char mode, const CdlLOC* pLoc)
{
    if (mode != 2)
    {
        return 0;
    }
    sCdReadPos_BD1894 = PSX_CdLoc_To_Pos_4FAE40(pLoc);
    return 1;
}

EXPORT int CC PSX_CD_File_Read_4FB210(int numSectors, void* pBuffer)
{
    IO_Seek_4F2490(sCdFileHandle_BD1CC4, sCdReadPos_BD1894 << 11, 0);
    IO_Read_4F23A0(sCdFileHandle_BD1CC4, pBuffer, numSectors << 11);
    sCdReadPos_BD1894 += numSectors;
    return 1;
}

EXPORT int CC PSX_CD_FileIOWait_4FB260(int bASync)
{
    if (!sCdFileHandle_BD1CC4)
    {
        return -1;
    }

    if (!bASync)
    {
        IO_WaitForComplete_4F2510(sCdFileHandle_BD1CC4);
    }
    return sCdFileHandle_BD1CC4->field_10_bDone != 0;
}

ALIVE_VAR(1, 0xC1D184, TPsxEmuCallBack, sPsxEmu_put_disp_env_callback_C1D184, nullptr);
ALIVE_VAR(1, 0xC1D17C, TPsxEmuCallBack, sPsxEmu_EndFrameFnPtr_C1D17C, nullptr);
ALIVE_VAR(1, 0xBD0F21, BYTE, sPsxDontChangeDispEnv_BD0F21, 0);
ALIVE_VAR(1, 0xBD145C, bool, sbBitmapsAllocated_BD145C, false);



EXPORT void CC PSX_DispEnv_4EDAB0(Bitmap* /*pBmp*/, int /*left*/, int /*top*/, int /*width*/)
{
    NOT_IMPLEMENTED();
}

EXPORT void CC PSX_DispEnv_Reset_Unknown_4ED9E0()
{
    NOT_IMPLEMENTED();
}

ALIVE_VAR(1, 0xC2D038, Bitmap*, spBitmap_C2D038, nullptr);



EXPORT void CC PSX_EMU_Init_4F9CD0(bool bShowVRam)
{
    memset(&sPsxVram_C1D160, 0, sizeof(sPsxVram_C1D160));
    memset(&stru_C1D1A0, 0, sizeof(stru_C1D1A0));

    sPsxEmu_EndFrameFnPtr_C1D17C = nullptr;
    sPsxEmu_put_disp_env_callback_C1D184 = nullptr;
    sPsxEMU_show_vram_BD1465 = bShowVRam;
    
    Psx_Render_Float_Table_Init();

    // Note: sPsxEmu_BD1454 removed
}

ALIVE_VAR(1, 0xBD1468, int, sVGA_DisplayType_BD1468, 0);

EXPORT void CC PSX_EMU_SetCallBack_4F9430(int callBackType, TPsxEmuCallBack fnPtr)
{
    if (callBackType)
    {
        if (callBackType == 1)
        {
            sPsxEmu_put_disp_env_callback_C1D184 = fnPtr;
        }
    }
    else
    {
        sPsxEmu_EndFrameFnPtr_C1D17C = fnPtr;
    }
}

EXPORT void CC PSX_EMU_Set_screen_mode_4F9420(char /*mode*/)
{
    NOT_IMPLEMENTED();
}

EXPORT signed int CC PSX_CD_Add_EMU_Path_4FAC00(const char* /*filePath*/)
{
    NOT_IMPLEMENTED();
    return 0;
}

#if _WIN32
const char kDirChar[] = "\\";
#else
const char kDirChar[] = "/";
#endif

EXPORT signed int CC PSX_EMU_Set_Cd_Emulation_Paths_4FAA70(const char* pPath1, const char* pPath2, const char* pPath3)
{
    if (pPath1)
    {
        if (strlen(pPath1) >= 128) // TODO: _countof when done
        {
            return -1;
        }
        strcpy(sCdEmu_Path1_C14620, pPath1);
        PSX_CD_Add_EMU_Path_4FAC00(sCdEmu_Path1_C14620);
        if (sCdEmu_Path1_C14620[strlen(sCdEmu_Path1_C14620) - 1] != kDirChar[0])
        {
            strcat(sCdEmu_Path1_C14620, kDirChar);
        }
    }

    if (pPath2)
    {
        if (strlen(pPath2) >= 128) // TODO: _countof when done
        {
            return -2;
        }
        strcpy(sCdEmu_Path2_C144C0, pPath2);
        PSX_CD_Add_EMU_Path_4FAC00(sCdEmu_Path2_C144C0);
        if (sCdEmu_Path2_C144C0[strlen(sCdEmu_Path2_C144C0) - 1] != kDirChar[0])
        {
            strcat(sCdEmu_Path2_C144C0, kDirChar);
        }
    }

    if (pPath3)
    {
        if (strlen(pPath3) >= 128) // TODO: _countof when done
        {
            return -3;
        }
        strcpy(sCdEmu_Path3_C145A0, pPath3);
        PSX_CD_Add_EMU_Path_4FAC00(sCdEmu_Path3_C145A0);
        if (sCdEmu_Path3_C145A0[strlen(sCdEmu_Path3_C145A0) - 1] != kDirChar[0])
        {
            strcat(sCdEmu_Path3_C145A0, kDirChar);
        }
    }

    return 0;
}

EXPORT int CC PSX_ResetCallBack_4FAA20()
{
    return 0;
}

EXPORT int CC PSX_StopCallBack_4FAA30()
{
    return 0;
}

EXPORT int CC PSX_CdInit_4FB2C0()
{
    return 1;
}

EXPORT int CC PSX_CdSetDebug_4FB330(int /*mode*/)
{
    return 1;
}

EXPORT int CC PSX_CdControlB_4FB320(int, int, int)
{
    return 0;
}

EXPORT int CC PSX_EMU_VideoAlloc_4F9D70()
{
    if (!sbBitmapsAllocated_BD145C)
    {
        if (sVGA_DisplayType_BD1468 == 1)
        {
            sVGA_DisplayType_BD1468 = 4;
            if (BMP_New_4F1990(&sPsxVram_C1D160, 1024, 512, 15, 1))
            {
                Error_PushErrorRecord_4F2920("C:\\abe2\\code\\PSXEmu\\PSXEMU.C", 405, -1, "PSXEMU_VideoAlloc: can't alloc PSX-VRAM");
                return -1;
            }

            PSX_EMU_SetDispType_4F9960(sVGA_DisplayType_BD1468);
        }
        else
        {
            int pixelFormat = 0;
            switch (sVGA_DisplayType_BD1468)
            {
            case 2:
                pixelFormat = 16;
                break;
            case 3:
                pixelFormat = 116;
                break;
            case 4:
                pixelFormat = 15;
                break;
            case 5:
                pixelFormat = 115;
                break;
            default:
                pixelFormat = 0;
                break;
            }

            if (BMP_New_4F1990(&sPsxVram_C1D160, 1024, 512, pixelFormat, 1))
            {
                Error_PushErrorRecord_4F2920("C:\\abe2\\code\\PSXEmu\\PSXEMU.C", 414, -1, "PSXEMU_VideoAlloc: can't alloc PSX-VRAM");
                return -1;
            }
        }

        bDontUseXYOffsetInRender_BD1464 = 0;
        sbBitmapsAllocated_BD145C = 1;
    }

    PSX_RECT rect = {};
    rect.x = 0;
    rect.y = 0;
    rect.w = 1024;
    rect.h = 512;
    PSX_ClearImage_4F5BD0(&rect, 0, 0, 0);
    return 0;
}

EXPORT void CC Init_VGA_AndPsxVram_494690()
{
    VGA_FullScreenSet_4F31F0(true);
    VGA_DisplaySet_4F32C0(640u, 480u, 16u, 2u, 0);

    RECT rect = {};
    rect.left = 0;
    rect.top = 0;
    rect.right = 640;
    rect.bottom = 480;
    BMP_ClearRect_4F1EE0(&sVGA_bmp_primary_BD2A20, &rect, 0);

    switch (VGA_GetPixelFormat_4F3EE0())
    {
    case 8:
        PSX_EMU_SetDispType_4F9960(1);
        break;
    case 15:
        PSX_EMU_SetDispType_4F9960(4);
        break;
    case 32: // Allow 32bit colour
    case 16:
        PSX_EMU_SetDispType_4F9960(2);
        break;
    case 115:
        PSX_EMU_SetDispType_4F9960(5);
        break;
    case 116:
        PSX_EMU_SetDispType_4F9960(3);
        break;
    default:
        Error_WarningMessageBox_4F2D80("This program requires a high-color display mode of 32768 or 65536 colors at 640x480 resolution.");
        Error_ShowErrorStackToUser_4F2A70(false);
        return;
    }
}

EXPORT void CC PSX_EMU_VideoDeAlloc_4FA010()
{
    if (sbBitmapsAllocated_BD145C)
    {
        Bmp_Free_4F1950(&sPsxVram_C1D160);
        if (bDontUseXYOffsetInRender_BD1464)
        {
            Bmp_Free_4F1950(&stru_C1D1A0);
            bDontUseXYOffsetInRender_BD1464 = 0;
        }
        sbBitmapsAllocated_BD145C = false;
    }
}


EXPORT void CC PSX_PutDispEnv_Impl_4F5640(const PSX_DISPENV* pDispEnv, char a2)
{
    if (!pDispEnv)
    {
        Error_PushErrorRecord_4F2920("C:\\abe2\\code\\PSXEmu\\LIBGPU.C", 217, -1, "PutDispEnv(): env == NULL");
        return;
    }

    MIDI_UpdatePlayer_4FDC80();
    memcpy(&sLastDispEnv_C2D060, pDispEnv, sizeof(sLastDispEnv_C2D060));
    if (sPsxVram_C1D160.field_4_pLockedPixels)
    {
        BMP_unlock_4F2100(&sPsxVram_C1D160);
    }

    if (!byte_BD0F20 && byte_578324)
    {
        if (sPsxEMU_show_vram_BD1465)
        {
            // NOTE: Slight OG change - still render debug text when debug render vram is enabled
            RECT rect = {0, 0, 640, 480};
            PSX_DrawDebugTextBuffers(&sPsxVram_C1D160, rect);

            VGA_CopyToFront_4F3710(&sPsxVram_C1D160, nullptr);
            MIDI_UpdatePlayer_4FDC80();
            return;
        }

        Bitmap* pBmp = nullptr;
        RECT rect = {};
        if (bDontUseXYOffsetInRender_BD1464)
        {
            rect.top = 0;
            rect.left = 0;
            rect.right = sLastDispEnv_C2D060.disp.w;
            rect.bottom = sLastDispEnv_C2D060.disp.h;
            pBmp = &stru_C1D1A0;
        }
        else
        {
            rect.left = sLastDispEnv_C2D060.disp.x;
            rect.top = sLastDispEnv_C2D060.disp.y;
            rect.right = sLastDispEnv_C2D060.disp.x + sLastDispEnv_C2D060.disp.w;
            rect.bottom = sLastDispEnv_C2D060.disp.y + sLastDispEnv_C2D060.disp.h;
            pBmp = &sPsxVram_C1D160;
        }

        PSX_DrawDebugTextBuffers(pBmp, rect);

        if (a2 && VGA_IsWindowMode_4F31E0())
        {
            PSX_DispEnv_4EDAB0(pBmp, rect.left, rect.top, rect.right - rect.left);
            PSX_DispEnv_Reset_Unknown_4ED9E0();
        }
        else
        {
            VGA_CopyToFront_4F3EB0(pBmp, &rect, sScreenMode_BD146D);
        }

        // TODO: Removed dead increment here
    }
    MIDI_UpdatePlayer_4FDC80();
}

EXPORT int CC PSX_ResetGraph_4F8800(int)
{
    return 0;
}

EXPORT int CC PSX_SetVideoMode_4FA8F0()
{
    return 0;
}

EXPORT int CC PSX_SetGraphDebug_4F8A10(int)
{
    return 0;
}

EXPORT void CC PSX_PutDispEnv_4F58E0(const PSX_DISPENV* pDispEnv)
{
    if (!sPsxEmu_put_disp_env_callback_C1D184 || !sPsxEmu_put_disp_env_callback_C1D184(0))
    {
        if (!sPsxDontChangeDispEnv_BD0F21)
        {
            if (sVGA_bmp_primary_BD2A20.field_8_width != 320 || pDispEnv->disp.w != 640)
            {
                PSX_PutDispEnv_Impl_4F5640(pDispEnv, 1);
            }
            else
            {
                PSX_PutDispEnv_Impl_4F5640(pDispEnv, 0);
            }
        }

        if (sPsxEmu_put_disp_env_callback_C1D184)
        {
            sPsxEmu_put_disp_env_callback_C1D184(1);
        }
    }
}

EXPORT void CC PSX_SetDefDrawEnv_4F5AA0(PSX_DRAWENV* pDrawEnv, __int16 x, __int16 y, __int16 w, __int16 h)
{
    PSX_DRAWENV drawEnv = {};
    drawEnv.field_0_clip.x = x;
    drawEnv.field_0_clip.y = y;

    drawEnv.field_8_ofs[0] = x;
    drawEnv.field_8_ofs[1] = y;

    drawEnv.field_0_clip.w = w;
    drawEnv.field_0_clip.h = h;

    drawEnv.field_16_dtd = 1;
    drawEnv.field_17_dfe = 1;

    drawEnv.field_C_tw.x = 0;
    drawEnv.field_C_tw.y = 0;

    drawEnv.field_C_tw.w = 640;
    drawEnv.field_C_tw.h = 0;

    drawEnv.field_14_tpage = 0;

    drawEnv.field_18_isbg = 0;
    drawEnv.field_19_r0 = 0;
    drawEnv.field_1A_g0 = 0;
    drawEnv.field_1B_b0 = 0;

    if (pDrawEnv)
    {
        memcpy(pDrawEnv, &drawEnv, sizeof(PSX_DRAWENV));
    }
    else
    {
        Error_PushErrorRecord_4F2920("C:\\abe2\\code\\PSXEmu\\LIBGPU.C", 442, -1, "SetDefDrawEnv(): env == NULL");
    }
}

EXPORT void CC PSX_SetDefDispEnv_4F55A0(PSX_DISPENV* pOutEnv, __int16 x, __int16 y, __int16 w, __int16 h)
{
    if (!pOutEnv)
    {
        Error_PushErrorRecord_4F2920("C:\\abe2\\code\\PSXEmu\\LIBGPU.C", 180, -1, "SetDefDispEnv(): env == NULL");
        return;
    }

    PSX_DISPENV defEnv = {};
    defEnv.disp.x = x;
    defEnv.disp.y = y;
    defEnv.disp.h = h;
    defEnv.disp.w = w;
    defEnv.screen.w = 256;
    defEnv.screen.h = 240;
    memcpy(pOutEnv, &defEnv, sizeof(PSX_DISPENV));
}

EXPORT void CC PSX_PutDispEnv_4F5890(PSX_DISPENV* pDispEnv)
{
    auto pFn = sPsxEmu_put_disp_env_callback_C1D184;
    if (sPsxEmu_put_disp_env_callback_C1D184)
    {
        if (sPsxEmu_put_disp_env_callback_C1D184(0))
        {
            return;
        }
        pFn = sPsxEmu_put_disp_env_callback_C1D184;
    }

    if (!sPsxDontChangeDispEnv_BD0F21)
    {
        PSX_PutDispEnv_Impl_4F5640(pDispEnv, 0);
        pFn = sPsxEmu_put_disp_env_callback_C1D184;
    }

    if (pFn)
    {
        pFn(1);
    }
}

EXPORT int CC PSX_SetDispMask_4F89F0(int /*mode*/)
{
    return 0;
}

EXPORT bool CC PSX_Rect_IsInFrameBuffer_4FA050(const PSX_RECT* pRect)
{
    return 
        pRect->x >= 0 && pRect->x < sPsxVram_C1D160.field_8_width
        && pRect->y >= 0
        && pRect->y < sPsxVram_C1D160.field_C_height
        && pRect->w + pRect->x - 1 >= 0
        && pRect->w + pRect->x - 1 < sPsxVram_C1D160.field_8_width
        && pRect->h + pRect->y - 1 >= 0
        && pRect->h + pRect->y - 1 < sPsxVram_C1D160.field_C_height;
}

EXPORT int CC PSX_LoadImage_4F5FB0(const PSX_RECT* pRect, const BYTE* pData)
{
    if (!PSX_Rect_IsInFrameBuffer_4FA050(pRect))
    {
        return 0;
    }

    if (!BMP_Lock_4F1FF0(&sPsxVram_C1D160))
    {
        Error_PushErrorRecord_4F2920(
            "C:\\abe2\\code\\PSXEmu\\LIBGPU.C",
            678,
            -1,
            "LoadImage: can't lock the _psxemu_videomem");
        return 1;
    }

    // TODO: Clean up more, treat as 1024x512 16bit array
    const unsigned int bytesPerPixel = sPsxVram_C1D160.field_14_bpp / 8;
    unsigned int srcWidthInBytes = pRect->w * bytesPerPixel;
    BYTE* pDst = (BYTE *)sPsxVram_C1D160.field_4_pLockedPixels + bytesPerPixel * (pRect->x + (pRect->y * sPsxVram_C1D160.field_8_width));
    const BYTE* pDataEnd = &pData[srcWidthInBytes * pRect->h];
    const BYTE* pDataIter = pData;

    while (pDataIter < pDataEnd)
    {
        memcpy(pDst, pDataIter, srcWidthInBytes);
        pDataIter += srcWidthInBytes;
        pDst += (sPsxVram_C1D160.field_8_width * bytesPerPixel);
    }

    BMP_unlock_4F2100(&sPsxVram_C1D160);
    return 1;

    // Note: Removed width == 32 optimization case.
}

EXPORT signed int CC PSX_StoreImage_4F5E90(const PSX_RECT* rect, WORD* pData)
{
    if (!PSX_Rect_IsInFrameBuffer_4FA050(rect))
    {
        return 0;
    }

    if (!BMP_Lock_4F1FF0(&sPsxVram_C1D160))
    {
        Error_PushErrorRecord_4F2920(
            "C:\\abe2\\code\\PSXEmu\\LIBGPU.C",
            628,
            -1,
            "StoreImage: can't lock the _psxemu_videomem"); // OG bug, name is wrong
        return 1;
    }

    WORD* pDstIter = pData;

    // TODO: Refactor
    const WORD* pVramIter = (const WORD *)((char *)sPsxVram_C1D160.field_4_pLockedPixels + 2 * (rect->x + (rect->y << 10)));
    const WORD* pVramEnd = &pVramIter[1024 * rect->h - 1024 + rect->w];
    int lineRemainder = 1024 - rect->w;
    for (int count = 1024 - rect->w; pVramIter < pVramEnd; pVramIter += lineRemainder)
    {
        const WORD* pLineStart = &pVramIter[rect->w];
        while (pVramIter < pLineStart)
        {
            const WORD vram_pixel = *pVramIter;
            ++pVramIter;
            // Convert and store pixel value
            *(pDstIter) =
                ((unsigned int)vram_pixel >> sRedShift_C215C4) & 0x1F
                | 32 * (((unsigned int)vram_pixel >> sGreenShift_C1D180) & 0x1F
                    | 32 * (((unsigned int)vram_pixel >> sBlueShift_C19140) & 0x1F
                        | 32 * ((unsigned int)vram_pixel >> sSemiTransShift_C215C0)));

            ++pDstIter;
            lineRemainder = count;
        }
    }
    BMP_unlock_4F2100(&sPsxVram_C1D160);
    return 1;
}

EXPORT int CC PSX_LoadImage16_4F5E20(const PSX_RECT* pRect, const BYTE* pData)
{
    const unsigned int pixelCount = pRect->w * pRect->h;
    WORD* pConversionBuffer = reinterpret_cast<WORD*>(malloc_4F4E60(pixelCount * (sPsxVram_C1D160.field_14_bpp / 8)));
    if (!pConversionBuffer)
    {
        Error_PushErrorRecord_4F2920("C:\\abe2\\code\\PSXEmu\\LIBGPU.C", 579, 0, "LoadImage16: can't do color conversion.");
        return PSX_LoadImage_4F5FB0(pRect, pData);
    }

    PSX_Pal_Conversion_4F98D0(reinterpret_cast<const WORD*>(pData), pConversionBuffer, pixelCount);
    const auto loadImageRet = PSX_LoadImage_4F5FB0(pRect, reinterpret_cast<BYTE*>(pConversionBuffer));
    mem_free_4F4EA0(pConversionBuffer);
    return loadImageRet;
}

EXPORT void CC PSX_SetDrawEnv_Impl_4FE420(int x, int y, int w, int h, int unknown, BYTE* pBuffer)
{
    sPsx_drawenv_clipx_BDCD40 = x;
    sPsx_drawenv_clipy_BDCD44 = y;
    sPsx_drawenv_clipw_BDCD48 = w;
    sPsx_drawenv_cliph_BDCD4C = h;
    sPsx_drawenv_k500_BDCD50 = unknown;
    sPsx_drawenv_buffer_BDCD54 = pBuffer;
}

EXPORT void CC PSX_PutDrawEnv_4F5980(const PSX_DRAWENV* pDrawEnv)
{
    if (pDrawEnv)
    {
        memcpy(&sPSX_EMU_DrawEnvState_C3D080, pDrawEnv, sizeof(sPSX_EMU_DrawEnvState_C3D080));
        if (bDontUseXYOffsetInRender_BD1464)
        {
            PSX_SetDrawEnv_Impl_4FE420(
                0,
                0,
                16 * sPSX_EMU_DrawEnvState_C3D080.field_0_clip.w - 16,
                16 * sPSX_EMU_DrawEnvState_C3D080.field_0_clip.h - 16,
                sConst_1000_578E88 / 2,
                nullptr);
        }
        else
        {
            PSX_SetDrawEnv_Impl_4FE420(
                16 * sPSX_EMU_DrawEnvState_C3D080.field_0_clip.x,
                16 * sPSX_EMU_DrawEnvState_C3D080.field_0_clip.y,
                16 * (sPSX_EMU_DrawEnvState_C3D080.field_0_clip.x + sPSX_EMU_DrawEnvState_C3D080.field_0_clip.w) - 16,
                16 * (sPSX_EMU_DrawEnvState_C3D080.field_0_clip.y + sPSX_EMU_DrawEnvState_C3D080.field_0_clip.h) - 16,
                sConst_1000_578E88 / 2,
                nullptr);
        }
    }
    else
    {
        Error_PushErrorRecord_4F2920("C:\\abe2\\code\\PSXEmu\\LIBGPU.C", 371, -1, "PutDrawEnv(): env == NULL");
    }
}

EXPORT signed int CC PSX_MoveImage_4F5D50(const PSX_RECT* pRect, int xpos, int ypos)
{
    if (PSX_Rect_IsInFrameBuffer_4FA050(pRect))
    {
        RECT rect = {};
        rect.left = pRect->x;
        rect.top = pRect->y;
        rect.right = pRect->x + pRect->w;
        rect.bottom = pRect->y + pRect->h;
        BMP_Blt_4F1E50(&sPsxVram_C1D160, xpos, ypos, &sPsxVram_C1D160, &rect, 0);
        return 0;
    }

    Error_DisplayMessageBox_4F2C80("C:\\abe2\\code\\PSXEmu\\LIBGPU.C", 531, "MoveImage: BAD SRC RECT !!!");
    return -1;
}

EXPORT void CC PSX_CD_Normalize_FileName_4FAD90(char* pNormalized, const char* pFileName)
{
    const char *fileNameIter = pFileName;
    char* pNormalizedIter = pNormalized;
    while (*fileNameIter)
    {
        if (*fileNameIter == ';')
        {
            break;
        }

        *pNormalizedIter = static_cast<char>(tolower(*fileNameIter));

        ++fileNameIter;
        ++pNormalizedIter;
    } 
    *pNormalizedIter = 0;
}

BOOL CC PSX_Rects_overlap_no_adjustment(const PSX_RECT* pRect1, const PSX_RECT* pRect2)
{
    return (pRect1->x < pRect2->w && pRect1->w > pRect2->x &&
            pRect1->y < pRect2->h && pRect1->h > pRect2->y);
}

EXPORT BOOL CC PSX_Rects_overlap_4FA0B0(const PSX_RECT* pRect1, const PSX_RECT* pRect2)
{
    return pRect1->x < (pRect2->x + pRect2->w) 
        && pRect1->y < (pRect2->y + pRect2->h) 
        && pRect2->x < (pRect1->x + pRect1->w) 
        && pRect2->y < (pRect1->y + pRect1->h);
}

ALIVE_VAR(1, 0xbbb9c4, int, sDispEnv_mode_BBB9C4, 0);

EXPORT void CC PSX_DispEnv_Set_4ED960(int mode)
{
    sDispEnv_mode_BBB9C4 = mode;
}

EXPORT void CC sub_4945B0()
{
    byte_BD0F20 = 1;
}

// If mode is 1, game doesn't frame cap at all. If it is greater than 1, then it caps to (60 / mode) fps.
EXPORT int CC PSX_VSync_4F6170(int mode)
{
    sVSync_Unused_578325 = 0;
    MIDI_UpdatePlayer_4FDC80();

    const int currentTime = SYS_GetTicks();

    if (!sVSyncLastMillisecond_BD0F2C)
    {
        sVSyncLastMillisecond_BD0F2C = currentTime;
    }

    if (mode == 1) // Ignore Frame cap
    {
        sVSync_Unused_578325 = 1;
        const int v3 = (signed int)((unsigned __int64)(1172812403ULL * (signed int)(240 * (currentTime - sVSyncLastMillisecond_BD0F2C))) >> 32) >> 14;
        return (v3 >> 31) + v3;
    }
    else if (mode < 0) // Nope.
    {
        sVSync_Unused_578325 = 1;
        Error_PushErrorRecord_4F2920("C:\\abe2\\code\\PSXEmu\\LIBGPU.C", 756, -1, "VSync(): negative param unsupported");
        return 0;
    }
    else
    {
        int frameTimeInMilliseconds = currentTime - sVSyncLastMillisecond_BD0F2C;
        if (mode > 0 && frameTimeInMilliseconds < 1000 * mode / 60)
        {
            int timeSinceLastFrame = 0;
            sVSync_Unused_578325 = 1;

            do
            {
                timeSinceLastFrame = SYS_GetTicks() - sVSyncLastMillisecond_BD0F2C;
                MIDI_UpdatePlayer_4FDC80();
            } while (timeSinceLastFrame < 1000 * mode / 60);

            frameTimeInMilliseconds = 1000 * mode / 60;
        }

        sVSyncLastMillisecond_BD0F2C += frameTimeInMilliseconds;
        sLastFrameTimestampMilliseconds_BD0F24 = currentTime + frameTimeInMilliseconds;

        return 240 * frameTimeInMilliseconds / 60000;
    }
}

EXPORT int CC PSX_DrawSync_4F6280(int /*mode*/)
{
    return 0;
}

namespace Test
{
    static void Test_PSX_ClearOTag_4F6290()
    {
        int* ot[5] = {};
        PSX_ClearOTag_4F6290(ot, 5);
        ASSERT_EQ(ot[0], (int*)&ot[1]);
        ASSERT_EQ(ot[4], (int*)0xFFFFFFFF);
    }

    void PsxTests()
    {
        Test_PSX_ClearOTag_4F6290();
    }
}
