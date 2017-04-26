/*
流编码格式:[huffman编码][结束符]
例如: 字符:Z  编码110@      //@是结束符
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define ASCII 256  //
#define USER_ENTER_SIZE_CONTROL  1024 //1K
//#define huffmanCodeing_Debug //由树生成编码调试
//#define buildTree_Debug      //构建huffman树调试
//#define node_Debug           //节点信息调试
//#define readConfig_Debug     //读取配置文件调试
//#define dataFlowCoding_Debug //用户输入的字符串生成数据流编码调试
//#define dataFlowDecoding_Debug
#define nodePrint_Debug



typedef struct userEnterStringInfo
{
	int N;
	int freq[ASCII];
	char userEnter[USER_ENTER_SIZE_CONTROL];
}userEnterStringInfo;


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
功能：搜索编码对应的字符
参数:根节点
返回值：无
*/
void quickSerachCharHuffmanCode(node *pnode)
{
	char userchar;
	printf("Please input you want search char!");
	scanf("%c",&userchar);
	while(1)
	{
		if(userchar == pnode->info_word)
		break;
		pnode+=1;
	}
	printf("字符:%c  编码:%s\n",pnode->info_word,pnode->info_huffmanCode);
}




/*
功能: 读取配置文件
参数:
	无
返回值: 返回根节点
*/


void  readHuffmanConfig(node*pnode)
{
	FILE *stream ;
	char arr[100];
	char * post;
	char ch[10];
	char huffmanCode[256];
	int huffmanWeight;
	int charAccount = 0,k = 0;
	
	stream = fopen("huffman.conf","r");
	if(stream ==NULL)
	{
		printf("打开配置文件失败   请检查配置文件! 错误代码:%d\n",errno);//错误代码
		exit(1);
	}
	while(!feof(stream))
	{
		memset(arr, 0, 100);
		memset(ch, 0, sizeof(ch));
		fgets(arr,100,stream);

		if(arr[0]=='#')
		continue;
		post = strchr(arr,':');//计算行post所在地址
		if (post == NULL)
		{
			continue;
		}
		strncpy(ch,arr,post - arr);
		ch[post-arr] = '\0';
		
		strncpy(huffmanCode,post + 1,strlen(arr) - (post -arr) -2);  //4 - 1 -1
		huffmanCode[strlen(arr) - (post -arr) -2] = '\0';
		
		//strcat(&ch[0][0],"\0");//从目标字符串的\0处开始链接，如果目标 字符串结尾没有\0 链接就会出错
		huffmanWeight = charStringTransformToInt(huffmanCode);
#ifdef readConfig_Debug
		printf("字符:%s  权值:%d\n",ch,huffmanWeight);
		getchar();
#endif
		pnode->info_weight = huffmanWeight;
		pnode->info_word = ch[0];
		pnode+=1;
		charAccount+=1;
		printf(">>>>>>>>>>>>>>>>>>>>>>>>>>%d\n",charAccount);
	}
	if(charAccount!=52)
	{
		printf("************** 错误!**************");
		printf(" 请检查配置文件字符完整性!\n note：目前仅仅支持英文大小写 共计52个字符 \n 下个版本将支持更多 敬 请期待");
		exit(1);
	}

}



