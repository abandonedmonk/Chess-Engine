// System Headers
#include <stdio.h>

// define bitboard datatypes
#define U64 unsigned long long

/***************************************\
=========================================
            Bit Manipulation
=========================================
\***************************************/

// set/get/pop macros
#define get_bit(bb, sq) (bb & (1ULL << sq))

// print bitboard
void print_bitboard(U64 bitboard)
{
    // loop over board ranks
    for (int rank = 0; rank < 8; rank++)
    {
        // loop over board files
        for (int file = 0; file < 8; file++)
        {
            // convert file and rank into square index
            int square = rank * 8 + file;

            // To show the presence of a piece, we print 1 else 0
            printf("%d ", get_bit(bitboard, square) ? 1 : 0);
        }

        // print new line every rank
        printf("\n");
    }
}

/***************************************\
=========================================
            Main Function
=========================================
\***************************************/
int main()
{
    U64 bitboard = 0ULL;
    print_bitboard(bitboard);
    return 0;
}