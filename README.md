# IP and TCP from Scratch

A C implementation of the IP and TCP protocols built from the ground up.  
This project is intended purely for educational purposes, focusing on understanding
how these protocols work internally.  
No optimizations were made for performance—efficiency was not a goal.
* [X] IP
* [ ] TCP
* [ ] Sending and recieving the packet

# Implementation motivation

Some function are not really usefull in the way that they just take a struct pointer and a value
and simply set a the value of a struct field to the value passed.
I find the implementation cleaner this way, so that every field has the same interface. So instead
of having `prot_set_field(prot, value)` for complex field and `prot->value = value` for simple field,
all fields can be set using the first interface.
Of course `prot->value = value` is still available, it's C struct you can do whatever you want.

# Valgrind output

```
==66098== HEAP SUMMARY:
==66098==     in use at exit: 0 bytes in 0 blocks
==66098==   total heap usage: 4 allocs, 4 frees, 5,612 bytes allocated
==66098==
==66098== All heap blocks were freed -- no leaks are possible
==66098==
==66098== For lists of detected and suppressed errors, rerun with: -s
==66098== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```
