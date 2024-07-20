//# Title: Interval cover
//# Description: Yoinked from kactl. Compute indices of smallest set of intervals covering another interval. Intervals should be \texttt{[inclusive, exclusive)}. To support \texttt{[inclusive, inclusive]}, change (A) to add \texttt{|| R.empty()}. Returns empty set on failure (or if G is empty).
//# Complexity: $\mathcal{O}(n \log n)$.

template<class T>
vi cover(pair<T, T> G, vector<pair<T, T>> I) {
	vi S(sz(I)), R;
	iota(all(S), 0);
	sort(all(S), [&](int a, int b) { return I[a] < I[b]; });
	T cur = G.first;
	int at = 0;
	while (cur < G.second) { // (A)
		pair<T, int> mx = make_pair(cur, -1);
		while (at < sz(I) && I[S[at]].first <= cur) {
			mx = max(mx, make_pair(I[S[at]].second, S[at]));
			at++;
		}
		if (mx.second == -1) return {};
		cur = mx.first;
		R.push_back(mx.second);
	}
	return R;
}
