#include "dtsource.h"
#include "pch.h"
#include "iostream"  
#include "string"  
#include "vector" 
#include <numeric> // for std::accumulate

using namespace std;
#pragma warning(disable : 4996)
//步骤1：添加对ADO的支持  
#import "C:/Program Files/Common Files/System/ado/msado15.dll" no_namespace rename("EOF","adoEOF")rename("BOF","doBOF")  

int q_base(const char* db_url, const char* db_name, const char* db_sql, char* result[256])
{
	CoInitialize(NULL); //初始化COM环境           
	_ConnectionPtr pMyConnect(__uuidof(Connection));//定义连接对象并实例化对象 
	_RecordsetPtr pRst(__uuidof(Recordset));//定义记录集对象并实例化对象               
	try
	{
		//步骤2：创建数据源连接
		/*打开数据库“SQLServer”，这里需要根据自己PC的数据库的情况 */
		pMyConnect->Open(db_url, "", "", adModeUnknown);
	}
	catch (_com_error& e)
	{

		cout << "Initiate failed!" << endl;
		cout << e.Description() << endl;
		cout << e.HelpFile() << endl;
		return 0;
	}
	cout << "Connect succeed!" << endl;

	//步骤3：对数据源中的数据库/表进行操作
	try
	{
		vector<string> vec = { "use", " ", db_name };
		string db_name_new ="";
		db_name_new=accumulate(vec.begin(), vec.end(), db_name_new);
		pMyConnect->Execute(db_name_new.c_str(), NULL, adCmdText);//执行SQL
		pRst = pMyConnect->Execute(db_sql, NULL, adCmdText);//执行SQL
		//Table_1是数据库的表名
		if (!pRst->adoEOF)
		{
			pRst->MoveFirst();
		}
		else
		{
			cout << "Data is empty!" << endl;
			return 0;
		}
		vector<_bstr_t> column_name;

		//	/*存储表的所有列名，显示表的列名*/
		for (int i = 0; i < pRst->Fields->GetCount(); i++)
		{
			cout << pRst->Fields->GetItem(_variant_t((long)i))->Name << endl;
			column_name.push_back(pRst->Fields->GetItem(_variant_t((long)i))->Name);
		}
		//cout << endl;

		//	/*对表进行遍历访问,显示表中每一行的内容*/
		while (!pRst->adoEOF)
		{
			vector<_bstr_t>::iterator iter = column_name.begin();
			for (iter; iter != column_name.end(); iter++)
			{
				if (pRst->GetCollect(*iter).vt != VT_NULL)
				{
					cout << (_bstr_t)pRst->GetCollect(*iter) << endl;
				}
				else
				{
					cout << "NULL" << endl;
				}
			}
			pRst->MoveNext();
		}
	}
	catch (_com_error& e)
	{
		cout << e.Description() << endl;
		cout << e.HelpFile() << endl;
		return 0;
	}

	//步骤4：关闭数据源
	/*关闭数据库并释放指针*/
	try
	{
		pRst->Close();     //关闭记录集               
		pMyConnect->Close();//关闭数据库               
		pRst.Release();//释放记录集对象指针               
		pMyConnect.Release();//释放连接对象指针
	}
	catch (_com_error& e)
	{
		cout << e.Description() << endl;
		cout << e.HelpFile() << endl;
		return 0;
	}
	CoUninitialize(); //释放COM环境
	return 1;
}

