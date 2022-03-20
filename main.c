/*  
    {
        "name": "Chess",
        "author": "Matteo Lambertucci, <matteolambertucci3@gmail.com>",
        "version": "0.1.0",
        "private": false,
        "repository": {
            "type": "git",
            "url": "https://github.com/MattDEV02/Chess.git"
        },
        "bugs": {
            "url": "https://github.com/MattDEV02/Chess/issues/"
        },
        "description": "Program that simulates the game of Chess between 2 people with real pieces. N.B. = this program does not work on Windows operating systems.",
        "license": "ISC",
        "dependencies": {
        },
        "scripts": {
            "build": "gcc main.c utils/stdutils/main.c utils/positions/main.c utils/icons/main.c utils/movements/main.c utils/chessboard/main.c -o main",
            "exec": "./main",
            "start": "gcc main.c utils/stdutils/main.c utils/positions/main.c utils/icons/main.c utils/movements/main.c utils/chessboard/main.c -o main && ./main"
        },
        "keywords": [
            "C",
            "Chess",
            "C Matrixs",
            "C Structs",
			"C Pointers",
			"C DateTimes"
        ]
    }
*/

/*
    SPECIFICS:
        * Description: Program that simulates the game of "Chess" between 2 people with real pieces. N.B. =                            this program does not work on Windows operating systems.
        * Input: 2 point of a (8 * 8) wchart_t matrix, anyone with 2 coordinates (row, col) = (x, y).
        * Pre-condition: rows and cols between 0 and 7.
        * Output: A short value named winner.
        * Post-condition: winner is 1 if the first player (with white icons) eat the opponent black queen, else 2.
        * Type of problem: Logic-game.
*/


#include <stdlib.h>
#include <locale.h>
#include "utils/stdutils/main.h"
#include "utils/positions/main.h"
#include "utils/icons/main.h"
#include "utils/movements/main.h"
#include "utils/chessboard/main.h"


int main(void) { 
    setlocale(LC_ALL, "");
    bool 
        hasWin = false,
        badMove = false;
	unsigned int movesCounter = 0;
    short
        player = 0,
        winner = 0,
        row1 = 0,
        col1 = 0;
	Point p1;
    wchar_t chessBoard[N][N];
    defineChessBoardMatrix(chessBoard);
    const time_t startTime = getCurrentDateTime(true);
    while((player < 2) && !hasWin) { 
        do {
            wprintf(L"\nTurno giocatore %i, colore %ls, mossa totale numero %d:\n \n", player + 1, player == 1 ? L"neri" : L"bianchi", movesCounter + 1);
            printMatrix(chessBoard);
            wprintf(L"\n \nGiocatore %i Inserisci la riga attuale: ", player + 1);
            scanf("%hu", &(row1));
            wprintf(L"\nGiocatore %i Inserisci la colonna attuale: ", player + 1);
            scanf("%hu", &(col1));
            row1 = setCoordinate(row1);
            col1 = setCoordinate(col1);
            if(player == 0 && isBlack(chessBoard[row1][col1])) {
                badMove = true;
                wprintf(L"\nGiocatore %i hai i bianchi, riprova.\n", player + 1);
            } else if(player == 1 && !isBlack(chessBoard[row1][col1]) && !isFreePosition(chessBoard[row1][col1])) {
                badMove = true;
                wprintf(L"\nGiocatore %i hai i neri, riprova.\n", player + 1);
            } else if(isFreePosition(chessBoard[row1][col1])) {
                badMove = true;
                wprintf(L"\nPosizione vuota, riprova.\n");
            } else 
                badMove = false;
        } while(badMove);
		p1.row = row1;
		p1.col = col1;
        wprintf(L"\nPosizione di partenza: %lc ; colore: %ls ; (%i, %i) ; ", chessBoard[row1][col1], isBlack(chessBoard[row1][col1]) ? L"nero" : L"bianco", row1, col1);
        printIconStringName(chessBoard[row1][col1]);
        hasWin = playerTurn(chessBoard, &(p1));
        winner = player + 1;
        movesCounter++;
        if(player == 0)
            player++;
        else 
            player = 0;
    } 
    system("tput bel"); // linux bell sound
    printMatrix(chessBoard);
    wprintf(L"\n \nVincitore: giocatore %i (%ls) in %d mosse totali.\n", winner, winner == 1 ? L"bianchi" : L"neri", movesCounter);
    const time_t endTime = getCurrentDateTime(false);
    const double secondsTimeDiff = dabs(difftime(endTime, startTime));
    wprintf(L"\nMosse totali per secondo: %g (%g secondi = %g minuti)\n \n \n", secondsTimeDiff / movesCounter, secondsTimeDiff, secondsTimeDiff / 60);
    return EXIT_SUCCESS;
}