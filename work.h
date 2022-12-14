#include<iostream>
#include<fstream>
#include<string>
#include<cstring>
#include<iomanip>
using namespace std;
#define OK 1
#define ERROR 0
#define OVERFLOW -2
typedef int Status; //Status 是函数返回值类型，其值是函数结果状态代码。
#define ENDFLAG 0 //输入0 结束
#define MAXSIZE 100			//顺序表可能达到的最大长度
//最小不平衡子树的子树的高度值。
#define LH +1 //左高
#define EH 0 //等高
#define RH -1 //右高

typedef struct
{
	string id;//学号
	string password;//密码
	string name;//姓名
	string sex;//性别
	double math;//数学
	double englidh;//英语
	double java;//java
} Student;

typedef struct
{
	string id;//工号
	string password;//密码
} Teacher;

typedef struct
{
	Student* elem; //存储空间的基地址
	int length; //当前长度
} SqList1;

typedef struct BSTNode
{
	Student data;    //结点数据域,存数据元素
	BSTNode* lchild, * rchild;    //左右孩子指针
	int BF;//平衡因子
} BSTNode, * BSTree;

typedef struct
{
	Teacher* elem; //存储空间的基地址
	int length; //当前长度
} SqList2;

void back_Sq(BSTree& T, SqList1& L, int i);
void InitList_Sq1(SqList1& L);
void InitList_Sq2(SqList2& L);
void In_file(SqList1& L); //打开book.txt文件，数据写入到表L
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
{ //算法2.1 顺序表的初始化
	//构造一个空的顺序表L
	L.elem = new Student[MAXSIZE]; //为顺序表分配一个大小为MAXSIZE的数组空间
	if (!L.elem)
		exit(OVERFLOW); //存储分配失败退出
	L.length = 0; //空表长度为0
	return;
}

void InitList_Sq2(SqList2& L)
{ //算法2.1 顺序表的初始化
	//构造一个空的顺序表L
	L.elem = new Teacher[MAXSIZE]; //为顺序表分配一个大小为MAXSIZE的数组空间
	if (!L.elem)
		exit(OVERFLOW); //存储分配失败退出
	L.length = 0; //空表长度为0
	return;
}

