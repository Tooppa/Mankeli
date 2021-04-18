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

int Board::count_bits(U64 bitboard)
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

int Board::get1BitIndex(U64 bitboard)
{
    // make sure bitboard is not 0
    if (bitboard)
        return count_bits((bitboard & -bitboard) - 1);
    else return -1;
}

U64 Board::generateBoardWithOneFile(int file) {
    U64 bitboard = 0ULL;
    for (int i = 0; i < 8; ++i) {
        int square = i * 8 + file;
        setBit(bitboard, square);
    }
    return bitboard;
}

U64 Board::generatePawnAttacks(int color, int square) {
    // init empty boards
    U64 attacks = 0ULL;
    U64 bitboard = 0ULL;

    // bitboard where one line is filled with ones
    U64 aFile = generateBoardWithOneFile(A);
    U64 hFile = generateBoardWithOneFile(H);

    // set piece on the board
    setBit(bitboard, square);

    // white pawns
    if (!color)
    {
        if ((bitboard >> 7) & ~aFile)
            attacks |= (bitboard >> 7);
        if ((bitboard >> 9) & ~hFile)
            attacks |= (bitboard >> 9);
    }
    else
    {
        if ((bitboard << 7) & ~hFile)
            attacks |= (bitboard << 7);
        if ((bitboard << 9) & ~aFile)
            attacks |= (bitboard << 9);
    }
    return attacks;
}

U64 Board::generateKnightAttacks( int square) {
    // init empty boards
    U64 attacks = 0ULL;
    U64 bitboard = 0ULL;

    // bitboard where one or more lines are filled with ones
    U64 aFile = generateBoardWithOneFile(A);
    U64 hFile = generateBoardWithOneFile(H);
    U64 abFile = generateBoardWithOneFile(A) | generateBoardWithOneFile(B);
    U64 hgFile = generateBoardWithOneFile(H) | generateBoardWithOneFile(G);

    // set piece on the board
    setBit(bitboard, square);

    // generate knight attacks
    if ((bitboard >> 17) & ~hFile)
        attacks |= (bitboard >> 17);
    if ((bitboard >> 15) & ~aFile)
        attacks |= (bitboard >> 15);
    if ((bitboard >> 10) & ~hgFile)
        attacks |= (bitboard >> 10);
    if ((bitboard >> 6) & ~abFile)
        attacks |= (bitboard >> 6);
    if ((bitboard << 17) & ~aFile)
        attacks |= (bitboard << 17);
    if ((bitboard << 15) & ~hFile)
        attacks |= (bitboard << 15);
    if ((bitboard << 10) & ~abFile)
        attacks |= (bitboard << 10);
    if ((bitboard << 6) & ~hgFile)
        attacks |= (bitboard << 6);

    return attacks;
}

U64 Board::generateKingAttacks(int square) {
    // init empty boards
    U64 attacks = 0ULL;
    U64 bitboard = 0ULL;

    // bitboard where one or more lines are filled with ones
    U64 aFile = generateBoardWithOneFile(A);
    U64 hFile = generateBoardWithOneFile(H);

    // set piece on the board
    setBit(bitboard, square);

    // generate king attacks
    if (bitboard >> 8)
        attacks |= (bitboard >> 8);
    if ((bitboard >> 9) & ~hFile)
        attacks |= (bitboard >> 9);
    if ((bitboard >> 7) & ~aFile)
        attacks |= (bitboard >> 7);
    if ((bitboard >> 1) & ~hFile)
        attacks |= (bitboard >> 1);
    if (bitboard << 8)
        attacks |= (bitboard << 8);
    if ((bitboard << 9) & ~aFile)
        attacks |= (bitboard << 9);
    if ((bitboard << 7) & ~hFile)
        attacks |= (bitboard << 7);
    if ((bitboard << 1) & ~aFile)
        attacks |= (bitboard << 1);

    return attacks;
}

U64 Board::generateBishopAttacks(int square) {
    // init empty boards
    U64 attacks = 0ULL;

    // get rank and file
    int rank = square / 8;
    int file = square % 8;

    // generate bishop attacks with out bits from the corners (2 -> 7 and b -> g)
    for (int i = rank + 1, y = file + 1; i < 7 && y < 7; i++, y++)
        attacks |= (1ULL << (i * 8 + y));
    for (int i = rank - 1, y = file + 1; i > 0 && y < 7; i--, y++)
        attacks |= (1ULL << (i * 8 + y));
    for (int i = rank + 1, y = file - 1; i < 7 && y > 0; i++, y--)
        attacks |= (1ULL << (i * 8 + y));
    for (int i = rank - 1, y = file - 1; i > 0 && y > 0; i--, y--)
        attacks |= (1ULL << (i * 8 + y));

    return attacks;
}

