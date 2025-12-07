//# Title: Articulation points finding
//# Description: Yoinked from CP-algorithms. Standard articulation points finding algorithm.
//# Complexity: $\mathcal{O}(V + E)$.

//@ tested on:
//@  1. https://www.spoj.com/problems/SUBMERGE/

int n; // number of nodes
vector<vector<int>> adj; // adjacency list of graph

vector<bool> vis;
vector<int> tin, low;
int timer;

void proc_artpoint(int v) {
	// Process articulation point here
	// Can be run multiple times per vertex
}

void dfs(int v, int p = -1) {
	vis[v] = true;
	tin[v] = low[v] = timer++;
	int children = 0;
	for (int to : adj[v]) {
		if (to == p) continue;
		if (vis[to]) {
			low[v] = min(low[v], tin[to]);
		} else {
			dfs(to, v);
			low[v] = min(low[v], low[to]);
			if (low[to] >= tin[v] && p != -1) proc_artpoint(v);
			++children;
		}
	}
	if (p == -1 && children > 1) proc_artpoint(v);
}

void find_artpoints() {
	timer = 0;
	vis.assign(n, false);
	tin.assign(n, -1);
	low.assign(n, -1);
	for (int i = 0; i < n; ++i) {
		if (!vis[i]) dfs(i);
	}
}
