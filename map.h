#include <iostream>

template <typename _data>
class Set {
	// nested classes
	private:
		struct TreeNode {
				_data val;
				TreeNode* parent;
				TreeNode* left;
				TreeNode* right;

				TreeNode(const _data& val, TreeNode* parent, TreeNode* left = nullptr, TreeNode* right = nullptr) : val(val), parent(parent), left(left), right(right) {}
		};
	
	// data members (root)
	private:
		TreeNode* root;
	
	public:
		class Iterator {
			private:
				TreeNode* pointer;
			public:
				Iterator(TreeNode* root) : pointer(root) {};

				Iterator operator++(int) {
					Iterator temp = *this;
					++(*this);
					return temp;
				}
				Iterator operator++() {
					if (this->pointer == nullptr) return *this;
					*this = inorderSuccessor(*this);
					return *this;
				}

				_data operator*() {
					return this->pointer->val;
				}

				bool operator==(const Iterator& itr) const {
					return itr.pointer == this->pointer;
				}
				bool operator!=(const Iterator& itr) const {
					return !(*this == itr);   // equivalent to return !(this->operator==(itr));
				}

			private:
				Iterator inorderSuccessor(Iterator itr) {
					if (itr.pointer->right) {
						itr.pointer = itr.pointer->right;
						while (itr.pointer->left) {
							itr.pointer = itr.pointer->left;
						}
					}
					else {
						TreeNode* p = itr.pointer->parent;
						while (p && p->right == itr.pointer) {
							itr.pointer = p;
							p = p->parent;
						}
						itr.pointer = p;
					}
					return itr;
				}
		};
	
	// public functions
	public:
		Set() : root(nullptr) {}
		~Set() {
			deleteTree(root);
		}
		void insert(const _data& val) {
			insert(val, root, nullptr);
		}
		const Iterator begin() {
			return beginIterator(root);
		}
		const Iterator end() {
			return Iterator(nullptr);
		}
		bool contains(const _data& val) {
			return contains(val, root);
		}

	// private recursive implmentations of public functions
	private:
		void deleteTree(TreeNode* root) {
			if (root == nullptr) return;
			deleteTree(root->left);
			deleteTree(root->right);
			delete root;
			root = nullptr;	 
		}

		void insert(const _data& val, TreeNode*& root, TreeNode* parent) {
			if (root == nullptr) {
				root = new TreeNode(val, parent);
				return;
			}
			if (root->val > val) {
				insert(val, root->left, root);
			}
			else if (root->val < val) {
				insert(val, root->right, root);
			}
		}

		Iterator beginIterator(TreeNode* root) {
			if (root == nullptr) return Iterator(nullptr);
			while (root->left) {
				root = root->left;
			}
			return Iterator(root);
		}

		bool contains(const _data& val, TreeNode* root) {
			if (root == nullptr) return false;
			else if (root->val > val) return contains(val, root->left);
			else if (root->val < val) return contains(val, root->right);
			else return true;
		}
};

template <typename _data1, typename _data2>
struct Pair {
	_data1 key;
	_data2 value;

	Pair(const _data1& key, const _data2& value) : key(key), value(value) {}

	bool operator >(const Pair& p) {
		return this->value  > p.value;
	}
	bool operator <(const Pair& p) {
		return this->value < p.value;
	}
	bool operator ==(const Pair& p) {
		return (this->value == p.value);
	}
	bool operator !=(const Pair& p) {
		return !(*this == p);
	}	
			
	const _data1 first() {
		return this->key;
	}
	const _data2 second() {
		return this->value;
	}
};

/*
int main() {
	Set<Pair<char, int>>* map = new Set<Pair<char, int>>();
	map->insert(Pair<char, int>('a', 10));
	map->insert(Pair<char, int>('j', 9));
	std::cout << map->contains(Pair<char, int>('c', 0)) << std::endl;
	map->insert(Pair<char, int>('c', 5));
	auto itr = map->begin();
	while (itr != map->end()) {
		std::cout << (*itr).first() << " " << (*itr).second() << std::endl;
		itr++;
	}
	return 0;
}
*/
