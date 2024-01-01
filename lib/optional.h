#ifndef OPTIONAL_H
#define OPTIONAL_H

/**
 * opt (optional, shortened for ease of typing) objects are used to pass around 
 * nullable objects. They provide explicit boolean conversion and access to the
 * underlying object through a reference. The contained type must implement the
 * copy constructor.
 */
template<typename T>
class opt {
private:
    
    T* _value;

public:

    opt() : _value(nullptr) {}

    opt(const T& value) {
        _value = new T(value); // copy ctor
    }

    opt(T&& value) {
        _value = new T(value); // copy ctor
    }

    opt(const opt<T>& other) {
        _value = new T(*other._value); // copy ctor
    }

    opt(opt<T>&& other) {
        _value = new T(*other._value); // copy ctor
    }

    opt<T>& operator=(const opt<T>& rhs) {
        if (this != &rhs) {
            if (_value != nullptr) delete _value;
            _value = new T;
            *_value = *rhs._value;
        }
        return *this;
    }

    opt<T>& operator=(opt<T>&& rhs) {
        if (_value != nullptr) delete _value;
        _value = new T;
        *_value = *rhs._value;
        return *this;
    }

    ~opt() {
        delete _value;
    }

    T& ref() {
        return *_value;
    }

    T* ptr() {
        return _value;
    }

    explicit operator bool() const {
        return (_value != nullptr);
    }

    static opt<T> none() {
        return opt<T>();
    }
};

#endif // OPTIONAL_H
