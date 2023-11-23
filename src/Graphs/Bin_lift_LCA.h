//# Title: Binary lifting with LCA
//# Description: Yoinked from kactl. Finds power of two jumps in a tree - and standard LCA. Assumes the root node points to itself!
//# Usage: \texttt{vector<vi> jmps = treeJump(parents); int l = lca(jmps, depth, a, b);}
//# Complexity: $\mathcal{O}(N \log N)$ construction. $\mathcal{O}(\log N)$ per query.

vector<vi> treeJump(vi& P){
	int on = 1, d = 1;
	while(on < sz(P)) on *= 2, d++;
	vector<vi> jmp(d, P);
	rep(i,1,d) rep(j,0,sz(P))
		jmp[i][j] = jmp[i-1][jmp[i-1][j]];
	return jmp;
}

int jmp(vector<vi>& tbl, int nod, int steps){
	rep(i,0,sz(tbl))
		if(steps&(1<<i)) nod = tbl[i][nod];
	return nod;
}

int lca(vector<vi>& tbl, vi& depth, int a, int b) {
	if (depth[a] < depth[b]) swap(a, b);
	a = jmp(tbl, a, depth[a] - depth[b]);
	if (a == b) return a;
	for (int i = sz(tbl); i--;) {
		int c = tbl[i][a], d = tbl[i][b];
		if (c != d) a = c, b = d;
	}
	return tbl[0][a];
}
