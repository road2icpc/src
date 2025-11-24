//# Title: Articulation points and Bridges
//# Description: Finds articulation point and bridges in an undirected graph
//# Usage:
//#  cutpoints(G) \\ G should be an undirected unweighted adjacencylist.
//#  art[i] is 1 if node i is an articulation point
//#  brd contains a list of edges that are bridges (The edges are not necessarily given with the correct orientation)
//# Complexity: $\mathcal{O}(N+E)$, where N is the number of nodes, and E is the number of edges.

//@ tested on:
//@	 https://cses.fi/problemset/task/2077
//@  https://cses.fi/problemset/task/2076

#pragma once

vector<int> lw, nm, pa, art;
vector<pair<int, int>> brd;
int tt, ch, rt;

void f(int u, const vector<vector<int>> &G) {
	lw[u] = nm[u] = tt++;
	for(int v : G[u]) {
		if(!nm[v]) {
			ch += (pa[v] = u) == rt;
			f(v, G);
			art[u] = lw[v] >= nm[u];
			if(lw[v] > nm[u]) brd.emplace_back(u, v);
			lw[u] = min(lw[u], lw[v]);
		}
		else if(v != pa[u]) lw[u] = min(lw[u], nm[v]);
	}
}

void cutpoints(const vector<vector<int>> &G) {
	int n = G.size();
	art.assign(n, 0);
	lw.assign(n, 0);
	nm.assign(n, 0);
	pa.assign(n, -1);
	brd.clear();
	tt = 1;
	for(int i = 0; i < n; ++i) 
		if(!nm[i]) {
			rt = i, ch = 0;
			f(i, G);
			art[rt] = ch > 1;
		}
}
