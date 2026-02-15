#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <iostream>
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
class DynamicArray {
    //data members
    private:
        size_t theSize;
        size_t theCapacity;
        _type* objects;
    
    //internal operations
    private:
        void reserve(size_t newCap) {
            if (newCap < theSize) 
                { throw Error{"(Capacity can't be changed) : reserve(newCap), newCap > DynamicArray(theSize)"}; }
            theCapacity = newCap;
            _type* newArray = new _type[theCapacity];
            for (size_t i{ 0 }; i<theSize; i++)
                { newArray[i] = objects[i]; }
            delete[] objects;
            objects = newArray;
        }

    public:
        //Constructor & Destructors
        explicit DynamicArray() : theSize(0), theCapacity(INITIAL_CAPACITY)
            { this->objects = new _type[theCapacity]; }
        //parameterised
        DynamicArray(size_t capacity = 0) : theSize(0), theCapacity(capacity+INITIAL_CAPACITY)
            { this->objects = new _type[theCapacity]; }   
        DynamicArray(size_t size, const int& initElement) : theSize(size), theCapacity(size+INITIAL_CAPACITY) {
            this->objects = new _type[theCapacity];
            for (size_t i{ 0 }; i<size; i++)
                { objects[i] = initElement; }
        }   
        //copy
        DynamicArray(const DynamicArray& obj) : theSize(obj.theSize), theCapacity(obj.theCapacity) {
            this->objects = new _type[theCapacity];
            for (size_t i{ 0 }; i<theSize; i++) {
                this->objects[i] = obj.objects[i];
            }
        }
        //Destructor
        ~DynamicArray()
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
                { throw Error{"(Array can't be resized) : resize(newSize), newSize < DynamicArray(theSize)"}; }
            else { 
                reserve(newSize*2);
                theSize = newSize; 
            }
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
        void insert(const size_t index, const _type element) {
            if (index < 0 || index >= theSize) 
                { throw Error{"(OutofBound) : operator[](index), index !in [0, theSize)"}; }
            if (theSize == theCapacity)
                { reserve(theSize*2); }
            for (size_t j{ theSize }; j>index; j++)
                { objects[j] = objects[j-1]; }
            objects[index] = element;
            theSize++;
        }
        //deletion
        void pop_back() { 
            if (theSize == 0)
                { throw Error{"(Underflow) : DynamicArray(theSize) < 0"}; }
            theSize--; 
        }
        void erase(const int index) {
            if (index >= theSize || index < 0)
                { throw Error{"(OutofBound) : operator[](index), index !in [0, theSize)"}; }
            for (size_t i{ index }; i<theSize-1; i++)
                { array[i] = array[i+1]};
            theSize--;
        }

        //operators
        const _type& operator[] (const int index) const {
            if (index < 0 || index >= theSize)
                { throw Error{"(OutofBound) : operator[](index), index !in [0, theSize)"}; }
            return objects[index]; 
        }
        _type& operator[] (const int index) { 
            if (index < 0 || index >= theSize)
                { throw Error{"(OutofBound) : operator[](index), index !in [0, theSize)"}; }
            return objects[index]; 
        }
        void operator = (const DynamicArray& obj) {
            theSize = obj.theSize;
            theCapacity = obj.theCapacity;
            resize(theCapacity);
            for (size_t i{ 0 }; i<theSize; i++)
                { objects[i] = obj[i]; }
        }
};

#endif // DYNAMIC_ARRAY_H