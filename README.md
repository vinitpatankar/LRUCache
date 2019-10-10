This program implements an LRU Cache.
LRU Cache is commonly used as a caching technique where priority is given to recently used items
The implementation uses a double linked list and a map as its two main data structures
The map keeps key -> HEAD pointer loopkup
Insertions or updates happen at the HEAD. Hence the last element (TAIL) is LRU, which gets deleted when capacity is full
