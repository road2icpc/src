//# Title: Persistent segment tree
//# Description: Zero-indexed, bounds are [l, r), operations can be modified. $\mathcal{O}(\log n)$ find\_first and the like can be implemented by checking bounds, then checking left tree, then right tree, recursively.
//# Usage: \texttt{Node* root = build(arr, 0, n); Node* another_root = update(root, ind, val, 0, 0, n); query(some_root, l, r, 0, n).val; Node* empty_root = nullptr; Node* another_version = update(empty_root, ind, val, 0, 0, n);}
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
	static std::deque <Node> pool;
	pool.emplace_back(std::forward <ARGS> (args)...);
	return &pool.back();
}
// slightly less memory, much slower:
// #define new_node(...) new Node(__VA_ARGS__)

// optional:
Node* build(const std::vector <int>& a, int l, int r) {
	if (!(r - l - 1)) return new_node(a[l]);
	int mid = (l + r) >> 1;
	return new_node(build(a, l, mid), build(a, mid, r));
}

// can be called with node == nullptr
Node* update(Node* node, int ind, int val, int now, int l, int r) {
	if (!(r - l - 1)) return new_node(val); // i.e. point update
	int mid = (l + r) >> 1;
	Node* lf = node ? node->l : nullptr;
	Node* rg = node ? node->r : nullptr;
	return new_node
		(ind < mid ? update(lf, ind, val, now, l, mid) : lf,
		ind >= mid ? update(rg, ind, val, now, mid, r) : rg);
}

Node query(Node* node, int tl, int tr, int l, int r) {
	if (l >= tr || r <= tl || !node) return Node(0); // i.e. empty node
	if (l >= tl && r <= tr) return *node;
	int mid = (l + r) >> 1;
	Node lf = query(node->l, tl, tr, l, mid);
	Node rg = query(node->r, tl, tr, mid, r);
	return Node(&lf, &rg);
}
