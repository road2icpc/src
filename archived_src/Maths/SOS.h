//# Title: SOS DP
//# Description: Some solution from some problem Elias solved. For each of $n$ elements $x$: The number of elements $y$ such that $x \mid y = x$. The number of elements $y$ such that $x \mathrel{\&} y = x$. The number of elements $y$ such that $x \mathrel{\&} y \neq 0$. NOTE: if TLE issues, try loop unrolling or C style arrays.
//# Complexity: $\mathcal{O}(V \log V + n)$ where $V$ is the maximum value.

//@ tested on:
//@  1. https://cses.fi/problemset/task/1654/
 
constexpr const int lgmxV = 20;
constexpr const int mxV = 1 << lgmxV;
 
int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int n; cin >> n;
    vector<int> v(n);
    for(auto &x : v)cin >> x;
    vector<vector<int>> sos1(mxV, vector<int> (lgmxV + 1, 0));
    vector<vector<int>> sos2(mxV, vector<int> (lgmxV + 1, 0));
    for(int i = 0; i < n; ++i){
        sos1[v[i]][0]++;
        sos2[v[i] ^ (mxV - 1)][0]++;
    }
    for(int i = 0; i < mxV; ++i){
        for(int j = 0; j < lgmxV; ++j){
            sos1[i][j + 1] = sos1[i][j];
            sos2[i][j + 1] = sos2[i][j];
            if(i & (1 << j)) { sos1[i][j + 1] += sos1[i - (1 << j)][j]; };
            if(i & (1 << j)) { sos2[i][j + 1] += sos2[i - (1 << j)][j]; };
        }
    }
    for(int i = 0; i < n; ++i){
        cout << sos1[v[i]][lgmxV] << ' ' << sos2[v[i] ^ (mxV - 1)][lgmxV] << ' ' << n - sos1[v[i] ^ (mxV - 1)][lgmxV] << '\n';
    }
}
