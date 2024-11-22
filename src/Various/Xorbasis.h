//# Title: Xor Basis
//# Description: Basis of vectors in $Z^d_{2}$

struct XB {
	vector<int> basis;
	void ins(int mask) {
		for(auto &y : basis) {
			if(y < mask) swap(y, mask);
			mask = min(mask, mask ^ y);
		}
		if(mask) basis.push_back(mask); // if mask is 0 value can already be represented by basis
	}
};
