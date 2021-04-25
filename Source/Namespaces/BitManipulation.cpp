//
// Created by Tomas on 25.4.2021.
//
#include "../Headers/Enums.h"

namespace BitManipulation {

    int countBits(U64 bitboard)
    {
        // counter
        int count = 0;

        // runs until bitboard is zero
        while (bitboard)
        {
            count++;
            // reset least significant 1st bit
            bitboard &= bitboard - 1;
        }
        return count;
    }

    int get1BitIndex(U64 bitboard)
    {
        // make sure bitboard is not 0
        if (bitboard)
            return countBits((bitboard & -bitboard) - 1);
        else return -1;
    }

    U64 generateBoardWithOneFile(int file) {
        U64 bitboard = 0ULL;
        for (int i = 0; i < 8; ++i) {
            int square = i * 8 + file;
            setBit(bitboard, square);
        }
        return bitboard;
    }

    U64 setOccupancy(int index, int bitMask, U64 attackMask)
    {
        U64 occupancy = 0ULL;

        for (int count = 0; count < bitMask; count++)
        {
            // get 1 bit index of attacks mask
            int square = get1BitIndex(attackMask);
            popBit(attackMask, square);

            // check that it is inside the board
            if (index & (1 << count))
                // populate occupancy map
                occupancy |= (1ULL << square);
        }
        return occupancy;
    }
}