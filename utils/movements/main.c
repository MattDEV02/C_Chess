#include "../stdutils/main.h"
#include "../positions/main.h"
#include "../icons/main.h"
#include "main.h"


bool isBlackPawnDiaogonalMovement(wchar_t chessBoard[N][N], Point* p1, Point* p2) {
    return !isFreePosition(chessBoard[p2->row][p2->col]) && (p1->row + p1->col - 2 == p2->row + p2->col || p1->row + p1->col == p2->row + p2->col) && (p1->row != p2->row && p1->col != p2->col);
}

bool isWhitePawnDiaogonalMovement(wchar_t chessBoard[N][N], Point* p1, Point* p2) {
    return !isFreePosition(chessBoard[p2->row][p2->col]) && (p1->row + p1->col + 2 == p2->row + p2->col || p1->row + p1->col == p2->row + p2->col) && (p1->row != p2->row && p1->col != p2->col);
}

bool isHorseMovement(Point* p1, Point* p2) {
    return 
        (p1->row == p2->row + 1 && p1->col == p2->col + 2) || 
        (p1->row == p2->row + 2 && p1->col == p2->col + 1) ||
        (p1->row == p2->row - 1 && p1->col == p2->col - 2) || 
        (p1->row == p2->row - 2 && p1->col == p2->col - 1) ||
        (p1->row == p2->row - 1 && p1->col == p2->col + 2) ||
        (p1->row == p2->row + 1 && p1->col == p2->col - 2) ||
        (p1->row == p2->row + 2 && p1->col == p2->col - 1) ||
        (p1->row == p2->row - 2 && p1->col == p2->col + 1);
};

bool isBishopMovement(Point* p1, Point* p2) {
    return ((p1->row + p1->col  - p2->row + p2->col) % 2 == 0) && (p1->row != p2->row && p1->col != p2->col);
}

bool isTowerMovement(Point* p1, Point* p2) {
    return 
        (p2->row > p1->row && p1->col == p2->col) ||
        (p1->row == p2->row && p1->col > p2->col) ||
        (p2->row < p1->row && p1->col == p2->col) ||
        (p1->row == p2->row && p1->col < p2->col);
}

bool isKingMovement(Point* p1, Point* p2) {
    return 
        isBishopMovement(p1, p2) ||
        isTowerMovement(p1, p2);
}

bool isQueenMovement(Point* p1, Point* p2) {
    return 
        (p1->row == p2->row - 1 && p1->col == p2->col) ||
        (p1->row == p2->row + 1 && p1->col == p2->col) ||
        (p1->row == p2->row && p1->col == p2->col - 1) ||
        (p1->row == p2->row && p1->col == p2->col + 1) ||
        (p1->row + p1->col - 2 == p2->row + p2->col && p1->row != p2->row && p1->col != p2->col) ||
        (p1->row + p1->col + 2 == p2->row + p2->col && p1->row != p2->row && p1->col != p2->col) ||
        (p1->row + p1->col == p2->row + p2->col && p1->row != p2->row && p1->col != p2->col);
}

bool move(wchar_t chessBoard[N][N], Point* p1, Point* p2) {
    const wchar_t temp = chessBoard[p2->row][p2->col];
    if(!isFreePosition(temp)) {
        wprintf(L"\nHai mangiato un %lc  %ls/a dell'avversario ! ; ", temp, isBlack(chessBoard[p2->row][p2->col]) ? L"nero" : L"bianco");
        printIconStringName(temp);
    }
    chessBoard[p2->row][p2->col] = chessBoard[p1->row][p1->col];
    chessBoard[p1->row][p1->col] = isEmptySquarePosition(p1) ? EMPTY_SQUARE : FILLED_SQUARE;
    return isQueen(temp);
}