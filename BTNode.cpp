//一般采用链式结构存储二叉树
#include<stdio.h>
#include<stdlib.h>

//链式存储结构 结构体定义
typedef struct 
{
	int data;
	BTNode*lchild;
	BTNode*rchild;
}BTNode;

//新建空visit方法，用于处理结点p
void visit(BTNode*p)
{
	/*访问结点数据*/
}

//三种遍历方式写法相似，区别在于打印的顺序
//主要做法是先判断结点是否为空，不为空则递归

//1先序遍历
void preorder(BTNode*p) 
{
	if (p != NULL)
	{
		visit(p);
		preorder(p->lchild);
		preorder(p->rchild);
	}
}

//2中序遍历
void inorder(BTNode*p)
{
	if (p != NULL)
	{
		preorder(p->lchild);
		visit(p);
		preorder(p->rchild);
	}
}

//3后序遍历
void postorder(BTNode*p)
{
	if (p != NULL)
	{
		preorder(p->lchild);
		preorder(p->rchild);
		visit(p);
	}
}



