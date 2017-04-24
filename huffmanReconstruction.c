#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#define DEBUG
// 1.
/*
typedef struct huffManTree
{
	int weight;
	char word;
	struct huffManTree *lchild,*rchild;

}tree;
*/
//2.
/*
功能:huffManTree节点信息  此在生成huffman编码后会销毁
*/
typedef struct HFTree
{
	int weight;        //huffManTree节点信息
	int lchild,rchild;//在huffman树中记录左右子树 (用户输入结构中的下标)
}HFTree;

/*
功能:用户输入节点信息
*/
typedef struct node
{
	int info_weight;            //权值
	char info_word;		    //字符
	char info_huffmanCode[256]; //huffman编码
}node;


/*
功能: 将char转换为int
参数:
	char ch[]   :字符数组地址
返回值: 转换后的int值

*/
int charStringTransformToInt(char ch[])//
{
	int weight;
	char *p;
	int len,n,nsum = 1;
	len = strlen(ch)-1;
	p = ch+len;
	weight = (*p) - 48;
	n = len;
//	printf("%d\n",weight);
	while(len -- )
	{
		p-=1;
		nsum = nsum*10;
		weight = weight + ((*p) - 48)*nsum;
		
	}
	return weight;
}
/*
功能: 读取配置文件
参数:
	node*pnode:字符和权值结构数组首地址
返回值: 无

*/


void readHuffmanConfig(node*pnode)
{
	FILE *stream ;
	char arr[100];
	char * post;
	char ch[10];
	char huffmanCode[256];
	int huffmanWeight;
	int i = 0,k = 0;
	stream = fopen("huffman.conf","r");
	while(!feof(stream))
	{
		memset(arr, 0, 100);
		memset(ch, 0, sizeof(ch));
		fgets(arr,100,stream);

		if(arr[0]=='#')
		continue;
		post = strchr(arr,':');
		if (post == NULL)
		{
			continue;
		}
		strncpy(ch,arr,post - arr);
		ch[post-arr] = '\0';
		
		strncpy(huffmanCode,post + 1,strlen(arr) - (post -arr) -2);  //4 - 1 -1
		huffmanCode[strlen(arr) - (post -arr) -2] = '\0';
		i++;
		//strcat(&ch[0][0],"\0");//从目标字符串的\0处开始链接，如果目标 字符串结尾没有\0 链接就会出错
		huffmanWeight = charStringTransformToInt(huffmanCode);
		printf("字符:%s  权值:%d\n",ch,huffmanWeight);
		pnode->info_weight = huffmanWeight;
		pnode->info_word = ch[0];
		pnode+=1;
	}
}




/*
功能:将用户输入的信息根据权值从小到大排序
参数:
	pnode * pnode         :保存权值和字符的结构地址
	int N                 :用户输入字符个数
返回值:返回权值最小的叶子节点	
*/
void sortMinToMax(node*pnode,int N)
{
	int i,j;
	int tmp_weight;
	char tmp_word;
	node * rootPnode,*parperPnode;
	rootPnode = pnode;
	for(i=0;i<N;i++)
	{
		pnode = parperPnode = rootPnode;
		
		for(j=1;j<N;j++)
		{
			parperPnode = pnode;
			pnode +=1;
			if(parperPnode->info_weight > pnode->info_weight)
			{
				printf("parperPnode=%d ",parperPnode->info_weight);
				printf("pnode=%d \n",pnode->info_weight);
				tmp_weight = parperPnode->info_weight;
				parperPnode->info_weight = pnode->info_weight;
				pnode->info_weight = tmp_weight;
			
				tmp_word = parperPnode->info_word;
				parperPnode->info_word = pnode->info_word;
				pnode->info_word = tmp_word;
			}
		}
	}
}

/*
功能:查找用户输入的权值最小的叶子
参数:
	pnode * pnode         :保存权值和字符的结构地址
	int N                 :用户输入字符个数
	HFTree*rootHuffmanTree:生成的huffman树根节点
返回值:返回权值最小的叶子节点	
*/
node * findMinNode(node * pnode ,int N,int k)
{
	int i;
	sortMinToMax(pnode,N);//first step :sort
	node * rootTree;
	node * minNode;
	//minNode->info_weight = pnode[k].info_weight;
	minNode = &pnode[k];
	for(i=k;i<N;i++)
	{
		if(minNode->info_weight > pnode[i].info_weight)
		minNode->info_weight = pnode[i].info_weight;
	}

return minNode;	
}

