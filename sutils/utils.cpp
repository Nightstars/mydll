#include "pch.h"
#include "utils.h"
#include <vector>
#include <string>
#include <comutil.h>
#include <iostream>

using namespace std;
#pragma warning(disable : 4996)

int split_char(const char* parm,const char* pattern, char** result)
{
	/*string str = parm;
	string _pattern = pattern;
	vector<string> ret;
	if (_pattern.empty()) return 0;
	size_t start = 0, index = str.find_first_of(_pattern, 0);
	while (index != str.npos)
	{
		if (start != index)
			ret.push_back(str.substr(start, index - start));
		start = index + 1;
		index = str.find_first_of(_pattern, start);
	}
	if (!str.substr(start).empty())
		ret.push_back(str.substr(start));
	int i = 0;
	for (auto val : ret)
	{
		*(result + i) = const_cast<char*>("ADC");
		i++;
	}*/

	char s[] = "my name is lmm";
	char* p;
	const char* delim = " ";
	p = strtok(s, delim);
	int i = 0;
	while (p) {
		*(result + i) = p;
		std::cout << p << std::endl;
		p = strtok(NULL, delim);
		i++;
	}

	return 1;
}
