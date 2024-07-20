//# Title: Divisor Count
//# Description: Counts number of divisors

ll divisor_cnt(ll n) {
    ll cnt = 1;
    map<ll, ll> factors = factorize(n);
    for (auto p : factors) cnt *= p.second+1;
    return cnt;
}
