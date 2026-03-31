Falcon
=====

A simple in-memory data structure library and demo server/client application written in C++.

This repository includes implementations and tests for:

- AVL tree (balanced binary search tree)
- Hashtable with incremental rehashing
- Heap (max-heap and min-heap via comparator)
- Sorted set (zset) abstraction
- Thread pool for concurrency support
- Example client and server using the data structures

## Goals

- Demonstrate clean and efficient data structure design in modern C++ (C++17)
- Provide test coverage for correct behavior
- Show incremental rehashing strategies for hashtables
- Enable easy integration into larger projects

## Project structure

- `avl.cpp`, `avl.h`: AVL tree implementation and API
- `hashtable.cpp`, `hashtable.h`: Hashtable implementation with `HMap` and `HNode`
- `heap.cpp`, `heap.h`: Heap implementation supporting both min and max mode
- `zset.cpp`, `zset.h`: Sorted set wrapper using internal indices and operations
- `thread_pool.cpp`, `thread_pool.h`: Thread pool and task queue
- `main.cpp`: Demo application entry point showing hashtable operations
- `client.cpp`, `server.cpp`: Example socket-based client/server (application-specific)
- `test_avl`, `test_hashtable`, `test_heap`: Executable tests

## Requirements

- Linux (or POSIX-compatible platform)
- GCC/Clang with C++17 support

## Build

To compile the core application:

```bash
cd /home/debojeet/Project/Falcon
g++ -std=c++17 -Wall -Wextra -O2 -o falcon main.cpp avl.cpp hashtable.cpp heap.cpp thread_pool.cpp zset.cpp client.cpp server.cpp
```

## Run

```bash
./falcon
```

Expected output includes a hashtable demo and successful operations.

## Tests

Run tests for each data structure module:

```bash
./test_avl
./test_hashtable
./test_heap
```

All tests should pass and print confirmation details.

## Maintenance

- Keep APIs stable in header files for external consumption
- Add unit tests for new functionality before commit
- Use `-Wall -Wextra` to catch warnings early

## License

The project uses the license provided in `LICENSE`.
