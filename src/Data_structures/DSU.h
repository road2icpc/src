//# Title: Disjoint Set Union
//# Description: Classic \texttt{DSU} using path compression and union by rank. \texttt{unite} returns true iff $u$ and $v$ were disjoint.
//# Usage: \texttt{Dsu d(n); d.unite(u, v); d.find(u);}
//# Complexity: \texttt{find()}, \texttt{unite()} are amortized $\mathcal{O}(\alpha(n))$, where $\alpha(n)$ is the inverse Ackermann function.

//@ tested on:
//@  1. https://judge.yosupo.jp/problem/unionfind

struct Dsu {
	vi p, rank;
	Dsu(int n) : p(n), rank(n, 0) {
		iota(all(p), 0);
	}
	int find(int x) {
		return p[x] == x ? x : p[x] = find(p[x]);
	}
	bool unite(int u, int v) {
		if ((u = find(u)) == (v = find(v))) return false;
		if (rank[u] < rank[v]) swap(u, v);
		rank[u] += rank[p[v] = u] == rank[v];
		return true;
	}
};
