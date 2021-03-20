//
// Created by Tomas on 16.3.2021.
//
#include "Headers/Board.h"

int main()
{
    Board test;

    test.initPawnAttacks();

    // loop over 64 board squares
    for (int square = 0; square < 64; square++)
        test.printBitBoard(test.getPawnAttack(black, square));
    return 0;
}