int q_rc(const char* db_url, const char* db_name, const char* db_sql, char** result)
{
	CoInitialize(NULL); //初始化COM环境           
	_ConnectionPtr pMyConnect(__uuidof(Connection));//定义连接对象并实例化对象 
	_RecordsetPtr pRst(__uuidof(Recordset));//定义记录集对象并实例化对象       
	int _err_num(0);
	try
	{
		//步骤2：创建数据源连接
		/*打开数据库“SQLServer”，这里需要根据自己PC的数据库的情况 */
		pMyConnect->Open(db_url, "", "", adModeUnknown);
	}
	catch (_com_error& e)
	{
		*(result+0)= const_cast<char*>("Initiate failed!");
		_err_num = WideCharToMultiByte(CP_OEMCP, NULL, (LPCWCH)e.Description(), -1, NULL, 0, NULL, FALSE);
		WideCharToMultiByte(CP_OEMCP, NULL, (LPCWCH)e.Description(), -1, *(result + 1), _err_num, NULL, FALSE);
		return 0;
	}
	*(result + 0) = const_cast<char*>("Connect succeed!");
	//步骤3：对数据源中的数据库/表进行操作
	try
	{
		vector<string> vec = { "USE", " ", db_name };
		string db_name_new = "";
		db_name_new = accumulate(vec.begin(), vec.end(), db_name_new);
		pMyConnect->Execute(db_name_new.c_str(), NULL, adCmdText);//执行SQL
		pRst = pMyConnect->Execute(db_sql, NULL, adCmdText);//执行SQL
		//Table_1是数据库的表名
		if (!pRst->adoEOF)
		{
			pRst->MoveFirst();
		}
		else
		{
			*(result + 0) = const_cast<char*>("Data is empty!");
			return 0;
		}
		vector<_bstr_t> column_name;
		vector<_bstr_t> column_name_r;
		_itoa(pRst->Fields->GetCount(), *(result + 3), 10);
		//	/*存储表的所有列名，显示表的列名*/
		for (int i = 0; i < pRst->Fields->GetCount(); i++)
		{
			//cout << pRst->Fields->GetCount() << endl;
			//cout << pRst->Fields->GetItem(_variant_t((long)i))->Name << endl;
			column_name.push_back(pRst->Fields->GetItem(_variant_t((long)i))->Name);
			column_name_r.push_back(pRst->Fields->GetItem(_variant_t((long)i))->Name);
			column_name_r.push_back("$");
		}
		//cout << endl;
		column_name_r.pop_back();
		_itoa(column_name_r.size(), *(result + 4), 10);
		_bstr_t s = "";
		s =accumulate(column_name_r.begin(), column_name_r.end(),s);
		int num = WideCharToMultiByte(CP_OEMCP, NULL, (LPCWCH)s, -1, NULL, 0, NULL, FALSE);
		WideCharToMultiByte(CP_OEMCP, NULL, (LPCWCH)s, -1, *(result + 6), num, NULL, FALSE);
		//	/*对表进行遍历访问,显示表中每一行的内容*/
		vector<_bstr_t> rc;
		while (!pRst->adoEOF)
		{
			vector<_bstr_t>::iterator iter = column_name.begin();
			for (iter; iter != column_name.end(); iter++)
			{
				if (pRst->GetCollect(*iter).vt != VT_NULL)
				{
					//cout << (_bstr_t)pRst->GetCollect(*iter) <<"\t";
					rc.push_back((_bstr_t)pRst->GetCollect(*iter));
					rc.push_back("$");
				}
				else
				{
					//cout << "NULL" << endl;
					rc.push_back("null");
					rc.push_back("$");
				}
			}
			rc.pop_back();
			rc.push_back("#");
			pRst->MoveNext();
		}
		//返回结果
		rc.pop_back();
		_itoa(rc.size(), *(result + 5), 10);
		_bstr_t _rc = "";
		_rc = accumulate(rc.begin(), rc.end(), _rc);
		int _num = WideCharToMultiByte(CP_OEMCP, NULL, (LPCWCH)_rc, -1, NULL, 0, NULL, FALSE);
		WideCharToMultiByte(CP_OEMCP, NULL, (LPCWCH)_rc, -1, *(result + 7), _num, NULL, FALSE);
	}
	catch (_com_error& e)
	{
		_err_num = WideCharToMultiByte(CP_OEMCP, NULL, (LPCWCH)e.Description(), -1, NULL, 0, NULL, FALSE);
		WideCharToMultiByte(CP_OEMCP, NULL, (LPCWCH)e.Description(), -1, *(result + 1), _err_num, NULL, FALSE);
		return 0;
	}

	//步骤4：关闭数据源
	/*关闭数据库并释放指针*/
	try
	{
		pRst->Close();     //关闭记录集               
		pMyConnect->Close();//关闭数据库               
		pRst.Release();//释放记录集对象指针               
		pMyConnect.Release();//释放连接对象指针
	}
	catch (_com_error& e)
	{
		_err_num = WideCharToMultiByte(CP_OEMCP, NULL, (LPCWCH)e.Description(), -1, NULL, 0, NULL, FALSE);
		WideCharToMultiByte(CP_OEMCP, NULL, (LPCWCH)e.Description(), -1, *(result + 1), _err_num, NULL, FALSE);
		return 0;
	}
	CoUninitialize(); //释放COM环境
	return 1;
}

