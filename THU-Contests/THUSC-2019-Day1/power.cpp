int N, P, U, V, W, Y, Q;

const int MAXN = 2;
struct Matrix
{
	int a[MAXN][MAXN];
};

Matrix operator *(Matrix x, Matrix y)
{
    // This is a readable (but slower) implementation.
    // You may refer to interactor.cpp for a faster version.
	Matrix z;
	for(int i = 0; i < N; i++)
		for(int j = 0; j < N; j++)
		{
			z.a[i][j] = 0;
			for(int k = 0; k < N; k++)
				z.a[i][j] = ((long long) x.a[i][k] * y.a[k][j] % P + z.a[i][j]) % P;
		}
	return z;
}
Matrix unit()
{
    Matrix x;
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            x.a[i][j] = (i == j);
    return x;
}
Matrix process(Matrix x)
{
    int sum = 0;
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            if(i != U || j != V)
                sum = ((long long) sum + x.a[i][j]) % P;
    x.a[U][V] = ((long long) sum * W % P + Y) % P;
    return x;
}
Matrix power(Matrix x)
{
    x = process(x);
    Matrix ans = unit();
    for(int i = 0; i < 31; i++)
    {
        if(Q >> i & 1) ans = ans * x;
        x = x * x;
    }
    return x;
}