void In_file(SqList1& L) //打开book.txt文件，数据写入到表L
{
	string head_1, head_2, head_3, head_4, head_5, head_6;
	int i;
	i = 0;
	InitList_Sq1(L);

	fstream file;
	file.open("Student.txt");//打开文件
	if (!file) {
		cout << "错误！未找到文件！" << endl;
		exit(ERROR);
	}
	file >> head_1 >> head_2 >> head_3 >> head_4 >> head_5 >> head_6; //获取抬头
	while (!file.eof()) { //文件未读取结束
		file >> L.elem[i].id >> L.elem[i].name >> L.elem[i].sex >> L.elem[i].math >> L.elem[i].englidh >> L.elem[i].java;
		i++;
	}
	cout << "输入 Student.txt 信息完毕\n";
	L.length = i;
	file.close();  //关闭文件
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
*对以P为跟结点的二叉排序树做右旋，旋转后p为新的根结点。
*/
void R_Rotate(BSTree* T) {
	BSTree L;
	L = (*T)->lchild; //p的左孩子，为新的根结点
	(*T)->lchild = L->rchild; //p的左孩子的右孩子，为p的左孩子
	L->rchild = (*T);//新的根结点右孩子，为原来的p
	*T = L;//指向新的根结点，原根结点的左孩子的左孩子指向没有变。
}

/*
*对p为根的二叉排序树做左旋处理，旋转后p为新的根结点
*/
void L_Rotate(BSTree* T) {
	BSTree R;
	R = (*T)->rchild;
	(*T)->rchild = R->lchild;
	R->lchild = (*T);
	*T = R;
}

/*
* 对T为根结点的最小不平衡子树做左平衡旋转
*/
void LeftBalance(BSTree* T) {
	BSTree L, Lr;
	L = (*T)->lchild;
	switch (L->BF) {
		//新插入结点在T的左孩子的左子树上，做右旋
	case LH:
		(*T)->BF = L->BF = EH;
		R_Rotate(T);
		break;
		//新插入结点在T的左孩子的右子树上，做双旋
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
		//对T的左子树做左旋
		L_Rotate(&((*T)->lchild));
		//对T做右旋
		R_Rotate(T);
	}
}

/*
 *对T为根结点的最小不平衡子树作右平衡旋转处理，
 */
void RightBalance(BSTree* T) {
	BSTree R, Rl;
	R = (*T)->rchild; /*	R指向T的右子树根结点 */
	switch (R->BF) { /*  检查T的右子树的平衡度，并作相应平衡处理 */
	case RH: /*  新结点插入在T的右孩子的右子树上，要作单左旋处理 */
		(*T)->BF = R->BF = EH;
		L_Rotate(T);
		break;
	case LH: /*  新结点插入在T的右孩子的左子树上，要作双旋处理 */
		Rl = R->lchild; /*  Rl指向T的右孩子的左子树根 */
		switch (Rl->BF) { /*	修改T及其右孩子的平衡因子 */
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
		R_Rotate(&(*T)->rchild); /*  对T的右子树作右旋平衡处理 */
		L_Rotate(T); /*  对T作左旋平衡处理 */
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
	if (!*T) { /*  插入新结点，树“长高”，置taller为TRUE */
		*T = new BSTNode;
		(*T)->data = e;
		(*T)->lchild = (*T)->rchild = NULL;
		(*T)->BF = EH;
		*taller = OK;
	}
	else {
		if (e.id == (*T)->data.id) { /*	树中已存在和e有相同关键字的结点则不再插入 */
			*taller = ERROR;
			return ERROR;
		}
		if (e.id < (*T)->data.id) { /*	应继续在T的左子树中进行搜索 */
			if (!InsertAVL1(&(*T)->lchild, e, taller, i)) /*	未插入 */
				return ERROR;
			if (*taller) { /*	已插入到T的左子树中且左子树“长高” */
				switch ((*T)->BF) {/*  检查T的平衡度 */
				case LH: /*  原本左子树比右子树高，需要作左平衡处理 */
					LeftBalance(T); *taller = ERROR;
					break;
				case EH: /*  原本左、右子树等高，现因左子树增高而使树增高 */
					(*T)->BF = LH; *taller = ERROR;
					break;
				case RH: /*  原本右子树比左子树高，现左、右子树等高 */
					(*T)->BF = EH; *taller = ERROR;
					break;
				}
			}
		}
		else { /*	应继续在T的右子树中进行搜索 */
			if (!InsertAVL1(&(*T)->rchild, e, taller, i)) /*	未插入 */
				return ERROR;
			if (*taller) { /*  已插入到T的右子树且右子树“长高” */
				switch ((*T)->BF) {/*  检查T的平衡度 */
				case LH: /*  原本左子树比右子树高，现左、右子树等高 */
					(*T)->BF = EH; *taller = ERROR;
					break;
				case EH: /*  原本左、右子树等高，现因右子树增高而使树增高  */
					(*T)->BF = RH; *taller = OK;
					break;
				case RH: /*  原本右子树比左子树高，需要作右平衡处理 */
					RightBalance(T); *taller = ERROR;
					break;
				}
			}
		}
	}
	return OK;
}

Status InsertAVL2(BSTree* T, string id, string password, Status* taller) {
	if (!*T) { /*  插入新结点，树“长高”，置taller为TRUE */
		*T = new BSTNode;
		(*T)->data.id = id;
		(*T)->data.password = password;
		(*T)->lchild = (*T)->rchild = NULL;
		(*T)->BF = EH;
		*taller = OK;
	}
	else {
		if (id == (*T)->data.id) { /*	树中已存在和e有相同关键字的结点则不再插入 */
			*taller = ERROR;
			return ERROR;
		}
		if (id < (*T)->data.id) { /*	应继续在T的左子树中进行搜索 */
			if (!InsertAVL2(&(*T)->lchild, id, password, taller)) /*	未插入 */
				return ERROR;
			if (*taller) { /*	已插入到T的左子树中且左子树“长高” */
				switch ((*T)->BF) {/*  检查T的平衡度 */
				case LH: /*  原本左子树比右子树高，需要作左平衡处理 */
					LeftBalance(T); *taller = ERROR;
					break;
				case EH: /*  原本左、右子树等高，现因左子树增高而使树增高 */
					(*T)->BF = LH; *taller = ERROR;
					break;
				case RH: /*  原本右子树比左子树高，现左、右子树等高 */
					(*T)->BF = EH; *taller = ERROR;
					break;
				}
			}
		}
		else { /*	应继续在T的右子树中进行搜索 */
			if (!InsertAVL2(&(*T)->rchild, id, password, taller)) /*	未插入 */
				return ERROR;
			if (*taller) { /*  已插入到T的右子树且右子树“长高” */
				switch ((*T)->BF) {/*  检查T的平衡度 */
				case LH: /*  原本左子树比右子树高，现左、右子树等高 */
					(*T)->BF = EH; *taller = ERROR;
					break;
				case EH: /*  原本左、右子树等高，现因右子树增高而使树增高  */
					(*T)->BF = RH; *taller = OK;
					break;
				case RH: /*  原本右子树比左子树高，需要作右平衡处理 */
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
	//在根指针T所指二叉平衡树中递归地查找某关键字等于key的数据元素
	//若查找成功，则返回指向该数据元素结点的指针，否则返回空指针
	if ((!T) || id == T->data.id)
	{
		return T;
	}
	else if (id < T->data.id)
	{
		return SearchBST(T->lchild, id);    //在左子树中继续查找
	}
	else
	{
		return SearchBST(T->rchild, id);    //在右子树中继续查找
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



void Out_file(SqList1 L) //表L的数据写回文件book.txt
{
	int i;
	Student e;
	string head_1, head_2, head_3, head_4, head_5, head_6;
	head_1 = "ID";
	head_2 = "姓名";
	head_3 = "性别";
	head_4 = "数学";
	head_5 = "英语";
	head_6 = "JAVA";

	fstream file("Student.txt", fstream::out | ios_base::trunc); //打开时清空文件
	if (!file) {
		cout << "错误！未找到文件！" << endl;
		exit(ERROR);
	}

	file << head_1 << "\t" << head_2 << "\t" << head_3 << "\t" << head_4 << "\t" << head_5 << "\t" << head_6 << endl;

	for (i = 0; i < L.length - 1 ; i++)
	{
		e = L.elem[i];
		file << left << e.id << "\t" << left << e.name << "\t" << left << e.sex << "\t" << left << e.math << "\t" << left << e.englidh << "\t" << left << e.java << endl;
	}
	e = L.elem[i];
	file << left << e.id << "\t" << left << e.name << "\t" << left << e.sex << "\t" << left << e.math << "\t" << left << e.englidh << "\t" << left << e.java;  //fstream最后一行写入文件不能有换行
	file.close();
}