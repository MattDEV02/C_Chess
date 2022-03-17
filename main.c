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
            "url": "https://github.com/MattDEV02/Chess/issues"
        },
        "description": "",
        "license": "ISC",
        "dependencies": {
        },
        "scripts": {
            "compile": "gcc main.c -o main",
            "run": "./main",
            "start": "gcc main.c -o main ; ./main"
        },
        "keywords": [
            "C",
            "Chess",
            "Matrixs"
        ]
    }

    SPECIFICS:
        * Description: .
        * Input: 2 point of a 8 * 8 matrix, anyone with 2 coordinates (x, y) = (row, col).
        * Pre-condition: rows and cols between 0 and 7.
        * Output: A short value named winner.
        * Post-condition: winner is 1 if the first player (with white icons) eat the opponent black queen, else 2.
        * Type of problem: Logic-game.
*/


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>
#include <wchar.h>
#include <time.h>

#define FILLED_SQUARE 0x25A0
#define EMPTY_SQUARE  0x25A1
#define BLACK_QUEEN   0x2654
#define BLACK_KING    0x2655
#define BLACK_TOWER   0x2656
#define BLACK_BISHOP  0x2657
#define BLACK_HORSE   0x2658
#define BLACK_PAWN    0x2659

#define COLOR_DIFF 6
#define N 8


struct tm* restrict printCurrentDateTime(bool isStartTime) {
    const size_t buffer_dim = 30;
    char dateTimeStringBuffer[buffer_dim];
    const time_t now = time(NULL);
    struct tm* restrict time_info = localtime(&(now));
    time_info->tm_hour += 1; 
    strftime(dateTimeStringBuffer, buffer_dim, "%Y-%m-%d %H:%M:%S", time_info);
    wprintf(L"\nGame %ls time = %s\n", isStartTime ? L"start" : L"end", dateTimeStringBuffer);
    return time_info;
}

void printRow(bool isUp) {
    unsigned short i = 0;
    isUp ? wprintf(L"\n \n \t   ") : wprintf(L"\n \t   ");
    for (; i < N; i++)
        wprintf(L" %i ", i);
    wprintf(L"\n");
}

void printMatrix(wchar_t matrix[N][N]) {
    unsigned short
        i = 0,
        j = 0;
    printRow(true);
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            if (j == 0)
                wprintf(L"\t%i | %lc ", i, matrix[i][j]);
            else if (j == N - 1)
                wprintf(L" %lc | %i", matrix[i][j], i);
            else
                wprintf(L" %lc ", matrix[i][j]);
            if (j == N - 1 && i < N - 1)
                wprintf(L"\n");
        }
    }
    printRow(false);
    wprintf(L"\n");
}

wchar_t getWhiteIcon(wchar_t black_icon) {
    return black_icon + COLOR_DIFF;
}

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

bool isPawn(wchar_t icon) {
    return icon == BLACK_PAWN || icon == getWhiteIcon(BLACK_PAWN);
}

bool isHorse(wchar_t icon) {
    return icon == BLACK_HORSE || icon == getWhiteIcon(BLACK_HORSE);
}

bool isBishop(wchar_t icon) {
    return icon == BLACK_BISHOP || icon == getWhiteIcon(BLACK_BISHOP);
}

bool isTower(wchar_t icon) {
    return icon == BLACK_TOWER || icon == getWhiteIcon(BLACK_TOWER);
}

bool isKing(wchar_t icon) {
    return icon == BLACK_KING || icon == getWhiteIcon(BLACK_KING);
}

bool isQueen(wchar_t icon) {
    return icon == BLACK_QUEEN || icon == getWhiteIcon(BLACK_QUEEN);
}

bool isBlack(wchar_t icon) {
    return icon >= BLACK_QUEEN && icon <= BLACK_PAWN;
}

bool isEqualColor(wchar_t icon1, wchar_t icon2) {
    return 
        (!isFreePosition(icon1) && !isFreePosition(icon2)) && (  
        (isBlack(icon1) && isBlack(icon2)) ||
        (!isBlack(icon1) && !isBlack(icon2))
    );
}

bool isBlackPawnDiaogonalMove(wchar_t chessBoard[N][N], unsigned short row1, unsigned short col1, unsigned short row2, unsigned short col2) {
    return !isFreePosition(chessBoard[row2][col2]) && (row1 + col1 - 2 == row2 + col2 || row1 + col1 == row2 + col2) && (row1 != row2 && col1 != col2);
}

bool isWhitePawnDiaogonalMove(wchar_t chessBoard[N][N], unsigned short row1, unsigned short col1, unsigned short row2, unsigned short col2) {
    return !isFreePosition(chessBoard[row2][col2]) && (row1 + col1 + 2 == row2 + col2 || row1 + col1 == row2 + col2) && (row1 != row2 && col1 != col2);
}

