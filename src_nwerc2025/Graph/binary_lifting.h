//@ Author: Johan Sannemo
//@ Date: 2015-02-06
//@ License: CC0
//@ Source: Folklore
//@ Status: Tested at Petrozavodsk, also stress-tested via LCA.cpp

//# Title: Binary Lifting
//# Description: [kactl] Calculate power of two jumps in a tree.
//#  Assumes root node points to itself
//# Usage:
//#  treeJump(parent list); // To get jump table
//#  jmp(jump table, v, k); // Get k'th ancestor of v
//#  lca(jumpt table, depth list, a, b); // Get lowest common ancestor of a and b
//# Complexity: construction $O(N \log N)$, queries $O(\log N)$

#pragma once

vector<vector<int>> treeJump(vector<int>& P){
	int on = 1, d = 1;
	while(on < (int)P.size()) on *= 2, d++;
	vector<vector<int>> jmp(d, P);
	for (int i = 1; i < d; i++)
		for (int j = 0; j < (int)P.size(); j++)
			jmp[i][j] = jmp[i-1][jmp[i-1][j]];
	return jmp;
}

int jmp(vector<vector<int>>& tbl, int nod, int steps){
	for (int i = 0; i < (int)tbl.size(); i++)
		if(steps&(1<<i)) nod = tbl[i][nod];
	return nod;
}

int lca(vector<vector<int>>& tbl, vector<int>& depth, int a, int b) {
	if (depth[a] < depth[b]) swap(a, b);
	a = jmp(tbl, a, depth[a] - depth[b]);
	if (a == b) return a;
	for (int i = tbl.size() - 1; ~i; i--) {
		int c = tbl[i][a], d = tbl[i][b];
		if (c != d) a = c, b = d;
	}
	return tbl[0][a];
}
