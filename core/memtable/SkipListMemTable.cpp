//
// Created by Samarth Mahendra on 2/20/26.
//

#include "SkipListMemTable.h"
#include "SkipListMemTable.h"
#include <limits>

SkipListMemTable::SkipListMemTable()
    : list_(Comparator{}), size_(0) {}

void SkipListMemTable::put(Key key, Value value, uint64_t seq) {
    Item item{
        InternalKey(std::move(key), seq, ValueType::PUT),
        std::move(value)
    };
    list_.insert(item);
    ++size_;
}

void SkipListMemTable::remove(Key key, uint64_t seq) {
    Item item{
        InternalKey(std::move(key), seq, ValueType::DELETE),
        Value{}
    };
    list_.insert(item);
    ++size_;
}

std::optional<Value> SkipListMemTable::get(const Key& user_key) const {
    InternalKey seek_key(
        Key(user_key.bytes()),
        std::numeric_limits<uint64_t>::max(),
        ValueType::PUT
    );

    Item seek{seek_key, Value{}};

    auto node = list_.lower_bound(seek);
    if (!node) return std::nullopt;

    const Item& found = node->key.value();

    if (found.ikey.user_key().bytes() != user_key.bytes())
        return std::nullopt;

    if (found.ikey.type() == ValueType::DELETE)
        return std::nullopt;

    return found.value;
}

void SkipListMemTable::apply(const Entry& entry) {
    if (entry.ikey.type() == ValueType::PUT)
        put(entry.ikey.user_key(), entry.value, entry.ikey.sequence());
    else
        remove(entry.ikey.user_key(), entry.ikey.sequence());
}

size_t SkipListMemTable::size() const {
    return size_;
}