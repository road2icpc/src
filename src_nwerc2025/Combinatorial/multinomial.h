//@ Author: Mattias de Zalenski, Fredrik Niemelä, Per Austrin, Simon Lindholm
//@ Date: 2002-09-26
//@ Source: Max Bennedich
//@ Status: Tested on kattis:lexicography

//# Title: Multinomial
//# Description: [kactl] Computes $\displaystyle \binom{k_1 + \dots + k_n}{k_1, k_2, \dots, k_n} = \frac{(\sum k_i)!}{k_1!k_2!...k_n!}$.

//@ tested on:
//@	nothing :(

#pragma once

ll multinomial(vector<int> v) {
	ll c = 1, m = v.size() ? v[0] : 1;
	for (int i = 1; i < (int)v.size(); i++)
		for (int j = 0; j < v[i]; j++)
			c = c * ++m / (j+1);
	return c;
}