bool isHorseMovement(unsigned short row1, unsigned short col1, unsigned short row2, unsigned short col2) {
    return 
        (row1 == row2 + 1 && col1 == col2 + 2) || 
        (row1 == row2 + 2 && col1 == col2 + 1) ||
        (row1 == row2 - 1 && col1 == col2 - 2) || 
        (row1 == row2 - 2 && col1 == col2 - 1) ||
        (row1 == row2 - 1 && col1 == col2 + 2) ||
        (row1 == row2 + 1 && col1 == col2 - 2) ||
        (row1 == row2 + 2 && col1 == col2 - 1) ||
        (row1 == row2 - 2 && col1 == col2 + 1);
};

bool isBishopMovement(unsigned short row1, unsigned short col1, unsigned short row2, unsigned short col2) {
    return ((row1 + col1  - row2 + col2) % 2 == 0) && (row1 != row2 && col1 != col2);
}

bool isTowerMovement(unsigned short row1, unsigned short col1, unsigned short row2, unsigned short col2) {
    return 
        (row2 > row1 && col1 == col2) ||
        (row1 == row2 && col1 > col2) ||
        (row2 < row1 && col1 == col2) ||
        (row1 == row2 && col1 < col2);
}

bool isKingMovement(unsigned short row1, unsigned short col1, unsigned short row2, unsigned short col2) {
    return 
        isBishopMovement(row1, col1, row2, col2) ||
        isTowerMovement(row1, col1, row2, col2);
}

bool isQueenMovement(unsigned short row1, unsigned short col1, unsigned short row2, unsigned short col2) {
    return 
        (row1 == row2 - 1 && col1 == col2) ||
        (row1 == row2 + 1 && col1 == col2) ||
        (row1 == row2 && col1 == col2 - 1) ||
        (row1 == row2 && col1 == col2 + 1) ||
        (row1 + col1 - 2 == row2 + col2 && row1 != row2 && col1 != col2) ||
        (row1 + col1 + 2 == row2 + col2 && row1 != row2 && col1 != col2) ||
        (row1 + col1 == row2 + col2 && row1 != row2 && col1 != col2);
}

void defineChessBoardMatrix(wchar_t chessBoard[N][N]) {
    unsigned short
        i = 0,
        j = 0;
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            if (isPawnPosition(i))
                chessBoard[i][j] = isBlackPosition(i) ? BLACK_PAWN : getWhiteIcon(BLACK_PAWN);
            else if (isBishopPosition(i, j))
                chessBoard[i][j] = isBlackPosition(i) ? BLACK_BISHOP : getWhiteIcon(BLACK_BISHOP);
            else if (isHorsePosition(i, j))
                chessBoard[i][j] = isBlackPosition(i) ? BLACK_HORSE : getWhiteIcon(BLACK_HORSE);
            else if (isTowerPosition(i, j))
                chessBoard[i][j] = isBlackPosition(i) ? BLACK_TOWER : getWhiteIcon(BLACK_TOWER);
            else if (isKingPosition(i, j))
                chessBoard[i][j] = isBlackPosition(i) ? BLACK_KING : getWhiteIcon(BLACK_KING);
            else if (isQueenPosition(i, j))
                chessBoard[i][j] = isBlackPosition(i) ? BLACK_QUEEN : getWhiteIcon(BLACK_QUEEN);
            else if (isEmptyPosition(i))
                chessBoard[i][j] = isEmptySquarePosition(i, j) ? EMPTY_SQUARE : FILLED_SQUARE;
        }
    }
}

void printIconStringName(wchar_t icon) { 
    if(isPawn(icon))
        wprintf(L"Pawn.\n");
    else if(isHorse(icon))
        wprintf(L"Horse.\n");
    else if(isBishop(icon))
        wprintf(L"Bishop.\n");
    else if(isTower(icon))
        wprintf(L"Tower.\n");
    else if(isKing(icon))
        wprintf(L"King.\n");
    else if(isQueen(icon))
        wprintf(L"Queen.\n");
    else if(isFreePosition(icon))
        wprintf(L"Empty.\n");
    else {
        wprintf(L"\n \nNot valid icon !\n \n");
        exit(EXIT_FAILURE);
    }
}

bool move(wchar_t chessBoard[N][N], unsigned short row1, unsigned short col1, unsigned short row2, unsigned short col2) {
    wchar_t temp = chessBoard[row2][col2];
    if(!isFreePosition(temp)) {
        wprintf(L"\nHai mangiato un %lc  %ls/a dell'avversario ! ; ", temp, isBlack(chessBoard[row2][col2]) ? L"nero" : L"bianco");
        printIconStringName(temp);
    }
    chessBoard[row2][col2] = chessBoard[row1][col1];
    chessBoard[row1][col1] = isEmptySquarePosition(row1, col1) ? EMPTY_SQUARE : FILLED_SQUARE;
    return isQueen(temp);
}

