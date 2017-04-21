/*ASCII*/
/*#include <stdio.h>
#include <malloc.h>
int main()
{
	int num;
	int i = 0;
	int tmp = 0;
	char *p;
	scanf("%d",&num);
	p = (char *)malloc(3*num*sizeof(char));
	for(i=0;i<num;i++)
	{	getchar();
		scanf("%c%c%c",p+3*i,p+1+3*i,p+2+3*i);
		//printf("%c %c %c",*(p+i*3),*(p+1+i*3),*(p+2+i*3));
	}
	
	for(i=0;i<num;i++)
	{
		if(*(p+i*3)>*(p+1+i*3))
		{
			tmp = *(p+i*3);
			*(p+i*3) = *(p+1+i*3);
			*(p+1+i*3) = tmp;
		}
		if(*(p+i*3)>*(p+2+i*3))
		{
			tmp = *(p+i*3);
			*(p+i*3) = *(p+2+i*3);
			*(p+2+i*3) = tmp;
		}
		if(*(p+1+i*3)>*(p+2+i*3))
		{
			tmp = *(p+1+i*3);
			*(p+1+i*3) = *(p+2+i*3);
			*(p+2+i*3) = tmp;
		}
	}
	
	for(i = 0;i<num;i++)
	printf("%c %c %c\n",*(p+i*3),*(p+1+i*3),*(p+2+i*3));
}
*//*
#include "stdio.h"
main()
{
char a,b,c,d;
int i;
scanf("%d",&i);
getchar();
while(i--)
{
scanf("%c%c%c",&a,&b,&c);
getchar();
if (a>b) {d=a;a=b;b=d;}
if (a>c) {d=a;a=c;c=d;}
if (b>c) {d=b;b=c;c=d;}
printf("%c %c %c\n",a,b,c);
}

}*/
/*Prime summation*/
/*
#include <stdio.h>
#include <malloc.h>
int main()
{
	int Znum=0,Cnum=0,Snum,sum = 0;
	int i=0,j=0,k=0;
	scanf("%d",&Znum);
	for(i=0;i<Znum;i++)
	{
		sum = 0;
		scanf("%d",&Cnum);
		for(j=0;j<Cnum;j++)
		{	
			scanf("%d",&Snum);
			//printf("a%d ",Snum);
			getchar();
			for(k=2;k<=Snum;k++)
			if(Snum%k ==0)
			{
				if(k<Snum)
				break;
				else
				{
				sum = sum + k;
				
				}
				
			}
			
			
		}
		printf("%d\n",sum);
	}	
}
*/


/*
#include<stdio.h>  
#include<string.h>  
#define MAXSIZE 1001  
int prime[MAXSIZE];  
//素数表  
void Prime()
{  int i,j;
    memset(prime,0,sizeof(prime));  
    for(i = 2;i < MAXSIZE;i++){  
        //非素数跳过  
        if(prime[i]){  
            continue;  
        }  
        else{  
            for(j = i*i;j < MAXSIZE;j += i){  
                prime[j] = 1;  
            }  
        }  
    }  
}  
  
int main()  
{  
    int N,i,M,sum,x;  
    //freopen("C:\\Users\\SJF\\Desktop\\acm.txt","r",stdin);  
    scanf("%d",&N);  
    //素数表  
    Prime();  
    prime[1] = 1;  
    prime[0] = 1;  
    //N组测试数据  
    while(N--)
    {  
        sum = 0;  
        //M个数据  
        scanf("%d",&M);  
        for(i = 0;i < M;i++){  
            scanf("%d",&x);  
            //素数相加  
            if(prime[x] == 0){  
                sum += x;  
            }  
        }  
        printf("%d\n",sum);  
    }  
    return 0;  
}  

*/
/*****Take stones******/
/*
#include <stdio.h>
int main()
{
	int Znum=0,i=0,k=0,j=0;
	int rule[2]=0;
	int sum=0;
	scanf("%d",&Znum);
	for(i=0;i<Znum;i++)
	{
		scanf("%d%d",&rule[0],&rule[1]);
		while(rule[0] - sum)
		{
			for(j=1;j<rule[2];j++)
			{
					
				for(k=1;k<rule[2];k++)
				{
					sum = j+k;
					if(sum >= rule[0])
					{
						printf("Win\n");
						break;		
					}			
				}
		
			}
		}
		
		
	}
}
*/
/*
#include <stdio.h>

int isPrime(int num)  
{  
	int i;
    if(num==1)return 0;  
    for(i=2;i*i<=num;i++)  
        if(num%i==0)  
            return 0; //N  
    return 1;   //Y
}

int main()
{
	int Znum,Snum;
	int p1=0,p2=0;
	int i = 0,j = 0;
	int x=0;
	scanf("%d",&Znum);
	for(;i<Znum;i++)
	{
		
		scanf("%d",&Snum);
		if(isPrime(Snum))
		{
			printf("%d %d\n",Snum,0);
		}else
		{
			for(j=Snum;j>1;j--)
			{
				
				if(isPrime(j))
				{
					p1=j;		
					break;
				}
			}
			for(j=Snum;;j++)
			{
				if(isPrime(j))
				{
					p2=j;		
					break;
				}
			}
			if(p2 ==2)
			printf("%d %d\n",p2,p2-Snum);
			else
			if(p2-Snum >= Snum-p1)
			printf("%d %d\n",p1,Snum-p1);
			else
			printf("%d %d\n",p2,p2-Snum);	
		}
	}	
}

*/

