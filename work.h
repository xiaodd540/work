#include<iostream>
#include<fstream>
#include<string>
#include<cstring>
#include<iomanip>
using namespace std;
#define OK 1
#define ERROR 0
#define OVERFLOW -2
typedef int Status; //Status �Ǻ�������ֵ���ͣ���ֵ�Ǻ������״̬���롣
#define ENDFLAG 0 //����0 ����
#define MAXSIZE 100			//˳�����ܴﵽ����󳤶�
//��С��ƽ�������������ĸ߶�ֵ��
#define LH +1 //���
#define EH 0 //�ȸ�
#define RH -1 //�Ҹ�

typedef struct
{
	string id;//ѧ��
	string password;//����
	string name;//����
	string sex;//�Ա�
	double math;//��ѧ
	double englidh;//Ӣ��
	double java;//java
} Student;

typedef struct
{
	string id;//����
	string password;//����
} Teacher;

typedef struct
{
	Student* elem; //�洢�ռ�Ļ���ַ
	int length; //��ǰ����
} SqList1;

typedef struct BSTNode
{
	Student data;    //���������,������Ԫ��
	BSTNode* lchild, * rchild;    //���Һ���ָ��
	int BF;//ƽ������
} BSTNode, * BSTree;

typedef struct
{
	Teacher* elem; //�洢�ռ�Ļ���ַ
	int length; //��ǰ����
} SqList2;

void back_Sq(BSTree& T, SqList1& L, int i);
void InitList_Sq1(SqList1& L);
void InitList_Sq2(SqList2& L);
void In_file(SqList1& L); //��book.txt�ļ�������д�뵽��L
void InOrderTraverseBST2(BSTree& T, string id, string passward, int& n);
void InOrderTraverseBST1(BSTree T, string id, string passward, int& m);
void InOrderTraverseBST3(BSTree& T, string id, string name, string sex, int& r);
void InitList_Sq1(SqList1& L);
void InitList_Sq2(SqList2& L);


/*void createfile()
{
	fstream file;
	file.open("Student.txt", std::ios::out | std::ios::app);
	if (!file.is_open())
	{
		return;
	}
	file.close();
}*/

void InitList_Sq1(SqList1& L)
{ //�㷨2.1 ˳���ĳ�ʼ��
	//����һ���յ�˳���L
	L.elem = new Student[MAXSIZE]; //Ϊ˳������һ����СΪMAXSIZE������ռ�
	if (!L.elem)
		exit(OVERFLOW); //�洢����ʧ���˳�
	L.length = 0; //�ձ���Ϊ0
	return;
}

void InitList_Sq2(SqList2& L)
{ //�㷨2.1 ˳���ĳ�ʼ��
	//����һ���յ�˳���L
	L.elem = new Teacher[MAXSIZE]; //Ϊ˳������һ����СΪMAXSIZE������ռ�
	if (!L.elem)
		exit(OVERFLOW); //�洢����ʧ���˳�
	L.length = 0; //�ձ���Ϊ0
	return;
}

void In_file(SqList1& L) //��book.txt�ļ�������д�뵽��L
{
	string head_1, head_2, head_3, head_4, head_5, head_6;
	int i;
	i = 0;
	InitList_Sq1(L);

	fstream file;
	file.open("Student.txt");//���ļ�
	if (!file) {
		cout << "����δ�ҵ��ļ���" << endl;
		exit(ERROR);
	}
	file >> head_1 >> head_2 >> head_3 >> head_4 >> head_5 >> head_6; //��ȡ̧ͷ
	while (!file.eof()) { //�ļ�δ��ȡ����
		file >> L.elem[i].id >> L.elem[i].name >> L.elem[i].sex >> L.elem[i].math >> L.elem[i].englidh >> L.elem[i].java;
		i++;
	}
	cout << "���� Student.txt ��Ϣ���\n";
	L.length = i;
	file.close();  //�ر��ļ�
}

void InOrderTraverseBST1(BSTree T, string id, string password, int& m)
{
	if (T == NULL)
	{
		//cout << "T is null!" <<endl;
		return;
	}
	else {
		InOrderTraverseBST1(T->lchild, id, password, m);
		if (T->data.id == id && T->data.password == password)
		{
			m = 1;
		}
		InOrderTraverseBST1(T->rchild, id, password, m);
	}
}

