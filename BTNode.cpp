//һ�������ʽ�ṹ�洢������
#include<stdio.h>
#include<stdlib.h>

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



