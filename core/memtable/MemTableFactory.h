//
// Created by Samarth Mahendra on 2/20/26.
//

#ifndef MEMTABLEFACTORY_H
#define MEMTABLEFACTORY_H


#pragma once

#include <memory>
#include "IMemTable.h"
#include "MemTable.h"
#include "SkipListMemTable.h"

enum class MemTableType {
    TREE,
    SKIPLIST
};

class MemTableFactory {
public:
    static std::unique_ptr<IMemTable> create(MemTableType type) {
        if (type == MemTableType::TREE)
            return std::make_unique<MemTable>();
        return std::make_unique<SkipListMemTable>();
    }
};
#endif //MEMTABLEFACTORY_H
