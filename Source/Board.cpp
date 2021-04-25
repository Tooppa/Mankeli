//
// Created by Tomas on 16.3.2021.
//
#include "Headers/Board.h"

void Board::printBitBoard(U64 bitboard) {
    std::cout << "\n\n";
    // ranks
    for (int i = 0; i < 8; i++) {
        // files
        for (int y = 0; y < 8; y++) {
            int square = i * 8 + y;
            // print rank number if y is zero
            if (!y)
                std::cout<< 8 - i << "  ";
            // print bits state
            std::cout << " " << getBit(bitboard, square) ? 1 : 0;
        }
        std::cout << "\n";
    }
    // print files char
    std::cout << "\n    a b c d e f g h\n\n";
}

void Board::initAttacks()
{
    // loop over 64 board squares
    for (int square = 0; square < 64; square++)
    {
        // init pawn attacks
        _pawnAttacks[white][square] = Attacks::generatePawnAttacks(white, square);
        _pawnAttacks[black][square] = Attacks::generatePawnAttacks(black, square);

        // knight attacks
        _knightAttacks[square] = Attacks::generateKnightAttacks(square);

        // king attacks
        _kingAttacks[square] = Attacks::generateKingAttacks(square);
    }
}