int q_rcnum(const char* db_url, const char* db_name, const char* db_sql, char** result)
{
	CoInitialize(NULL); //初始化COM环境           
	_ConnectionPtr pMyConnect(__uuidof(Connection));//定义连接对象并实例化对象 
	_RecordsetPtr pRst(__uuidof(Recordset));//定义记录集对象并实例化对象  
	int _err_num(0);
	try
	{
		//步骤2：创建数据源连接
		/*打开数据库“SQLServer”，这里需要根据自己PC的数据库的情况 */
		pMyConnect->Open(db_url, "", "", adModeUnknown);
	}
	catch (_com_error& e)
	{
		*(result + 0) = const_cast<char*>("Initiate failed!");
		_err_num = WideCharToMultiByte(CP_OEMCP, NULL, (LPCWCH)e.Description(), -1, NULL, 0, NULL, FALSE);
		WideCharToMultiByte(CP_OEMCP, NULL, (LPCWCH)e.Description(), -1, *(result + 1), _err_num, NULL, FALSE);
		/*_err_num = WideCharToMultiByte(CP_OEMCP, NULL, (LPCWCH)e.HelpFile(), -1, NULL, 0, NULL, FALSE);
		WideCharToMultiByte(CP_OEMCP, NULL, (LPCWCH)e.HelpFile(), -1, *(result + 2), _err_num, NULL, FALSE);*/
		return 0;
	}
	*(result + 0) = const_cast<char*>("Connect succeed!");
	//步骤3：对数据源中的数据库/表进行操作
	try
	{
		vector<string> vec = { "USE", " ", db_name };
		string db_name_new = "";
		db_name_new = accumulate(vec.begin(), vec.end(), db_name_new);
		pMyConnect->Execute(db_name_new.c_str(), NULL, adCmdText);//执行SQL
		pRst = pMyConnect->Execute(db_sql, NULL, adCmdText);//执行SQL
		//Table_1是数据库的表名
		if (!pRst->adoEOF)
		{
			pRst->MoveFirst();
		}
		else
		{
			*(result + 0) = const_cast<char*>("Data is empty!");
			return 0;
		}
		vector<_bstr_t> column_name;
		vector<_bstr_t> column_name_r;
		//返回列数
		_itoa(pRst->Fields->GetCount(), *(result + 3), 10);
		//	/*存储表的所有列名，显示表的列名*/
		for (int i = 0; i < pRst->Fields->GetCount(); i++)
		{
			column_name.push_back(pRst->Fields->GetItem(_variant_t((long)i))->Name);
			column_name_r.push_back(pRst->Fields->GetItem(_variant_t((long)i))->Name);
			column_name_r.push_back("$");
		}
		column_name_r.pop_back();
		//返回列名
		/*_bstr_t s = "";
		s = accumulate(column_name_r.begin(), column_name_r.end(), s);
		int num = WideCharToMultiByte(CP_OEMCP, NULL, (LPCWCH)s, -1, NULL, 0, NULL, FALSE);
		WideCharToMultiByte(CP_OEMCP, NULL, (LPCWCH)s, -1, *(result + 4), num, NULL, FALSE);*/
		_itoa(column_name_r.size(), *(result + 4), 10);
		//	/*对表进行遍历访问,显示表中每一行的内容*/
		vector<_bstr_t> rc;
		while (!pRst->adoEOF)
		{
			vector<_bstr_t>::iterator iter = column_name.begin();
			for (iter; iter != column_name.end(); iter++)
			{
				if (pRst->GetCollect(*iter).vt != VT_NULL)
				{
					rc.push_back((_bstr_t)pRst->GetCollect(*iter));
					rc.push_back("$");
				}
				else
				{
					rc.push_back("null");
					rc.push_back("$");
				}
			}
			rc.pop_back();
			rc.push_back("#");
			pRst->MoveNext();
		}
		//返回结果
		rc.pop_back();

		//_bstr_t _rc = "";
		//_rc = accumulate(rc.begin(), rc.end(), _rc);
		//int _num = WideCharToMultiByte(CP_OEMCP, NULL, (LPCWCH)_rc, -1, NULL, 0, NULL, FALSE);
		//WideCharToMultiByte(CP_OEMCP, NULL, (LPCWCH)_rc, -1, *(result + 5), _num, NULL, FALSE);
		_itoa(rc.size(), *(result + 5), 10);
	}
	catch (_com_error& e)
	{
		_err_num = WideCharToMultiByte(CP_OEMCP, NULL, (LPCWCH)e.Description(), -1, NULL, 0, NULL, FALSE);
		WideCharToMultiByte(CP_OEMCP, NULL, (LPCWCH)e.Description(), -1, *(result + 1), _err_num, NULL, FALSE);
		/*_err_num = WideCharToMultiByte(CP_OEMCP, NULL, (LPCWCH)e.HelpFile(), -1, NULL, 0, NULL, FALSE);
		WideCharToMultiByte(CP_OEMCP, NULL, (LPCWCH)e.HelpFile(), -1, *(result + 2), _err_num, NULL, FALSE);*/
		return 0;
	}

	//步骤4：关闭数据源
	/*关闭数据库并释放指针*/
	try
	{
		pRst->Close();     //关闭记录集               
		pMyConnect->Close();//关闭数据库               
		pRst.Release();//释放记录集对象指针               
		pMyConnect.Release();//释放连接对象指针
	}
	catch (_com_error& e)
	{
		_err_num = WideCharToMultiByte(CP_OEMCP, NULL, (LPCWCH)e.Description(), -1, NULL, 0, NULL, FALSE);
		WideCharToMultiByte(CP_OEMCP, NULL, (LPCWCH)e.Description(), -1, *(result + 1), _err_num, NULL, FALSE);
		/*_err_num = WideCharToMultiByte(CP_OEMCP, NULL, (LPCWCH)e.HelpFile(), -1, NULL, 0, NULL, FALSE);
		WideCharToMultiByte(CP_OEMCP, NULL, (LPCWCH)e.HelpFile(), -1, *(result + 2), _err_num, NULL, FALSE);*/
		return 0;
	}
	CoUninitialize(); //释放COM环境
	return 1;
}

