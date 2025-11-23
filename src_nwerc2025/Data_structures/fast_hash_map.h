//# Title: Fast hash map
//# Description: 3x faster hash map, 1.5x more memory usage, similar API to std::unordered\_map. Initial capacity, if provided, must be power of 2.
//# Usage: \texttt{hash\_map <key\_t, val\_t> mp; mp[key] = val; mp.find(key); mp.begin(); mp.end(); mp.erase(key); mp.size();}
//# Complexity: $\mathcal{O}(1)$ per operation on average.

#pragma once

#include <bits/extc++.h>

struct chash {
	const uint64_t C = ll(4e18 * acos(0)) | 71;
	ll operator () (ll x) const { return __builtin_bswap64(x * C); }
};

template <typename KEY_T, typename VAL_T> using hash_map = __gnu_pbds::gp_hash_table <KEY_T, VAL_T, chash>;

