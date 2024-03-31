#include "BC_header.h"
#include <stdio.h>
#include <stdlib.h>
// Functions on Stack
void init_list(list *l)
{
    l->front = NULL;
    l->rear = NULL;
    return;
}
int islistEmpty(list l)
{
    if (l.front == NULL)
        return 1;
    else
        return 0;
}
void insertright(list *l, int d)
{
    node *newnode = (node *)malloc(sizeof(node));
    newnode->next = NULL;
    newnode->prev = NULL;
    newnode->data = d;
    if (!islistEmpty(*l))
    {
        node *temp = l->front;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = newnode;
        newnode->prev = temp;
        l->rear = newnode;
    }
    else
    {
        l->front = newnode;
        l->rear = newnode;
    }
}
void insertleft(list *l, int d)
{
    node *nn = (node *)malloc(sizeof(node));
    if (nn)
    {
        nn->prev = nn->next = NULL;
        nn->data = d;
    }
    else
        return;
    if (!islistEmpty(*l))
    {
        (l->front)->prev = nn;
        nn->next = l->front;
        l->front = nn;
    }
}
void printlistLR(list l)
{
    node *p;
    p = l.front;
    if (!p)
        return;
    do
    {
        printf("%d ", p->data);
        p = p->next;
    } while (p != NULL);
}
void printlistRL(list l)
{
    node *p;
    p = l.rear;
    printf("%d ", p->data);
    if (!p)
        return;
    do
    {
        printf("%d ", p->data);
        p = p->prev;
    } while (p != NULL);
    return;
}

// Functions on Stack
void init_stackList(stack_list *l)
{
    l->sfront = NULL;
    l->srear = NULL;
    return;
}
void init_stack(stack *s)
{
    init_stackList(&(s->l));
    s->top = NULL;
    return;
}
int isstackListEmpty(stack_list l)
{
    if (l.sfront == NULL)
        return 1;
    else
        return 0;
}
int isstackEmpty(stack s)
{
    if (s.top == NULL)
        return 1;
    else
        return 0;
}
void insert_stackLeft(stack_list *l, void *d)
{
    stack_node *nn = (stack_node *)malloc(sizeof(stack_node));
    if (nn)
    {
        nn->sprev = nn->snext = NULL;
        nn->sdata = d;
    }
    else
        return;
    if (!isstackListEmpty(*l))
    {
        l->sfront->sprev = nn;
        nn->snext = l->sfront;
        l->sfront = nn;
    }
}
void insert_stackRight(stack_list *l, void *d)
{
    stack_node *nn = (stack_node *)malloc(sizeof(stack_node));
    if (nn)
    {
        nn->sprev = nn->snext = NULL;
        nn->sdata = d;
    }
    else
        return;
    if (!isstackListEmpty(*l))
    {
        l->srear->snext = nn;
        nn->sprev = l->srear;
        l->srear = nn;
    }
    else
    {
        l->sfront = nn;
        l->srear = nn;
    }
}
void push(stack *s, void *d)
{
    insert_stackRight(&(s->l), d);
    s->top = s->l.srear;
    return;
}
stack_node *pop(stack *s)
{
    stack_node *ret = s->top->sdata;
    stack_node *del = s->top;
    stack_node *ptr = s->l.srear->sprev;
    ptr->snext = NULL;
    s->top = ptr;
    free(del);
    return ret;
}

