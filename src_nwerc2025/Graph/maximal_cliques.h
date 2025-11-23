//@ Author: Simon Lindholm
//@ Date: 2018-07-18
//@ License: CC0
//@ Source: https://en.wikipedia.org/wiki/Bron%E2%80%93Kerbosch_algorithm
//@ Status: stress-tested

//# Title: Maximal Cliques
//# Description: [kactl] Runs a callback for all maximal cliques in a graph (given as a
//#  symmetric bitset matrix; self-edges not allowed). Callback is given a bitset
//#  representing the maximal clique.
//# Complexity: $\mathcal{O}(3^{n/3})$, much faster for sparse graphs

#pragma once
/// Possible optimization: on the top-most
/// recursion level, ignore 'cands', and go through nodes in order of increasing
/// degree, where degrees go down as nodes are removed.
/// (mostly irrelevant given MaximumClique)

typedef bitset<128> B;
template<class F>
void cliques(vector<B>& eds, F f, B P = ~B(), B X={}, B R={}) {
	if (!P.any()) { if (!X.any()) f(R); return; }
	auto q = (P | X)._Find_first();
	auto cands = P & ~eds[q];
	for (int i = 0; i < (int)eds.size()) if (cands[i]) {
		R[i] = 1;
		cliques(eds, f, P & eds[i], X & eds[i], R);
		R[i] = P[i] = 0; X[i] = 1;
	}
}
