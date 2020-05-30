#include <iostream>
#include <sstream>
#include <map>
#include "clases.h"
#include "plantillas.h"

using namespace  std;

void question_1(string filename) {
    tester_t tester;
    tester << filename;
    cout << tester << endl;
    tester.push_method(new bubble_sort_t("bubble"));
    tester.push_method(new merge_sort_t("merge"));
    tester();
    cout << tester << endl;
}

void question_2(string filename) {
    queue<sort_t*> q_1;
    queue<sort_t*> q_2;
    q_1.push(new bubble_sort_t("bubble"));
    q_2.push(new merge_sort_t("merge"));
    auto q_3 = q_1 + q_2;

    vector<int> data_;
    ifstream file(filename);
    data_.clear();
    int value_;
    while (file >> value_)
        data_.push_back(value_);

    imprimir_collection(cout, data_) << endl;

    while (!q_3.empty()) {
        auto current_ = q_3.front();
        (*current_)(data_);
        cout << "The duration of the method " << current_->name()
            << " is " << current_->duration() << " ms" << endl;

        q_3.pop();
    }

    imprimir_collection(cout, data_) << endl;
}

void question_3() {
    cout << boolalpha << is_palidrome("a sd  @ d s __a") << endl;
    cout << boolalpha << is_palidrome("aaalaaa") << endl;
    cout << boolalpha << is_palidrome("aa bb") << endl;
}

void question_4() {
    // variables
    string numbers;
    string indexes;
    int distance = 0;
    int filler = 0;
    
    // input
    getline(cin, indexes);
    getline(cin, numbers);
    cin >> distance >> filler;

    // additional variables
    stringstream snumbers{ numbers };
    stringstream sindexes{ indexes };
    map<int, int> data;
    int value = 0;
    int index = 0;

    // input data
    while (snumbers >> value && sindexes >> index)
        data[--index] = value;

    // processing
    vector<int> result(data.size() + distance * (data.size() - 1), filler);
    auto iter_d = begin(data);
    auto iter_r = begin(result);

    *iter_r++ = (iter_d++)->second;
    while (iter_d != end(data))
    {
        iter_r += distance;
        *iter_r++ = (iter_d++)->second;
    }

    // print data
    imprimir_collection(cout, result);
}

int main() {
    auto size = 20;
    string filename = "data2.txt";
    //generate_data(filename, size, 1, size);
    //question_1(filename);
    //question_2(filename);
    //question_3();
    question_4();
    return 0;
}