unsigned short setCoordinate(int x) {
    if(x < 0)
        return 0;
    else if(x > N - 1)
        return N - 1;
    else 
        return x;
}

bool playerTurn(wchar_t chessBoard[N][N], unsigned short row1, unsigned short col1) {
    unsigned short
        row2 = 0,
        col2 = 0,
        i = 0,
        j = 0;
    bool 
        badMove = false,
        hasWin = false;
    do { 
        if(badMove)
            printMatrix(chessBoard);
        wprintf(L"\nInserisci la riga dove vuoi arrivare: ");
        scanf("%hu", &(row2));
        wprintf(L"\nInserisci la colonna dove vuoi arrivare: ");
        scanf("%hu", &(col2));
        row2 = setCoordinate(row2);
        col2 = setCoordinate(col2);
        wprintf(L"\nPosizione di arrivo: %lc ; (%i, %i) ; ", chessBoard[row2][col2], row2, col2);
        printIconStringName(chessBoard[row2][col2]);
        if (isPawn(chessBoard[row1][col1])) {
            if (isBlack(chessBoard[row1][col1])) {
                if (row1 == N - 2) {
                    if(isFreePosition(chessBoard[row2][col2])) {
                        if((row2 == row1 - 1 || row2 == row1 - 2) && col1 == col2) {
                            badMove = false;
                            hasWin = move(chessBoard, row1, col1, row2, col2);
                        } else {
                            badMove = true;
                            wprintf(L"\nMossa non valida (pedone nero frontale), riprova.\n");
                        }
                    } else {
                        if(isBlackPawnDiaogonalMove(chessBoard, row1, col1, row2, col2) && !isEqualColor(chessBoard[row1][col1], chessBoard[row2][col2])) {
                            badMove = false;
                            hasWin = move(chessBoard, row1, col1, row2, col2);   
                        } else {
                            badMove = true;
                            wprintf(L"\nMossa non valida (pedone nero diagonale), riprova.\n");
                        }
                    }  
                } else {
                    if(isFreePosition(chessBoard[row2][col2])) {
                        if(row2 == row1 - 1 && col1 == col2) {
                            badMove = false;
                            hasWin = move(chessBoard, row1, col1, row2, col2);
                        } else {
                            badMove = true;
                            wprintf(L"\nMossa non valida (pedone nero frontale), riprova.\n");   
                        }
                    } else {
                        if(isBlackPawnDiaogonalMove(chessBoard, row1, col1, row2, col2) && !isEqualColor(chessBoard[row1][col1], chessBoard[row2][col2])) {
                            badMove = false;
                            hasWin = move(chessBoard, row1, col1, row2, col2);   
                        } else {
                            badMove = true;
                            wprintf(L"\nMossa non valida (pedone nero diagonale), riprova.\n");
                        }
                    }
                }
            } else {
                if (row1 == 1) {
                    if(isFreePosition(chessBoard[row2][col2])) {
                        if((row2 == row1 + 1 || row2 == row1 + 2) && col1 == col2) {
                            badMove = false;
                            hasWin = move(chessBoard, row1, col1, row2, col2);
                        } else {
                            badMove = true;
                            wprintf(L"\nMossa non valida (pedone bianco frontale), riprova.\n");
                        }
                    } else {
                        if(isWhitePawnDiaogonalMove(chessBoard, row1, col1, row2, col2) && !isEqualColor(chessBoard[row1][col1], chessBoard[row2][col2])) {
                            badMove = false;
                            hasWin = move(chessBoard, row1, col1, row2, col2);   
                        } else {
                            badMove = true;
                            wprintf(L"\nMossa non valida (pedone bianco diagonale), riprova.\n");
                        }
                    }  
                } else {
                    if(isFreePosition(chessBoard[row2][col2])) {
                        if(row2 == row1 + 1 && col1 == col2) {
                            badMove = false;
                            hasWin = move(chessBoard, row1, col1, row2, col2);
                        } else {
                            badMove = true;
                            wprintf(L"\nMossa non valida (pedone bianco frontale), riprova.\n");   
                        }
                    } else {
                        if(isWhitePawnDiaogonalMove(chessBoard, row1, col1, row2, col2) && !isEqualColor(chessBoard[row1][col1], chessBoard[row2][col2])) {
                            badMove = false;
                            hasWin = move(chessBoard, row1, col1, row2, col2);   
                        } else {
                            badMove = true;
                            wprintf(L"\nMossa non valida (pedone bianco diagonale), riprova.\n");
                        }
                    }
                }
            }
        }
        if (isHorse(chessBoard[row1][col1])) {
            if(isBlack(chessBoard[row1][col1])) {
                if(isHorseMovement(row1, col1, row2, col2)) {
                    if(isFreePosition(chessBoard[row2][col2]) || !isEqualColor(chessBoard[row1][col1], chessBoard[row2][col2])) {
                       badMove = false;
                       hasWin = move(chessBoard, row1, col1, row2, col2);
                    } else {
                        badMove = true;
                        wprintf(L"\nMossa non valida (cavallo nero), riprova.\n");  
                    }
                } else {
                    badMove = true;
                    wprintf(L"\nMossa non valida (cavallo nero), riprova.\n");
                }
            } else {
                if(isHorseMovement(row1, col1, row2, col2)) {
                    if(isFreePosition(chessBoard[row2][col2]) || !isEqualColor(chessBoard[row1][col1], chessBoard[row2][col2])) {
                        badMove = false;
                        hasWin = move(chessBoard, row1, col1, row2, col2);
                    } else {
                        badMove = true;
                        wprintf(L"\nMossa non valida (cavallo bianco), riprova.\n");  
                    }
                } else {
                    badMove = true;
                    wprintf(L"\nMossa non valida (cavallo bianco), riprova.\n");
                }
            }
        }
        if (isBishop(chessBoard[row1][col1])) {
            if(isBlack(chessBoard[row1][col1])) {
                if(isBishopMovement(row1, col1, row2, col2)) {
                    if(isFreePosition(chessBoard[row2][col2]) || !isEqualColor(chessBoard[row1][col1], chessBoard[row2][col2])) {
                        badMove = false;
                        if(row1 > row2 && col1 > col2) {
                            for(i = row1 - 1, j = col1 - 1; ((i >= row2 + 1) || (j >= col2 + 1)) && !badMove; i--, j--) {
                                i = setCoordinate(i);
                                j = setCoordinate(j);
                                //wprintf(L"\n[%d][%d] = %lc, %d\n", i, j, chessBoard[i][j], badMove);
                                if(!isFreePosition(chessBoard[i][j])) 
                                    badMove = true;
                            } 
                            if(badMove)
                                wprintf(L"\nMossa non valida (alfiere nero sx alto), riprova.\n");   
                            else 
                                hasWin = move(chessBoard, row1, col1, row2, col2);   
                        } else if(row1 > row2 && col1 < col2) {
                            for(i = row1 + 1, j = col1 - 1; ((i < row2) || (j >= col2 + 1)) && !badMove; i++, j--) {
                                i = setCoordinate(i);
                                j = setCoordinate(j);
                                if(!isFreePosition(chessBoard[i][j])) 
                                    badMove = true;
                            } 
                            if(badMove)
                                wprintf(L"\nMossa non valida (alfiere nero dx alto), riprova.\n");   
                            else 
                                hasWin = move(chessBoard, row1, col1, row2, col2);  
                        } else if(row1 < row2 && col1 > col2) {
                            for(i = row1 + 1, j = col1 - 1; ((i < row2) || (j >= col2 + 1)) && !badMove; i++, j--) {
                                i = setCoordinate(i);
                                j = setCoordinate(j);
                                if(!isFreePosition(chessBoard[i][j])) 
                                    badMove = true;
                            } 
                            if(badMove)
                                wprintf(L"\nMossa non valida (alfiere nero sx basso), riprova.\n");   
                            else 
                                hasWin = move(chessBoard, row1, col1, row2, col2); 
                        } else if(row1 < row2 && col1 < col2) {
                            for(i = row1 + 1, j = col1 + 1; ((i < row2) || (j < col2)) && !badMove; i++, j++) {
                                i = setCoordinate(i);
                                j = setCoordinate(j);
                                if(!isFreePosition(chessBoard[i][j])) 
                                    badMove = true;
                            } 
                            if(badMove)
                                wprintf(L"\nMossa non valida (alfiere nero dx basso), riprova.\n");   
                            else 
                                hasWin = move(chessBoard, row1, col1, row2, col2);  
                        }
                    } else {
                        badMove = true;
                        wprintf(L"\nMossa non valida (alfiere nero), riprova.\n");   
                    }
                } else {
                    badMove = true;
                    wprintf(L"\nMossa non valida (alfiere nero), riprova.\n");
                }
        } else {
                if(isBishopMovement(row1, col1, row2, col2)) {
                    if(isFreePosition(chessBoard[row2][col2]) || !isEqualColor(chessBoard[row1][col1], chessBoard[row2][col2])) {
                        badMove = false;
                         badMove = false;
                        if(row1 > row2 && col1 > col2) {
                            for(i = row1 - 1, j = col1 - 1; ((i >= row2 + 1) || (j >= col2 + 1)) && !badMove; i--, j--) {
                                //wprintf(L"\n[%d][%d] = %lc, %d\n", i, j, chessBoard[i][j], badMove);
                                i = setCoordinate(i);
                                j = setCoordinate(j);
                                if(!isFreePosition(chessBoard[i][j])) 
                                    badMove = true;
                            } 
                            if(badMove)
                                wprintf(L"\nMossa non valida (alfiere bianco dx basso), riprova.\n");   
                            else 
                                hasWin = move(chessBoard, row1, col1, row2, col2);   
                        } else if(row1 > row2 && col1 < col2) {
                            for(i = row1 + 1, j = col1 - 1; ((i < row2) || (j >= col2 + 1)) && !badMove; i++, j--) {
                                i = setCoordinate(i);
                                j = setCoordinate(j);
                                if(!isFreePosition(chessBoard[i][j])) 
                                    badMove = true;
                            } 
                            if(badMove)
                                wprintf(L"\nMossa non valida (alfiere bianco sx basso), riprova.\n");   
                            else 
                                hasWin = move(chessBoard, row1, col1, row2, col2);  
                        } else if(row1 < row2 && col1 > col2) {
                            for(i = row1 + 1, j = col1 - 1; ((i < row2) || (j >= col2 + 1)) && !badMove; i++, j--) {
                                i = setCoordinate(i);
                                j = setCoordinate(j);
                                if(!isFreePosition(chessBoard[i][j])) 
                                    badMove = true;
                            } 
                            if(badMove)
                                wprintf(L"\nMossa non valida (alfiere bianco dx alto), riprova.\n");   
                            else 
                                hasWin = move(chessBoard, row1, col1, row2, col2); 
                        } else if(row1 < row2 && col1 < col2) {
                            for(i = row1 + 1, j = col1 + 1; ((i < row2) || (j < col2)) && !badMove; i++, j++) {
                                i = setCoordinate(i);
                                j = setCoordinate(j);
                                if(!isFreePosition(chessBoard[i][j]))
                                    badMove = true;
                            } 
                            if(badMove)
                                wprintf(L"\nMossa non valida (alfiere bianco sx alto), riprova.\n");   
                            else 
                                hasWin = move(chessBoard, row1, col1, row2, col2);  
                        }
                    } else {
                        badMove = true;
                        wprintf(L"\nMossa non valida (alfiere bianco), riprova.\n");   
                    }
                } else {
                    badMove = true;
                    wprintf(L"\nMossa non valida (alfiere bianco), riprova.\n");
                }
            }
        }
        if (isTower(chessBoard[row1][col1])) {
            if(isBlack(chessBoard[row1][col1])) {
                if(isTowerMovement(row1, col1, row2, col2) && !isEqualColor(chessBoard[row1][col1], chessBoard[row2][col2])) {
                    if(row1 > row2 && col1 == col2) {
                        badMove = false;
                        for(i = row1 - 1; (i >= row2 + 1) && !badMove; i--) {
                            if(!isFreePosition(chessBoard[i][col2])) 
                                badMove = true;
                        }
                        if(badMove) 
                            wprintf(L"\nMossa non valida (torre nera frontale), riprova.\n");
                        else 
                            hasWin = move(chessBoard, row1, col1, row2, col2);
                    } else if(row1 < row2 && col1 == col2) {
                        // wprintf(L"giu");
                        badMove = false;
                        for(i = row1 + 1; (i < row2) && !badMove; i++) {
                            if(!isFreePosition(chessBoard[i][col2])) {
                                badMove = true;
                            }
                        }
                        if(badMove) 
                            wprintf(L"\nMossa non valida (torre nera retro), riprova.\n");
                        else 
                            hasWin = move(chessBoard, row1, col1, row2, col2);
                    } else if(row1 == row2 && col1 > col2) {
                        badMove = false;
                        for(j = col1 - 1; (j >= col2 + 1) && !badMove; j--) {
                            if(!isFreePosition(chessBoard[row2][j])) 
                                badMove = true;
                        }
                        if(badMove) 
                            wprintf(L"\nMossa non valida (torre nera sx), riprova.\n");
                        else 
                            hasWin = move(chessBoard, row1, col1, row2, col2);
                    } else if(row1 == row2 && col1 < col2) {
                        badMove = false;
                        for(j = col1 + 1; (j < col2) && !badMove; j++) {
                            if(!isFreePosition(chessBoard[row2][j])) 
                                badMove = true;
                        }
                        if(badMove) 
                            wprintf(L"\nMossa non valida (torre nera dx), riprova.\n");
                        else 
                            hasWin = move(chessBoard, row1, col1, row2, col2);
                    }
                } else {
                    badMove = true;
                    wprintf(L"\nMossa non valida (torre nera), riprova.\n");
                }
            } else {
                if(isTowerMovement(row1, col1, row2, col2) && !isEqualColor(chessBoard[row1][col1], chessBoard[row2][col2])) {
                    if(row1 > row2 && col1 == col2) {
                        badMove = false;
                        for(i = row1 - 1; (i >= row2 + 1) && !badMove; i--) {
                            if(!isFreePosition(chessBoard[i][col2])) 
                                badMove = true;
                        }
                        if(badMove) 
                            wprintf(L"\nMossa non valida (torre bianca retro), riprova.\n");
                        else 
                            hasWin = move(chessBoard, row1, col1, row2, col2);
                    } else if(row1 < row2 && col1 == col2) {
                        badMove = false;
                        for(i = row1 + 1; (i < row2) && !badMove; i++) {
                            if(!isFreePosition(chessBoard[i][col2])) 
                                badMove = true;
                        }
                        if(badMove) 
                            wprintf(L"\nMossa non valida (torre bianca frontale), riprova.\n");
                        else 
                            hasWin = move(chessBoard, row1, col1, row2, col2);
                    } else if(row1 == row2 && col1 > col2) {
                        badMove = false;
                        for(j = col1 - 1; (j >= col2 + 1) && !badMove; j--) {
                            if(!isFreePosition(chessBoard[row2][j])) 
                                badMove = true;
                        }
                        if(badMove) 
                            wprintf(L"\nMossa non valida (torre bianca sx), riprova.\n");
                        else 
                            hasWin = move(chessBoard, row1, col1, row2, col2);
                    } else if(row1 == row2 && col1 < col2) {
                        badMove = false;
                        for(j = col1 + 1; (j < col2) && !badMove; j++) {
                            if(!isFreePosition(chessBoard[row2][j])) 
                                badMove = true;
                        }
                        if(badMove) 
                            wprintf(L"\nMossa non valida (torre bianca dx), riprova.\n");
                        else 
                            hasWin = move(chessBoard, row1, col1, row2, col2);
                    }
                } else {
                    badMove = true;
                    wprintf(L"\nMossa non valida (torre bianca), riprova.\n");
                }
            }
        }
        if (isKing(chessBoard[row1][col1])) {
            if(isBlack(chessBoard[row1][col1])) {
                if(isKingMovement(row1, col1, row2, col2) && !isEqualColor(chessBoard[row1][col1], chessBoard[row2][col2])) {
                    badMove = false;
                    // su, giù, sx, dx.
                    if(row1 > row2 && col1 == col2) {
                        badMove = false;
                        for(i = row1 - 1; (i >= row2 + 1) && !badMove; i--) {
                            if(!isFreePosition(chessBoard[i][col2])) 
                                badMove = true;
                        }
                        if(badMove) 
                            wprintf(L"\nMossa non valida (Re nero frontale), riprova.\n");
                        else 
                            hasWin = move(chessBoard, row1, col1, row2, col2);
                    } else if(row1 < row2 && col1 == col2) {
                        badMove = false;
                        for(i = row1 + 1; (i < row2) && !badMove; i++) {
                            if(!isFreePosition(chessBoard[i][col2])) 
                                badMove = true;
                        }
                        if(badMove) 
                            wprintf(L"\nMossa non valida (Re nero retro), riprova.\n");
                        else 
                            hasWin = move(chessBoard, row1, col1, row2, col2);
                    } else if(row1 == row2 && col1 > col2) {
                        badMove = false;
                        for(j = col1 - 1; (j >= col2 + 1) && !badMove; j--) {
                            if(!isFreePosition(chessBoard[row2][j])) 
                                badMove = true;
                        }
                        if(badMove) 
                            wprintf(L"\nMossa non valida (Re nero sx), riprova.\n");
                        else 
                            hasWin = move(chessBoard, row1, col1, row2, col2);
                    } else if(row1 == row2 && col1 < col2) {
                        badMove = false;
                        for(j = col1 + 1; (j < col2) && !badMove; j++) {
                            if(!isFreePosition(chessBoard[row2][j])) 
                                badMove = true;
                        }
                        if(badMove) 
                            wprintf(L"\nMossa non valida (Re nero dx), riprova.\n");
                        else 
                            hasWin = move(chessBoard, row1, col1, row2, col2);
                    }
                    // diag sup-sx , diag inf-sx, diag su-dx, diag inf-dx
                    if(row1 > row2 && col1 > col2) {
                        for(i = row1 - 1, j = col1 - 1; ((i >= row2 + 1) || (j >= col2 + 1)) && !badMove; i--, j--) {
                            //wprintf(L"\n[%d][%d] = %lc, %d\n", i, j, chessBoard[i][j], badMove);
                            i = setCoordinate(i);
                            j = setCoordinate(j);
                            if(!isFreePosition(chessBoard[i][j])) 
                                badMove = true;
                        } 
                        if(badMove)
                            wprintf(L"\nMossa non valida (Re nero sx alto), riprova.\n");   
                        else 
                            hasWin = move(chessBoard, row1, col1, row2, col2);   
                    } else if(row1 > row2 && col1 < col2) {
                        for(i = row1 - 1, j = col1 + 1; ((i >= row2 + 1) || (j < col2)) && !badMove; i--, j++) {
                            i = setCoordinate(i);
                            j = setCoordinate(j);
                            if(!isFreePosition(chessBoard[i][j])) 
                                badMove = true;
                        } 
                        if(badMove)
                            wprintf(L"\nMossa non valida (Re nero dx alto), riprova.\n");   
                        else 
                            hasWin = move(chessBoard, row1, col1, row2, col2);  
                    } else if(row1 < row2 && col1 > col2) {
                        for(i = row1 + 1, j = col1 - 1; ((i < row2) || (j >= col2 + 1)) && !badMove; i++, j--) {
                            i = setCoordinate(i);
                            j = setCoordinate(j);
                            if(!isFreePosition(chessBoard[i][j])) 
                                badMove = true;
                        } 
                        if(badMove)
                            wprintf(L"\nMossa non valida (Re nero sx basso), riprova.\n");   
                        else 
                            hasWin = move(chessBoard, row1, col1, row2, col2); 
                    } else if(row1 < row2 && col1 < col2) {
                        for(i = row1 + 1, j = col1 + 1; ((i < row2) || (j < col2)) && !badMove; i++, j++) {
                            i = setCoordinate(i);
                            j = setCoordinate(j);
                            if(!isFreePosition(chessBoard[i][j])) 
                                badMove = true;
                        } 
                        if(badMove)
                            wprintf(L"\nMossa non valida (Re nero dx basso), riprova.\n");   
                        else 
                            hasWin = move(chessBoard, row1, col1, row2, col2);  
                    }
                } else {
                    badMove = true;
                    wprintf(L"\nMossa non valida (Re nero), riprova.\n");
                }
            } else {
                if(isKingMovement(row1, col1, row2, col2) && !isEqualColor(chessBoard[row1][col1], chessBoard[row2][col2])) {
                    // su, giù, sx, dx.
                    badMove = false;
                    if(row1 > row2 && col1 == col2) {
                        badMove = false;
                        for(i = row1 - 1; (i >= row2 + 1) && !badMove; i--) {
                            if(!isFreePosition(chessBoard[i][col2])) 
                                badMove = true;
                        }
                        if(badMove) 
                            wprintf(L"\nMossa non valida (Re bianco retro), riprova.\n");
                        else 
                            hasWin = move(chessBoard, row1, col1, row2, col2);
                    } else if(row1 < row2 && col1 == col2) {
                        badMove = false;
                        for(i = row1 + 1; (i < row2) && !badMove; i++) {
                            if(!isFreePosition(chessBoard[i][col2])) 
                                badMove = true;
                        }
                        if(badMove) {
                            wprintf(L"\nMossa non valida (Re bianco frontale), riprova.\n");
                        } else 
                            hasWin = move(chessBoard, row1, col1, row2, col2);
                    } else if(row1 == row2 && col1 > col2) {
                        badMove = false;
                        for(j = col1 - 1; (j >= col2 + 1) && !badMove; j--) {
                            if(!isFreePosition(chessBoard[row2][j])) 
                                badMove = true;
                        }
                        if(badMove) 
                            wprintf(L"\nMossa non valida (Re bianco dx), riprova.\n");
                        else 
                            hasWin = move(chessBoard, row1, col1, row2, col2);
                    } else if(row1 == row2 && col1 < col2) {
                        badMove = false;
                        for(j = col1 + 1; (j < col2) && !badMove; j++) {
                            if(!isFreePosition(chessBoard[row2][j])) 
                                badMove = true;
                        }
                        if(badMove) 
                            wprintf(L"\nMossa non valida (Re bianco sx), riprova.\n");
                        else 
                            hasWin = move(chessBoard, row1, col1, row2, col2);
                    }
                    // diag sup-sx , diag inf-sx, diag su-dx, diag inf-dx
                    if(row1 > row2 && col1 > col2) {
                        for(i = row1 - 1, j = col1 - 1; ((i >= row2 + 1) || (j >= col2 + 1)) && !badMove; i--, j--) {
                            i = setCoordinate(i);
                            j = setCoordinate(j);
                            //wprintf(L"\n[%d][%d] = %lc, %d\n", i, j, chessBoard[i][j], badMove);
                            if(!isFreePosition(chessBoard[i][j])) 
                                badMove = true;
                        } 
                        if(badMove)
                            wprintf(L"\nMossa non valida (Re bianco dx basso), riprova.\n");   
                        else 
                            hasWin = move(chessBoard, row1, col1, row2, col2);   
                    } else if(row1 > row2 && col1 < col2) {
                        for(i = row1 + 1, j = col1 - 1; ((i < row2) || (j >= col2 + 1)) && !badMove; i++, j--) {
                            i = setCoordinate(i);
                            j = setCoordinate(j);
                            if(!isFreePosition(chessBoard[i][j])) 
                                badMove = true;
                        } 
                        if(badMove)
                            wprintf(L"\nMossa non valida (Re bianco sx basso), riprova.\n");   
                        else 
                            hasWin = move(chessBoard, row1, col1, row2, col2);  
                    } else if(row1 < row2 && col1 > col2) {
                        for(i = row1 + 1, j = col1 - 1; ((i < row2) || (j >= col2 + 1)) && !badMove; i++, j--) {
                            i = setCoordinate(i);
                            j = setCoordinate(j);
                            if(!isFreePosition(chessBoard[i][j])) 
                                badMove = true;
                        } 
                        if(badMove)
                            wprintf(L"\nMossa non valida (Re bianco dx alto), riprova.\n");   
                        else 
                            hasWin = move(chessBoard, row1, col1, row2, col2); 
                    } else if(row1 < row2 && col1 < col2) {
                        for(i = row1 + 1, j = col1 + 1; ((i < row2) || (j < col2)) && !badMove; i++, j++) {
                            i = setCoordinate(i);
                            j = setCoordinate(j);
                            if(!isFreePosition(chessBoard[i][j])) 
                                badMove = true;
                        } 
                        if(badMove)
                            wprintf(L"\nMossa non valida (Re bianco sx alto), riprova.\n");   
                        else 
                            hasWin = move(chessBoard, row1, col1, row2, col2);  
                    }
                } else {
                    badMove = true;
                    wprintf(L"\nMossa non valida (Re bianco), riprova.\n");
                }
            }
        }
        if (isQueen(chessBoard[row1][col1])) {
            if(isBlack(chessBoard[row1][col1])) {
                if(isQueenMovement(row1, col1, row2, col2) && !isEqualColor(chessBoard[row1][col1], chessBoard[row2][col2])) {
                    badMove = false;
                    hasWin = move(chessBoard, row1, col1, row2, col2);
                } else {
                    badMove = true;
                    wprintf(L"\nMossa non valida (Regina nera), riprova.\n");
                }
            } else {
                if(isQueenMovement(row1, col1, row2, col2) && !isEqualColor(chessBoard[row1][col1], chessBoard[row2][col2])) {
                    badMove = false;
                    hasWin = move(chessBoard, row1, col1, row2, col2);
                } else {
                    badMove = true;
                    wprintf(L"\nMossa non valida (Regina bianca), riprova.\n");
                }
            }
        }   
    } while(badMove);
    return hasWin;
}

