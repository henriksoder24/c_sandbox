#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define TABLE_INT_SIZE 157

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
	- h_destroy(h_table * table) : frees all table memory
	- h_total(h_table * table) : returns the total number of entries stored in table
	- RunTests(void) : void function running tests for above functions

Changelog
	23.12.2022
		- Initial commit: Started work on polynomial rolling hashing function
	26.12.2022
		- Completed rolling hash function:
			- Using Rabin-Karp rolling hash function
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
	27.01.2023
		- Finished h_check(), h_set(), h_dump()
		- Started work on h_destroy()
	28.01.2023
		- finished h_destroy(), h_get()
		- added function h_total()
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


int charnum(char character) {
	int char_num = (int) character;
	return char_num;
}


unsigned int Hash(char * string) {
	unsigned long long int sum = 0;
	unsigned int base = 31;
	unsigned int str_len = strlen(string);

	for (int i=0; i<str_len; i++) {

		unsigned int char_num = charnum(string[i]);
		sum += char_num * power(base, str_len - i);
	}
	unsigned int index = sum % TABLE_INT_SIZE;
	return index;
}


h_table * ht_create(void) {

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
	// printf("Looking for key: %s\n", key);

	if (current_slot == NULL) {
		return false;
	} else if (current_slot -> key == key) {
		return true;
	} else {
		// printf("HERE IN CHECK\n");
		while (current_slot != NULL) {
			// printf("HERE IN WHILE LOOP\n");

			// printf("Current key: %s\n", current_slot -> key);
			if (current_slot -> key == key) {
				// printf("RETURNING KEY HERE\n");
				return true;
			}
			current_slot = current_slot -> next;
		}
		// printf("HERE IN CONDITION\n");
		return false;
	}
}


entry * h_entry(char * key, char * value) {
	entry * new_entry = NULL;
	new_entry = (entry *) malloc(sizeof(struct entry));
	new_entry -> key = key;
	new_entry -> value = value;
	new_entry -> next = NULL;

	return new_entry;
}


char * h_get(h_table * table, char * key) {
	unsigned int slot = Hash(key);
	if (table->entries[slot] == NULL) {
		return NULL;
	} else {
		entry * current_slot = table->entries[slot];
		while (current_slot != NULL) {
			if (current_slot -> key == key) {
				return current_slot -> value;
			}
			current_slot = current_slot -> next;
		}
	}
	return NULL;
}


void h_delete(h_table * table, char * key) {
	// deletes a key from the table
	unsigned int slot = Hash(key);
	if (table -> entries[slot] != NULL) {
		free(table -> entries[slot]);
		table -> entries[slot] = NULL;
	}
}


void h_dump(h_table * table) {
	printf("\n-------------------------------------\n\n");
	// lists out all contents in the table
	for (int i = 0; i < TABLE_INT_SIZE; ++i) {

		entry * current_slot = table -> entries[i];

		while (current_slot != NULL) {
			if (current_slot != NULL) {
				printf("slot[%i]=('%s','%s') ", i, current_slot -> key, current_slot -> value);
			}
			current_slot = current_slot -> next;
			if (current_slot == NULL) {
				printf("\n");
			}
		}
	}
	printf("\n-------------------------------------\n");
}


void h_set(h_table * table, char * key, char * value) {

	unsigned int slot = Hash(key); // this is the index in which we place the information
	// printf("Key '%s' gets hash %i\n", key, slot);
	// check key existence
	bool ex = h_check(table, key);

	if (ex == true) {
		printf("ERROR: Key '%s' already exists\n", key);
		exit(1);
	}

	if (table -> entries[slot] == NULL) {
		// Meaning that this slot is unoccupied
		table -> entries[slot] = h_entry(key, value);
	} else {

		entry * current_slot = table -> entries[slot];
		// Loop from first 'next' entry until we get to a slot where the next node has no entry
		while (1) {
			if (current_slot -> next == NULL) {
				current_slot -> next = h_entry(key, value);
				break;
			}
			current_slot = current_slot -> next;
		}
	}
}


