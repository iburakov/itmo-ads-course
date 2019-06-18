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

	Node(int key) : key(key) {}

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
		if (to) {
			to->parent = this;
		}
		from->parent = nullptr;
	}

	void subtree_change_height(Node* from, int dh = 1) {
		if (left == from) {
			balance -= dh;
		} else {
			assert(right == from);
			balance += dh;
		}
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
	Node* tree = new Node(rd.k);

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
	// малый левый
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

	// updating balances
	if (b->balance == 1) {
		b->balance = 0;
		a->balance = 0;
	} else if (b->balance == 0) {
		a->balance = 1;
		b->balance = -1;
	} else if (b->balance == 2) {
		// rl rotation
		a->balance = -1;
		b->balance = 0;
	} else if (b->balance == -1) {
		// lr rotation
		a->balance = 0;
		b->balance = -2;
	} else {
		assert(false);
	}
}

void rotate_r(Node*& tree) {
	// малый правый
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

	// updating balances
	if (b->balance == -1) {
		b->balance = 0;
		a->balance = 0;
	} else if (b->balance == 0) {
		a->balance = -1;
		b->balance = 1;
	} else if (b->balance == 1) {
		// rl rotation
		b->balance = 2;
		a->balance = 0;
	} else if (b->balance == -2) {
		// lr rotation
		b->balance = 0;
		a->balance = 1;
	} else {
		assert(false);
	}
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

bool balance_tree(Node*& tree, bool balancing_done, int dh = 1) {
	if (tree->balance == 2) {
		if (tree->right->balance == -1) {
			rotate_rl(tree);
		} else {
			rotate_l(tree);
		}
	} else if (tree->balance == -2) {
		if (tree->left->balance == 1) {
			rotate_lr(tree);
		} else {
			rotate_r(tree);
		}
	}

	// recalculate balances due to height change
	// if node has a parent and subtree's height was increased (balance != 0)
	if (tree->parent && (tree->balance != 0 || (!tree->left && !tree->right)) && !balancing_done) {
		tree->parent->subtree_change_height(tree, dh);
		return false;
	}
	return true;
}

bool insert_to_tree(Node*& tree, Node* node) {
	if (tree == nullptr) {
		tree = node;
		return true;
	}

	bool balancing_done = false;
	// digging into the tree to find a right place for a node
	if (node->key == tree->key) {
		assert(false && "key already in tree");
	} else if (node->key < tree->key) {
		if (tree->left) {
			balancing_done = insert_to_tree(tree->left, node);
		} else {
			tree->left = node;
			node->parent = tree;
			tree->balance--;
		}
	} else {
		if (tree->right) {
			balancing_done = insert_to_tree(tree->right, node);
		} else {
			tree->right = node;
			node->parent = tree;
			tree->balance++;
		}
	}

	// balancing on our way back if needed
	return balance_tree(tree, balancing_done);
}

void delete_node_simple(Node*& tree) {
	if (tree->left == nullptr && tree->right == nullptr) {
		if (tree->parent) {
			tree->parent->subtree_change_height(tree, -1);
			// tree->parent->replace_child(tree, nullptr);
		}
		delete tree;
		tree = nullptr;
	} else if (tree->left == nullptr || tree->right == nullptr) {
		Node* saved = (tree->right) ? tree->right : tree->left;
		if (tree->parent) {
			tree->parent->subtree_change_height(tree, -1);
			// tree->parent->replace_child(tree, saved);
		}
		saved->parent = tree->parent;
		delete tree;
		tree = saved;
	} else {
		assert(false && "not a simple node to delete!");
	}
}


bool delete_from_tree(Node*& tree, int key, Node* target = nullptr) {
	if (!tree->parent && !tree->left && !tree->right) {
		if (key == tree->key) {
			delete_node_simple(tree);
			return false;
		} else {
			assert(false && "key not in a tree!");
		}
	}

	bool balancing_done = false;
	if (!target) {
		// digging into the tree 
		if (key == tree->key) {
			if (!tree->left && !tree->right) {
				delete_node_simple(tree);
				return false;
			} else if (!tree->left) {
				delete_node_simple(tree);
				return false;
			} else {
				balancing_done = delete_from_tree(tree->left, key, tree);
			}
		} else if (key < tree->key) {
			balancing_done = delete_from_tree(tree->left, key);
		} else {
			assert(key > tree->key);
			balancing_done = delete_from_tree(tree->right, key);
		}
	} else {
		if (tree->right) {
			balancing_done = delete_from_tree(tree->right, key, target);
		} else {
			// found prev
			target->key = tree->key;
			delete_node_simple(tree);
			return false;
		}
	}
	
	// balancing on our way back if needed
	return balance_tree(tree, balancing_done, -1);
}

void ddelete_from_tree(Node*& tree, int key) {
	assert(tree != nullptr);
	if (tree->left == nullptr && tree->right == nullptr) {
		if (tree->key == key) {
			delete_node_simple(tree);
			return;
		} else {
			assert(false && "key not in a tree!");
		}
	}
	
	Node* current_node = tree;
	bool skip_bubbling = false;
	while (current_node) {
		// digging into the tree
		if (current_node->key == key) {
			// deleting this node
			if (current_node->left == nullptr) {
				Node* deleted = current_node;
				if (!current_node->parent) {
					tree = current_node->right;
				} else {
					current_node = current_node->parent;
					skip_bubbling = true;
				}
				delete_node_simple(deleted);
				if (!skip_bubbling) {
					current_node = deleted;
				}
				break;
			} else {
				Node* prev = current_node->left;
				while (prev->right) prev = prev->right;
				current_node->key = prev->key;

				// jumping to prev's parent
				current_node = prev->parent;
				if (current_node->balance != 0) {
					skip_bubbling = true;
				}
				delete_node_simple(prev);
				break;
			}
		} else if (key < current_node->key) {
			if (current_node->left) {
				current_node = current_node->left;
			} else {
				assert(false && "key not in a tree!");
			}
		} else {
			assert(key > current_node->key);
			if (current_node->right) {
				current_node = current_node->right;
			} else {
				assert(false && "key not in a tree!");
			}
		}
	}

	while (current_node && (skip_bubbling || (current_node = current_node->parent))) {
		skip_bubbling = false;
		Node* old_current_node = current_node;

		if (balance_tree(current_node, false, -1)) {
			if (!current_node->parent) {
				tree = current_node;
			}
			return;
		}
	}
}

int main() {
	int n;
	io >> n;

	TreeDescription input(n);
	for (auto& descr : input.descriptions) {
		io >> descr.k >> descr.li >> descr.ri;
	}

	Node* tree = nullptr;
	if (n) {
		tree = build_tree(input);
	}

	int k;
	io >> k;
	delete_from_tree(tree, k);

	if (!tree) {
		io << "0";
		return 0;
	}

	TreeDescription output;
	output.populate_from_tree(tree);

	io << output.descriptions.size() << "\n";
	for (auto& descr : output.descriptions) {
		io << descr.k << " " << descr.li << " " << descr.ri << "\n";
	}

	return 0;
}
