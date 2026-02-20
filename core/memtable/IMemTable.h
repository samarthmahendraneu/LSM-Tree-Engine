//
// Created by Samarth Mahendra on 2/20/26.
//

#ifndef IMEMTABLE_H
#define IMEMTABLE_H


#pragma once

#include <optional>
#include "../types/Entry.h"

class IMemTable {
public:
    virtual ~IMemTable() = default;

    virtual void put(Key key, Value value, uint64_t seq) = 0;
    virtual void remove(Key key, uint64_t seq) = 0;
    virtual std::optional<Value> get(const Key& key) const = 0;
    virtual void apply(const Entry& entry) = 0;
    virtual size_t size() const = 0;
};

#endif //IMEMTABLE_H
