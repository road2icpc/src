//# Title: Fenwick tree
//# Description: Computes prefix sums and single element updates. Uses 0-indexing.
//# Usage: \texttt{...}
//# Complexity: $\mathcal{O}(\log n)$ per update/query

//@ tested on:
//@  1. ???

struct Fen {
	vector <ll> v;
	Fen(int s) : v(s, 0) { }
	void update(int ind, ll val) {
		for (; ind < (int) v.size(); ind |= ind + 1) v[ind] += val;
	}
	ll query(int ind) { // [0, ind), ind < 0 returns 0
		ll res = 0;
		for (; ind > 0; ind &= ind - 1) res += v[ind - 1]; // operation can be modified
		return res;
	}
	int lower_bound(ll sum) { // returns first i with query(i + 1) >= sum, n if not found
		int ind = 0;
		for (int p = 1 << 25; p; p >>= 1) // 1 << 25 can be lowered to ceil(log2(v.size()))
			if (ind + p <= (int) v.size() && v[ind + p - 1] < sum)
				sum -= v[(ind += p) - 1];
		return ind;
	}
};
