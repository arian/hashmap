
#include <stdlib.h>
#include <stdio.h>

#include "hashmap.h"

static Hashmap_Item create_item(void *key, void *value)
{
	Hashmap_Item item = (Hashmap_Item) malloc(sizeof(struct hashmap_item));
	item->key = key;
	item->value = value;
	return item;
}

static int hash(Hashmap hm, void * ptr)
{
	return (int) (((long) ptr) % HASHMAP_BUCKETS);
}

Hashmap hashmap_create()
{
	return (Hashmap) malloc(sizeof(struct hashmap));
}

void * hashmap_get(Hashmap hm, void *key)
{
	int index = hash(hm, key);
	Hashmap_Item item;

	for (item = hm->buckets[index]; item != NULL; item = item->next) {
		if (item->key == key)
			return item->value;
	}

	return NULL;
}

void hashmap_set(Hashmap hm, void *key, void *value)
{
	Hashmap_Item item;
	int index = hash(hm, key);

	for (item = hm->buckets[index]; item != NULL;) {
		if (item->key == key) {/* key already exists */
			item->value = value;
			return;
		}
		if (item->next == NULL) { /* last element in this bucket */
			item->next = create_item(key, value);
			return;
		}
		item = item->next;
	}

	/* bucket is empty */
	hm->buckets[index] = create_item(key, value);
}

void hashmap_each(Hashmap hm, void fn(void *, void *, int))
{
	int i;
	Hashmap_Item item;

	for (i = 0; i < HASHMAP_BUCKETS; i++) {
		for (item = hm->buckets[i]; item != NULL; item = item->next) {
			(*fn)(item->value, item->key, i);
		}
	}
}

void hashmap_delete(Hashmap hm, void * key)
{
	int index = hash(hm, key);
	Hashmap_Item item, next;

	item = hm->buckets[index];

	if (item == NULL)
		return;

	if (item->next == NULL) {
		free(item);
		hm->buckets[index] = NULL;
		return;
	}

	while (item != NULL) {
		next = item->next;
		if (next != NULL && next->key == key) {
			item->next = next->next;
			free(next);
			return;
		}
		item = next;
	}
}

void hashmap_free(Hashmap hm)
{
	int i;
	Hashmap_Item item, next;

	for (i = 0; i < HASHMAP_BUCKETS; i++) {
		for (item = hm->buckets[i]; item != NULL;) {
			next = item->next;
			free(item);
			item = next;
		}
	}

	free(hm);
}
