//# Title: Gauss-Jordan elimination
//# Description: Yoinked from CP-algorithms. The description is taken from CP-algorithms as well: Following is an implementation of Gauss-Jordan. Choosing the pivot row is done with heuristic: choosing maximum value in the current column. The input to the function \texttt{gauss} is the system matrix $a$. The last column of this matrix is vector $b$. The function returns the number of solutions of the system $(0, 1,\textrm{or } \infty)$. If at least one solution exists, then it is returned in the vector $ans$.
//# Implementation notes:
//# \begin{itemize}
//#   \item The function uses two pointers - the current column $col$ and the current row $row$.
//#   \item For each variable $x_i$, the value $where(i)$ is the line where this column is not zero. This vector is needed because some variables can be independent.
//#   \item In this implementation, the current $i$ th line is not divided by $a_{ii}$ as described above, so in the end the matrix is not identity matrix (though apparently dividing the $i$ th line can help reducing errors).
//#   \item After finding a solution, it is inserted back into the matrix - to check whether the system has at least one solution or not. If the test solution is successful, then the function returns 1 or $\inf$, depending on whether there is at least one independent variable.
//# \end{itemize}
//# kactl also has code for solving linear systems somewhere in the document, if needed.
//# Complexity: $\mathcal{O}(\min(n, m) \cdot nm)$ -- I.e. cubic.

const double EPS = 1e-9;
const int INF = 2; // it doesn't actually have to be infinity or a big number

int gauss (vector < vector<double> > a, vector<double> & ans) {
	int n = (int) a.size();
	int m = (int) a[0].size() - 1;

	vector<int> where (m, -1);
	for (int col=0, row=0; col<m && row<n; ++col) {
		int sel = row;
		for (int i=row; i<n; ++i)
			if (abs (a[i][col]) > abs (a[sel][col]))
				sel = i;
		if (abs (a[sel][col]) < EPS)
			continue;
		for (int i=col; i<=m; ++i)
			swap (a[sel][i], a[row][i]);
		where[col] = row;

		for (int i=0; i<n; ++i)
			if (i != row) {
				double c = a[i][col] / a[row][col];
				for (int j=col; j<=m; ++j)
					a[i][j] -= a[row][j] * c;
			}
		++row;
	}

	ans.assign (m, 0);
	for (int i=0; i<m; ++i)
		if (where[i] != -1)
			ans[i] = a[where[i]][m] / a[where[i]][i];
	for (int i=0; i<n; ++i) {
		double sum = 0;
		for (int j=0; j<m; ++j)
			sum += ans[j] * a[i][j];
		if (abs (sum - a[i][m]) > EPS)
			return 0;
	}

	for (int i=0; i<m; ++i)
		if (where[i] == -1)
			return INF;
	return 1;
}
