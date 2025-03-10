#include "stdafx.h"
#include "VRam.hpp"
#include "Function.hpp"
#include "PsxDisplay.hpp"
#include <gmock/gmock.h>

const int kMaxAllocs = 512;

ALIVE_ARY(1, 0x5cb888, PSX_RECT, kMaxAllocs, sVramAllocations_5CB888, {});
ALIVE_VAR(1, 0x5cc888, int, sVram_Count_dword_5CC888, 0);
ALIVE_VAR(1, 0x5CC88C, WORD, word_5CC88C, 0);

EXPORT char CC Vram_calc_width_4955A0(int width, int depth)
{
    switch (depth)
    {
    case 0:
        return ((width + 7) >> 2) & 0xFE;
    case 1:
        return ((width + 3) >> 1) & 0xFE;
    case 2:
        return (width + 1) & 0xFE;
    }
    return 0;
}

EXPORT int CC Vram_Is_Area_Free_4958F0(PSX_RECT* pRect, int depth)
{
    pRect->x = 1024 - pRect->w;
    if (pRect->x < 0)
    {
        return 0;
    }

    short newX = 0;
    const int depthShift = 2 - depth;
    while (true)
    {
        if ((pRect->w << depthShift) + ((pRect->x & 63) << depthShift) > 256)
        {
            newX = pRect->x + 64 - 1;
            newX = (pRect->x + (64 - 1)) & ~(64 - 1);
            if (newX < pRect->x)
            {
                pRect->x = newX;
            }
        }
        else
        {
            if (sVram_Count_dword_5CC888 <= 0)
            {
                return 1;
            }

            int i = 0;
            while (!Vram_rects_overlap_4959E0(pRect, &sVramAllocations_5CB888[i]))
            {
                i++;
                if (i >= sVram_Count_dword_5CC888)
                {
                    return 1;
                }
            }

            newX = sVramAllocations_5CB888[i].x - pRect->w + 1;

            if (newX < pRect->x)
            {
                pRect->x = newX;
            }
        }

        if (--pRect->x < 0)
        {
            return 0;
        }
    }
}

EXPORT int CC Vram_alloc_block_4957B0(PSX_RECT* pRect, int depth)
{
    if (pRect->w > 1024 || pRect->h > 512)
    {
        return 0;
    }

    if (pRect->h * pRect->w >= 1024)
    {
        pRect->y = 512 - pRect->h;
        while (pRect->y >= 0)
        {
            // Old Code: if (static_cast<unsigned __int8>(pRect->y) + pRect->h <= 256)
            // Instead of casting to unsigned __int8 to wrap around the integer, we're
            // going to do it manually in case other platforms don't auto wrap integers on
            // cast.
            if ((pRect->y % 256) + pRect->h <= 256)
            {
                if (Vram_Is_Area_Free_4958F0(pRect, depth))
                {
                    return 1;
                }
            }
            else
            {
                // v7 &= 0xFFFFFF00; // Todo: check this. was LOBYTE(v7) = 0; Doesn't seem needed
                // to pass tests.
                const short ypos = (pRect->y + 255) - pRect->h + 1;
                if (ypos < pRect->y)
                {
                    pRect->y = ypos;
                }
            }
            --pRect->y;
        }
        return 0;
    }

    pRect->y = 0;
    if (512 - pRect->h <= 0)
    {
        return 0;
    }

    // Search Loop
    while (true)
    {
        const short yPos = pRect->y;
        if (pRect->h + yPos <= 255 || yPos >= 256)
        {
            if (!Vram_Is_Area_Free_4958F0(pRect, depth))
            {
                pRect->y++;
                if (pRect->y >= 512 - pRect->h)
                {
                    return 0;
                }

                continue;
            }
            else
            {
                return 1;
            }
        }
        pRect->y = 255;

        ++pRect->y;
        if (pRect->y >= 512 - pRect->h)
        {
            return 0;
        }
    }
    
    return 1;
}

EXPORT signed __int16 CC Vram_alloc_4956C0(unsigned __int16 width, __int16 height, unsigned __int16 colourDepth, PSX_RECT* pRect)
{
    PSX_RECT rect = {};

    const int depth = colourDepth / 8;

    rect.w = Vram_calc_width_4955A0(width, depth);
    rect.h = height;

    if (sVram_Count_dword_5CC888 >= kMaxAllocs || !Vram_alloc_block_4957B0(&rect, depth))
    {
        return 0;
    }

    sVramAllocations_5CB888[sVram_Count_dword_5CC888++] = rect;
    *pRect = rect;

    return 1;
}