int q_db(const char* db_url, char** result)
{
	CoInitialize(NULL); //初始化COM环境           
	_ConnectionPtr pMyConnect(__uuidof(Connection));//定义连接对象并实例化对象 
	_RecordsetPtr pRst(__uuidof(Recordset));//定义记录集对象并实例化对象  
	int _err_num(0);
	try
	{
		//步骤2：创建数据源连接
		/*打开数据库“SQLServer”，这里需要根据自己PC的数据库的情况 */
		pMyConnect->Open(db_url, "", "", adModeUnknown);
	}
	catch (_com_error& e)
	{
		*(result + 0) = const_cast<char*>("Initiate failed!");
		_err_num = WideCharToMultiByte(CP_OEMCP, NULL, (LPCWCH)e.Description(), -1, NULL, 0, NULL, FALSE);
		WideCharToMultiByte(CP_OEMCP, NULL, (LPCWCH)e.Description(), -1, *(result + 1), _err_num, NULL, FALSE);
		return 0;
	}
	*(result + 0) = const_cast<char*>("Connect succeed!");
	//步骤3：对数据源中的数据库/表进行操作
	try
	{
		pRst = pMyConnect->Execute("SELECT NAME FROM MASTER..SYSDATABASES WHERE DBID>4 ORDER BY NAME", NULL, adCmdText);//执行SQL
		//Table_1是数据库的表名
		if (!pRst->adoEOF)
		{
			pRst->MoveFirst();
		}
		else
		{
			*(result + 0) = const_cast<char*>("Data is empty!");
			return 0;
		}
		vector<_bstr_t> column_name;
		vector<_bstr_t> column_name_r;
		//返回列数
		_itoa(pRst->Fields->GetCount(), *(result + 3), 10);
		//	/*存储表的所有列名，显示表的列名*/
		for (int i = 0; i < pRst->Fields->GetCount(); i++)
		{
			column_name.push_back(pRst->Fields->GetItem(_variant_t((long)i))->Name);
			column_name_r.push_back(pRst->Fields->GetItem(_variant_t((long)i))->Name);
			column_name_r.push_back("$");
		}
		column_name_r.pop_back();
		_itoa(column_name_r.size(), *(result + 4), 10);
		//返回列名
		_bstr_t s = "";
		s = accumulate(column_name_r.begin(), column_name_r.end(), s);
		int num = WideCharToMultiByte(CP_OEMCP, NULL, (LPCWCH)s, -1, NULL, 0, NULL, FALSE);
		WideCharToMultiByte(CP_OEMCP, NULL, (LPCWCH)s, -1, *(result + 6), num, NULL, FALSE);
		//	/*对表进行遍历访问,显示表中每一行的内容*/
		vector<_bstr_t> rc;
		while (!pRst->adoEOF)
		{
			vector<_bstr_t>::iterator iter = column_name.begin();
			for (iter; iter != column_name.end(); iter++)
			{
				if (pRst->GetCollect(*iter).vt != VT_NULL)
				{
					rc.push_back((_bstr_t)pRst->GetCollect(*iter));
					rc.push_back("$");
				}
				else
				{
					rc.push_back("null");
					rc.push_back("$");
				}
			}
			rc.pop_back();
			rc.push_back("#");
			pRst->MoveNext();
		}
		//返回结果
		rc.pop_back();
		_itoa(rc.size(), *(result + 5), 10);
		_bstr_t _rc = "";
		_rc = accumulate(rc.begin(), rc.end(), _rc);
		int _num = WideCharToMultiByte(CP_OEMCP, NULL, (LPCWCH)_rc, -1, NULL, 0, NULL, FALSE);
		WideCharToMultiByte(CP_OEMCP, NULL, (LPCWCH)_rc, -1, *(result + 7), _num, NULL, FALSE);
	}
	catch (_com_error& e)
	{
		_err_num = WideCharToMultiByte(CP_OEMCP, NULL, (LPCWCH)e.Description(), -1, NULL, 0, NULL, FALSE);
		WideCharToMultiByte(CP_OEMCP, NULL, (LPCWCH)e.Description(), -1, *(result + 1), _err_num, NULL, FALSE);
		return 0;
	}

	//步骤4：关闭数据源
	/*关闭数据库并释放指针*/
	try
	{
		pRst->Close();     //关闭记录集               
		pMyConnect->Close();//关闭数据库               
		pRst.Release();//释放记录集对象指针               
		pMyConnect.Release();//释放连接对象指针
	}
	catch (_com_error& e)
	{
		_err_num = WideCharToMultiByte(CP_OEMCP, NULL, (LPCWCH)e.Description(), -1, NULL, 0, NULL, FALSE);
		WideCharToMultiByte(CP_OEMCP, NULL, (LPCWCH)e.Description(), -1, *(result + 1), _err_num, NULL, FALSE);
		return 0;
	}
	CoUninitialize(); //释放COM环境
	return 1;
}

