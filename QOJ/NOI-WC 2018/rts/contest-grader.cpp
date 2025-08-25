#include "testlib.h"
#include <cstdio>

unsigned int seed;

inline int nextInt() {
	seed ^= seed << 13;
	seed ^= seed >> 17;
	seed ^= seed << 5;

	seed ^= seed << 13;
	seed ^= seed >> 17;
	seed ^= seed << 5;

	return (seed << 2) >> 2;
}

int n, T, dataType;

int main(int argc, char *argv[]) {
    registerInteraction(argc, argv);

	seed = inf.readInt();
	for (int i = 0; i < 10; i++) {
		nextInt();
	}
    n = inf.readInt();
    T = inf.readInt();
    dataType = inf.readInt();
	n ^= nextInt();
	T ^= nextInt();
	dataType ^= nextInt();
	printf("%d %d %d\n", n, T, dataType); fflush(stdout);
	for (int i = 1; i < n; i++) {
		int u, v;
		u = inf.readInt();
		v = inf.readInt();
		u ^= nextInt();
		v ^= nextInt();
		printf("%d %d\n", u, v); fflush(stdout);
	}

	int x = ouf.readInt(), y = ouf.readInt();
	if (x == 0)
	{
		quitf(_ok, "Accepted! explore() is calles %d time(s).\n", y);
	}
	else
	{
		if (x == -1) quitf(_wa, "explore: too many calls");
		else if (x == -2) quitf(_pe, "explore: argument x (%d) not in [1, n]", y);
		else if (x == -3) quitf(_pe, "explore: argument y (%d) not in [1, n]", y);
		else if (x == -4) quitf(_pe, "explore: argument x = y = %d", y);
		else if (x == -5) quitf(_pe, "explore: node x (%d) not discovered", y);
		else if (x == -6) quitf(_wa, "node %d not discovered after the game", y);
		else quitf(_wa, "unknown option");
	}
	return 0;
}
