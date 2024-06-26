//# Title: Min rotation
//# Description: Yoinked from kactl. Finds the lexicographically smallest rotation of a string.
//# Usage: \texttt{rotate(v.begin(), v.begin() + minRotation(v), v.end());}
//# Complexity: $\mathcal{O}(n)$.

int minRotation(string s) {
	int a=0, N=sz(s); s += s;
	rep(b,0,N) rep(k,0,N) {
		if (a+k == b || s[a+k] < s[b+k]) {b += max(0, k-1); break;}
		if (s[a+k] > s[b+k]) { a = b; break; }
	}
	return a;
}
