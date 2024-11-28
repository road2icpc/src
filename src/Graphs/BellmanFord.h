//# Title: Bellman-Ford
//# Description: Calculates shortest paths from $s$ in a graph that might have negative edge weights. Unreachable nodes get \texttt{dist = inf;}, nodes reachable through negative-weight cycles get \texttt{dist = -inf;}. Assumes $V^2 \cdot \max (w_i) < \tilde{} 2^63{}$.
//# Usage: \texttt{bellmanFord(nodes, edges, s)}
//# Complexity: $\mathcal{O}(VE)$

//@ tested on:
//@  1. https://cses.fi/problemset/task/1673/

const ll inf = LLONG_MAX;
struct Ed { int v, u, w; };
struct Node { ll dist = inf; int prev = -1; };

void bellmanFord(vector<Node> &nodes, vector<Ed> eds, int s) {
	nodes[s].dist = 0;
	int n = nodes.size();
	for (int i = 0; i < n; i++) {
		for (auto ed : eds) {
			Node v = nodes[ed.v], &u = nodes[ed.u];
			if (abs(v.dist) == inf) continue;
			ll d = v.dist + ed.w;
			if (d < u.dist) {
				u.prev = ed.v;
				u.dist = (i < n-1 ? d : -inf);
			}
		}
	}
	for (int i = 0; i < n-1; i++)
		for (auto ed : eds)
			if (nodes[ed.v].dist == -inf)
				nodes[ed.u].dist = -inf;
}
