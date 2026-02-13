### Current Status -> Defined Entry,Key, Value


### high level flow 

Client API
↓
Write Path
- WAL
- MemTable
  ↓
  Flush
- Immutable MemTable → SSTable
  ↓
  Storage
- SSTables (multiple levels)
- Index + Bloom filters
  ↓
  Compaction
- Merge / Rewrite / Delete
  ↓
  Read Path
- MemTable → SSTables → Merge
