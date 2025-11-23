//@ Author: Emil Lenngren, Simon Lindholm
//@ Date: 2011-11-29
//@ License: CC0
//@ Source: folklore
//@ Status: stress-tested

//# Title: 2SAT
//# Description: [kactl] Classic 2sat.
//#  Negated variables are represented by bit-inversions (\texttt{\tilde{}x}).
//# Usage:
//#  TwoSat ts(number of boolean variables)
//#  ts.implies(0, \tilde3); // Var 0 is true implies Var 3 is false
//#  ts.setValue(2); // Var 2 is true
//#  ts.solve(); // Returns true iff solvable
//#  ts.values[0..N-1] holds the assigned values of the vars
//# Complexity: O(N+E), where N is the number of boolean variables, and E is the number of implications.

//@ tested on:
//@	nothing :(

#pragma once

struct TwoSat {
	int N;
	vector<vector<int>> gr;
	vector<int> values; // 0 = false, 1 = true

	TwoSat(int n = 0) : N(n), gr(2*n) {}

	int addVar() { // (optional)
		gr.emplace_back();
		gr.emplace_back();
		return N++;
	}

	void implies(int f, int j) {
		f = max(2*f, -1-2*f);
		j = max(2*j, -1-2*j);
		gr[f].push_back(j);
		gr[j^1].push_back(f^1);
	}
	void setValue(int x) { implies(~x, x); }

	vector<int> val, comp, z;
	int time = 0;
	int dfs(int i) {
		int low = val[i] = ++time, x; z.push_back(i);
		for(int e : gr[i]) if (!comp[e])
			low = min(low, val[e] ?: dfs(e));
		if (low == val[i]) do {
			x = z.back(); z.pop_back();
			comp[x] = low;
			if (values[x>>1] == -1)
				values[x>>1] = x&1;
		} while (x != i);
		return val[i] = low;
	}

	bool solve() {
		values.assign(N, -1);
		val.assign(2*N, 0); comp = val;
		for (int i = 0; i < 2 * N; i++) if (!comp[i]) dfs(i);
		for (int i = 0; i < N; i++) if (comp[2*i] == comp[2*i+1]) return 0;
		return 1;
	}
};
