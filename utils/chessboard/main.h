#ifndef __CHESSBOARD_H_
#define __CHESSBOARD_H_


#include "../stdutils/main.h"
#include "../positions/main.h"
#include "../icons/main.h"
#include "../movements/main.h"


void defineChessBoardMatrix(ChessBoard chessBoard);

ChessBoard chessBoardCalloc();

void chessBoardDealloc(ChessBoard chessBoard);

/* 
    SPECIFICS:
        * Description: function that, given as input a (8 * 8) wchar_t matrix a point (coordinates of start and finish), allows one of the two players in the chess game to take his turns.
        * Input: a (8 * 8) wchar_t matrix reference, a Point (row, col) reference.
        * Pre-condition: chessBoard must is a wchar_t (8 * 8) matrix reference, Point row and Point col between 0 and 7 (integers).
        * Output: a boolean value named "hasWin".
        * Post-condition: hasWin holds true if a player eats the opponent's queen.
*/
bool playerTurn(ChessBoard chessBoard, Point* p1);


#endif