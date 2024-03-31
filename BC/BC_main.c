#include<stdio.h>
#include"BC_logic.c"

int main(){
    char *infix;
    infix = getInput();
    char *postfix;
    int j = InfixtoPostfix(infix, postfix);
    printf("hello");
    number result = evaluatPostfix(postfix);
    print_num(result);
    printf("hi");
    return 0;
}