int h_total(h_table * table) {
	// returns the total number of keys stored in the table
	int total_items = 0;

	for (int i = 0; i < TABLE_INT_SIZE; ++i) {
		if (table -> entries[i] != NULL) {
			total_items++;
			entry * current_slot = table -> entries[i];
			while (1) {
				if (current_slot -> next != NULL) {
					total_items++;
					current_slot = current_slot -> next;
				} else {
					break;
				}

			}
		}
	}
	return total_items;
}


void h_destroy(h_table * table) {

	int pointer_no = h_total(table);
	// this function collects all pointers and destroys them
	// find all pointers. they are all entry pointers

	struct entry ** all_pointers = NULL;
	all_pointers = malloc(sizeof(struct entry *) * pointer_no);

	printf("Size of struct entry pointer: %lu\n", sizeof(struct entry *));
	printf("Size of pointer arrays to destroy: %lu\n", sizeof(all_pointers));


	for (int i = 0; i < TABLE_INT_SIZE; ++i) {
		// entry * current_slot = table -> entries[i];
		if (table -> entries[i] != NULL) {
			printf("Freeing slot number: %i\n", i);
			free(table -> entries[i]);

			entry * current_slot = table -> entries[i];
			while (1) {
				
				if (current_slot -> next != NULL) {
					free(current_slot -> next);
					current_slot = current_slot -> next;

				}
			}

			table -> entries[i] = NULL;
		} 
	}
}


void RunTests(void) {
	printf("-------------------------------------\n");

	h_table * my_table = ht_create();

	printf("Setting keys, running existence checks...\n");
	h_set(my_table, "foo", "bar");
	h_set(my_table, "Helloworld", "yes");
	h_set(my_table, "foo_bar", "nono");
	h_set(my_table, "noe_bar", "yea");
	h_set(my_table, "F7LAKBMANS", "hey man");
	h_set(my_table, "8wA9G6Thke", "edelweiss");
	h_set(my_table, "RzAJKXfvgd", "cie");
	h_set(my_table, "Ex6QGHnLXD", "verbena blossom");
	h_set(my_table, "DB3rIs6Ssw", "solgar company");
	h_set(my_table, "PpGTpDmaZ1", "apple");
	h_set(my_table, "MHhUhexXkU", "logitech");
	h_set(my_table, "1OZ3lWcqIt", "blue shields");
	h_set(my_table, "dPxwo2jjcZ", "IKEA");

	// Dump Table
	h_dump(my_table);

	// Check occupied indexes
	int occ_indexes = 0;
	int unocc_indexes = 0;
	for (int i = 0; i < TABLE_INT_SIZE; ++i) {
		if (my_table -> entries[i] == NULL) {
			unocc_indexes++;
		} else {
			occ_indexes++;
		}
	}
	printf("Total indexes: %i\n", TABLE_INT_SIZE);
	printf("Occupied indexes: %i\n", occ_indexes);
	printf("NUll indexes: %i\n", unocc_indexes);
	printf("-------------------------------------\n");

	// // Check occupied indexes
	// int occ_indexes1 = 0;
	// int unocc_indexes1 = 0;
	// for (int i = 0; i < TABLE_INT_SIZE; ++i) {
	// 	if (my_table -> entries[i] == NULL) {
	// 		unocc_indexes1++;
	// 	} else {
	// 		occ_indexes1++;
	// 	}
	// }
	// printf("-------------------------------------\n");
	// printf("Total indexes: %i\n", TABLE_INT_SIZE);
	// printf("Occupied indexes: %i\n", occ_indexes1);
	// printf("NUll indexes: %i\n", unocc_indexes1);
	printf("Total items: %i\n", h_total(my_table));

	// Destroy table
	// h_destroy(my_table);

}


int main() {

	RunTests();

	return 0;
}
