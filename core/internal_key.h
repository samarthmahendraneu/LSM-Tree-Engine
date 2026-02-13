//
// Created by Samarth Mahendra on 2/13/26.
//

#ifndef INTERNAL_KEY_H
#define INTERNAL_KEY_H


#pragma once

#include <cstdint>
#include "key.h"
#include "value_type.h"

class InternalKey {
public:
    InternalKey(Key user_key,
                uint64_t sequence,
                ValueType type)
        : user_key_(std::move(user_key)),
          sequence_(sequence),
          type_(type) {}

    const Key& user_key() const { return user_key_; }
    uint64_t sequence() const { return sequence_; }
    ValueType type() const { return type_; }

private:
    Key user_key_;
    uint64_t sequence_;
    ValueType type_;
};


#endif //INTERNAL_KEY_H
