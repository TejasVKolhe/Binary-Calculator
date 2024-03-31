#include"header.h"
#include<stdlib.h>

void init_list(list *l){
    l->front = NULL;
    l->rear = NULL;
}


int isempty(list l){
    if(l.front ==NULL)
         return 1;
    return 0;
}


void insertright(list *l, int d) {
  node *newnode = (node*)malloc(sizeof(node));
  newnode->next =NULL;
  newnode->prev =NULL;
  newnode->data =d;
  if(!isempty(*l)){
     node *temp = l->front;
     while(temp->next!=NULL)
            temp = temp->next;
     temp->next = newnode;
     newnode->prev = temp;
     l->rear = newnode;
  }
  else{
     l->front = newnode;
     l->rear = newnode;
  }
}

void insertleft(list *l, int d){
	node *nn = (node *)malloc(sizeof(node));
	if(nn){
		nn->prev = nn->next = NULL;
		nn->data = d;
	}
	else return;
	if(!isempty(*l)){
		(l->front)->prev = nn;
		nn->next = l->front;
		l->front = nn;
	}
}

void printlistLR(list l) {    
    node *p;
    p = l.front;
    if(!p) return;
    do {
        printf("%d ", p->data);
        p = p->next;
    }while(p != NULL);
}

void printlistRL(list l) {
    node *p;
    p = l.rear;
    printf("%d ", p->data);
    if(!p) return;
    do {
        printf("%d ", p->data);
        p = p->prev;
    }while(p != NULL);
    return;
}

int isDigit(int a){
	if(0<= a && a<=9) return 1;
	else return 0;
}

list add(list l1, list l2){
    node *p, *q;
    p = l1.rear;
    q = l2.rear;
    
    list sum;
    init_list(&sum);
    while(p!=NULL || q!=NULL){
        int val = p->data + q->data;
        // printf("%d", val);
        insertleft(&sum, val);
        p = p->prev;
        q = q->prev;
    }
    return sum;
}

char* getInput(){
    int init_size = 50;
    int incr_size = 25;
    char *input = (char *)malloc(init_size * sizeof(char));
    if(input == NULL){
        printf("Memory not allocated !");
        return input;
    }

    int size;
    printf("Enter a string : ");
    while(1){
        fgets(input , init_size, stdin);
        size = strlen(input);

        if(input[size-1] != '\n'){
            init_size += incr_size;
            input = (char *)realloc(input, init_size *sizeof(char));

            if(input == NULL){
                printf("Memory allocation failed !");
                return input;
            }
        }
        else{
                input[size-1] = '\0';
                printf("String entered is :%s", input);
                size = 0;
                break;
        }
        
    }
    return input;
}

int isOperator(char c){
    if( c == '+' || c == '-' || c == '*' || c == '/' ) return 1;
    else return 0;
}

list storeNum(char* s){
    int i = 0;
    list num;
    init_num(num);
    for(int i = 0; s[i]!='\0'; i++){
        if(isOperator(s[i])){

            break;
        }
        insertright(&num, s[i]-'0');
        printf("\n");
        printlistLR(num);
    }
    return num;
}

int list_length(list l){
    node* p = l.front;
    int count = 0;
    while(p){
        count++;
        p = p->next;
    }
    return count;
}

void init_num(number n){
    init_list(&n.fractional);
    init_list(&n.whole);
    return;
}
long long int count_op(char *s){
    long long int count = 0;
    for(int i = 0 ; s[i]!='\0'; i++){
        if(isOperator(s[i])){
            count++;
        }
    }
    return count;
}


number store(char* s){
    number n1;
    init_num(n1);
    int i = 0;
    while(s[i] != '.'){
        insertright(&n1.whole, s[i]-'0');
        i++;
    }
    if(s[i] == '.'){
        int j = i+1;
        while(isDigit(s[j])){
            insertright(&n1.fractional, s[i]-'0');
            j++;
        }
    }
    return n1;
}

number add_num(number n, number m){
    number res;
    init_num(res);
    int carry = 0;
    int len1, len2;
    len1 = list_length(n.fractional);
    len2 = list_length(m.fractional);
    
    node *p = n.fractional.rear;
    node *q = m.fractional.rear;
        
    if(len1==len2){    
        while(p && q){
            int sum = 0;
            sum = carry + p->data + q->data;
            insertright(&res.fractional, sum%10);
            carry = sum/10;
            p = p->prev;
            q = q->prev;
        }
    }
    else if(len1 > len2){
        for(int i= 0; i<(len1-len2) ; i++){
            int sum = 0;
            sum = carry + p->data;
            insertright(&res.fractional, sum%10);
            carry = sum/10;
            p = p->prev;
        }
        while(p && q){
            int sum = 0;
            sum = carry + p->data + q->data;
            insertright(&res.fractional, sum%10);
            carry = sum/10;
            p = p->prev;
            q = q->prev;
        }
    }
    else if(len2>len1){
        for(int i= 0; i<(len2-len1) ; i++){
            int sum = 0;
            sum = carry + q->data;
            insertright(&res.fractional, sum%10);
            carry = sum/10;
            q = q->prev;
        }
        while(p && q){
            int sum = 0;
            sum = carry + p->data + q->data;
            insertright(&res.fractional, sum%10);
            carry = sum/10;
            p = p->prev;
            q = q->prev;
        }
    }

    // For the whole part
    node *s = n.whole.rear;
    node *t = m.whole.rear;
    while(s || t){
        if(s && t){
            int sum = 0; 
            sum = carry + s->data + t->data;
            carry = sum/10;
            insertright(&res.whole, sum%10);
            s = t->prev;
            t = t->prev;x
        }
        else if(!s){
            int sum = 0;
            sum = carry + t->data;
            carry = sum/10;
            insertright(&res.whole, sum%10);
            t = t->prev;
        }
        else if(!t){
            int sum = 0;
            sum = carry + s->data;
            carry = sum/10;
            insertright(&res.whole, sum%10);
            s = s->prev;
        }
    }
    return res;
}

