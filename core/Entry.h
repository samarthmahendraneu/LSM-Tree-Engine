//
// Created by Samarth Mahendra on 2/13/26.
//

#ifndef ENTRY_H
#define ENTRY_H
#include "key.h"
#include "value.h"


class Entry {

    Key key;
    Value value;
    uint64_t seq{};
    // soft delete feature using tombstone
    bool tombstone{};

public:

    Entry(Key key,
      Value value,
      uint64_t seq,
      bool tombstone)
    : key(std::move(key)),
      value(std::move(value)),
      seq(seq),
      tombstone(tombstone) {}


    // Declare friend for access to private members
    friend std::ostream& operator<<(std::ostream& os, const Entry& e);

};
std::ostream& operator<<(std::ostream& os, const Entry& e);
#endif //ENTRY_H

