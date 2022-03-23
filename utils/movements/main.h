#ifndef __MOVEMENTS_H_
#define __MOVEMENTS_H_


bool isBlackPawnDiaogonalMovement(ChessBoard chessBoard, Point* p1, Point* p2);

bool isWhitePawnDiaogonalMovement(ChessBoard chessBoard, Point* p1, Point* p2);

bool isHorseMovement(Point* p1, Point* p2);

bool isBishopMovement(Point* p1, Point* p2);

bool isTowerMovement(Point* p1, Point* p2);

bool isKingMovement(Point* p1, Point* p2);

bool isQueenMovement(Point* p1, Point* p2);

bool move(ChessBoard chessBoard, Point* p1, Point* p2);

bool isCastlingMovement(ChessBoard chessBoard, Point* p1, Point* p2);

void castling(ChessBoard chessBoard, Point* p1, Point* p2);


#endif