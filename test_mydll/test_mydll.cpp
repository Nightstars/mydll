// test_mydll.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <Windows.h>
using namespace std;
int main()
{
	typedef void(*PLUSFUNC)(int*);
	typedef void(*PLUSFUNC1)(int*);
	typedef void(*PLUSFUNC2)(int,int,int *);
	HINSTANCE hDllInst;

	hDllInst = LoadLibrary(L"mydll.dll");

	PLUSFUNC add = (PLUSFUNC)GetProcAddress(hDllInst, "add");
	PLUSFUNC1 add1 = (PLUSFUNC1)GetProcAddress(hDllInst, "add1");
	PLUSFUNC2 add2 = (PLUSFUNC2)GetProcAddress(hDllInst, "add2");

	int num(10),num1(100),a(12),b(4),result;

	add(&num);
	cout << num << endl;

	add1(&num1);
	cout << num1 << endl;

	add2(a, b, &result);
	cout << result << endl;

	FreeLibrary(hDllInst);
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
