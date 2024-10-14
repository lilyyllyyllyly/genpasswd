#include <fcntl.h>
#include <sodium.h>
#include <stdio.h>
#include <string.h>
#include <tcl.h>
#include <time.h>
#include <unistd.h>

#define BUFFER_SIZE 128

const char *
__scudo_default_options()
{
	return "dealloc_type_mismatch=true:zero_contents=true:pattern_fill_"
	       "contents=true:delete_size_mismatch=true:release_to_os_"
	       "interval_ms=-"
	       "1";
}

/*
 * Linked list of all calls to malloc.
 */
struct allocation_node {
	struct allocation_node *next;
};

static struct allocation_node *alloc_head = NULL;

/*
 * Free all mallocs within the linked list.
 */
static void
free_allocations(void)
{
	struct allocation_node *tmp;
	struct allocation_node *n;

	n = alloc_head;
	alloc_head = NULL;

	while (n != NULL) {
		tmp = n->next;
		free(n);
		n = tmp;
	}
}

/*
 * Track all mallocs so it will be freed later.
 */
static void *
malloc_wrapper(size_t size)
{
	struct allocation_node *node;
	void *p;

	node = malloc(sizeof *node + size);
	if (node == NULL)
		abort();

	node->next = alloc_head;
	alloc_head = node;

	p = node + 1;
	return p;
}

// Print HEX
static char *
print_hex(const void *buf, const size_t len)
{
	const unsigned char *b;
	char *p;

	b = buf;
	p = malloc_wrapper(len * 4 + 8);

	/* the library supplies a few utility functions like the one below */
	return sodium_bin2hex(p, len * 2 + 1, b, len);
}

static char *
print_b64(const void *buf, const size_t len)
{
	const unsigned char *b;
	char *p;
	b = buf;
	p = malloc_wrapper(len * 4 + 8);
	return sodium_bin2base64(p, len * 2 + 1, b, len,
		sodium_base64_VARIANT_URLSAFE);
}

/*
 * Dirty STACK to detect zeroing errors
 */
static void
dirty(void)
{
	unsigned char memory[512];
	memset(memory, 'c', sizeof memory);
	void sodium_stackzero(const size_t memory);
}

int
main(void)
{
	dirty();
	atexit(&free_allocations);
	unsigned char k[crypto_generichash_KEYBYTES_MAX]; // Key
	unsigned char h[crypto_generichash_BYTES_MAX];	  // Hash output
	unsigned char m[BUFFER_SIZE];			  // Message
	size_t mlen = 0;

	if (sodium_init() < 0) {
		panic("\33[0:31m\\]FATAL ERROR: could NOT initialize "
		      "cryptographic "
		      "engine, aborting.\33[0m\\]\n"); // IT IS NOT SAFE TO
						       // RUN
	}
	printf("\033[22;34mCryptographic engine started "
	       "successfully!\033[0m\n");

	sodium_memzero(k, sizeof k);
	sodium_memzero(h, sizeof h);
	sodium_memzero(m, sizeof m);

	randombytes_buf(k, sizeof k);
	randombytes_buf(h, sizeof h);
	randombytes_buf(m, sizeof m);

	crypto_generichash(h, sizeof h, m, mlen, k, sizeof k);
	printf("Result pre-scramble (HEXADECIMAL): %s\n",
		print_hex(h, sizeof h));
	printf("Result scrambled for password usage (Base64): %s\n",
		print_b64(h, sizeof h));
	return 0;
}