// General Functions
int isDigit(char c)
{
    if (48<=c && c<=57)
        return 1;
    else
        return 0;
}
int isOperator(char c)
{
    if (c == '+' || c == '-' || c == '*' || c == '/')
        return 1;
    else
        return 0;
}
long long int count_op(char *s)
{
    long long int count = 0;
    for (int i = 0; s[i] != '\0'; i++)
    {
        if (isOperator(s[i]))
        {
            count++;
        }
    }
    return count;
}
char *getInput()
{
    int init_size = 50;
    int incr_size = 25;
    char *input = (char *)malloc(init_size * sizeof(char));
    if (input == NULL)
    {
        printf("Memory not allocated !");
        return input;
    }

    int size;
    printf("Enter a string : ");
    while (1)
    {
        fgets(input, init_size, stdin);
        size = strlen(input);

        if (input[size - 1] != '\n')
        {
            init_size += incr_size;
            input = (char *)realloc(input, init_size * sizeof(char));

            if (input == NULL)
            {
                printf("Memory allocation failed !");
                return input;
            }
        }
        else
        {
            input[size - 1] = '\0';
            printf("String entered is :%s", input);
            size = 0;
            break;
        }
    }
    return input;
}
int precedence(char x)
{
    if (x == '+' || x == '-')
        return 1;
    else if (x == '*' || x == '/')
        return 2;
    return 0;
}
long long int InfixtoPostfix(char *infix, char *postfix)    
{
    postfix[3 * count_op(infix)];
    int flag = 1;
    int i = 0, j = 0, k = 0;
    char *op1, *op2;
    stack s;
    init_stack(&s);
    int init_size = 100;
    while (infix[i])
    {
        if (infix[i] == ' ')
            i++;
        if (isDigit(infix[i])){   
            op1 = (char *)malloc(init_size * sizeof(char));
            while (isDigit(infix[i]))
            {
                op1[k++] = infix[i++];
            }
            op1[k] = 0;
            postfix[j++] = op1;
            k = flag = 0;
        }
        if (infix[i] == '('){
            op1 = (char *)malloc(1 * sizeof(char));
            strcpy(op1, "(");
            push(&s, (void *)op1);
        }
        if (infix[i] == ')'){
            op1 = (char *)pop(&s);
            while (op1 && strcmp(op1, "("))
            {
                postfix[j++] = op1;
                op1 = (char *)pop(&s);
            }
        }
        if ((flag == 0) && isOperator(infix[i])){
            op2 = (char *)pop(&s);
            printf("this is %c", op2[0]);
            while (op2 && (precedence(op2[0]) >= precedence(infix[i]))){
                postfix[j++] = op2;
                op2 = (char *)pop(&s);
            }
            if (op2 && (precedence(op2[0]) < precedence(infix[i]))){
                push(&s, (void *)op2);
            }
            flag = 1;
            op1 = (char *)malloc(2 * sizeof(char));
            if (infix[i] == '+')
                strcpy(op1, "+");
            if (infix[i] == '-')
                strcpy(op1, "-");
            if (infix[i] == '*')
                strcpy(op1, "*");
            if (infix[i] == '/')
                strcpy(op1, "/");
            push(&s, (void *)op1);
        }
        i++;
    }
    op2 = (char *)pop(&s);
    while (op2)
    {
        postfix[j++] = op2;
        op2 = (char *)pop(&s);
    }
    return j;
}
int list_length(list l)
{
    node *p = l.front;
    int count = 0;
    while (p)
    {
        count++;
        p = p->next;
    }
    return count;
}
void init_num(number n)
{
    init_list(&n.fractional);
    init_list(&n.whole);
    return;
}
number store(char *s)
{
    number n1;
    init_num(n1);
    int i = 0;
    while (s[i] != '.')
    {
        insertright(&n1.whole, s[i] - '0');
        i++;
    }
    if (s[i] == '.')
    {
        int j = i + 1;
        while (isDigit(s[j]))
        {
            insertright(&n1.fractional, s[i] - '0');
            j++;
        }
    }
    return n1;
}
number add_num(number n, number m)
{
    number res;
    init_num(res);
    int carry = 0;
    int len1, len2;
    len1 = list_length(n.fractional);
    len2 = list_length(m.fractional);

    node *p = n.fractional.rear;
    node *q = m.fractional.rear;

    if (len1 == len2)
    {
        while (p && q)
        {
            int sum = 0;
            sum = carry + p->data + q->data;
            insertright(&res.fractional, sum % 10);
            carry = sum / 10;
            p = p->prev;
            q = q->prev;
        }
    }
    else if (len1 > len2)
    {
        for (int i = 0; i < (len1 - len2); i++)
        {
            int sum = 0;
            sum = carry + p->data;
            insertright(&res.fractional, sum % 10);
            carry = sum / 10;
            p = p->prev;
        }
        while (p && q)
        {
            int sum = 0;
            sum = carry + p->data + q->data;
            insertright(&res.fractional, sum % 10);
            carry = sum / 10;
            p = p->prev;
            q = q->prev;
        }
    }
    else if (len2 > len1)
    {
        for (int i = 0; i < (len2 - len1); i++)
        {
            int sum = 0;
            sum = carry + q->data;
            insertright(&res.fractional, sum % 10);
            carry = sum / 10;
            q = q->prev;
        }
        while (p && q)
        {
            int sum = 0;
            sum = carry + p->data + q->data;
            insertright(&res.fractional, sum % 10);
            carry = sum / 10;
            p = p->prev;
            q = q->prev;
        }
    }

    // For the whole part
    node *s = n.whole.rear;
    node *t = m.whole.rear;
    while (s || t)
    {
        if (s && t)
        {
            int sum = 0;
            sum = carry + s->data + t->data;
            carry = sum / 10;
            insertright(&res.whole, sum % 10);
            s = t->prev;
            t = t->prev;
        }
        else if (!s)
        {
            int sum = 0;
            sum = carry + t->data;
            carry = sum / 10;
            insertright(&res.whole, sum % 10);
            t = t->prev;
        }
        else if (!t)
        {
            int sum = 0;
            sum = carry + s->data;
            carry = sum / 10;
            insertright(&res.whole, sum % 10);
            s = s->prev;
        }
    }
    return res;
}
void print_num(number n)
{
    node *a = n.whole.front;
    while (a)
    {
        printf("%d", a->data);
        a = a->next;
    }
    printf(".");
    a = n.fractional.front;
    while (a)
    {
        printf("%d", a->data);
    }
    return;
}
number evaluatPostfix(char *postfix)
{
    stack s;
    init_stack(&s);
    long long int length = strlen(postfix);
    number result;
    while (*postfix)
    {
        if (postfix[(length - 1)] == '+')
        {
            length--;
            number num1 = store(&postfix[length--]);
            number num2 = store(&postfix[length--]);
            result = add_num(num1, num2);
        }
    }
    return result;
}




