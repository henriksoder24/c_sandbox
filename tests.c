#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct texts {
	char * string;
};

int main() {

	struct texts * new;
	new = (struct texts *) malloc(sizeof(struct texts));
	new->string = "Hello World!\n";

	printf("%lu\n", strlen(new->string));

	return 0;
}