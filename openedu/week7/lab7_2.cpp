#include "edx-io.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <list>
#include <assert.h>
#include <tuple>

using namespace std;

typedef int32_t balance_t;

struct Node {
	int key;
	balance_t balance = 0;
	int height = 1;

	Node* parent = nullptr;
	Node* left = nullptr;
	Node* right = nullptr;

	// dirty hack
	int latest_population_descr_index;

	balance_t get_left_balance() { return (left) ? left->balance : -1; };
	balance_t get_right_balance() { return (right) ? right->balance : -1; };

	int get_left_height() { return (left) ? left->height : -1; };
	int get_right_height() { return (right) ? right->height : -1; };

	void replace_child(Node* from, Node* to) {
		if (left == from) {
			left = to;
		} else {
			assert(right == from);
			right = to;
		}
		to->parent = this;
		from->parent = nullptr;
	}
};

struct NodeDescription {
	int k;
	int li = 0;
	int ri = 0;
};

struct TreeDescription {
	vector<NodeDescription> descriptions;

	TreeDescription() {}
	TreeDescription(int size) : descriptions(size) {}

	NodeDescription& description_for_index(int index) {
		return descriptions[index];
	}

	void populate_from_tree(Node* tree) {
		// children set later
		descriptions.push_back(NodeDescription{ tree->key });
		
		// dirty hack for setting children!
		int current_index = descriptions.size() - 1;
		tree->latest_population_descr_index = current_index;

		// setting children of previously added things
		if (tree->parent) {
			if (tree->parent->left == tree) {
				descriptions[tree->parent->latest_population_descr_index].li = current_index + 1;
			} else {
				assert(tree->parent->right == tree);
				descriptions[tree->parent->latest_population_descr_index].ri = current_index + 1;
			}
		}

		// recursively populate from subtrees
		if (tree->left) {
			populate_from_tree(tree->left);
		}

		if (tree->right) {
			populate_from_tree(tree->right);
		}
	}
};

Node* build_tree(TreeDescription &input, int root_index = 0) {
	// root node description
	auto& rd = input.description_for_index(root_index);

	// create new node
	Node* tree = new Node();
	tree->key = rd.k;
	
	// recursively build left and right subtrees if needed
	if (rd.li) {
		tree->left = build_tree(input, rd.li - 1);
		tree->left->parent = tree;
	}

	if (rd.ri) {
		tree->right = build_tree(input, rd.ri - 1);
		tree->right->parent = tree;
	}
	
	// calculate height and balance
	tree->height = max(tree->get_right_height(), tree->get_left_height()) + 1;
	tree->balance = tree->get_right_height() - tree->get_left_height();

	return tree;
}

Node*& find_node(Node*& tree, int key) {
	if (tree == nullptr) {
		return tree;
	} else if (key == tree->key) {
		return tree;
	} else if (key < tree->key) {
		return find_node(tree->left, key);
	} else {
		return find_node(tree->right, key);
	}
}

void rotate_l(Node*& tree) {
	assert(tree->right != nullptr);
	Node* a = tree;
	Node* b = a->right;
	Node* x = a->left;
	Node* y = b->left;
	Node* z = b->right;

	if (a->parent) {
		a->parent->replace_child(a, b);
	} else {
		b->parent = nullptr;
	}
	
	b->left = a;
	a->parent = b;

	a->right = y;
	if (y) {
		y->parent = a;
	}

	tree = b;
}

void rotate_r(Node*& tree) {
	assert(tree->left != nullptr);
	Node* a = tree;
	Node* b = a->left;
	Node* x = a->right;
	Node* y = b->right;
	Node* z = b->left;

	if (a->parent) {
		a->parent->replace_child(a, b);
	} else {
		b->parent = nullptr;
	}

	b->right = a;
	a->parent = b;

	a->left = y;
	if (y) {
		y->parent = a;
	}

	tree = b;
}

void rotate_lr(Node*& tree) {
	// большой правый
	rotate_l(tree->left);
	rotate_r(tree);
}

void rotate_rl(Node*& tree) {
	// большой левый
	rotate_r(tree->right);
	rotate_l(tree);
}

int main() {
	int n;
	io >> n;
	
	TreeDescription input(n);
	for (auto& descr : input.descriptions) {
		io >> descr.k >> descr.li >> descr.ri;
	}

	auto tree = build_tree(input);

	if (tree->right->balance == -1) {
		rotate_rl(tree);
	} else {
		rotate_l(tree);
	}

	TreeDescription output;
	output.populate_from_tree(tree);

	io << n << "\n";
	for (auto& descr : output.descriptions) {
		io << descr.k << " " << descr.li << " " << descr.ri << "\n";
	}
	
	return 0;
}
