#include <bits/stdc++.h>
using namespace std;

// Input and output files
ifstream inputFile("stole.in");
ofstream outputFile("stole.out");

class FileHandler {
public:
    ~FileHandler() {
        inputFile.close();
        outputFile.close();
    }
} fileHandler;

using ull = unsigned long long;

class MathUtils {
private:
    const int mod;

public:
    constexpr MathUtils(int p) : mod(p) {}

    constexpr ull modPow(ull base, ull exp) const {
        ull result = 1;
        while (exp) {
            if (exp & 1) result = (result * base) % mod;
            base = (base * base) % mod;
            exp >>= 1;
        }
        return result;
    }

    constexpr ull modInverse(ull x) const {
        return modPow(x, mod - 2);
    }
};

class LagrangeInterpolation {
public:
    ull interpolate(const vector<ull>& y, const vector<ull>& x, ull evalX, int mod) const {
        int n = y.size();
        ull result = 0;
        MathUtils math(mod);

        for (int i = 0; i < n; ++i) {
            ull term = y[i];
            for (int j = 0; j < n; ++j) {
                if (i != j) {
                    term = term * (evalX + mod - x[j]) % mod * math.modInverse((x[i] + mod - x[j]) % mod) % mod;
                }
            }
            result = (result + term) % mod;
        }
        return result;
    }
};

int main() {
    ios::sync_with_stdio(false);
    inputFile.tie(nullptr);

    int n, r, mod;
    inputFile >> n >> r >> mod;

    MathUtils math(mod);

    // Precompute factorials and modular inverses
    vector<ull> factorial(n + 7, 1), invFactorial(n + 7);
    for (int i = 1; i < n + 7; ++i) {
        factorial[i] = factorial[i - 1] * i % mod;
    }
    for (int i = 0; i < n + 7; ++i) {
        invFactorial[i] = math.modInverse(factorial[i]);
    }

    auto combination = [&](int a, int b) -> ull {
        if (a < b) return 0;
        return factorial[a] * invFactorial[b] % mod * invFactorial[a - b] % mod;
    };

    const int m = min(n * (n - 1) / 2, r) + 7;

    // DP table for computing f
    vector<vector<ull>> f(n + 1, vector<ull>(m + 1));
    fill(f[1].begin() + 1, f[1].end(), 1);

    for (int w = 1; w <= m; ++w) {
        vector<ull> powers(n * n + 7, 1);
        for (int i = 1; i < n * n + 7; ++i) {
            powers[i] = powers[i - 1] * (mod + r - w + 2) % mod;
        }

        vector<vector<ull>> g(n + 1, vector<ull>(n + 1));
        g[1][0] = 1;

        for (int a = 2; a <= n; ++a) {
            f[a][w] = f[a][w - 1];
            g[a][0] = f[a][w - 1];

            for (int k = 1; k < n; ++k) {
                for (int b = 1; b < a; ++b) {
                    for (int x = 0; x < k; ++x) {
                        ull temp = g[b][x] * g[a - b][k - x - 1] % mod;
                        temp = temp * combination(a, 2) % mod;
                        temp = temp * combination(a - 2, b - 1) % mod;
                        temp = temp * powers[b * (a - b) - 1] % mod;
                        g[a][k] = (g[a][k] + temp) % mod;
                    }
                }
                g[a][k] = g[a][k] * math.modInverse(k) % mod;
                f[a][w] = (f[a][w] + g[a][k]) % mod;
            }
        }
    }

    vector<ull> fValues(m), positions(m);
    iota(positions.begin(), positions.end(), 1);
    for (int i = 0; i < m; ++i) {
        fValues[i] = f[n][i + 1];
    }

    LagrangeInterpolation lagrange;
    outputFile << lagrange.interpolate(fValues, positions, r, mod) << '\n';

    return 0;
}
