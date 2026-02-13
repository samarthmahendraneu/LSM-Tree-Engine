//
// Created by Samarth Mahendra on 2/13/26.
//

#include "Entry.h"

std::ostream& operator<<(std::ostream& os, const Entry& e) {
    os << "key: " << e.key.bytes()
       << ", value: " << e.value.bytes()
       << ", seq: " << e.seq
       << ", tombstone: " << e.tombstone;
    return os;
}
