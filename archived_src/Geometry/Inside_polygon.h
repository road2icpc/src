//# Title: Inside polygon
//# Description: Yoinked from kactl. Returns true if p lies within the polygon. If strict is true, it returns false for points on the boundary. The algorithm uses products in intermediate steps so watch out for overflow.
//# Usage: \texttt{vector<P> v = \{P\{4,4\}, P\{1,2\}, P\{2,1\}\};\\bool in = inPolygon(v, P\{3, 3\}, false);}
//# Complexity: $\mathcal{O}(n)$.

#include "Point.h"
#include "On_segment.h"
#include "Segment_distance.h"

template<class P>
bool inPolygon(vector<P> &p, P a, bool strict = true) {
	int cnt = 0, n = sz(p);
	rep(i,0,n) {
		P q = p[(i + 1) % n];
		if (onSegment(p[i], q, a)) return !strict;
		//or: if (segDist(p[i], q, a) <= eps) return !strict;
		cnt ^= ((a.y<p[i].y) - (a.y<q.y)) * a.cross(p[i], q) > 0;
	}
	return cnt;
}
