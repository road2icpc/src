//# Title: Segment tree
//# Description: Zero-indexed, bounds are [l, r), operations can be modified. $\mathcal{O}(\log n)$ find\_first and the like can be implemented by checking bounds, then checking left tree, then right tree, recursively.
//# Usage: \texttt{Segtree seg(n); seg.update(ind, val); seg.query(l, r);}
//# Complexity: $\mathcal{O}(\log n)$ per update/query.

//@ tested on:
//@  1. https://cses.fi/problemset/task/1648/
//@  2. https://cses.fi/problemset/task/1649/

struct Segtree {
	typedef ll T; // change type here
	static constexpr T unit = 0; // change unit here
	T f(T l, T r) { return l + r; } // change operation here
	int size;
	vector <T> v;
	Segtree(int s = 0) : size(s ? 1 << (32 - __builtin_clz(s)) : 0), v(size << 1, unit) { }
	void update(int ind, T val) { update(ind, val, 0, 0, size); }
	T query(int l, int r) { return query(l, r, 0, 0, size); }
	void update(int ind, T val, int now, int l, int r) {
		if (!(r - l - 1)) { v[now] = val; return; } // operation can be modified
		int mid = (l + r) >> 1;
		if (ind < mid) update(ind, val, now * 2 + 1, l, mid);
		else update(ind, val, now * 2 + 2, mid, r);
		v[now] = f(v[now * 2 + 1], v[now * 2 + 2]);
	}
	T query(int tl, int tr, int now, int l, int r) {
		if (l >= tr || r <= tl) return unit;
		if (l >= tl && r <= tr) return v[now];
		int mid = (l + r) >> 1;
		return f(query(tl, tr, now * 2 + 1, l, mid), query(tl, tr, now * 2 + 2, mid, r));
	}
	template <typename U> void build(const vector <U>& a) {
		for (int i = 0; i < (int) a.size(); i++) v[size - 1 + i] = a[i]; // operation can be modified
		for (int i = size - 2; i >= 0; i--) v[i] = f(v[i * 2 + 1], v[i * 2 + 2]);
	}
};
