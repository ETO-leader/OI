/*
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx")
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("popcnt,avx2")
*/
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100000 + 5;
const int B = 64;
const int LEN = (MAXN + B - 1) / B;

struct MyBitset {
  uint64_t a[LEN];
  inline void clear() {
    #pragma GCC unroll 8
    for (int i = 0; i < LEN; i++) a[i] = 0ULL;
  }
  inline void set0() { a[0] |= 1ULL; }
  inline bool getN(int n) const { return (a[n / B] >> (n & 63)) & 1ULL; }
  static inline void shift1(uint64_t *dst, const uint64_t *src) {
    uint64_t carry = 0;
    #pragma GCC unroll 8
    for (int i = 0; i < LEN; i++) {
      uint64_t x = src[i];
      dst[i] = (x << 1) | carry;
      carry = x >> 63;
    }
  }
  static inline void band(uint64_t *dst, const uint64_t *a, const uint64_t *b) {
    #pragma GCC unroll 8
    for (int i = 0; i < LEN; i++) dst[i] = a[i] & b[i];
  }
  static inline void bor(uint64_t *dst, const uint64_t *src) {
    #pragma GCC unroll 8
    for (int i = 0; i < LEN; i++) dst[i] |= src[i];
  }
  static inline void copy(uint64_t *dst, const uint64_t *src) {
    #pragma GCC unroll 8
    for (int i = 0; i < LEN; i++) dst[i] = src[i];
  }
};

MyBitset Spos[26];
uint64_t ok[LEN], prev_pending[LEN], new_ok[LEN], tmp[LEN];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  freopen("string.in","r",stdin);
  freopen("string.out","w",stdout);
  int T, id; cin >> T >> id;
  while (T--) {
    string s, t;
    cin >> s >> t;
    int n = s.size(), m = t.size();
    for (int c = 0; c < 26; c++) Spos[c].clear();
    for (int i = 0; i < LEN; i++) ok[i] = prev_pending[i] = 0ULL;
    for (int i = 0; i < n; i++) {
      int c = s[i] - 'a';
      Spos[c].a[i >> 6] |= (1ULL << (i & 63));
    }
    ok[0] |= 1ULL;
    int prev_char = -1;
    for (int j = 0; j < m; j++) {
      int c = t[j] - 'a';
      for (int i = 0; i < LEN; i++) new_ok[i] = 0ULL;
      if (prev_char == c) MyBitset::bor(new_ok, prev_pending);
      MyBitset::band(tmp, ok, Spos[c].a);
      MyBitset::shift1(tmp, tmp);
      MyBitset::bor(new_ok, tmp);
      MyBitset::copy(prev_pending, ok);
      MyBitset::copy(ok, new_ok);
      prev_char = c;
    }
    cout << ( ((ok[n >> 6] >> (n & 63)) & 1ULL) ? "YES\n" : "NO\n");
  }
}