void print_num(number n){
    node* a = n.whole.front;
    while(a){
        printf("%d", a->data);
        a = a->next;
    }
    printf(".");
    a = n.fractional.front;
    while(a){
        printf("%d", a->data);
    }
    return;
}

long long int InfixtoPostfix(char *s, char *postfix){
    char postfix[count_op(s)];
    int flag = 1;
    int i = 0, j = 0, j = 0, k = 0;
    char *op1, *op2;
    stack s;
    init_stack(&s);
    int init_size = 100;
    while(s[i]){
        if(s[i]==' ') i++;
        if(isDigit(s[i])){
            op1 = (char*)malloc(size*sizeof(char));
            int size = strlen(op1);
            while(isDigit(s[i])){
                if(op[size-1] != '\n'){
                    init_size += init_size;
                    op1 = (char*)realloc(op1, init_size*sizeof(char));
                }
                op1[k++] = s[i++];
            }
            op1[k] = 0;
            postfix[j++] = op1;
            k = flag = 0;
        }
        if(s[i] == '('){
            op1= (char*)malloc(2*sizeof(char));
            strcpy(op1, "(");
            push(&s, (void*)op1);
        }
        if (s[i]==')'){
			op1=(char*)pop(&s);
			while (op1&&strcmp(op1, "(")){
				postfix[j++]=op1;
				op1 = (char*) pop(&s);
			}
		}
        if( (flag==0) && isOperator(s[i]) ){
            op2 = (char*) pop(&s);
            while( op2 && (precedence(op2[0]) >= precedence(s[i]) ) ){
                postfix[j++] = op2;
                op2 = (char*) pop(&s);
            }
            if( op2 && (precedence(op2[0]) < precedence(s[i]) ) ){
                push(&s, (void*)op2);
            }
            flag = 1;
            op1 = (char*)malloc(2*sizeof(char));
            if (s[i]=='+') strcpy(op1, "+");
			if (s[i]=='-') strcpy(op1, "-");
			if (s[i]=='') strcpy(op1, "");
			if (s[i]=='/') strcpy(op1, "/");
            push(&s, (void*)op1);
        }   
        i++
    }
	op2=(char*)pop(&s);

	while (op2){
		postfix[j++]=op2;
		op2=(char*)pop(&s);
	}
	return j;
}

int infixToPostfix(char infix[], char *postfix[]){
	int flag=1,i=0,j=0,k=0;
	char *op1, *op2;
	stack s;
	init_stack(&s);

	while (infix[i]){
		if (infix[i]==' ') i++;
		if (isdigit(infix[i])){
			op1 = (char *)malloc(100*sizeof(char));
			while (isdigit(infix[i])){
				op1[k++]=infix[i++];
			}
			op1[k]=0;
			postfix[j++]=op1;
			k=0;
			flag=0;
		}
		if (infix[i]=='('){
			op1=(char*)malloc(2*sizeof(char));
			strcpy(op1, "(");
			push(&s, (void*)op1);
		}
		if (infix[i]==')'){
			op1=(char*)pop(&s);
			while (op1&&strcmp(op1, "(")){
				postfix[j++]=op1;
				op1 = (char*) pop(&s);
			}
		}
		if ((flag==0)&&isOp(infix[i])){
			op2 = (char*) pop(&s);
			while (op2&&(precedence(op2[0]) >= precedence(infix[i]))){
				postfix[j++]=op2;
				op2=(char*)pop(&s);
			}
			if (op2&&(precedence(op2[0])<precedence(infix[i]))){
				push(&s, (void*) op2);
			}
			flag=1;
			op1=(char*)malloc(2*sizeof(char));
			if (infix[i]=='+') strcpy(op1, "+");
			if (infix[i]=='-') strcpy(op1, "-");
			if (infix[i]=='') strcpy(op1, "");
			if (infix[i]=='/') strcpy(op1, "/");
			push(&s, (void*) op1);
		}
		i++;
	}

	op2=(char*)pop(&s);

	while (op2){
		postfix[j++]=op2;
		op2=(char*)pop(&s);
	}
	return j;
}