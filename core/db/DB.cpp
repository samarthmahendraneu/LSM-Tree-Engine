//
// Created by Samarth Mahendra on 2/15/26.
//

#include "DB.h"

#include <algorithm>


//constructor
DB::DB(const std::string& wal_path)
    : memtable_(MemTableFactory::create(MemTableType::SKIPLIST)),
      wal_(wal_path) {
    recover();
}

// Recovery
// rebuild MemTable from WAL
void DB::recover() {
    auto entries = wal_.replay();

    uint64_t max_seq = 0;

    for (const auto& e : entries) {
        memtable_->apply(e);
        max_seq = std::max(max_seq, e.ikey.sequence());
    }

    // Ensure new writes always have higher sequence
    next_seq_ = max_seq + 1;
}

// PUT operation
bool DB::put(const Key& key, const Value& value) {
    Entry entry(key, value, next_seq_++, false);

    wal_.append(entry);     // durability first
    memtable_->apply(entry); // then in-memory state

    return true;
}

// DELETE operation
bool DB::remove(const Key& key) {
    Entry entry(key, Value{}, next_seq_++, true);

    wal_.append(entry);
    memtable_->apply(entry);

    return true;
}

// GET operation
std::optional<Value> DB::get(const Key& key) const {
    return memtable_->get(key);
}

// Debug helper
size_t DB::size() const {
    return memtable_->size();
}

