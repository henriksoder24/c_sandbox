#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define TABLE_INT_SIZE 11

/* Functionality

Functions:
	- CharNum(char character) : returns the integer value of a character
	- Hash(char * string) : returns a integer value for a given string
	- HashTable(void) : initialises the hash table, returns map pointer
	- h_set(h_table * table, char * key, char * value) : add new item to the table
	- h_delete(h_table * table, char * key) : delete key from table, accounts for linked list
	- h_get(h_table * table, char * key) : returns value stored in key in table
	- h_dump(h_table * table) : prints all contained information in table
	- h_check(h_table * table, char * key) : checks existence of a key
	- RunTests(void) : void function running tests for above functions

Changelog
	23.12.2022
		- Initial commit: Started work on polynomial rolling hashing function
	26.12.2022
		- Completed rolling hash function:
			- Using Rabin-Karp Search Algorithm
		- Started work with table structs
	27.12.2022
		- Finalised type system for string hashing function
			- fixed type issues (i -> li -> lu -> llu)
		- Completed table + entry structs with LinkedList implementation
		- Added function HashTable()
		- Added function h_set(h_table * table, char * key, char * value)
		- Added function h_delete(h_table * table, char * key)
	28.12.2022
		- Added function h_get(h_table * table, char * key)
		- Added function h_dump(h_table * table)
		- Wrote tests for h_set(), h_get(), h_delete()
	08.01.2023
		- Added function h_check(h_table * table, char * key)
		- Added additional functionality to h_set()
			- Duplicate key handling
			- Key collision handling
		- Completed functionality for h_dump()
			- Print out all values
		- Wrote additional tests for h_set() and h_dump()
*/

typedef struct h_table {
	struct entry ** entries;
} h_table;


