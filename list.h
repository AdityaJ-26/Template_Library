// [ Doubly Linked List Template Implementation ]

// Structure
/*
class List {

    private:
        struct Node() 
            { data, next, prev , constructors }

    private:
        { _size, head, tail } 
    
    public:
        -> init() - initialiser for List members
        -> construtors() - default, parameterised, copy (& , &&)
        -> operator = 
        -> destructor
        -> empty(), clear(), size()
        -> push_back(), push_front() - (&, &&) ||  pop_back(), pop_back()
        -> insert() - (&, && ) || erase(), erase(ranged)
        -> front(), end()

        class const_iterator {
            public:
                -> default constructor
                -> operator*, ==, !=, ++ (post&pre)
                -> 
            protected:
                { Node* current }
                -> parameterised constructor
                -> retrieve()
            friend List<_type>
        };
        class iterator public:const_iterator {
            public:
                -> operator* (mutator and accessor)
            protected:
                -> parametrised constructor
        };
};
*/

// Missing 
/*
-> print()
->
*/

#ifndef LIST_H
#define LIST_H

#include <iostream>

template <typename _type>
class List{
    private:
        struct Node {
            _type data;
            Node* next;
            Node* prev;
            Node(const _type& d = _type{}, Node* n = nullptr, Node* p = nullptr) : 
                                            data{d}, next{n}, prev{p} {}
            Node(_type&& d, Node* n = nullptr, Node* p = nullptr) :
                                             data{std::move(d)}, next{n}, prev{p} {}
        };

    public:
        class const_iterator;
        class iterator;

        //iterator functions
        iterator begin() 
            { return iterator{this->head->next}; }
        const_iterator begin() const
            { return const_iterator{this->head->next}; }
        iterator end()
            { return iterator{this->tail}; }
        const_iterator end() const
            { return const_iterator{this->tail}; }

        //list manipulators
        _type& front() 
            { return *begin(); }
        _type& back()
            { return *(--end()); }
        const _type& front() const 
            { return *begin(); }
        const _type& back() const
            { return *(--end()); }
        void push_front(const _type& obj)
            { insert(begin(), obj); }
        void push_front(_type&& obj)
            { insert(begin(), std::move(obj)); }
        void pop_front()
            { erase(begin()); }
        void push_back(const _type& obj)
            { insert(end(), obj); }
        void push_back(_type&& obj)
            { insert(end(), std::move(obj)); }
        void pop_back()
            { erase(end()); }

        // initialiser
        void init() {
            this->_size = 0;
            this->head = new Node;
            this->tail = new Node;
            head->next = tail;
            tail->prev = head;
        }
        // big-five
        List()
            { init(); }
        List(const List& l) {
            init();
            for (auto& x : l) 
                this->push_back(begin(), x);
        }
        List(List&& l) : _size{ l._size }, head{ l.head }, tail{ l.tail } {
            l._size = 0;
            l.head = nullptr;
            l.tail = nullptr;
        }
        List& operator = (const List& l) {
            List copy = l;
            std::swap(*this, copy);
            return *this;
        }
        List& operator = (List&& l) {
            std::swap(_size, l._size);
            std::swap(head, l.head);
            std::swap(tail. l.tail);
            return *this;
        }
        ~List() {
            clear();
            delete head;
            delete tail;
        }

        // common functions
        int size() const
            { return this->_size; }
        bool empty() const
            { return (this->size() == 0); }
        void clear() {
            while (!this->empty()) {
                pop_front();
            }
        }
        
        //const_iterator
        class const_iterator {
            public:
                const_iterator() = default;
                //operator overloading
                const _type& operator* () const
                    { return this->retrieve(); }
                const_iterator& operator++ () {
                    current = current->next;
                    return *this;
                }
                const_iterator operator++ (int) {
                    const_iterator retPtr = *this;
                    ++(*this);
                    return retPtr;
                }
                bool operator== (const const_iterator& itr)
                    { return (this->current = itr.current); }
                bool operator!= (const const_iterator& itr)
                    { return !(*this == itr); }
            protected:
                Node* current;
                const_iterator(Node* ptr) : current{ptr} {}
                _type& retrieve()
                    { return this->current->data; }
            friend class List<_type>;   //friend so that List can access protected members
        };

        // iterator
        class iterator : public const_iterator {
            public:
                // operator redefined to give mutator values
                _type& operator* () 
                    { return const_iterator::retrieve(); }
                const _type& operator* () const
                    { return const_iterator::operator*(); }
            protected:
                iterator(Node* ptr) : const_iterator{ptr} {}
            friend class List<_type>;
        };
        
        // insert function - adds at index; returns index of new Object added
        iterator insert(iterator itr, const _type& obj) {
            Node* p = itr.current;
            Node* newNode = new Node(obj, itr, itr->prev);
            p->prev->next = p->prev = newNode;
            this->_size++;
            return iterator(newNode);
        }
        // insert for rvalue
        iterator insert(iterator itr, _type&& obj) {
            Node* p = itr.current;
            Node* newNode = new Node(std::move(obj));
            p->prev->next = p->prev = newNode;
            this->_size++;
            return iterator(newNode);
        }
        // erase - remove current node and returns next node iterator
        iterator erase(iterator itr) {
            Node* temp = itr.current;
            iterator retItr{ temp->next };
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
            delete temp;
            this->_size--;
            return retItr;
        }
        // erase - ranged
        iterator erase(iterator start, iterator& end) {
            while(start != end) {
                start = erase(start);
            }
            return end;
        }
    private:
        size_t _size;
        Node* head;
        Node* tail;
};

#endif //LIST_H