#include "main.h"


const time_t getCurrentDateTime(bool isStartTime) {
	const size_t bufferDim = 30;
	char dateTimeStringBuffer[bufferDim];
	const time_t now = time(NULL);
	struct tm *restrict time_info = localtime(&(now));
	time_info->tm_hour += 2;
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
	unsigned int rowNum = 0;
	FILE* fp = fopen(txtFname, "r");
	if(fp != NULL) {
		char row[70];
		while(fgets(row, sizeof(row), fp) ) 
			rowNum++;
	} 
	fclose(fp);
	return rowNum / 1;
}

void saveChessBoard(ChessBoard chessBoard) { 
	FILE *fp = fopen(binFname, "ab");
	if(fp != NULL) {
		unsigned short 
		i = 0, 
		j = 0;
		wchar_t temp[N][N];
		for(i = 0; i < N; i++) {
			for(j = 0; j < N; j++) 
				temp[i][j] = chessBoard[i][j];
		}
		fwrite(temp, sizeof(wchar_t [N][N]), 1, fp);	
	}
	fclose(fp);
}

void saveChessBoardGames(unsigned short winner, unsigned short movesCounter) {
	FILE *fp = fopen(txtFname, "a");
	if(fp != NULL) {
		time_t t = time(NULL);
  		struct tm tm = *localtime(&t);
		fprintf(
			fp,
			"Winner: player number %i (%ls) with %i moves (%d-%02d-%02d %02d:%02d:%02d).\n",
			winner,
			winner == 1 ? L"white" : L"black",
			movesCounter,
			tm.tm_mday, 
			tm.tm_mon + 1,
			tm.tm_year + 1900, 
			tm.tm_hour + 2, 
			tm.tm_min, 
			tm.tm_sec
		);
		fclose(fp);	
	}
}

void readChessBoardArchive() {
	FILE *fp = fopen(binFname, "rb");
	if (fp != NULL) {
		unsigned int i = 1;
		wchar_t temp[N][N];
		while(fread(temp, sizeof(wchar_t [N][N]), 1, fp) > 0) {
			wprintf(L"%d )", i);
			printChessBoardN(temp);
			i++;
		}
	}
	fclose(fp);
    wprintf(L"\n");
}

void readChessBoardGames() {
	FILE *fp = fopen(txtFname, "r");
	if (fp != NULL) {
		wprintf(L"%d games in the historical archive: \n \n", getFileDim());
		char row[70];
		while (fgets(row, sizeof(row), fp))
			wprintf(L"%s\n", row);
	}
	wprintf(L"\n");
	fclose(fp);
}