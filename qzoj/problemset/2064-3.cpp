#include <bits/stdc++.h>
using namespace std;

#pragma GCC target("popcnt")
#pragma GCC optimize("Ofast,unroll-loops")

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    if (!(cin >> n >> m)) return 0;
    vector<string> s(n);
    for (int i = 0; i < n; ++i) cin >> s[i];

    const int W = (m + 63) >> 6; // number of 64-bit blocks
    vector<vector<uint64_t>> row(W ? n : 0, vector<uint64_t>(W, 0));

    // pack rows into 64-bit words: bit j of row[i] is column j (LSB is lower column index)
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (s[i][j] == '1') {
                int w = j >> 6;
                int b = j & 63;
                row[i][w] |= (1ull << b);
            }
        }
    }

    unsigned long long ans = 0;
    vector<uint64_t> ColXor(W); // C[c] in 64-bit blocks

    // iterate top row r1
    for (int r1 = 0; r1 < n; ++r1) {
        // reset ColXor
        fill(ColXor.begin(), ColXor.end(), 0ull);

        // extend bottom row r2
        for (int r2 = r1; r2 < n; ++r2) {
            // update column xor with row r2: C ^= row[r2]
            for (int w = 0; w < W; ++w) ColXor[w] ^= row[r2][w];

            // Now we need to compute equalPairs:
            // iterate over columns in block order, keep running_par = U[pos] (parity up to previous bit)
            unsigned long long equalPairs = 0;
            unsigned long long onesQ = 0; // number of ones in Q up to previous position
            unsigned char running_par = 0; // U[pos] for current pos

            for (int w = 0; w < W; ++w) {
                uint64_t Sword = row[r1][w] ^ row[r2][w]; // S bits for this block
                uint64_t Cword = ColXor[w];               // C bits for this block

                // process each bit in the 64-bit block
                // position index = w*64 + k
                int base = w << 6;
                // unroll by 1... simple loop (most time is here)
                for (int k = 0; k < 64; ++k) {
                    int pos = base + k;
                    if (pos >= m) break; // last block may be partial
                    unsigned char sbit = (Sword >> k) & 1u;
                    unsigned char u = running_par;       // U[pos]
                    unsigned char u_next = u ^ sbit;     // U[pos+1]
                    unsigned char cbit = (Cword >> k) & 1u; // C[pos]
                    unsigned char Qbit = u ^ cbit;       // Q[pos] = U[pos] xor C[pos]
                    unsigned char Pbit = u_next ^ cbit;  // P[pos] = U[pos+1] xor C[pos]
                    // update prefix ones of Q (includes this pos)
                    onesQ += Qbit;
                    if (Pbit) {
                        equalPairs += onesQ;
                    } else {
                        equalPairs += (unsigned long long)(pos + 1) - onesQ;
                    }
                    running_par = u_next;
                }
            }

            unsigned long long totalIntervals = (unsigned long long)m * (m + 1ull) / 2ull;
            unsigned long long oddCount = totalIntervals - equalPairs;
            ans += oddCount;
        }
    }

    cout << ans << '\n';
    return 0;
}
