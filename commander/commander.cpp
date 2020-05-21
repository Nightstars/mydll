#include "pch.h"
#include "commander.h"
#include <cstdio>
#include <iostream>
#pragma warning(disable : 4996)

// 描述:execmd函数执行命令，并将结果存储到result字符串数组中 
// 参数:cmd表示要执行的命令
// result是执行的结果存储的字符串数组
// 函数执行成功返回1，失败返回0
int execmd(const char* cmd, char* result)
{
	char buffer[128];                         //定义缓冲区                        
	FILE* pipe = _popen(cmd, "r");            //打开管道，并执行命令 
	if (!pipe)
		return 0;                      //返回0表示运行失败 

	while (!feof(pipe)) {
		if (fgets(buffer, 128, pipe)) {             //将管道输出到result中 
			strcat(result, buffer);
		}
	}
	_pclose(pipe);                            //关闭管道 
	return 1;
}
