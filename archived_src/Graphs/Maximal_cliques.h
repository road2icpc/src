//# Title: Maximum clique callbacks
//# Description: Yoinked from kactl. Runs a callback for all maximal cliques in a graph (given as a symmetric bitset matrix; self-edges not allowed). Callback is given a bitset representing the maximal clique.
//# Usage: \texttt{cliques(eds, callback, ...);}
//# Complexity: $\mathcal{O}(3^{n/3})$ - \textit{much} faster for sparse graphs.

typedef bitset<128> B;
template<class F>
void cliques(vector<B>& eds, F f, B P = ~B(), B X={}, B R={}) {
	if (!P.any()) { if (!X.any()) f(R); return; }
	auto q = (P | X)._Find_first();
	auto cands = P & ~eds[q];
	rep(i,0,sz(eds)) if (cands[i]) {
		R[i] = 1;
		cliques(eds, f, P & eds[i], X & eds[i], R);
		R[i] = P[i] = 0; X[i] = 1;
	}
}