/*
*����PΪ�����Ķ�������������������ת��pΪ�µĸ���㡣
*/
void R_Rotate(BSTree* T) {
	BSTree L;
	L = (*T)->lchild; //p�����ӣ�Ϊ�µĸ����
	(*T)->lchild = L->rchild; //p�����ӵ��Һ��ӣ�Ϊp������
	L->rchild = (*T);//�µĸ�����Һ��ӣ�Ϊԭ����p
	*T = L;//ָ���µĸ���㣬ԭ���������ӵ�����ָ��û�б䡣
}

/*
*��pΪ���Ķ���������������������ת��pΪ�µĸ����
*/
void L_Rotate(BSTree* T) {
	BSTree R;
	R = (*T)->rchild;
	(*T)->rchild = R->lchild;
	R->lchild = (*T);
	*T = R;
}

/*
* ��TΪ��������С��ƽ����������ƽ����ת
*/
void LeftBalance(BSTree* T) {
	BSTree L, Lr;
	L = (*T)->lchild;
	switch (L->BF) {
		//�²�������T�����ӵ��������ϣ�������
	case LH:
		(*T)->BF = L->BF = EH;
		R_Rotate(T);
		break;
		//�²�������T�����ӵ��������ϣ���˫��
	case RH:
		Lr = L->rchild;
		switch (Lr->BF) {
		case LH:
			(*T)->BF = RH;
			L->BF = EH;
			break;
		case EH:
			(*T)->BF = L->BF = EH;
			break;
		case RH:
			(*T)->BF = EH;
			L->BF = LH;
			break;
		}
		Lr->BF = EH;
		//��T��������������
		L_Rotate(&((*T)->lchild));
		//��T������
		R_Rotate(T);
	}
}

/*
 *��TΪ��������С��ƽ����������ƽ����ת����
 */
void RightBalance(BSTree* T) {
	BSTree R, Rl;
	R = (*T)->rchild; /*	Rָ��T������������� */
	switch (R->BF) { /*  ���T����������ƽ��ȣ�������Ӧƽ�⴦�� */
	case RH: /*  �½�������T���Һ��ӵ��������ϣ�Ҫ������������ */
		(*T)->BF = R->BF = EH;
		L_Rotate(T);
		break;
	case LH: /*  �½�������T���Һ��ӵ��������ϣ�Ҫ��˫������ */
		Rl = R->lchild; /*  Rlָ��T���Һ��ӵ��������� */
		switch (Rl->BF) { /*	�޸�T�����Һ��ӵ�ƽ������ */
		case RH:
			(*T)->BF = LH;
			R->BF = EH;
			break;
		case EH:
			(*T)->BF = R->BF = EH;
			break;
		case LH:
			(*T)->BF = EH;
			R->BF = RH;
			break;
		}
		Rl->BF = EH;
		R_Rotate(&(*T)->rchild); /*  ��T��������������ƽ�⴦�� */
		L_Rotate(T); /*  ��T������ƽ�⴦�� */
	}
}

void back_Sq(BSTree& T, SqList1& L, int i)
{
	if (T)
	{
		back_Sq(T->lchild, L, i);
		L.elem[i] = T->data;
		i++;
		back_Sq(T->rchild, L, i);
	}
	else
	{
		return;
	}
}

