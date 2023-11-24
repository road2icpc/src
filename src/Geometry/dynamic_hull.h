struct point {
    ll x, y;
    point(ll x=0, ll y=0): x(x), y(y) {}
    point operator-(const point &p) const { return point(x-p.x, y-p.y); }
    point operator*(const ll k) const { return point(k*x, k*y); }
    ll cross(const point &p) const { return x*p.y - p.x*y; }
    bool operator<(const point &p) const { return x < p.x || x == p.x && y < p.y; }
};

bool above(set<point> &hull, point p, ll scale = 1) {
    auto it = hull.lower_bound(point((p.x+scale-1)/scale, 0));
    if (it == hull.end()) return true;
    if (p.y <= it->y*scale) return false;
    if (it == hull.begin()) return true;
    auto jt = it--;
    return (p-*it*scale).cross(*jt-*it) < 0;
}

void add(set<point> &hull, point p) {
    if (!above(hull, p)) return;
    auto pit = hull.insert(p).first;
    while (pit != hull.begin()) {
        auto it = prev(pit);
        if (it->y <= p.y || (it != hull.begin() && (*it-*prev(it)).cross(*pit-*it) >= 0))
            hull.erase(it);
        else
            break;
    }
    auto it = next(pit);
    while (it != hull.end()) {
        if (next(it) != hull.end() && (*it-p).cross(*next(it)-*it) >= 0)
            hull.erase(it++);
        else
            break;
    }
}