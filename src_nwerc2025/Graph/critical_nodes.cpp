//# Title: Critical nodes
//# Description: Finds necessary nodes in a directed graph between two cities u, v. That is nodes that appears on every path between u and v
//# Usage:
//#  critical(G) \\ G should be an directed unweighted adjacencylist.
//#  returns a list with the indices of the critical nodes.
//#  Returns an empty list if u and v are not in the same component.
//#  Additionally pt will contain a path from u to v.
//# Complexity: $\mathcal{O}(N+E)$, where N is the number of nodes, and E is the number of edges.

//@ tested on:
//@  https://cses.fi/problemset/task/1703/
#pragma once

vector<int> pt, nx, s1, s2;

int f1(int u, int tg, const vector<vector<int>> &G, int d = 0) {
	if(s1[u]) return 0;
	pt.push_back(u);
	nx[u] = d;
	s1[u] = 1;
	if(u == tg) return 1;
	for (int v : G[u]) if(f1(v, tg, G, d + 1)) return 1;
	pt.pop_back();
	return nx[u] = 0;
}

int f2(int u, const vector<vector<int>> &G) {
	int a = 0;
	if(s2[u]) return 0;
	s2[u] = 1;
	for(int v : G[u]) a = max(a, nx[v] ? nx[v] : f2(v, G));
	return a;
}

vector<int> critical(const vector<vector<int>> &G, int u, int v) {
	int n = G.size();
	nx.assign(n, 0);
	s1.assign(n, 0);
	s2.assign(n, 0);
	f1(u, v, G);
	vector<int> art;
	for(int i = 0, j = 0; i < (int)pt.size(); j = max(j, f2(pt[i++], G))) 
		if(i == j) art.push_back(pt[i]);
	return art;
}
