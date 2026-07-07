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

				const _data operator*() const {
					return this->pointer->val;
				}

				bool operator==(const Iterator& itr) const {
					return itr.pointer == this->pointer;
				}
				bool operator!=(const Iterator& itr) const {
					return !(*this == itr);   // equivalent to return !(this->operator==(itr));
				}

			private:
				Iterator inorderSuccessor(Iterator itr) const {
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
		void insert(const _data& val) const {
			insert(val, root, nullptr);
		}
		const Iterator begin() const {
			return beginIterator(root);
		}
		const Iterator end() const {
			return Iterator(nullptr);
		}
		bool contains(const _data& val) const {
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

/*
int main() {
	Set<int>* s = new Set<int>();
	s->insert(5);
	s->insert(6);
	s->insert(2);
	auto itr = s->begin();
	std::cout << s->contains(2);
	std::cout << " " << s->contains(10) << std::endl;
	while (itr != s->end()) {
		std::cout << *itr << " ";
		itr++;
	}
}
*/
