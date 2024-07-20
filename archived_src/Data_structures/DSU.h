//# Title: Disjoint Set Union
//# Description: Classic DSU using path compression and union by rank. \texttt{unite} returns true iff \texttt{u} and \texttt{v} were disjoint.
//# Usage: \texttt{Dsu d(n); d.unite(a, b); d.find(a);}
//# Complexity: \texttt{find()}, \texttt{unite()} are amortized $\mathcal{O}(\alpha(n))$, where $\alpha(n)$ is the inverse Ackermann function. Basically $\mathcal{O}(1)$.

//@ tested on:
//@ - trust me bro

struct Dsu {
	vector <int> p, rank;
	Dsu(int n) {
		p.resize(n); rank.resize(n, 0);
		iota(p.begin(), p.end(), 0);
	}
	int find(int x) {
		return p[x] == x ? x : p[x] = find(p[x]);
	}
	bool unite(int u, int v) {
		if ((u = find(u)) == (v = find(v))) return false;
		if (rank[u] < rank[v]) swap(u, v);
		p[v] = u;
		rank[u] += rank[u] == rank[v];
		return true;
	}
};