void nodeCheckPrint(node*rootPnode,int N)
{
	int i;
	printf("************* nodePrint_Debug Start *************\n");
	for(i=0;i<N;i++)
	{
		printf("nodePrint_Debug--权值:%d  字符:%c \n",rootPnode[i].info_weight,rootPnode[i].info_word);
	}
	printf("************* nodePrint_Debug stop*************\n");
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
#ifdef node_Debug
				printf("parperPnode=%d ",parperPnode->info_weight);
				printf("pnode=%d \n",pnode->info_weight);
#endif	
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
********************注意:此函数会将节点信息按照从小到大的顺序排序保存到结构中********************
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
#ifdef huffmanCodeing_Debug
			printf("LLLL%s\n",codeL);
			getchar();
#endif	
			strcpy(pnode[i+1].info_huffmanCode,codeL);//根据huffman树生成编码保存到节点结构的info_huffmancode字段中
			strcat(pnode[i+1].info_huffmanCode,"@");
		}else
		if(rootHuffmanTree[i].lchild == -1)
		{
			
			code = "1";//you R
			codeT= "0";
			
			strcpy(codeR,codeF);//codeR = codeF  + code;
			strcat(codeR,code);
			strcat(codeF,codeT);//codeF = codeF + codeT;	
#ifdef huffmanCodeing_Debug	
			printf("RRR%s\n",codeR);
			getchar();
#endif	
			strcpy(pnode[i+1].info_huffmanCode,codeR);//根据huffman树生成编码保存到节点结构的info_huffmancode字段中
			strcat(pnode[i+1].info_huffmanCode,"@");
		}else
		{
			code = "1";//you R
			codeT= "0" ;
			
			strcpy(codeL,codeF);//codeL = codeF + 0;
			strcat(codeL,codeT);
			
			strcpy(codeR,codeF);//codeL = codeF + 0;
			strcat(codeR,code);//codeR = codeF + 1;
			
			strcpy(pnode[i].info_huffmanCode,codeL);
			strcat(pnode[i].info_huffmanCode,"@");
			
			strcpy(pnode[i+1].info_huffmanCode,codeR);//根据huffman树生成编码保存到节点结构的info_huffmancode字段中
			strcat(pnode[i+1].info_huffmanCode,"@");

#ifdef huffmanCodeing_Debug
			printf("LLLL%s\n",codeL);
			printf("RRRR%s\n",codeR);
			getchar();
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
/*BUG 1*/		
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
#ifdef buildTree_Debug
			printf("走右子树\n");
			getchar();
#endif
			rootHuffmanTree[i-1].rchild = (secondPnode-pnode);
			rootHuffmanTree[i-1].lchild = -1;
		}else
		{
#ifdef buildTree_Debug
			printf(" 走左子树\n");
			getchar();
#endif
			rootHuffmanTree[i-1].lchild = (secondPnode - pnode);
			rootHuffmanTree[i-1].rchild = -1;
		}	
		
	}
	return rootHuffmanTree;
}
/*
功能:单个字符解码
参数:
	pnode * pnode:保存权值和字符的结构地址
	int N        :用户输入字符个数
*/
void huffmanSingleCharacterDecoding(node*rootPnode,int N)
{
	int i = 0;
	char userDecoding[20];
	char ch;
	int num;
	int x;
	printf("Please input huffmanCode for decoding\n");
#ifdef HOME_MACHINE
	getchar();
#endif	
	getchar();
	while((ch = getchar()) != '\n')
	{
		userDecoding[i++] =ch; 
	}
	userDecoding[i] = '\0';
	printf("userDecoding=%s\n",userDecoding);
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
/*
功能:流解码
参数:
	pnode * pnode:保存权值和字符的结构地址
	int N        :用户输入字符个数
*/

void dataFlowDecoding(node *pnode,char userStringHuffmanCodeDecoding[])
{
	
	char * user = userStringHuffmanCodeDecoding;
	int i = 0;
	int k = 0;
	int len;
	int N;
	char ch;
	node * rootPnode;
	char oneStringHuffmanCode[256];
	rootPnode = pnode;
	memset(user,0,sizeof(user));

	printf("输入数据流用于解码\n");
	N = strlen(pnode->info_huffmanCode) + 1;
	fflush(stdin);
	while((ch = getchar())!='\n')//A:65 a:97 z:122
	{
		//if(ch == '\0')
		//strcat(user,'\0')
		pnode = rootPnode;
		if(ch != '@')
		{
			oneStringHuffmanCode[k] = ch;
			k+=1;		
			
		}else
		{
			oneStringHuffmanCode[k] = '@';
			oneStringHuffmanCode[k+1] = '\0';
			while(1)
			{
				if(!strcmp(oneStringHuffmanCode,pnode->info_huffmanCode))//if oneStringHuffmanCode == pnode->info_huffmanCode
				{
/*BUG2 在使用strcat链接字符串的时候出现问题*/
					//strcat(user,&(pnode->info_word));
					*user = pnode->info_word;
					user+=1;
					break;
				}	
				pnode+=1;
				//printf("++++++++++++++++++++++++++++%s\n",user);
			}	
			k = 0;
			memset(oneStringHuffmanCode,0,sizeof(oneStringHuffmanCode));
		}
#ifdef dataFlowDecoding_Debug
		printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>%s\n",user);		
#endif
	}
}

/*
功能:生成编码流
参数:
	pnode * pnode:保存权值和字符的结构地址
	int userStringHuffmanCodeing[]        :保存的编码
*/
void dataFlowCoding(node*pnode,char userStringHuffmanCodeing[])
{
	////由于节点是按照权值大小排序保存的 不能按照字符的ascii码大小来查找字符所在的数组的位置,因为不能确定字符在数组中的位置 所以只能搜遍整个数组查找此字符
	char ch;
	node * rootPnode = pnode;
	char *user =userStringHuffmanCodeing;
	memset(userStringHuffmanCodeing,0,sizeof(userStringHuffmanCodeing));
	printf("输入要编码的字符串生成编码\n");
	//getchar();
	while((ch = getchar())!='\n')//A:65 a:97 z:122
	{
		//if(ch == '\0')
		//strcat(user,'\0')
		pnode = rootPnode;
		while(1)//The char location on the node structs
		{
#ifdef dataFlowCoding_Debug
			printf("now\n");
#endif			
			if(ch == pnode->info_word)
			{
				strcat(user,pnode->info_huffmanCode);
				break;
			}
			else
			pnode+=1;	
		}
		//user+=1;
#ifdef dataFlowCoding_Debug
		printf("=====%s\n",user);
#endif
	}
	
}
/*
接受用户输入
*/
void acceptUserInput(userEnterStringInfo * userInfo)
{
	char ch;
	int i = 0;
	getchar();
	while((ch = getchar()) != '\n')
	{
		userInfo->userEnter[i] = ch;
		i+=1;
	}
	userInfo->userEnter[i] = '\0';
	//printf(">>>>>>>>>>>>>>>>>>>>>>>>%s\n",userInfo->userEnter);
}

/*
功能:根据用户输入的字符串   动态计算各字符的权值
参数:
返回值:
*/

void  characterFrequency(userEnterStringInfo * userInfo)
{
	//aaAvsdwfg
	int i;
	//统计字符个数,为开辟空间做准备
	//A:65 -- z:122
	char *user = userInfo->userEnter;
	while(*user!='\0')
		userInfo->freq[*user++]++;		
	for(i=0;i<122;i++)
	{
		if(userInfo->freq[i] != 0)
		{
			(userInfo->N)+=1;
			printf("'%c':%d   ",i,userInfo->freq[i]);	
		}
	}	
	
}

/*userEnterStringInfo * readUserString( userEnterStringInfo * userEnterInfo)*/
/*{*/
	//node* rootPnode;
/*test*/	
	//userEnterInfo.userEnter;
	//characterFrequency(userEnterInfo);
	//printf("=============%d\n",userEnterInfo.N);
/*	*/
/*return &userEnterInfo;*/
/*}*/




int main(int argc,char *argv[])
{
	int N;
	int i,j;
	int weight;
	char word;
	int MODE;
	char tmp[100];
	char tmp2[100];
	userEnterStringInfo * userEnter,userEnterInfo = {0,{0},"How are you !"};//默认值
	node *pnode,*rootPnode;
	HFTree * rootHuffmanTree;
	printf("Please select the MODE !\n");
	printf("1.自定义   2.根据配置文件生成   3.动态生成编码\n");
	scanf("%d",&MODE);
	
	//scanf("%d",&N);
	//rootPnode = pnode = (node*)malloc(N*sizeof(node));
	/*for(i=0;i<N;i++)
	{
		scanf("%d %c",&pnode->info_weight,&pnode->info_word);
		memset(pnode->info_huffmanCode,0,sizeof(pnode->info_huffmanCode));
		pnode++;
		
	}*/
	//*****************************************************
	
	switch(MODE)
	{
		case 1://1.********************用户输入字符和权值*********************
		{
			printf("Please input the NODE number!\n");
			scanf("%d",&N);
			rootPnode = pnode = (node*)malloc(N*sizeof(node));
			for(i=0;i<N;i++)
			{
				scanf("%d %c",&pnode->info_weight,&pnode->info_word);
				memset(pnode->info_huffmanCode,0,sizeof(pnode->info_huffmanCode));
				pnode++;
		
			}
			printf("*****now*****\n");
		}break;
		case 2://2.*******************从配置文件读取字符和权值******************
		{
			rootPnode = pnode = (node*)malloc(52*sizeof(node));
			readHuffmanConfig(rootPnode);
			N = 52;
		}break;
		case 3://3.************根据用户输入的字符串动态生成权值和编码************
		{
			N = 0;
			//userEnter = readUserString(&userEnterInfo);
			acceptUserInput(&userEnterInfo);
			characterFrequency(&userEnterInfo);
			rootPnode = pnode = (node *)malloc((userEnterInfo.N)*sizeof(node));
			//N = userEnter->N;
			for(i=0;i<122;i++)
			{
				//while()
				if(userEnterInfo.freq[i] != 0)
				{
					//N+=1;
					printf("'%c':%d   ",i,userEnterInfo.freq[i]);
					pnode->info_word = i;
					//printf(">>>>>>>>>>>>>>>>>>>>>pnode->info_word=%c\n",pnode->info_word);
					pnode->info_weight = userEnterInfo.freq[i];	
					pnode+=1;
				}
			}
			N = userEnterInfo.N;
			
		}break;
	}
	getchar();
#ifdef nodePrint_Debug
	nodeCheckPrint(rootPnode,N);
#endif
	rootHuffmanTree = createHuffmanTree(rootPnode,N);
	huffmanCodeing(rootPnode,N,rootHuffmanTree);
	for(i=0;i<N;i++)
//#ifdef DEBUG
	printf("权值:%d  字符:%c  编码:%s\n",rootPnode[i].info_weight,rootPnode[i].info_word,rootPnode[i].info_huffmanCode);
//解码//输入huffman以解码
	//huffmanSingleCharacterDecoding(rootPnode,N);//单个字符解码  不需要@结束确认位置码(流解码的时候需要)
	//quickSerachCharHuffmanCode(rootPnode);//搜索字符的huffman编码    备用接口   不需要@结束确认位置码
	//将用户输入字符串编码
//编码
	dataFlowCoding(rootPnode,tmp);//流编码
	printf("用户输入字符串编码:%s\n",tmp);
//解码
	dataFlowDecoding(rootPnode,tmp2);//流解码
	printf("解码:%s\n",tmp2);
	
	//readUserString();	
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
