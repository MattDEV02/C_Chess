#ifndef STDUTILS_H

#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <wchar.h>

#define COLOR_DIFF 6
#define N 8 
// N is the matrix order


const time_t getCurrentDateTime(bool isStartTime);

void printRow(bool isUp);

void printMatrix(wchar_t matrix[N][N]);

unsigned short setCoordinate(int x);

const double dabs(double value);

#endif