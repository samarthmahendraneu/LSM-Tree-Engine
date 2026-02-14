//
// Created by Samarth Mahendra on 2/13/26.
//

#ifndef MEMTABLE_H
#define MEMTABLE_H



#pragma once

#include <map>
#include <optional>
#include "../types/Entry.h"
#include "../types/internal_key_comparator.h"

class MemTable {
public:
    void put(Key key, Value value, uint64_t seq);
    void remove(Key key, uint64_t seq);
    std::optional<Value> get(const Key& key) const;
    void apply(const Entry& entry);
    size_t size() const;

private:
    std::map<InternalKey, Value, InternalKeyComparator> table_;
};



#endif //MEMTABLE_H
