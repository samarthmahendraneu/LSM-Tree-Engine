#include "core/memtable/MemTable.h"
#include "core/types/key.h"
#include "core/types/value.h"
#include "core/wal/WAL.h"

#include <iostream>

#include "core/db/DB.h"

int main() {

    DB db("test.wal");



    // ---- WRITE PATH (append to WAL + apply to memtable) ----

    db.put(Key("A"), Value("10"));
    db.put(Key("A"), Value("20"));

    db.remove(Key("A"));
    db.put(Key("B"), Value("99"));
    std::cout << "=== After writes ===\n";

    auto a = db.get(Key("A"));
    if (a.has_value())
        std::cout << "A = " << a->bytes() << "\n";
    else
        std::cout << "A NOT FOUND\n";

    auto b = db.get(Key("B"));
    if (b.has_value())
        std::cout << "B = " << b->bytes() << "\n";
    else
        std::cout << "B NOT FOUND\n";

    std::cout << "MemTable size = " << db.size() << "\n\n";



    // restart
    std::cout << "=== Simulating restart ===\n";

    DB recovered("test.wal");

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

