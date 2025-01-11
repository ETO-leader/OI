#include "attack.h"
#include <signal.h>
#include <bits/stdc++.h>
using namespace std;

static int N, P, U, V, W, Y, Q;

#define die(x...) do{rewind(stdout); puts("0"); printf(x); puts(""); exit(1);} while(0)

static void signal_handler(int signum)
{
    die("Runtime error: %s (%d)", strsignal(signum), signum);
}

static int read_int(char name, int l, int r)
{
    int x;
    if(scanf("%d", &x) != 1) die("Illegal input: can't read integer %c", name);
    if(x < l || x > r) die("Illegal input: got %c = %d, out of range [%d, %d]", name, x, l, r);
    return x;
}

static bool is_prime(int x)
{
    if(x <= 1) return false;
    for(int i = 2; i * i <= x; ++i) if(!(x % i)) return false;
    return true;
}

static bool got_u, got_v, got_w, got_y, got_q;
int get_u()
{
    got_u = true;
    return U;
}
int get_v()
{
    got_v = true;
    return V;
}
int get_w()
{
    got_w = true;
    return W;
}
int get_y()
{
    got_y = true;
    return Y;
}
int get_q()
{
    got_q = true;
    return Q;
}

static int cost = 0;
static inline int count_bit(int x)
{
    return x ? 32 - __builtin_clz(x) : 1;
}
static inline long long mul(int x, int y, int &local_cost)
{
    local_cost += count_bit(x) * count_bit(y);
    return (long long) x * y % P;
}
static Matrix operator *(const Matrix &x, const Matrix &y)
{
    // This is a not-so-readable but slightly faster version.
    // You may look at power.cpp to figure out how to multiply two matrices.
    // The commented-out code below more clearly shows how to calculate the cost.
    // Feel free to copy any code to your program if you need.
	Matrix z;
    int local_cost = cost;
#define CALC(i, j, k) z.a[i][j] = (mul(x.a[i][k], y.a[k][j], local_cost) + z.a[i][j]) % P;
#define CALC1(i, j) z.a[i][j] = 0; CALC(i, j, 0);
#define CALC2(i, j) CALC1(i, j); CALC(i, j, 1);
    if(N == 2)
    {
        CALC2(0, 0); CALC2(0, 1);
        CALC2(1, 0); CALC2(1, 1);
    }
    else if(N == 1)
    {
        CALC1(0, 0);
    }
    cost = local_cost;
#undef CALC2
#undef CALC1
#undef CALC
	return z;
}
/*
static Matrix operator *(const Matrix &x, const Matrix &y)
{
	Matrix z;
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
        {
            z.a[i][j] = 0;
            for(int k = 0; k < N; k++)
                z.a[i][j] = (z.a[i][j] + mul(x.a[i][k], y.a[k][j], cost)) % P;
        }
    return z;
}
*/
static Matrix unit()
{
    Matrix x;
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            x.a[i][j] = (i == j);
    return x;
}
static Matrix process(Matrix x)
{
    int sum = 0;
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            if(i != U || j != V)
                sum = ((long long) sum + x.a[i][j]) % P;
    // x.a[U][V] = (mul(sum, W, cost) % P + Y) % P;
    x.a[U][V] = (sum * W % P + Y) % P;
    return x;
}
static Matrix power(Matrix x)
{
    x = process(x);
    Matrix ans = unit();
    for(int i = 0; i < 31; i++)
    {
        if(Q >> i & 1) ans = ans * x;
        x = x * x;
    }
    return ans;
}

static int get_time_calls;
int get_time(Matrix x)
{
    if(get_time_calls >= 1000000) die("Too many calls to get_time: you called >1000000 times!");
    ++get_time_calls;
    
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            if(x.a[i][j] < 0 || x.a[i][j] >= P)
                die("Illegal parameter: x.a[%d][%d] = %d out of range", i, j, x.a[i][j]);
    
    cost = 0;
    power(x);
    return cost;
}

int main()
{
    N = read_int('N', 1, 3);
    P = read_int('P', 1 << 7, (1u << 31) - 1);
    U = read_int('U', 0, N - 1);
    V = read_int('V', 0, N - 1);
    W = read_int('W', 1, P - 1);
    Y = read_int('Y', 1, P - 1);
    Q = read_int('Q', 1, P - 1);
    
    got_u = got_v = got_w = got_y = got_q = 0;
    get_time_calls = 0;
    
    if(!is_prime(P)) die("Illegal input: P = %d is not a prime number", P);
    
    int outU = -1, outV = -1, outQs[500];
    memset(outQs, 0xff, sizeof(outQs));
    
    for(int i = 1; i <= 31; ++i) signal(i, signal_handler);
    attack(N, P, outU, outV, outQs);
    
    int get_time_calls_saved = get_time_calls;
    
    if(outU != U) die("Wrong answer: you returned U = %d but answer is %d", outU, U);
    if(outV != V) die("Wrong answer: you returned V = %d but answer is %d", outV, V);
    
    static char info[1 << 20];
    char *pinfo = info;
    
    pinfo += sprintf(pinfo, "Your answer U = %d, V = %d is correct.\n", outU, outV);
    pinfo += sprintf(pinfo, "The correct Q should be %d.\n", Q);
    
    bool ok = false;
    for(int i = 0; i < 500; ++i) if(outQs[i] == Q)
    {
        pinfo += sprintf(pinfo, "Your answer Qs[%d] matches the answer!\n", i);
        ok = true;
    }
    
    if(!ok)
    {
        pinfo += sprintf(pinfo, "None of your answers in Qs[] is correct.\n");
        pinfo += sprintf(pinfo, "Your Qs is:\n");
        for(int i = 0; i < 100; ++i)
        {
            for(int j = 0; j < 5; ++j)
                pinfo += sprintf(pinfo, "%11d", outQs[i * 5 + j]);
            pinfo += sprintf(pinfo, "\n");
        }
        die("Wrong answer:\n%s", info);
    }
    
    int score = 100;
    if(got_u)
    {
        pinfo += sprintf(pinfo, "You called get_u and lost 10 points.\n");
        score -= 10;
    }
    if(got_v)
    {
        pinfo += sprintf(pinfo, "You called get_v and lost 10 points.\n");
        score -= 10;
    }
    if(got_w)
    {
        pinfo += sprintf(pinfo, "You called get_w and lost 20 points.\n");
        score -= 20;
    }
    if(got_y)
    {
        pinfo += sprintf(pinfo, "You called get_y and lost 20 points.\n");
        score -= 20;
    }
    if(got_q)
    {
        pinfo += sprintf(pinfo, "You called get_q and lost 80 points.\n");
        score -= 80;
    }
    pinfo += sprintf(pinfo, "You called get_time %d times.\n", get_time_calls_saved);
    if(get_time_calls_saved > 50000)
    {
        pinfo += sprintf(pinfo, "That's too many times, and you lost 100 points.\n");
        score -= 100;
    }
    pinfo += sprintf(pinfo, "Your score is %d.\n", score);
    if(score < 0)
    {
        pinfo += sprintf(pinfo, "That's too low. Let your score be 0 then.\n");
        score = 0;
    }
    printf("%d\nCorrect answer:\n%s", score, info);
    return 0;
}
