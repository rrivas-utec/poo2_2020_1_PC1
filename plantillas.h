//
// Created by rudri on 5/29/2020.
//

#ifndef POO2_2020_1_PC1_PLANTILLAS_H
#define POO2_2020_1_PC1_PLANTILLAS_H

template<typename T>
class queue {
    T* data_;
    size_t size_;
public:
    queue(): data_{nullptr}, size_{0}{}
    ~queue() {
        delete[] data_;
    }
    queue(const queue<T>& other) {
        size_ = other.size_;
        data_ = new T [size_];
        for (size_t i = 0; i < size_; ++i)
            data_[i] = other.data_[i];
    }

    queue<T> operator=(const queue<T>& other) {
        delete[] data_;
        size_ = other.size_;
        data_ = new T [size_];
        for (size_t i = 0; i < size_; ++i)
            data_[i] = other.data_[i];
        return *this;
    }

    void push(T value) {
        auto temp_ = new T [size_ + 1];
        for (size_t i = 0; i < size_; ++i) {
            temp_[i] = data_[i];
        }
        temp_[size_++] = value;
        delete[] data_;
        data_ = temp_;
    }

    void pop() {
        auto temp_ = new T [size_ - 1];
        for (size_t i = 1; i < size_; ++i) {
            temp_[i - 1] = data_[i];
        }
        delete data_[0];
        delete[] data_;
        size_--;
        data_ = temp_;
    }
    
    T front() {
        return data_[0];
    }
    
    T back() {
        return data_[size_ - 1];
    }
    
    bool empty() const { return size_ == 0; }
    size_t size() const { return size_; }

    queue<T> operator+(const queue<T>& other) {
        queue<T> result_;
        for (size_t i = 0; i < size_; ++i) {
            result_.push(data_[i]);
        }
        for (size_t i = 0; i < other.size_; ++i) {
            result_.push(other.data_[i]);
        }
        return result_;
    }
};

#endif //POO2_2020_1_PC1_PLANTILLAS_H
