//------------------------------------------------------------------------------
// 4190.308                     Computer Architecture                  Fall 2015
//
// Cache Simulator Lab
//
// File: cachesim..c
//
// (C) 2015 Computer Systems and Platforms Laboratory, Seoul National University
//
// Changelog
// 20151119   bernhard    created
//

#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cache.h"

int parse_arguments(int argc, char *argv[], uint32 *capacity, uint32 *blocksize,
                    uint32 *ways, uint32 *rp, uint32 *wp, uint32 *verbosity)
{
  int i;
  *capacity = *blocksize = *ways;
  *rp = RP_RR;
  *wp = WP_WRITEALLOC;

  // parse command line
  for (i=1; i<argc; i++) {
    // extract option and option value
    char *opt = argv[i++];
    if (!(strcmp(opt, "-h") && strcmp(opt, "--help"))) return EXIT_FAILURE;
    if (!(strcmp(opt, "-v") && strcmp(opt, "--verbose"))) {
      (*verbosity)++;
      continue;
    }
    if (i == argc) {
      fprintf(stderr, "Missing value after option '%s'.\n", opt);
      return EXIT_FAILURE;
    }

    // convert string to numerical value
    char *endptr;
    errno = 0;
    long int val = strtol(argv[i], &endptr, 0);
    if ((errno != 0) || (endptr == argv[i])) {
      fprintf(stderr, "Invalid numerical value after option '%s': '%s'.\n",
              opt, argv[i]);
      return EXIT_FAILURE;
    }

    if (!(strcmp(opt, "-c") && strcmp(opt, "--capacity"))) *capacity = val;
    else if (!(strcmp(opt, "-b") && strcmp(opt, "--blocksize"))) *blocksize=val;
    else if (!(strcmp(opt, "-w") && strcmp(opt, "--ways"))) *ways = val;
    else if (!(strcmp(opt, "-r") && strcmp(opt, "--replacement"))) *rp = val;
    else if (!(strcmp(opt, "-W") && strcmp(opt, "--write"))) *wp = val;
    else {
      fprintf(stderr, "Invalid command line argument '%s'.\n", opt);
      return EXIT_FAILURE;
    }
  }

  // validation
  if (*capacity == 0) {
    fprintf(stderr, "Cache capacity not set.\n");
    return EXIT_FAILURE;
  }
  if (*blocksize == 0) {
    fprintf(stderr, "Blocksize not set.\n");
    return EXIT_FAILURE;
  }
  if (*ways == 0) {
    fprintf(stderr, "Ways not set.\n");
    return EXIT_FAILURE;
  }
  if (*rp > RP_MAX) {
    fprintf(stderr, "Invalid replacement policy.\n");
    return EXIT_FAILURE;
  }
  if (*wp > WP_MAX) {
    fprintf(stderr, "Invalid write allocate policy.\n");
    return EXIT_FAILURE;
  }


  return EXIT_SUCCESS;
}

void syntax(void)
{
  uint32 i;

  printf("cachesim: a cache simulator.\n"
         "\n"
         "Usage: $ cachesim <options>\n"
         "where <options> is\n"
         "  -h / --help                  Show this help screen.\n"
         "  -v / --verbose               Be verbose while running.\n"
         "  -c / --capacity <number>     Set the cache capacity.\n"
         "  -b / --blocksize <number>    Set the block size.\n"
         "  -w / --ways <number>         Set the number of ways.\n"
         "  -r / --replacement <number>  Set the replacement strategy.\n");
  for (i=0; i<=RP_MAX; i++) {
    printf("%32s%2d  %s%s\n", "", i, RP_STR[i], (i==0?" (default)":""));
  }
  printf("  -W / --write <number>       Set the write strategy.\n");
  for (i=0; i<=WP_MAX; i++) {
    printf("%32s%2d  %s%s\n", "", i, WP_STR[i], (i==0?" (default)":""));
  }
  printf("\n");

  exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
  uint32 c, b, w, rp, wp, v;
  Cache *cache;

  // parse arguments
  if (parse_arguments(argc, argv, &c, &b, &w, &rp, &wp, &v) != EXIT_SUCCESS) {
    syntax();
  }

  // create cache
  cache = create_cache(c, b, w, rp, wp, v);

  // set initial random seed
  srand(1522000800);

  // read input line by line
  char *type = NULL;
  uint32 address, length;
  char *line = NULL;
  size_t ll = 0;
  ssize_t ilen = getline(&line, &ll, stdin);
  uint32 count = 0;

  printf("Processing input..."); fflush(stdout);
  if (v) printf("\n");

  while (ilen > 0) {
    if (sscanf(line, "%ms %x,%x", &type, &address, &length) == 3) {
      switch (type[0]) {
        // instruction
        case 'I':
          // ignore
          break;

        // memory load ('L') or load-store ('M')
        case 'M':
        case 'L':
          cache_access(cache, READ, address, length);
          if (type[0] == 'L') break;

        // memory store ('S') or load-store ('M')
        case 'S':
          cache_access(cache, WRITE, address, length);
          break;
      }
    }

    // read next line from input
    if (type != NULL) { free(type); type = NULL; }
    ilen = getline(&line, &ll, stdin);

    count++;
    if (!v && (count % 32768 == 0)) { printf("."); fflush(stdout); }
  }

  // print statistics
  printf("\n\n"
         "Cache simulation statistics:\n"
         "  accesses:       %8d\n"
         "  hit:            %8d\n"
         "  miss:           %8d\n"
         "  evictions:      %8d\n"
         "  miss ratio:     %4.2f%%\n",
         cache->s_access, cache->s_hit, cache->s_miss, cache->s_evict,
         cache->s_access > 0 ? ((float)cache->s_miss)/cache->s_access*100 : 0.0);

  // free cache & exit
  delete_cache(cache);

  return EXIT_SUCCESS;
}
