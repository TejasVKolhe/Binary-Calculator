#include <stdio.h>
#include "logic.c"

int main()
{
	char *s;
	s = getInput();
	list l1 = storeNum(s);
	node* p = l1.front;
	printf("\n");
	// printlistLR(l1);

	number nos;
	init_num(nos);
	print_num(store(s));	
	return 0;
}
