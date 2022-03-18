#ifndef POSITIONS_H


bool isBlackPosition(short row);

bool isPawnPosition(short row);

bool isHorsePosition(short row, short col);

bool isBishopPosition(short row, short col);

bool isTowerPosition(short row, short col);

bool isKingPosition(short row, short col);

bool isQueenPosition(short row, short col);

bool isEmptyPosition(short row);

bool isEmptySquarePosition(short row, short col);

bool isFreePosition(wchar_t icon);


#endif