//
// Created by Samarth Mahendra on 2/14/26.
//

#include "Wal.h"
#include "../types/Entry.h"


Wal::Wal(const std::string &path): path_(path) {
    out_.open(path_, std::ios::binary | std::ios::app);
}


void Wal::append(Entry &entry) {
    if (!out_.is_open()) return;
    //
    // | seq (uint64) |
    // | type (uint8) |
    // | key_size (uint32) |
    // | key bytes |
    // | value_size (uint32) |
    // | value bytes |

    const auto& ikey = entry.ikey;
    const auto& key_data = ikey.user_key().bytes();
    const auto& value_data = entry.value.bytes();

    uint64_t seq = ikey.sequence();
    auto type = static_cast<uint8_t>(ikey.type());
    auto key_size = static_cast<uint32_t>(key_data.size());
    auto val_size = static_cast<uint32_t>(value_data.size());

    // writing to buffer
    //
    out_.write(reinterpret_cast<char*>(&seq), sizeof(seq));
    out_.write(reinterpret_cast<char*>(&type), sizeof(type));
    out_.write(reinterpret_cast<char*>(&key_size), sizeof(key_size));
    out_.write(key_data.data(), key_size);
    out_.write(reinterpret_cast<char*>(&val_size), sizeof(val_size));
    out_.write(value_data.data(), val_size);

    out_.flush();
}



vector<Entry> Wal::replay() {
    vector<Entry> entries;

    ifstream in(path_, ios::binary);
    if (!in.is_open()) return entries;

    while (true){
        uint64_t seq;
        uint8_t type;
        uint32_t key_size;
        uint32_t val_size;

        if (!in.read(reinterpret_cast<char*>(&seq), sizeof(seq))) break;
        if (!in.read(reinterpret_cast<char*>(&type), sizeof(type))) break;
        if (!in.read(reinterpret_cast<char*>(&key_size), sizeof(key_size))) break;

        string key_buf(key_size, '\0');
        if (!in.read(key_buf.data(), key_size)) break;

        if (!in.read(reinterpret_cast<char*>(&val_size), sizeof(val_size))) break;

        string val_buf(val_size, '\0');
        if (!in.read(val_buf.data(), val_size)) break;

        ValueType vtype =
            (type == static_cast<uint8_t>(ValueType::DELETE))
            ? ValueType::DELETE
            : ValueType::PUT;
        Entry e(
            Key(key_buf),
            Value(val_buf),
            seq,
            vtype == ValueType::DELETE
        );

        entries.push_back(std::move(e));

    }
    return entries;
}


