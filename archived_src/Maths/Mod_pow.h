//# Title: Mod pow
//# Description: Yoinked from kactl. What u think mans. (this interface is used by a few other things, hence included in the document)
//# Complexity: $\mathcal{O}(\log e)$.

const ll mod = 1000000007; // faster if const

ll modpow(ll b, ll e) {
	ll ans = 1;
	for (; e; b = b * b % mod, e /= 2)
		if (e & 1) ans = ans * b % mod;
	return ans;
}