/*
功能: 根据huffman树生成huffman编码
参数:
	pnode * pnode         :保存权值和字符的结构地址
	int N                 :用户输入字符个数
	HFTree*rootHuffmanTree:生成的huffman树根节点
*/
void huffmanCodeing(node * pnode,int N,HFTree *rootHuffmanTree)
{
	char *code;
	char *codeT;
	char codeF[256];
	char codeL[256];
	char codeR[256];
	int k = 0,i;
	//生成huffman编码
	memset(codeF,0,sizeof(codeF));
	memset(codeL,0,sizeof(codeL));
	memset(codeR,0,sizeof(codeR));
	for(i=N-2,k=0;i>=0;i--,k++)//
	{
		if(rootHuffmanTree[i].rchild == -1 )
		{
			code = "0";//zuo L
			codeT= "1" ;
			
			strcpy(codeL,codeF);//codeL = codeF  + code;
			strcat(codeL,code);
			strcat(codeF,codeT);//codeF = codeF + codeT;	
#ifdef DEBUG
			printf("LLLL%s\n",codeL);
#endif	
			strcpy(pnode[i+1].info_huffmanCode,codeL);//根据huffman树生成编码保存到节点结构的info_huffmancode字段中
		}else
		if(rootHuffmanTree[i].lchild == -1)
		{
			
			code = "1";//you R
			codeT= "0";
			
			strcpy(codeR,codeF);//codeR = codeF  + code;
			strcat(codeR,code);
			strcat(codeF,codeT);//codeF = codeF + codeT;	
#ifdef DEBUG	
			printf("RRR%s\n",codeR);
#endif	
			strcpy(pnode[i+1].info_huffmanCode,codeR);//根据huffman树生成编码保存到节点结构的info_huffmancode字段中
		}else
		{
			code = "1";//you R
			codeT= "0" ;
			
			strcpy(codeL,codeF);//codeL = codeF + 0;
			strcat(codeL,codeT);
			
			strcpy(codeR,codeF);//codeL = codeF + 0;
			strcat(codeR,code);//codeR = codeF + 1;
			strcpy(pnode[i].info_huffmanCode,codeL);
			strcpy(pnode[i+1].info_huffmanCode,codeR);//根据huffman树生成编码保存到节点结构的info_huffmancode字段中
#ifdef DEBUG
			printf("LLLL%s\n",codeL);
			printf("RRRR%s\n",codeR);
#endif
		}
	}
	free(rootHuffmanTree);
}
/*
功能:生成huffman树
参数:
	pnode * pnode:保存权值和字符的结构地址
	int N        :用户输入字符个数
*/
HFTree * createHuffmanTree(node * pnode,int N)
{
	int i;
	int account=0;
	HFTree * rootHuffmanTree,*tmpLinkTree;
	node *firstPnode,*secondPnode;
	secondPnode = pnode;
	firstPnode = (node*)malloc(sizeof(node));
	firstPnode->info_word='T';
	tmpLinkTree = rootHuffmanTree = NULL;
	rootHuffmanTree = (HFTree*)malloc((N-1)*sizeof(HFTree));
	for(i=1;i<N;i++)
	{
		if(i == 1)
		{
			firstPnode->info_weight = secondPnode->info_weight;
		
		}
		else
		{
			firstPnode->info_weight = rootHuffmanTree->weight;
		}
		

		secondPnode = findMinNode(pnode,N,i);//second step:find min node
		tmpLinkTree = rootHuffmanTree;
		
		rootHuffmanTree->weight = firstPnode->info_weight + secondPnode->info_weight;
		//memset(rootHuffmanTree->huffmanCode,0,sizeof(rootHuffmanTree->huffmanCode);//
		//生成huffman树
		if(i == 1)
		{
			rootHuffmanTree->lchild = 0;
			rootHuffmanTree->rchild = (secondPnode - pnode);	
		}
		else if(firstPnode->info_weight < secondPnode->info_weight)//firstPnode两个权值最小的叶子生成的和节点  secondPnode是剩下叶子中 权值最小的
		{
			//rootHuffmanTree
			//printf("走右子树\n");
			rootHuffmanTree[i-1].rchild = (secondPnode-pnode);
			rootHuffmanTree[i-1].lchild = -1;
		}else
		{
			//printf(" 走左子树\n");
			rootHuffmanTree[i-1].lchild = (secondPnode - pnode);
			rootHuffmanTree[i-1].rchild = -1;
		}	
	}
	return rootHuffmanTree;
}
/*
功能:解码
参数:
	pnode * pnode:保存权值和字符的结构地址
	int N        :用户输入字符个数
*/
void huffmanDecoding(node*rootPnode,int N)
{
	int i = 0;
	char userDecoding[20];
	char ch;
	int num;
	int x;
	printf("Please input huffmanCode for decoding\n");
	getchar();
	while((ch = getchar()) != '\n')
	{
		userDecoding[i++] =ch; 
	}
	userDecoding[i] = '\0';
	num = strlen(userDecoding);
	
	if(N-num > 1)
	{
		printf("编码:%s  字符:%c\n",userDecoding,rootPnode[N - num].info_word);
	}else
	{
		if(!strcmp(userDecoding,rootPnode[0].info_huffmanCode))
		{
			printf("编码:%s  字符:%c\n",userDecoding,rootPnode[0].info_word);	
		}else
		if(!strcmp(userDecoding,rootPnode[1].info_huffmanCode))
		{
			printf("编码:%s  字符:%c\n",userDecoding,rootPnode[1].info_word);
		}
	}
}

int main(int argc,char *argv[])
{
	int N;
	int i,j;
	int weight;
	char word;
	node *pnode,*rootPnode;
	HFTree * rootHuffmanTree;
	printf("Please input the NODE num!\n");
	scanf("%d",&N);
	rootPnode = pnode = (node*)malloc(N*sizeof(node));
	/*for(i=0;i<N;i++)
	{
		scanf("%d %c",&pnode->info_weight,&pnode->info_word);
		memset(pnode->info_huffmanCode,0,sizeof(pnode->info_huffmanCode));
		pnode++;
		
	}*/
	readHuffmanConfig(rootPnode);
	rootHuffmanTree = createHuffmanTree(rootPnode,N);
	huffmanCodeing(rootPnode,N,rootHuffmanTree);
	for(i=0;i<N;i++)
//#ifdef DEBUG
	printf("权值:%d  字符:%c  编码:%s\n",rootPnode[i].info_weight,rootPnode[i].info_word,rootPnode[i].info_huffmanCode);
	//解码//输入huffman以解码
	huffmanDecoding(rootPnode,N);
//#endif
//MYDEBUG;
}
/*
example:
4
1 a
2 b
5 c
7 d
权值:1  字符:a  编码:100
权值:2  字符:b  编码:101
权值:5  字符:c  编码:11
权值:7  字符:d  编码:0
root@ubuntu:/usr/work/workspace/CPP/Huffman/Test#

*/
