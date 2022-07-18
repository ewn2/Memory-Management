Memory Management Simulation

Reads in 'memory.dat' file with format:

PROCESS_ID  ACTION  PAGE

Implements a virtual memory system with 20 (0 - 19) total physical pages, and infinite swap.

Simulates FIFO, LRU (least-recently-used), and Random memory/swap policies.
LRU tries to take advantage of locality in the memory-reference stream, assuming it is likely that an entry that has not been recently used is a good candidate for eviction.
