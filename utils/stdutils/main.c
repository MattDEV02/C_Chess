#include "main.h"


const time_t getCurrentDateTime(bool isStartTime) {
	const size_t bufferDim = 30;
	char dateTimeStringBuffer[bufferDim];
	const time_t now = time(NULL);
	struct tm *restrict time_info = localtime(&(now));
	time_info->tm_hour += 1;
	strftime(dateTimeStringBuffer, bufferDim, "%Y-%m-%d %H:%M:%S", time_info);
	wprintf(
		L"\nGame %ls time = %s\n",
		isStartTime ? L"start" : L"end",
		dateTimeStringBuffer);
	return now;
}

short shortReader(short integer, wchar_t *prompt) {
	wprintf(prompt);
	scanf("%hu", &(integer));
	return integer;
}

unsigned short setCoordinate(int x) {
	if (x < 0)
		return 0;
	else if (x > N - 1)
		return N - 1;
	else
		return x;
}

const short sabs(short value) {
	return value >= 0 ? value : (-1 * value);
}

const double dabs(double value) {
	return value >= 0.0 ? value : (-1.0 * value);
}

void sound(unsigned short times) {
	unsigned short i = 0;
	for (; i < times; i++)
		system("tput bel");
}

char txtFname[] = "static/chessBoardGames.txt";

char binFname[] = "static/chessBoardArchive.dat";

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

void printChessBoardN(wchar_t chessBoard[N][N]) {
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


unsigned int getFileDim() {
	int rowNum = 0;
	FILE* fp = fopen(txtFname, "r");
	if(fp != NULL) {
		const unsigned short rowDim = 50;
		char row[rowDim];
		while(fgets(row, rowDim, fp)) 
		rowNum++;
	}
	fclose(fp);
	return rowNum;
}

void saveChessBoard(ChessBoard chessBoard) { 
	FILE *fp = fopen(binFname, "ab");
    unsigned short 
		i = 0, 
		j = 0;
	wchar_t temp[N][N];
	for(i = 0; i < N; i++) {
		for(j = 0; j < N; j++) 
			temp[i][j] = chessBoard[i][j];
	}
	fwrite(temp, sizeof(wchar_t [N][N]), 1, fp);
	fclose(fp);
}

void saveChessBoardGames(unsigned short winner, unsigned short movesCounter) {
	FILE *fp = fopen(txtFname, "a");
	fprintf(
		fp,
		"Winner: player number %i (%ls) with %i moves (%s).\n",
		winner,
		winner == 1 ? L"white" : L"black",
		movesCounter,
		"");
	fclose(fp);
}

void readChessBoardArchive() {
	FILE *fp = fopen(binFname, "rb");
	if (fp != NULL) {
		wchar_t temp[N][N];
		while(fread(temp, sizeof(wchar_t [N][N]), 1, fp) > 0)
			printChessBoardN(temp);
	}
	fclose(fp);
    wprintf(L"\n");
}

void readChessBoardGames() {
	const int rowDim = 70; // single row dimension (in chars)
	FILE *fp = fopen(txtFname, "r");
	if (fp != NULL) {
		wprintf(L"%d games history archive: \n \n", getFileDim());
		char row[rowDim];
		while (fgets(row, rowDim, fp))
			wprintf(L"%s\n", row);
	}
	fclose(fp);
}