Status InsertAVL1(BSTree* T,Student e, Status* taller, int i) {
	if (!*T) { /*  �����½�㣬�������ߡ�����tallerΪTRUE */
		*T = new BSTNode;
		(*T)->data = e;
		(*T)->lchild = (*T)->rchild = NULL;
		(*T)->BF = EH;
		*taller = OK;
	}
	else {
		if (e.id == (*T)->data.id) { /*	�����Ѵ��ں�e����ͬ�ؼ��ֵĽ�����ٲ��� */
			*taller = ERROR;
			return ERROR;
		}
		if (e.id < (*T)->data.id) { /*	Ӧ������T���������н������� */
			if (!InsertAVL1(&(*T)->lchild, e, taller, i)) /*	δ���� */
				return ERROR;
			if (*taller) { /*	�Ѳ��뵽T�����������������������ߡ� */
				switch ((*T)->BF) {/*  ���T��ƽ��� */
				case LH: /*  ԭ�����������������ߣ���Ҫ����ƽ�⴦�� */
					LeftBalance(T); *taller = ERROR;
					break;
				case EH: /*  ԭ�����������ȸߣ��������������߶�ʹ������ */
					(*T)->BF = LH; *taller = ERROR;
					break;
				case RH: /*  ԭ�����������������ߣ������������ȸ� */
					(*T)->BF = EH; *taller = ERROR;
					break;
				}
			}
		}
		else { /*	Ӧ������T���������н������� */
			if (!InsertAVL1(&(*T)->rchild, e, taller, i)) /*	δ���� */
				return ERROR;
			if (*taller) { /*  �Ѳ��뵽T���������������������ߡ� */
				switch ((*T)->BF) {/*  ���T��ƽ��� */
				case LH: /*  ԭ�����������������ߣ������������ȸ� */
					(*T)->BF = EH; *taller = ERROR;
					break;
				case EH: /*  ԭ�����������ȸߣ��������������߶�ʹ������  */
					(*T)->BF = RH; *taller = OK;
					break;
				case RH: /*  ԭ�����������������ߣ���Ҫ����ƽ�⴦�� */
					RightBalance(T); *taller = ERROR;
					break;
				}
			}
		}
	}
	return OK;
}

Status InsertAVL2(BSTree* T, string id, string password, Status* taller) {
	if (!*T) { /*  �����½�㣬�������ߡ�����tallerΪTRUE */
		*T = new BSTNode;
		(*T)->data.id = id;
		(*T)->data.password = password;
		(*T)->lchild = (*T)->rchild = NULL;
		(*T)->BF = EH;
		*taller = OK;
	}
	else {
		if (id == (*T)->data.id) { /*	�����Ѵ��ں�e����ͬ�ؼ��ֵĽ�����ٲ��� */
			*taller = ERROR;
			return ERROR;
		}
		if (id < (*T)->data.id) { /*	Ӧ������T���������н������� */
			if (!InsertAVL2(&(*T)->lchild, id, password, taller)) /*	δ���� */
				return ERROR;
			if (*taller) { /*	�Ѳ��뵽T�����������������������ߡ� */
				switch ((*T)->BF) {/*  ���T��ƽ��� */
				case LH: /*  ԭ�����������������ߣ���Ҫ����ƽ�⴦�� */
					LeftBalance(T); *taller = ERROR;
					break;
				case EH: /*  ԭ�����������ȸߣ��������������߶�ʹ������ */
					(*T)->BF = LH; *taller = ERROR;
					break;
				case RH: /*  ԭ�����������������ߣ������������ȸ� */
					(*T)->BF = EH; *taller = ERROR;
					break;
				}
			}
		}
		else { /*	Ӧ������T���������н������� */
			if (!InsertAVL2(&(*T)->rchild, id, password, taller)) /*	δ���� */
				return ERROR;
			if (*taller) { /*  �Ѳ��뵽T���������������������ߡ� */
				switch ((*T)->BF) {/*  ���T��ƽ��� */
				case LH: /*  ԭ�����������������ߣ������������ȸ� */
					(*T)->BF = EH; *taller = ERROR;
					break;
				case EH: /*  ԭ�����������ȸߣ��������������߶�ʹ������  */
					(*T)->BF = RH; *taller = OK;
					break;
				case RH: /*  ԭ�����������������ߣ���Ҫ����ƽ�⴦�� */
					RightBalance(T); *taller = ERROR;
					break;
				}
			}
		}
	}
	return OK;
}

void InOrderTraverseBST2(BSTree& T, string id, string password, int& n)
{
	if (T == NULL)
	{
		//cout << "T is null!" <<endl;
		return;
	}
	else
	{
		InOrderTraverseBST2(T->lchild, id, password, n);
		if (T->data.id == id)
		{
			n = 1;
			T->data.password = password;
		}
		InOrderTraverseBST2(T->rchild, id, password, n);
	}
}

