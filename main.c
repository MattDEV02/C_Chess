#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>
#include <wchar.h>

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

void printRow() {
    int i = 0;
    wchar_t c = L'_';
    wprintf(L"\n \n ");
    for (; i < N; i++)
        wprintf(L" %d ", i);
    wprintf(L"\n");
}

void printMatrix(wchar_t m[N][N]) {
    int
        i = 0,
        j = 0;
    printRow();
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            if (j == 0)
                wprintf(L"| %lc ", m[i][j]);
            else if (j == N - 1)
                wprintf(L" %lc | %d", m[i][j], i);
            else
                wprintf(L" %lc ", m[i][j]);
            if (j == N - 1 && i < N - 1)
                wprintf(L"\n");
        }
    }
    wprintf(L"\n \n");
}

wchar_t getWhiteIcon(wchar_t black_icon) {
    return black_icon + COLOR_DIFF;
}

bool isBlackPosition(int row) {
    return row == 6 || row == 7;
}

bool isPawnPosition(int row) {
    return row == 1 || row == 6;
}

bool isHorsePosition(int row, int col) {
    return (row == 0 || row == 7) && (col == 1 || col == 6);
}

bool isBishopPosition(int row, int col) {
    return (row == 0 || row == 7) && (col == 2 || col == 5);
}

bool isTowerPosition(int row, int col) {
    return (row == 0 || row == 7) && (col == 0 || col == 7);
}

bool isKingPosition(int row, int col) {
    return (row == 0 || row == 7) && (col == 4);
}

bool isQueenPosition(int row, int col) {
    return (row == 0 || row == 7) && (col == 3);
}

bool isEmptyPosition(int row) {
    return row >= 2 && row <= 5;
}

bool isEmptySquarePosition(int row, int col) {
    return (row + col) % 2 == 0;
}

bool isFreePosition(wchar_t chessBoard[N][N], int row, int col) {
    return chessBoard[row][col] == EMPTY_SQUARE || chessBoard[row][col] == FILLED_SQUARE;
}

bool isEmpty(wchar_t chessBoard[N][N], int row, int col) {
    return chessBoard[row][col] != EMPTY_SQUARE && chessBoard[row][col] != FILLED_SQUARE;
}

bool isPawn(wchar_t chessBoard[N][N], int row, int col) {
    return chessBoard[row][col] == BLACK_PAWN || chessBoard[row][col] == getWhiteIcon(BLACK_PAWN);
}

bool isHorse(wchar_t chessBoard[N][N], int row, int col) {
    return chessBoard[row][col] == BLACK_HORSE || chessBoard[row][col] == getWhiteIcon(BLACK_HORSE);
}

bool isBishop(wchar_t chessBoard[N][N], int row, int col) {
    return chessBoard[row][col] == BLACK_BISHOP || chessBoard[row][col] == getWhiteIcon(BLACK_BISHOP);
}

bool isTower(wchar_t chessBoard[N][N], int row, int col) {
    return chessBoard[row][col] == BLACK_TOWER || chessBoard[row][col] == getWhiteIcon(BLACK_TOWER);
}

bool isKing(wchar_t chessBoard[N][N], int row, int col) {
    return chessBoard[row][col] == BLACK_KING || chessBoard[row][col] == getWhiteIcon(BLACK_KING);
}

bool isQueen(wchar_t chessBoard[N][N], int row, int col) {
    return chessBoard[row][col] == BLACK_QUEEN || chessBoard[row][col] == getWhiteIcon(BLACK_QUEEN);
}

bool isBlack(wchar_t chessBoard[N][N], int row, int col) {
    return chessBoard[row][col] >= BLACK_QUEEN && chessBoard[row][col] <= BLACK_PAWN;
}

bool isEqualColor(wchar_t chessBoard[N][N], int row1, int col1, int row2, int col2) {
    return 
        !isFreePosition(chessBoard, row2, col2) && (
        (isBlack(chessBoard, row1, col1) && isBlack(chessBoard, row2, col2)) ||
        (!isBlack(chessBoard, row1, col1) && !isBlack(chessBoard, row2, col2))
    );
}

bool isBlackPawnDiaogonalMove(wchar_t chessBoard[N][N], int row1, int col1, int row2, int col2) {
    return !isFreePosition(chessBoard, row2, col2) && (row1 + col1 - 2 == row2 + col2 || row1 + col1 == row2 + col2);
}

