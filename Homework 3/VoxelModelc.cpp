//
//  VoxelModelc.cpp
//  Homework 2
//
//  Created by Jason Ghiglieri with help from Kyle Thomas, Oswaldo Menchaca, and Evan Derby on 1/17/18.
//  Copyright © 2018 Jason Ghiglieri. All rights reserved.
//

#include "VoxelModelc.hpp"
#include <cstdint>


// Method for retrieving the index of the given X, Y, Z coordinates
u_int8_t getIndex(int x, int y, int z)
{
    u_int8_t resultIndex = 0;
    
    resultIndex += (x*16);
    
    resultIndex += (y*4);
    
    resultIndex += z;
    
    return resultIndex;
}


// Method for retrieving the X value of a given index
u_int8_t getX(u_int8_t index)
{
    u_int8_t xValue = 0;
    
    xValue = index / 16;
    
    return xValue;
}


// Method for retrieving the Y value of a given index
u_int8_t getY(u_int8_t index)
{
    u_int8_t yValue = 0;
    
    int x = index / 16;
    index = index - (x*16);
    
    yValue = index / 4;
    
    return yValue;
}


// Method for retrieving the Z value of a given index
u_int8_t getZ(u_int8_t index)
{
    u_int8_t zValue;
    
    int x = index / 16;
    index = index - (x * 16);
    
    int y = index / 4;
    index  = index - (y * 4);
    
    zValue = index;
    
    return zValue;
}


// Method for producing a completely empty model, with all bits set to 0
u_int64_t emptyModel()
{
    return 0;
}


// Method for producing a completely full model, with all bits set to 1
u_int64_t fullModel()
{
    return ~0;
}



// Helper Method for creating a comparator to that avoids issues concerning 5 bit shift limit on IA-32 processors.
u_int64_t getComparator(u_int64_t index)
{
    u_int64_t comparator = 1;
    
    if (index > 31)
    {
        comparator = comparator << 32;
        comparator = comparator << (index % 32);
    }
    else
    {
        comparator = comparator << index;
    }
    return comparator;
}



// Method for checking what whether a specified bit is a 0 (false) or a 1 (true)
bool getBit(u_int64_t model, int x, int y, int z)
{
    u_int64_t copy = model;
    u_int8_t index = getIndex(x, y, z);
    
    u_int64_t comparator = getComparator(index);
    
    if ((copy ^ comparator) < model)
    {
        return true;
    }
    else
    {
        return false;
    }
}


// Method for setting a specified bit to 1
u_int64_t setBit(u_int64_t model, int x, int y, int z)
{
    u_int64_t copy = model;
    int index = getIndex(x, y, z);
    
    u_int64_t comparator = getComparator(index);
    
    u_int64_t result;
    result = (copy | comparator);
    return result;
}


// Method for setting a specified bit to 0
u_int64_t clearBit(u_int64_t model, int x, int y, int z)
{
    u_int64_t copy = model;
    int index = getIndex(x, y, z);
    
    u_int64_t comparator = getComparator(index);
    comparator = ~comparator;
    
    u_int64_t result;
    result = (copy & comparator);
    return result;
}


// Method for toggling a specified bit
u_int64_t toggleBit(u_int64_t model, int x, int y, int z)
{
    u_int64_t copy = model;
    int index = getIndex(x, y, z);
    
    u_int64_t comparator = getComparator(index);
    
    u_int64_t result;
    if ((copy ^ comparator) < model)
    {
        copy = model;
        comparator = ~comparator;
        result = (copy & comparator);
    }
    else
    {
        copy = model;
        result = (copy | comparator);
    }
    return result;
}

