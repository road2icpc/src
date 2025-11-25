//# Title: Critical nodes on minimal path
//# Description: Finds minimal-route necessary nodes in a directed weighted graph between two cities u, v. That is nodes that appears on every minimum-length path between u and v
//# Usage:
//#  \texttt{critical(G)} \\ G should be an directed unweighted adjacencylist.
//#  returns a list with the indices of the critical nodes.
//#  Returns an empty list if u and v are not in the same component.
//# Complexity: $\mathcal{O}(N+E)$, where $N$ is the number of nodes, and $E$ is the number of edges.

//@ tested on:
//@  https://cses.fi/problemset/task/1203/

#pragma once

vector<int> critical_minimal(const vector<vector<pair<int, int>>> &G, int u, int v) {
	int n = G.size();
	priority_queue<array<ll, 3>> pq;
	queue<int> q;
	vector<ll> di(n, -1);
	vector<int> dg(n, 0), art;
	set<int> am;
	vector<vector<int>> ig(n);
	pq.push({0, u, u});
	while(pq.size()){
		auto [d, x, p] = pq.top();
		pq.pop();
		if(~di[x]){
			if(-d == di[x]) ig[x].push_back(p);
			continue;
		}
		di[x] = -d;
		if(x != p) ig[x].push_back(p);
		for(auto y : G[x]) pq.push({d - y.second, y.first, x});
	}
	if(!~di[v]) return {};
	for(int i = 0; i < n; ++i) for(auto x : ig[i]) dg[x]++;
	for(int i = 0; i < n; ++i) if(!dg[i]) q.push(i);
	while(q.size()) {
		auto x = q.front();
		q.pop();
		if(x == v) continue;
		for(auto y : ig[x]) if(!--dg[y]) q.push(y);
	}
	q.push(v);
	while(q.size()) {
		auto x = q.front();
		q.pop();
		am.erase(x);
		if(!am.size()) art.push_back(x);
		for(auto y : ig[x]) {
			am.insert(y);
			if(!--dg[y]) q.push(y);
		}
	}
	return art;
}