int q_dt(const char* db_url, const char* db_name, char** result)
{
	CoInitialize(NULL); //初始化COM环境           
	_ConnectionPtr pMyConnect(__uuidof(Connection));//定义连接对象并实例化对象 
	_RecordsetPtr pRst(__uuidof(Recordset));//定义记录集对象并实例化对象        
	int _err_num(0);
	try
	{
		//步骤2：创建数据源连接
		/*打开数据库“SQLServer”，这里需要根据自己PC的数据库的情况 */
		pMyConnect->Open(db_url, "", "", adModeUnknown);
	}
	catch (_com_error& e)
	{
		*(result + 0) = const_cast<char*>("Initiate failed!");
		_err_num = WideCharToMultiByte(CP_OEMCP, NULL, (LPCWCH)e.Description(), -1, NULL, 0, NULL, FALSE);
		WideCharToMultiByte(CP_OEMCP, NULL, (LPCWCH)e.Description(), -1, *(result + 1), _err_num, NULL, FALSE);
		return 0;
	}
	*(result + 0) = const_cast<char*>("Connect succeed!");
	//步骤3：对数据源中的数据库/表进行操作
	try
	{
		vector<string> vec = { "SELECT NAME FROM ", db_name,"..SYSOBJECTS WHERE XTYPE='U' ORDER BY NAME" };
		string db_name_new = "";
		db_name_new = accumulate(vec.begin(), vec.end(), db_name_new);
		pMyConnect->Execute(db_name_new.c_str(), NULL, adCmdText);//执行SQL
		//Table_1是数据库的表名
		if (!pRst->adoEOF)
		{
			pRst->MoveFirst();
		}
		else
		{
			*(result + 0) = const_cast<char*>("Data is empty!");
			return 0;
		}
		vector<_bstr_t> column_name;
		vector<_bstr_t> column_name_r;
		_itoa(pRst->Fields->GetCount(), *(result + 3), 10);
		//	/*存储表的所有列名，显示表的列名*/
		for (int i = 0; i < pRst->Fields->GetCount(); i++)
		{
			column_name.push_back(pRst->Fields->GetItem(_variant_t((long)i))->Name);
			column_name_r.push_back(pRst->Fields->GetItem(_variant_t((long)i))->Name);
			column_name_r.push_back("$");
		}
		column_name_r.pop_back();
		//返回列名
		_itoa(column_name_r.size(), *(result + 4), 10);
		_bstr_t s = "";
		s = accumulate(column_name_r.begin(), column_name_r.end(), s);
		int num = WideCharToMultiByte(CP_OEMCP, NULL, (LPCWCH)s, -1, NULL, 0, NULL, FALSE);
		WideCharToMultiByte(CP_OEMCP, NULL, (LPCWCH)s, -1, *(result + 6), num, NULL, FALSE);
		//	/*对表进行遍历访问,显示表中每一行的内容*/
		vector<_bstr_t> rc;
		while (!pRst->adoEOF)
		{
			vector<_bstr_t>::iterator iter = column_name.begin();
			for (iter; iter != column_name.end(); iter++)
			{
				if (pRst->GetCollect(*iter).vt != VT_NULL)
				{
					rc.push_back((_bstr_t)pRst->GetCollect(*iter));
					rc.push_back("$");
				}
				else
				{
					rc.push_back("null");
					rc.push_back("$");
				}
			}
			rc.pop_back();
			rc.push_back("#");
			pRst->MoveNext();
		}
		//返回结果集
		rc.pop_back();
		_itoa(rc.size(), *(result + 5), 10);
		_bstr_t _rc = "";
		_rc = accumulate(rc.begin(), rc.end(), _rc);
		int _num = WideCharToMultiByte(CP_OEMCP, NULL, (LPCWCH)_rc, -1, NULL, 0, NULL, FALSE);
		WideCharToMultiByte(CP_OEMCP, NULL, (LPCWCH)_rc, -1, *(result + 7), _num, NULL, FALSE);
	}
	catch (_com_error& e)
	{
		_err_num = WideCharToMultiByte(CP_OEMCP, NULL, (LPCWCH)e.Description(), -1, NULL, 0, NULL, FALSE);
		WideCharToMultiByte(CP_OEMCP, NULL, (LPCWCH)e.Description(), -1, *(result + 1), _err_num, NULL, FALSE);
		return 0;
	}

	//步骤4：关闭数据源
	/*关闭数据库并释放指针*/
	try
	{
		pRst->Close();     //关闭记录集               
		pMyConnect->Close();//关闭数据库               
		pRst.Release();//释放记录集对象指针               
		pMyConnect.Release();//释放连接对象指针
	}
	catch (_com_error& e)
	{
		_err_num = WideCharToMultiByte(CP_OEMCP, NULL, (LPCWCH)e.Description(), -1, NULL, 0, NULL, FALSE);
		WideCharToMultiByte(CP_OEMCP, NULL, (LPCWCH)e.Description(), -1, *(result + 1), _err_num, NULL, FALSE);
		return 0;
	}
	CoUninitialize(); //释放COM环境
	return 1;
}

