//
// Created by Samarth Mahendra on 2/13/26.
//

#ifndef ENTRY_H
#define ENTRY_H
#include "value.h"
#include "internal_key.h"


class Entry {

    InternalKey ikey;
    Value value;

public:

    Entry(Key key,
          Value value,
          uint64_t seq,
          bool tombstone)
        : ikey(
              std::move(key),
              seq,
              tombstone ? ValueType::DELETE : ValueType::PUT
          ),
          value(std::move(value)) {}


    // Declare friend for access to private members
    friend std::ostream& operator<<(std::ostream& os, const Entry& e);

};
std::ostream& operator<<(std::ostream& os, const Entry& e);
#endif //ENTRY_H

