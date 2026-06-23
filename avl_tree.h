// [ AVL Tree Template Implementation ]
/* 
- AVL Tree implementation with insertion, deletion and balancing implementation
*/

// Structure
/*
struct AvlNode() 
    { element, next, prev , height, constructors }

class AvlTree {

    private:
        -> height() - to get height handling the nullptr exception
        -> balance() - method to call specific balancing method
        -> rotateWithLeftChild() - balancing method for imbalance due to insertion in left subtree of left node (LL imbalance)
        -> rotateWithRightChild() - balancing method for imbalance due to insertion in right subtree of right node (RR imbalance)
        -> doubleWithLeftChild() - balancing method for imbalance due to insertion in right subtree of left node (LR imbalance)
        -> doubleWithRightChild() - balancing method for imbalance due to insertion in left subtree of right node (RL imbalance)
        -> findMin() - helper for remove(), returns inorder successor

    public:
        -> insert(element, root) - inserts element(same as BST) and calls balance()
        -> remove(element, root) - removes element and calls balance()
        -> clear(root) - clear, frees the allocated nodes
        -> print(root) - prints tree by level order(morris traversal) for debugging
};
*/

// Missing / Problem
/*
-> seperate node and tree class
*/

/*
*1. >= operator is used for LL and RR imbalance to support deletion logic where deletion from one side(left or right) causes imbalance and the other side have same
no of elements in subtree, eg. if deletion occurs in left part of a node t and causes imbalance at t, and right node of t have equal height subtrees then the balancing
must be done at root with right child (RR imbalance), so >= ensures this.
*/

#ifndef AVL_TREE
#define AVL_TREE

#include <iostream>
#include <algorithm>
#include <queue>

template <typename Comparable>
struct AvlNode {
    Comparable element;
    AvlNode* left;
    AvlNode* right;
    int height;

    AvlNode(const Comparable& ele, AvlNode* lt = nullptr, AvlNode* rt = nullptr, int h = 0) :
        element(ele), left(lt), right(rt), height(h) 
    {}
    AvlNode(Comparable&& ele, AvlNode* lt = nullptr, AvlNode* rt = nullptr, int h = 0) :
        element(std::move(ele)), left(lt), right(rt), height(h)
    {}
};

template <typename Comparable>
class AvlTree {

    static const int ALLOWED_IMBALANCE = 1;

    private:
        int height(AvlNode<Comparable>* t) const
        { return t == nullptr ? -1 : t->height; }
        
        void balance(AvlNode<Comparable>*& t) {
            if (t == nullptr)
                { return; }
            
            if (height(t->left) - height(t->right) > ALLOWED_IMBALANCE) {
                if (height(t->left->left) >= height(t->left->right))                                // *1
                    { rotateWithLeftChild(t); }
                else
                    { doubleWithLeftChild(t); }
            }
            else if (height(t->right) - height(t->left) > ALLOWED_IMBALANCE) {
                if (height(t->right->right) >= height(t->right->left))                              // *1
                    { rotateWithRightChild(t); }
                else 
                    { doubleWithRightChild(t); } 
            }
    
            t->height = std::max(height(t->left), height(t->right)) + 1;
        }

        void rotateWithLeftChild(AvlNode<Comparable>*& k1) {
            AvlNode<Comparable>* k2 = k1->left;
            k1->left = k2->right;
            k2->right = k1; 

            k1->height = std::max(height(k1->left), height(k1->right)) + 1;
            k2->height = std::max(height(k2->right), k1->height) + 1;
            
            k1 = k2;
        }

        void rotateWithRightChild(AvlNode<Comparable>*& k1) {
            AvlNode<Comparable>* k2 = k1->right;
            k1->right = k2->left;
            k2->left = k1;

            k1->height = std::max(height(k1->left), height(k1->right)) + 1;
            k2->height = std::max(height(k2->left), k1->height) + 1;

            k1 = k2;
        }

        void doubleWithLeftChild(AvlNode<Comparable>*& k3) {
            rotateWithRightChild(k3->left);
            rotateWithLeftChild(k3);
        }
        
        void doubleWithRightChild(AvlNode<Comparable>*& k3) {
            rotateWithLeftChild(k3->right);
            rotateWithRightChild(k3);
        }

        Comparable findMin(AvlNode<Comparable>* t) const {
            while (t->left)
                { t = t->left; }
            return t->element;
        }
        
    public:
        void insert(const Comparable& x, AvlNode<Comparable>*& t) {
            if (t == nullptr) {
                t = new AvlNode<Comparable>(x);
                return;
            }
            else if (t->element > x) 
                { insert(x, t->left); }
            else if (t->element < x) 
                { insert(x, t->right); }
            
            balance(t);
        }

        void remove(const Comparable& x, AvlNode<Comparable>*& t) {
            if (t == nullptr)
                { return; }
             
            if (t->element > x)
                { remove(x, t->left); }
            else if (t->element < x)
                { remove(x, t->right); }
            
            else if (t->left != nullptr && t->right != nullptr) {
                t->element = findMin(t->right);
                remove(t->element, t->right);
            }
            else {
                AvlNode<Comparable>* oldNode = t;
                t = (t->left != nullptr) ? t->left : t->right;
                delete oldNode;
            }

            balance(t);
        }

        // functions to free nodes
        void clear(AvlNode<Comparable>*& t) {
            if (t == nullptr)
                { return; }
            clear(t->left);
            clear(t->right);
            delete t;
            t = nullptr;
        }

        // print function to print tree by height
        void print(AvlNode<Comparable>*& t) {
            std::queue<AvlNode<Comparable>*> q;
            q.push(t);
            while (!q.empty()) {
                int q_size = q.size();
                for (int i{ 0 }; i < q_size; i++) {
                    AvlNode<Comparable>* temp = q.front();
                    q.pop();
                    if (temp == nullptr) { 
                        std::cout << " N "; 
                        continue;
                    }
                    else {
                        std::cout << " " << temp->element << " ";
                    }
                    q.push(temp->left);
                    q.push(temp->right);
                }
                std::cout << "\n";
            }
        }
};

/*
// test run
int main() {
    AvlTree<int>* tree = new AvlTree<int>();
    AvlNode<int>* root = nullptr;

    tree->insert(10, root);
    tree->insert(5, root);
    tree->insert(20, root);
    tree->insert(2, root);
    tree->insert(1, root);
    tree->insert(0, root);
    tree->print(root);
    std::cout << '\n';

    tree->remove(0, root);
    tree->remove(1, root);
    tree->print(root);

    tree->clear(root);
    return 0;
}
*/


#endif // ! AVL_TREE