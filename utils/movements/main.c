#include "main.h"


bool isBlackPawnFrontalMovement(Point* p1, Point *p2) {
	return (
		(p2->row == p1->row - 1) && 
		(p1->col == p2->col)
	);	
}

bool isWhitePawnFrontalMovement(Point *p1, Point *p2) {
	return (
		(p2->row == p1->row + 1) && 
		(p1->col == p2->col)
	);	
}

bool isBlackPawnDualFrontalMovement(Point* p1, Point* p2) {
	return (
		(p2->row == p1->row - 1 || p2->row == p1->row - 2) && 
		(p1->col == p2->col)
	);
}

bool isWhitePawnDualFrontalMovement(Point* p1, Point* p2) {
	return (
		(p2->row == p1->row + 1 || p2->row == p1->row + 2) && 
		(p1->col == p2->col)
	);
}
	 
bool isBlackPawnDiagonalMovement(ChessBoard chessBoard, Point* p1, Point* p2) {
    return (
		!isFreePosition(chessBoard[p2->row][p2->col]) && 
		(p1->row + p1->col == p2->row + p2->col + 2 || p1->row + p1->col == p2->row + p2->col) && 
		(p1->row != p2->row && p1->col != p2->col) &&
		(p1->row > p2->row)
	);
}

bool isWhitePawnDiagonalMovement(ChessBoard chessBoard, Point* p1, Point* p2) {
    return (
		!isFreePosition(chessBoard[p2->row][p2->col]) && 
		(p1->row + p1->col == p2->row + p2->col - 2 || p1->row + p1->col == p2->row + p2->col) && 
		(p1->row != p2->row && p1->col != p2->col) &&
		(p1->row < p2->row)
	);
}

bool isHorseMovement(Point* p1, Point* p2) {
    return (
        (p1->row == p2->row + 1 && p1->col == p2->col + 2) || 
        (p1->row == p2->row + 2 && p1->col == p2->col + 1) ||
        (p1->row == p2->row - 1 && p1->col == p2->col - 2) || 
        (p1->row == p2->row - 2 && p1->col == p2->col - 1) ||
        (p1->row == p2->row - 1 && p1->col == p2->col + 2) ||
        (p1->row == p2->row + 1 && p1->col == p2->col - 2) ||
        (p1->row == p2->row + 2 && p1->col == p2->col - 1) ||
        (p1->row == p2->row - 2 && p1->col == p2->col + 1)
	);
}

bool isBishopMovement(Point* p1, Point* p2) {
    return (
		((p1->row + p1->col - p2->row + p2->col) % 2 == 0) && 
		(p1->row != p2->row && p1->col != p2->col) &&
		(sabs(p1->row - p2->row) == sabs(p1->col - p2->col)) &&
		!isHorseMovement(p1, p2)
	);
}

bool isTowerMovement(Point* p1, Point* p2) {
    return (
        (p2->row > p1->row && p1->col == p2->col) ||
        (p1->row == p2->row && p1->col > p2->col) ||
        (p2->row < p1->row && p1->col == p2->col) ||
        (p1->row == p2->row && p1->col < p2->col)
	);
}

bool isKingMovement(Point* p1, Point* p2) {
    return (
        isBishopMovement(p1, p2) ||
        isTowerMovement(p1, p2)
	);
}

bool isQueenMovement(Point* p1, Point* p2) {
    return (
        (p1->row == p2->row - 1 && p1->col == p2->col) ||
        (p1->row == p2->row + 1 && p1->col == p2->col) ||
        (p1->row == p2->row && p1->col == p2->col - 1) ||
        (p1->row == p2->row && p1->col == p2->col + 1) ||
        (p1->row + p1->col - 2 == p2->row + p2->col && p1->row != p2->row && p1->col != p2->col) ||
        (p1->row + p1->col + 2 == p2->row + p2->col && p1->row != p2->row && p1->col != p2->col) ||
        (p1->row + p1->col == p2->row + p2->col && p1->row != p2->row && p1->col != p2->col)
	);
}

