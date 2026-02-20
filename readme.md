# LSM Tree Engine

##  Current Status

The engine now has a fully functional **durable write path** and in-memory state management.

✔ Key / Value abstractions  
✔ InternalKey (sequence-based versioning + ordering)  
✔ Entry (logical mutation record)  
✔ WAL (binary log with replay for recovery)  
✔ MemTable (ordered structure with version-aware lookup)  
✔ DB facade (orchestrates WAL, MemTable, and recovery)
✔ Skip List MemTable

---

##  High-Level Architecture

Client API (DB)
↓
Write Path
- WAL (durability, append-only log)
- MemTable (mutable in-memory state)
↓
Flush (future)
- Immutable MemTable → SSTable
↓
Storage (future)
- SSTables (multi-level sorted runs)
- Index blocks
- Bloom filters
↓
Compaction (future)
- Merge / Rewrite / Tombstone cleanup
↓
Read Path
- MemTable → SSTables → Merge iterator

---

## 🔄 Current Write Flow

1. Client calls `DB::put` or `DB::remove`
2. Sequence number assigned
3. Entry appended to WAL (durability)
4. Entry applied to MemTable (visibility)

**Invariant:** WAL append happens before MemTable mutation

---

## 🔁 Recovery Flow

On startup:

1. WAL is replayed sequentially  
2. Entries are applied to MemTable  
3. Sequence counter is restored  

This ensures crash-safe recovery of the latest state.

---

##  Storage Model (Target Design)

The engine follows a classic **LSM-tree architecture**:

- Writes are sequential and append-only
- Reads merge multiple sorted sources
- Background compaction maintains performance
- Tombstones provide logical deletes

---

## 📍 Next Milestones

- MemTable flush threshold
- Immutable MemTable
- SSTable file format
- Block index + Bloom filters
- Compaction scheduler
