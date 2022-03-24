#include "../stdutils/main.h"
#include "../positions/main.h"
#include "../icons/main.h"
#include "../movements/main.h"
#include "main.h"


void defineChessBoardMatrix(ChessBoard chessBoard) {
    unsigned short
        i = 0,
        j = 0;
	Point p;
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
			p.row = i;
			p.col = j;
            if (isPawnPosition(i))
                chessBoard[i][j] = isBlackPosition(i) ? BLACK_PAWN : getWhiteIcon(BLACK_PAWN);
            else if (isBishopPosition(&(p)))
                chessBoard[i][j] = isBlackPosition(i) ? BLACK_BISHOP : getWhiteIcon(BLACK_BISHOP);
            else if (isHorsePosition(&(p)))
                chessBoard[i][j] = isBlackPosition(i) ? BLACK_HORSE : getWhiteIcon(BLACK_HORSE);
            else if (isTowerPosition(&(p)))
                chessBoard[i][j] = isBlackPosition(i) ? BLACK_TOWER : getWhiteIcon(BLACK_TOWER);
            else if (isKingPosition(&(p)))
                chessBoard[i][j] = isBlackPosition(i) ? BLACK_KING : getWhiteIcon(BLACK_KING);
            else if (isQueenPosition(&(p)))
                chessBoard[i][j] = isBlackPosition(i) ? BLACK_QUEEN : getWhiteIcon(BLACK_QUEEN);
            else if (isEmptyPosition(i))
                defineSquare(chessBoard, &(p));
        }
    }
}

