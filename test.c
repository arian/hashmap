
#include <assert.h>
#include <stdio.h>

#include "hashmap.h"

void loop(void * value, void * key, int k)
{
	printf("(%d) %s - %s\n", k, (char *) value, (char *) key);
}

int main(void)
{

	char *key = "hello";
	char *key2 = "hey";
	char *key3 = "hey 1";
	char *key4 = "hey 2";
	char *key5 = "hey 3";
	char *key6 = "hey 9";
	Hashmap hm;
	char * ret;

	hm = hashmap_create(10);

	hashmap_set(hm, key, "bar");
	hashmap_set(hm, key2, "bar 2");
	hashmap_set(hm, key3, "bar 2");
	hashmap_set(hm, key4, "bar 2");
	hashmap_set(hm, key5, "bar 2");
	hashmap_set(hm, key6, "bar 2");

	hashmap_each(hm, loop);
	printf("\n");

	hashmap_delete(hm, key3);
	hashmap_delete(hm, key4);
	hashmap_delete(hm, key5);
	hashmap_delete(hm, key6);

	ret = hashmap_get(hm, key);
	hashmap_each(hm, loop);

	hashmap_free(hm);

	if (ret == NULL)
		printf("ret is null\n");
	else
		printf("%s\n", ret);

	return 0;
}
