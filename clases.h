//
// Created by rudri on 5/29/2020.
//

#ifndef POO2_2020_1_PC1_CLASES_H
#define POO2_2020_1_PC1_CLASES_H
#include <vector>
#include <string>
#include <chrono>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <random>
#include <stack>

using namespace std;
using namespace std::chrono;

class sort_t {
protected:
    string name_;
    long long duration_;
public:
    explicit sort_t(string  name);
    virtual ~sort_t() = default;
    virtual void operator()(vector<int>& data) = 0;
    long long duration() const;
    string name() const;
};

class merge_sort_t: public sort_t {
    static void merge_(vector<int>& data, size_t left, size_t middle, size_t right);
    void merge_sort_(vector<int>& data, size_t left, size_t right);
public:
    merge_sort_t(string name);
    void operator()(vector<int>& data) override;
};

class bubble_sort_t: public sort_t {
public:
    bubble_sort_t(string name);
    void operator()(vector<int>& data) override;
};

class queue_t {
    sort_t** data_;
    size_t size_;
public:
    queue_t();
    ~queue_t();
    queue_t(const queue_t& other);
    queue_t& operator=(const queue_t& other);
    void push(sort_t* sort);
    void pop();
    sort_t* front();
    sort_t* back();
    bool empty() const;
    size_t size() const;
    queue_t operator+(const queue_t& other);
};

class tester_t {
    queue_t queue_;
    vector<int> data_;
public:
    tester_t() = default;
    void push_method(sort_t* sort);
    void operator()();
    void operator <<(const string& filename);
    friend ostream& operator <<(ostream& out, const tester_t tester);
};

template <typename T>
auto get_random(T first, T last) {
    random_device rd;
    default_random_engine eng(rd());

    if constexpr (is_integral_v<T>)
    {
        uniform_int_distribution<T> dis(first, last);
        return dis(eng);
    }
    else
    {
        uniform_real_distribution<T> dis(first, last);
        return dis(eng);
    }
}

template<typename T>
void generate_data(string filename, size_t quantity, T first, T last) {
    ofstream file(filename);
    for (int i = 0; i < quantity; ++i)
        file << get_random(first, last) << endl;
}

template<typename T>
ostream& imprimir_collection(ostream& out, T data) {
    out << "[";
    auto iter_ = begin(data);
    out << *iter_++;
    while (iter_ != end(data))
        out << ", " << *iter_++;
    out << "]";
    return out;
}

bool is_palidrome(string text);



#endif //POO2_2020_1_PC1_CLASES_H