EXPORT void CC Vram_init_495660()
{
    for (int i = 0; i < kMaxAllocs; i++)
    {
        sVramAllocations_5CB888[i] = {};
    }
    sbDebugFontLoaded_BB4A24 = 0;
    sVram_Count_dword_5CC888 = 0;
}

EXPORT void CC Vram_alloc_explicit_4955F0(__int16 x, __int16 y, __int16 w, __int16 h)
{
    if (sVram_Count_dword_5CC888 < kMaxAllocs)
    {
        sVramAllocations_5CB888[sVram_Count_dword_5CC888].x = x;
        sVramAllocations_5CB888[sVram_Count_dword_5CC888].y = y;
        sVramAllocations_5CB888[sVram_Count_dword_5CC888].w = w - x + 1;
        sVramAllocations_5CB888[sVram_Count_dword_5CC888].h = h - y + 1;
        sVram_Count_dword_5CC888++;
    }
}

EXPORT void CC Vram_free_495A60(PSX_Point xy, PSX_Point wh)
{
    // Find the allocation
    for (int i = 0; i < sVram_Count_dword_5CC888; i++)
    {
        if (sVramAllocations_5CB888[i].x == xy.field_0_x &&
            sVramAllocations_5CB888[i].y == xy.field_2_y &&
            sVramAllocations_5CB888[i].w == wh.field_0_x &&
            sVramAllocations_5CB888[i].h == wh.field_2_y)
        {
            // Copy the last element to this one
            sVramAllocations_5CB888[i] = sVramAllocations_5CB888[sVram_Count_dword_5CC888-1];

            // Decrement the used count
            sVram_Count_dword_5CC888--;
            return;
        }
    }
}

EXPORT BOOL CC Vram_rects_overlap_4959E0(const PSX_RECT* pRect1, const PSX_RECT* pRect2)
{
    const int x1 = pRect1->x;
    const int x2 = pRect2->x;
    if (x1 >= x2 + pRect2->w)
    {
        return 0;
    }

    const int y2 = pRect2->y;
    const int y1 = pRect1->y;
    if (y1 >= y2 + pRect2->h)
    {
        return 0;
    }

    if (x2 < x1 + pRect1->w)
    {
        return y2 < y1 + pRect1->h;
    }

    return 0;
}


ALIVE_VAR(1, 0x5c9162, __int16, pal_xpos_5C9162, 0);
ALIVE_VAR(1, 0x5c9160, __int16, pal_ypos_5C9160, 0);

ALIVE_VAR(1, 0x5c915c, __int16, pal_width_5C915C, 0);
ALIVE_VAR(1, 0x5c915e, __int16, pal_free_count_5C915E, 0);

ALIVE_ARY(1, 0x5c9164, int, 77, sPal_table_5C9164, {}); // TODO: Actually 32 in size ?

static bool Pal_Allocate_Helper(int& i, int& palX_idx, int maskValue, int numBits)
{
    for (i = 0; i < pal_free_count_5C915E; i++)
    {
        if (sPal_table_5C9164[i] != (1 << (pal_width_5C915C + 1)) - 1)
        {
            if (pal_width_5C915C != numBits)
            {
                palX_idx = 0;
                bool foundMatch = true;
                while ((maskValue << palX_idx) & sPal_table_5C9164[i])
                {
                    if (++palX_idx >= pal_width_5C915C - numBits)
                    {
                        foundMatch = false;
                        break;
                    }
                }

                if (foundMatch)
                {
                    return true;
                }
            }
        }
    }

    // Failed, out of pals
    return false;
}

EXPORT signed __int16 CC Pal_Allocate_483110(PSX_RECT* pRect, unsigned int paletteColorCount)
{
    if (!pal_free_count_5C915E)
    {
        return 0;
    }

    if (paletteColorCount != 256 && paletteColorCount != 64 && paletteColorCount != 16 )
    {
        return 0;
    }

    int pal_rect_y = 0;
    int palX_idx = 0;
    int palBitMask = 0;
    
    if (paletteColorCount == 16)
    {
        palBitMask = 1;
        if (!Pal_Allocate_Helper(pal_rect_y, palX_idx, palBitMask, 0))
        {
            return 0;
        }
    }
    else if (paletteColorCount == 64)
    {
        palBitMask = 0xF;
        if (!Pal_Allocate_Helper(pal_rect_y, palX_idx, palBitMask, paletteColorCount / 16)) // 64/16 = 4
        {
            return 0;
        }
    }
    else if (paletteColorCount == 256)
    {
        palBitMask = 0xFFFF;
        if (!Pal_Allocate_Helper(pal_rect_y, palX_idx, palBitMask, paletteColorCount / 16)) // 256/16 = 16
        {
            return 0;
        }
    }

    pRect->w = static_cast<short>(paletteColorCount);

    palBitMask = palBitMask << palX_idx;
    sPal_table_5C9164[pal_rect_y] |= palBitMask;
    pRect->x = static_cast<short>(pal_xpos_5C9162 + (16 * palX_idx));
    pRect->y = static_cast<short>(pal_rect_y + pal_ypos_5C9160);
    return 1;
}

