//# Title: Centroid decomposition
//# Description: Computes a centroid decomposition and invokes the given callback in top-down depth-first order. Takes an adjacency list. See comment in case of disconnected graphs.
//@ Usage: \texttt{centroid_decomposition(adj, [] (int centroid) { ... }, optional_root);}
//# Complexity: $\mathcal{O}(n \log n)$ and exactly one callback invocation per vertex

#pragma once

void centroid_decomposition(const std::vector <std::vector <int>>& g, std::function <void (int)>& callback, int root = 0) {
	const int n = g.size();
	std::vector <bool> vis(n, false);
	std::vector <int> sub(n);
	auto size = [&] (auto&& self, int v, int p = -1) -> int {
		sub[v] = 1;
		for (int x : g[v]) if (!vis[x] && x != p) sub[v] += self(self, x, v);
		return sub[v];
	};
	auto cen = [&] (auto&& self, int ts, int v, int p = -1) -> int {
		for (int x : g[v])
			if (!vis[x] && x != p && sub[x] >= ts)
				return self(self, ts, x, v);
		return v;
	};
	auto dfs = [&] (auto&& self, int v) -> void {
		int c = cen(cen, size(size, v) >> 1, v);
		callback(c);
		vis[c] = true;
		for (int x : g[c]) if (!vis[x]) self(self, x);
	};
	dfs(dfs, root);
	// if g is disconnected, do this instead
	// for (int v = 0; v < n; v++) if (!vis[v]) dfs(dfs, v);
}
