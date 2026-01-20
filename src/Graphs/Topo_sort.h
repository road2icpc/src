//# Title: Topological sort
//# Description: Yoinked from kactl. Given is an oriented graph. Output is an ordering of vertices, such that there are edges only from left to right. If there are cycles, the returned list will have size smaller than $n$ -- nodes reachable from cycles will not be returned.
//# Usage: \texttt{vi res = topoSort(gr);}
//# Complexity: $\mathcal{O}(V + E)$.

//@ tested on:
//@  1. https://cses.fi/problemset/task/1679/

#pragma once

vi topoSort(const vector<vi> &gr) {
	int n = gr.size();
	vi deg(n), ret;
	for (auto &li : gr)
		for (auto x : li)
			deg[x]++;
	queue<int> q;
	for (int i = 0; i < n; i++)
		if (!deg[i])
			q.push(i);
	while (!q.empty()) {
		int v = q.front();
		ret.push_back(v);
		q.pop();
		for (auto u : gr[v])
			if (--deg[u] == 0)
				q.push(u);
	}
	return ret;
}
