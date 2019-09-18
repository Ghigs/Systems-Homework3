//
//  VoxelModelc.hpp
//  Homework 2
//
//  Created by Jason Ghiglieri with support from Kyle Thomas, Oswaldo Menchaca, and Evan Derby on 1/17/18.
//  Copyright © 2018 Jason Ghiglieri. All rights reserved.
//

#ifndef VoxelModelc_hpp
#define VoxelModelc_hpp

#include <stdio.h>
#include <cstdint>


u_int8_t getIndex(int x, int y, int z);


u_int8_t getX(u_int8_t index);
u_int8_t getY(u_int8_t index);
u_int8_t getZ(u_int8_t index);


u_int64_t emptyModel();
u_int64_t fullModel();
bool getBit(u_int64_t model, int x, int y, int z);
u_int64_t setBit(u_int64_t model, int x, int y, int z);
u_int64_t clearBit(u_int64_t model, int x, int y, int z);
u_int64_t toggleBit(u_int64_t model, int x, int y, int z);

#endif /* VoxelModelc_hpp */