int q_type(const char* db_url, const char* db_name, const char* dt_name, char** result)
{
	CoInitialize(NULL); //初始化COM环境           
	_ConnectionPtr pMyConnect(__uuidof(Connection));//定义连接对象并实例化对象 
	_RecordsetPtr pRst(__uuidof(Recordset));//定义记录集对象并实例化对象        
	int _err_num(0);
	try
	{
		//步骤2：创建数据源连接
		/*打开数据库“SQLServer”，这里需要根据自己PC的数据库的情况 */
		pMyConnect->Open(db_url, "", "", adModeUnknown);
	}
	catch (_com_error& e)
	{
		*(result + 0) = const_cast<char*>("Initiate failed!");
		_err_num = WideCharToMultiByte(CP_OEMCP, NULL, (LPCWCH)e.Description(), -1, NULL, 0, NULL, FALSE);
		WideCharToMultiByte(CP_OEMCP, NULL, (LPCWCH)e.Description(), -1, *(result + 1), _err_num, NULL, FALSE);
		return 0;
	}
	*(result + 0) = const_cast<char*>("Connect succeed!");
	//步骤3：对数据源中的数据库/表进行操作
	try
	{
		vector<string> vec = { "USE", " ", db_name };
		string db_name_new = "";
		db_name_new = accumulate(vec.begin(), vec.end(), db_name_new);
		pMyConnect->Execute(db_name_new.c_str(), NULL, adCmdText);//执行SQL
		vector<string> vec_sql = { "SELECT A.NAME AS TABLE_NAME, B.NAME AS COLUMN_NAME, C.VALUE AS COLUMN_DESCRIPTION, T.TYPE, T.LENGTH FROM SYS.TABLES A INNER JOIN SYS.COLUMNS B ON B.OBJECT_ID = A.OBJECT_ID LEFT JOIN SYS.EXTENDED_PROPERTIES C ON C.MAJOR_ID = B.OBJECT_ID AND C.MINOR_ID = B.COLUMN_ID INNER JOIN(SELECT SYSCOLUMNS.NAME AS NAME,SYSTYPES.NAME AS TYPE,SYSCOLUMNS.LENGTH AS LENGTH FROM SYSCOLUMNS INNER JOIN SYSTYPES ON SYSTYPES.XTYPE=SYSCOLUMNS.XTYPE WHERE ID=(SELECT ID FROM SYSOBJECTS WHERE NAME='",dt_name,"' AND SYSTYPES.NAME<> 'SYSNAME'))T ON T.NAME=B.NAME WHERE A.NAME = '",dt_name,"' ORDER BY B.NAME" };
		string db_sql = "";
		db_sql = accumulate(vec_sql.begin(), vec_sql.end(), db_sql);
		pRst = pMyConnect->Execute(db_sql.c_str(), NULL, adCmdText);//执行SQL
		//Table_1是数据库的表名
		if (!pRst->adoEOF)
		{
			pRst->MoveFirst();
		}
		else
		{
			*(result + 0) = const_cast<char*>("Data is empty!");
			return 0;
		}
		vector<_bstr_t> column_name;
		vector<_bstr_t> column_name_r;
		_itoa(pRst->Fields->GetCount(), *(result + 3), 10);
		//	/*存储表的所有列名，显示表的列名*/
		for (int i = 0; i < pRst->Fields->GetCount(); i++)
		{
			column_name.push_back(pRst->Fields->GetItem(_variant_t((long)i))->Name);
			column_name_r.push_back(pRst->Fields->GetItem(_variant_t((long)i))->Name);
			column_name_r.push_back("$");
		}
		column_name_r.pop_back();
		//返回列明
		_itoa(column_name_r.size(), *(result + 4), 10);
		_bstr_t s = "";
		s = accumulate(column_name_r.begin(), column_name_r.end(), s);
		int num = WideCharToMultiByte(CP_OEMCP, NULL, (LPCWCH)s, -1, NULL, 0, NULL, FALSE);
		WideCharToMultiByte(CP_OEMCP, NULL, (LPCWCH)s, -1, *(result + 6), num, NULL, FALSE);
		//	/*对表进行遍历访问,显示表中每一行的内容*/
		vector<_bstr_t> rc;
		while (!pRst->adoEOF)
		{
			vector<_bstr_t>::iterator iter = column_name.begin();
			for (iter; iter != column_name.end(); iter++)
			{
				if (pRst->GetCollect(*iter).vt != VT_NULL)
				{
					rc.push_back((_bstr_t)pRst->GetCollect(*iter));
					rc.push_back("$");
				}
				else
				{
					rc.push_back("null");
					rc.push_back("$");
				}
			}
			rc.pop_back();
			rc.push_back("#");
			pRst->MoveNext();
		}
		//返回结果集
		rc.pop_back();
		_itoa(rc.size(), *(result + 5), 10);
		_bstr_t _rc = "";
		_rc = accumulate(rc.begin(), rc.end(), _rc);
		int _num = WideCharToMultiByte(CP_OEMCP, NULL, (LPCWCH)_rc, -1, NULL, 0, NULL, FALSE);
		WideCharToMultiByte(CP_OEMCP, NULL, (LPCWCH)_rc, -1, *(result + 7), _num, NULL, FALSE);
	}
	catch (_com_error& e)
	{
		_err_num = WideCharToMultiByte(CP_OEMCP, NULL, (LPCWCH)e.Description(), -1, NULL, 0, NULL, FALSE);
		WideCharToMultiByte(CP_OEMCP, NULL, (LPCWCH)e.Description(), -1, *(result + 1), _err_num, NULL, FALSE);
		return 0;
	}

	//步骤4：关闭数据源
	/*关闭数据库并释放指针*/
	try
	{
		pRst->Close();     //关闭记录集               
		pMyConnect->Close();//关闭数据库               
		pRst.Release();//释放记录集对象指针               
		pMyConnect.Release();//释放连接对象指针
	}
	catch (_com_error& e)
	{
		_err_num = WideCharToMultiByte(CP_OEMCP, NULL, (LPCWCH)e.Description(), -1, NULL, 0, NULL, FALSE);
		WideCharToMultiByte(CP_OEMCP, NULL, (LPCWCH)e.Description(), -1, *(result + 1), _err_num, NULL, FALSE);
		return 0;
	}
	CoUninitialize(); //释放COM环境
	return 1;
}
