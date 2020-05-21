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
int execme_hide(char* CommandLine, char* result)

{

	SECURITY_ATTRIBUTES   sa;

	HANDLE   hRead, hWrite;



	sa.nLength = sizeof(SECURITY_ATTRIBUTES);

	sa.lpSecurityDescriptor = NULL;

	sa.bInheritHandle = TRUE;

	if (!CreatePipe(&hRead, &hWrite, &sa, 0))

	{

		return   0;

	}



	STARTUPINFOA   si;

	PROCESS_INFORMATION   pi;

	si.cb = sizeof(STARTUPINFO);

	GetStartupInfoA(&si);

	si.hStdError = hWrite;

	si.hStdOutput = hWrite;

	si.wShowWindow = SW_HIDE;

	si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;

	//关键步骤，CreateProcess函数参数意义请查阅MSDN   

	if (!CreateProcessA(NULL, CommandLine, NULL, NULL, TRUE, NULL, NULL, NULL, &si, &pi))

	{

		return   0;

	}

	CloseHandle(hWrite);



	char   buffer[4096] = { 0 };

	DWORD   bytesRead;

	while (true)

	{

		memset(buffer, 0, strlen(buffer));

		if (ReadFile(hRead, buffer, 4095, &bytesRead, NULL) == NULL)

			break;

		//buffer中就是执行的结果，可以保存到文本，也可以直接输出   

		//printf(buffer);//这行注释掉就可以了  
		strcat(result, buffer);
		//Sleep(100);

	}

	return   1;

}