// generate bishop attacks with a blocker board
U64 Board::bishopAttacksWithBlocker(int square, U64 block)
{
    // result attacks bitboard
    U64 attacks = 0ULL;

    // init target rank & files
    int rank = square / 8;
    int file = square % 8;

    // generate bishop attacks
    for (int r = rank + 1, f = file + 1; r <= 7 && f <= 7; r++, f++)
    {
        attacks |= (1ULL << (r * 8 + f));
        if ((1ULL << (r * 8 + f)) & block) break;
    }
    for (int r = rank - 1, f = file + 1; r >= 0 && f <= 7; r--, f++)
    {
        attacks |= (1ULL << (r * 8 + f));
        if ((1ULL << (r * 8 + f)) & block) break;
    }
    for (int r = rank + 1, f = file - 1; r <= 7 && f >= 0; r++, f--)
    {
        attacks |= (1ULL << (r * 8 + f));
        if ((1ULL << (r * 8 + f)) & block) break;
    }
    for (int r = rank - 1, f = file - 1; r >= 0 && f >= 0; r--, f--)
    {
        attacks |= (1ULL << (r * 8 + f));
        if ((1ULL << (r * 8 + f)) & block) break;
    }

    // return attack map
    return attacks;
}

// generate rook attacks with a blocker board
U64 Board::rookAttacksWithBlocker(int square, U64 block)
{
    // result attacks bitboard
    U64 attacks = 0ULL;

    // init target rank & files
    int rank = square / 8;
    int file = square % 8;

    // generate rook attacks
    for (int r = rank + 1; r <= 7; r++)
    {
        attacks |= (1ULL << (r * 8 + file));
        if ((1ULL << (r * 8 + file)) & block) break;
    }
    for (int r = rank - 1; r >= 0; r--)
    {
        attacks |= (1ULL << (r * 8 + file));
        if ((1ULL << (r * 8 + file)) & block) break;
    }
    for (int f = file + 1; f <= 7; f++)
    {
        attacks |= (1ULL << (rank * 8 + f));
        if ((1ULL << (rank * 8 + f)) & block) break;
    }
    for (int f = file - 1; f >= 0; f--)
    {
        attacks |= (1ULL << (rank * 8 + f));
        if ((1ULL << (rank * 8 + f)) & block) break;
    }

    // return attack map
    return attacks;
}

U64 Board::generateRookAttacks(int square) {
    // init empty boards
    U64 attacks = 0ULL;

    // get rank and file
    int rank = square / 8;
    int file = square % 8;

    // generate rook attacks with out bits from the corners (2 -> 7 and b -> g)
    for (int i = rank + 1; i < 7; i++)
        attacks |= (1ULL << (i * 8 + file));
    for (int i = rank - 1; i > 0; i--)
        attacks |= (1ULL << (i * 8 + file));
    for (int i = file + 1; i < 7; i++)
        attacks |= (1ULL << (rank * 8 + i));
    for (int i = file - 1; i > 0; i--)
        attacks |= (1ULL << (rank * 8 + i));

    return attacks;
}

U64 Board::setOccupancy(int index, int bitMask, U64 attackMask)
{
    U64 occupancy = 0ULL;

    for (int count = 0; count < bitMask; count++)
    {
        // get 1 bit index of attacks mask
        int square = get1BitIndex(attackMask);
        popBit(attackMask, square);

        // check that it is iside the board
        if (index & (1 << count))
            // populate occupancy map
            occupancy |= (1ULL << square);
    }
    return occupancy;
}



void Board::initAttacks()
{
    // loop over 64 board squares
    for (int square = 0; square < 64; square++)
    {
        // init pawn attacks
        _pawnAttacks[white][square] = generatePawnAttacks(white, square);
        _pawnAttacks[black][square] = generatePawnAttacks(black, square);

        // knight attacks
        _knightAttacks[square] = generateKnightAttacks(square);

        // king attacks
        _kingAttacks[square] = generateKingAttacks(square);
    }
}