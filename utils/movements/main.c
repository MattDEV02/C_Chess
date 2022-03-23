#include "../stdutils/main.h"
#include "../positions/main.h"
#include "../icons/main.h"
#include "main.h"


bool isBlackPawnDiaogonalMovement(wchar_t** chessBoard, Point* p1, Point* p2) {
    return !isFreePosition(chessBoard[p2->row][p2->col]) && (p1->row + p1->col - 2 == p2->row + p2->col || p1->row + p1->col == p2->row + p2->col) && (p1->row != p2->row && p1->col != p2->col);
}

bool isWhitePawnDiaogonalMovement(wchar_t** chessBoard, Point* p1, Point* p2) {
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

bool move(wchar_t** chessBoard, Point* p1, Point* p2) {
    const wchar_t 
		icon1 = chessBoard[p1->row][p1->col],	
		icon2 = chessBoard[p2->row][p2->col];
    if(!isFreePosition(icon2)) {
        wprintf(L"\nHai mangiato un %lc  %ls/a dell'avversario ! ; ", icon2, isBlack(chessBoard[p2->row][p2->col]) ? L"nero" : L"bianco");
        printIconStringName(icon2);
    }
    chessBoard[p2->row][p2->col] = icon1;
    defineSquare(chessBoard, p1);
	if(isPawn(icon1)) {
		if(isBlack(icon1) && p2->row == 0) 
			pawnTransition(chessBoard, p2, true);
		else if(!isBlack(icon1) && p2->row == N - 1) 
			pawnTransition(chessBoard, p2, false);
	}
    return isQueen(icon2);
}

bool isCastlingMovement(wchar_t** chessBoard, Point* p1, Point* p2) {
	return 
		isQueen(chessBoard[p1->row][p1->col]) &&
		(p1->row == p2->row && (p1->row == 0 || p1->row == 7)) &&
		(p1->col == 4 && p2->col == 6) &&
		isFreePosition(chessBoard[p1->row][p1->col + 1]) &&
		isFreePosition(chessBoard[p2->row][p2->col]) &&
		isTower(chessBoard[p2->row][p2->col + 1]) &&
		isEqualColor(chessBoard[p1->row][p1->col], chessBoard[p2->row][p2->col + 1]);
}

void castling(wchar_t** chessBoard, Point* p1, Point* p2) {
	Point towerPoint;
	towerPoint.row = p1->row;
	towerPoint.col = p2->col + 1;
	const wchar_t 
		queen = chessBoard[p1->row][p1->col],
		tower = chessBoard[p2->row][p2->col + 1];
	chessBoard[p2->row][p2->col] = queen;
	chessBoard[p1->row][p1->col + 1] = tower;
	defineSquare(chessBoard, &(towerPoint));
}