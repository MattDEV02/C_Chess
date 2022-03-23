#ifndef __CHESSBOARD_H_
#define __CHESSBOARD_H_


void defineChessBoardMatrix(wchar_t** chessBoard);

/* 
    SPECIFICS:
        * Description: function that, given as input a (8 * 8) wchar_t matrix and 2 points (coordinates of start and finish), allows one of the two players in the chess game to take his turns.
        * Input: a (8 * 8) wchar_t matrix, the memory address of a Point (row, col), and the memory addresses of 2 boolean flags.
        * Pre-condition: chessBoard must is a wchar_t (8 * 8) matrix, Point row and Point col between 0 and 7 (integers).
        * Output: a boolean value named "hasWin".
        * Post-condition: hasWin holds true if a player eats the opponent's queen.
*/
bool playerTurn(wchar_t** chessBoard, Point* p1, bool* isBlackCastlingPossible, bool* isWhiteCastlingPossible);


#endif