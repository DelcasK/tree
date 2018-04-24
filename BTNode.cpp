//一般采用链式结构存储二叉树
#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 100

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

//求树的深度
int getDepth(BTNode*p)
{
	int ld, rd;//左树深度，右树深度
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

//匹配数据，返回结点
void search(BTNode*p, BTNode*&q, int key)        //q用于存储返回的结点的指针，key为要匹配的数据
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

//同上，进行剪枝操作优化
void search2(BTNode*p, BTNode*&q, int key)        //q用于存储返回的结点的指针，key为要匹配的数据
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

//打印遍历的第k个数据，分别为先序，中序，后序
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


//层次遍历
void level(BTNode*p)
{
	BTNode*que[MAXSIZE];                                 //用队列存放结点
	int front, rear;
	front = rear = 0;
	BTNode*q;
	if (p != NULL)
	{
		rear = (rear + 1) % MAXSIZE;                     //头结点入队
		que[rear] = p;
		while (front!=rear)
		{
			front = (front + 1) % MAXSIZE;              //队头结点出队
			q = que[front];
			visit(q);
			if (q->lchild)                                            //先判断左结点，再判断右结点，入队
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
