#include "pch.h"
#include "commander.h"
#include <cstdio>
#include <iostream>
#pragma warning(disable : 4996)

// ����:execmd����ִ�������������洢��result�ַ��������� 
// ����:cmd��ʾҪִ�е�����
// result��ִ�еĽ���洢���ַ�������
// ����ִ�гɹ�����1��ʧ�ܷ���0
int execmd(const char* cmd, char* result)
{
	char buffer[128];                         //���建����                        
	FILE* pipe = _popen(cmd, "r");            //�򿪹ܵ�����ִ������ 
	if (!pipe)
		return 0;                      //����0��ʾ����ʧ�� 

	while (!feof(pipe)) {
		if (fgets(buffer, 128, pipe)) {             //���ܵ������result�� 
			strcat(result, buffer);
		}
	}
	_pclose(pipe);                            //�رչܵ� 
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

	//�ؼ����裬CreateProcess�����������������MSDN   

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

		//buffer�о���ִ�еĽ�������Ա��浽�ı���Ҳ����ֱ�����   

		//printf(buffer);//����ע�͵��Ϳ�����  
		strcat(result, buffer);
		//Sleep(100);

	}

	return   1;

}
