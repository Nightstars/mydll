#include "pch.h"
#include "utils.h"
#include <vector>
#include <string>
#include <comutil.h>
#include <iostream>

using namespace std;
#pragma warning(disable : 4996)

int split(char* src, const char* separator, char** dest, int* num) {
	char* pNext;
	int count = 0;
	if (src == NULL || strlen(src) == 0)
		return 0;
	if (separator == NULL || strlen(separator) == 0)
		return 0;
	pNext = strtok(src, separator);
	while (pNext != NULL) {
		*dest++ = pNext;
		++count;
		pNext = strtok(NULL, separator);
	}
	*num = count;
	return 1;
}
