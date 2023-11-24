//# Title: Linear Recurrences
//# Description: Having a linear recurrence of the form f(n) = a_1 * f(n-1) + a_2 * f(n - 2) .. can be solved in log time with matrix exponentation.

#define Matrix vector<vector<ll>>
const ll m = 1000000007;
Matrix operator*(const Matrix& a, const Matrix& b) {
    Matrix c = Matrix(len(a), vector<ll>(len(b[0])));
    for (int i = 0; i < len(a); i++) {
        for (int j = 0; j < len(b[0]); j++) {
            for (int k = 0; k < len(b); k++) {
                c[i][j] += a[i][k]*b[k][j]%m;
                c[i][j] %= m;
            }
        }
    }
    return c;
}
// DOES THIS WORK? Why dp needed?
Matrix fast_exp(const Matrix& a, ll b, map<ll, Matrix>& dp) {
    if (dp.count(b)) return dp[b];
    if (b == 1) return a;
    if (b%2) return dp[b] = fast_exp(a, b/2, dp)*fast_exp(a, b/2, dp)*a;
    return dp[b] = fast_exp(a, b/2, dp)*fast_exp(a, b/2, dp);
}
Matrix operator^(const Matrix& a, ll b) {
    map<ll, Matrix> dp;
    return fast_exp(a, b, dp);
}
void linear_recurrence() {
    /*
        dp[j] += dp[i] * X[i][j] <-- genral case
    */
}
