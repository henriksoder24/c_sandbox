#include <stdio.h>
#include <stdlib.h>


/* We need two types of elements:

*/

// Define Node Struct
struct node {
	int data;
	struct node * next;
	struct node * last; // This property remains NULL for all except the Head Node
};

// Initialise new Linked List Object
struct node * LinkedList(int data) {

	struct node * head = NULL;
	head = (struct node *) malloc(sizeof(struct node));
	head->next = NULL;
	head->last = NULL;

	if (data != 0) {
		head->data = data;
	}
	return head;
}

void InsertNewNode(struct node * LinkedList, int data) {

	// Add new node with data to a Linked List Object

	struct node * next_node = NULL;
	next_node = (struct node *) malloc(sizeof(struct node));


	if (data != 0) {
		next_node->data = data;
	}
	next_node->next = NULL;

	if (LinkedList->next == NULL) {
		LinkedList->next = next_node;
		LinkedList->last = next_node;
	} else if (LinkedList->next != NULL) {
		LinkedList->last->next = next_node;
		LinkedList->last = next_node;
	}
}

void TraverseList(struct node * LinkedList) {

	// Print out the content in each node for all nodes in the order of the Linked List

	int is_null = 0;
	struct node * current_node = LinkedList;

	while (is_null == 0) {
		printf("%i\n", current_node->data);
		if (current_node->next == NULL) {
			printf("End of List.\n");
			is_null = 1;
		} else {
			current_node = current_node->next;
		}
	}
}

void InsertBeforeNode(struct node * LinkedList, int insertion_point) {

	// Inserts new node before the node containing specific integer

	/*
	Requirements:
		- In case there is no node with the insertion point, do nothing	

	Two things are needed really, the previous nodes "next" and the next node's place in memory

	 */

	int dest = 0;
	int node_exists = 0;
	struct node * current_node = LinkedList; // Takes the head node

	while (dest == 0) {

		if (current_node->data == insertion_point) {
			printf("Found node with value %i\n", insertion_point);

			struct node * new_node = NULL;
			new_node = (struct node *) malloc(sizeof(struct node));


			dest = 1;
		} else {
			current_node = current_node->next;
			if (current_node == NULL) {
				printf("Reached the end of the list. No node with value %i exists\n", insertion_point);
				dest = 1;
			}
		}
	}


}


int main() {
	printf("Running Linked List Test...\n");

	struct node * myList = LinkedList(157);

	InsertNewNode(myList, 256);
	InsertNewNode(myList, 138);
	InsertNewNode(myList, 120);
	InsertNewNode(myList, 121);
	InsertNewNode(myList, 122);
	InsertNewNode(myList, 123);
	InsertNewNode(myList, 124);
	InsertNewNode(myList, 125);

	InsertBeforeNode(myList, 155);

	// TraverseList(myList);

	return 0;
}





