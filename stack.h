// [ Stack Template Implementation ]
/* 
- Stack implementation with push(), pop(), top() operations
- Recreation of C++ STL std::stack
*/

// Structure
/*
class List {

    private:
        {stack, top} 
    
    public:
        -> constructor (default, copy), destructors
        -> empty(), size(), clear()
        -> push() (lhs & rhs), pop(), top (const&, &)
        -> opeartor ==, !=, =

};
*/

// Missing / Problem
/*
-> missing functions, constructors
-> no checks
-> comparator
*/

#ifndef STACK_H
#define STACK_H

#include <iostream>
#include "array.h"

template <typename _type>
class Stack {
    private:
        Array<_type> stack;
        int _top;
    
    public:
        //constructor
        Stack() : _top(-1), stack(0) {};
        Stack(const Stack& st) : stack(st.stack) {
            this->_top = st._top;
        }
        ~Stack() {}

        size_t size() const
            { return _top+1; }
        bool empty() const
            { return (this->size() == 0); }
        void clear() {
            while (!empty())
                { pop(); }
        }
        
        void push(const _type& element) {
            _top++;
            stack.push_back(element);
        }
        void push(_type&& element) {
            _top++;
            stack.push_back(element);
        }
        void pop() {
            if (this->_top == -1)
                { throw std::runtime_error{"underflow"}; }
            stack.pop_back();
            _top--;
        }
        const _type& top() const {
            if (this->_top == -1)
                { throw std::runtime_error{"empty stack"}; }
            return stack[_top];  
        }
        
        //operators
        void operator= (const Stack& st) {
            this->_top = st._top;
            this->stack = st.stack;
        }
        bool operator== (const Stack& st) {
            return (this->stack == st.stack);
        }
        bool operator!= (const Stack& st)
            { return !( (*this)==st ); }
};

#endif // STACK_H