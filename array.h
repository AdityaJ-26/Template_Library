// [ Dynamic Array Template Implementation ]
/* 
- Dynamic Array with dynamically growing size & capacity, insertion & deletion operations
- Minimal Bound checks implemented by throw
- Recreation of C++ STL std::vector
*/

// Structure
/*
class Error {
    private:
        { string }
    public:
        -> constructor
        -> what()
}

class List {

    private:
        {theSize, theCapacity, <template>* objects} 
    
    private:
        -> reserve()

    public:
        -> constructor (parameterised, default, copy), destructors
        -> empty(), size(), clear()
        -> insert(), erase()
        -> resize()
        -> push_back() (lhs & rhs), pop_back()
        -> operator [], =, ==, !=

};
*/

// Missing / Problem
/*
-> iterator
-> vector, array comparison
-> sorts
-> error checks
-> comparator
*/

#ifndef ARRAY_H
#define ARRAY_H

#include <string>

constexpr int INITIAL_CAPACITY = 2;

class Error {
    private:
        std::string err;
    public:
        Error(const std::string& err) : err{"_exception_error -> " + err} {}
        Error(std::string&& err) : err{std::move(err)} {}
        Error(const Error& e) : err{e.err} {};
        const std::string& what() 
            { return err; }
};

template <typename _type>
class Array {
    //data members
    private:
        size_t theSize;
        size_t theCapacity;
        _type* objects;
    
    //internal operations
    private:
        void reserve(size_t newCap) {
            if (newCap < theSize) 
                { throw Error{"(Capacity can't be changed) : reserve(newCap), newCap > Array(theSize)"}; }
            theCapacity = newCap;
            _type* newArray = new _type[theCapacity];
            for (size_t i{ 0 }; i<theSize; i++)
                { newArray[i] = objects[i]; }
            delete[] objects;
            objects = newArray;
        }

    public:
        //Constructor & Destructors
        explicit Array() : theSize(0), theCapacity(INITIAL_CAPACITY)
            { this->objects = new _type[theCapacity]; }
        //parameterised
        Array(size_t size = 0) : theSize(size), theCapacity(size+INITIAL_CAPACITY)
            { this->objects = new _type[theCapacity]; }   
        Array(size_t size, const int& initElement) : theSize(size), theCapacity(size+INITIAL_CAPACITY) {
            this->objects = new _type[theCapacity];
            for (size_t i{ 0 }; i<size; i++)
                { objects[i] = initElement; }
        }   
        //copy
        Array(const Array& obj) : theSize(obj.theSize), theCapacity(obj.theCapacity) {
            this->objects = new _type[theCapacity];
            for (size_t i{ 0 }; i<theSize; i++) {
                this->objects[i] = obj.objects[i];
            }
        }
        //Destructor
        ~Array()
            { delete[] objects; }
        
        
        //basic utilities
        size_t size()
            { return theSize; }
        size_t capacity()
            { return theCapacity; }
        bool empty()
            { return size() == 0; }
        void resize(size_t newSize) {
            if (newSize < theSize) 
                { throw Error{"(Array can't be resized) : resize(newSize), newSize < Array(theSize)"}; }
            else { 
                reserve(newSize*2);
                theSize = newSize; 
            }
        }
        void clear() {
            while (!empty())
                { pop_back(); }
        }
        

        //insertion operations
        void push_back(const _type& element) {
            if (theSize == theCapacity)
                { reserve(theSize*2); }
            objects[theSize] = element;
            theSize++;
        }  
        void push_back(_type&& element) {
            if (theSize == theCapacity)
                { reserve(theSize*2); }
            objects[theSize] = std::move(element);
            theSize++;
        }  
        void insert(const size_t index, const _type& element) {
            if (index < 0 || index >= theSize) 
                { throw Error{"(OutofBound) : operator[](index), index !in [0, array.size())"}; }
            if (theSize == theCapacity)
                { reserve(theSize*2); }
            for (size_t j{ theSize }; j>index; j--)
                { objects[j] = objects[j-1]; }
            objects[index] = element;
            theSize++;
        }
        void insert(const size_t index, _type&& element) {
            insert(index, std::move(element));
        }
        //deletion
        void pop_back() { 
            if (theSize == 0)
                { throw Error{"(Underflow) : Array(theSize) < 0"}; }
            theSize--; 
        }
        void erase(const int index) {
            if (index >= theSize || index < 0)
                { throw Error{"(OutofBound) : operator[](index), index !in [0, array.size())"}; }
            for (size_t i{ index }; i<theSize-1; i++)
                { objects[i] = objects[i+1]; }
            theSize--;
        }

        //operators
        const _type& operator[] (const int index) const {
            if (index < 0 || index >= theSize)
                { throw Error{"(OutofBound) : operator[](index), index !in [0, array.size())"}; }
            return objects[index]; 
        }
        _type& operator[] (const int index) { 
            if (index < 0 || index >= theSize)
                { throw Error{"(OutofBound) : operator[](index), index !in [0, array.size())"}; }
            return objects[index]; 
        }
        void operator = (const Array& obj) {
            theSize = obj.theSize;
            theCapacity = obj.theCapacity;
            resize(theCapacity);
            for (size_t i{ 0 }; i<theSize; i++)
                { objects[i] = obj[i]; }
        }
        bool operator == (const Array& obj) {
            if (this->theSize != obj.theSize)
                { return false; }
            for (size_t i{ 0 }; i<theSize; i++) {
                if ((*this)[i] != obj[i])
                    { return false; }
            }
            return true;
        }
        bool operator != (const Array& obj)
            { return ( !(this->operator==(obj)) ); }
};

#endif // ARRAY_H