/*
#include <stdio.h>
int main()
{
	int Znum,Snum;
	int j,i,k;
	scanf("%d",&Znum);
	for(i=0;i<Znum;i++)
	{
		scanf("%d",&Snum);//1000000
		for(j=Snum;j>2;j--)
		{
			for(k=2;k<=Snum;k++)
			if(j%k == 0)
			{
				if(k < j)
				break;
			}
		}
		
		
	}
}
*/









/*


#include<stdio.h>  
#include<stdlib.h>  
  
int isPrime(int num)  
{  
	int i;
    if(num==1)return 0;  
    for(i=2;i*i<=num;i++)  
        if(num%i==0)  
            return 0;  
    return 1;  
}  
  
int main()  
{  
    int n,num,numUp,numDown,deltUp,deltDown;  
    scanf("%d",&n);  
    while(n--)  
    {  
        scanf("%d",&num);  
        if(isPrime(num))//本身是素数，后面就不用了   
          printf("%d 0\n",num);  
        else  
        {  
            numUp=numDown=num;  
            while(!isPrime(numUp))  
            {  
                numUp+=1;  
            }  
            while(!isPrime(numDown)&&numDown>0)//边界条件，否则不能通过   
            {  
                numDown-=1;  
            }  
            deltUp = numUp-num;  
            deltDown = num-numDown;  
              
            if(numDown==0)//特殊情况：左边没有找到   
              printf("%d %d\n",numUp,deltUp);  
            else if(deltUp>=deltDown)//输出距离小的, 相等则左   
                printf("%d %d\n",numDown,deltDown);  
            else  
                printf("%d %d\n",numUp,deltUp);  
        }  
  
    }  
    //system("PAUSE");  
    return 0;  
}  
*/
/*
#include<iostream>
#include<cmath>
using namespace std;
bool isprime(int n)
{
for(int k=2;k<=sqrt((double)n);k++)
if((n%k)==0)
return false;
return true;
}
int main()
{
int n;
cin>>n;
while(n--)
{
int num,i,j;       
cin>>num;
if(num==1)
{
cout<<"2 1"<<endl;
continue;
}
for(i=num;!isprime(i);i--);
for(j=num;!isprime(j);j++);
if((num-i)<(j-num))
cout<<i<<' '<<(num-i)<<endl;
else if((num-i)>(j-num))
cout<<j<<' '<<(j-num)<<endl;
else if((num-i)==(j-num))
cout<<i<<' '<<(num-i)<<endl;
}
}
*/


