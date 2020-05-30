//
// Created by rudri on 5/29/2020.
//

#include "clases.h"

#include <utility>

sort_t::sort_t(string  name) : duration_{ 0 }, name_{ std::move(name) } {}

long long sort_t::duration() const {
	return duration_;
}

string sort_t::name() const {
	return name_;
}

void merge_sort_t::operator()(vector<int>& data) {
	auto now_ = steady_clock::now;
	auto start_ = now_();
	merge_sort_(data, 0, data.size() - 1);
	auto end_ = now_();
	duration_ = duration_cast<microseconds>(end_ - start_).count();
}

void merge_sort_t::merge_(vector<int>& data, size_t left, size_t middle, size_t right) {
	vector<int> left_side(middle - left + 1);
	vector<int> right_side(right - middle);

	copy(next(begin(data), left), next(begin(data), middle + 1), begin(left_side));
	copy(next(begin(data), middle + 1), next(begin(data), right + 1), begin(right_side));

	std::merge(begin(left_side), end(left_side), begin(right_side), end(right_side),
		next(begin(data), left));
}

void merge_sort_t::merge_sort_(vector<int>& data, size_t left, size_t right) {
	if (right <= left) return;
	auto middle = (left + right) / 2;
	merge_sort_(data, left, middle);
	merge_sort_(data, middle + 1, right);
	merge_(data, left, middle, right);
}

merge_sort_t::merge_sort_t(string name) : sort_t(name) {
}

void bubble_sort_t::operator()(vector<int>& data) {
	auto now_ = steady_clock::now;
	auto start_ = now_();
	for (size_t i = 0; i < data.size(); ++i)
		for (size_t j = i; j < data.size(); ++j)
			if (data[i] > data[j])
				swap(data[i], data[j]);
	auto end_ = now_();
	duration_ = duration_cast<microseconds>(end_ - start_).count();
}

bubble_sort_t::bubble_sort_t(string name) : sort_t(name) {
}

queue_t::queue_t() : data_{ nullptr }, size_{ 0 } {}

queue_t::~queue_t()
{
	delete[] data_;
}

queue_t::queue_t(const queue_t& other) {
	size_ = other.size_;
	data_ = new sort_t * [size_];
	for (size_t i = 0; i < size_; ++i)
		data_[i] = other.data_[i];
}

queue_t& queue_t::operator=(const queue_t& other) {
	delete[] data_;
	size_ = other.size_;
	data_ = new sort_t * [size_];
	for (size_t i = 0; i < size_; ++i)
		data_[i] = other.data_[i];
	return *this;
}

void queue_t::push(sort_t* sort) {
	auto temp_ = new sort_t * [size_ + 1];
	for (size_t i = 0; i < size_; ++i) {
		temp_[i] = data_[i];
	}
	temp_[size_++] = sort;
	delete[] data_;
	data_ = temp_;
}

void queue_t::pop() {
	auto temp_ = new sort_t * [size_ - 1];
	for (size_t i = 1; i < size_; ++i) {
		temp_[i - 1] = data_[i];
	}
	delete data_[0];
	delete[] data_;
	size_--;
	data_ = temp_;
}

sort_t* queue_t::front() {
	return data_[0];
}

sort_t* queue_t::back() {
	return data_[size_ - 1];
}

bool queue_t::empty() const {
	return size_ == 0;
}

size_t queue_t::size() const {
	return size_;
}

queue_t queue_t::operator+(const queue_t& other) {
	queue_t result_;
	for (size_t i = 0; i < size_; ++i) {
		result_.push(data_[i]);
	}
	for (size_t i = 0; i < other.size_; ++i) {
		result_.push(other.data_[i]);
	}
	return result_;
}

void tester_t::push_method(sort_t* sort) {
	queue_.push(sort);
}

void tester_t::operator()() {
	auto methods_ = queue_;
	while (!methods_.empty()) {
		auto current_ = methods_.front();
		(*current_)(data_);
		cout << "The duration of the method " << current_->name()
			<< " is " << current_->duration() << " ms" << endl;

		methods_.pop();
	}
}

void tester_t::operator<<(const string& filename) {
	ifstream file(filename);
	data_.clear();
	int value_;
	while (file >> value_)
		data_.push_back(value_);
}

ostream& operator<<(ostream& out, tester_t tester) {
	return imprimir_collection(out, tester.data_);
}

bool is_palidrome(string text)
{
	stack<char> reversed;
	string filtered;
	for (const auto& car : text)
		if (tolower(car) >= 'a' && tolower(car) <= 'z') {
			filtered += car;
			reversed.push(car);
		}

	auto iter = begin(filtered);
	while (!reversed.empty())
	{
		if (*iter++ != reversed.top())
			return false;
		reversed.pop();
	}
	return true;
}


