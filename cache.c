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
#include <stdint.h>
#include <string.h>
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

static uint32 ilog2(const uint32 x) {
  uint32 y;
  asm ("bsr %1, %0" : "=r"(y) : "r" (x));
  return y;
}

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
Cache* create_cache(uint32 capacity, uint32 blocksize, uint32 way_count,
                    uint32 rp, uint32 wp, uint32 verbosity)
{
  uint32 blocks = capacity / blocksize;

  // 1. check cache parameters
  check(is_power_of_2(capacity), "Capacity should be power of 2");
  check(is_power_of_2(blocksize), "Blocksize should be power of 2");
  check(is_power_of_2(way_count), "Number of ways should be power of 2");
  check(capacity >= blocksize, "Capacity should be >= blocksize");
  check(blocks >= way_count, "Number of blocks must be >= the number of ways");

  uint32 set_count = blocks / way_count;

  // 2. allocate cache and initialize them
  Set *sets = (Set*)malloc(sizeof(Set) * set_count);
  for (uint32 i = 0; i < set_count; ++i) {
    Line *lines = malloc(sizeof(Line) * way_count);
    memset(lines, 0, sizeof(Line) * way_count);

    sets[i].way = lines;
  }

  Cache *cache = malloc(sizeof(Cache));
  cache->sets = sets;
  cache->set_count = set_count;
  cache->way_count = way_count;

  cache->s_access = 0;
  cache->s_hit = 0;
  cache->s_miss = 0;
  cache->s_evict = 0;

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
         capacity, blocksize, way_count, set_count,
         ilog2(way_count) + ilog2(set_count), RP_STR[rp], WP_STR[wp]);

  // 4. return cache
  return cache;
}

void delete_cache(Cache *cache) {
  Set *sets = cache->sets;

  uint32 set_count = cache->set_count;
  for (uint32 i = 0; i < set_count; ++i) { free(sets[i].way); }

  free(sets);
  free(cache);
}


//
// simulate access to a cache line
//
static void line_access(Cache *cache, Line *line) {
  // TODO
  // update data structures to reflect access to a cache line
}


//
// allocate a tag into a given cache line
//
static void line_alloc(Cache *c, Line *l, uint32 tag) {
  // TODO
  // update data structures to reflect allocation of a new block into a line
}


//
// find a victim line for a given cache set
//
static uint32 set_find_victim(Cache *c, Set *s) {
  // TODO
  // for a given set, return the victim line where to place the new block
  return 0;
}

void cache_access(Cache *cache, uint32 type, uint32 address, uint32 length) {
  uint32 set_index = (address >> ilog2(cache->blocksize)) & (cache->set_count - 1);
  uint32 tag = address >> (ilog2(cache->blocksize) + ilog2(cache->set_count));

  printf("\e[33mdebug\e[0m set index: %d, tag: %d\n", set_index, tag);

  // TODO
  // simulate a cache access
  // 1. compute set & tag
  // 2. check if we have a cache hit
  // 3. on a cache miss, find a victim block and allocate according to the
  //    current policies
  // 4. update statistics (# accesses, # hits, # misses)
}
