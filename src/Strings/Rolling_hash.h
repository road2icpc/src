//# Title: Rolling Hash
//# Description: RH prepare string s, and hash gives the hash of the substring [l, r] inclusive. ib is pow(b, -1, MD), MD should be prime
//# Complexity: $\mathcal{O}(n)$ preprocessing, $\mathcal{O}(1)$ hash.

struct RH {
	int MD, n, b, ib; // b is base, ib inverse base mod MD
	vector<int> p, ip, hs;
	RH(string s, int _b = 69, int _ib = 579710149, int _MD = 1e9 + 7) : MD(_MD), n((int)s.size()), b(_b), ib(_ib), p(n), ip(n), hs(n) { // _b = 63, _ib = 698412843, MD = 1e9 + 207
		p[0] = ip[0] = 1;
		hs[0] = s[0];
		for(int i = 1; i < n; ++i){
			p[i] = (ll) p[i - 1] * b % MD;
			ip[i] = (ll) ip[i - 1] * ib % MD;
			hs[i] = ((ll) s[i] * p[i] + hs[i - 1]) % MD; // s[i] can be changed to some hash function
		}
	}
	int hash(int l, int r){
		return (ll) (hs[r] - (l ? hs[l - 1] : 0) + MD) * ip[l] % MD;
	}
};
