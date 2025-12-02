# mini-malloc — A Custom Memory Allocator in C

`mini-malloc` is a lightweight implementation of a custom memory allocator written in C.  
It recreates the core behavior of `malloc`, `free`, and `calloc` using low-level system calls and manual memory management.

This project demonstrates:

- Pointer arithmetic  
- Low-level memory layout handling  
- Free-list data structures  
- Block metadata management  
- Fragmentation handling  
- System-level memory allocation (`sbrk` or `mmap`)  

It's a great learning project for understanding how real allocators work under the hood.

---

## ✨ Features

### Implemented
- `void* my_malloc(size_t size)`
- `void  my_free(void* ptr)`
- `void* my_calloc(size_t nmemb, size_t size)`
- First-Fit allocation strategy
- Block metadata including:
  - size  
  - free flag  
  - next pointer  
- Automatic heap growth using `sbrk()` (or optional `mmap()` version)

### Stretch Features (Optional)
- `void* my_realloc(void* ptr, size_t size)`
- Best-Fit or Next-Fit allocation strategies
- Coalescing adjacent free blocks
- Memory corruption checks

---

## 📁 Project Structure
```
mini-malloc/
│
├── src/
│ ├── my_alloc.c # allocator implementation
│ └── my_alloc.h # allocator API
│
├── tests/
│ └── test_allocator.c # basic tests for the allocator
│
└── Makefile # build & test commands
```

---

## 🛠️ Building

Make sure you have GCC or Clang installed.

Run:

```bash
make
```

### This compiles:

*src/my_alloc.c*

*tests/test_allocator.c*

and produces the executable : 

```bash
./test_allocator
```

---

## ▶️ Running Tests

After building:

```bash
./test_allocator
```

---

## 🧠 Concepts Demonstrated

This project shows understanding of:

- Pointer arithmetic  
- Linked list block management  
- Internal vs external fragmentation  
- Dynamic heap growth  
- Custom memory allocation mechanics  
- Memory block metadata structures  
- System-level memory operations  

### This makes it ideal for:

- Systems programming practice  
- OS class projects  
- Interview portfolio work  
- Memory allocator study  

---

## 🧪 Example Usage

```c
#include "my_alloc.h"

int main() {
    int* values = my_malloc(sizeof(int) * 10);
    values[0] = 42;

    char* buffer = my_calloc(100, sizeof(char)); // zero-initialized

    my_free(values);
    my_free(buffer);
}
```

### Acknowledgment
This project is inspired by classical memory allocator designs, OS development books, and various educational resources used for teaching low-level memory management.

Thanks to the open-source community for providing foundational allocator examples that shaped the API and structure of this project.

## 📜 License

This project is released under the MIT License.
You may freely modify, distribute, or use it in your own software.
