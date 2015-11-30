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

// ISPOW2: returns 1 if x is a power of 2, 0 otherwise
#define ISPOW2(x) ((x != 0) && !(x & (x-1)))

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
// (hint: for the simulation you do not need to store the actual data in the
//        cache, the tag and management information is sufficient)
typedef struct __line {
  // TODO
  // if necessary add more fields
} Line;

// Set: one set of the cache
typedef struct __set {
  Line  *way;                         // cache lines

  // TODO
  // if necessary add more fields
} Set;

// Cache: the cache
typedef struct __cache {
  Set   *set;                         // cache sets

  uint32 s_access;                    // statistics: number of accesses
  uint32 s_hit;                       // statistics: number of hits
  uint32 s_miss;                      // statistics: number of misses
  uint32 s_evict;                     // statistics: number of evictions

  // TODO
  // if necessary add more fields
  //
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
// simulate access to a cache line
//
void line_access(Cache *c, Line *l);

//
// allocate a tag into a given cache line
//
void line_alloc(Cache *c, Line *l, uint32 tag);

//
// find a victim line for a given cache set
//
uint32 set_find_victim(Cache *c, Set *s);

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
