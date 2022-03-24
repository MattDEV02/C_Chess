#include <stdlib.h>
#include "main.h"


const time_t getCurrentDateTime(bool isStartTime) {
    const size_t bufferDim = 30;
    char dateTimeStringBuffer[bufferDim];
    const time_t now = time(NULL);
    struct tm* restrict time_info = localtime(&(now));
    time_info->tm_hour += 1; 
    strftime(dateTimeStringBuffer, bufferDim, "%Y-%m-%d %H:%M:%S", time_info);
    wprintf(L"\nGame %ls time = %s\n", isStartTime ? L"start" : L"end", dateTimeStringBuffer);
    return now;
}

void printChessBoardRow(bool isUp) {
    unsigned short i = 0;
    isUp ? wprintf(L"\n \n \t   ") : wprintf(L"\n \t   ");
    for (; i < N; i++)
        wprintf(L" %i ", i);
    wprintf(L"\n");
}

void printChessBoard(ChessBoard chessBoard) {
    unsigned short
        i = 0,
        j = 0;
    printChessBoardRow(true);
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            if (j == 0)
                wprintf(L"\t%i | %lc ", i, chessBoard[i][j]);
            else if (j == N - 1)
                wprintf(L" %lc | %i", chessBoard[i][j], i);
            else
                wprintf(L" %lc ", chessBoard[i][j]);
            if (j == N - 1 && i < N - 1)
                wprintf(L"\n");
        }
    }
    printChessBoardRow(false);
    wprintf(L"\n");
}

ChessBoard chessBoardCalloc() {
	ChessBoard m = calloc(N, sizeof(wchar_t*));
	if(m != NULL) {
		unsigned short row = 0;
		for(; row < N; row++) 
			m[row] = calloc(N, sizeof(wchar_t));
	} else {
		wprintf(L"\nErrore: Memoria heap per la scacchiera non allocata.\n");
		exit(EXIT_FAILURE);
	}
	return m;
}

void chessBoardDealloc(ChessBoard chessBoard) {
	unsigned short row = 0;
	for(; row < N; row++)
		free(chessBoard[row]);
	free(chessBoard);
}

unsigned short setCoordinate(int x) {
    if(x < 0)
        return 0;
    else if(x > N - 1)
        return N - 1;
    else 
        return x;
}

const double dabs(double value) {
    return value >= 0 ? value : (-1 * value);
}

void sound(unsigned short times) {
	unsigned short i = 0;
	for(; i < times; i++)
		system("tput bel");
}