bool isWhitePawnDiaogonalMove(wchar_t chessBoard[N][N], int row1, int col1, int row2, int col2) {
    return !isFreePosition(chessBoard, row2, col2) && (row1 + col1 + 2 == row2 + col2 || row1 + col1 == row2 + col2);
}

bool isHorseMovement(int row1, int col1, int row2, int col2) {
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

bool isBishopMovement(int row1, int col1, int row2, int col2) {
    return (row1 + col1  - row2 + col2) % 2 == 0 && row1 != row2 && col1 != col2;
}

bool isTowerMovement(int row1, int col1, int row2, int col2) {
    return 
        (row2 > row1 && col1 == col2) ||
        (row1 == row2 && col1 > col2) ||
        (row2 < row1 && col1 == col2) ||
        (row1 == row2 && col1 < col2);
}

bool isKingMovement(int row1, int col1, int row2, int col2) {
    return true;
}

bool isQueenMovement(int row1, int col1, int row2, int col2) {
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
    int
        i = 0,
        j = 0;
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            if (isPawnPosition(i))
                chessBoard[i][j] = isBlackPosition(i) ? BLACK_PAWN : getWhiteIcon(BLACK_PAWN);
            if (isBishopPosition(i, j))
                chessBoard[i][j] = isBlackPosition(i) ? BLACK_BISHOP : getWhiteIcon(BLACK_BISHOP);
            if (isHorsePosition(i, j))
                chessBoard[i][j] = isBlackPosition(i) ? BLACK_HORSE : getWhiteIcon(BLACK_HORSE);
            if (isTowerPosition(i, j))
                chessBoard[i][j] = isBlackPosition(i) ? BLACK_TOWER : getWhiteIcon(BLACK_TOWER);
            if (isKingPosition(i, j))
                chessBoard[i][j] = isBlackPosition(i) ? BLACK_KING : getWhiteIcon(BLACK_KING);
            if (isQueenPosition(i, j))
                chessBoard[i][j] = isBlackPosition(i) ? BLACK_QUEEN : getWhiteIcon(BLACK_QUEEN);
            if (isEmptyPosition(i))
                chessBoard[i][j] = isEmptySquarePosition(i, j) ? EMPTY_SQUARE : FILLED_SQUARE;
        }
    }
}

bool move(wchar_t chessBoard[N][N], int row1, int col1, int row2, int col2) {
    wchar_t temp = chessBoard[row2][col2];
    if(temp != FILLED_SQUARE && temp != EMPTY_SQUARE)
        wprintf(L"\nHai mangiato!\n");
    chessBoard[row2][col2] = chessBoard[row1][col1];
    chessBoard[row1][col1] = isEmptySquarePosition(row1, col1) ? EMPTY_SQUARE : FILLED_SQUARE;
    return temp == BLACK_QUEEN || temp == getWhiteIcon(BLACK_QUEEN);
}

int setCoordinate(int x) {
    if(x < 0)
        return 0;
    else if(x > N - 1)
        return N - 1;
    else 
        return x;
}

