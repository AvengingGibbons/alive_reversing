#pragma once

#include "FunctionFwd.hpp"

// TODO: Can be made into a template when all usages are reversed.
void DynamicArray_ForceLink();

class DynamicArray
{
public:
    EXPORT DynamicArray* ctor_40CA60(__int16 startingSize);
    EXPORT DynamicArray* ctor_40C9E0(__int16 startingSize);
    EXPORT void dtor_40CAD0();

    EXPORT __int16 Expand_40CBE0(__int16 expandSize);
    bool IsEmpty() const { return field_4_used_size == 0; }
    __int16 Size() const { return field_4_used_size; }
public:
    EXPORT __int16 Push_Back_40CAF0(void* pValue);
protected:
    EXPORT __int16 Remove_Item_40CB60(void* pItemToRemove);
    void** field_0_array;
public:
    __int16 field_4_used_size;
private:
    __int16 field_6_max_size;
    __int16 field_8_expand_size;
    // padding

    friend class DynamicArrayIter;
};
ALIVE_ASSERT_SIZEOF(DynamicArray, 0xC);

// Typed wrapper for DynamicArray
template<class T>
class DynamicArrayT : public DynamicArray
{
public:
    __int16 Push_Back(T* pValue)
    {
        return Push_Back_40CAF0(pValue);
    }

    __int16 Remove_Item(T* pItemToRemove)
    {
        return Remove_Item_40CB60(pItemToRemove);
    }

    T* ItemAt(int idx)
    {
        return reinterpret_cast<T*>(field_0_array[idx]);
    }

    void SetAt(int idx, T* itemToSet)
    {
        field_0_array[idx] = itemToSet;
    }
};

class DynamicArrayIter
{
public:
    EXPORT void Remove_At_Iter_40CCA0();

    DynamicArray* field_0_pDynamicArray;
    __int16 field_4_idx;
    // padding
};
ALIVE_ASSERT_SIZEOF(DynamicArrayIter, 0x8);
