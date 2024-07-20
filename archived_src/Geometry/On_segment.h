//# Title: Is on segment
//# Description: Yoinked from kactl. Returns true iff p lies on the line segment from s to e. Use \texttt{(segDist(s,e,p)<=epsilon)} instead when using \texttt{Point <double>}.

#include "Point.h"

template<class P> bool onSegment(P s, P e, P p) {
	return p.cross(s, e) == 0 && (s - p).dot(e - p) <= 0;
}
