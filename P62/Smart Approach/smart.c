#include <stdio.h>
#include <stdlib.h>

unsigned long sort_digits(unsigned long n) {
  // get it into a string
  static char s[21];           /* log_10(2^64) + 1 */
  int length = sprintf(s, "%lu", n);
  // bubble sort it because i don't give a shit today
  int swapped;
  do {
    int i;
    swapped = 0;
    for(i = 0; i < length - 1; i++) {
      if(s[i + 1] > s[i]) {
        s[i + 1] ^= s[i];
        s[i] ^= s[i + 1];
        s[i + 1] ^= s[i];
        swapped = 1;
      }
    }
  } while(swapped);
  // get it back to an int
  return strtol(s, NULL, 10);
}

#define BUCKETS 16384

// this is somewhat of a weird hash table but it's useful for what
// we're doing. each key is a ulong, each value is a (counter, index)
// pair. counter gets incremented on each incr() call, index is the
// value of i at the first time it was incremented (since we're
// looking for the *smallest* of the squares here, but we won't
// realize it's the one we're looking for until we find the 5th number
// with the same sorted-digits)

// since the only operations we're doing are that weird
// increment-and-set thing and a get for the index, that's all i've
// impemented

typedef struct hashbucket_t {
  struct hashbucket_t *next;
  unsigned long key;
  int value;
  int index;
} *hashbucket;

hashbucket hash[BUCKETS] = {0};

int incr(unsigned long key, int index) {
  int bucket = key % BUCKETS;
  if(hash[bucket]) {
    hashbucket p = hash[bucket], p2;
    while(p) {
      if(p->key == key) {
        // we found the key! increment it
        return ++p->value;
      }
      p2 = p;
      p = p->next;
    }
    // the bucket's been allocated but our key isn't in it
    p2->next = calloc(1, sizeof(struct hashbucket_t));
    p2->next->key = key;
    p2->next->index = index;
    return p2->next->value = 1;
  } else {
    // the bucket hasn't been allocated
    hash[bucket] = calloc(1, sizeof(struct hashbucket_t));
    hash[bucket]->key = key;
    hash[bucket]->index = index;
    return hash[bucket]->value = 1;
  }
}

int index_of(unsigned long key) {
  int bucket = key % BUCKETS;
  if(hash[bucket]) {
    hashbucket p = hash[bucket];
    while(p) {
      if(p->key == key) {
        return p->index;
      }
    }
    return -1;
  }
  return -1;
}

int main(void) {
  unsigned long i;
  for(i = 0; ; i++) {
    unsigned long sorted = sort_digits(i * i * i);
    if(incr(sorted, i) >= 5) {
      i = index_of(sorted);
      printf("%lu^3 = %lu\n", i, i * i * i);
      break;
    }
  }
}