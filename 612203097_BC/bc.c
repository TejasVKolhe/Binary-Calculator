#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include"bc.h"

void print(node *head){
    while(head){
        printf("%d",head->data);
        head = head->next;
    }
    printf("\n");
    return;
}

node* reverse(node*head){
    if (!head || !head->next) return head;
    node*temp = head->next;
    node*smallhead = reverse(head->next);
    temp->next = head;
    head->next = NULL;
    return smallhead;
}

int length(node *head){
    if (!head) return 0;
    return 1+length(head->next);
}

// --------- ADDITION --------- //

node* add(node* first, node* second) {
    int carry = 0;
    node* ansHead = NULL;
    node* ansTail = NULL;
    while(first != NULL || second != NULL || carry != 0) {
        int val1 = 0;
        if(first != NULL)
            val1 = first -> data;
        int val2 = 0;
        if(second !=NULL)
            val2 = second -> data;
        int sum = carry + val1 + val2;
        int digit = sum%10;
        node*newnode = (node*)malloc(sizeof(node));
        newnode->data = digit;
        newnode->next = NULL;
        if (!ansHead){
            ansHead = newnode;
            ansTail = newnode;
        }
        else{
            ansTail->next = newnode;
            ansTail = newnode;
        }
        carry = sum/10;
        if(first != NULL)
            first = first -> next;
        if(second != NULL)
            second = second -> next;
    }
    return ansHead;
}

node* addTwoLists(node* first, node* second){
    first = reverse(first);
    second = reverse(second);
    node* ans = add(first, second);
    ans = reverse(ans);
    first = reverse(first);        
    second = reverse(second);        
    return ans;
    }

// --------- SUBTRACTION ----------- //

node* subtract(node *head1,node*head2){
    if (!head1 && !head2) return NULL;
    if (!head2) return head1;
    if (!head1){
        head2->data*=-1;
        return head2;
    }
    node *anshead = NULL;
    node *anstail = NULL;
    int len1 = length(head1);
    int len2 = length(head2);
    int flag = 1;
    if (len1<len2) flag = 0;
    else if (len1 == len2){
         node*a=head1;
         node*b=head2;
         while(a && b){
            if (a->data < b->data){
            flag = 0;
            break;
            }
            a = a->next;
            b = b->next;
        }
    }
    while(len1!=len2){
        node*newnode = (node*)malloc(sizeof(node));
        newnode->data = 0;
        if (len1<len2){
            newnode->next = head1;
            head1 = newnode;
            len1++;
        }
        else{
            newnode->next = head2;
            head2 = newnode;
            len2++;
        }
    }
    if (!flag){
        node*c = head1;
        head1 = head2;
        head2  = c;
    }
    head1 = reverse(head1);
    head2 = reverse(head2);
    node*temp1 = head1;
    node*temp2 = head2;
    int ans = 0;
    while(temp1 || temp2){
        if (temp1->data<temp2->data){
            if (temp1){
                temp1->data+=10;
                node*temp = temp1->next;
                while(temp && temp->data==0){
                    temp = temp->next;
                }
                if (temp){
                    temp->data--;
                }
                node *store = temp1->next;
                while(store!=temp){
                    store->data+=9;
                    store = store->next;
                }
            }
        }
        ans=(temp1->data - temp2->data);
        node *newnode = (node*)malloc(sizeof(node));
        newnode->data = ans;
        newnode->next = NULL;
        if (!anshead){
            anshead = newnode;
            anstail = newnode;
        }
        else{
            anstail->next = newnode;
            anstail = newnode;
        }
        temp1 = temp1->next;    
        temp2 = temp2->next;    
    }
    node*s = reverse(anshead);
    while(s->data == 0) s = s->next;
    if (!flag && s){
        s->data*=-1;
        flag = 1;
    }
    return s;
}

// ------------- MULTIPLICATION ------------ //

node* multiply(node *head1, node *head2){
    if (!head1 || !head2) return NULL;
    node*head = NULL;
    node*tail = NULL;
    node*newhead1 = reverse(head1);
    node*newhead2 = reverse(head2);
    int ct = 0;
    int multiply_by = 0;
    int carry = 0;
    while(newhead2){
        multiply_by = newhead2->data;
        carry = 0;
        node*temp = newhead1;
        node*temphead = NULL;
        node*temptail = NULL;
        while(temp){
            int val = (temp->data)*(multiply_by) + carry;
            int data = val%10;
            carry = val/10;
            node*newnode = (node*)malloc(sizeof(node));
            newnode->data = data;
            newnode->next = NULL;
            if (!temphead){
                temphead = newnode;
                temptail = newnode;
            }
            else{
                temptail->next = newnode;
                temptail = newnode;
            }
            if (!(temp->next) && carry){
                node*ansnode = (node*)malloc(sizeof(node));
                ansnode->data = carry;
                ansnode->next = NULL;
                if (!temphead){
                    temphead = ansnode;
                    temptail = ansnode;
                }
                else{
                    temptail->next = ansnode;
                    temptail = ansnode;
                }
            }
            temp = temp->next;
        }
        int store = ct;
        while(store){
            node*nn = (node*)malloc(sizeof(node));
            nn->data = 0;
            nn->next = temphead;
            temphead = nn;
            store--;
        }
        temphead = reverse(temphead);
        head = addTwoLists(head,temphead);
        newhead2 = newhead2->next;
        ct++;
    }    
    return head;
}

