//# Title: Suffix automaton
//# Description: Standard suffix automaton. Does what you'd expect.
//# Usage: See example main function below. This was thrown in last minute from a working cses solution.
//# Complexity: $\mathcal{O}(\log n)$ per update/query

//@ tested on:
//@  1. https://cses.fi/problemset/task/2106/
//@  2. several other cses.fi problems

struct SA {
	struct State {
		int length;
		int link;
		int next[26];
		int cnt;
		bool is_clone;
		int first_pos;
		State(int _length, int _link) :
		length(_length),
		link(_link),
		cnt(0),
		is_clone(false),
		first_pos(-1)
		{
			memset(next, -1, sizeof(next));
		}
	};
	std::vector <State> states;
	int size;
	int last;
	bool did_init_count;
	int str_len;
	bool did_init_css;
	SA() :
	states(1, State(0, -1)),
	size(1),
	last(0),
	did_init_count(false),
	str_len(0),
	did_init_css(false)
	{ }
	void push(char c) {
		str_len++;
		did_init_count = false;
		did_init_css = false;
		int cur = size;
		states.resize(++size, State(states[last].length + 1, -1));
		states[cur].first_pos = states[cur].length - 1;
		int p = last;
		while (p != -1 && states[p].next[c - 'a'] == -1) {
			states[p].next[c - 'a'] = cur;
			p = states[p].link;
		}
		if (p == -1) {
			states[cur].link = 0;
		} else {
			int q = states[p].next[c - 'a'];
			if (states[p].length + 1 == states[q].length) {
				states[cur].link = q;
			} else {
				int clone = size;
				states.resize(++size, State(states[p].length + 1, states[q].link));
				states[clone].is_clone = true;
				memcpy(states[clone].next, states[q].next, sizeof(State::next));
				states[clone].first_pos = states[q].first_pos;
				while (p != -1 && states[p].next[c - 'a'] == q) {
					states[p].next[c - 'a'] = clone;
					p = states[p].link;
				}
				states[q].link = states[cur].link = clone;
			}
		}
		last = cur;
	}
	bool exists(const std::string& pattern) {
		int node = 0;
		int index = 0;
		while (index < (int) pattern.length() && states[node].next[pattern[index] - 'a'] != -1) {
			node = states[node].next[pattern[index] - 'a'];
			index++;
		}
		return index == (int) pattern.size();
	}
	int count(const std::string& pattern) {
		if (!did_init_count) {
			did_init_count = true;
			for (int i = 1; i < size; i++) {
				states[i].cnt = !states[i].is_clone;
			}
			std::vector <std::vector <int>> of_length(str_len + 1);
			for (int i = 0; i < size; i++) {
				of_length[states[i].length].push_back(i);
			}
			for (int l = str_len; l >= 0; l--) {
				for (int node : of_length[l]) {
					if (states[node].link != -1) {
						states[states[node].link].cnt += states[node].cnt;
					}
				}
			}
		}
		int node = 0;
		int index = 0;
		while (index < (int) pattern.length() && states[node].next[pattern[index] - 'a'] != -1) {
			node = states[node].next[pattern[index] - 'a'];
			index++;
		}
		return index == (int) pattern.size() ? states[node].cnt : 0;
	}
	int first_occ(const std::string& pattern) {
		int node = 0;
		int index = 0;
		while (index < (int) pattern.length() && states[node].next[pattern[index] - 'a'] != -1) {
			node = states[node].next[pattern[index] - 'a'];
			index++;
		}
		return index == (int) pattern.size() ? states[node].first_pos - (int) pattern.size() + 1 : -1;
	}
	size_t count_substrings() {
		static std::vector <size_t> dp;
		if (!did_init_css) {
			did_init_css = true;
			dp = std::vector <size_t> (size, 0);
			auto dfs = [&] (auto&& self, int node) -> size_t {
				if (node == -1) {
					return 0;
				}
				if (dp[node]) {
					return dp[node];
				}
				dp[node] = 1;
				for (int i = 0; i < 26; i++) {
					dp[node] += self(self, states[node].next[i]);
				}
				return dp[node];
			};
			dfs(dfs, 0);
		}
		return dp[0] - 1;
	}
};

// usage example: Repeating Substring submission on cses.fi
int main() {
	std::ios::sync_with_stdio(0); std::cin.tie(0);
	std::string s; std::cin >> s;
	int n; std::cin >> n;
	SA sa;
	for (char c : s) {
		sa.push(c);
	}
	sa.count("");
	int len = -1;
	int ind = -1;
	for (int i = 1; i < sa.size; i++) {
		if (sa.states[i].cnt > 1) {
			if (len < sa.states[i].length) {
				len = sa.states[i].length;
				ind = sa.states[i].first_pos - len + 1;
			}
		}
	}
	if (len == -1) {
		std::cout << "-1\n";
		return 0;
	}
	for (int i = 0; i < len; i++) {
		std::cout << s[i + ind];
	}
	std::cout << "\n";
}
