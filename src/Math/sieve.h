//# Title: Sieve of Eratosthenes
//# Description: Generates all primes up to $n$ (inclusive). Note: this version uses much less memory for large $n$ and is far more cache-friendly. Prefer this for large $n$! This is ~3.5x faster for $n \approx 5 \cdot 10^8$ compared to normal sieve (with all optimizations).
//# Usage: \texttt{sieve(n)} where $n$ is the upper bound.
//# Complexity: $\mathcal{O}(n \log \log n)$ time, $\mathcal{O}(\sqrt(n) + S)$ space where $S$ is the block size.

//@ tested on:
//@  1. https://judge.yosupo.jp/problem/enumerate_primes

#pragma once

vi sieve(int n) {
	if (n < 2) return { };
	const int S = 1 << 15, sq = round(sqrt(n));
	vi res = { 2 }, pr, start;
	vector <char> isp(max(S, sq + 1), 1);
	for (int i = 3; i <= sq; i += 2) if (isp[i]) {
		pr.push_back(i); start.push_back(i * i / 2);
		for (int j = i * i; j < sq; j += i * 2) isp[j] = 0;
	}
	n = (n - 1) / 2;
	for (int l = 0; l < n; l += S) {
		isp.assign(S, 1);
		for (int i = 0, p, j; i < siz(pr); i++) {
			for (p = pr[i], j = start[i]; j < S; j += p) isp[j] = 0;
			start[i] = j - S;
		}
		isp[0] &= !!l;
		for (int i = 0; i < S && l + i <= n; i++) if (isp[i]) res.push_back((l + i) * 2 + 1);
	}
	return res;
}
