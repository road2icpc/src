//# Title: Implicit 2D segment tree
//# Description: Classic implicit 2D segment tree taken from my solution to IOI game 2013. It is in rough shape, but it works. Designed to be \texttt{[inclusive, exclusive)}. It is old and looks shady, only rely slightly on it, maybe even just make a new one if you need one.
//# Usage: See usage example at the bottom.
//# Complexity: $\mathcal{O}(\log^2 n)$ per operation \textit{I think}.

//@ tested on:
//@ - https://oj.uz/problem/view/IOI13_game

constexpr const int MX_RC = 1 << 30;
 
struct Inner {
	long long val;
	int lv, rv;
	Inner* lc,* rc;
	Inner(long long _val, int _l, int _r) :
	val(_val), lv(_l), rv(_r), lc(nullptr), rc(nullptr)
	{ }
	~Inner() {
		delete(lc);
		delete(rc);
	}
	void update(int ind, long long nev, int l = 0, int r = MX_RC) {
		if (!(r - l - 1)) {
			assert(lv == l && rv == r);
			assert(ind == l);
			val = nev;
			return;
		}
		int mid = (l + r) >> 1;
		if (ind < mid) {
			if (lc) {
				if (lc->lv != l || lc->rv != mid) {
					Inner* tmp = lc;
					lc = new Inner(0, l, mid);
					(tmp->lv < ((l + mid) >> 1) ? lc->lc : lc->rc) = tmp;
				}
				lc->update(ind, nev, l, mid);
			} else lc = new Inner(nev, ind, ind + 1);
		} else {
			if (rc) {
				if (rc->lv != mid || rc->rv != r) {
					Inner* tmp = rc;
					rc = new Inner(0, mid, r);
					(tmp->lv < ((mid + r) >> 1) ? rc->lc : rc->rc) = tmp;
				}
				rc->update(ind, nev, mid, r);
			} else rc = new Inner(nev, ind, ind + 1);
		}
		val = std::gcd(lc ? lc->val : 0, rc ? rc->val : 0);
	}
	long long query(int tl, int tr, int l = 0, int r = MX_RC) {
		if (l >= tr || r <= tl) return 0;
		if (!(rv - lv - 1)) {
			if (lv >= tr || rv <= tl) return 0;
			return val;
		}
		assert(l == lv && r == rv);
		if (l >= tl && r <= tr) return val;
		int mid = (l + r) >> 1;
		return std::gcd(lc ? lc->query(tl, tr, l, mid) : 0, rc ? rc->query(tl, tr, mid, r) : 0);
	}
	void fill(Inner* source) {
		val = source->val;
		if (!(lv - rv - 1)) return;
		if (source->lc) {
			lc = new Inner(source->lc->val, source->lc->lv, source->lc->rv);
			lc->fill(source->lc);
		}
		if (source->rc) {
			rc = new Inner(source->rc->val, source->rc->lv, source->rc->rv);
			rc->fill(source->rc);
		}
	}
};
 
struct Outer {
	Inner* inner;
	int lv, rv;
	Outer* lc,* rc;
	Outer(Inner* _inner, int _l, int _r) :
	inner(_inner), lv(_l), rv(_r), lc(nullptr), rc(nullptr)
	{ }
	void update(int ind_outer, int ind_inner, long long nev, int l = 0, int r = MX_RC) {
		if (!(r - l - 1)) {
			assert(lv == l && rv == r);
			assert(ind_outer == l);
			assert(inner);
			inner->update(ind_inner, nev);
			return;
		}
		int mid = (l + r) >> 1;
		if (ind_outer < mid) {
			if (lc) {
				if (lc->lv != l || lc->rv != mid) {
					Outer* tmp = lc;
					lc = new Outer(new Inner(0, 0, MX_RC), l, mid);
					lc->inner->fill(tmp->inner);
					(tmp->lv < ((l + mid) >> 1) ? lc->lc : lc->rc) = tmp;
				}
				lc->update(ind_outer, ind_inner, nev, l, mid);
			} else {
				lc = new Outer(new Inner(0, 0, MX_RC), ind_outer, ind_outer + 1);
				lc->inner->update(ind_inner, nev);
			}
		} else {
			if (rc) {
				if (rc->lv != mid || rc->rv != r) {
					Outer* tmp = rc;
					rc = new Outer(new Inner(0, 0, MX_RC), mid, r);
					rc->inner->fill(tmp->inner);
					(tmp->lv < ((mid + r) >> 1) ? rc->lc : rc->rc) = tmp;
				}
				rc->update(ind_outer, ind_inner, nev, mid, r);
			} else {
				rc = new Outer(new Inner(nev, 0, MX_RC), ind_outer, ind_outer + 1);
				rc->inner->update(ind_inner, nev);
			}
		}
		inner->update(ind_inner, std::gcd(
		lc ? lc->inner->query(ind_inner, ind_inner + 1) : 0,
		rc ? rc->inner->query(ind_inner, ind_inner + 1) : 0));
	}
	long long query(int tl_outer, int tr_outer, int tl_inner, int tr_inner, int l = 0, int r = MX_RC) {
		if (l >= tr_outer || r <= tl_outer) return 0;
		if (!(rv - lv - 1)) {
			if (lv >= tr_outer || rv <= tl_outer) return 0;
			return inner->query(tl_inner, tr_inner);
		}
		assert(l == lv && r == rv);
		if (l >= tl_outer && r <= tr_outer)
			return inner->query(tl_inner, tr_inner);
		int mid = (l + r) >> 1;
		return std::gcd(
		lc ? lc->query(tl_outer, tr_outer, tl_inner, tr_inner, l, mid) : 0,
		rc ? rc->query(tl_outer, tr_outer, tl_inner, tr_inner, mid, r) : 0);
	}
};
 
// this is how it has been used in the solution to IOI game 2013
Outer root(new Inner(0, 0, MX_RC), 0, MX_RC);
void update(int r, int c, long long k) {
	root.update(r, c, k);
}
long long calculate(int r_l, int c_l, int r_r, int c_r) {
	return root.query(r_l, r_r + 1, c_l, c_r + 1);
}
