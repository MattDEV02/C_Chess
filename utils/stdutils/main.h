#ifndef __STDUTILS_H_
#define __STDUTILS_H_


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <wchar.h>


#define COLOR_DELTA 6
#define N 8 
// N is the matrix order.
// COLOR_DELTA is the costtant unicode wchar difference between white icons and black icons.


typedef struct Point {
	short row; // y coordinate
	short col; // x coordinate
} Point; 

typedef wchar_t** ChessBoard;

const time_t getCurrentDateTime(bool isStartTime);

short shortReader(short integer, wchar_t* prompt);

unsigned short setCoordinate(int x);

const short sabs(short value); // abs function for short type values

const double dabs(double value); // abs function for double type values

void sound(unsigned short times);

void saveChessBoard(ChessBoard chessBoard);

void saveChessBoardGames(unsigned short winner, unsigned short movesCounter);

void readChessBoardArchive();

void readChessBoardGames();

#endif