//# Title: Biconnected Components
//# Description: Finds all biconnected components in an undirected graph, and
//#  construct the block-cut tree of the graph. In a block-cut tree each node
//#  correspond to a biconnected component or an articualtion point. Checking
//#  if there is a path from u to v not going through w in the graph then 
//#  correspond to checking if there exists a path from id[u] to id[v] in the
//#  block-cut tree not going through id[w].
//# Usage:
//#  G should be an adjacenylist with edges both ways
//#  vector<bool> art;
//#  vector<int> id;
//#  auto T = bcomps(G, art, id)
//#  then T is the block-cut tree.
//# Complexity: $\mathcal{O}(E + V)$

#pragma once

vector<vector<int>> bcomps(vector<vector<int>> &G, vector<bool> &art, vector<int> &id) {
	int n = G.size();
	vector<vector<int>> cmps, t;
	vector<int> s, nm(n, 0), lw(n, 0);
	art.resize(n);
	id.resize(n);
	int tt = 0;
	auto f = [&](auto &&self, int u, int p) -> void {
		lw[u] = nm[u] = ++tt;
		s.push_back(u);
		for(int v : G[u]) {
			if(v == p) continue;
			if(nm[v]) lw[u] = min(lw[u], nm[v]);
			else {
				self(self, v, u);
				lw[u] = min(lw[u], lw[v]);
				if(lw[v] >= nm[u]) {
					art[u] = (nm[u] > 1 || nm[v] > 2);
					cmps.push_back({u});
					while(cmps.back().back() != v) {
						cmps.back().push_back(s.back());
						s.pop_back();
					}
				}
			}
		}
	};
	for(int i = 0; i < n; ++i) if(!nm[i]) {
		tt = 0;
		f(f, i, -1);
	}
	int ni = 0;
	for(int i = 0; i < n; ++i) if(art[i]) {
		id[i] = ni++;
		t.push_back({});
	}
	for(auto &c : cmps) {
		int u = ni++;
		t.push_back({});
		for(int v : c) {
			if(!art[v]) id[v] = u;
			else {
				t[u].push_back(id[v]);
				t[id[v]].push_back(u);
			}
		}
	}
	return t;
}
