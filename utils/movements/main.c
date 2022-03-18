#include "../stdutils/main.h"
#include "../positions/main.h"
#include "../icons/main.h"
#include "main.h"


bool isBlackPawnDiaogonalMovement(wchar_t chessBoard[N][N], short row1, short col1, short row2, short col2) {
    return !isFreePosition(chessBoard[row2][col2]) && (row1 + col1 - 2 == row2 + col2 || row1 + col1 == row2 + col2) && (row1 != row2 && col1 != col2);
}

bool isWhitePawnDiaogonalMovement(wchar_t chessBoard[N][N], short row1, short col1, short row2, short col2) {
    return !isFreePosition(chessBoard[row2][col2]) && (row1 + col1 + 2 == row2 + col2 || row1 + col1 == row2 + col2) && (row1 != row2 && col1 != col2);
}

bool isHorseMovement(short row1, short col1, short row2, short col2) {
    return 
        (row1 == row2 + 1 && col1 == col2 + 2) || 
        (row1 == row2 + 2 && col1 == col2 + 1) ||
        (row1 == row2 - 1 && col1 == col2 - 2) || 
        (row1 == row2 - 2 && col1 == col2 - 1) ||
        (row1 == row2 - 1 && col1 == col2 + 2) ||
        (row1 == row2 + 1 && col1 == col2 - 2) ||
        (row1 == row2 + 2 && col1 == col2 - 1) ||
        (row1 == row2 - 2 && col1 == col2 + 1);
};

bool isBishopMovement(short row1, short col1, short row2, short col2) {
    return ((row1 + col1  - row2 + col2) % 2 == 0) && (row1 != row2 && col1 != col2);
}

bool isTowerMovement(short row1, short col1, short row2, short col2) {
    return 
        (row2 > row1 && col1 == col2) ||
        (row1 == row2 && col1 > col2) ||
        (row2 < row1 && col1 == col2) ||
        (row1 == row2 && col1 < col2);
}

bool isKingMovement(short row1, short col1, short row2, short col2) {
    return 
        isBishopMovement(row1, col1, row2, col2) ||
        isTowerMovement(row1, col1, row2, col2);
}

bool isQueenMovement(short row1, short col1, short row2, short col2) {
    return 
        (row1 == row2 - 1 && col1 == col2) ||
        (row1 == row2 + 1 && col1 == col2) ||
        (row1 == row2 && col1 == col2 - 1) ||
        (row1 == row2 && col1 == col2 + 1) ||
        (row1 + col1 - 2 == row2 + col2 && row1 != row2 && col1 != col2) ||
        (row1 + col1 + 2 == row2 + col2 && row1 != row2 && col1 != col2) ||
        (row1 + col1 == row2 + col2 && row1 != row2 && col1 != col2);
}

bool move(wchar_t chessBoard[N][N], short row1, short col1, short row2, short col2) {
    const wchar_t temp = chessBoard[row2][col2];
    if(!isFreePosition(temp)) {
        wprintf(L"\nHai mangiato un %lc  %ls/a dell'avversario ! ; ", temp, isBlack(chessBoard[row2][col2]) ? L"nero" : L"bianco");
        printIconStringName(temp);
    }
    chessBoard[row2][col2] = chessBoard[row1][col1];
    chessBoard[row1][col1] = isEmptySquarePosition(row1, col1) ? EMPTY_SQUARE : FILLED_SQUARE;
    return isQueen(temp);
}