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
