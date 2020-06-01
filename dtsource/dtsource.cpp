#include "dtsource.h"
#include "pch.h"
#include "iostream"  
#include "string"  
#include "vector" 
#include <numeric> // for std::accumulate
using namespace std;
//����1����Ӷ�ADO��֧��  
#import "C:/Program Files/Common Files/System/ado/msado15.dll" no_namespace rename("EOF","adoEOF")rename("BOF","doBOF")  

int q_base(const char* db_url, const char* db_name, const char* db_sql, const char* result)
{
	CoInitialize(NULL); //��ʼ��COM����           
	_ConnectionPtr pMyConnect(__uuidof(Connection));//�������Ӷ���ʵ�������� 
	_RecordsetPtr pRst(__uuidof(Recordset));//�����¼������ʵ��������               
	try
	{
		//����2����������Դ����
		/*�����ݿ⡰SQLServer����������Ҫ�����Լ�PC�����ݿ����� */
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

	//����3��������Դ�е����ݿ�/����в���
	try
	{
		vector<string> vec = { "use", " ", db_name };
		string db_name_new ="";
		db_name_new=accumulate(vec.begin(), vec.end(), db_name_new);
		pMyConnect->Execute(db_name_new.c_str(), NULL, adCmdText);//ִ��SQL
		pRst = pMyConnect->Execute(db_sql, NULL, adCmdText);//ִ��SQL
		//Table_1�����ݿ�ı���
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

		//	/*�洢���������������ʾ�������*/
		for (int i = 0; i < pRst->Fields->GetCount(); i++)
		{
			cout << pRst->Fields->GetItem(_variant_t((long)i))->Name << endl;
			column_name.push_back(pRst->Fields->GetItem(_variant_t((long)i))->Name);
		}
		cout << endl;

		//	/*�Ա���б�������,��ʾ����ÿһ�е�����*/
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

	//����4���ر�����Դ
	/*�ر����ݿⲢ�ͷ�ָ��*/
	try
	{
		pRst->Close();     //�رռ�¼��               
		pMyConnect->Close();//�ر����ݿ�               
		pRst.Release();//�ͷż�¼������ָ��               
		pMyConnect.Release();//�ͷ����Ӷ���ָ��
	}
	catch (_com_error& e)
	{
		cout << e.Description() << endl;
		cout << e.HelpFile() << endl;
		return 0;
	}
	CoUninitialize(); //�ͷ�COM����
	return 1;
}
