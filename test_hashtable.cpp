#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "hashtable.h"

// Simple string key/value node for testing
struct KVNode {
    HNode node;
    const char* key;
    const char* value;
};

// Hash function for KVNode
uint64_t kv_hash(const char* key) {
    // Simple djb2 hash
    uint64_t hash = 5381;
    int c;
    while ((c = *key++)) {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return hash;
}

// Equality function for KVNode
bool kv_eq(HNode* a, HNode* b) {
    KVNode* node_a = reinterpret_cast<KVNode*>(a);
    KVNode* node_b = reinterpret_cast<KVNode*>(b);
    return strcmp(node_a->key, node_b->key) == 0;
}

int main() {
    printf("Testing hashtable implementation...\n");
    
    // Create a hash map
    HMap map;
    map.newer.tab = NULL;
    map.older.tab = NULL;
    map.migrate_pos = 0;
    
    // Test insertion
    KVNode* nodes[10];
    const char* keys[10] = {
        "apple", "banana", "cherry", "date", "elderberry",
        "fig", "grape", "honeydew", "kiwi", "lemon"
    };
    const char* values[10] = {
        "red", "yellow", "red", "brown", "purple",
        "purple", "purple", "green", "brown", "yellow"
    };
    
    for (int i = 0; i < 10; i++) {
        nodes[i] = static_cast<KVNode*>(malloc(sizeof(KVNode)));
        nodes[i]->key = keys[i];
        nodes[i]->value = values[i];
        nodes[i]->node.hcode = kv_hash(keys[i]);
        nodes[i]->node.next = NULL;
        
        hm_insert(&map, &nodes[i]->node);
        printf("Inserted: %s -> %s\n", keys[i], values[i]);
    }
    
    // Test lookup
    for (int i = 0; i < 10; i++) {
        KVNode* key = static_cast<KVNode*>(malloc(sizeof(KVNode)));
        key->key = keys[i];
        key->value = NULL; // Not used in lookup
        key->node.hcode = kv_hash(keys[i]);
        key->node.next = NULL;
        
        HNode* found = hm_lookup(&map, &key->node, kv_eq);
        if (found) {
            KVNode* value_node = reinterpret_cast<KVNode*>(found);
            printf("Found: %s -> %s\n", keys[i], value_node->value);
            assert(strcmp(value_node->value, values[i]) == 0);
        } else {
            printf("ERROR: Could not find %s\n", keys[i]);
            assert(false);
        }
        
        free(key);
    }
    
    // Test deletion
    for (int i = 0; i < 10; i++) {
        KVNode* key = static_cast<KVNode*>(malloc(sizeof(KVNode)));
        key->key = keys[i];
        key->value = NULL; // Not used in deletion
        key->node.hcode = kv_hash(keys[i]);
        key->node.next = NULL;
        
        HNode* deleted = hm_delete(&map, &key->node, kv_eq);
        if (deleted) {
            KVNode* value_node = reinterpret_cast<KVNode*>(deleted);
            printf("Deleted: %s -> %s\n", keys[i], value_node->value);
            assert(strcmp(value_node->value, values[i]) == 0);
            free(value_node);
        } else {
            printf("ERROR: Could not delete %s\n", keys[i]);
            assert(false);
        }
        
        free(key);
    }
    
    // Verify map is empty
    assert(hm_size(&map) == 0);
    printf("Map size after deletions: %zu\n", hm_size(&map));
    
    // Clean up
    hm_clear(&map);
    
    printf("All tests passed!\n");
    return 0;
}