/*
#include <stdio.h>
int main()
{
	int Znum;
	int i,j;
	int arr[9];
	int narr[3][3]={0};
	scanf("%d",&Znum);
	while(Znum--)
	{
		for(i=0;i<9;i++)
		{
			scanf("%d",&arr[i]);
		}	
		for(i=0;i<3;i++)
		{
			narr[i][0]=arr[i];
			narr[i][1]=arr[i+3];
			narr[i][2]=arr[i+6];	
			printf("%d ",narr[i][0]);
			printf("%d ",narr[i][1]);
			printf("%d ",narr[i][2]);
			
			printf("\n");
		}
	
		for(i=0;i<3;i++)
		{
			for(j=0;j<3;j++)
			printf("%d ",narr[i][j]);
			printf("\n");
		}
		
	}
}
*/
/*
#include <stdio.h>
#define symbols 10001
int main()
{
	int N,M;
	int L,R;
	int Znum;;
	int i;
	int sum = 0;
	int Last[symbols]={0};
	int flag = 0;
	scanf("%d",&Znum);
	while(Znum--)
	{
		sum=0;
		
		scanf("%d %d",&N,&M);
		while(M--)
		{
			flag =0;
			scanf("%d",&L);
			getchar();
			scanf("%d",&R);
			getchar();
			//printf("%d %d",L,R);
			for(i=L;i<=R;i++)
			{
				Last[i] = 1;
				flag++;
			}	
		printf("FFFFFFF%d\n",flag);
		
		}
			for(i=0;i<=10000;i++)
			{
				if(Last[i])
				{
					sum++;
					printf("%d-%d ",i,Last[i]);
				}
			}
			printf("SSSSSSSS%d\n",sum);
			printf("LLLL%d\n",N-sum);
	}
}
*/
/*
#include <iostream>  
using namespace std;  
int main()  
{  
    int n;  
    cin>>n;  
    while(n--){  
        int L,m,w,q,num=0;  
        cin>>L;  
        int a[L+1];  
        cin>>m;  
        for(int i=0;i<L+1;i++){  
            a[i]=0;  
        }  
        for(int i=0;i<m;i++){  
            cin>>w>>q;  
            for(int i=w;i<=q;i++){  
                a[i]=1;  
            }  
        }  
  
        for(int i=0;i<L+1;i++){  
            if(a[i]==0){  
                num++;  
            }  
        }  
        cout<<num<<endl;  
    }  
    return 0;  
}  


*/
/*
#include <stdio.h>
int main()
{
	int N;
	int i,j,k;
	int arr[2];
	int account = 0;
	scanf("%d",&N);
	while(N--)
	{	
		account = 0;
		scanf("%d",&arr[0]);
		getchar();
		scanf("%d",&arr[1]);
		getchar();
		for(i=arr[0];i>0;i--)
		{
			k = i;
			while(1)
			{
				if(!(k%arr[1])) //if==0
				{
					k = k/arr[1];
					account+=1;;
				}else
				break;
			}
		}
		printf("%d\n",account);
	}
}


*/

/*
#include <stdio.h>

int * sortFindMaxandMin(int num, int M[])
{
	int i,j;
	int arr[4];//1234
	int tmp=1;
	int max = 0;
	int min =0;
	M[1]=M[0] = 0;
	for(i=3;i>=0;i--)
	{
		arr[i] = (num) % 10; //4
		num = (num)/10;
	}
	for(i=0;i<4;i++)
	{	
		for(j=i+1;j<4;j++)
		if(arr[i]<arr[j])
		{
			tmp=arr[i];
			arr[i] = arr[j];
			arr[j] = tmp;
		}	
	}
	for(i=0;i<4;i++)
	tmp =1;
	for(i=2;i>=0;i--)//4 ci //Max
	{
		tmp = 10*tmp;
		M[0] = arr[i]*tmp + M[0];
	}
	M[0] = M[0]+arr[3];
	tmp = 10000;
	for(i=3;i>=0;i--)       //Min
	{
		tmp = tmp/10;
		M[1] = arr[i]*tmp + M[1];
	}	
	
	return M;
		
}


int main()
{
	int N;
	int i,j;
	int arr;	
	int max;
	int tmp;
	int k;
	int M[2] = {0};
	int account = 0;
	scanf("%d",&N);
	while(N--)
	{
		account =0;
		scanf("%d",&arr);
		getchar();
		sortFindMaxandMin(arr,M);
		tmp= M[0];
		while(1)
		{			
			if(M[0]-M[1] == k)
			{
				break;
			}	
			else
			{
				
				k = tmp;
				tmp = M[0]-M[1];
				sortFindMaxandMin(tmp,M);
				account+=1;
			}
		}	
		
		printf("%d\n",account);
	}
}

*/

