#include <stdlib.h>
#include "../stdutils/main.h"
#include "../icons/main.h"
#include "../movements/main.h"
#include "../positions/main.h"
#include "main.h"


wchar_t getWhiteIcon(wchar_t black_icon) {
    return black_icon + COLOR_DELTA;
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
    return (icon >= BLACK_QUEEN && icon <= BLACK_PAWN) && !isFreePosition(icon);
}

bool isEqualColor(wchar_t icon1, wchar_t icon2) {
    return 
        (!isFreePosition(icon1) && !isFreePosition(icon2)) && (  
        (isBlack(icon1) && isBlack(icon2)) ||
        (!isBlack(icon1) && !isBlack(icon2))
    );
}

void printIconStringName(wchar_t icon) { 
    if(isPawn(icon))
        wprintf(L"icon name = Pawn.\n");
    else if(isHorse(icon))
        wprintf(L"icon name = Horse.\n");
    else if(isBishop(icon))
        wprintf(L"icon name = Bishop.\n");
    else if(isTower(icon))
        wprintf(L"icon name = Tower.\n");
    else if(isKing(icon))
        wprintf(L"icon name = King.\n");
    else if(isQueen(icon))
        wprintf(L"icon name = Queen.\n");
    else if(isFreePosition(icon))
        wprintf(L"icon name = Empty pos.\n");
    else {
        wprintf(L"\n \nNot valid icon !\n \n");
        exit(EXIT_FAILURE);
    }
}

void pawnTransition(wchar_t chessBoard[N][N], Point *p, bool isBlack) {
	short pawnChoice = 0;
	sound(6);
	wprintf(L"\nScegli in cosa vuoi trasformare il pedone: \n");
	wprintf(L"\n \n   0: King. \n \n   1: Tower. \n \n   2: Horse. \n \n   3: Bishop.\n \n");
	scanf("%hu", &(pawnChoice));
	if(pawnChoice < 0)
		pawnChoice = 0;
	else if(pawnChoice > 3)
		pawnChoice = 3;
	switch(pawnChoice) {
		case 0: {
			chessBoard[p->row][p->col] = isBlack ? BLACK_KING : getWhiteIcon(BLACK_KING);
			break;
		};
		case 1: {
			chessBoard[p->row][p->col] = isBlack ? BLACK_TOWER : getWhiteIcon(BLACK_TOWER);
			break;
		};
		case 2: {
			chessBoard[p->row][p->col] = isBlack ? BLACK_HORSE : getWhiteIcon(BLACK_HORSE);
			break;
		};
		case 3: {
			chessBoard[p->row][p->col] = isBlack ? BLACK_BISHOP : getWhiteIcon(BLACK_BISHOP);
			break;
		};
		default: {
			wprintf(L"\n \nNot valid pawn transition !\n \n");
			exit(EXIT_FAILURE);
			break;
		};
	}
	const wchar_t newIcon = chessBoard[p->row][p->col];
	wprintf(L"\nScelta: %lc  ; (%i, %i) ; ", newIcon, p->row, p->col);
	printIconStringName(newIcon);
}

const unsigned short countBlackIcons(wchar_t chessBoard[N][N]) {
	unsigned short
		i = 0,
		j = 0,
		count = 0;
	wchar_t icon;
	for(i = 0; i < N; i++) {
		for(j = 0; j < N; j++) {
			icon = chessBoard[i][j];
			if(isBlack(icon) && !isFreePosition(icon))
				count++;	
		}
	}
	return count;
}

const unsigned short countWhiteIcons(wchar_t chessBoard[N][N]) {
	unsigned short
		i = 0,
		j = 0,
		count = 0;
	wchar_t icon;
	for(i = 0; i < N; i++) {
		for(j = 0; j < N; j++) {
			icon = chessBoard[i][j];
			if(!isBlack(icon) && !isFreePosition(icon))
				count++;	
		}
	}
	return count;
}

const float iconPercentage(unsigned short remainingIcons) {
	const float totalColorIcons = (float)(2 * N);
	remainingIcons = (float)(remainingIcons);
	return ((totalColorIcons - remainingIcons) / totalColorIcons) * 100.0; 
}