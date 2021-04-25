//
// Created by Tomas on 16.3.2021.
//
#pragma once
#include <iostream>
#include "Enums.h"
#include "Namespaces/Attacks.cpp"

class Board {
public:
    void initAttacks();                                         // Fills appropriate attack tables
    void printBitBoard(U64);                                    // Print bitboard

private:
    U64 _bitBoards[12];                                         // Stores bitboards for every peace for both colors
    U64 _pawnAttacks[2][64];                                    // Stores all possible pawn attacks except french word
    U64 _knightAttacks[64];                                     // Stores all possible knight attacks
    U64 _kingAttacks[64];                                       // Stores all possible king attacks
    U64 _bishopAttacks[64];                                     // Stores all possible bishop attacks
    U64 _rookAttacks[64];                                       // Stores all possible rook attacks
};
