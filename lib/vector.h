#ifndef VECTOR_H
#define VECTOR_H

#define VECTOR_DEFAULT_SIZE 10

#include <cstring> // memmove

template<typename T>
class vector {
private:

    T* _values;
    unsigned int _length;
    unsigned int _tail;

public:

    vector() : 
        _values(nullptr),
        _length(VECTOR_DEFAULT_SIZE),
        _tail(0)
    {
        _allocate(&_values);
    }

    vector(unsigned int reserve) : 
        _values(nullptr),
        _length(reserve),
        _tail(0)
    {
        _allocate(&_values);
    }

    vector(const vector<T>& other) {
        this->_values = nullptr;
        this->_length = other._length;
        this->_tail = other._tail;
        _allocate(&_values);
        other._copy_elements(this->_values);
    }

    vector(vector<T>&& other) {
        this->_values = nullptr;
        this->_length = other._length;
        this->_tail = other._tail;
        _allocate(&_values);
        other._copy_elements(this->_values);

        delete[] other._values;
        other._length = 0;
        other._tail = 0;
    }

    vector<T>& operator= (const vector<T>& rhs) {
        if (this != &rhs) {
            this->_values = nullptr;
            this->_length = rhs._length;
            this->_tail = rhs._tail;
            _allocate(&_values);
            rhs._copy_elements(this->_values);
        }
        return *this;
    }

    vector<T>& operator= (vector<T>&& rhs) {
        if (this != &rhs) {
            this->_values = nullptr;
            this->_length = rhs._length;
            this->_tail = rhs._tail;
            _allocate(&_values);
            rhs._copy_elements(this->_values);

            delete[] rhs._values;
            rhs._length = 0;
            rhs._tail = 0;
        }
        return *this;
    }

    ~vector() {
        delete[] _values;
    }

    void append(const T& item) {
        if (_tail == _length) {
            _expand();
        }
        T copy(item); // copy ctor
        memmove(_values + _tail++, static_cast<void*>(&copy), sizeof(T));
        
        // *(_values + _tail++) = item; // assignment operator
    }

    void append(T&& item) {
        if (_tail == _length) {
            _expand();
        }
        T copy(item); // copy ctor
        memmove(_values + _tail++, static_cast<void*>(&copy), sizeof(T));

        // *(_values + _tail++) = item; // assignment operator
    }

    void prepend(const T& item) {
        if (_tail == _length) {
            _expand();
        }
        _copy_elements(_values + 1);

        T copy(item); // copy ctor
        memmove(_values, static_cast<void*>(&copy), sizeof(T));

        // *_values = item; // assignment operator
        
        _tail++;
    }

    void prepend(T&& item) {
        if (_tail == _length) {
            _expand();
        }
        _copy_elements(_values + 1);

        T copy(item); // copy ctor
        memmove(_values, static_cast<void*>(&copy), sizeof(T));

        // *_values = item; // assignment operator
        
        _tail++;
    }

    void insert(unsigned int index, const T& item) {
        if (_tail == _length) {
            _expand();
        }
        if (_tail != 0) {
            _copy_sub_elements(_values + (index + 1), index, _tail);
        }

        T copy(item); // copy ctor
        memmove(_values + index, static_cast<void*>(&copy), sizeof(T));

        // *(_values + index) = item; // assignment operator
        
        _tail++;
    }

    void insert(unsigned int index, T&& item) {
        if (_tail == _length) {
            _expand();
        }
        if (_tail != 0) {
            _copy_sub_elements(_values + (index + 1), index, _tail);
        }

        T copy(item); // copy ctor
        memmove(_values + index, static_cast<void*>(&copy), sizeof(T));

        // *(_values + index) = item; // assignment operator
        
        _tail++;
    }

    void clear() {
        _tail = 0;
    }

    T& operator[](int index) {
        return *(_values + index);
    }

    unsigned int size() {
        return _tail;
    }

    unsigned int capacity() {
        return _length;
    }

    class Iterator {
    private:
        T* m_ptr;
    public:
        Iterator(T* v) : m_ptr(v) {}
        T& operator*() { return *m_ptr; }
        T* operator->() { return m_ptr; }
        void operator++() { m_ptr++; }
        bool operator!=(const Iterator& rhs) { return m_ptr != rhs.m_ptr; }
    };

    Iterator begin() const { return Iterator(_values); }
    Iterator end() const { return Iterator(_values + _tail); }

private:

    // Copy entire array pointed to by this->_value to new address
    void _copy_elements(T* ptr) {
        // int ix = _tail;
        // while (ix >= 0) {
        //     *(ptr + ix) = *(this->_values + ix); // assignment operator
        //     ix--;
        // }
        memmove(ptr, this->_values, sizeof(T) * this->_tail);
    }

    // Copy a subset of the array pointed to by this->_values to a new address
    void _copy_sub_elements(T* ptr, int start, int end) {
        // start/end are implicitly converted to signed ints for start = 0 case
        
        // int ix = end;
        // while (ix >= start) {
        //     *(ptr + (ix - start)) = *(this->_values + ix); // assignment operator
        //     ix--;
        // }

        memmove(ptr, this->_values + start, sizeof(T) * (end - start));
    }

    void _allocate(T** ptr) {
        *ptr = reinterpret_cast<T*>(new unsigned char[_length * sizeof(T)]);
    }

    void _expand() {
        _length *= 2;
        T* tmp = nullptr;
        _allocate(&tmp);
        _copy_elements(tmp);
        delete[] _values;
        _values = tmp;
    }

};

#endif // VECTOR_H
