#include"work.h"

void list1();
void list2();
void list3();
int input(int max, bool isZero);

void list1()
{
	cout << "=====================================" << endl;
	cout << "--------学生成绩管理系统-------------" << endl;
	cout << "1.学生                              " << endl;
	cout << "2.老师                              " << endl;
	cout << "0.退出                              " << endl;
}

void list2()
{
	SqList1 L;
	BSTree T = NULL, temp;
	char num;
	int lock;
	Status taller;
	Status shorter = ERROR;
	int i = 0, m = 0, n = 0, r = 0,j=0;
	string id, password, name, sex;
	while (1)
	{
		cout << "=========================================" << endl;
		cout << "-------------------学生端----------------" << endl;
		cout << "1.注册                                   " << endl;
		cout << "2.登录                                   " << endl;
		cout << "3.修改密码                               " << endl;
		cout << "4.录入个人信息                          " << endl;
		cout << "5.查询信息                               " << endl;
		cout << "6.注销账号                               " << endl;
		cout << "7.导入数据                               " << endl;
		cout << "0.退出                                   " << endl;
		cout << "请输入你的选项：";
		cin >> num;
		lock = num - '0';
		switch (lock)
		{
		case 1:
			//createfile();
			In_file(L);
			while(L.elem[i].id.length()!=0)
			{
				InsertAVL1(&T, L.elem[i], &taller, i);
				i++;
			}
			cout << "请输入你的id：" << endl;
			cin >> id;
			cout << "请输入你的密码：" << endl;
			cin >> password;
			if (InsertAVL2(&T, id, password, &taller))
			{
				cout << "注册成功"<<endl;
			}
			else
			{
				cout << "注册失败,有重复id."<<endl;
			}
			break;
		case 2:
			cout << "请输入你的id:";
			cin >> id;
			cout << "请输入你的密码:";
			cin >> password;
			InOrderTraverseBST1(T, id, password, m);
			if (m == 0)
			{
				cout << "登陆失败" <<endl;
			}
			else
			{
				cout << "登录成功"<<endl;
			}
			break;
		case 3:
			cout << "请输入你的id:";
			cin >> id;
			cout << "请输入你的密码:";
			cin >> password;
			InOrderTraverseBST2(T, id, password, n);
			if (n == 0)
			{
				cout << "修改失败" <<endl;
			}
			else
			{
				cout << "修改成功"<<endl;
			}
			break;
		case 4:
			cout << "请输入你的id:";
			cin >> id;
			cout << "请输入你的信息(姓名 性别):";
			cin >> name >> sex;
			InOrderTraverseBST3(T, id, name, sex, r);
			if (r == 0)
			{
				cout << "录入失败" << endl;
			}
			else
			{
				cout << "录入成功"<<endl;
			}
			break;
		case 5:
			cout << "请输入id用来查找：";
			cin >> id;
			temp = SearchBST(T, id);
			if (temp)
			{
				cout << "查找成功\n\n";
				cout << "信息如下:\n";
				cout << left << setw(15) << temp->data.id << "\t" << left << setw(50)
					<< temp->data.name << "\t" << left << setw(5) << temp->data.sex << setw(5) << temp->data.math << setw(5) << temp->data.englidh << setw(5) << temp->data.java << endl;
			}
			else
			{
				cout << "查找失败"<<endl;
			}
			break;
		case 6:
			cout << "请输入你的id：";
			cin >> id;
			if (delNode(T, id, shorter))
			{
				cout << "注销成功"<<endl;
			}
			else
			{
				cout << "注销失败"<<endl;
			}
			break;
		case 7:
			cout << "传输数据" << endl;
			back_Sq(T, L, j);
			Out_file(L);
			cout << "导入成功"<<endl;
			break;
		default:
			cout << "终止程序" << endl;
			return;
		}
		system("pause");
		system("cls");
	}
}
void list3()
{
	char num;
	int lock;
	while (1)
	{
		cout << "============================================" << endl;
		cout << "----------------教师端----------------------" << endl;
		cout << "1,注册                                      " << endl;
		cout << "2.登录                                      " << endl;
		cout << "3.修改密码                                  " << endl;
		cout << "4.录入成绩                                  " << endl;
		cout << "5.修改成绩                                  " << endl;
		cout << "6.注销账号                                  " << endl;
		cout << "7.成绩升序排序                           " << endl;
		cout << "0.退出                                      " << endl;
		cout << "请输入你的选项：";
		cin >> num;
		lock = num - '0';
		switch (lock)
		{
		case 1:
			cout << "注册成功";
			break;
		case 2:
			cout << "登录成功";
			break;
		case 3:
			cout << "修改成功";
			break;
		case 4:
			cout << "开始录入";
			break;
		case 5:
			cout << "开始修改";
			break;
		case 6:
			cout << "注销成功";
			break;
		case 7:
			cout << "排序";
			break;
		default:
			cout << "终止程序";
			return;
		}
		system("pause");
		system("cls");
	}
}

/*int input(int max, bool isZero)
{
	string input;
again:
	std::cout << "请输入您的选项:";
	getline(cin, input);
	if (input.length() > 1)
	{
		cout << "输入错误,请重新输入" << endl;
		goto again;
	}
	int lock = input[0] - '0';
	if (isZero == true)
	{
		if (lock < 0 || lock> max)
		{
			cout << "输入错误,请重新输入" << endl;
			goto again;
		}
	}
	else
	{
		if (lock<1 || lock>max)
		{
			cout << "输入错误,请重新输入" << endl;
			goto again;
		}
	}
	return lock;
}*/



int main()
{
	char num;
	int lock;
	while (1)
	{
		list1();
		cout << "请输入你的选项：";
		cin >> num;
		lock = num - '0';
		switch (lock)
		{
		case 1:
			list2();
			break;
		case 2:
			list3();
			break;
		default:
			cout << "程序终止";
			return 0;
		}
		system("pause");
		system("cls");
	}
}