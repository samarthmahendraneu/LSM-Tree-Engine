#include "core/memtable/MemTable.h"
#include "core/types/key.h"
#include "core/types/value.h"
#include "core/wal/WAL.h"

#include <iostream>

int main() {
    // ---- OPEN WAL ----
    Wal wal("test.wal");

    // ---- MEMTABLE ----
    MemTable mem;

    // ---- WRITE PATH (append to WAL + apply to memtable) ----

    Entry e1(Key("A"), Value("10"), 1, false);
    wal.append(e1);
    mem.apply(e1);

    Entry e2(Key("A"), Value("20"), 2, false);
    wal.append(e2);
    mem.apply(e2);

    Entry e3(Key("A"), Value(""), 3, true);
    wal.append(e3);
    mem.apply(e3);

    Entry e4(Key("B"), Value("99"), 4, false);
    wal.append(e4);
    mem.apply(e4);

    std::cout << "=== After writes ===\n";

    auto a = mem.get(Key("A"));
    if (a.has_value())
        std::cout << "A = " << a->bytes() << "\n";
    else
        std::cout << "A NOT FOUND\n";

    auto b = mem.get(Key("B"));
    if (b.has_value())
        std::cout << "B = " << b->bytes() << "\n";
    else
        std::cout << "B NOT FOUND\n";

    std::cout << "MemTable size = " << mem.size() << "\n\n";



    // restart
    std::cout << "=== Simulating restart ===\n";

    MemTable recovered;

    auto entries = wal.replay();
    for (const auto& e : entries) {
        recovered.apply(e);
    }

    auto a2 = recovered.get(Key("A"));
    if (a2.has_value())
        std::cout << "Recovered A = " << a2->bytes() << "\n";
    else
        std::cout << "Recovered A NOT FOUND\n";

    auto b2 = recovered.get(Key("B"));
    if (b2.has_value())
        std::cout << "Recovered B = " << b2->bytes() << "\n";
    else
        std::cout << "Recovered B NOT FOUND\n";

    std::cout << "Recovered MemTable size = " << recovered.size() << "\n";
}

