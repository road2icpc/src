//# Title: Modular inverses
//# Description: Yoinked from kactl. Pre-computation of modular inverses. Assumes LIM $\le$ mod and that mod is a prime.

// const ll mod = 1000000007, LIM = 200000; ///include-line
ll* inv = new ll[LIM] - 1; inv[1] = 1;
rep(i,2,LIM) inv[i] = mod - (mod / i) * inv[mod % i] % mod;
