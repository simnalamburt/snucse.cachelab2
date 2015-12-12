//------------------------------------------------------------------------------
// 4190.308                     Computer Architecture                  Fall 2015
//
// Cache Simulator Lab
//
// File: cache.c
//
// (C) 2015 Computer Systems and Platforms Laboratory, Seoul National University
//
// Changelog
// 20151119   bernhard    created
//

#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "cache.h"

char RP_STR[RP_MAX+1][32] = {
  "round robin", "random", "LRU (least-recently used)",
  "MRU (most-recently used)", "LFU (least-frequently used)",
  "MFU (most-frequently used)"
};

char WP_STR[2][20] = {
  "write-allocate", "no write-allocate"
};


//
// Utils
//
static bool is_power_of_2(uint32 x) { return (x != 0) && !(x & (x-1)); }

// msg 를 출력하고, exit(1);
static void panic(const char *msg) {
  fputs(msg, stderr);
  fputc('\n', stderr);
  exit(EXIT_FAILURE);
}

// Assertion
static void check(bool cond, const char *msg) {
  if (!cond) { panic(msg); }
}


//
// Implementation
//
Cache* create_cache(uint32 capacity, uint32 blocksize, uint32 ways,
                    uint32 rp, uint32 wp, uint32 verbosity)
{
  // 1. check cache parameters
  check(is_power_of_2(capacity), "Capacity is not power of 2");
  check(is_power_of_2(blocksize), "Blocksize is not power of 2");
  check(is_power_of_2(ways), "Number of ways is not power of 2");
  check(capacity > blocksize, "Capacity should be > blocksize");
  check(ways >= blocksize, "Number of ways must be >= the number of blocks");

  // TODO
  // 2. allocate cache and initialize them
  //    - use the above data structures Cache, Set, and Line


  // 3. print cache configuration
  printf("Cache configuration:\n"
         "  capacity:        %6u\n"
         "  blocksize:       %6u\n"
         "  ways:            %6u\n"
         "  sets:            %6u\n"
         "  tag shift:       %6u\n"
         "  replacement:     %s\n"
         "  on write miss:   %s\n"
         "\n",
         capacity, blocksize, ways, 0, 0, "", ""); // TODO

  // 4. return cache
  return NULL;
}

void delete_cache(Cache *c)
{
  // TODO
  //
  // clean-up the allocated memory
}

void line_access(Cache *c, Line *l)
{
  // TODO
  //
  // update data structures to reflect access to a cache line
}


void line_alloc(Cache *c, Line *l, uint32 tag)
{
  // TODO
  //
  // update data structures to reflect allocation of a new block into a line
}

uint32 set_find_victim(Cache *c, Set *s)
{
  // TODO
  //
  // for a given set, return the victim line where to place the new block
  return 0;
}

void cache_access(Cache *c, uint32 type, uint32 address, uint32 length)
{
  // TODO
  //
  // simulate a cache access
  // 1. compute set & tag
  // 2. check if we have a cache hit
  // 3. on a cache miss, find a victim block and allocate according to the
  //    current policies
  // 4. update statistics (# accesses, # hits, # misses)
}
