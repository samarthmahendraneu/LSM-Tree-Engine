//
// Created by Samarth Mahendra on 2/13/26.
//

#include <ostream>
#include "internal_key.h"

std::ostream& operator<<(std::ostream& os, const InternalKey& k) {
    os << "InternalKey("
       << k.user_key().bytes()
       << ", seq=" << k.sequence()
       << ", type=" << (k.type() == ValueType::PUT ? "PUT" : "DELETE")
       << ")";
    return os;
}
