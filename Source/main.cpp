//
// Created by Tomas on 16.3.2021.
//
#include "Headers/Board.h"

int main()
{
    u64 bitboard = 0ULL;
    Board test;

    setBit(bitboard, e4);
    setBit(bitboard, c3);
    setBit(bitboard, f2);
    test.printBitBoard(bitboard);
    return 0;
}
