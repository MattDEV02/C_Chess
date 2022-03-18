wchar_t getWhiteIcon(wchar_t black_icon) {
    return black_icon + COLOR_DIFF;
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