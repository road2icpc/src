i64 divisor_cnt(i64 n) {
    i64 cnt = 1;
    map<i64, i64> factors = factorize(n);
    for (auto p : factors) cnt *= p.second+1;
    return cnt;
}