//
// Created by Samarth Mahendra on 2/15/26.
//

#ifndef DB_H
#define DB_H


#include "../memtable/MemTable.h"
#include "../memtable/MemTableFactory.h"
#include "../types/key.h"
#include "../types/value.h"
#include "../wal/Wal.h"


class DB {

public:

    explicit DB(const std::string& wal_path = "db.wal");

    bool put(const Key &key, const Value &value);
    bool remove(const Key &key);
    [[nodiscard]] std::optional<Value> get(const Key& key) const;
    [[nodiscard]] size_t size() const;
    ~DB() = default;

private:
    void recover();

    std::unique_ptr<IMemTable> memtable_;
    Wal wal_;
    uint64_t next_seq_{1};
};


#endif //DB_H
