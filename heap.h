#pragma once

#include <stddef.h>
#include <stdint.h>


struct HeapItem {
    uint64_t val = 0;
    size_t *ref = NULL;
};

size_t heap_parent(size_t i);
size_t heap_left(size_t i);
size_t heap_right(size_t i);
void heap_up(HeapItem *a, size_t pos);
void heap_down(HeapItem *a, size_t pos, size_t len);
void heap_update(HeapItem *a, size_t pos, size_t len);