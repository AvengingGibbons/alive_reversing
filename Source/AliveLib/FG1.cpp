#include "stdafx.h"
#include "FG1.hpp"
#include "Function.hpp"
#include "stdlib.hpp"
#include "ResourceManager.hpp"
#include "Map.hpp"
#include "ScreenManager.hpp"
#include "PsxDisplay.hpp"

ALIVE_VAR(1, 0x5D1E28, DynamicArrayT<FG1>*, gFG1List_5D1E28, nullptr);

const static __int16 sFg1_layer_to_bits_layer_5469BC[6] = { 4, 18, 23, 37, 0, 0 };

enum eChunkTypes
{
    ePartialChunk = 0,
    eFullChunk = 0xFFFE,
    eEndCompressedData = 0xFFFC,
    eStartCompressedData = 0xFFFD,
    eEndChunk = 0xFFFF
};

struct Fg1Chunk
{
    unsigned __int16 field_0_type;
    unsigned __int16 field_2_layer;
    __int16 field_4_xpos;
    __int16 field_6_ypos;
    unsigned __int16 field_8_width;
    unsigned __int16 field_A_height;
};
ALIVE_ASSERT_SIZEOF(Fg1Chunk, 0xC);

struct FG1ResourceBlockHeader
{
    DWORD mCount;
    Fg1Chunk mChunks;
};

FG1* FG1::ctor_499FC0(BYTE** pFG1Res)
{
    BaseGameObject_ctor_4DBFA0(1, 0);

    SetVTable(this, 0x5469C8); // vTbl_FG1_5469C8

    field_6_flags.Set(BaseGameObject::eUpdateDuringCamSwap);
    field_6_flags.Set(BaseGameObject::eSurviveDeathReset);
    field_6_flags.Set(BaseGameObject::eDrawable);

    field_4_typeId = Types::eFG1_101;

    field_24_level_id = gMap_5C3030.sCurrentLevelId_5C3030;
    field_26_path_id = gMap_5C3030.sCurrentPathId_5C3032;

    gFG1List_5D1E28->Push_Back(this);
    
    // Cast to the actual FG1 resource block format
    FG1ResourceBlockHeader* pHeader = reinterpret_cast<FG1ResourceBlockHeader*>(*pFG1Res);

    // So we can extract out the count of chunks and allocate a resource for it
    field_20 = 0;
    field_28_render_block_count = static_cast<short>(pHeader->mCount);
    field_2C_ptr = ResourceManager::Allocate_New_Locked_Resource_49BF40(ResourceManager::Resource_CHNK, 0, pHeader->mCount * sizeof(Fg1Block));
    field_30_chnk_res = reinterpret_cast<Fg1Block*>(*field_2C_ptr);
    
    // And take a pointer to the first chunk to iterate them
    Fg1Chunk* pChunkIter = &pHeader->mChunks;
    int render_block_idx = 0;
    for (;;) // Exit when we hit the end chunk
    {
        switch (pChunkIter->field_0_type)
        {
        case ePartialChunk:
        {
            // Convert the raw FG1 data from disk to internal render format
            Fg1Block* pRenderBlock = &field_30_chnk_res[render_block_idx++];
            Convert_Chunk_To_Render_Block_49A210(pChunkIter, pRenderBlock);

            // Skip to the next block - a bit more tricky as we must skip the bit field array thats used for the transparent pixels
            BYTE* pNextChunk = reinterpret_cast<BYTE*>(pChunkIter) + ((pChunkIter->field_A_height * sizeof(DWORD)) + sizeof(Fg1Chunk));
            pChunkIter = reinterpret_cast<Fg1Chunk*>(pNextChunk);
        }
        break;

        case eFullChunk:
        {
            // Redraw a full solid block of the background "on top"
            pScreenManager_5BB5F4->InvalidateRect_40EC50(
                pChunkIter->field_4_xpos,
                pChunkIter->field_6_ypos,
                pChunkIter->field_8_width + pChunkIter->field_4_xpos - 1,
                pChunkIter->field_A_height + pChunkIter->field_6_ypos - 1,
                pChunkIter->field_2_layer);

            // Move to the next FG1 data from disk
            pChunkIter++;
        }
        break;

        case eStartCompressedData:
        {
            ALIVE_FATAL("eStartCompressedData is not in any AE data, impossible!");
        }
        break;

        case eEndCompressedData:
        {
            ALIVE_FATAL("eEndCompressedData is not in any AE data, impossible!");
        }
        break;

        case eEndChunk:
        {
            return this;
        }

        default:
            ALIVE_FATAL("Unknown FG1 block type");
        }
    }
}

