//
//  main.cpp
//  Homework 3
//
//  Created by Jason Ghiglieri with emotional support from Evan Derby on 1/28/18.
//  Copyright © 2018 Jason Ghiglieri. All rights reserved.
//

#include <iostream>
#include "surfaceExtraction.hpp"
#include "VoxelModelc.hpp"


int main(int argc, const char * argv[])
{
    uint64_t model = emptyModel();
    for (int i = 0; i < 64; i+=5)
    {
        model = toggleBit(model, getX(i), getY(i), getZ(i));
    }
    
    
    writeSTL(model, "file.stl");
}
