#include "dtsource.h"
#include "pch.h"
#include "iostream"  
#include "string"  
#include "vector" 
#include <numeric> // for std::accumulate
using namespace std;
//步骤1：添加对ADO的支持  
#import "C:/Program Files/Common Files/System/ado/msado15.dll" no_namespace rename("EOF","adoEOF")rename("BOF","doBOF")  

int q_base(const char* db_url, const char* db_name, const char* db_sql, const char* result)
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
		cout << endl;

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
			cout << endl;
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
