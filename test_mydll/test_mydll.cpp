﻿// test_mydll.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <Windows.h>
using namespace std;
#pragma warning(disable : 4996)
#include<fstream>
#include <vector>
#include <numeric> // for std::accumulate
#include<iostream>
#include<fstream>

int main()
{
#pragma region demo
	/*typedef void(*PLUSFUNC)(int*);
	typedef void(*PLUSFUNC1)(int*);
	typedef void(*PLUSFUNC2)(int,int,int *);
	HINSTANCE hDllInst;

	hDllInst = LoadLibrary(L"mydll.dll");

	PLUSFUNC add = (PLUSFUNC)GetProcAddress(hDllInst, "add");
	PLUSFUNC1 add1 = (PLUSFUNC1)GetProcAddress(hDllInst, "add1");
	PLUSFUNC2 add2 = (PLUSFUNC2)GetProcAddress(hDllInst, "add2");

	int num(10),num1(100),a(18),b(24),result;

	add(&num);
	cout << num << endl;

	add1(&num1);
	cout << num1 << endl;

	add2(a, b, &result);
	cout << result << endl;*/

	//using namespace std;
	//vector<string> vec = { "hello", " ", "world" };
	//string s = accumulate(vec.begin(), vec.end(), s);
	//cout << s << endl; // prints 'hello world' to standard output. 
#pragma endregion

#pragma region test_dll_commander
	//typedef int(*PLUSFUNC)(const char* cmd, char* result);
	//HINSTANCE hDllInst;
	//hDllInst = LoadLibrary("commander.dll");
	//PLUSFUNC execmd = (PLUSFUNC)GetProcAddress(hDllInst, "execmd");
	//char result[1024 * 4] = "";                   //定义存放结果的字符串数组 
	//if (1 == execmd("ping 127.0.0.1", result)) {
	//	printf(result);
	//}
	//FreeLibrary(hDllInst);
#pragma endregion

#pragma region tow_dimensional pointer
	/*char* name[4] = {};
	name[0] = const_cast<char*>("test");
	name[1] = const_cast<char*>("multiply");
	name[2] = const_cast<char*>("string");
	cout << name[0] << endl;
	cout << name[1] << endl;
	cout << name[2] << endl;*/

	//int n(2);
	//char** pchar = NULL;
	//pchar = (char**)malloc(n* sizeof(char*)*100000); // pchar其实就是一个char * []数组
	//for (int i(0); i < n; i++)
	//{
	//	*(pchar + i) = (char*)malloc(n * sizeof(char) * 100000);
	//}
	//	pchar[0] = const_cast<char*>("test");
	//	pchar[1] = const_cast<char*>("multiply");
	//	cout << pchar[0] << endl;
	//	cout << pchar[1] << endl;

	//	for (int i(0); i < n; i++)
	//	{
	//		pchar[i] = nullptr;
	//		free(pchar[i]);
	//	}
	//	free(pchar);

#pragma endregion


#pragma region test_dll_dasource
	//typedef int(*QBASEFUNC)(const char* db_url, const char* db_name, const char* db_sql, char** result);
	//HINSTANCE hDllInst;
	//hDllInst = LoadLibrary("dtsource.dll");
	//QBASEFUNC q_rcnum = (QBASEFUNC)GetProcAddress(hDllInst, "q_rc");
	//const char* db_url =(char *)malloc(1024 * sizeof(char));
	//const char* db_name =(char *)malloc(128 * sizeof(char));
	//const char* dt_name =(char *)malloc(128 * sizeof(char));
	//const char* db_sql =(char *)malloc(4096 * sizeof(char));
	//db_url = "Provider=SQLOLEDB; Server=192.168.0.187,1433\MSSQLSERVER;Database=CMS; uid=sa; pwd=Ihavenoidea@0;";
	//db_name= "PUB_PARA";
	//dt_name= "CURR";
	//db_sql= "SELECT * FROM CURR";
	//int n(8);
	//char** pchar = NULL;
	//pchar = (char**)malloc(n* sizeof(char*)); // pchar其实就是一个char * []数组
	//for (int i(0); i < n; i++)
	//{
	//	*(pchar + i) = (char*)malloc(64*1819*sizeof(char));
	//}

	//int stat=q_rcnum(db_url,db_name,db_sql,pchar);
	//if (stat == 1) {
	//	cout << "status：" << *(pchar + 0) << endl;
	//	cout << "clumsize：" << *(pchar + 3) << endl;
	//	cout << "clums：" << *(pchar + 4) << endl;
	//	cout << "recoders：" << *(pchar + 5) << endl;
	//	cout << "clum_name：" << *(pchar + 6) << endl;
	//	cout << "rc_name：" << *(pchar + 7) << endl;
	//}
	//else {
	//	cout << "status：" << *(pchar + 0) << endl;
	//	cout << "Description：" <<*(pchar + 1) << endl;
	//}
	//
	//
	//FreeLibrary(hDllInst);
	//for (int i(0); i < n; i++)
	//{
	//	pchar[i] = nullptr;
	//	free(pchar[i]);
	//}
	//free(pchar);
#pragma endregion

	//fstream fs("F:\\vsstudio\\mydll\\x64\\Debug\\test.txt", ios::binary | ios::out | ios::in);
	////跳转到开头的第二个字节位置进行写入，正常写入
	//fs.seekp(29, ios::beg);
	//fs.write("\r\n!\r\n!\r\n!", 15);
	//fs.close();

	int i = 0, num;
	char str[100][500] = { 0 }, linedata[100] = { 0 };
	FILE* fp = fopen("F:\\vsstudio\\mydll\\x64\\Debug\\test.txt", "r");
	FILE* fpw;
	while (fgets(linedata, sizeof(linedata) - 1, fp))
	{
		if (strcmp(linedata, "[{$1$}]\n") == 0|| strcmp(linedata, "[{$1$}]") == 0)
		{
			strcpy(str[i], "this\nis\ngenc\ntest\n");
		}
		else
		{
			strcpy(str[i], linedata);
		}
		i++;
	}
	fclose(fp);
	num = i;
	fpw = fopen("F:\\vsstudio\\mydll\\x64\\Debug\\temp.txt", "w");
	for (i = 0; i < num; i++)
	{
		fputs(str[i], fpw);
	}
	fclose(fpw);



	system("pause");
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
