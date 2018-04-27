//一般采用链式结构存储二叉树
#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 100

//链式存储结构 结构体定义
typedef struct BTNode
{
	int data;
	struct BTNode*lchild;
	struct BTNode*rchild;
}BTNode;

//新建空visit方法，用于处理结点p
void visit(BTNode*p)
{
	/*访问结点数据*/
	printf("%d\t", p->data);
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


//求二叉树的宽度
typedef struct                                                                                     //新建结构，存储结点以及结点对应的层数
{
	BTNode*p;
	int lno;
}St;
int maxNode(BTNode*q)
{
	St que[MAXSIZE];                                                                           //用队列保存结点，结点的数据不会消失，
	int front, rear,maxlno,max,n;                                                          // max和n用于循环队列时找出宽度,maxlno记录最深层的层数
	front = rear = 0;
	if (q!=NULL)
	{
		++rear;                                                                                       //头结点入队
		que[rear].p = q;
		maxlno=que[rear].lno = 1;
		while (front!=rear)
		{
			++front;
			if (que[front].p->lchild) {
				++rear;
				que[rear].p = que[front].p->lchild;
				maxlno=que[rear].lno = que[front].lno + 1;                      //maxlno跟随结点的层数变化
			}
			if (que[front].p->rchild) {
				++rear;
				que[rear].p = que[front].p->rchild;
				maxlno=que[rear].lno = que[front].lno + 1;
			}
		}
	}
	else
	{
		return 0;
	}
	max = 0;
	for (int i = 1;i <= maxlno;++i)                                                       //两次遍历，用max保留最大值
	{
		n = 0;
		for (int j = 1;j <= rear;++j)
		{
			if (que[j].lno = i)
			{
				++n;
			}
		}
		if (max<n)
		{
			max = n;
		}
	}
	//以下为优化（make by myself）
	//max = n = 1;                                                                                  
	//for (int i = 1;i <= rear;++i)
	//{
	//	if (i > 2&&que[i].lno==que[i-1].lno)
	//	{
	//		++n;
	//	}
	//	else
	//	{
	//		n = 1;
	//	}
	//	max = n > max ? n : max;
	//}
	return max;
}

//二叉树遍历算法的改进
//即用自定义的栈来代替递归（递归实际上是系统通过栈来实现，用自定义的栈效率会更高，但这并不是绝对的）
void preorderNonrecuision(BTNode*bt)
{
	if (bt!=NULL)
	{
		BTNode*stack[MAXSIZE];
		BTNode*p;
		int top = 0;
		stack[top] = bt;
		while (top!=-1)
		{
			p = stack[top];
			visit(p);
			--top;
			if (p->rchild)                                               //根据先序遍历的特点，右孩子先入栈
			{
				++top;
				stack[top] = p->rchild;
			}
			if (p->lchild)
			{
				++top;
				stack[top] = p->lchild;
			}
		}
	}
}
 
void inorderNonrecursion(BTNode*bt)
{
	if (bt)
	{
		BTNode*stack[MAXSIZE];
		int top = -1;
		BTNode*p;
		p = bt;
		while (p||top!=-1)
		{
			while (p)                                             //判断结点不为空，则将结点的左结点入栈，循环进行
			{
				stack[++top] = p;
				p = p->lchild;
			}
			if (top!=-1)                                         //栈不为空就出栈一个结点，并将p指向出栈结点的右结点，再进入外层循环
			{
				p = stack[top--];
				visit(p);
				p = p->rchild;
			}
		}
	}
}
//made by myself
//void inorderNonrecursion1(BTNode*bt)                   
//{
//	if (bt)
//	{
//		BTNode*stack[MAXSIZE];
//		BTNode*p=NULL;                                                     //p用于判断右结点是否为空
//		int top = 0;
//		stack[top] = bt;
//		BTNode*q = stack[top];                                           //q始终指向栈顶的位置的结点
//		while (p || top != -1)
//		{
//			while (q->lchild)                                                   //先将左结点全部入栈
//			{
//				stack[++top] = q->lchild;
//				q = stack[top];
//			}
//			while (!q->rchild&&top!=-1)                                //出栈，并判断出栈的结点的右结点是不是空
//			{
//				p = NULL;
//				visit(stack[top--]);
//				q =top==-1?NULL: stack[top];
//			}
//			if (q->rchild)                                                          //若是因为右结点不为空而退出while循环，则出栈后将右结点入栈，再开始最外层循环
//			{
//				visit(stack[top--]);
//				stack[++top] = q->rchild;
//				p = q->rchild;
//				q = p;
//			}
//		}
//	}
//}

void postorderNonrecursion(BTNode*bt)                            //先序遍历时，将左右孩子的进栈顺序交换，得到的序列是逆后序序列，逆序后既得后序遍历序列
{
	if (bt)
	{
		BTNode*stack1[MAXSIZE], *stack2[MAXSIZE];
		int top1 = 0, top2 = -1;
		stack1[top1] = bt;
		BTNode*p=NULL;
		while (top1!=-1)
		{
			p= stack1[top1--];
			stack2[++top2] = p;
			if (p->lchild)
			{
				stack1[++top1]=p->lchild;
			}
			if (p->rchild)
			{
				stack1[++top1]=p->rchild;
			}
		}
		while (top2!=-1)
		{
			p = stack2[top2--];
			visit(p);
		}
	}
}

//线索二叉树
typedef struct TBTNode                                 //tag值为0时，child指向孩子，为1时指向前（后）驱
{
	int data;
	int ltag, rtag;
	struct TBTNode*lchild, *rchild;
}TBTNode;

//二叉树中序线索化
void inThread(TBTNode*p, TBTNode*&pre)
{
	if (p)
	{
		inThread(p->lchild, pre);
		if (p->lchild==NULL)
		{
			p->lchild = pre;
			p->ltag = 1;
		}
		if (pre != NULL && pre->rchild==NULL)
		{
			pre->rchild = p;
			pre->rtag = 1;
		}
		pre = p;
		p = p->rchild;
		inThread(p, pre);
	}
}
void createInThread(TBTNode*root)
{
	TBTNode*pre = NULL;
	if (root != NULL)
	{
		inThread(root, pre);
		pre->rchild = NULL;
		pre->rtag = 1;
	}
}

//遍历中序线索二叉树（先找出第一个结点，即左下角的结点，注意并不一定是叶结点）
TBTNode*First(TBTNode*p)                                    //找出第一个结点
{
	while (p->ltag==0)
	{
		p = p->lchild;
	}
	return p;
}
TBTNode*Next(TBTNode*p)                                   //找出p结点的后继结点
{
	if (p->rtag == 0)
	{
		return First(p->rchild);
	}
	return p->rchild;
}
void visit2(TBTNode*p)
{
	printf("%d", p->data);
}
void Inorder(TBTNode*root) 
{
	TBTNode*p = First(root);
	do
	{
		visit2(p);
		p = Next(p);
	} while (p);
}

//前序线索二叉树
void preThread(TBTNode*p, TBTNode*&pre)
{
	if (p != NULL)
	{
		if (p->lchild==NULL)
		{
			p->ltag = 1;
			p->lchild = pre;
		}
		if (pre!=NULL&&pre->rchild==NULL)
		{
			p->rtag = 1;
			p->rchild = p;
		}
		pre = p;
		if (p->ltag==0)
		{
			preThread(p->lchild, pre);
		}
		if (p->rtag==0)
		{
			preThread(p->rchild, pre);
		}
	}
}
void preorder(TBTNode*root)
{
	if (root != NULL)
	{
		TBTNode*p = root;
		while (p)
		{
			while (p->ltag==0)                      //向左方向做循环
			{
				visit2(p);
				p = p->lchild;
			}
			visit2(p);
			p = p->rchild;                              //此时无论rtag为多少，都可以
		}
	}
}

//后序线索二叉树
void postThread(TBTNode*p,TBTNode*&pre)
{
	if (p)
	{
		postThread(p->lchild, pre);
		postThread(p->rchild, pre);
		if (p->lchild == NULL)
		{
			p->ltag = 1;
			p->lchild = pre;
		}
		if (pre&&pre->rchild==NULL)
		{
			p->rtag = 1;
			p->rchild = p;
		}
		pre = p;
	}
}

//测试代码
int main()
{
	BTNode a, b, c, d, e;
	BTNode *a1, *b1, *c1, *d1, *e1;
	a1 = &a;
	b1 = &b;
	c1 = &c;
	d1 = &d;
	e1 = &e;
	a.data = 1;
	a.lchild = b1;
	a.rchild = c1;
	b.data = 2;
	b.lchild = d1;
	b.rchild = e1;
	c.data = 3;
	c.lchild = NULL;
	c.rchild = NULL;
	d.data = 4;
	d.lchild = NULL;
	d.rchild = NULL;
	e.data = 5;
	e.lchild = NULL;
	e.rchild = NULL;
	inorderNonrecursion(a1);
}

