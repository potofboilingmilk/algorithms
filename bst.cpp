#include <stdio.h>
#include <iostream>

using namespace std;

class Node {	// Define a Node object.
	public: 
		int value;		// It has an integer value...
		Node* left;		// ...a left neighbor...
		Node* right; 	// ...and a right neighbor.
		
		Node(int val) {				// Constructor function.
			this->value = val;		// This runs whenever a Node is created.
			this->left = NULL;		// It sets it up with some dummy parameters.
			this->right = NULL;
		}
};



void bst_inorder(Node* node) {		// Print a given Binary Search Tree in order.

	if (node == NULL) {				// If there's no Node to work on, stop execution. 
		return;						// This becomes REALLY RELEVANT once we start recurring.
	}								
	
	bst_inorder(node->left);		// Recursively execute this very function on the left neighbor of the input Node.
	
	cout << node->value << endl;	// Once we can't recur anymore, print the value of the Node we're currently analyzing.
	
	bst_inorder(node->right);		// Then, if applicable, start recurring for the right neighbor of the current input Node.
									// This can get confusing! Be sure to reference the Recursion Report to see a full explanation of how this function works.
}


int main() {
	char end;
	//BST values: 30, 18, 44, 11, 21, 35, 50
	//node initialization
	Node* root = new Node(30);
	root->left = new Node(18);
	root->right = new Node(44);
	root->left->left = new Node(11);
	root->left->right = new Node(21);
	root->right->left = new Node(35);
	root->right->right = new Node(50);
	
	bst_inorder(root);

	
	cin >> end;

}