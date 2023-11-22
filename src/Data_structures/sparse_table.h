//# Title: Sparse table
//# Description: Yeeted from kactl. Classic sparse table, implemented with range minimum queries, can be modified.
//# Usage: \texttt{Sparse s(vec); s.query(a, b);}
//# Complexity: $\mathcal{O}(\mid V \mid \log \mid V \mid + Q)$.

template<class T> struct Sparse {
	vector<vector<T>> jmp;
	Sparse(const vector<T>& V) : jmp(1, V) {
		for (int pw = 1, k = 1; pw * 2 <= sz(V); pw *= 2, ++k) {
			jmp.emplace_back(sz(V) - pw * 2 + 1);
			rep(j,0,sz(jmp[k]))
				jmp[k][j] = min(jmp[k - 1][j], jmp[k - 1][j + pw]);
		}
	}
	T query(int a, int b) { // interval [a, b)
		assert(a < b); // or return inf if a == b
		int dep = 31 - __builtin_clz(b - a);
		return min(jmp[dep][a], jmp[dep][b - (1 << dep)]);
	}
};