bool playerTurn(wchar_t chessBoard[N][N], int row1, int col1) {
    int
        row2 = 0,
        col2 = 0;
    bool 
        badMove = false,
        hasWin = false;
    do { 
        wprintf(L"\nInserisci la riga dove vuoi arrivare: ");
        scanf("%d", & row2);
        wprintf(L"\nInserisci la colonna dove vuoi arrivare: ");
        scanf("%d", & col2);
        row2 = setCoordinate(row2);
        col2 = setCoordinate(col2);
        wprintf(L"\nPosizione di arrivo: %lc ; (%d, %d)\n", chessBoard[row2][col2], row2, col2);
        if (isPawn(chessBoard, row1, col1)) {
            if (isBlack(chessBoard, row1, col1)) {
                if (row1 == N - 2) {
                    if(isFreePosition(chessBoard, row2, col2)) {
                        if((row2 == row1 - 1 || row2 == row1 - 2) && col1 == col2) {
                            badMove = false;
                            move(chessBoard, row1, col1, row2, col2);
                        } else {
                            badMove = true;
                            wprintf(L"\nMossa non valida (pedone nero frontale)\n");
                        }
                    } else {
                        if(isBlackPawnDiaogonalMove(chessBoard, row1, col1, row2, col2)) {
                            badMove = false;
                            hasWin = move(chessBoard, row1, col1, row2, col2);   
                        } else {
                            badMove = true;
                            wprintf(L"\nMossa non valida (pedone nero diagonale)\n");
                        }
                    }  
                } else {
                    if(isFreePosition(chessBoard, row2, col2)) {
                        if(row2 == row1 - 1 && col1 == col2) {
                            badMove = false;
                            move(chessBoard, row1, col1, row2, col2);
                        } else {
                            badMove = true;
                            wprintf(L"\nMossa non valida (pedone nero frontale)\n");   
                        }
                    } else {
                        if(isBlackPawnDiaogonalMove(chessBoard, row1, col1, row2, col2)) {
                            badMove = false;
                            hasWin = move(chessBoard, row1, col1, row2, col2);   
                        } else {
                            badMove = true;
                            wprintf(L"\nMossa non valida (pedone nero diagonale)\n");
                        }
                    }
                }
            } else {
                if (row1 == 1) {
                    if(isFreePosition(chessBoard, row2, col2)) {
                        if((row2 == row1 + 1 || row2 == row1 + 2) && col1 == col2) {
                            badMove = false;
                            move(chessBoard, row1, col1, row2, col2);
                        } else {
                            badMove = true;
                            wprintf(L"\nMossa non valida (pedone bianco frontale)\n");
                        }
                    } else {
                       if(isWhitePawnDiaogonalMove(chessBoard, row1, col1, row2, col2)) {
                            badMove = false;
                            hasWin = move(chessBoard, row1, col1, row2, col2);   
                        } else {
                            badMove = true;
                            wprintf(L"\nMossa non valida (pedone bianco diagonale)\n");
                        }  
                    }
                } else {
                    if(isFreePosition(chessBoard, row2, col2)) {
                        row2 == row1 + 1 && col1 == col2 ?
                            move(chessBoard, row1, col1, row2, col2) : 
                            wprintf(L"\nMossa non valida (pedone bianco frontale)\n");
                    } else {
                        if(isWhitePawnDiaogonalMove(chessBoard, row1, col1, row2, col2)) {
                            badMove = false;
                            hasWin = move(chessBoard, row1, col1, row2, col2);   
                        } else {
                            badMove = true;
                            wprintf(L"\nMossa non valida (pedone bianco diagonale)\n");
                        }
                    }
                }
            }
        }
        if (isHorse(chessBoard, row1, col1)) {
            if(isBlack(chessBoard, row1, col1)) {
                if(isHorseMovement(row1, col1, row2, col2)) {
                    if(isFreePosition(chessBoard, row2, col2) || !isEqualColor(chessBoard, row1, col1, row2, col2)) {
                       badMove = false;
                       hasWin = move(chessBoard, row1, col1, row2, col2);
                    } else {
                        badMove = true;
                        wprintf(L"\nMossa non valida (cavallo nero)\n");  
                    }
                } else {
                    badMove = true;
                    wprintf(L"\nMossa non valida (cavallo nero)\n");
                }
            } else {
                if(isHorseMovement(row1, col1, row2, col2)) {
                    if(isFreePosition(chessBoard, row2, col2) || !isEqualColor(chessBoard, row1, col1, row2, col2)) {
                        badMove = false;
                        hasWin = move(chessBoard, row1, col1, row2, col2);
                    } else {
                        badMove = true;
                        wprintf(L"\nMossa non valida (cavallo bianco)\n");  
                    }
                } else {
                    badMove = true;
                    wprintf(L"\nMossa non valida (cavallo bianco)\n");
                }
            }
        }
        if (isBishop(chessBoard, row1, col1)) {
            if(isBlack(chessBoard, row1, col1)) {
                if(isBishopMovement(row1, col1, row2, col2)) {
                    if(isFreePosition(chessBoard, row2, col2) || !isEqualColor(chessBoard, row1, col1, row2, col2)) {
                        badMove = false;
                        hasWin = move(chessBoard, row1, col1, row2, col2);
                    } else {
                        badMove = true;
                        wprintf(L"\nMossa non valida (alfiere nero)\n");   
                    }
                } else {
                    badMove = true;
                    wprintf(L"\nMossa non valida (alfiere nero)\n");
                }
        } else {
                if(isBishopMovement(row1, col1, row2, col2)) {
                    if(isFreePosition(chessBoard, row2, col2) || !isEqualColor(chessBoard, row1, col1, row2, col2)) {
                        badMove = false;
                        hasWin = move(chessBoard, row1, col1, row2, col2);
                    } else {
                        badMove = true;
                        wprintf(L"\nMossa non valida (alfiere bianco)\n");
                    }
                } else {
                    badMove = true;
                    wprintf(L"\nMossa non valida (alfiere bianco)\n");
                }
            }
        }
        if (isTower(chessBoard, row1, col1)) {
            if(isBlack(chessBoard, row1, col1)) {
                if(isTowerMovement(row1, col1, row2, col2) && !isEqualColor(chessBoard, row1, col1, row2, col2)) {
                    badMove = false;
                    if(row1 > row2 && col1 == col2) {
                        wprintf(L"su");
                        hasWin = move(chessBoard, row1, col1, row2, col2);
                    } else if(row1 < row2 && col1 == col2) {
                        wprintf(L"giu");
                        hasWin = move(chessBoard, row1, col1, row2, col2);
                    } else if(row1 == row2 && col1 > col2) {
                        wprintf(L"dx");
                        hasWin = move(chessBoard, row1, col1, row2, col2);
                    } else if(row1 == row2 && col1 < col2) {
                        wprintf(L"sx");
                        hasWin = move(chessBoard, row1, col1, row2, col2);
                    }
                } else {
                    badMove = true;
                    wprintf(L"\nMossa non valida (torre nera)\n");
                }
            } else {
                if(isTowerMovement(row1, col1, row2, col2) && !isEqualColor(chessBoard, row1, col1, row2, col2)) {
                    badMove = false;
                    if(row1 > row2 && col1 == col2) {
                        hasWin = move(chessBoard, row1, col1, row2, col2);
                    } else if(row1 < row2 && col1 == col2) {
                        hasWin = move(chessBoard, row1, col1, row2, col2);
                    } else if(row1 == row2 && col1 > col2) {
                        hasWin = move(chessBoard, row1, col1, row2, col2);
                    } else if(row1 == row2 && col1 < col2) {
                        hasWin = move(chessBoard, row1, col1, row2, col2);
                    }
                } else {
                    badMove = true;
                    wprintf(L"\nMossa non valida (torre bianca)\n");
                }
            }
        }
        if (isKing(chessBoard, row1, col1)) {
            if(isBlack(chessBoard, row1, col1)) {
                if(isKingMovement(row1, col1, row2, col2) && !isEqualColor(chessBoard, row1, col1, row2, col2)) {
                    badMove = false;
                    hasWin = move(chessBoard, row1, col1, row2, col2);
                } else {
                    badMove = true;
                    wprintf(L"\nMossa non valida (Re nero)\n");
                }
            } else {
                
            }
        }
        if (isQueen(chessBoard, row1, col1)) {
            if(isBlack(chessBoard, row1, col1)) {
                if(isQueenMovement(row1, col1, row2, col2) && !isEqualColor(chessBoard, row1, col1, row2, col2)) {
                    badMove = false;
                    hasWin = move(chessBoard, row1, col1, row2, col2);
                } else {
                    badMove = true;
                    wprintf(L"\nMossa non valida (Regina nera)\n");
                }
            } else {
                
            }
        }
    } while(badMove);
    return hasWin;
}

