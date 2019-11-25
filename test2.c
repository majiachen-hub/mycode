#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<malloc.h>

#define maxSize 1000
#define DataCount 20;
#define MaxData 100;
#define MinData 0;
#define weight 1;	//有向表权重

int count=0;
int count_root = 0;

typedef struct struct_bitree	//定义节点结构体
{
	int data;
	int lflag;
	int rflag;
	struct struct_bitree *lchild;
	struct struct_bitree *rchild;
}bitree;

typedef struct ArcNode {	//定义链表类型（表节点）
	int adjvex;
	struct ArcNode *nextarc;
	int info;
}ArcNode;

typedef struct {			//定义邻接表的表头类型（头节点）
	int data;
	ArcNode *firstarc;
}Vnode;

typedef struct {			//定义图
	Vnode adjlist[maxSize];
	int n, e;
}AGraph;

bitree *BSTinsert(bitree *root, int e)	//生成二叉排序树
{
	if (root == NULL)
	{
		root = (bitree *)malloc(sizeof(bitree));
		root->data = e;
		root->lchild = NULL;
		root->rchild = NULL;
		return root;
	}
	else if (e < root->data)
	{
		root->lchild = BSTinsert(root->lchild, e);
		printf("父节点为:%d,e值为：%d，为左子节点\n\n\n",root->data,e);
		return root;
	}
	else
	{
		root->rchild = BSTinsert(root->rchild, e);
		printf("父节点为:%d,e值为：%d，为右子节点\n\n\n", root->data, e);
		return root;
	}
}

void visit(bitree *root)	//输出打印函数
{
	if (root->lchild != NULL)
	{
		root->lflag = 1;
	}
	else
	{
		root->lflag = 0;
	}
	if (root->rchild != NULL)
	{
		root->rflag = 1;
	}
	else
	{
		root->rflag = 0;
	}
	printf("%d\n", root->data);
}

int TreeHeigh(bitree *root)
{
	if (root == NULL)
	{
		return 0;
	}
	else
	{
		return 1 + max(TreeHeigh(root->lchild), TreeHeigh(root->rchild));
	}
}

int countleaf(bitree *root)	//计算叶子
{
	if (root == NULL)
	{
		return 0;
	}
	else if (root->lchild == NULL && root->rchild == NULL)
	{
		count++;
		
	}
	else
	{
		countleaf(root->lchild);
		countleaf(root->rchild);
	}
	return count;
}

void inorder(bitree *root)	//中序遍历函数(递归)
{
	if (root != NULL)
	{
		inorder(root->lchild);
		visit(root);
		inorder(root->rchild);
	}
}

void save_ROOT(bitree *root, bitree **ROOT)	   //将产生的节点地址保存到ROOT中
{
	if (root != NULL)
	{
		save_ROOT(root->lchild, ROOT);
		ROOT[count_root++] = root;
		//printf("root地址为：%d\n", root);
		//printf("ROOT[%d]地址为：%d\n", count_root-1, ROOT[count_root-1]);
		save_ROOT(root->rchild, ROOT);
	}
}

bitree *CopyTree(bitree *toproot)	//复制二叉树
{
	if (toproot == NULL)
	{
		return NULL;
	}
	else
	{
		bitree *newtree;
		newtree = (bitree *)malloc(sizeof(bitree));
		newtree->data = toproot->data;
		newtree->lchild = CopyTree(toproot->lchild);
		newtree->rchild = CopyTree(toproot->rchild);
		return newtree;
	}
}

bitree *Find(bitree *root, int n)	//查找节点
{
	if (n == root->data)
	{
		printf("查找成功\n");
		printf("数据为：%d\n", root->data);
		printf("数据节点地址为：%d\n", root);
		return root;
	}
	else if (n < root->data)
	{
		Find(root->lchild, n);

	}
	else
	{
		Find(root->rchild, n);
	}
}

/*bitree *Find_Father_Node(bitree *root, int n)	//查找节点
{
	if (root->lchild == NULL)
	{
		return;
	}
	else if (n == root->lchild->data)
	{
		printf("父节点查找成功\n");
		printf("父节点数据为：%d\n", root->data);
		printf("父亲节点地址为：%d\n", root);
		return root;
	}
	else if (root->rchild == NULL)
	{
		return;
	}
	else if (n == root->rchild->data)
	{
		printf("查找成功\n");
		printf("父亲节点数据为：%d\n", root->data);
		printf("父亲节点地址为：%d\n", root);
		return root;
	}
	else if (n < root->data)
	{
		Find_Father_Node(root->lchild, n);

	}
	else if(n > root->data)
	{
		Find_Father_Node(root->rchild, n);
	}
}*/

