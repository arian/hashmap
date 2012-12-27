
#ifndef HASHMAP_HEADER
#define HASHMAP_HEADER

#define HASHMAP_BUCKETS 5

typedef struct hashmap_item *Hashmap_Item;

struct hashmap_item {
	Hashmap_Item next;
	void *key;
	void *value;
};

struct hashmap {
	Hashmap_Item buckets[HASHMAP_BUCKETS];
};

typedef struct hashmap *Hashmap;

Hashmap hashmap_create();
void * hashmap_get(Hashmap, void *);
void hashmap_set(Hashmap, void *, void *);
void hashmap_each(Hashmap, void fn(void *, void *, int));
void hashmap_delete(Hashmap, void *);
void hashmap_free(Hashmap);

#endif
