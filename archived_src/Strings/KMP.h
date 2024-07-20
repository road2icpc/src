//# Title: Knuth-Morris-Pratt algorithm
//# Description: Yoinked from kactl. Finds all occurrences of a pattern in a string. \texttt{p[x]} computes the length of the longest prefix of \texttt{s} that ends at \texttt{x}, other than \texttt{s[0...x]} itself (\texttt{abacaba -> 0010123}).
//# Complexity: $\mathcal{O}(n)$.

vi pi(const string& s) {
	vi p(sz(s));
	rep(i,1,sz(s)) {
		int g = p[i-1];
		while (g && s[i] != s[g]) g = p[g-1];
		p[i] = g + (s[i] == s[g]);
	}
	return p;
}

vi match(const string& s, const string& pat) {
	vi p = pi(pat + '\0' + s), res;
	rep(i,sz(p)-sz(s),sz(p))
		if (p[i] == sz(pat)) res.push_back(i - 2 * sz(pat));
	return res;
}