int Delete(bitree *tree, int x)		//删除节点
{

	bitree *cur = tree;
	bitree *parent = tree;
	bitree *del = NULL;

	while (cur)
	{
		if (cur->data > x)
		{
			parent = cur;
			cur = cur->lchild;
		}
		else if (cur->data < x)
		{
			parent = cur;
			cur = cur->rchild;
		}
		else
		{
			del = cur;

			if (cur->lchild == NULL)	//左孩子为空
			{
				if (parent->lchild == cur)
					parent->lchild = cur->rchild;
				else if (parent->rchild == cur)
					parent->rchild = cur->rchild;
				else if (parent == cur)		//没有父亲节点时
					tree = parent->rchild;
			}
			else if (cur->rchild == NULL)	 //右孩子为空
			{
				if (parent->lchild == cur)
					parent->lchild = cur->lchild;
				else if (parent->rchild == cur)
					parent->rchild = cur->rchild;
				else if (parent == cur)		//没有父亲节点时
					tree = parent->rchild;
			}
			else //左右孩子都不为空
			{
				bitree *sub = cur->rchild;
				while (sub->lchild)
				{
					parent = sub;
					sub = sub->lchild;
				}

				del = sub;
				cur->lchild = sub->data;

				if (parent->lchild == sub)
					parent->lchild = sub->rchild;
				else
					parent->rchild = sub->rchild;
			}

			free(del);
			del = NULL;
			return 0;

		}
	}

	return -1;
}

AGraph *graph;

void  insertNode(ArcNode *node, ArcNode *newNode)	//向邻接表中插入节点
{		
	ArcNode *p = node;
	while (p->nextarc != NULL) {
		p = p->nextarc;
	}
	p->nextarc = newNode;
}

void create(bitree **ROOT)		//创建邻接表
{
	bitree *root;
	graph = (AGraph*)malloc(sizeof(AGraph));
	graph->n = MaxData;
	graph->e = DataCount;
	printf("数据最大值：%d\n", graph->n);

	int u = -1, v = -1;
	for (int i = 0; i < graph->n; i++) {
		graph->adjlist[i].firstarc = NULL;
	}

	ArcNode *node;
	printf("节点个数：%d\n", graph->e);
	for (int i = 0; i < graph->e; i++) {
		root = ROOT[i];
		u = root->data;
		while (root->lflag != 0 || root->rflag != 0)
		{
			if (root->lflag != 0 && root->lchild != NULL)
			{
				v = root->lchild->data;
				root->lflag = 0;
			}
			else if (root->rflag != 0 && root->rchild!= NULL)
			{
				v = root->rchild->data;
				root->rflag = 0;
			}
			node = (ArcNode *)malloc(sizeof(ArcNode));
			node->adjvex = v;
			node->info = weight;
			node->nextarc = NULL;
			graph->adjlist[u].data = u;
			if (graph->adjlist[u].firstarc == NULL) {
				graph->adjlist[u].firstarc = node;
			}
			else {
				insertNode(graph->adjlist[u].firstarc, node);
			}
		}
	}
}

void  travseTree() {		//遍历邻接表
	printf("邻接表输出为：\n");
	for (int i = 0; i < graph->n; i++) {
		if (graph->adjlist[i].firstarc != NULL) {
			printf("%d ->", i);
			ArcNode *p = graph->adjlist[i].firstarc;
			while (p != NULL) {
				printf("%d ->", p->adjvex);
				p = p->nextarc;
			}
			printf("\n");
		}
	}
}

int main()
{
	int pasue, flag = 1, input;
	int a, i = 0;
	int high,count,datacount;
	int array[100] = { 0 };	//判断0-100内随机数有无重复
	bitree *newtree,*father_node,*son_node;
	////int num[20] = { 0 };		//保存生成的20个随机数
	////datacount = 20;
	////int n;
	////printf("请输入数组大小:");
	////scanf("%d", &n);
	datacount = DataCount;
	int *num = (int *)malloc(sizeof(int)*datacount);
	////datacount = DataCount;
	////int test[int(DataCount)] = { 0 };
	bitree *root = NULL, *toproot = NULL;
	bitree **ROOT = (bitree *)malloc(sizeof(bitree)*datacount);


	srand((unsigned)time(NULL));
	////while (num[n] == 0)
	while (i < datacount)////
	{
		a = rand() % MaxData;
		if (array[a] == 0)
		{
			printf("###################################\n");
			printf("------------a的值为：%d------------\n", a);
			array[a] = 1;
			num[i] = a;
			i++;
			root = BSTinsert(root, a);
			printf("---root:%d-----", root);
			if (flag)
			{
				toproot = root;
				flag = 0;
			}
			printf("root元素：%d\n", root->data);
		}
	}

	////free(num);
	newtree = CopyTree(toproot);
	save_ROOT(toproot, ROOT);

	printf("_________________________________\n\n");

	printf("二叉排序树复制完成\n");
	printf("新的二叉树：\n");
	printf("newtree->data:%d\n", newtree->data);
	printf("新的二叉树首地址为：%d\n\n", newtree);

	//printf("旧的二叉树首地址为：%d\n", toproot);
	//printf("toproot->data值为：%d\n\n", toproot->data);

	printf("中序遍历结果为：\n");
	inorder(toproot);

	printf("请输入要查找的数：");
	scanf("%d", &input);
	son_node=Find(toproot,input);

	printf("请输入要删除的数（须为序列中的数）：");
	scanf("%d", &input);
	son_node = Find(newtree, input);

	Delete(newtree, input);
	printf("副本中序遍历结果为：\n");
	inorder(newtree);

	create(ROOT);
	travseTree();

	//count = countleaf(toproot);
	//high = TreeHeigh(toproot);

	//datacount = DataCount;
	//printf("数据元素有%d个\n",datacount);
	//printf("叶子节点有：%d个\n",count);
	//printf("二叉树高度为：%d\n", high);

	printf("输入任意数字结束程序：");
	scanf("%d",&pasue);
	return 0;
}
