//
// Created by Tomas on 16.3.2021.
//
#include "Headers/Board.h"

int main()
{
    Board test;

    test.printBitBoard(test.generateBishopAttacks(d5));
    return 0;
}