EXPORT void CC Pal_free_483390(PSX_Point xy, __int16 palDepth)
{
    const int palIdx = xy.field_2_y - pal_ypos_5C9160;
    const int palWidthBits = xy.field_0_x - pal_xpos_5C9162;
    switch (palDepth)
    {
    case 16: // 1 bit
        sPal_table_5C9164[palIdx] ^= 1 << ((palWidthBits) / 16); // div 16 to get num bits
        break;
    case 64: // 4 bits
        sPal_table_5C9164[palIdx] ^= 0xF << ((palWidthBits) / 16);
        break;
    case 256: // 16 bits
        sPal_table_5C9164[palIdx] ^= 0xFFFF << ((palWidthBits) / 16);
        break;
    }
}

EXPORT void CC Pal_Area_Init_483080(__int16 xpos, __int16 ypos, unsigned __int16 width, unsigned __int16 height)
{
    pal_xpos_5C9162 = xpos;
    pal_ypos_5C9160 = ypos;

    pal_width_5C915C = width / 4;
    pal_free_count_5C915E = height;

    Vram_alloc_explicit_4955F0(xpos, ypos, xpos + width - 1, ypos + height - 1);
    
    for (int i = 0; i < height; i++)
    {
        sPal_table_5C9164[i] = 0;
    }
}

EXPORT void CC Pal_Copy_483560(PSX_Point pPoint, __int16 w, WORD* pPalData, PSX_RECT* rect)
{
    rect->x = pPoint.field_0_x;
    rect->y = pPoint.field_2_y;
    rect->w = w;
    rect->h = 1;
    PSX_StoreImage_4F5E90(rect, pPalData);
}

EXPORT unsigned int CC Pal_Make_Colour_4834C0(BYTE r, BYTE g, BYTE b, __int16 bOpaque)
{
    return (bOpaque != 0 ? 0x8000 : 0) + ((unsigned int)r >> 3) + 4 * ((g & 0xF8) + 32 * (b & 0xF8));
}

EXPORT void CC Pal_Set_483510(PSX_Point xy, __int16 w, const BYTE* palData, PSX_RECT* rect)
{
    rect->x = xy.field_0_x;
    rect->y = xy.field_2_y;
    rect->w = w;
    rect->h = 1;
    PSX_LoadImage16_4F5E20(rect, palData);
}

using namespace ::testing;

namespace Test
{
    void Test_VRamAllocate()
    {
        PSX_RECT rect;
        Vram_alloc_4956C0(64, 128, 8, &rect);
        ASSERT_EQ(rect.x, 992);
        ASSERT_EQ(rect.y, 384);
        ASSERT_EQ(rect.w, 32);
        ASSERT_EQ(rect.h, 128);

        PSX_RECT rect2;
        Vram_alloc_4956C0(32, 45, 16, &rect2);
        ASSERT_EQ(rect2.x, 960);
        ASSERT_EQ(rect2.y, 467);
        ASSERT_EQ(rect2.w, 32);
        ASSERT_EQ(rect2.h, 45);

        PSX_RECT rect3;
        Vram_alloc_4956C0(32, 16, 8, &rect3);

        
        ASSERT_EQ(sVram_Count_dword_5CC888, 3);
        Vram_free_495A60({ rect2.x, rect2.y }, { rect2.w, rect2.h });

        ASSERT_TRUE(memcmp(&sVramAllocations_5CB888[1], &sVramAllocations_5CB888[2], sizeof(PSX_RECT)) == 0);
        ASSERT_EQ(sVram_Count_dword_5CC888, 2);

        Vram_free_495A60({ rect.x, rect.y }, { rect.w, rect.h });
        Vram_free_495A60({ rect3.x, rect2.y }, { rect3.w, rect3.h });
    }

    void VRamTests()
    {
        Test_VRamAllocate();
    }
}
