//------------------------------------------------------------------------------
// 4190.308                     Computer Architecture                  Fall 2015
//
// Cache Simulator
//
// File: cache.h
//
// (C) 2015 Computer Systems and Platforms Laboratory, Seoul National University
//
// Changelog
// 20151119   bernhard    created
//

#ifndef __CACHE_H__
#define __CACHE_H__

// access types
#define READ                  0       // read access
#define WRITE                 1       // write access

// replacement policies
#define RP_RR                 0       // round robin
#define RP_RANDOM             1       // random
#define RP_LRU                2       // least-recently used
#define RP_MRU                3       // most-recently used
#define RP_LFU                4       // least-frequently used
#define RP_MFU                5       // most-frequently used
#define RP_MAX                RP_MFU

// write allocate policies
#define WP_WRITEALLOC         0       // write-allocate
#define WP_NOWRITEALLOC       1       // no write-alloate
#define WP_MAX                WP_NOWRITEALLOC

// use these to print replacement and write allocate policies
extern char RP_STR[RP_MAX+1][32];
extern char WP_STR[2][20];

// too lazy to type 'unsigned int' every time
typedef unsigned char uint8;
typedef unsigned int uint32;

// Line: one cache line
typedef struct __line {
  uint32 tag;
  uint8 valid : 1;
} Line;

// Set: one set of the cache
typedef struct __set {
  Line  *way;                         // cache lines
} Set;

// Cache: the cache
typedef struct __cache {
  Set *sets;                         // cache sets
  uint32 blocksize;
  uint32 set_count;
  uint32 way_count;

  uint32 s_access;                    // statistics: number of accesses
  uint32 s_hit;                       // statistics: number of hits
  uint32 s_miss;                      // statistics: number of misses
  uint32 s_evict;                     // statistics: number of evictions
} Cache;

//
// create/delete a cache
//
// create initializes the data structure of a cache given its capacity,
// blocksize, number of ways, replacement policy and write-allocate policy
//
// delete frees the memory of a cache (lines, sets, and the cache itself)
//
Cache* create_cache(uint32 capacity, uint32 blocksize, uint32 ways,
                    uint32 rp, uint32 wp, uint32 verbosity);
void delete_cache(Cache *c);


//
// simulate a cache access
//
// parameters
//   type         READ/WRITE
//   address      requested address
//   length       length of the access
//
void cache_access(Cache *c, uint32 type, uint32 address, uint32 length);

#endif // __CACHE_H__
