//# Title: Euclid
//# Description: Yoinked from kactl. Finds two integers $x$ and $y$, such that $ax+by=\gcd(a,b)$. If $a$ and $b$ are coprime, then $x$ is the inverse of $a \pmod{b}$.
//# Complexity: $\mathcal{O}(\log n)$.

ll euclid(ll a, ll b, ll &x, ll &y) {
	if (!b) return x = 1, y = 0, a;
	ll d = euclid(b, a % b, y, x);
	return y -= a/b * x, d;
}
