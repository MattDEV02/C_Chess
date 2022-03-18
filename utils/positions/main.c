#include "../stdutils/main.h"
#include "../icons/main.h"
#include "main.h"


bool isBlackPosition(short row) {
    return row == 6 || row == 7;
}

bool isPawnPosition(short row) {
    return row == 1 || row == 6;
}

bool isHorsePosition(short row, short col) {
    return (row == 0 || row == 7) && (col == 1 || col == 6);
}

bool isBishopPosition(short row, short col) {
    return (row == 0 || row == 7) && (col == 2 || col == 5);
}

bool isTowerPosition(short row, short col) {
    return (row == 0 || row == 7) && (col == 0 || col == 7);
}

bool isKingPosition(short row, short col) {
    return (row == 0 || row == 7) && (col == 4);
}

bool isQueenPosition(short row, short col) {
    return (row == 0 || row == 7) && (col == 3);
}

bool isEmptyPosition(short row) {
    return row >= 2 && row <= 5;
}

bool isEmptySquarePosition(short row, short col) {
    return (row + col) % 2 == 0;
}

bool isFreePosition(wchar_t icon) {
    return icon == EMPTY_SQUARE || icon == FILLED_SQUARE;
}