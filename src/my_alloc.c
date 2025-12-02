
#define _DEFAULT_SOURCE
#include "my_alloc.h"
#include <unistd.h>
#include <string.h>
#include <stdio.h>

typedef struct block_header {
    size_t size;
    int free;
    struct block_header* next;
} block_header;

#define BLOCK_SIZE sizeof(block_header)

static block_header* free_list = NULL;

static block_header* find_free_block(size_t size) {
    block_header* curr = free_list;

    while (curr) {
        if (curr->free && curr->size >= size) {
            return curr;
        }
        curr = curr->next;
    }
    return NULL;
}

static block_header* request_space(size_t size) {
    void* request = sbrk(0);
    void* ret = sbrk(size + BLOCK_SIZE);

    if (ret == (void*) -1)
        return NULL;

    block_header* block = (block_header*) request;
    block->size = size;
    block->free = 0;
    block->next = NULL;

    if (!free_list)
        free_list = block;
    else {
        block_header* last = free_list;
        while (last->next)
            last = last->next;
        last->next = block;
    }

    return block;
}

void* my_malloc(size_t size) {
    if (size == 0) return NULL;

    block_header* block = find_free_block(size);

    if (!block) {
        block = request_space(size);
        if (!block) return NULL;
    } else {
        block->free = 0;
    }

    return (block + 1);
}

static void merge_free_blocks() {
    block_header* curr = free_list;

    while (curr && curr->next) {
        if (curr->free && curr->next->free) {
            curr->size += BLOCK_SIZE + curr->next->size;
            curr->next = curr->next->next;
        } else {
            curr = curr->next;
        }
    }
}

void my_free(void* ptr) {
    if (!ptr) return;

    block_header* block = (block_header*)ptr - 1;

    block->free = 1;
    merge_free_blocks();
}

void* my_calloc(size_t nmemb, size_t size) {
    size_t total = nmemb * size;
    void* ptr = my_malloc(total);

    if (ptr)
        memset(ptr, 0, total);

    return ptr;
}

void* my_realloc(void* ptr, size_t size) {
    if (!ptr)
        return my_malloc(size);

    block_header* block = (block_header*)ptr - 1;

    if (block->size >= size)
        return ptr;

    void* new_ptr = my_malloc(size);
    if (!new_ptr) return NULL;

    memcpy(new_ptr, ptr, block->size);
    my_free(ptr);

    return new_ptr;
}