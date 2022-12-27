#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TABLE_INT_SIZE 157

/* Functionality

Functions:
	- CharNum(char character) : returns the integer value of a character
	- Hash(char * string) : returns a integer value for a given string
	- HashTable() : initialises the hash map, returns map pointer
	- h_set(h_table * table, char * key, char * value) : add new item to the hashmap
	- h_delete(char * key) : delete key from hashmap, accounts for linked list


Changelog
	23.12.2022
		- Initial commit: Started work on polynomial rolling hashing function
	26.12.2022
		- Completed rolling hash function:
			- Using Rabin-Karp Search Algorithm
		- Started work with table structs
	27.12.2022
		- Finalised type system for string hashing function
		- Completed table + entry structs with LinkedList implementation
		- Added function HashTable()
		- Added function h_set(h_table * table, char * key, char * value)
		- Added function h_delete(h_table * table, char * key)
*/

typedef struct h_table {
	struct entry ** entries;
} h_table;


typedef struct entry {
	char * key;
	char * value;
	struct node * next;
} entry;


unsigned long long int power(int base, int exp) {
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
	// printf("Index: %i\n", index);
	return index;
}


h_table * HashTable() {

	h_table * new_table = (h_table *) malloc(sizeof(struct h_table));
	new_table -> entries = malloc(sizeof(struct entry *) * TABLE_INT_SIZE);

	// Set each item in the entries array to zero
	for (int i = 0; i < TABLE_INT_SIZE; ++i) {
		new_table -> entries[i] = NULL;
	}

	return new_table;
}


void h_set(h_table * table, char * key, char * value) {

	int slot = Hash(key); // this is the index in which we place the information

	if (table -> entries[slot] == NULL) {
		// this means the slot is unoccupied
		entry * new_entry = NULL;
		new_entry = (entry *) malloc(sizeof(struct entry));
		new_entry -> key = key;
		new_entry -> value = value;
		new_entry -> next = NULL;

		table -> entries[slot] = new_entry;
	}

	entry * new_entry = NULL;
	new_entry = malloc(sizeof(struct entry));

}

void h_delete(h_table * table, char * key) {
	// deletes a key from the table
	int slot = Hash(key);
	if (table -> entries[slot] != NULL) {
		free(table -> entries[slot]);
	}
}


void RunTests() {

	printf("Running hash function test...\n");
	int slot1 = Hash("F7LAKBMANS");
	int slot2 = Hash("L25I5OWMK5");
	int slot3 = Hash("6UJN5UV9YO");
	int slot4 = Hash("PY49WSG5LM");
	int slot5 = Hash("Helloworld");
	int slot6 = Hash("foo_bar");
	int slot7 = Hash("doo_bar");

	printf("Index: %i\n", slot1);
	printf("Index: %i\n", slot2);
	printf("Index: %i\n", slot3);
	printf("Index: %i\n", slot4);
	printf("Index: %i\n", slot5);
	printf("Index: %i\n", slot6);
	printf("Index: %i\n", slot7);
}


int main() {

	RunTests();

	return 0;
}