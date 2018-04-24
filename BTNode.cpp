//һ�������ʽ�ṹ�洢������
#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 100

//��ʽ�洢�ṹ �ṹ�嶨��
typedef struct 
{
	int data;
	BTNode*lchild;
	BTNode*rchild;
}BTNode;

//�½���visit���������ڴ�����p
void visit(BTNode*p)
{
	/*���ʽ������*/
}

//���ֱ�����ʽд�����ƣ��������ڴ�ӡ��˳��
//��Ҫ���������жϽ���Ƿ�Ϊ�գ���Ϊ����ݹ�

//1�������
void preorder(BTNode*p) 
{
	if (p != NULL)
	{
		visit(p);
		preorder(p->lchild);
		preorder(p->rchild);
	}
}

//2�������
void inorder(BTNode*p)
{
	if (p != NULL)
	{
		preorder(p->lchild);
		visit(p);
		preorder(p->rchild);
	}
}

//3�������
void postorder(BTNode*p)
{
	if (p != NULL)
	{
		preorder(p->lchild);
		preorder(p->rchild);
		visit(p);
	}
}

//���������
int getDepth(BTNode*p)
{
	int ld, rd;//������ȣ��������
	if (p)
	{
		ld = getDepth(p->lchild);
		rd = getDepth(p->rchild);
		return (ld>rd?ld:rd)+1;
	}
	else
	{
		return 0;
	}
}

//ƥ�����ݣ����ؽ��
void search(BTNode*p, BTNode*&q, int key)        //q���ڴ洢���صĽ���ָ�룬keyΪҪƥ�������
{
	if (p != NULL)
	{
		if (p->data == key)
		{
			q = p;
		}
		else
		{
			search(p->lchild, q, key);
			search(p->rchild, q, key);
		}
	}
}

//ͬ�ϣ����м�֦�����Ż�
void search2(BTNode*p, BTNode*&q, int key)        //q���ڴ洢���صĽ���ָ�룬keyΪҪƥ�������
{
	if (p != NULL)
	{
		if (p->data == key)
		{
			q = p;
		}
		else
		{
			search(p->lchild, q, key);
			if(q==NULL) search(p->rchild, q, key);
		}
	}
}

//��ӡ�����ĵ�k�����ݣ��ֱ�Ϊ�������򣬺���
void trave1(BTNode*p, int k)
{
	static int n = 0;
	if (p!=NULL)
	{
		++n;
		if (k == n)
		{
			printf("%d", p->data);
			return;
		}
		trave1(p->lchild, k);
		trave1(p->rchild, k);
	}
}

void trave2(BTNode*p, int k)
{
	static int n = 0;
	if (p != NULL)
	{
		trave2(p->lchild, k);
		++n;
		if (k == n)
		{
			printf("%d", p->data);
			return;
		}
		trave2(p->rchild, k);
	}
}

void trave3(BTNode*p, int k)
{
	static int n = 0;
	if (p != NULL)
	{
		trave3(p->lchild, k);
		trave3(p->rchild, k);
		++n;
		if (k == n)
		{
			printf("%d", p->data);
			return;
		}
	}
}


//��α���
void level(BTNode*p)
{
	BTNode*que[MAXSIZE];                                 //�ö��д�Ž��
	int front, rear;
	front = rear = 0;
	BTNode*q;
	if (p != NULL)
	{
		rear = (rear + 1) % MAXSIZE;                     //ͷ������
		que[rear] = p;
		while (front!=rear)
		{
			front = (front + 1) % MAXSIZE;              //��ͷ������
			q = que[front];
			visit(q);
			if (q->lchild)                                            //���ж����㣬���ж��ҽ�㣬���
			{
				rear = (rear + 1) % MAXSIZE;
				que[rear] = q->lchild;
			}
			if (q->rchild)
			{
				rear = (rear + 1) % MAXSIZE;
				que[rear] = q->rchild;
			}
		}
	}
}
