#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>
#define infinity 10000			//定义一个无限大的值 确保 所有的 权值都可以参与编码
/*哈夫曼树类型定义*/
typedef struct
{
	char ch;      //字母
	unsigned int weight;             //权值
	unsigned int parent,lchild,rchild; //节点之间的关系
}HTNode,*HuffmanTree; 

typedef char **HuffmanCode; /*存放哈夫曼编码*/
HuffmanTree HT;
HuffmanCode HC;
int *w,n,s;
char *x;

//查找所有的节点 返回一个最小的节点
int Min(HuffmanTree t,int n) //返回树中n个结点中权值最小的结点序号
{ 
	int i,flag;
	int f=infinity;					//f为一个无限大的值
	for(i=1;i<=n;i++)
		if(t[i].weight<f&&t[i].parent==0) 
			f=t[i].weight,flag=i;
		t[flag].parent=1;			//给选中的结点的双亲结点赋值1，避免再次查找该结点
		return flag;
}

//每次取最小的两个节点
void Select(HuffmanTree *t,int n,int *s1,int *s2)//在n个结点中选择两个权值最小的结点序号，其中s1最小，s2次小
{ 
	int x;
	*s1=Min(*t,n);
	*s2=Min(*t,n);
	if((*t)[*s1].weight>(*t)[*s2].weight)	/*如果序号s1的权值大于序号s2的权值，将两者交换，使s1最小，s2次小*/
	{
		x=*s1;
		*s1=*s2;
		*s2=x;
	}
}

//编码 
void HuffmanCoding(HuffmanTree *HT,HuffmanCode *HC,int *w,int n,char *x)//构造哈夫曼树HT，哈夫曼树的编码存放在HC中，w为n个字符的权值
{ 
	int m,i,s1,s2,start;
	unsigned int c,f;
	HuffmanTree p;
	char *cd;
	if(n<=1)
		return;
	m=2*n-1;
	*HT=(HuffmanTree)malloc((m+1)*sizeof(HTNode)); //*第零个单元未用
	for(p=*HT+1,i=1;i<=n;++i,++p,++w,++x)				/*初始化n个叶子结点*/
	{
		(*p).weight=*w;
		(*p).ch=*x;
		(*p).parent=0;
		(*p).lchild=0;
		(*p).rchild=0;
	}
	for(;i<=m;++i,++p)									/*将n-1个非叶子结点的双亲结点初始化化为0*/
		(*p).parent=0;
	for(i=n+1;i<=m;++i)			/*构造哈夫曼树*/
	{ 
		Select(HT,i-1,&s1,&s2);	/*查找树中权值最小的两个结点*/
		(*HT)[s1].parent=(*HT)[s2].parent=i;
		(*HT)[i].lchild=s1;
		(*HT)[i].rchild=s2;
		(*HT)[i].weight=(*HT)[s1].weight+(*HT)[s2].weight; //最小的两个权值和 替换
	}
	/*从叶子结点到根结点求每个字符的哈夫曼编码*/
	*HC=(HuffmanCode)malloc((n+1)*sizeof(char*));
	cd=(char*)malloc(n*sizeof(char));		/*为哈夫曼编码动态分配空间*/
	cd[n-1]='\0'; 
	/*求n个叶子结点的哈夫曼编码*/
	for(i=1;i<=n;i++) //每一次判断父节点的 int型的左右孩子的值  奇数是左孩子编码0 偶数是右孩子 编码是1
	{ 
		start=n-1;												/*编码结束符位置*/
		for(c=i,f=(*HT)[i].parent;f!=0;c=f,f=(*HT)[f].parent)	/*从叶子结点到根结点求编码*/
			if((*HT)[f].lchild==c)//1
			{
				cd[--start]='0';
			}
			else
			{//2
				cd[--start]='1';
			}
			(*HC)[i]=(char*)malloc((n-start)*sizeof(char));	/*为第i个字符编码分配空间*/
			strcpy((*HC)[i],&cd[start]);						/*将当前求出结点的哈夫曼编码复制到HC*/
	}

	free(cd);
	
}

//===================================================================================
//解码 根据编码找到 最顶尖的根节点的成员x值    确定那一层的 节点    然后 确定是左右哪个节点

void HuffmanCodeprint(HuffmanTree *HT,HuffmanCode *HC,int n)
//*构造哈夫曼树HT，哈夫曼树的编码存放在HC中，w为n个字符的权值
{ 
	int k;
	char cd[100];
	int m,i,start;

	unsigned int c,f;
	if(n<=1)
		return;
	printf("请输入编码\n");
	getchar();
	gets(cd);
		printf("解码：");
    m=2*n-1;
	i=m;
	start=0;
	while(1)
	 {
		if(cd[start]=='2')
		{
			printf("\n");
			break;
		}
		else
		{
			  if(cd[start]=='0')
			  {
			   i=(*HT)[i].lchild;   //走向左孩子
			  // printf("i==%d ",i);
			  // printf("\n");
			  }
			  else if(cd[start]=='1')
			  {
			   i=(*HT)[i].rchild;   //走向右孩子
			   //printf("rf==%d ",i);
			  // printf("\n");
			  }
			  else
			  {
				  printf("输入编码有误");
				  break;
			  }
			  if((*HT)[i].lchild==0)     //tree[i]是叶结点
			  {
			   printf("%c",(*HT)[i].ch);
			   i=m;		     //回到根结点
			  }
			  start++;
		}		  
	 }
}

//======================================================================================

void HuffmanCodebiao(HuffmanTree *HT)
{
	int i;
		for(i=1;i<=n;i++)
	{
		printf("%c",(*HT)[i].ch);
		printf("哈夫曼编码:");
		puts(HC[i]);
	}
}


void HuffmanCoderule()
{
	
	printf("请输入叶子结点的个数: ");
	scanf("%d",&n);
	getchar();
	w=(int*)malloc(n*sizeof(int));		//*为n个结点的权值分配内存空间
	x=(char*)malloc(n*sizeof(char));
	for(s=0;s<n;s++)
	{
		printf("请输入第%d个结点的权值:",s+1); //第一个节点没用
		scanf("%d",w+s);
		getchar();
		printf("请输入第%d个结点的word:",s+1); //第一个节点没用
		scanf("%c",x+s );
		getchar();
	}	
}

void menu()
{
	
	printf("           ====  1.编码：");
	printf("2.解码：");
	printf("3.解码表：");
	printf("4.退出程序   ===\n");

}

void HuffmanCodefree()//*释放内存空间
{
	
	for(s=1;s<=n;s++)
		free(HC[s]);
	free(HC);
	free(HT);
}

void main()
{
	int l;
	printf("                欢迎使用赫夫曼编码系统 v1.0 by Jay\n");
	while(1)
	{
		menu();
		scanf("%d",&l);
		switch(l)
		{
			case 1:HuffmanCoderule();HuffmanCoding(&HT,&HC,w,n,x);break;
			case 2:HuffmanCodeprint(&HT,&HC,n);break;
			case 3:HuffmanCodebiao(&HT);break;
			case 4:HuffmanCodefree();exit(0);
		}
	}

}



