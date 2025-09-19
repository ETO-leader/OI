#include <math.h>
#include <random>
#include <vector>
#include <time.h>
#include <stdio.h>
#include <algorithm>
using namespace std;
extern vector<int> Encode(vector<int>);
extern vector<int> Decode(vector<int>);
const int mod = 998244353;
const int test_time = 10000;
mt19937 rndint(0);
vector<int> in, out, tmp;
int getmark(int);
void wa();
int main()
{
	int x, sum = 100;
	in.resize(100);
	for (int i = 0; i < test_time; ++i)
	{
		for (int j = 0; j < 100; ++j)
			in[j] = rndint() % mod;
		tmp = Encode(in);
		tmp = Encode(in);
		tmp = Encode(in);
		for (int j : tmp)
			if (j < 0 || j >= mod)
				wa();
		for (int j = 0; j < tmp.size(); ++j)
			if (rndint() & 1)
				tmp[j] = rndint() % mod;
		out = Decode(tmp);
		if (out.size() != 100)
			wa();
		for (int j = 0; j < 100; ++j)
			if (in[j] != out[j])
				wa();
		sum = min(sum, getmark(tmp.size()));
	}
	printf ("%d\n", sum);
	return 0;
}

int getmark(int a)
{
	if (!a)
		return 0;
	return min(100, int(1500 / ceil(a * 0.02)));
}

void wa()
{
	puts("Illegaled operation");
	exit(0);
}
