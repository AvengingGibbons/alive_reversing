#pragma once

#include "FunctionFwd.hpp"
#include "BaseGameObject.hpp"
#include "Psx.hpp"
#include "FixedPoint.hpp"
#include "Primitives.hpp"

struct Prim_Sprt;

enum class LevelIds : __int16;

#pragma pack(push)
#pragma pack(2)
class Camera // TODO: May actually just be "ResourceList" ?
{
public:
    Camera();
public:
    EXPORT void ctor_480DD0();
    EXPORT void dtor_480E00();
    EXPORT static void CC On_Loaded_480ED0(Camera* pCamera);

    DynamicArrayT<BYTE*> field_0;
    BYTE** field_C_pCamRes;
    int field_10_camera_resource_id;
    __int16 field_14_xpos;
    __int16 field_16_ypos;
    __int16 field_18_path;
    LevelIds field_1A_level;
    __int16 field_1C_camera_number;
    char field_1E_cam_name[12];
    int field_2A;
    __int16 field_2E;
    __int16 field_30_flags;
};
#pragma pack(pop)
ALIVE_ASSERT_SIZEOF(Camera, 0x32);

struct DirtyBits
{
    WORD mData[20]; // 20 Columns

    bool GetTile(int x, int y)
    {
        return mData[x] & (1 << y) ? true : false;
    }

    void SetTile(int x, int y, bool b)
    {
        if (b)
        {
            mData[x] |= 1 << y;
        }
        else
        {
            mData[x] &= ~(1 << y);
        }
    }
};

namespace Oddlib
{
    struct BitsLogic;
}

struct SprtTPage
{
    Prim_Sprt mSprt;
    Prim_SetTPage mTPage;
};

class ScreenManager : public BaseGameObject
{
public:
    // TODO
    EXPORT void sub_40EE10();

    EXPORT void MoveImage_40EB70();

    EXPORT void InvalidateRect_40EC90(int x, int y, signed int width, signed int height, int idx);
    EXPORT void InvalidateRect_40EC10(int x, int y, signed int width, signed int height);
    EXPORT void InvalidateRect_Layer3_40EDB0(int x, int y, signed int width, signed int height);
    EXPORT void InvalidateRect_40EC50(int x, int y, signed int width, signed int height, int idx);

    EXPORT __int16 IsDirty_40EBC0(int idx, int x, int y);
    EXPORT void UnsetDirtyBits_40EDE0(int idx);
    EXPORT void UnsetDirtyBits_FG1_40ED70();

    virtual BaseGameObject* VDestructor(signed int flags) override;
    virtual void VUpdate() override {}

    void process_segment(WORD* aVlcBufferPtr, int xPos);
    void vlc_decode(WORD* aCamSeg, WORD* aDst);
    void vlc_decoder(int aR, int aG, int aB, signed int aWidth, int aVramX, int aVramY);
    void write_4_pixel_block(const Oddlib::BitsLogic& aR, const Oddlib::BitsLogic& aG, const Oddlib::BitsLogic& aB, int aVramX, int aVramY);

    EXPORT void DecompressToVRam_40EF60(WORD** ppBits);

    EXPORT ScreenManager* ctor_40E3E0(BYTE** ppBits, FP_Point* pCameraOffset);
    
    EXPORT void Init_40E4B0(BYTE** ppBits);
   
    EXPORT void dtor_40E490();
    EXPORT BaseGameObject* vdtor_40E460(signed int flags);
    int next_bits();

    EXPORT static int CC GetTPage_40F040(char tp, char abr, int* xpos, int* ypos);
    
    virtual void VRender(int** pOrderingTable) override;
    EXPORT void Render_Helper_40E9F0(int xpos, int ypos, int idx, int sprite_idx, int** ot);
    EXPORT void sub_40EE50();
    EXPORT void VRender_40E6E0(int **ot);

    virtual void VScreenChanged() override;
private:
    void AddCurrentSPRT_TPage(int **ot);

public:
    FP_Point* field_20_pCamPos;
    SprtTPage* field_24_screen_sprites;
    int field_28;
    unsigned __int16 field_2C_upos;
    unsigned __int16 field_2E_vpos;
    __int16 field_30_cam_width;
    __int16 field_32_cam_height;
    int field_34;
    __int16 field_38;
    unsigned __int16 field_3A_idx;
    unsigned __int16 field_3C_y_idx;
    unsigned __int16 field_3E_x_idx;
    int field_40_flags;
    unsigned __int16 field_44;
    unsigned __int16 field_46;
    int field_48;
    int field_4C;
    int field_50;
    int field_54;
    int field_58;
    int field_5C;
    int field_60;
    DirtyBits field_64_20x16_dirty_bits[8];

    signed int g_left7_array = 0;
    int g_right25_array = 0;
    unsigned short int* g_pointer_to_vlc_buffer = nullptr;
};
//ALIVE_ASSERT_SIZEOF(ScreenManager, 0x1A4u);

ALIVE_VAR_EXTERN(ScreenManager*, pScreenManager_5BB5F4);

namespace Test
{
    void ScreenManagerTests();
}
