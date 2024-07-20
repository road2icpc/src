//# Title: Polygon area
//# Description: Yoinked from kactl. Returns \textit{twice} the signed area of a polygon. Clockwise enumeration gives negative area. Watch out for overflow if using int as T!

#include "Point.h"

template<class T>
T polygonArea2(vector<Point<T>>& v) {
	T a = v.back().cross(v[0]);
	rep(i,0,sz(v)-1) a += v[i].cross(v[i+1]);
	return a;
}
