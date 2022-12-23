#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* Functionality

	List of defined functions:

		- LinkedList (int data, bool double_link)
		- AppendNode(struct node *, int data)
		- TraverseList(struct node *)
		- GetListData(struct node *)

	Change Log

	09.10.2022
		- First commit
	18.12.2022
		- Added support for doubly-linked lists
		- Removed old functions:
			- InsertNode (currently being re-engineered)
			- DeleteNode (currently being re-engineered)
		- Re-engineered functions to support doubly-linked lists:
			- LinkedList
			- AppendNode
			- TraverseList
			- GetListData
*/


// Define Head Node Struct for Single Link
struct head {
	int data;

	// Single-linked nodes
	struct node * next;
	struct node * last; // Last node in the list

	// double-linked nodes
	struct dnode * _next;
	struct dnode * _last;

	// Linked List Properties
	bool dlinked;
	int length;

	// Struct Methods
	//void (*AppendNode)(struct node *, int data);
};

// Single-linked Node
struct node {
	int data;
	struct node * next;
};

// Double-linked Nodes
struct dnode {
	int data;
	struct dnode * next;
	struct dnode * previous;
};

typedef struct string_obj {
	char * data;
	int length;
} string_obj;


// Initialise new Linked List Object
struct head * LinkedList(int data, bool double_link) {

	struct head * head_node = NULL;
	head_node = (struct head *) malloc(sizeof(struct head));

	head_node -> dlinked = double_link;
	head_node -> data = data;
	head_node -> last = NULL;
	head_node -> next = NULL;
	head_node -> _next = NULL;
	head_node -> _last = NULL;
	head_node -> length = 1;

	return head_node;
};


void AppendNode(struct head * head, int data) {

	if (head -> dlinked == true) {
		// Initialise new node in the list
		struct dnode * new_node = NULL;
		new_node = (struct dnode *) malloc(sizeof(struct dnode));
		new_node -> data = data;
		new_node -> next = NULL; 

		if (head -> length == 1) {
			new_node -> previous = NULL;
			head -> _next = new_node;
			head -> _last = new_node;
		} else {
			new_node -> previous = head -> _last;
			head -> _last -> next = new_node;
			head -> _last = new_node;
		}
	} else {
		struct node * new_node = NULL;
		new_node = (struct node *) malloc(sizeof(struct node));
		new_node -> data = data;
		if (head -> length == 1) {
			head -> next = new_node;
			head -> last = new_node;
		} else {
			head -> last -> next = new_node;
			head -> last = new_node;
		}
	}
	head -> length++;
}


void TraverseList(struct head * list) {
	// Prints out data in every node of the list

	printf("Node #0: %i\n", list -> data);
	int node_count = 1;

	if (list -> dlinked == true) {
		struct dnode * current_node = list -> _next;
		while(current_node != NULL) {
			printf("Node #%i: %i\n", node_count, current_node -> data);
			node_count++;
			current_node = current_node -> next;
		}
	} else {
		struct node * current_node = list -> next;
		while(current_node != NULL) {
			printf("Node #%i: %i\n", node_count, current_node -> data);
			node_count++;
			current_node = current_node -> next;
		}
	}
} 


int * GetListData(struct head * list) {

	int * arr = (int *) malloc(sizeof(int) * list -> length);
	int node_count = 1;
	arr[0] = list -> data;

	if (list -> dlinked == true) {
		struct dnode * current_node = list -> _next;
		while(current_node != NULL) {
			arr[node_count] = current_node -> data;
			node_count++;
			current_node = current_node -> next;
		}
	} else {
		struct node * current_node = list -> next;
		while(current_node != NULL) {
			arr[node_count] = current_node -> data;
			node_count++;
			current_node = current_node -> next;
		}
	}
	return arr;
}


void RunTests() {


	printf("Running Linked List Test...\n");
	int data_point = 157;
	bool double_linked = true;
	struct head * myList = LinkedList(157, true);
	AppendNode(myList, 111);
	AppendNode(myList, 222);
	AppendNode(myList, 444);
	AppendNode(myList, 445);
	AppendNode(myList, 446);
	AppendNode(myList, 447);
	AppendNode(myList, 448);
	TraverseList(myList);

	int * ListData = GetListData(myList);
	for (int i = 0; i<myList->length; i++) {
		printf("Value in list: %i\n", ListData[i]);
	}
}


int main() {

	RunTests();

	return 0;
}





