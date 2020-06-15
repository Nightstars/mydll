#include "pch.h"
#include "gencode.h"
#include <cstdio>
#include <string>
#include <vector>
using namespace std;
#pragma warning(disable : 4996)

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
vector<string> split(const string& str, const string& pattern)
{
	vector<string> ret;
	if (pattern.empty()) return ret;
	size_t start = 0, index = str.find_first_of(pattern, 0);
	while (index != str.npos)
	{
		if (start != index)
			ret.push_back(str.substr(start, index - start));
		start = index + 1;
		index = str.find_first_of(pattern, start);
	}
	if (!str.substr(start).empty())
		ret.push_back(str.substr(start));
	return ret;
}