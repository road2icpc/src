//# Title: Solve linear equations extended
//# Description: Yoinked from kactl. To get all uniquely determined values of $x$ back from SolveLinear, make the following changes:

#include "Solve_linear.h"

rep(j,0,n) if (j != i) // instead of rep(j,i+1,n)
// ... then at the end:
x.assign(m, undefined);
rep(i,0,rank) {
	rep(j,rank,m) if (fabs(A[i][j]) > eps) goto fail;
	x[col[i]] = b[i] / A[i][i];
fail:; }
