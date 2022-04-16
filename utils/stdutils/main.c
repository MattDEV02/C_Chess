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

void saveChessBoard(ChessBoard chessBoard) {
	FILE *fp = fopen("static/chessBoardArchive.dat", "ab");
	fwrite(chessBoard, sizeof(chessBoard), 1, fp);
	fclose(fp);
}

void saveChessBoardGames(unsigned short winner, unsigned short movesCounter) {
	FILE *fp = fopen("static/chessBoardGames.txt", "a");
	fprintf(
		fp,
		"Winner: player number %i (%ls) with %i moves.\n",
		winner,
		winner == 1 ? L"white" : L"black",
		movesCounter);
	fclose(fp);
}

void readChessBoardArchive() {
	FILE *fp = fopen("static/chessBoardArchive.dat", "rb");
	if (fp != NULL) {
		unsigned short i = 0;
		wchar_t row[N];
		ChessBoard chessBoard;
		for (i = 0; i < N; i++) {
			while (fgetws(row, N * N, fp)) {
			}
		}
		fclose(fp);
		//printChessBoard(chessBoard);
	}
}

void readChessBoardGames() {
	const int rowDim = 50;
	FILE *fp = fopen("static/chessBoardGames.txt", "r");
	if (fp != NULL) {
		wprintf(L"Games history archive: \n \n");
		char row[rowDim];
		while (fgets(row, rowDim, fp))
			wprintf(L"%s\n", row);
        wprintf(L"\n");
	}
}