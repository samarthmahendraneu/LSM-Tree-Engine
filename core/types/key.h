//
// Created by Samarth Mahendra on 2/13/26.
//

#ifndef KEY_H
#define KEY_H
#include <string_view>
#include <iostream>

using namespace std;

class Key {

public:
    explicit Key(std::string_view data) {
        data_ = data;
    }

    string_view bytes() const{
        return data_;
    }

    size_t size() const {
        return data_.size();
    }

    bool operator==(const Key& other) const {
        return this->data_ == other.data_;
    }

    bool operator!=(const Key& other) const {
        return this->data_ != other.data_;
    }



private:
    string data_;


};

#endif //KEY_H
