#include<stdio.h>
#include<stdlib.h>
#include<string.h>


//All structured required
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

typedef struct stack_node{
    void *sdata;
    struct stack_node *sprev, *snext;
}stack_node;

typedef struct stack_list{
    stack_node *sfront, *srear;
}stack_list;

typedef struct stack{
    stack_list l;
    stack_node *top;
}stack;

//Functions on Doubly Linked List
void init_list(list *l);
int islistEmpty(list l);
void insertright(list *l, int d);
void insertleft(list *l, int d);
void printlistLR(list l);
void printlistRL(list l);

//Functions on Stack using DLL
void init_stackList(stack_list *l);
void init_stack(stack *s);
int isstackListEmpty(stack_list l);
int isstackEmpty(stack s);
void insert_stackLeft(stack_list *l, void* d);
void insert_stackRight(stack_list *l, void* d);
void push(stack *s, void *d);
stack_node* pop(stack *s);

//General Functions
int isDigit(char c);
int isOperator(char c);
int precedence(char x);
long long int count_op(char *s);
char* getInput();
long long int InfixtoPostfix(char *s, char *postfix);
number store(char* s);
number add_num(number n, number m);
void print_num(number n);
number evaluatPostfix(char *postfix);
void init_num(number n);
int list_length(list l);