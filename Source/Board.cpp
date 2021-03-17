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
