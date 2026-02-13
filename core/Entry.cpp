//
// Created by Samarth Mahendra on 2/13/26.
//

#include "Entry.h"

inline const char* value_type_to_string(ValueType t) {
    switch (t) {
        case ValueType::PUT:    return "PUT";
        case ValueType::DELETE: return "DELETE";
    }
    return "UNKNOWN";
}

std::ostream& operator<<(std::ostream& os, const Entry& e) {
    os << "key: " << e.ikey.user_key().bytes()
       << ", value: " << e.value.bytes()
       << ", seq: " << e.ikey.sequence()
    << ", type: " << value_type_to_string(e.ikey.type());
    return os;
}
