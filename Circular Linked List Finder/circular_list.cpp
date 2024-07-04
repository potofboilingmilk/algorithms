#include <stdio.h>
#include <iostream>

using namespace std;

class Node {
	public: 
		int value;
		Node* prev;
		Node* next;
		
		
		
		Node(int val = 1) {
			value = val;
			prev = nullptr;
			next = nullptr;
		}
};


void size_detector(Node* this_node, Node* p, Node* q) {
	p = this_node;		// Keep track of where we started. This one won't change.
	q = this_node;		// We'll use q to operate on the list itself. This one will change.
	int list_size = 0;
	if (q->next != nullptr) {		// So long as there is a next node...
			while(q != p) {			// ...and our current node isn't the same as the node we just logged...
				list_size++;		// ...increment the list size. 
				q = q->next;		// ...and set q to the next node.
			}
	}
	
	if (q->next == nullptr) {
		cout << "End reached: has a definite end." << endl; 
	} else if (q == p) {
		cout << "End reached: it seems to be at least a little circular!" << endl;
	}
			
}

void circle_detector(Node* this_node, Node* p, Node* q) {	// Currently only supports linked lists that are circles. A second version of the algorithm (which is more definitive) is available, but requires a definite linked list size.
	p = this_node;				// Keep track of where we started.
	if (p->next != nullptr) {	// Make sure that the next node exists!
		q = p->next;			// ...and set q equal to it.
	} else {
		cout << "It seems that this linked list consists of only one member!" << endl;		// If this doesn't work, the linked list probably has only one element, or it's misconfigured.
	}
	
	while (q->next != nullptr) {						// So long as there's a next element...
		//cout << "p-value = " <<  p->value << endl;	// The algorithm compares the actual memory addresses of both nodes.
		//cout << "q-value = " <<  q->value << endl;	// Their values don't matter... but if they're all unique, it may help illustrate how the algorithm works!
		if (q == p) {									// If our q node is the exact same as the p node...
			cout << "The linked list is circular!" << endl;	// then that must mean we looped back to where we started!
			return;											// End function execution if we do!
		}
		q = q->next;									// Otherwise, q takes the value of its next neighbor.
	}
	
	cout << "The linked list seems to have a definite end.\nIt may not be circular!" << endl;	// The function can only reach this place if we don't return earlier. Therefore, it can only reach here if the list isn't circular.
}


void circle_detector_adv(Node* this_node, Node* p, Node* q, int list_size, int round = 0) {	// 
	p = this_node;	// Keep track of where we started.
	int i = round;	// We will operate on this value.
	int k = round;	// We will keep track of this one. Whenever this algorithm recurs, this value increments. The algorithm ceases recursion when this value is equal to the size of the list.
	
	if (p->next != nullptr) {	// If p has a next neighbor...
		q = p->next;			// ...set q = p's next neighbor.
	} else {
		cout << "The given start node has no next neighbor!" << endl;	// Otherwise, the list has already ended.
	}
	
	while ((q->next != nullptr) & (i < list_size)) {	// So long as q has a next neighbor, AND a tracker variable 'i' isn't exceeding the size of the list...
		//cout << "p-value = " <<  p->value << endl;	// The algorithm compares the actual memory addresses of both nodes.
		//cout << "q-value = " <<  q->value << endl;	// Their values don't matter... but if they're all unique, it may help illustrate how the algorithm works!
		if (q == p) {									// If p and q are the same node...
			cout << "The linked list is circular!" << endl;	// ...then the list must be circular!
			k = list_size;									// Tracker variable 'k' is set to exceed the list size to prevent unnecessary recursion.
			return;											// End execution!
		}
		q = q->next;									// Otherwise, q becomes its next neighbor...
		i++;											// ...and 'i' increments. 
	}													// If 'i' reaches the size of the list, then we've looked at each element at least once (or perhaps a lot more than once). Either way, if we kept going, we'd be wasting time with repeated comparisons.
	
	if (k < list_size) {								// If 'k' doesn't exceed the size of the list...
		k++;											// ...increment it by once...
		circle_detector_adv(p->next, p, q, list_size, k);	// ...and recur. Note, that the new 'this_node' parameter is p's next neighbor. Recall: p has not changed this entire time.
	}														// Therefore, until the list is found to be circular, or we run out of nodes to analyze, the value for p will slowly 'creep up' each node of the array.
														// It will be the first node, then the second, then the third... until, based on 'k', it's been every node at least once.
														// If this function doesn't return any output to console, then the list must have a definitive end.

	
}

int main() {
	char end;

	// Create the linked list!
	Node *node_a = new Node(1);
	Node *node_b = new Node(2);
	Node *node_c = new Node(3);
	Node *node_d = new Node(4);
	Node *node_e = new Node(5);
	Node *node_f = new Node(6);
	
	// Create some helper nodes.
	Node *temp_a = new Node(0);
	Node *temp_b = new Node(0);
	
	
	
	// Order the linked list. Connect the nodes.
	// First, connect them forwards...
	node_a->next = node_b;
	node_b->next = node_c;
	node_c->next = node_d;
	node_d->next = node_e;
	node_e->next = node_f;
	node_f->next = node_d; // <---------- Set node_f->next = node_a if you're testing circle_detector() and NOT circle_detector_adv()!!!!!!!
	
	// Now, backwards!
	node_a->prev = node_f;
	node_f->prev = node_e;
	node_e->prev = node_d;
	node_d->prev = node_c;
	node_c->prev = node_b;
	node_b->prev = node_a;
	
	
	// Okay, now lets work with it.

	circle_detector_adv(node_a, temp_a, temp_b, 6);
	
	
	
	cin >> end;
	
	delete node_a, node_b, node_c, node_d, node_e, node_f, temp_a, temp_b;

}