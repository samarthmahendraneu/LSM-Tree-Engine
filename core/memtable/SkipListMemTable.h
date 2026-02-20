//
// Created by Samarth Mahendra on 2/20/26.
//

#ifndef SKIPLISTMEMTABLE_H
#define SKIPLISTMEMTABLE_H



#pragma once

#include "IMemTable.h"
#include "../types/internal_key_comparator.h"
#include "SkipList.h"

class SkipListMemTable : public IMemTable {
public:
    SkipListMemTable();

    void put(Key key, Value value, uint64_t seq) override;
    void remove(Key key, uint64_t seq) override;
    std::optional<Value> get(const Key& key) const override;
    void apply(const Entry& entry) override;
    size_t size() const override;

private:
    struct Item {
        InternalKey ikey;
        Value value;
    };

    struct Comparator {
        InternalKeyComparator cmp;
        bool operator()(const Item& a, const Item& b) const {
            return cmp(a.ikey, b.ikey);
        }
    };

    SkipList<Item, Comparator> list_;
    size_t size_;
};



#endif //SKIPLISTMEMTABLE_H
