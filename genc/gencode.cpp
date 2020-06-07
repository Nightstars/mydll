#include "pch.h"
#include "gencode.h"
#include <cstdio>
#include <string>
using namespace std;

int q_rcnum(const char** parm, char* result)
{
	FILE* fpw;
	fpw = fopen(*(parm + 0), "w");
	if (fpw == NULL) {
		result=const_cast<char *>("打开文件时发生错误");
		return 0;
	}
	//write file
	for (int i = 0; i < atoi(*(parm + 1)); i++)
	{
		fputs(*(parm + i), fpw);
	}
	//close file
	fclose(fpw);
	return 1;
}