//
// Created by Tomas on 16.3.2021.
//
#include "Headers/Board.h"

void Board::printBitBoard(u64 bitboard) {
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
// numbers make up a board filled with ones except one file
const u64 not_a_file = 18374403900871474942ULL;
const u64 not_h_file = 9187201950435737471ULL;

u64 Board::generatePawnAttacks(int color, int square) {
    // init empty boards
    u64 attacks = 0ULL;
    u64 bitboard = 0ULL;

    // set piece on the board
    setBit(bitboard, square);

    // white pawns
    if (!color)
    {
        if ((bitboard >> 7) & not_a_file) attacks |= (bitboard >> 7);
        if ((bitboard >> 9) & not_h_file) attacks |= (bitboard >> 9);
    }
    else
    {
        if ((bitboard << 7) & not_h_file) attacks |= (bitboard << 7);
        if ((bitboard << 9) & not_a_file) attacks |= (bitboard << 9);
    }
    return attacks;
}
void Board::initPawnAttacks()
{
    // loop over 64 board squares
    for (int square = 0; square < 64; square++)
    {
        // init pawn attacks
        _pawnAttacks[white][square] = generatePawnAttacks(white, square);
        _pawnAttacks[black][square] = generatePawnAttacks(black, square);
    }
}

u64 Board::getPawnAttack(int color, int square) {
    return _pawnAttacks[color][square];
}
