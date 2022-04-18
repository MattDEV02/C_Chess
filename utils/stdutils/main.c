#include "main.h"
#include "../chessboard/main.h"


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
	FILE *fp = fopen("static/chessBoardArchive.dat", "ab");
	fwrite(chessBoard, sizeof(ChessBoard), 1, fp);
	fclose(fp);
}

void saveChessBoardGames(unsigned short winner, unsigned short movesCounter) {
	FILE *fp = fopen(txtFname, "a");
	fprintf(
		fp,
		"Winner: player number %i (%ls) with %i moves.\n",
		winner,
		winner == 1 ? L"white" : L"black",
		movesCounter);
	fclose(fp);
}

void readChessBoardArchive() {
	FILE *fp = fopen(binFname, "rb");
	if (fp != NULL) {
		unsigned short i = 0;
		const int rowNum = getFileDim();
		wchar_t chessBoard[N][N];
		for(i = 0; i < rowNum; i++) {
			fread(chessBoard, sizeof(wchar_t [N][N]), 1, fp);
			printChessBoardN(chessBoard);
		}
	}
	fclose(fp);
}

void readChessBoardGames() {
	const int rowDim = 50;
	FILE *fp = fopen(txtFname, "r");
	if (fp != NULL) {
		wprintf(L"%d Games history archive: \n \n", getFileDim());
		char row[rowDim];
		while (fgets(row, rowDim, fp))
			wprintf(L"%s\n", row);
	}
	fclose(fp);
}