int main(void) {
    setlocale(LC_ALL, "");
    bool 
        hasWin = false,
        isFreePos = true;
    int
        row1 = 0,
        col1 = 0,
        player = 1,
        contaMosse = 1;
    wchar_t chessBoard[N][N];
    defineChessBoardMatrix(chessBoard);
    //chessBoard[5][5] = BLACK_QUEEN;
    while(!hasWin) {
        while(isFreePos) {
            wprintf(L"\nMossa %d:\n", contaMosse);
            printMatrix(chessBoard);
            wprintf(L"\n \nInserisci la riga attuale: ");
            scanf("%d", & row1);
            wprintf(L"\nInserisci la colonna attuale: ");
            scanf("%d", & col1);
            row1 = setCoordinate(row1);
            col1 = setCoordinate(col1);
            if(!isFreePosition(chessBoard, row1, col1))
                isFreePos = false;
            else
                wprintf(L"\nPosizione vuota, riprova.\n");
        }
        isFreePos = true;
        wprintf(L"\nPosizione di partenza: %lc ; colore: %ls ; (%d, %d)\n", chessBoard[row1][col1], isBlack(chessBoard, row1, col1) ? L"nero" : L"bianco", row1, col1);
        hasWin = playerTurn(chessBoard, row1, col1);
        contaMosse++;
    }
    system("tput bel");
    printMatrix(chessBoard);
    wprintf(L"\n \nVincitore: %d", player);
    return EXIT_SUCCESS;
}