//# Title: Sum over subsets
//# Description: Used to calculate the sum of values for all subsets of
//# a given set or bitmask essentially calculates $S_x = \sum_{i|x = x}v_i$ for all x
//# Usage: 
//#   v should be a frequency array where the values correspond to how many elements have such mask
//#   SOS(v) // returns vector with S_x
//# Complexity: $\mathcal{O}(N \log N)$ 

vector<int> SOS(vector<int> v) {
	int lg = 31 - __builtin_clz((int)v.size()), mx = 1 << lg;
	v.resize(mx);
	for(int i = 0; i < lg; ++i) for(int j = (1 << i); j < mx; ++j) if(j >> i & 1) v[j] += v[j - (1 << i)];
	return v;
}
