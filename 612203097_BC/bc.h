#ifndef BC_H
#define BC_H
typedef struct node{
    int data;
    struct node*next;
}node;

typedef struct stack{
    node* *arr;
    int size;
    int top; 
} stack;

struct Stack{
    int size;
    int top;
    char *arr;
};

void print(node *head);
node* reverse(node*head);
int length(node *head);

node* add(node* first, node* second);
node* addTwoLists(node* first, node* second);
node* subtract(node *head1,node*head2);
node* multiply(node *head1, node *head2);

void init_stack(stack *s, int size);
int isFull(stack s);
int isEmpty(stack s);
void push(stack *s,node*head);
node* pop(stack *s);
int isOperator(char ch);
int isOperand(char ch);
node* evaluate(char postfix[], stack s);

int stackTop(struct Stack* sp);
int isFULL(struct Stack *ptr);
int isEMPTY(struct Stack *ptr);
void PUSH(struct Stack* ptr, char val);
char POP(struct Stack* ptr);
int precedence(char ch);
char* infixToPostfix(char* infix);

#endif
