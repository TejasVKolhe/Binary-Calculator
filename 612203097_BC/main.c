#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include"bc.h"
#include"bc.c"

int main(){
    char infix[25]={'\0'};
    printf("Enter Expression :\n");
    scanf("%s", infix);
    
    char *postfix = infixToPostfix(infix);
    
    stack s;
    init_stack(&s,100);
    node*head = evaluate(postfix,s);
    
    printf("Result :\n");
    print(head);
    printf("\n");
    return 0;
}
