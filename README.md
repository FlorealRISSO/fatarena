# FatArena

`FatArena` is a simple memory management system that provides an interface for allocating and writing to a custom memory arena. This C-based library allows for manual control over memory allocation and deallocation with low overhead.

## Features

- Memory allocation within an arena
- Read and write operations to the allocated memory
- Efficient access to memory pointers within the arena

## API

### Data Structure

```c
typedef struct FatArena {
 uint8_t *addr;
 size_t remain;
 size_t size;
} FatArena;
```

`FatArena` represents a memory arena with:

- `addr`: A pointer to the base address of the arena.
- `remain`: The amount of free space remaining.
- `size`: The total size of the arena.

### Functions

- **`size_t getpgsz()`**  
  Returns the page size of the system.

- **`Bool ftnew(FatArena *a, size_t sz)`**  
  Initializes a new memory arena with the given size `sz`.

- **`int ftalloc(FatArena *a, size_t sz)`**  
  Allocates a block of memory within the arena of size `sz` and returns the index of the allocated block.

- **`Bool ftwrite(FatArena *a, int idx, const uint8_t *ptr, size_t sz)`**  
  Writes `sz` bytes from `ptr` to the allocated block at index `idx`.

- **`Bool ftread(const FatArena *a, int idx, uint8_t *ptr, size_t sz)`**  
  Reads `sz` bytes from the block at index `idx` into `ptr`.

- **`uint8_t* ftptr(const FatArena *a, int idx)`**  
  Returns a pointer to the memory block at index `idx`.

- **`int ftidx(const FatArena *a, const uint8_t *ptr)`**  
  Returns the index corresponding to a given memory pointer.

## Usage

```c
#include "FatArena.h"

int main() {
    FatArena arena;
    if (ftnew(&arena, 4096)) {
        int idx = ftalloc(&arena, 128);
        if (idx >= 0) {
            uint8_t data[128] = { /* data to write */ };
            ftwrite(&arena, idx, data, sizeof(data));

            uint8_t read_data[128];
            ftread(&arena, idx, read_data, sizeof(read_data));
        }
    }
    return 0;
}
```

## Learn More

For a more detailed explanation and use cases, check out [this article](https://florealrisso.github.io/articles/fatarena.html)
