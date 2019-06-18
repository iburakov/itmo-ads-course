#include "edx-io.hpp"
#include <vector>
#include <algorithm>

using namespace std;

struct NodeDescription {
	int k;
	int ln;
	int rn;
};

vector<NodeDescription> descriptions;

struct Node {
	int k;
	Node* parent;
	Node* l = nullptr;
	Node* r = nullptr;
	
	int getSize() {
		return (size == -1) ? recalculateSize() : size;
	}

	int recalculateSize() {
		int lsize = l ? l->getSize() : 0;
		int rsize = r ? r->getSize() : 0;

		size = lsize + rsize + 1;
		return size;
	}

	static Node* createFromDescription(NodeDescription &descr) {
		auto n = new Node();
		n->k = descr.k;

		if (descr.ln) {
			n->l = createFromDescription(descriptions[descr.ln - 1]);
			n->l->parent = n;
		}

		if (descr.rn) {
			n->r = createFromDescription(descriptions[descr.rn - 1]);
			n->r->parent = n;
		}

		return n;
	}

private:
	int size = -1;
};

void dropNode(Node* tree, int key) {
	if (key < tree->k) {
		if (tree->l) dropNode(tree->l, key);
	} else if (key > tree->k) {
		if (tree->r) dropNode(tree->r, key);
	} else {
		// screw memory management! nogc!
		if (tree->parent->l == tree) {
			tree->parent->l = nullptr;
		} else {
			tree->parent->r = nullptr;
		}

		// but efficient size calculation management is important
		do {
			tree = tree->parent;
			tree->recalculateSize();
		} while (tree->parent);
	}
}

int main() {
	int n;
	io >> n;

	descriptions = vector<NodeDescription>(n);
	for (auto &e : descriptions) {
		e = NodeDescription();
		io >> e.k >> e.ln >> e.rn;
	}
	
	Node* tree = Node::createFromDescription(descriptions[0]);

	int kn;
	io >> kn;
	for (int i = 0; i < kn; i++) {
		int key;
		io >> key;
		dropNode(tree, key);
		io << tree->getSize() << "\n";
	}
	
	return 0;
}
