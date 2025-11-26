//# Title: (FROM CHAT-GPT) Lazy Treap
//# Description: Yoinked from CHAT-GPT. Treap supporting entire tree updates/queries + split/merge. Tested a bit.
//# Complexity: $\mathcal{O}(\log n)$ or better on average.

#pragma once

namespace gpt {

	struct Node {
		int val;            // Value of the node
		int priority;       // Priority for treap balancing
		int size;           // Size of the subtree rooted at this node
		int subtree_min;    // Minimum value in the subtree
		int lazy_add;       // Lazy propagation value
		std::shared_ptr <Node> left;         // Left child
		std::shared_ptr <Node> right;        // Right child

		Node(int _val) : val(_val), priority(std::rand()), size(1), subtree_min(_val),
						 lazy_add(0), left(nullptr), right(nullptr) {}
	};

	int Size(std::shared_ptr <Node> node) {
		return node ? node->size : 0;
	}

	int SubtreeMin(std::shared_ptr <Node> node) {
		return node ? node->subtree_min : std::numeric_limits<int>::max();
	}

	void Propagate(std::shared_ptr <Node> node) {
		if (node && node->lazy_add != 0) {
			node->val += node->lazy_add;

			if (node->left) {
				node->left->lazy_add += node->lazy_add;
				node->left->subtree_min += node->lazy_add;
			}
			if (node->right) {
				node->right->lazy_add += node->lazy_add;
				node->right->subtree_min += node->lazy_add;
			}

			node->lazy_add = 0;

			// Update subtree_min after propagation
			node->subtree_min = std::min(node->val, std::min(SubtreeMin(node->left), SubtreeMin(node->right)));
		}
	}

	void Update(std::shared_ptr <Node> node) {
		if (node) {
			node->size = 1 + Size(node->left) + Size(node->right);
			node->subtree_min = std::min(node->val, std::min(SubtreeMin(node->left), SubtreeMin(node->right)));
		}
	}

	void Split(std::shared_ptr <Node> node, int index, std::shared_ptr <Node>& left, std::shared_ptr <Node>& right) {
		if (!node) {
			left = right = nullptr;
			return;
		}
		Propagate(node);
		int curr_index = Size(node->left);
		if (index <= curr_index) {
			Split(node->left, index, left, node->left);
			right = node;
		} else {
			Split(node->right, index - curr_index - 1, node->right, right);
			left = node;
		}
		Update(node);
	}

	std::shared_ptr <Node> Merge(std::shared_ptr <Node> left, std::shared_ptr <Node> right) {
		Propagate(left);
		Propagate(right);
		if (!left || !right) {
			return left ? left : right;
		}
		if (left->priority > right->priority) {
			left->right = Merge(left->right, right);
			Update(left);
			return left;
		} else {
			right->left = Merge(left, right->left);
			Update(right);
			return right;
		}
	}

	void AddValue(std::shared_ptr <Node> node, int value) {
		if (!node) return;
		node->lazy_add += value;
		node->subtree_min += value;
	}

	int GetMin(std::shared_ptr <Node> node) {
		if (!node) return std::numeric_limits<int>::max();
		Propagate(node);
		return node->subtree_min;
	}

	int GetMinIndex(std::shared_ptr <Node> node, int offset = 0) {
		if (!node) return -1;
		Propagate(node);
		int min_val = node->subtree_min;

		if (node->val == min_val) {
			return offset + Size(node->left);
		} else if (SubtreeMin(node->left) == min_val) {
			return GetMinIndex(node->left, offset);
		} else {
			return GetMinIndex(node->right, offset + Size(node->left) + 1);
		}
	}

	int GetValue(std::shared_ptr <Node> node, int index) {
		if (!node) return std::numeric_limits<int>::max();  // Or throw an exception
		Propagate(node);
		int curr_index = Size(node->left);
		if (index < curr_index) {
			return GetValue(node->left, index);
		} else if (index == curr_index) {
			return node->val;
		} else {
			return GetValue(node->right, index - curr_index - 1);
		}
	}

	void SetValue(std::shared_ptr <Node> node, int index, int value) {
		if (!node) return;  // Or throw an exception
		Propagate(node);
		int curr_index = Size(node->left);
		if (index < curr_index) {
			SetValue(node->left, index, value);
		} else if (index == curr_index) {
			node->val = value;
		} else {
			SetValue(node->right, index - curr_index - 1, value);
		}
		Update(node);
	}

	void InOrder(std::shared_ptr <Node> node) {
		if (!node) return;
		Propagate(node);
		InOrder(node->left);
		std::cout << node->val << " ";
		InOrder(node->right);
	}

	// Helper function to build a treap from an array
	std::shared_ptr <Node> Build(const int arr[], int l, int r) {
		if (l > r) return nullptr;
		int m = (l + r) / 2;
		std::shared_ptr <Node> node = std::make_shared <Node>(arr[m]);
		node->left = Build(arr, l, m - 1);
		node->right = Build(arr, m + 1, r);
		Update(node);
		return node;
	}

	class Tree {

	public:

		Tree() : m_data(nullptr) {
			this->m_init_random();
		}
		Tree(const std::vector <int>& data) {
			this->m_init_random();
			data.empty() ? this->m_data = nullptr :
			this->m_data = Build(data.data(), 0, data.size() - 1);
		}

		Tree split(int at) {
			assert(this->m_data && 0 <= at && at <= Size(this->m_data));
			if (Size(this->m_data) == 0) {
				return Tree();
			}
			Tree result;
			std::shared_ptr <Node> left, right;
			Split(this->m_data, at, left, right);
			this->m_data = left;
			result.m_data = right;
			return result;
		}

		void merge(Tree& rhs) {
			this->m_data = Merge(this->m_data, rhs.m_data);
			rhs.m_data = nullptr;
		}

		void add_value(int value) {
			if (this->m_data) {
				AddValue(this->m_data, value);
			}
		}

		int get_min_index() {
			assert(this->m_data);
			return GetMinIndex(this->m_data);
		}

		int at(int index) {
			assert(this->m_data && 0 <= index && index < Size(this->m_data));
			return GetValue(this->m_data, index);
		}

		void set(int index, int value) {
			assert(this->m_data && 0 <= index && index < Size(this->m_data));
			SetValue(this->m_data, index, value);
		}

		int size() {
			return Size(this->m_data);
		}

	private:

		std::shared_ptr <Node> m_data;

	private:

		void m_init_random() {
			static bool initialized = false;
			if (!initialized) {
				std::srand(std::time(nullptr));
				initialized = true;
			}
		}

	};

}
