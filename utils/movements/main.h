#ifndef __MOVEMENTS_H_
#define __MOVEMENTS_H_


bool isBlackPawnDiaogonalMovement(wchar_t chessBoard[N][N], Point* p1, Point* p2);

bool isWhitePawnDiaogonalMovement(wchar_t chessBoard[N][N], Point* p1, Point* p2);

bool isHorseMovement(Point* p1, Point* p2);

bool isBishopMovement(Point* p1, Point* p2);

bool isTowerMovement(Point* p1, Point* p2);

bool isKingMovement(Point* p1, Point* p2);

bool isQueenMovement(Point* p1, Point* p2);

bool move(wchar_t chessBoard[N][N], Point* p1, Point* p2);

bool isBlackCastling(wchar_t chessBoard[N][N], Point* p1, Point* p2);

bool isWhiteCastling(wchar_t chessBoard[N][N], Point* p1, Point* p2);

void castling(wchar_t chessBoard[N][N], Point* p1, Point* p2);


#endif