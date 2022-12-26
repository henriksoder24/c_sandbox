#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TABLE_INT_SIZE 157

/* Functionality

Functions:
	- char ** HashMap() : initialise the hash map
	- void HashMapAdd(char[] key, char[] value) : add new item to the hashmap
	- void HashMapDelete(char[] key)
	- char ** HashMapValues() : get list of all values stored in the HashMap

Changelog
	23.12.2022
		- Initial commit: Started work on polynomial rolling hashing function
	26.12.2022
		- Completed rolling hash function:
			- Using Rabin-Karp Search Algorithm
		- Started work with table structs
*/

// typedef struct ht {
// 	entries ** entries;
// };


int power(int base, int exp) {
	unsigned long long int product = base;
	if (exp == 0) {
		return 1;
	}
	for (int i = 1; i<exp; i++) {
		product *= base;
	}
	return product;
}


int CharNum(char character) {
	int char_num = (int) character;
	return char_num;
}


int Hash(char * string) {
	unsigned long long int sum = 0;
	int base = 31;
	int str_len = strlen(string);

	for (int i=0; i<str_len; i++) {

		int char_num = CharNum(string[i]);
		sum += char_num * power(base, str_len - i);
	}
	int index = sum % TABLE_INT_SIZE;
	printf("Index: %i\n", index);
	return 0;
}


void RunTests() {

	printf("Running hash function test...\n");
	Hash("F7LAKBMANS");
	Hash("L25I5OWMK5");
	Hash("6UJN5UV9YO");
	Hash("PY49WSG5LM");
}


int main() {

	RunTests();

	return 0;
}