#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct node{
	struct node *prev, *next;
	int data;
}node;

typedef struct list{
	node *front, *rear;
}list;

typedef struct number{
	list whole, fractional;
}number;

//typedef struct stack{
//	ptr btm, top;
//	int length;
//}stack;

void init_list(list*);
int isempty(list);
void insertright(list*, int);
void insertleft(list*, int);
void printlistLR(list );
void printlistRL(list );
int isDigit(int a);
list add(list, list);

char* getInput();
int isOperator(char c);
list storeNum(char* s);
int list_length(list l);
void init_num(number n);
number store(char* s);
number add_num(number n, number m);
void print_num(number n);

