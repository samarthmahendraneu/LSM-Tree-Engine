#include "core/memtable/MemTable.h"
#include "core/types/key.h"
#include "core/types/value.h"

#include <iostream>

int main() {
    MemTable mem;

    // PUT A -> 10 (seq 1)
    mem.put(Key("A"), Value("10"), 1);

    // PUT A -> 20 (seq 2) (newer version)
    mem.put(Key("A"), Value("20"), 2);

    // DELETE A (seq 3)
    mem.remove(Key("A"), 3);

    // PUT B -> 99 (seq 4)
    mem.put(Key("B"), Value("99"), 4);

    // ===== LOOKUPS =====

    auto a = mem.get(Key("A"));
    if (a.has_value()) {
        std::cout << "A = " << a->bytes() << "\n";
    } else {
        std::cout << "A NOT FOUND\n";
    }

    auto b = mem.get(Key("B"));
    if (b.has_value()) {
        std::cout << "B = " << b->bytes() << "\n";
    } else {
        std::cout << "B NOT FOUND\n";
    }

    std::cout << "MemTable size = " << mem.size() << "\n";
}