int main(void) { 
    setlocale(LC_ALL, "");
    bool 
        hasWin = false,
        badMove = false;
    unsigned short
        player = 0,
        winner = 0,
        row1 = 0,
        col1 = 0;
    unsigned int movesCounter = 0;
    wchar_t chessBoard[N][N];
    defineChessBoardMatrix(chessBoard);
    printCurrentDateTime(true);
    while(!hasWin) {
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
                } else if(player == 1 && !isBlack(chessBoard[row1][col1])) {
                    badMove = true;
                    wprintf(L"\nGiocatore %i hai i neri, riprova.\n", player + 1);
                } else if(isFreePosition(chessBoard[row1][col1])) {
                    badMove = true;
                    wprintf(L"\nPosizione vuota, riprova.\n");
                } else 
                    badMove = false;
            } while(badMove);
            wprintf(L"\nPosizione di partenza: %lc ; colore: %ls ; (%i, %i) ; ", chessBoard[row1][col1], isBlack(chessBoard[row1][col1]) ? L"nero" : L"bianco", row1, col1);
            printIconStringName(chessBoard[row1][col1]);
            hasWin = playerTurn(chessBoard, row1, col1);
            winner = player + 1;
            movesCounter++;
            if(player == 0)
                player++;
            else 
                player = 0;
        } 
    }
    system("tput bel"); // linux sound
    printMatrix(chessBoard);
    wprintf(L"\n \nVincitore: giocatore %i (%ls) in %d mosse totali.\n", winner, winner == 1 ? L"bianchi" : L"neri", movesCounter);
    printCurrentDateTime(false);
    wprintf(L"\n");
    return EXIT_SUCCESS;
}