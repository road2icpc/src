//# Title: Polygon center of mass
//# Description: Yoinked from kactl. Returns the center of mass for a polygon.
//# Complexity: $\mathcal{O}(n)$.

#include "Point.h"

typedef Point<double> P;
P polygonCenter(const vector<P>& v) {
	P res(0, 0); double A = 0;
	for (int i = 0, j = sz(v) - 1; i < sz(v); j = i++) {
		res = res + (v[i] + v[j]) * v[j].cross(v[i]);
		A += v[j].cross(v[i]);
	}
	return res / A / 3;
}
