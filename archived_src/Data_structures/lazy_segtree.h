//# Title: Lazy segment tree
//# Description: Zero-indexed, bounds are [l, r), operations can be modified. $\mathcal{O}(\log n)$ find\_first and the like can be implemented by checking bounds, then checking left tree, then right tree, recursively.
//# Usage: \texttt{Lazy\_segtree seg(n); seg.update(l, r, val); seg.query(l, r);}
//# Complexity: $\mathcal{O}(\log n)$ per update/query

//@ tested on:
//@  1. https://cses.fi/problemset/task/1735/

struct Lazy_segtree {
	typedef ll T; // change type here
	typedef ll LAZY_T; // change type here
	static constexpr T unit = 0; // change unit here
	static constexpr LAZY_T lazy_unit = 0; // change lazy unit here
	T f(T l, T r) { return l + r; } // change operation here
	void push(int now, int l, int r) {
		if (w[now] == lazy_unit) return;
		v[now] += w[now] * (r - l); // operation can be modified
		if (r - l - 1)
			w[now * 2 + 1].first += w[now],
			w[now * 2 + 2].first += w[now];
		w[now] = lazy_unit;
	}
	int size;
	vector <T> v;
	vector <LAZY_T> w;
	Lazy_segtree(int s = 0) : size(s ? 1 << (32 - __builtin_clz(s)) : 0), v(size << 1, unit), w(size << 1, lazy_unit) { }
	template <typename U> void update(int l, int r, U val) { update(l, r, val, 0, 0, size); }
	T query(int l, int r) { return query(l, r, 0, 0, size); }
	template <typename U> void update(int tl, int tr, U val, int now, int l, int r) {
		push(now, l, r);
		if (l >= tr || r <= tl) return;
		if (l >= tl && r <= tr) {
			// this does not *have* to accumulate, push is called before this:
			w[now] += val; // operation can be modified
			push(now, l, r);
			return;
		}
		int mid = (l + r) >> 1;
		update(tl, tr, val, now * 2 + 1, l, mid);
		update(tl, tr, val, now * 2 + 2, mid, r);
		v[now] = f(v[now * 2 + 1], v[now * 2 + 2]);
	}
	T query(int tl, int tr, int now, int l, int r) {
		push(now, l, r);
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
