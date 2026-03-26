// [ Binary Search Tree Template Implementation ]
/* 
- BST with insertion, deletion, contains, constructor and destructors
- implemented public operation method with corresponding private recursive functions
- implemented with custom comparator template for comparing values
*/

// Structure
/*
class Comparator {
    operator() - overload
}

class BinarySearchTree {

    private:
        struct BinaryNode() 
            { data, left, right, constructors }

    private:
        { root, Comparator } 
    
    public:
        -> construtors() - parameterised(with default value), copy (& , &&)
        -> operator = 
        -> destructor
        -> isEmpty()
        -> remove() - (&, &&)
        -> insert() - (&, && )
        -> print()
        -> contains() - (&, &&)

    private:
        -> clone()
        -> makeEmpty()
        -> successor()
        -> remove(), insert(), contains() (private recursive functions)
};
*/

// Missing / Problem
/*
-> print()
-> comparator for vector, string, pointers, etc
-> custom comparator support
-> implementation for duplicates
*/

#ifndef BINARY_SEARCH_TREE
#define BINARY_SEARCH_TREE

#include <string>
#include <iostream>

class Error {
    private:
        std::string errStatement;
    public:
        Error( const std::string& err ) 
            : errStatement{"_exceptional_error_ : " + err} {}
        Error( std::string&& err ) 
            : errStatement{"_exceptional_error_ : " + std::move( err )} {}
        const std::string& what()
            { return errStatement; }
};

template <typename Comparable>
class Comparator {
    public:
        bool operator()( const Comparable& x, const Comparable& y ) const
            { return ( x < y ); }
};

template <typename _type>
class BinarySearchTree {

    private:
            struct BinaryNode {
                _type data;
                BinaryNode* left;
                BinaryNode* right;
                
                BinaryNode( const _type& data, BinaryNode* left = nullptr, BinaryNode* right = nullptr )
                    : data{ data },
                    left{ left },
                    right{ right } 
                {}
                BinaryNode( _type&& data, BinaryNode* left = nullptr, BinaryNode* right = nullptr )
                    : data{ std::move(data) },
                    left{ left },
                    right{ right }
                {}
            };

    private:
            BinaryNode* root;
            Comparator<_type> isLessThan;


    public:
            // constructors
            BinarySearchTree( BinaryNode* root = nullptr ) 
                : root(root), isLessThan() { }
            BinarySearchTree( const BinarySearchTree& bst ) 
                { this->root = clone(bst.root); }
            ~BinarySearchTree()
                { this->makeEmpty(root); }
            
            // inserting public methods (calling private recursive methods)
            void insert( const _type& element )
                { insert( element, this->root ); }
            void insert( _type&& element )
                { insert( element, this->root ); }

            bool isEmpty() const
                { return (this->root == nullptr); }

            // public contains
            bool contains( const _type& element ) const
                { return contains( element, root ); }

            void operator=( const BinarySearchTree& bst )
                { this->root = clone(bst.root); }
            
            // void print() const
            //     { print(this->root, std::ostream()); }
            
            // remove method
            void remove( const _type& element )
                { remove( element, this->root ); }
            void remove( _type&& element )
                { remove( element, this->root ); }

    private:
            // clone to copy one tree to another (used by copy constructor and =)
            BinaryNode* clone( BinaryNode* t ) {
                if (t == nullptr)
                    { return t; }
                else {
                    return new BinaryNode{ t->data, clone(t->left), clone(t->right) };
                }
            }
            
            // used by ~BinarySearchTree
            void makeEmpty( BinaryNode* t ) {
                if (t == nullptr)
                    { return; }
                else {
                    makeEmpty( t->left );
                    makeEmpty( t->right );
                    delete t;
                }
                t = nullptr;
            }
            
            // method for finding leftmost element of Node (inorder successor) (used by remove)
            BinaryNode* successor( BinaryNode* t ) const {
                if ( t != nullptr ) {
                    while ( t->left != nullptr )
                        t = t->left;
                }
                return t;
            }

            // private recursive functions
            void insert( const _type& value, BinaryNode*& t ) {
                if (t == nullptr)
                    { t = new BinaryNode(value); }
                else if ( isLessThan(value, t->data) )
                    { insert( value, t->left ); }
                else if ( isLessThan(t->data, value) )
                    { insert( value, t->right ); }
            }

            void insert( _type&& value, BinaryNode*& t ) {
                if ( t == nullptr )
                    { t = new BinaryNode(value); }
                else if ( isLessThan(value, t->data) )
                    { insert( value, t->left ); }
                else if ( isLessThan(t->data, value) )
                    { insert( value, t->right ); }
            }

            bool contains( const _type& value, BinaryNode* t) const {
                if (t == nullptr) 
                    { return false; }
                if ( isLessThan(value, t->data) )
                    { return contains(value, t->left); }
                if ( isLessThan(t->data, value) )
                    { return contains(value, t->right); }
                else 
                    { return true; }
            }

            // void print( const BinaryNode* t, std::ostream& out ) const {
            //     if (t == nullptr) return;
            //     print(t->left, out);
            //     out << t->data << " ";
            //     print(t->right, out);
            // }

            // recursive remove
            void remove(const _type& value, BinaryNode*& t) {
                if (t == nullptr)
                    { return; }
                else if ( isLessThan(value, t->data) ) {
                    remove( value, t->left );
                }
                else if ( isLessThan(t->data, value) ) {
                    remove( value, t->right );
                }
                else {
                    if ( t->left != nullptr && t->right != nullptr ) {
                        t->data = successor(t->right)->data;
                        remove( t->data, t->right );
                    }
                    else {
                        BinaryNode* del = t;
                        t = (t->left != nullptr) ? (t->left) : (t->right);
                        delete(del);
                    }
                }
            }
};

#endif // BINARY_SEARCH_TREE