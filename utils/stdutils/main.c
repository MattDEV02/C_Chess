#include "main.h"


const time_t getCurrentDateTime(bool isStartTime) {
    const size_t bufferDim = 30;
    char dateTimeStringBuffer[bufferDim];
    const time_t now = time(NULL);
    struct tm* restrict time_info = localtime(&(now));
    time_info->tm_hour += 1; 
    strftime(dateTimeStringBuffer, bufferDim, "%Y-%m-%d %H:%M:%S", time_info);
    wprintf(L"\nGame %ls time = %s\n", isStartTime ? L"start" : L"end", dateTimeStringBuffer);
    return now;
}

short shortReader(short integer, wchar_t* prompt) {
	wprintf(prompt);
	scanf("%hu", &(integer));
	return integer;
}

unsigned short setCoordinate(int x) {
    if(x < 0)
        return 0;
    else if(x > N - 1)
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
	for(; i < times; i++)
		system("tput bel");
}