void InOrderTraverseBST3(BSTree& T, string id, string name, string sex, int& r)
{
	if (T == NULL)
	{
		//cout << "T is null!" <<endl;
		return;
	}
	else
	{
		InOrderTraverseBST3(T->lchild, id, name, sex, r);
		if (T->data.id == id)
		{
			r = 1;
			T->data.name = name;
			T->data.sex = sex;
		}
		InOrderTraverseBST3(T->rchild, id, name, sex, r);
	}
}

BSTree SearchBST(BSTree T, string id)
{
	//�ڸ�ָ��T��ָ����ƽ�����еݹ�ز���ĳ�ؼ��ֵ���key������Ԫ��
	//�����ҳɹ����򷵻�ָ�������Ԫ�ؽ���ָ�룬���򷵻ؿ�ָ��
	if ((!T) || id == T->data.id)
	{
		return T;
	}
	else if (id < T->data.id)
	{
		return SearchBST(T->lchild, id);    //���������м�������
	}
	else
	{
		return SearchBST(T->rchild, id);    //���������м�������
	}
}

Status delNode(BSTree& T, string id, Status& shorter) {
	if (T == NULL) {
		return ERROR;
	}
	else if (id == T->data.id) {
		BSTree tmp = NULL;
		if (T->lchild == NULL) {
			tmp = T;
			T = T->rchild;
			delete tmp;
			shorter = OK;
		}
		else if (T->rchild == NULL) {
			tmp = T;
			T = T->lchild;
			delete tmp;
			shorter = OK;
		}
		else {
			tmp = T->lchild;
			while (tmp->rchild) {
				tmp = tmp->rchild;
			}
			T->data = tmp->data;
			delNode(T->lchild, tmp->data.id, shorter);
		}
	}
	else if (id < T->data.id) {
		if (!delNode(T->lchild, id, shorter)) {
			return ERROR;
		}
		if (shorter) {
			switch (T->BF)
			{
			case LH:
				T->BF = EH;
				shorter = OK;
				break;
			case RH:
				RightBalance(&T);
				if (T->rchild->BF == EH) {
					shorter = ERROR;
				}
				else {
					shorter = OK;
				}
				break;
			case EH:
				T->BF = RH;
				shorter = ERROR;
				break;
			}
		}
	}
	else {
		if (!delNode(T->rchild, id, shorter)) {
			return false;
		}
		if (shorter) {
			switch (T->BF)
			{
			case LH:
				LeftBalance(&T);
				if (T->lchild->BF == EH) {
					shorter = false;
				}
				else {
					shorter = true;
				}
				break;
			case EH:
				T->BF = LH;
				shorter = false;
				break;
			case RH:
				T->BF = EH;
				shorter = true;
				break;
			}
		}
	}
	return OK;
}



void Out_file(SqList1 L) //��L������д���ļ�book.txt
{
	int i;
	Student e;
	string head_1, head_2, head_3, head_4, head_5, head_6;
	head_1 = "ID";
	head_2 = "����";
	head_3 = "�Ա�";
	head_4 = "��ѧ";
	head_5 = "Ӣ��";
	head_6 = "JAVA";

	fstream file("Student.txt", fstream::out | ios_base::trunc); //��ʱ����ļ�
	if (!file) {
		cout << "����δ�ҵ��ļ���" << endl;
		exit(ERROR);
	}

	file << head_1 << "\t" << head_2 << "\t" << head_3 << "\t" << head_4 << "\t" << head_5 << "\t" << head_6 << endl;

	for (i = 0; i < L.length - 1 ; i++)
	{
		e = L.elem[i];
		file << left << e.id << "\t" << left << e.name << "\t" << left << e.sex << "\t" << left << e.math << "\t" << left << e.englidh << "\t" << left << e.java << endl;
	}
	e = L.elem[i];
	file << left << e.id << "\t" << left << e.name << "\t" << left << e.sex << "\t" << left << e.math << "\t" << left << e.englidh << "\t" << left << e.java;  //fstream���һ��д���ļ������л���
	file.close();
}