//# Title: Ordered Map
//# Description: \texttt{extc++.h} order statistics tree. \texttt{find\_by\_order} returns an iterator to the $k$th element (0-indexed), \texttt{order\_of\_key} returns the index of the element (0-indexed), i.e. the number of elements less than the argument.
//# Usage: \texttt{ordered\_set <int> s; s.insert(1); s.insert(2); *s.find\_by\_order(0) = 3; s.erase(3); s.order\_of\_key(2);}
//# Complexity: Everything is $\mathcal{O}(\log n)$.

#include <bits/extc++.h>
using namespace __gnu_pbds;
template <typename T> using ordered_set = tree <T, null_type, less <T>, rb_tree_tag, tree_order_statistics_node_update>;
template <typename T, typename U> using ordered_map = tree <T, U, less <T>, rb_tree_tag, tree_order_statistics_node_update>;

// yeet from kactl:
void example() {
	ordered_set <int> t, t2; t.insert(8);
	auto it = t.insert(10).first;
	assert(it == t.lower_bound(9));
	assert(t.order_of_key(10) == 1);
	assert(t.order_of_key(11) == 2);
	assert(*t.find_by_order(0) == 8);
	t.join(t2); // assuming T < T2 or T > T2, merge t2 into t
}
