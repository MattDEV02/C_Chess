#ifndef __POSITIONS_H_
#define __POSITIONS_H_


#include "../stdutils/main.h"
#include "../icons/main.h"


bool isBlackPosition(short row);

bool isPawnPosition(short row);

bool isHorsePosition(Point* p);

bool isBishopPosition(Point* p);

bool isTowerPosition(Point* p);

bool isKingPosition(Point* p);

bool isQueenPosition(Point* p);

bool isEmptyPosition(short row);

bool isEmptySquarePosition(Point* p);

bool isFreePosition(wchar_t icon);

void defineSquare(ChessBoard chessBoard, Point *p);


#endif