/*################### Interprocess communication ####################*/
//1.pipe
/*
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
int main(int argc,char*argv[])
{
	char *childstring = "This is send form child !";
	int fd[2];
	char buf[100]={0};
	pipe(fd);
	pid_t pid;
	pid = fork();
	if(pid<0)
	{
		printf("Fork is ERROR ! exit");
		exit(1);
	}
	if(pid == 0)
	{
		printf("This is child process!\n");
		close(fd[0]);//close the read pipe
		write(fd[1],argv[1],strlen(argv[1]));
		close(fd[1]);	
		
	}else
	{
		memset(buf,0,100);
		printf("This is father process!\n");
		close(fd[1]);
		read(fd[0],buf,100);
		close(fd[0]);
		printf("Buf size=%d\n",sizeof(buf));
		printf("%s\n",buf);
	}
	waitpid( pid, NULL, 0 );
}

*/
//Famous pipe
/*
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>    
#include <sys/stat.h>    
#include <fcntl.h>


#define FIFO /usr/work/workspace/FUCKYOU/fifo
int main()
{
	int account =55;
	char * string = "This is test mkfifo!";
	pid_t pid2,pid1;
	int fd;
	int fd2;
	char buf[100];
	pid1 = fork();
	if(pid1 == 0)//child
	{
		memset(buf,0,sizeof(buf));
		printf("This is Pid1 child process! pid1==%d\n",getpid());
		printf("The pid1 father process ID:%d\n",getppid());
		fd = open("FIFO",O_RDONLY );
		read(fd,buf,sizeof(buf));
		close(fd);
		
		printf("%s\n",buf);
		printf("account==%d\n",account);
	}
	
	pid2 = fork();
	if(pid2 ==0)
	{
		printf("This is Pid2 child process! pid2==%d\n",getpid());
		printf("The pid2 father process ID:%d\n",getppid());
		fd2 = open("FIFO",O_WRONLY);
		write(fd2,string,strlen(string));
		close(fd2);
		account+=1;
		printf("account==%d\n",account);	
	}

	waitpid(NULL);	
	
}
*/
//
/*
#include <signal.h>
#include <stdio.h>
int account =55;
void sigHandel(int sig)
{
	if(sig ==SIGUSR1)
	account+=1;
	if(sig == SIGUSR2)
	account = 100;
}
int main()
{
	int signum;
	pid_t pid;
	signal(SIGUSR1,sigHandel);
	signal(SIGUSR2,sigHandel);
	pid = fork();
	if(pid == 0)
	{
		printf("child process ID:%d father process ID:%d\n",getpid(),getppid());
		kill(getppid(),SIGUSR2);
		printf("TTTT%d\n",account);
	}
	else
	{
		sleep(1);
		printf("father process ID:%d  account:%d\n",getpid(),account);	
	}
	waitpid(NULL);
	return 0;
	
}



*/
/*
#include <stdio.h>
struct tree
{
	int a;
};

void fun()
{
	printf("This is fun!\n");
}


int a;
const int c = 10;
int main()
{
static int b;

	//char *p;
	//char arr[]="dweqrgfsrwh";
	//p = F();
	//p = arr;
	//p[0]=L';
	//printf("%s\n",p);
	
	void (*F)();
	
	char *p;
	char arr[]="asdfghjkl";
	p = arr;
	struct tree T;	
	printf("a == %d\n",++a);
	printf("b == %d\n",++b);	
	printf("c == %d\n",c);
	printf("%x\n",T);
	printf("p==%x",p);
	printf("&arr==%x\n",&arr);
	printf("&arr[0]==%x\n",&arr[0]);
	printf("++++++++++++++++++++++++\n");
	
	F =&fun;
	F();
	
	printf("fun == %x\n",fun);
	printf("fun == %x\n",&fun);
	
}

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MYDEBUG {#ifdef DEBUG printf("HHHHHHHH\n"); #endif}

typedef struct huffManTree
{
	int weight;
	char word;
	struct huffManTree *lchild,*rchild;

}tree;

typedef struct node
{
	int info_weight;
	char info_word;
}node;


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
	
	for(i=0;i<N;i++)
	printf("%d \n",*(rootPnode+i));	
}

/*
void createHuffmanTree(node * pnode,int N)
{
	int i;
	int k = 2;
	node *rootPnode,*lastPnode;
	tree * newHuffmanTree,*oldHuffmanTree,*rootHuffmanTree;
	rootPnode = lastPnode =pnode = NULL;
	newHuffmanTree = oldHuffmanTree =NULL;
	for(i=N;i>0;i--)
	{
		//build two tree node from pnode
		for(k=0;k<2;k++)
		{
			oldHuffmanTree = newHuffmanTree;
			newHuffmanTree = (tree *)malloc(sizeof(tree));
			newHuffmanTree->weight = lastPnode[i-k].info_weight;
			newHuffmanTree->word = lastPnode[i-k].info_word;
			newHuffmanTree->lchild = NULL;
			newHuffmanTree->rchild = NULL;
		}
		if(newHuffmanTree->weight > oldHuffmanTree->weight)
		{
			rootHuffmanTree = (tree*)malloc(sizeof(tree));
			rootHuffmanTree->weight = newHuffmanTree->weight + oldHuffmanTree->weight;
			rootHuffmanTree->word='T';
			rootHuffmanTree->lchild = oldHuffmanTree;
			rootHuffmanTree->rchild = newHuffmanTree; 
		}
							
	}
}
*/


int main()
{
	int N;
	int i,j;
	int weight;
	char word;
	node *pnode,*rootPnode;
	printf("Please input the NODE num!\n");
	scanf("%d",&N);
	rootPnode = pnode = (node*)malloc(N*sizeof(node));
	for(i=0;i<N;i++)
	{
		scanf("%d %c",&pnode->info_weight,&pnode->info_word);
		pnode++;
		
	}
	//for(i=0;i<;)
	//scanf();

	sortMinToMax(rootPnode,N);
	for(i=0;i<N;i++)
//#ifdef DEBUG
	printf("%d  %c\n",rootPnode[i].info_weight,rootPnode[i].info_word);	
//#endif
//MYDEBUG;
}



