// ------------ STACK ------------- //


void init_stack(stack *s, int size){
    s->arr = (node**)malloc(sizeof(node*) * size);
    s->size = size;
    s->top = -1;
}

int isEmpty(stack s){
   return (s.top == -1); 
}

int isFull(stack s){
    return (s.top == (s.size - 1));
}

void push(stack *s,node*head){
    if (isFull(*s)) return;
    s->top++;
    s->arr[s->top] = head;
    return;
}

node* pop(stack *s){
    if (isEmpty(*s)) return NULL;
    node*head = s->arr[s->top];
    s->arr[s->top] = NULL; 
    s->top--;
    return head;
}

int isOperator(char ch){
    return (ch == '+' || ch == '-' || ch == '/' || ch == '*');
}

int isOperand(char ch){
    return ('0'<=ch && ch<='9');
}

node* evaluate(char postfix[], stack s){
    node*temp = NULL;
    int i = 0;
    while(i<strlen(postfix)){
        char ch  = postfix[i];
        if (isOperator(ch)){
            node* second_op = pop(&s);
            node* first_op = pop(&s);
            switch(ch){
                case('+'):
                    temp = addTwoLists(first_op,second_op);
                    break;
                case('-'):
                    temp = subtract(first_op,second_op);
                    break;
                case('*'):
                    temp = multiply(first_op,second_op);
                    break;
                default:    
                    break;
            }
            push(&s,temp);
            i++;
        }
        else if (isOperand(ch)){
            int val = 0;
            node*temphead = NULL;
            node*temptail = NULL;
            do{
                val =  postfix[i]-'0';
                node*newnode = (node*)malloc(sizeof(node));
                newnode->data = val;
                newnode->next = NULL;
                if (!temphead){
                    temphead = newnode;
                    temptail = newnode;
                }
                else{
                    temptail->next = newnode;
                    temptail = newnode;
                }
            i++;
            }
            while(isOperand(postfix[i]));
            push(&s,temphead);
        }
        else i++;
    }
    return pop(&s);
}


// ------------- Infix to Postfix -------------- //
 
int stackTop(struct Stack* sp){
    return sp->arr[sp->top];
}
 
int isEMPTY(struct Stack *ptr){
    if (ptr->top == -1)
        return 1;
    else
        return 0;
}
 
int isFULL(struct Stack *ptr){
    if (ptr->top == ptr->size - 1)
        return 1;
    else
        return 0;
}
 
void PUSH(struct Stack* ptr, char val){
    if(isFULL(ptr)){
        printf("Stack Overflow!\n");
    }
    else{
        ptr->top++;
        ptr->arr[ptr->top] = val;
    }
}
 
char POP(struct Stack* ptr){
    if(isEMPTY(ptr)){
        printf("Stack Underflow!\n");
        return -1;
    }
    else{
        char val = ptr->arr[ptr->top];
        ptr->top--;
        return val;
    }
}

int precedence(char ch){
    if(ch == '*' || ch=='/')
        return 3;
    else if(ch == '+' || ch=='-')
        return 2; 
    else
        return 0;
}

char* infixToPostfix(char* infix){
    struct Stack * sp = (struct Stack *) malloc(sizeof(struct Stack));
    sp->size = 10; 
    sp->top = -1;
    sp->arr = (char *) malloc(sp->size * sizeof(char));
    char * postfix = (char *) malloc((strlen(infix)+1) * sizeof(char));
    int i=0; 
    int j = 0;
    while (infix[i]!='\0'){
        if (infix[i] == '('){
            PUSH(sp,infix[i]);
            i++;
        }
        else if (infix[i] == ')'){
            while((stackTop(sp))!='('){
                postfix[j] = POP(sp);
                j++;
            }
            POP(sp);
            i++;
        }
        if(isOperand(infix[i])){
            do{
            postfix[j] = infix[i];
            j++;
            i++;
            }
            while(isOperand(infix[i]));
            postfix[j]=' ';
            j++;
        }
        else if(isOperator(infix[i])){
            if(precedence(infix[i])> precedence(stackTop(sp))){
                PUSH(sp, infix[i]);
                i++;
            }
            else{
                postfix[j] = POP(sp);
                j++;
            }
   	    }
        else i++;
    }
    while (!isEMPTY(sp)){
        postfix[j] = POP(sp);
        j++;
    }
    postfix[j] = '\0';
    return postfix;
}

