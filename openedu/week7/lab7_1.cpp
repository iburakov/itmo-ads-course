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

	balance_t get_left_balance() { return (left) ? left->balance : -1; };
	balance_t get_right_balance() { return (right) ? right->balance : -1; };

	int get_left_height() { return (left) ? left->height : -1; };
	int get_right_height() { return (right) ? right->height : -1; };
};

struct NodeDescr {
	int k;
	int li;
	int ri;

	// remember balance just for this task
	balance_t balance_result;
};

Node* build_tree(vector<NodeDescr> &input, int root_index = 0) {
	// root node description
	NodeDescr& rd = input[root_index];

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

	// remember balance just for this task
	rd.balance_result = tree->balance;

	return tree;
}

Node* find_node(Node* tree, int key) {
	if (tree == nullptr) {
		return nullptr;
	} else if (key == tree->key) {
		return tree;
	} else if (key < tree->key) {
		return find_node(tree->left, key);
	} else {
		return find_node(tree->right, key);
	}
}

int main() {
	int n;
	io >> n;
	
	vector<NodeDescr> input(n);
	for (auto& descr : input) {
		io >> descr.k >> descr.li >> descr.ri;
	}

	auto tree = build_tree(input);

	for (auto& descr : input) {
		io << descr.balance_result << "\n";
	}
	
	return 0;
}