/* 
    SPECIFICS:
        * Description: function that, given as input a (8 * 8) wchar_t matrix and 2 points (coordinates of start and finish), allows one of the two players in the chess game to take his turns.
        * Input: a (8 * 8) wchar_t matrix, the memory address of a Point (row, col), and the memory addresses of 2 boolean flags.
        * Pre-condition: chessBoard must is a wchar_t (8 * 8) matrix, Point row and Point col between 0 and 7 (integers).
        * Output: a boolean value named "hasWin".
        * Post-condition: hasWin holds true if a player eats the opponent's queen.
*/
bool playerTurn(ChessBoard chessBoard, Point* p1, bool* isBlackCastlingPossible, bool* isWhiteCastlingPossible) {
    short
        row2 = 0,
        col2 = 0,
        i = 0,
        j = 0;
    bool 
        badMove = false,
        hasWin = false;
    do { 
        if(badMove)
            printChessBoard(chessBoard);
        wprintf(L"\nInserisci la riga dove vuoi arrivare: ");
        scanf("%hu", &(row2));
        wprintf(L"\nInserisci la colonna dove vuoi arrivare: ");
        scanf("%hu", &(col2));
        row2 = setCoordinate(row2);
        col2 = setCoordinate(col2);
		Point p2;
		p2.row = row2;
		p2.col = col2;
        wprintf(L"\nPosizione di arrivo: %lc ; (%i, %i) ==> (%i, %i) ; ", chessBoard[p2.row][p2.col], p1->row, p1->col, p2.row, p2.col);
        printIconStringName(chessBoard[p2.row][p2.col]);
        if(isPawn(chessBoard[p1->row][p1->col])) {
            if (isBlack(chessBoard[p1->row][p1->col])) {
                if (p1->row == N - 2) {
                    if(isFreePosition(chessBoard[p2.row][p2.col])) {
                        if((p2.row == p1->row - 1 || p2.row == p1->row - 2) && p1->col == p2.col) {
                            badMove = false;
                            hasWin = move(chessBoard, p1, &(p2));
                        } else {
                            badMove = true;
                            wprintf(L"\nMossa non valida (pedone nero), riprova.\n");
                        }
                    } else {
                        if(isBlackPawnDiaogonalMovement(chessBoard, p1, &(p2)) && !isEqualColor(chessBoard[p1->row][p1->col], chessBoard[p2.row][p2.col])) {
                            badMove = false;
                            hasWin = move(chessBoard, p1, &(p2));   
                        } else {
                            badMove = true;
                            wprintf(L"\nMossa non valida (pedone nero), riprova.\n");
                        }
                    }  
                } else {
                    if(isFreePosition(chessBoard[p2.row][p2.col])) {
                        if(p2.row == p1->row - 1 && p1->col == p2.col) {
                            badMove = false;
                            hasWin = move(chessBoard, p1, &(p2));
                        } else {
                            badMove = true;
                            wprintf(L"\nMossa non valida (pedone nero), riprova.\n");   
                        }
                    } else {
                        if(isBlackPawnDiaogonalMovement(chessBoard, p1, &(p2)) && !isEqualColor(chessBoard[p1->row][p1->col], chessBoard[p2.row][p2.col])) {
                            badMove = false;
                            hasWin = move(chessBoard, p1, &(p2));   
                        } else {
                            badMove = true;
                            wprintf(L"\nMossa non valida (pedone nero), riprova.\n");
                        }
                    }
                }
            } else {
                if (p1->row == 1) {
                    if(isFreePosition(chessBoard[p2.row][p2.col])) {
                        if((p2.row == p1->row + 1 || p2.row == p1->row + 2) && p1->col == p2.col) {
                            badMove = false;
                            hasWin = move(chessBoard, p1, &(p2));
                        } else {
                            badMove = true;
                            wprintf(L"\nMossa non valida (pedone bianco), riprova.\n");
                        }
                    } else {
                        if(isWhitePawnDiaogonalMovement(chessBoard, p1, &(p2)) && !isEqualColor(chessBoard[p1->row][p1->col], chessBoard[p2.row][p2.col])) {
                            badMove = false;
                            hasWin = move(chessBoard, p1, &(p2));   
                        } else {
                            badMove = true;
                            wprintf(L"\nMossa non valida (pedone bianco), riprova.\n");
                        }
                    }  
                } else {
                    if(isFreePosition(chessBoard[p2.row][p2.col])) {
                        if(p2.row == p1->row + 1 && p1->col == p2.col) {
                            badMove = false;
                            hasWin = move(chessBoard, p1, &(p2));
                        } else {
                            badMove = true;
                            wprintf(L"\nMossa non valida (pedone bianco), riprova.\n");   
                        }
                    } else {
                        if(isWhitePawnDiaogonalMovement(chessBoard, p1, &(p2)) && !isEqualColor(chessBoard[p1->row][p1->col], chessBoard[p2.row][p2.col])) {
                            badMove = false;
                            hasWin = move(chessBoard, p1, &(p2));   
                        } else {
                            badMove = true;
                            wprintf(L"\nMossa non valida (pedone bianco), riprova.\n");
                        }
                    }
                }
            }
        }
        if(isHorse(chessBoard[p1->row][p1->col])) {
            if(isBlack(chessBoard[p1->row][p1->col])) {
                if(isHorseMovement(p1, &(p2))) {
                    if(isFreePosition(chessBoard[p2.row][p2.col]) || !isEqualColor(chessBoard[p1->row][p1->col], chessBoard[p2.row][p2.col])) {
                       badMove = false;
                       hasWin = move(chessBoard, p1, &(p2));
                    } else {
                        badMove = true;
                        wprintf(L"\nMossa non valida (cavallo nero), riprova.\n");  
                    }
                } else {
                    badMove = true;
                    wprintf(L"\nMossa non valida (cavallo nero), riprova.\n");
                }
            } else {
                if(isHorseMovement(p1, &(p2))) {
                    if(isFreePosition(chessBoard[p2.row][p2.col]) || !isEqualColor(chessBoard[p1->row][p1->col], chessBoard[p2.row][p2.col])) {
                        badMove = false;
                        hasWin = move(chessBoard, p1, &(p2));
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
        if(isBishop(chessBoard[p1->row][p1->col])) {
            if(isBlack(chessBoard[p1->row][p1->col])) {
                if(isBishopMovement(p1, &(p2))) {
					
                    if(isFreePosition(chessBoard[p2.row][p2.col]) || !isEqualColor(chessBoard[p1->row][p1->col], chessBoard[p2.row][p2.col])) {
						wprintf(L"Alfiere");
                        badMove = false;
                        if(p1->row > p2.row && p1->col > p2.col) {
                            for(i = p1->row - 1, j = p1->col - 1; ((i >= p2.row + 1) || (j >= p2.col + 1)) && !badMove; i--, j--) {
                                i = setCoordinate(i);
                                j = setCoordinate(j);
                                if(!isFreePosition(chessBoard[i][j])) 
                                    badMove = true;
                            } 
                            if(badMove)
                                wprintf(L"\nMossa non valida (alfiere nero sx alto), riprova.\n");   
                            else 
                                hasWin = move(chessBoard, p1, &(p2));   
                        } else if(p1->row > p2.row && p1->col < p2.col) {
                            for(i = p1->row - 1, j = p1->col + 1; ((i >= p2.row + 1) || (j < p2.col)) && !badMove; i--, j++) {
                                i = setCoordinate(i);
                                j = setCoordinate(j);
                                if(!isFreePosition(chessBoard[i][j])) 
                                    badMove = true;
                            } 
                            if(badMove)
                                wprintf(L"\nMossa non valida (alfiere nero dx alto), riprova.\n");   
                            else 
                                hasWin = move(chessBoard, p1, &(p2));  
                        } else if(p1->row < p2.row && p1->col > p2.col) {
                            for(i = p1->row + 1, j = p1->col - 1; ((i < p2.row) || (j >= p2.col + 1)) && !badMove; i++, j--) {
                                i = setCoordinate(i);
                                j = setCoordinate(j);
                                if(!isFreePosition(chessBoard[i][j])) 
                                    badMove = true;
                            } 
                            if(badMove)
                                wprintf(L"\nMossa non valida (alfiere nero sx basso), riprova.\n");   
                            else 
                                hasWin = move(chessBoard, p1, &(p2)); 
                        } else if(p1->row < p2.row && p1->col < p2.col) {
                            for(i = p1->row + 1, j = p1->col + 1; ((i < p2.row) || (j < p2.col)) && !badMove; i++, j++) {
                                i = setCoordinate(i);
                                j = setCoordinate(j);
                                if(!isFreePosition(chessBoard[i][j])) 
                                    badMove = true;
                            } 
                            if(badMove)
                                wprintf(L"\nMossa non valida (alfiere nero dx basso), riprova.\n");   
                            else 
                                hasWin = move(chessBoard, p1, &(p2));  
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
                if(isBishopMovement(p1, &(p2))) {
                    if(isFreePosition(chessBoard[p2.row][p2.col]) || !isEqualColor(chessBoard[p1->row][p1->col], chessBoard[p2.row][p2.col])) {
                        badMove = false;
                         badMove = false;
                        if(p1->row > p2.row && p1->col > p2.col) {
                            for(i = p1->row - 1, j = p1->col - 1; ((i >= p2.row + 1) || (j >= p2.col + 1)) && !badMove; i--, j--) {
                                i = setCoordinate(i);
                                j = setCoordinate(j);
                                if(!isFreePosition(chessBoard[i][j])) 
                                    badMove = true;
                            } 
                            if(badMove)
                                wprintf(L"\nMossa non valida (alfiere bianco dx basso), riprova.\n");   
                            else 
                                hasWin = move(chessBoard, p1, &(p2));   
                        } else if(p1->row > p2.row && p1->col < p2.col) {
                            for(i = p1->row - 1, j = p1->col + 1; ((i >= p2.row + 1) || (j < p2.col)) && !badMove; i--, j++) {
                                i = setCoordinate(i);
                                j = setCoordinate(j);
                                if(!isFreePosition(chessBoard[i][j])) 
                                    badMove = true;
                            } 
                            if(badMove)
                                wprintf(L"\nMossa non valida (alfiere bianco sx basso), riprova.\n");   
                            else 
                                hasWin = move(chessBoard, p1, &(p2));  
                        } else if(p1->row < p2.row && p1->col > p2.col) {
                            for(i = p1->row + 1, j = p1->col - 1; ((i < p2.row) || (j >= p2.col + 1)) && !badMove; i++, j--) {
                                i = setCoordinate(i);
                                j = setCoordinate(j);
                                if(!isFreePosition(chessBoard[i][j])) 
                                    badMove = true;
                            } 
                            if(badMove)
                                wprintf(L"\nMossa non valida (alfiere bianco dx alto), riprova.\n");   
                            else 
                                hasWin = move(chessBoard, p1, &(p2)); 
                        } else if(p1->row < p2.row && p1->col < p2.col) {
                            for(i = p1->row + 1, j = p1->col + 1; ((i < p2.row) || (j < p2.col)) && !badMove; i++, j++) {
                                i = setCoordinate(i);
                                j = setCoordinate(j);
                                if(!isFreePosition(chessBoard[i][j]))
                                    badMove = true;
                            } 
                            if(badMove)
                                wprintf(L"\nMossa non valida (alfiere bianco sx alto), riprova.\n");   
                            else 
                                hasWin = move(chessBoard, p1, &(p2));  
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
        if(isTower(chessBoard[p1->row][p1->col])) {
            if(isBlack(chessBoard[p1->row][p1->col])) {
                if(isTowerMovement(p1, &(p2)) && !isEqualColor(chessBoard[p1->row][p1->col], chessBoard[p2.row][p2.col])) {
                    if(p1->row > p2.row && p1->col == p2.col) {
                        badMove = false;
                        for(i = p1->row - 1; (i >= p2.row + 1) && !badMove; i--) {
                            if(!isFreePosition(chessBoard[i][p2.col])) 
                                badMove = true;
                        }
                        if(badMove) 
                            wprintf(L"\nMossa non valida (torre nera frontale), riprova.\n");
                        else {
							hasWin = move(chessBoard, p1, &(p2));
							*isBlackCastlingPossible = false;
						}
                    } else if(p1->row < p2.row && p1->col == p2.col) {
                        badMove = false;
                        for(i = p1->row + 1; (i < p2.row) && !badMove; i++) {
                            if(!isFreePosition(chessBoard[i][p2.col])) {
                                badMove = true;
                            }
                        }
                        if(badMove) 
                            wprintf(L"\nMossa non valida (torre nera retro), riprova.\n");
                        else { 
							hasWin = move(chessBoard, p1, &(p2));
							*isBlackCastlingPossible = false;
						}
                    } else if(p1->row == p2.row && p1->col > p2.col) {
                        badMove = false;
                        for(j = p1->col - 1; (j >= p2.col + 1) && !badMove; j--) {
                            if(!isFreePosition(chessBoard[p2.row][j])) 
                                badMove = true;
                        }
                        if(badMove) 
                            wprintf(L"\nMossa non valida (torre nera sx), riprova.\n");
                        else {
							hasWin = move(chessBoard, p1, &(p2));
							*isBlackCastlingPossible = false;
						}    
                    } else if(p1->row == p2.row && p1->col < p2.col) {
                        badMove = false;
                        for(j = p1->col + 1; (j < p2.col) && !badMove; j++) {
                            if(!isFreePosition(chessBoard[p2.row][j])) 
                                badMove = true;
                        }
                        if(badMove) 
                            wprintf(L"\nMossa non valida (torre nera dx), riprova.\n");
                        else {
							hasWin = move(chessBoard, p1, &(p2));
							*isBlackCastlingPossible = false;
						}
                    }
                } else {
                    badMove = true;
                    wprintf(L"\nMossa non valida (torre nera), riprova.\n");
                }
            } else {
                if(isTowerMovement(p1, &(p2)) && !isEqualColor(chessBoard[p1->row][p1->col], chessBoard[p2.row][p2.col])) {
                    if(p1->row > p2.row && p1->col == p2.col) {
                        badMove = false;
                        for(i = p1->row - 1; (i >= p2.row + 1) && !badMove; i--) {
                            if(!isFreePosition(chessBoard[i][p2.col])) 
                                badMove = true;
                        }
                        if(badMove) 
                            wprintf(L"\nMossa non valida (torre bianca retro), riprova.\n");
                        else {
							hasWin = move(chessBoard, p1, &(p2));
							*isWhiteCastlingPossible = false;
						}
                    } else if(p1->row < p2.row && p1->col == p2.col) {
                        badMove = false;
                        for(i = p1->row + 1; (i < p2.row) && !badMove; i++) {
                            if(!isFreePosition(chessBoard[i][p2.col])) 
                                badMove = true;
                        }
                        if(badMove) 
                            wprintf(L"\nMossa non valida (torre bianca frontale), riprova.\n");
                        else {
							hasWin = move(chessBoard, p1, &(p2));
							*isWhiteCastlingPossible = false;
						}
                    } else if(p1->row == p2.row && p1->col > p2.col) {
                        badMove = false;
                        for(j = p1->col - 1; (j >= p2.col + 1) && !badMove; j--) {
                            if(!isFreePosition(chessBoard[p2.row][j])) 
                                badMove = true;
                        }
                        if(badMove) 
                            wprintf(L"\nMossa non valida (torre bianca sx), riprova.\n");
                        else {
							hasWin = move(chessBoard, p1, &(p2));
							*isWhiteCastlingPossible = false;
						}
                    } else if(p1->row == p2.row && p1->col < p2.col) {
                        badMove = false;
                        for(j = p1->col + 1; (j < p2.col) && !badMove; j++) {
                            if(!isFreePosition(chessBoard[p2.row][j])) 
                                badMove = true;
                        }
                        if(badMove) 
                            wprintf(L"\nMossa non valida (torre bianca dx), riprova.\n");
                        else {
							hasWin = move(chessBoard, p1, &(p2));
							*isWhiteCastlingPossible = false;
						}
                    }
                } else {
                    badMove = true;
                    wprintf(L"\nMossa non valida (torre bianca), riprova.\n");
                }
            }
        }
        if(isKing(chessBoard[p1->row][p1->col])) {
            if(isBlack(chessBoard[p1->row][p1->col])) {
                if(isKingMovement(p1, &(p2)) && !isEqualColor(chessBoard[p1->row][p1->col], chessBoard[p2.row][p2.col])) {
                    badMove = false;
                    // su, giù, sx, dx.
                    if(p1->row > p2.row && p1->col == p2.col) {
                        badMove = false;
                        for(i = p1->row - 1; (i >= p2.row + 1) && !badMove; i--) {
                            if(!isFreePosition(chessBoard[i][p2.col])) 
                                badMove = true;
                        }
                        if(badMove) 
                            wprintf(L"\nMossa non valida (Re nero frontale), riprova.\n");
                        else 
                            hasWin = move(chessBoard, p1, &(p2));
                    } else if(p1->row < p2.row && p1->col == p2.col) {
                        badMove = false;
                        for(i = p1->row + 1; (i < p2.row) && !badMove; i++) {
                            if(!isFreePosition(chessBoard[i][p2.col])) 
                                badMove = true;
                        }
                        if(badMove) 
                            wprintf(L"\nMossa non valida (Re nero retro), riprova.\n");
                        else 
                            hasWin = move(chessBoard, p1, &(p2));
                    } else if(p1->row == p2.row && p1->col > p2.col) {
                        badMove = false;
                        for(j = p1->col - 1; (j >= p2.col + 1) && !badMove; j--) {
                            if(!isFreePosition(chessBoard[p2.row][j])) 
                                badMove = true;
                        }
                        if(badMove) 
                            wprintf(L"\nMossa non valida (Re nero sx), riprova.\n");
                        else 
                            hasWin = move(chessBoard, p1, &(p2));
                    } else if(p1->row == p2.row && p1->col < p2.col) {
                        badMove = false;
                        for(j = p1->col + 1; (j < p2.col) && !badMove; j++) {
                            if(!isFreePosition(chessBoard[p2.row][j])) 
                                badMove = true;
                        }
                        if(badMove) 
                            wprintf(L"\nMossa non valida (Re nero dx), riprova.\n");
                        else 
                            hasWin = move(chessBoard, p1, &(p2));
                    }
                    // diag sup-sx , diag inf-sx, diag su-dx, diag inf-dx
                    if(p1->row > p2.row && p1->col > p2.col) {
                        for(i = p1->row - 1, j = p1->col - 1; ((i >= p2.row + 1) || (j >= p2.col + 1)) && !badMove; i--, j--) {
                            i = setCoordinate(i);
                            j = setCoordinate(j);
                            if(!isFreePosition(chessBoard[i][j])) 
                                badMove = true;
                        } 
                        if(badMove)
                            wprintf(L"\nMossa non valida (Re nero sx alto), riprova.\n");   
                        else 
                            hasWin = move(chessBoard, p1, &(p2));   
                    } else if(p1->row > p2.row && p1->col < p2.col) {
                        for(i = p1->row - 1, j = p1->col + 1; ((i >= p2.row + 1) || (j < p2.col)) && !badMove; i--, j++) {
                            i = setCoordinate(i);
                            j = setCoordinate(j);
                            if(!isFreePosition(chessBoard[i][j])) 
                                badMove = true;
                        } 
                        if(badMove)
                            wprintf(L"\nMossa non valida (Re nero dx alto), riprova.\n");   
                        else 
                            hasWin = move(chessBoard, p1, &(p2));  
                    } else if(p1->row < p2.row && p1->col > p2.col) {
                        for(i = p1->row + 1, j = p1->col - 1; ((i < p2.row) || (j >= p2.col + 1)) && !badMove; i++, j--) {
                            i = setCoordinate(i);
                            j = setCoordinate(j);
                            if(!isFreePosition(chessBoard[i][j])) 
                                badMove = true;
                        } 
                        if(badMove)
                            wprintf(L"\nMossa non valida (Re nero sx basso), riprova.\n");   
                        else 
                            hasWin = move(chessBoard, p1, &(p2)); 
                    } else if(p1->row < p2.row && p1->col < p2.col) {
                        for(i = p1->row + 1, j = p1->col + 1; ((i < p2.row) || (j < p2.col)) && !badMove; i++, j++) {
                            i = setCoordinate(i);
                            j = setCoordinate(j);
                            if(!isFreePosition(chessBoard[i][j])) 
                                badMove = true;
                        } 
                        if(badMove)
                            wprintf(L"\nMossa non valida (Re nero dx basso), riprova.\n");   
                        else 
                            hasWin = move(chessBoard, p1, &(p2));  
                    }
                } else {
                    badMove = true;
                    wprintf(L"\nMossa non valida (Re nero), riprova.\n");
                }
            } else {
                if(isKingMovement(p1, &(p2)) && !isEqualColor(chessBoard[p1->row][p1->col], chessBoard[p2.row][p2.col])) {
                    // su, giù, sx, dx.
                    badMove = false;
                    if(p1->row > p2.row && p1->col == p2.col) {
                        badMove = false;
                        for(i = p1->row - 1; (i >= p2.row + 1) && !badMove; i--) {
                            if(!isFreePosition(chessBoard[i][p2.col])) 
                                badMove = true;
                        }
                        if(badMove) 
                            wprintf(L"\nMossa non valida (Re bianco retro), riprova.\n");
                        else 
                            hasWin = move(chessBoard, p1, &(p2));
                    } else if(p1->row < p2.row && p1->col == p2.col) {
                        badMove = false;
                        for(i = p1->row + 1; (i < p2.row) && !badMove; i++) {
                            if(!isFreePosition(chessBoard[i][p2.col])) 
                                badMove = true;
                        }
                        if(badMove) {
                            wprintf(L"\nMossa non valida (Re bianco frontale), riprova.\n");
                        } else 
                            hasWin = move(chessBoard, p1, &(p2));
                    } else if(p1->row == p2.row && p1->col > p2.col) {
                        badMove = false;
                        for(j = p1->col - 1; (j >= p2.col + 1) && !badMove; j--) {
                            if(!isFreePosition(chessBoard[p2.row][j])) 
                                badMove = true;
                        }
                        if(badMove) 
                            wprintf(L"\nMossa non valida (Re bianco dx), riprova.\n");
                        else 
                            hasWin = move(chessBoard, p1, &(p2));
                    } else if(p1->row == p2.row && p1->col < p2.col) {
                        badMove = false;
                        for(j = p1->col + 1; (j < p2.col) && !badMove; j++) {
                            if(!isFreePosition(chessBoard[p2.row][j])) 
                                badMove = true;
                        }
                        if(badMove) 
                            wprintf(L"\nMossa non valida (Re bianco sx), riprova.\n");
                        else 
                            hasWin = move(chessBoard, p1, &(p2));
                    }
                    // diag sup-sx , diag inf-sx, diag su-dx, diag inf-dx
                    if(p1->row > p2.row && p1->col > p2.col) {
                        for(i = p1->row - 1, j = p1->col - 1; ((i >= p2.row + 1) || (j >= p2.col + 1)) && !badMove; i--, j--) {
                            i = setCoordinate(i);
                            j = setCoordinate(j);
                            if(!isFreePosition(chessBoard[i][j])) 
                                badMove = true;
                        } 
                        if(badMove)
                            wprintf(L"\nMossa non valida (Re bianco dx basso), riprova.\n");   
                        else 
                            hasWin = move(chessBoard, p1, &(p2));   
                    } else if(p1->row > p2.row && p1->col < p2.col) {
                        for(i = p1->row - 1, j = p1->col + 1; ((i >= p2.row + 1) || (j < p2.col)) && !badMove; i--, j++) {
                            i = setCoordinate(i);
                            j = setCoordinate(j);
                            if(!isFreePosition(chessBoard[i][j])) 
                                badMove = true;
                        } 
                        if(badMove)
                            wprintf(L"\nMossa non valida (Re bianco sx basso), riprova.\n");   
                        else 
                            hasWin = move(chessBoard, p1, &(p2));  
                    } else if(p1->row < p2.row && p1->col > p2.col) {
                        for(i = p1->row + 1, j = p1->col - 1; ((i < p2.row) || (j >= p2.col + 1)) && !badMove; i++, j--) {
                            i = setCoordinate(i);
                            j = setCoordinate(j);
                            if(!isFreePosition(chessBoard[i][j])) 
                                badMove = true;
                        } 
                        if(badMove)
                            wprintf(L"\nMossa non valida (Re bianco dx alto), riprova.\n");   
                        else 
                            hasWin = move(chessBoard, p1, &(p2)); 
                    } else if(p1->row < p2.row && p1->col < p2.col) {
                        for(i = p1->row + 1, j = p1->col + 1; ((i < p2.row) || (j < p2.col)) && !badMove; i++, j++) {
                            i = setCoordinate(i);
                            j = setCoordinate(j);
                            if(!isFreePosition(chessBoard[i][j])) 
                                badMove = true;
                        } 
                        if(badMove)
                            wprintf(L"\nMossa non valida (Re bianco sx alto), riprova.\n");   
                        else 
                            hasWin = move(chessBoard, p1, &(p2));  
                    }
                } else {
                    badMove = true;
                    wprintf(L"\nMossa non valida (Re bianco), riprova.\n");
                }
            }
        }
        if(isQueen(chessBoard[p1->row][p1->col])) {
            if(isBlack(chessBoard[p1->row][p1->col])) {
                if(isQueenMovement(p1, &(p2)) && !isEqualColor(chessBoard[p1->row][p1->col], chessBoard[p2.row][p2.col])) {
					badMove = false;
                    hasWin = move(chessBoard, p1, &(p2));
					*isBlackCastlingPossible = false;
                } else if(isCastlingMovement(chessBoard, p1, &(p2)) && *isBlackCastlingPossible) {
					// arrocco nero
					badMove = false;
                    castling(chessBoard, p1, &(p2));
					*isBlackCastlingPossible = false;
					wprintf(L"\nArrocco nero eseguito !\n");
				} else {
                    badMove = true;
                    wprintf(L"\nMossa non valida (Regina nera), riprova.\n");
                }
            } else {
                if(isQueenMovement(p1, &(p2)) && !isEqualColor(chessBoard[p1->row][p1->col], chessBoard[p2.row][p2.col])) {
					badMove = false;
                    hasWin = move(chessBoard, p1, &(p2));
					*isWhiteCastlingPossible = false;
                } else if(isCastlingMovement(chessBoard, p1, &(p2)) && *isWhiteCastlingPossible) {
					// arrocco bianco
					badMove = false;
                    castling(chessBoard, p1, &(p2));
					*isWhiteCastlingPossible = false;
					wprintf(L"\nArrocco bianco eseguito !\n");
				} else {
                    badMove = true;
                    wprintf(L"\nMossa non valida (Regina bianca), riprova.\n");
                }
            }
        }   
    } while(badMove);
    return hasWin;
}