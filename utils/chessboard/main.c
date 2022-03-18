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

/* 
    SPECIFICS:
        * Description: .
        * Input: .
        * Pre-condition: .
        * Output: .
        * Post-condition: .
*/
bool playerTurn(wchar_t chessBoard[N][N], short row1, short col1) {
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
                        if(isBlackPawnDiaogonalMovement(chessBoard, row1, col1, row2, col2) && !isEqualColor(chessBoard[row1][col1], chessBoard[row2][col2])) {
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
                        if(isBlackPawnDiaogonalMovement(chessBoard, row1, col1, row2, col2) && !isEqualColor(chessBoard[row1][col1], chessBoard[row2][col2])) {
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
                        if(isWhitePawnDiaogonalMovement(chessBoard, row1, col1, row2, col2) && !isEqualColor(chessBoard[row1][col1], chessBoard[row2][col2])) {
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
                        if(isWhitePawnDiaogonalMovement(chessBoard, row1, col1, row2, col2) && !isEqualColor(chessBoard[row1][col1], chessBoard[row2][col2])) {
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