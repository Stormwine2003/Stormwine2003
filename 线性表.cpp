#include "stdio.h"
#include<stdlib.h>
#define YES 1
#define NO 0
#define initsize 10
#define ERROR -1

typedef struct {
	int* elem;
	int length;
	int listsize;
} Sqlist;

Sqlist InitList(Sqlist &L)
{
	L.elem = (int*)malloc(sizeof(Sqlist) * initsize);
	if (!L.elem)
	{
		printf("空间不足");
	}
	L.length = 0;
	L.listsize = initsize;
	return L;
}

int MakeEmpty(Sqlist& L)
{
	if (!L.length)
		return NO;
	L.length = 0;
	return YES;
}

void Destroy(Sqlist& L)
{
	free(L.elem);
	L.elem = NULL;
	L.length = 0;
	L.listsize = 0;
}

int Insert(Sqlist& L, int station, int e)
{
	if (L.length == L.listsize)
	{
		L.elem = (int*)realloc(L.elem, sizeof(int) * initsize + 1);
		if (!L.elem)
			return NO;
		L.listsize += 1;
	}
	if (station > L.length || station < 1)
		return NO;
	int j;
	for (j = L.listsize - 1; j > station; j--)
		L.elem[j] = L.elem[j - 1];
	L.elem[station] = e;
	L.length++;
	return YES;
}

int Find(Sqlist& L, int e, int& station)
{
	int i = -1;
	while (i++ < L.length)
		if (L.elem[i] == e)
		{
			station = i;
			e = 0;
			break;
		}
	if (!e)
		return station;
	return NO;
}

int EDelete(Sqlist& L, int e)
{
	int t = 0, j;
	if (!Find(L, e, t))
		return NO;
	t = Find(L, e, t);
	for (j = t; j < L.length; j++)
		L.elem[j] = L.elem[j + 1];
	L.elem[L.length--] = NULL;
	return t;
}//删除某元素，返回位置

int SDelete(Sqlist& L, int station)
{
	int t = 0, j;
	if (station<0 || station>L.length)
		return NO;
	t = L.elem[station];
	for (j = station; j < L.length; j++)
	{
		L.elem[j] = L.elem[j + 1];
	}
	L.elem[L.length--] = NULL;
	return t;
}

int IsEmpty(Sqlist L)
{
	return L.length = 0 ? YES : NO;
}

void PrintList(Sqlist &L)
{
	int i = 0;
	while (i++ < L.length)
	{
		printf("%d\t", L.elem[i]);
		if (i % 4 == 0)
			printf("\n");
	}
}

int main()
{
	Sqlist L;
	L=InitList(L);
	printf("%d,%d\n", L.listsize, L.length);
	int i = 0,t=1;
	while (i++ < initsize)
	{
		L.elem[i] = t++;
		L.length++;
	}
	printf("初始化的列表\n");
	PrintList(L);
	printf("\n");
	EDelete(L, 9);
	printf("删除一个元素的列表\n");
	PrintList(L);
	printf("\n");
	SDelete(L, 5);
	printf("删除一个位置的列表\n");
	PrintList(L);
	printf("\n");
	Insert(L, 4, 666);
	printf("插入后的列表\n");
	PrintList(L);
	printf("\n");
	if (IsEmpty(L))
		printf("列表非空\n");
	MakeEmpty(L);
	return 0;
}