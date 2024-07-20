//# Title: Persistent segment tree
//# Description: Zero-indexed, bounds are [l, r), operations can be modified. \texttt{update(...)} returns a pointer to a new tree with the applied update, all other trees remain unchanged. $\mathcal{O}(\log n)$ find\_first and the like can be implemented by checking bounds, then checking left tree, then right tree, recursively.
//# Usage: \texttt{Node* root = build(arr, 0, n); Node* another\_root = update(root, ind, val, 0, n); query(some\_root, l, r, 0, n).val; Node* empty\_root = nullptr; Node* another\_version = update(empty\_root, ind, val, 0, n);}
//# Complexity: $\mathcal{O}(\log n)$ per update/query, $\mathcal{O}(n)$ per build

//@ tested on:
//@  1. https://cses.fi/problemset/task/1737/

struct Node {
	Node* l,* r;
	int val; // i.e. data
	Node(int _v) : l(nullptr), r(nullptr), val(_v) { }
	Node(Node* _l, Node* _r) : l(_l), r(_r), val(0) {
		// i.e. merge two nodes:
		if (l) val += l->val;
		if (r) val += r->val;
	}
};

// slightly more memory, much faster:
template <typename... ARGS> Node* new_node(ARGS&&... args) {
	static deque <Node> pool;
	pool.emplace_back(forward <ARGS> (args)...);
	return &pool.back();
}
// slightly less memory, much slower:
// #define new_node(...) new Node(__VA_ARGS__)

// optional:
Node* build(const vector <int>& a, int l, int r) {
	if (!(r - l - 1)) return new_node(a[l]);
	int mid = (l + r) >> 1;
	return new_node(build(a, l, mid), build(a, mid, r));
}

// can be called with node == nullptr
Node* update(Node* node, int ind, int val, int l, int r) {
	if (!(r - l - 1)) return new_node(val); // i.e. point update
	int mid = (l + r) >> 1;
	Node* lf = node ? node->l : nullptr;
	Node* rg = node ? node->r : nullptr;
	return new_node
		(ind < mid ? update(lf, ind, val, l, mid) : lf,
		ind >= mid ? update(rg, ind, val, mid, r) : rg);
}

Node query(Node* node, int tl, int tr, int l, int r) {
	if (l >= tr || r <= tl || !node) return Node(0); // i.e. empty node
	if (l >= tl && r <= tr) return *node;
	int mid = (l + r) >> 1;
	Node lf = query(node->l, tl, tr, l, mid);
	Node rg = query(node->r, tl, tr, mid, r);
	return Node(&lf, &rg);
}
