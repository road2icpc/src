//# Title: Modulo multiplication for 64-bit integers
//# Description: Yoinked from kactl. Calculate $a\cdot b\bmod c$ (or $a^b \bmod c$) for $0 \le a, b \le c \le 7.2\cdot 10^{18}$. This runs ~2x faster than the naive \texttt{(\_\_int128\_t)a * b \% M}.
//# Complexity: $\mathcal{O}(1)$ for \texttt{modmul}, $\mathcal{O}(\log b)$ for \texttt{modpow}.

typedef unsigned long long ull;
ull modmul(ull a, ull b, ull M) {
	ll ret = a * b - M * ull(1.L / M * a * b);
	return ret + M * (ret < 0) - M * (ret >= (ll)M);
}
ull modpow(ull b, ull e, ull mod) {
	ull ans = 1;
	for (; e; b = modmul(b, b, mod), e /= 2)
		if (e & 1) ans = modmul(ans, b, mod);
	return ans;
}