typedef struct entry {
	char * key;
	char * value;
	struct entry * next;
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


unsigned int Hash(char * string) {
	unsigned long long int sum = 0;
	unsigned int base = 31;
	unsigned int str_len = strlen(string);

	for (int i=0; i<str_len; i++) {

		unsigned int char_num = CharNum(string[i]);
		sum += char_num * power(base, str_len - i);
	}
	unsigned int index = sum % TABLE_INT_SIZE;
	return index;
}


h_table * HashTable(void) {

	h_table * new_table = (h_table *) malloc(sizeof(struct h_table));
	new_table -> entries = malloc(sizeof(struct entry *) * TABLE_INT_SIZE);

	// Set each item in the entries array to zero
	for (int i = 0; i < TABLE_INT_SIZE; ++i) {
		new_table -> entries[i] = NULL;
	}
	return new_table;
}


bool h_check(h_table * table, char * key) {

	unsigned int slot = Hash(key);
	entry * current_slot = table -> entries[slot];

	if (current_slot == NULL) {
		return false;
	} else if (current_slot -> key == key) {
		return true;
	} else {
		while (current_slot -> next != NULL) {
			if (current_slot -> key == key) {
				return true;
			}
			current_slot = current_slot -> next;
		}
		return false;
	}
}


void h_set(h_table * table, char * key, char * value) {

	unsigned int slot = Hash(key); // this is the index in which we place the information
	// check key existence
	bool ex = h_check(table, key);

	if (ex == true) {
		printf("ERROR: Key already exists\n");
		exit(1);
	}

	// get entry after existence check
	entry * entry_point = table -> entries[slot];
	// allocate memory for a new entry
	entry * new_entry = NULL;
	new_entry = (entry *) malloc(sizeof(struct entry));
	// insert key/value information
	new_entry -> key = key;
	new_entry -> value = value;
	new_entry -> next = NULL;

	if (entry_point == NULL) {
		// this means the slot is unoccupied
		entry_point = new_entry;
		printf("The slot is now occupied with key '%s' and value '%s'\n", new_entry -> key, new_entry -> value);
	
	} else {
		printf("The key has been placed into the linked list...\n");
		bool last_node = false;
		while (last_node != true) {
			

			if ()
		}

	}
}


char * h_get(h_table * table, char * key) {
	unsigned int slot = Hash(key);
	if (table->entries[slot] == NULL) {
		return NULL;
	} else {
		return table -> entries[slot] -> value;
	}
}

void h_delete(h_table * table, char * key) {	// deletes a key from the table
	unsigned int slot = Hash(key);
	if (table -> entries[slot] != NULL) {
		free(table -> entries[slot]);
		table -> entries[slot] = NULL;
	}
}

void h_dump(h_table * table) {
	// lists out all contents in the table

	for (int i = 0; i < TABLE_INT_SIZE; ++i)
	{
		if (table -> entries[i] != NULL) {
			printf("slot[%i]:", i);
		}
	}
}


void RunTests(void) {
	printf("-------------------------------------\n");
	printf("Running hash function test...\n");
	unsigned int slot1 = Hash("F7LAKBMANS");
	unsigned int slot2 = Hash("L25I5OWMK5");
	unsigned int slot3 = Hash("6UJN5UV9YO");
	unsigned int slot4 = Hash("PY49WSG5LM");
	unsigned int slot5 = Hash("Helloworld");
	unsigned int slot6 = Hash("foo_bar");
	unsigned int slot7 = Hash("doo_bar");

	printf("Index: %i\n", slot1);
	printf("Index: %i\n", slot2);
	printf("Index: %i\n", slot3);
	printf("Index: %i\n", slot4);
	printf("Index: %i\n", slot5);
	printf("Index: %i\n", slot6);
	printf("Index: %i\n", slot7);

	printf("-------------------------------------\n");
	printf("Initialising new hash table...\n");
	h_table * my_table = HashTable();
	printf("-------------------------------------\n");
	printf("Checking null for all slots in new hash table...\n");
	int null_indexes = 0;
	int not_null_indexes = 0;
	for (int i = 0; i < TABLE_INT_SIZE; ++i) {

		if (my_table -> entries[i] == NULL) {
			null_indexes++;
		} else {
			not_null_indexes++;
		}
	}
	printf("Table size: %i\n", TABLE_INT_SIZE);
	printf("Null indexes: %i\n", null_indexes);
	printf("Null index errors: %i\n", not_null_indexes);
	printf("-------------------------------------\n");
	printf("Setting test key: 'foo' with value 'bar'...\n");
	h_set(my_table, "foo", "bar");
	printf("-------------------------------------\n");
	printf("Getting value from test key 'foo'...\n");
	char * test_res = h_get(my_table, "foo");
	printf("Value from test key: %s\n", test_res);
	printf("-------------------------------------\n");
	printf("Deleting test key/value pair 'foo': 'bar'...\n");
	h_delete(my_table, "foo");
	printf("Getting value from test key 'foo'...\n");
	// h_set(my_table, "foo1", "bar1");
	char * test_res_2 = h_get(my_table, "foo");
	printf("Value from test key: %s\n", test_res_2);
	printf("-------------------------------------\n");
	printf("Checking null state of slots in table...\n");
	int null_indexes_1 = 0;
	int not_null_indexes_1 = 0;
	for (int i = 0; i < TABLE_INT_SIZE; ++i) {

		if (my_table -> entries[i] == NULL) {
			null_indexes_1++;
		} else {
			not_null_indexes_1++;
		}
	}
	printf("Table size: %i\n", TABLE_INT_SIZE);
	printf("Null indexes: %i\n", null_indexes_1);
	printf("Occupied indexes: %i\n", not_null_indexes_1);
	printf("-------------------------------------\n");
	printf("Setting keys, running existence checks...\n");

	h_set(my_table, "foo_bar", "bar_1");
	h_set(my_table, "doo_bar", "bar_2");

	printf("The key 'foo_bar' exists (T/F): %i\n", h_check(my_table, "foo_bar"));
	printf("The key 'doo_bar' exists (T/F): %i\n", h_check(my_table, "doo_bar"));
	printf("The key 'coo_bar' exists (T/F): %i\n", h_check(my_table, "coo_bar"));

	printf("-------------------------------------\n");
	printf("Running duplication tests...\n");

	h_set(my_table, "Helloworld", "bar3");
	printf("The key 'Helloworld' exists (T/F): %i\n", h_check(my_table, "Helloworld"));
}


int main() {

	RunTests();

	return 0;
}
