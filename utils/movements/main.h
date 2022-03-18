#ifndef POSITIONS_H


bool isBlackPawnDiaogonalMovement(wchar_t chessBoard[N][N], short row1, short col1, short row2, short col2);

bool isWhitePawnDiaogonalMovement(wchar_t chessBoard[N][N], short row1, short col1, short row2, short col2);

bool isHorseMovement(short row1, short col1, short row2, short col2);

bool isBishopMovement(short row1, short col1, short row2, short col2);

bool isTowerMovement(short row1, short col1, short row2, short col2);

bool isKingMovement(short row1, short col1, short row2, short col2);

bool isQueenMovement(short row1, short col1, short row2, short col2);

bool move(wchar_t chessBoard[N][N], short row1, short col1, short row2, short col2);


#endif