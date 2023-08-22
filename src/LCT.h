// Li-Chao tree
// insert/query with (l, r) = (0, size)

//@ tested on:
//@  1. https://cses.fi/problemset/task/2084/
//@  2. https://cses.fi/problemset/task/2085/

struct Line { ll a, b; ll f(ll x) { return a * x + b; } };
constexpr const Line LINF { 0, 1LL << 60 };
struct LCT {
	vector <Line> v; // add coordinate compression by converting v[x] to v[conert(x)]
	LCT(int size) { v.resize(size + 1, LINF); }
	void insert(Line line, int l, int r) {
		if (l > r) return;
		int mid = (l + r) >> 1;
		if (line.f(mid) < v[mid].f(mid)) swap(line, v[mid]);
		if (line.f(l) < v[mid].f(l)) insert(line, l, mid - 1);
		else insert(line, mid + 1, r);
	}
	Line query(int x, int l, int r) {
		if (l > r) return LINF;
		int mid = (l + r) >> 1;
		if (x == mid) return v[mid]; // faster on avg. - not necessary
		if (x < mid) return best_of(v[mid], query(x, l, mid - 1), x);
		return best_of(v[mid], query(x, mid + 1, r), x);
	}
	Line best_of(Line a, Line b, ll x) { return a.f(x) < b.f(x) ? a : b; }
};

