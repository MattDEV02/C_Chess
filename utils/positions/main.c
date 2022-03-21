#include "../stdutils/main.h"
#include "../icons/main.h"
#include "main.h"


bool isBlackPosition(short row) {
    return row == 6 || row == 7;
}

bool isPawnPosition(short row) {
    return row == 1 || row == 6;
}

bool isHorsePosition(Point* p) {
    return (p->row == 0 || p->row == 7) && (p->col == 1 || p->col == 6);
}

bool isBishopPosition(Point* p) {
    return (p->row == 0 || p->row == 7) && (p->col == 2 || p->col == 5);
}

bool isTowerPosition(Point* p) {
    return (p->row == 0 || p->row == 7) && (p->col == 0 || p->col == 7);
}

bool isKingPosition(Point* p) {
    return (p->row == 0 || p->row == 7) && (p->col == 3);
}

bool isQueenPosition(Point* p) {
    return (p->row == 0 || p->row == 7) && (p->col == 4);
}

bool isEmptyPosition(short row) {
    return row >= 2 && row <= 5;
}

bool isEmptySquarePosition(Point* p) {
    return ((p->row + p->col) % 2) == 0;
}

bool isFreePosition(wchar_t icon) {
    return icon == EMPTY_SQUARE || icon == FILLED_SQUARE;
}