BaseGameObject* FG1::VDestructor(signed int flags)
{
    return vdtor_49A1E0(flags);
}

BaseGameObject* FG1::vdtor_49A1E0(signed int flags)
{
    dtor_49A540();
    if (flags & 1)
    {
        Mem_Free_495540(this);
    }
    return this;
}

void FG1::dtor_49A540()
{
    SetVTable(this, 0x5469C8); // vTbl_FG1_5469C8
    gFG1List_5D1E28->Remove_Item(this);
    ResourceManager::FreeResource_49C330(field_2C_ptr);
    BaseGameObject_dtor_4DBEC0();
}

__int16 FG1::Convert_Chunk_To_Render_Block_49A210(const Fg1Chunk* pChunk, Fg1Block* pBlock)
{
    // Map the layer from FG1 internal to OT layer
    pBlock->field_66_mapped_layer = sFg1_layer_to_bits_layer_5469BC[pChunk->field_2_layer];

    // Copy in the bits that represent the see through pixels
    memcpy(pBlock->field_68_array_of_height, &pChunk[1], pChunk->field_A_height * sizeof(DWORD));

    for (Poly_FT4& rPoly : pBlock->field_0_polys)
    {
        rPoly = {};

        PolyFT4_Init_4F8870(&rPoly);

        Poly_Set_SemiTrans_4F8A60(&rPoly.mBase.header, FALSE);
        Poly_Set_Blending_4F8A20(&rPoly.mBase.header, TRUE);

        SetTPage(&rPoly, static_cast<WORD>(PSX_getTPage_4F60E0(2, 0, 0, 0)));

        SetXYWH(&rPoly, pChunk->field_4_xpos, pChunk->field_6_ypos, pChunk->field_8_width, pChunk->field_A_height);

        SetPrimExtraPointerHack(&rPoly, pBlock->field_68_array_of_height);
    }
    return 1;
}

void FG1::VRender(int** pOrderingTable)
{
    vRender_49A3C0(pOrderingTable);
}

void FG1::vRender_49A3C0(int** pOt)
{
    for (int i = 0; i < field_28_render_block_count; i++)
    {
        Poly_FT4* pPoly = &field_30_chnk_res[i].field_0_polys[gPsxDisplay_5C1130.field_C_buffer_index];
        const int xpos = X0(pPoly);
        const int ypos = Y0(pPoly);
        if (pScreenManager_5BB5F4->IsDirty_40EBC0(pScreenManager_5BB5F4->field_3A_idx, xpos, ypos) || pScreenManager_5BB5F4->IsDirty_40EBC0(3, xpos, ypos))
        {
            OrderingTable_Add_4F8AA0(&pOt[field_30_chnk_res[i].field_66_mapped_layer], &pPoly->mBase.header);
            // NOTE: Polygon has a pointer to the bit fields for which pixels should be skipped
            pScreenManager_5BB5F4->InvalidateRect_40EC90(xpos, ypos, X3(pPoly), Y3(pPoly), pScreenManager_5BB5F4->field_3A_idx);
        }
    }
}

void FG1::VScreenChanged()
{
    vScreenChanged_49A520();
}

void FG1::vScreenChanged_49A520()
{
    field_6_flags.Set(BaseGameObject::eDead);
}
