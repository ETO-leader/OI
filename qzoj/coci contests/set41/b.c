// compile: gcc -O2 -march=native -pipe -static -s -o solve solve.c
// 注意: -static 可选，按评测要求决定是否使用
#define _GNU_SOURCE
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef long long ll;

/* ---------- fast raw read (read syscall) ---------- */
static const size_t READ_BLOCK = 1<<20;
static char *inbuf = NULL;
static size_t inlen = 0, inpos = 0;
static void refill_inbuf() {
    ssize_t r;
    // expand buffer if needed
    if(inbuf == NULL) {
        inbuf = (char*)malloc(READ_BLOCK);
        inlen = 0; inpos = 0;
    }
    // try to read more (append)
    r = read(0, inbuf + inlen, READ_BLOCK);
    if(r > 0) inlen += (size_t)r;
    // if r==0 -> EOF, leave as is
}
static inline int next_char() {
    if(inpos >= inlen) {
        // try to read once more
        ssize_t r = read(0, inbuf == NULL ? (inbuf = (char*)malloc(READ_BLOCK), inbuf) : inbuf + inlen, READ_BLOCK);
        if(r > 0) {
            inlen += (size_t)r;
        } else {
            return -1;
        }
    }
    return (unsigned char)inbuf[inpos++];
}
static long long read_int() {
    int c = next_char();
    while(c != -1 && c <= ' ') c = next_char();
    if(c == -1) return 0;
    int sign = 0;
    if(c == '-') { sign = 1; c = next_char(); }
    long long x = 0;
    while(c > ' ') {
        x = x*10 + (c - '0');
        c = next_char();
    }
    return sign ? -x : x;
}

/* ---------- fast write ---------- */
static char outbuf[1<<20];
static size_t outpos = 0;
static void flush_out() {
    if(outpos) {
        write(1, outbuf, outpos);
        outpos = 0;
    }
}
static void write_ll_ln(long long x) {
    if(outpos > sizeof(outbuf) - 40) flush_out();
    if(x == 0) {
        outbuf[outpos++] = '0';
        outbuf[outpos++] = '\n';
        return;
    }
    if(x < 0) {
        outbuf[outpos++] = '-';
        x = -x;
    }
    char s[32]; int p=0;
    while(x) { s[p++] = '0' + (x%10); x/=10; }
    while(p--) outbuf[outpos++] = s[p];
    outbuf[outpos++] = '\n';
}

/* ---------- qsort compare ---------- */
static int cmp_int(const void *aa, const void *bb){
    int a = *(const int*)aa;
    int b = *(const int*)bb;
    return (a > b) - (a < b);
}

/* ---------- DSU ---------- */
static int *parent_;
static int findp(int x){
    int r = x;
    while(parent_[r] != r) r = parent_[r];
    // path compress
    while(parent_[x] != r){ int t = parent_[x]; parent_[x] = r; x = t; }
    return r;
}
static void unite(int x,int y){
    parent_[findp(x)] = findp(y);
}

/* ---------- main algorithm ---------- */
int main(){
    // read entire input chunks (we will call next_char/read_int as needed)
    // parse n and array
    long long tn = read_int();
    int n = (int)tn;
    if(n <= 0) { write_ll_ln(0); flush_out(); return 0; }

    int *t = (int*)malloc((size_t)n * sizeof(int));
    for(int i=0;i<n;i++){
        t[i] = (int)read_int();
    }

    // sort and unique
    qsort(t, n, sizeof(int), cmp_int);
    int *a = (int*)malloc((size_t)n * sizeof(int));
    int k = 0;
    for(int i=0;i<n;i++){
        if(i==0 || t[i] != t[i-1]) a[k++] = t[i];
    }
    free(t);
    if(k == 0){
        free(a);
        write_ll_ln(0); flush_out();
        return 0;
    }

    int mxa = a[k-1];
    // id array size mxa+2
    int id_size = mxa + 2;
    int *id = (int*)malloc((size_t)id_size * sizeof(int));
    for(int i=0;i<id_size;i++) id[i] = -1;
    int las = -1;
    for(int i=0;i<k;i++){
        int upto = a[i];
        for(int x = las+1; x <= upto; ++x) id[x] = i;
        las = upto;
    }

    // First pass: count number of edges per delta (0..mxa)
    int *cnt = (int*)calloc((size_t)(mxa+1), sizeof(int));
    long long total_edges = 0;
    for(int ix=0; ix<k; ix++){
        int x = a[ix];
        for(int w = x; w <= mxa; w += x){
            int idx = w + (w==x ? 1 : 0);
            if(idx > mxa+1) continue;
            int upb = id[idx];
            if(upb >= 0){
                int delta = a[upb] - w;
                if(delta < x){
                    cnt[delta]++;
                    total_edges++;
                }
            }
        }
    }

    // prefix sums -> offsets
    int *pos = (int*)malloc((size_t)(mxa+2) * sizeof(int)); // pos[i] start index for bucket i
    pos[0] = 0;
    for(int i=0;i<=mxa;i++) pos[i+1] = pos[i] + cnt[i];

    // allocate edge arrays contiguous
    int *edge_u = (int*)malloc((size_t) (total_edges>0 ? total_edges : 1) * sizeof(int));
    int *edge_v = (int*)malloc((size_t) (total_edges>0 ? total_edges : 1) * sizeof(int));
    // reuse cnt as write pointer (initialize to pos)
    for(int i=0;i<=mxa;i++) cnt[i] = pos[i];

    // Second pass: fill edges
    for(int ix=0; ix<k; ix++){
        int x = a[ix];
        for(int w = x; w <= mxa; w += x){
            int idx = w + (w==x ? 1 : 0);
            if(idx > mxa+1) continue;
            int upb = id[idx];
            if(upb >= 0){
                int delta = a[upb] - w;
                if(delta < x){
                    int p = cnt[delta]++;
                    edge_u[p] = ix;
                    edge_v[p] = upb;
                }
            }
        }
    }

    // DSU
    parent_ = (int*)malloc((size_t)k * sizeof(int));
    for(int i=0;i<k;i++) parent_[i] = i;

    // Kruskal-like: iterate deltas from 0..mxa
    ll ans = 0;
    for(int d=0; d<=mxa; d++){
        int start = pos[d], end = pos[d+1];
        for(int p = start; p < end; p++){
            int u = edge_u[p], v = edge_v[p];
            if(findp(u) != findp(v)){
                unite(u,v);
                ans += d;
            }
        }
    }

    // output
    write_ll_ln(ans);
    flush_out();

    // free
    free(inbuf);
    free(a); free(id); free(cnt); free(pos);
    free(edge_u); free(edge_v); free(parent_);

    return 0;
}
