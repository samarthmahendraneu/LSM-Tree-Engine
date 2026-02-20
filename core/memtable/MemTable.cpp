//
// Created by Samarth Mahendra on 2/13/26.
//

#include "MemTable.h"
#include <limits>


void MemTable::put(Key key, Value value, uint64_t seq) {
    table_.emplace(
        InternalKey(std::move(key), seq, ValueType::PUT),
        std::move(value)
    );
}

void MemTable::remove(Key key, uint64_t seq) {
    table_.emplace(
        InternalKey(std::move(key), seq, ValueType::DELETE),
        Value{}
    );
}

std::optional<Value> MemTable::get(const Key& user_key) const {
    if (table_.empty()) return std::nullopt;

    InternalKey seek_key(
        Key(user_key.bytes()),
        std::numeric_limits<uint64_t>::max(),
        ValueType::PUT
    );

    auto it = table_.lower_bound(seek_key);
    if (it == table_.end()) return std::nullopt;

    if (it->first.user_key().bytes() != user_key.bytes()) {
        return std::nullopt;
    }

    if (it->first.type() == ValueType::DELETE) {
        return std::nullopt;
    }

    return it->second;
}

void MemTable::apply(const Entry& entry) {
    if (entry.ikey.type() == ValueType::PUT) {
        put(entry.ikey.user_key(), entry.value, entry.ikey.sequence());
    } else {
        remove(entry.ikey.user_key(), entry.ikey.sequence());
    }
}


size_t MemTable::size() const {
    return table_.size();
}
