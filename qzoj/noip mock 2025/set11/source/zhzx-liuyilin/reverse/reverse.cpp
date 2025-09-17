/* by IceKylin */

#include <bits/stdc++.h>
using namespace std;

#ifndef ONLINE_JUDGE
struct ReadFile {
  ReadFile() {
    assert(freopen("reverse.in", "r", stdin));
    assert(freopen("reverse.out", "w", stdout));
  }
} read_file;
#endif

using uint = unsigned int;
using ll   = long long;
using ull  = unsigned long long;

#define __FREAD__
namespace Fread {

constexpr int size = 1 << 20;
char buf[size]; int p1 = -1, p2;
inline char getchar() {
  if (++p1 == p2) {
    p2 = fread(buf, 1, size, stdin), p1 = 0;
    if (!p2) return EOF;
  }
  return buf[p1];
}
inline char getchar_unchecked() {
  return buf[++p1];
}

}

#define __FWRITE__
namespace Fwrite {

constexpr int size = 1 << 20;
char buf[size + 1]; int p = -1;
inline void flush() {
  fwrite(buf, 1, p + 1, stdout), p = -1;
}
inline void putchar(char ch) {
  buf[++p] = ch;
  if (p == size) flush();
}
inline void putchar_unchecked(char ch) {
  buf[++p] = ch;
}
struct Exit {
  ~Exit() { flush(); }
} exit;

}

#define __FAST_IO__
namespace FastIO {

static bool is_blank(char ch) {
  return ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r';
}

/* read */
#ifdef __MMAP__
using Mmap::getchar;
#elif defined(__FREAD__)
using Fread::getchar;
#endif
template <class T = int>
T read() {
  T x = 0; bool neg = false; char ch = getchar();
  for (; !isdigit(ch); ch = getchar()) if (ch == '-') neg = true;
  for (; isdigit(ch); ch = getchar()) x = x * 10 + (ch & 15);
  return neg ? -x : x;
}
template <class T>
T read(T& x) { return x = read<T>(); }
inline void read(char& ch) {
  ch = getchar();
  while (is_blank(ch)) ch = getchar();
}
inline void read(string& s) {
  s.clear(); char ch = getchar();
  while (is_blank(ch)) ch = getchar();
  while (!is_blank(ch)) {
    if (ch == EOF) return;
    s.push_back(ch), ch = getchar();
  }
}
template <class T1, class T2>
void read(pair<T1, T2>& a) { read(a.first), read(a.second); }
template <class T, class... R>
void read(T& x, R& ...args) { read(x), read(args...); }
template <class It>
void read_each(It first, It last) {
  for (; first != last; ++first) read(*first);
}

/* write */
#ifdef __FWRITE__
using Fwrite::putchar;
#endif
template <class T>
void write(T x) {
  if (x < 0) putchar('-'), x = -x;
  static int digits[39]; int cnt = 0;
  do { digits[cnt++] = x % 10, x /= 10; } while (x);
  while (cnt) putchar(digits[--cnt] | 48);
}
inline void write(char ch) { putchar(ch); }
inline void write(const char* s) { while (*s != '\0') putchar(*s++); }
inline void write(string s) { for (char ch : s) putchar(ch); }
template <class T, class... R>
void write(T x, R ...args) { write(x), write(args...); }
template <class... R>
void writeln(R ...args) { write(args...), putchar('\n'); }
template <class It>
void write_each(It first, It last, const char* sep = " ", const char* end = "\n") {
  if (first == last) { write(end); return; }
  write(*first);
  for (++first; first != last; ++first) write(sep, *first);
  write(end);
}

}
using namespace FastIO;

constexpr int N = 1e6 + 5;

inline constexpr int hole(int x) {
  return x + (x >> 10);
}

int id, n, k, a[N], bit[hole(N) + 10], cnt, tot, bitc;

inline void add(int x) {
  ++bitc;
  for (; x <= n; x += x & -x) ++bit[hole(x)];
}
inline void del(int x) {
  --bitc;
  for (; x <= n; x += x & -x) --bit[hole(x)];
}
inline int query(int x, int k = 0) {
  for (; x; x &= (x - 1)) k += bit[hole(x)];
  return k;
}
vector<pair<int, int>> ans;
int main() {
  read(id, n, k);
  for (int i = 1; i <= n; ++i) {
    read(a[i]);
  }
  for (int i = n; i >= 1; --i) {
    add(a[i]), tot += query(a[i] - 1);
  }
  memset(bit, 0, sizeof(bit));
  bitc = 0;
  tot -= k;
  while (tot > 0) {
    int l = 1, r = 1, cur = 0, ansl = 1, ansr = 1, mx = 0;
    add(a[1]);
    while (true) {
      while (r < n && cur <= tot) {
        if (cur > mx) ansl = l, ansr = r, mx = cur;
        add(a[++r]), cur += bitc - query(a[r]);
      }
      if (cur <= tot) {
        if (cur > mx) ansl = l, ansr = r, mx = cur;
        break;
      }
      del(a[l]), cur -= query(a[l] - 1);
      if (++l > n) break;
    }
    tot -= mx;
    ans.emplace_back(ansl, ansr);
    sort(a + ansl, a + ansr + 1);
    memset(bit, 0, sizeof(bit));
    bitc = 0;
  }
  writeln(ans.size());
  for (auto x : ans) {
    writeln(x.first, ' ', x.second);
  }
  return 0;
}