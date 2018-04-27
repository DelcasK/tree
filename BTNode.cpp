//һ�������ʽ�ṹ�洢������
#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 100

//��ʽ�洢�ṹ �ṹ�嶨��
typedef struct BTNode
{
	int data;
	struct BTNode*lchild;
	struct BTNode*rchild;
}BTNode;

//�½���visit���������ڴ�����p
void visit(BTNode*p)
{
	/*���ʽ������*/
	printf("%d\t", p->data);
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


//��������Ŀ��
typedef struct                                                                                     //�½��ṹ���洢����Լ�����Ӧ�Ĳ���
{
	BTNode*p;
	int lno;
}St;
int maxNode(BTNode*q)
{
	St que[MAXSIZE];                                                                           //�ö��б����㣬�������ݲ�����ʧ��
	int front, rear,maxlno,max,n;                                                          // max��n����ѭ������ʱ�ҳ����,maxlno��¼�����Ĳ���
	front = rear = 0;
	if (q!=NULL)
	{
		++rear;                                                                                       //ͷ������
		que[rear].p = q;
		maxlno=que[rear].lno = 1;
		while (front!=rear)
		{
			++front;
			if (que[front].p->lchild) {
				++rear;
				que[rear].p = que[front].p->lchild;
				maxlno=que[rear].lno = que[front].lno + 1;                      //maxlno������Ĳ����仯
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
	for (int i = 1;i <= maxlno;++i)                                                       //���α�������max�������ֵ
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
	//����Ϊ�Ż���make by myself��
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

//�����������㷨�ĸĽ�
//�����Զ����ջ������ݹ飨�ݹ�ʵ������ϵͳͨ��ջ��ʵ�֣����Զ����ջЧ�ʻ���ߣ����Ⲣ���Ǿ��Եģ�
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
			if (p->rchild)                                               //��������������ص㣬�Һ�������ջ
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
			while (p)                                             //�жϽ�㲻Ϊ�գ��򽫽���������ջ��ѭ������
			{
				stack[++top] = p;
				p = p->lchild;
			}
			if (top!=-1)                                         //ջ��Ϊ�վͳ�ջһ����㣬����pָ���ջ�����ҽ�㣬�ٽ������ѭ��
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
//		BTNode*p=NULL;                                                     //p�����ж��ҽ���Ƿ�Ϊ��
//		int top = 0;
//		stack[top] = bt;
//		BTNode*q = stack[top];                                           //qʼ��ָ��ջ����λ�õĽ��
//		while (p || top != -1)
//		{
//			while (q->lchild)                                                   //�Ƚ�����ȫ����ջ
//			{
//				stack[++top] = q->lchild;
//				q = stack[top];
//			}
//			while (!q->rchild&&top!=-1)                                //��ջ�����жϳ�ջ�Ľ����ҽ���ǲ��ǿ�
//			{
//				p = NULL;
//				visit(stack[top--]);
//				q =top==-1?NULL: stack[top];
//			}
//			if (q->rchild)                                                          //������Ϊ�ҽ�㲻Ϊ�ն��˳�whileѭ�������ջ���ҽ����ջ���ٿ�ʼ�����ѭ��
//			{
//				visit(stack[top--]);
//				stack[++top] = q->rchild;
//				p = q->rchild;
//				q = p;
//			}
//		}
//	}
//}

void postorderNonrecursion(BTNode*bt)                            //�������ʱ�������Һ��ӵĽ�ջ˳�򽻻����õ�����������������У������ȵú����������
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

//����������
typedef struct TBTNode                                 //tagֵΪ0ʱ��childָ���ӣ�Ϊ1ʱָ��ǰ������
{
	int data;
	int ltag, rtag;
	struct TBTNode*lchild, *rchild;
}TBTNode;

//����������������
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

//�����������������������ҳ���һ����㣬�����½ǵĽ�㣬ע�Ⲣ��һ����Ҷ��㣩
TBTNode*First(TBTNode*p)                                    //�ҳ���һ�����
{
	while (p->ltag==0)
	{
		p = p->lchild;
	}
	return p;
}
TBTNode*Next(TBTNode*p)                                   //�ҳ�p���ĺ�̽��
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

//ǰ������������
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
			while (p->ltag==0)                      //��������ѭ��
			{
				visit2(p);
				p = p->lchild;
			}
			visit2(p);
			p = p->rchild;                              //��ʱ����rtagΪ���٣�������
		}
	}
}

//��������������
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

//���Դ���
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

