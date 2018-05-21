#include <stdlib.h>
#include <string.h>
void test() {
	int *p = malloc(sizeof(int));
	free(p);
	*p = 1; // warn: use after free
}

int f(int *p) __attribute__((nonnull));
int f(int *p) { return *p; }

void nonnullAttribute(int *p) {
	if (!p)
		f(p); // warn
}

void resultGarbage() {
	int x;
	int y = x + 1; // warn: left operand is garbage
}

void accessOutOfBound() {
	strcpy("small","enormous");
}

void divideZero(int z) {
	if (z == 0) {
		int x = 1 / z;
	}
}

void useAfterFree() {
	int *p = malloc(sizeof(int));
	free(p);
	*p = 1; // warn: use after free
}

void doubleFree() {
	int *p = malloc(1);
	free(p);
	free(p); // warn: attempt to free released memory
}

void uninitializedValue() {
	void (*foo)(void);
	foo(); // warn: function pointer is uninitialized
}

void memoryLeak() {
	int *p = malloc(1);
	if (p)
		return; // warn: memory is never released
}

void nullDereference(int *p) {
	if (!p)
		*p = 0; // warn
}

void allocateZero() {
	void *p = malloc(0); // warn: allocation size of 0 bytes
}

void allocatorSizeOfMismatch() {
	long *p = malloc(sizeof(short));
	// warn: result is converted to 'long *', which is
	// incompatible with operand type 'short'
	free(p);
}

int main() {
	int i = 0;
	return 0;
}
