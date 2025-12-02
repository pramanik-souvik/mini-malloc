CC = gcc
CFLAGS = -Wall -Wextra -g

SRC = src/my_alloc.c
TEST = tests/test_allocator.c

all: test_allocator

test_allocator: $(SRC) $(TEST)
	$(CC) $(CFLAGS) -o test_allocator $(SRC) $(TEST)

clean:
	rm -f test_allocator
