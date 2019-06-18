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
	Node* l;
	Node* r;

	static Node* createFromDescription(NodeDescription &descr) {
		auto n = new Node();
		n->k = descr.k;
		n->l = descr.ln ? createFromDescription(descriptions[descr.ln - 1]) : nullptr;
		n->r = descr.rn ? createFromDescription(descriptions[descr.rn - 1]) : nullptr;
		return n;
	}
};

int find_depth(Node* tree) {
	if (tree == nullptr) {
		return 0;
	}

	return max(find_depth(tree->l), find_depth(tree->r)) + 1;
}

int main() {
	int n;
	io >> n;

	if (n == 0) {
		io << 0;
		return 0;
	}

	descriptions = vector<NodeDescription>(n);
	for (auto &e : descriptions) {
		e = NodeDescription();
		io >> e.k >> e.ln >> e.rn;
	}
	
	Node* tree = Node::createFromDescription(descriptions[0]);

	io << find_depth(tree);

	return 0;
}
