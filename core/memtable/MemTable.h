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
#include "IMemTable.h"

class MemTable : public IMemTable{
public:
    void put(Key key, Value value, uint64_t seq) override;
    void remove(Key key, uint64_t seq) override;
    [[nodiscard]] std::optional<Value> get(const Key& key) const override;
    void apply(const Entry& entry) override;
    [[nodiscard]] size_t size() const override;

private:
    std::map<InternalKey, Value, InternalKeyComparator> table_;
};



#endif //MEMTABLE_H
