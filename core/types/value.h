//
// Created by Samarth Mahendra on 2/13/26.
//

#ifndef VALUE_H
#define VALUE_H
#include <string>
#include <string_view>
using namespace std;

class Value {
public:
    Value() = default;

    explicit Value(std::string_view data)
    : data_(data) {}

    std::string_view bytes() const {
        return data_;
    }

    size_t size() const {
        return data_.size();
    }

    bool empty() const {
        return data_.empty();
    }
private:
    string data_;
};


#endif //VALUE_H
