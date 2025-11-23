//@ Author: Simon Lindholm
//@ Date: 2018-07-06
//@ License: CC0
//@ Description: Permutation -> integer conversion. (Not order preserving.)
//@ Integer -> permutation can use a lookup table.
//@ Time: O(n)

//# Title: Permutation to Int
//# Description: [kactl] Given a permutation, returns the number of lexicographically strictly smaller permutations.
//# Complexity: $\mathcal{O}(n)$, but returns a value that is $\mathcal{O}(n!)$

//@ tested on:
//@	1. nothing :(

#pragma once

int permToInt(vector<int> v) {
	int use = 0, i = 0, r = 0;
	for(int x : v) {
		r = r * ++i + __builtin_popcount(use & -(1<<x));
		use |= 1 << x;
	}
	return r;
}
