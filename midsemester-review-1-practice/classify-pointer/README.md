### Let's assume the following function exists:
It prints "STACK" if p contains an address on the stack;
it prints "HEAP" if p contains an address on the heap;
it prints "NEITHER" if p contains an address neither on the stack nor on the heap.
```C
void classify_pointer(void *p);
```

### Go through classify.c and think about what (1), (2), (3), (4), (5), (6), and (7) prints.  If something prints NEITHER, think about where the address lives.

Note, this will not actually compile if you use the method "classify_pointer", since it is not actually defined anywhere.