bool move(ChessBoard chessBoard, Point* p1, Point* p2) {
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

bool isCastlingMovement(ChessBoard chessBoard, Point* p1, Point* p2) {
	return 
		isQueen(chessBoard[p1->row][p1->col]) &&
		(p1->row == p2->row && (p1->row == 0 || p1->row == 7)) &&
		(p1->col == 4 && p2->col == 6) &&
		isFreePosition(chessBoard[p1->row][p1->col + 1]) &&
		isFreePosition(chessBoard[p2->row][p2->col]) &&
		isTower(chessBoard[p2->row][p2->col + 1]) &&
		isEqualColor(chessBoard[p1->row][p1->col], chessBoard[p2->row][p2->col + 1]);
}

void castling(ChessBoard chessBoard, Point* p1, Point* p2) {
	Point towerPoint;
	towerPoint.row = p1->row;
	towerPoint.col = p2->col + 1;
	const wchar_t 
		queen = chessBoard[p1->row][p1->col],
		tower = chessBoard[p2->row][p2->col + 1];
	chessBoard[p2->row][p2->col] = queen;
	chessBoard[p1->row][p1->col + 1] = tower;
	defineSquare(chessBoard, p1);
	defineSquare(chessBoard, &(towerPoint));
}

bool dispPawnMovements(ChessBoard chessBoard, Point* p1, bool isWhite) {
	bool disp = false; 
	const wchar_t start = chessBoard[p1->row][p1->col];
	if(isWhite) {
		if(
			(p1->row >= (N -1) || p1->col <= 0) ||
			(!isFreePosition(chessBoard[p1->row + 1][p1->col - 1]) && !isFreePosition(chessBoard[p1->row + 1][p1->col + 2]))
		) {
			disp = (
				isEqualColor(start, chessBoard[p1->row + 1][p1->col - 1]) &&
				isEqualColor(start, chessBoard[p1->row + 1][p1->col + 2]) &&
				(!isFreePosition(chessBoard[p1->row + 1][p1->col]))
			);
		} else {
			disp = (!isFreePosition(chessBoard[p1->row + 1][p1->col]));
		}
	} else {
		if(
			(p1->row <= 0 || p1->col >= (N - 1)) ||
			(!isFreePosition(chessBoard[p1->row - 1][p1->col + 1]) && !isFreePosition(chessBoard[p1->row - 1][p1->col + 2]))
		) {
			disp = (
				isEqualColor(start, chessBoard[p1->row - 1][p1->col + 1]) &&
				isEqualColor(start, chessBoard[p1->row - 1][p1->col + 2]) &&
				(!isFreePosition(chessBoard[p1->row - 1][p1->col]))
			);
		} else {
			disp = (!isFreePosition(chessBoard[p1->row - 1][p1->col]));
		}
	}
	return disp;
}

bool dispHorseMovements(ChessBoard chessBoard, Point* p1) {
	const wchar_t start = chessBoard[p1->row][p1->col];
	return (
		(
			((p1->row <= 1) || (p1->col == 0)) || 
			(
				(!isFreePosition(chessBoard[p1->row - 2][p1->col - 1])) && 
				(isEqualColor(start, chessBoard[p1->row - 2][p1->col - 1]))
			)
		) &&
		(
			((p1->row >= (N - 2)) || (p1->col >= (N - 1))) ||
			(
				(!isFreePosition(chessBoard[p1->row + 2][p1->col + 1])) && 
				(isEqualColor(start, chessBoard[p1->row + 2][p1->col + 1]))
			)
		) &&
		(
			((p1->row >= (N - 1)) || (p1->col >= (N - 2))) ||
			(
				(!isFreePosition(chessBoard[p1->row + 1][p1->col + 2])) && 
				(isEqualColor(start, chessBoard[p1->row + 1][p1->col + 2]))
			)
		) && 
		(
			((p1->row <= 1) || (p1->col >= (N - 1))) ||
			(
				(!isFreePosition(chessBoard[p1->row - 2][p1->col + 1])) && 
				(isEqualColor(start, chessBoard[p1->row - 2][p1->col + 1]))
			) 
		) &&
		(
			((p1->row >= (N - 1)) || (p1->col >= (N - 2))) ||
			(
				(!isFreePosition(chessBoard[p1->row + 1][p1->col + 2])) && 
				(isEqualColor(start, chessBoard[p1->row + 1][p1->col + 2]))
			)
		) &&
		(
			((p1->row >= (N - 1)) || (p1->col <= 1)) ||
			(
				(!isFreePosition(chessBoard[p1->row + 1][p1->col - 2])) && 
				(isEqualColor(start, chessBoard[p1->row + 1][p1->col - 2]))
			) 
		) &&
		(
			((p1->row >= (N - 2)) || (p1->col <= 0)) ||
			(
				(!isFreePosition(chessBoard[p1->row + 2][p1->col - 1])) && 
				(isEqualColor(start, chessBoard[p1->row + 2][p1->col - 1]))
			)
		)
	);
}

bool dispBishopMovements(ChessBoard chessBoard, Point* p1) {
	const wchar_t start = chessBoard[p1->row][p1->col];
	return (
		(
			(p1->row == (N - 1) || p1->col == (N - 1)) || 
			(!isFreePosition(chessBoard[p1->row + 1][p1->col + 1]) && isEqualColor(start, chessBoard[p1->row + 1][p1->col + 1]))
		) &&
		(
			(p1->row == 0 || p1->col == 0) ||
			(!isFreePosition(chessBoard[p1->row - 1][p1->col - 1]) && isEqualColor(start, chessBoard[p1->row - 1][p1->col - 1]))
		) &&
		(
			(p1->row == (N - 1) || p1->col == 0) || 
			(!isFreePosition(chessBoard[p1->row + 1][p1->col - 1]) && isEqualColor(start, chessBoard[p1->row + 1][p1->col - 1]))
		) &&
		(
			(p1->row == 0 || p1->col == (N - 1)) ||
			(!isFreePosition(chessBoard[p1->row - 1][p1->col + 1]) && isEqualColor(start, chessBoard[p1->row - 1][p1->col + 1]))
		) 
	);
}

bool dispTowerMovements(ChessBoard chessBoard, Point* p1) {
	const wchar_t start = chessBoard[p1->row][p1->col];
	return (
		(
			(p1->row == 0) ||
			((!isFreePosition(chessBoard[p1->row - 1][p1->col])) && isEqualColor(start, chessBoard[p1->row - 1][p1->col]))
		) &&
		(
			(p1->row == (N - 1)) ||
			((!isFreePosition(chessBoard[p1->row + 1][p1->col])) && isEqualColor(start, chessBoard[p1->row + 1][p1->col]))
		) &&
		(
			(p1->col == (N - 1)) ||
			((!isFreePosition(chessBoard[p1->row][p1->col + 1])) && isEqualColor(start, chessBoard[p1->row][p1->col + 1]))
		) &&
		(
			(p1->col == 0) ||
			((!isFreePosition(chessBoard[p1->row][p1->col - 1])) && isEqualColor(start, chessBoard[p1->row][p1->col - 1]))
		)
	);
}

bool dispKingMovements(ChessBoard chessBoard, Point* p1) {
	return (
		dispTowerMovements(chessBoard, p1) &&
		dispBishopMovements(chessBoard, p1)
	);
}

bool dispQueenMovements(ChessBoard chessBoard, Point* p1) {
	return dispKingMovements(chessBoard, p1);
}