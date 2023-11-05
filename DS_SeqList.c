/*
1. 必做题目 
设计和编写程序：定义、创建和显示顺序表L（表中的数据类型为整型，正整数），编写函数（DeleteList）实现将L中的偶数删除

2. 选做题目
（1）已知非递减顺序表L（录入数据时可以手动保证L是非递减的），插入一个元素e后，L仍然是非递减的。
（2） 已知顺序表L，从第i个元素起（包括第i个 ）连续删除k个元素。
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10
typedef int Status;

typedef struct
{
    int *elem;
    int length;
    int listsize;
}SqList;

Status InitList_Sq(SqList *L)//Initializing
{
    L->elem=(int*)malloc(LIST_INIT_SIZE*sizeof(int));
    if(!L->elem)
    {
        exit(OVERFLOW);
    }
    L->length=0;
    L->listsize=LIST_INIT_SIZE;
    return OK;
}

void CreateList(SqList *L,int n)
{
    if(n<0)
    {
        return;
    }
    printf("Please input %d integers.\n",n);
    for(int tmp=0;tmp<n;tmp++)
    {
        scanf("%d",&L->elem[tmp]);
    }
    L->length=n;
    return;
}

void NoinputCreateList(SqList *L,int n,int arr[])
{
    if(n<0)
    {
        return;
    }
    for(int tmp=0;tmp<n;tmp++)
    {
        L->elem[tmp]=arr[tmp];
    }
    L->length=n;
    return;
}

void PrintList(SqList *L)
{
    printf("Data in SqList are:\n");
    for(int tmp=0;tmp<L->length;tmp++)
    {
        printf("%d ",L->elem[tmp]);
    }
    printf("\n");
    return;
}

void Search_Elememt(SqList *L,int Element)
{
    for(int tmp=0;tmp<L->length;tmp++)
    {
        if(Element==L->elem[tmp])
        {
            printf("The *Element:%d* is at No.%d.\n",Element,tmp+1);
            return;
        }
    }
    printf("The *Element:%d* does not exist!",Element);
    exit(ERROR);
    return;
}

void Insert_Element(SqList *L,int Element,int Location)
{
    if(Location<=0||Location>L->length)
    {
        printf("Illegal Location!");
        exit(ERROR);
    }
    L->elem=(int*)realloc(L->elem,(++(L->listsize))*sizeof(int));
    if (!L->elem) 
    {
        exit(OVERFLOW);
    }
    for(int tmp=L->length;tmp>=Location-1;tmp--)
    {
        L->elem[tmp+1]=L->elem[tmp];
    }
    L->elem[Location-1]=Element;
    L->length++;
    return;
}

int Delete_Element(SqList *L,int Location)
{
    int Del_num=L->elem[Location-1];
    if(Location<=0||Location>L->length)
    {
        //printf("Illegal Location!");
        exit(ERROR);
    }
    for(int tmp=Location-1;tmp<L->length-1;tmp++)
    {
        L->elem[tmp]=L->elem[tmp+1];
    }
    L->length--;
    //printf("Done!\n");
    return Del_num;
}

SqList DeleteList(SqList *L)
{
    static SqList ans;
    InitList_Sq(&ans);
    int ANS[100001];
    int count=0,tmpp=0;
    for(int tmp=0;tmp<L->length;tmp++)
    {
        if(L->elem[tmp]%2!=0)
        {
            count++;
            ANS[tmpp]=L->elem[tmp];
            tmpp++;
        }
    }
    NoinputCreateList(&ans,count,ANS);
    return ans;
}
SqList SpTest(SqList *L,int m)
{
    static SqList ans;
    InitList_Sq(&ans);
    int ANS[100001];
    int count=0,tmpp=0;
    for(int tmp=L->length-m;tmp<L->length;tmp++)
    {
        ANS[tmpp]=L->elem[tmp];
        tmpp++;count++;
    }
    for(int tmp=0;tmp<L->length-m;tmp++)
    {
        ANS[tmpp]=L->elem[tmp];
        tmpp++;count++;
    }
    NoinputCreateList(&ans,count,ANS);
    return ans;
}

int SpecialInsert(SqList *L,int element)
{
    for(int tmp=0;tmp<L->length;tmp++)
    {
        if(L->elem[tmp]>element)
        {
            Insert_Element(L,element,tmp+1);
            return OK;
        }
    }
    return OK;
}

int ContinuousDel(SqList *L,int location,int count)
{
    if(location+count-1>L->length||location>L->length)
        return 0;
    for(int tmp=location-1;tmp<=(L->length-1-count);tmp++)
    {
        L->elem[tmp]=L->elem[tmp+count];
    }
    L->length-=count;
    return 1;
}

int main()
{
    SqList L;
    if(InitList_Sq(&L)!=OK)
    {
        printf("Initialize Failed!\n");
        exit(ERROR);
    }
    CreateList(&L,5);
    PrintList(&L);
    getchar();

    /*printf("SpTest:");
    int m=0;    scanf("%d",&m);
    L=SpTest(&L,m);
    PrintList(&L);
    return 0;*/

    printf("Delete?\n");
    int Status=0;   scanf("%d",&Status);
    if(Status==1)   L=DeleteList(&L);
    PrintList(&L);
    int Insert,count;
    printf("Insert whattt?\n");
    scanf("%d",&Status);
    SpecialInsert(&L,Status);
    PrintList(&L);
    printf("Delete where in ? counts\n");
    scanf("%d %d",&Status,&count);
    if(ContinuousDel(&L,Status,count)==0)   printf("ERROR\n");
    PrintList(&L);
    free(L.elem);
}
