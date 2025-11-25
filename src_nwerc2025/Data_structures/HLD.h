//@ Author: Benjamin Qi, Andrew Cheng, Jack Lim
//@ Date: ??
//@ License: CC0
//@ Source: USACO-guide
//@ Status: not tested

//# Title:
//#   Heavy Light Decomposition
//# Description:
//#   Splits tree up in heavy and light paths, so a maximum of \log N
//#   light paths are on path between two nodes, allows for efficient 
//#   updates and queries on paths and subtrees at the same time.
//# Usage:
//#   Change MaxSegmentTree<T> depending on problem
//#   HLD<T, VALS_IN_EDGES> hld(G); // T should be nodes used in segtree VALS_IN_EDGES should be true if the values are on the edge from the node to the parent
//#   G should be an adjacency list for the tree
//#   change query_path / modify_node to match the problem
//# Complexity: \mathcal{O}(N + S) build time. N is the size of the tree and S is the time to build the Segtree, and \mathcal{O}(\log N \cdot F) per path query where F is the time of the segtree queries.

template <class T, bool VALS_IN_EDGES> class HLD {
  private:
	int N, R, tim = 0;  // n, root node, time
	vector<vector<int>> adj;
	vector<int> par, siz, depth, rt, pos;  // parent, size, depth, root, position arrays
	MaxSegmentTree<T> segtree;             // Modify as needed

	/** Compute the size of each subtree and set parent-child relationship
	 * Subtree of node v corresponds to segment [ pos[v], pos[v] + sz[v] ) */
	void dfs_sz(int v) {
		if (par[v] != -1) adj[v].erase(find(adj[v].begin(), adj[v].end(), par[v]));
		for (int &u : adj[v]) {
			par[u] = v, depth[u] = depth[v] + 1;
			dfs_sz(u);
			siz[v] += siz[u];
			if (siz[u] > siz[adj[v][0]]) swap(u, adj[v][0]);
		}
	}

	/** Assign positions for nodes
	  * Path from v to the last vertex in ascending heavy path
	    corresponds to [ pos[rt[v]], pos[v] ] */
	void dfs_hld(int v) {
		pos[v] = tim++;
		for (int u : adj[v]) {
			rt[u] = (u == adj[v][0] ? rt[v] : u);
			dfs_hld(u);
		}
	}

	/** process all heavy path and combine their results */
	template <class B> void process(int u, int v, B op) {
		for (; rt[u] != rt[v]; v = par[rt[v]]) {
			if (depth[rt[u]] > depth[rt[v]]) swap(u, v);
			op(pos[rt[v]], pos[v]);
		}
		if (depth[u] > depth[v]) swap(u, v);
		op(pos[u] + VALS_IN_EDGES, pos[v]);
	}
  public:
	HLD(vector<vector<int>> adj_, int _R)
	    : N(adj_.size()), R(_R), adj(adj_), par(N, -1), siz(N, 1), depth(N), rt(N),
	      pos(N), segtree(N)  // modify as needed
	{
		rt[R] = R;
		dfs_sz(R);
		dfs_hld(R);
	}
	T query_path(int u, int v) {
		T res = 0;  // default value, modify depending on problem
		process(u, v, [&](int l, int r) {
			res = max(res, segtree.range_max(l, r + 1));  // modify depending on problem
		});
		return res;
	}
	void modify_node(int u, T val) { segtree.set(pos[u], val); }
};
