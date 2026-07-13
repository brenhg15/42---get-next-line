*This project has been created as part of the 42 curriculum by bhernand*

---

## Description
The goal of this project is to write a function in C that reads from a given file descriptor and returns one line at a time. A "line" is defined as a sequence of characters ending with a newline character (`\n`) or the End-Of-File. 

Repeated calls to `get_next_line()` allow an application to read an entire text stream sequentially without loading the whole file into heap memory at once[cite: 1]. This project serves as a practical introduction to the manipulation of static variables, buffer management, and strict dynamic memory allocation boundaries in C.

---

## Algorithm & Architecture Justification
The implementation utilizes a buffer-driven approach paired with a persistent static allocation to seamlessly bridge the gap between fixed-size reads and variable-length lines.

### Core Logic Workflow
1. **Dynamic Chunk Reading (`ft_read_fd`):** The function reads chunks of size `BUFFER_SIZE` from the file descriptor into a temporary scratch buffer. It appends these chunks to a static string tracking all unparsed data (`unfiltered_line`). This reading cycle loops continuously until a newline character (`\n`) is discovered within the static string or the end of the file is hit.
2. **Line Extraction (`ft_filter_line`):** The function scans the static string up to the first `\n` character (inclusive), allocates the precise amount of memory required, and copies out the single completed line to return to the user.
3. **State Preservation (`ft_rest_unfiltered`):** Any data read past the newline character represents the beginning of subsequent lines. The function preserves this data by copying it back into the static pointer, freeing the stale memory behind it.

### Why This Design Was Selected
* **Static Memory Stability:** By using a single static string block, the state of the read stream is safely maintained across multiple independent invocations of `get_next_line()` without losing tracking data.
* **No-Leak Error Resilience:** The architecture isolates raw system input. If a `read()` failure or invalid file descriptor is introduced mid-stream, the cleanup routines immediately intercept the error, free all pending heap allocations, and zero out the static pointer safely to prevent memory leakage.

---

## Instructions

### Compilation
The code must be compiled with the `-Wall -Wextra -Werror` flags alongside a specific macro flag defining the `BUFFER_SIZE`

Note: If no explicit -D BUFFER_SIZE is declared during compilation, the header safely falls back to a default value of 42.
To clean object files:

To compile:

```bash
make 
```
To remove all buidl artifacts:

```bash
make clean
```

To remove all build artifacts including the executable:

```bash
make fclean
```

To recompile from scratch:

```bash
make re
```

## Resources
### Documentation & References

* Input/Output Systems: Unix read(), malloc(), and free() manual documentation.

* C Concepts: ISO/IEC 9899 standard literature regarding static storage duration, storage layout, and lifetime behaviors of local static pointers.

### AI Usage Statement
* Code Implementation: AI was not utilized to generate architectural strategies or direct code solutions. First-principles reasoning and peer-to-peer debugging exchanges were leveraged to map out the pointer mutation states.

* Troubleshooting & Optimization: AI was strictly used as an automated static code analyzer to locate subtle memory leak vectors highlighted by strict unit testers (such as gnlTester), specifically pointing out dangling pointer tracking when handling late invalid file descriptors or mid-stream read failures.
