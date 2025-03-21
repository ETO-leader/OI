#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;

typedef unsigned int u32;
typedef unsigned long long u64;

inline u32 next_integer(u32 x) {
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    return x;
}

bool output_arr(void *a, u32 size) {
    if (size % 4) {
        return puts("-1"), 0;
    }

    u32 blocks = size / 4;
    u32 *A = (u32 *)a;
    u32 ret = size;
    u32 x = 23333333;
    for (u32 i = 0; i < blocks; i++) {
        ret = ret ^ (A[i] + x);
        x ^= x << 13;
        x ^= x >> 17;
        x ^= x << 5;
    }

    return printf("%u\n", ret), 1;
}

// ===== header ======

namespace Sorting {

void init_data(u32 *a, int n, u32 seed) {
    for (int i = 0; i < n; i++) {
        seed = next_integer(seed);
        a[i] = seed;
    }
}


auto usort(uint*a,const int n){
    static array<int,(1<<8)> cnt;
    memset(cnt.begin(),0,sizeof(cnt));
    auto b=new uint[n];
    const auto usr=(1<<8)-1;
    cir(i,0,n) ++cnt[a[i]&usr];
    auto pre=0;
    cir(i,0,(1<<8)){
        const auto lc=cnt[i];
        cnt[i]=pre;
        pre+=lc;
    }
    cir(i,0,n) b[cnt[a[i]&usr]]=a[i],++cnt[a[i]&usr];
    
    memset(cnt.begin(),0,sizeof(cnt));
    cir(i,0,n) ++cnt[(b[i]>>8)&usr];
    pre=0;
    cir(i,0,(1<<8)){
        const auto lc=cnt[i];
        cnt[i]=pre;
        pre+=lc;
    }
    cir(i,0,n) a[cnt[(b[i]>>8)&usr]]=b[i],++cnt[(b[i]>>8)&usr];
    
    memset(cnt.begin(),0,sizeof(cnt));
    cir(i,0,n) ++cnt[(a[i]>>16)&usr];
    pre=0;
    cir(i,0,(1<<8)){
        const auto lc=cnt[i];
        cnt[i]=pre;
        pre+=lc;
    }
    cir(i,0,n) b[cnt[(a[i]>>16)&usr]]=a[i],++cnt[(a[i]>>16)&usr];
    
    memset(cnt.begin(),0,sizeof(cnt));
    cir(i,0,n) ++cnt[(b[i]>>24)&usr];
    pre=0;
    cir(i,0,(1<<8)){
        const auto lc=cnt[i];
        cnt[i]=pre;
        pre+=lc;
    }
    cir(i,0,n) a[cnt[(b[i]>>24)&usr]]=b[i],++cnt[(b[i]>>24)&usr];

    delete[] b;
}

void main() {
    int n;
    u32 seed;
    scanf("%d%u", &n, &seed);

    u32 *a = new u32[n];
    init_data(a, n, seed);

    usort(a, n);

    output_arr(a, n * sizeof(u32));
    delete[] a;
}
}

namespace Game {

template<const int len>
class _Bitset{
private:
    array<uint64_t,(len+63)/64> b;
public:
    auto set(uint p){
        b[p>>6]|=(1ull<<(p&63));
    }
    auto and_cnt(const _Bitset&c,const auto spu,const auto spc,const int k){
        auto res=0u;
        auto res0=0,res1=0,res2=0,res3=0,res4=0,res5=0,res6=0,res7=0;
        const auto al=spu>>6;
        const auto bl=spc>>6;
        auto i=0;
        for(;i+8<(k>>6);i+=8){
            res0+=popcount(b[al+i]&c.b[bl+i]);
            res1+=popcount(b[al+i+1]&c.b[bl+i+1]);
            res2+=popcount(b[al+i+2]&c.b[bl+i+2]);
            res3+=popcount(b[al+i+3]&c.b[bl+i+3]);
            res4+=popcount(b[al+i+4]&c.b[bl+i+4]);
            res5+=popcount(b[al+i+5]&c.b[bl+i+5]);
            res6+=popcount(b[al+i+6]&c.b[bl+i+6]);
            res7+=popcount(b[al+i+7]&c.b[bl+i+7]);
        }
        res=res0+res1+res2+res3+res4+res5+res6+res7;
        for(;i<(k>>6);++i) res+=popcount(b[al+i]&c.b[bl+i]);
        res+=popcount((b[al+(k>>6)]&c.b[bl+(k>>6)])&((1ull<<(k&63))-1));
        return res;
    }
    _Bitset(){memset(b.begin(),0,sizeof(b));}
};

static constexpr auto maxn=(int)(3e5+7);

auto solve(const int n,const int q,const char*s1,const char*s2,const int*q_x,const int*q_y,const int*q_len,uint*ans){
    static array<array<_Bitset<maxn>,64>,3> bx,by;
    cir(c,0,64){
        cir(i,c,n) bx[s1[i]-'0'][c].set(i-c);
        cir(i,c,n) by[s2[i]-'0'][c].set(i-c);
    }
    cir(i,0,q){
        const auto qx=q_x[i],qy=q_y[i],ql=q_len[i];
        const auto ans0=bx[0][qx&63].and_cnt(by[1][qy&63],qx,qy,ql);
        const auto ans1=bx[1][qx&63].and_cnt(by[2][qy&63],qx,qy,ql);
        const auto ans2=bx[2][qx&63].and_cnt(by[0][qy&63],qx,qy,ql);
        ans[i]=ans0+ans1+ans2;
    }
}

void main() {
    int n, q;
    scanf("%d%d", &n, &q);

    char *s1 = new char[n + 1];
    char *s2 = new char[n + 1];
    scanf("%s%s", s1, s2);

    u32 *anss = new u32[q];
    int *q_x = new int[q];
    int *q_y = new int[q];
    int *q_len = new int[q];

    for (int i = 0; i < q; i++) {
        scanf("%d%d%d", q_x + i, q_y + i, q_len + i);
    }

    solve(n, q, s1, s2, q_x, q_y, q_len, anss);

    output_arr(anss, q * sizeof(u32));
    delete[] s1;
    delete[] s2;
    delete[] q_x;
    delete[] q_y;
    delete[] q_len;
    delete[] anss;
}
}

namespace Parentheses {

auto solve(const int n,const char*s){
    auto f=new uint[n*2+7]+n+3;
    const auto fs=f-n-3;
    memset(fs,0,sizeof(uint)*(n*2+7));
    f[0]=1;
    cir(i,0,n){
        if(s[i]=='('){
            --f;
        }else if(s[i]==')'){
            ++f;
        }else{
            auto lastop=0u;
            auto w=0;
            for(;w+8<min(i+1,n-i)+1;w+=8) if(i&1){
                const auto cur1=f[w+1];
                const auto cur3=f[w+3];
                const auto cur5=f[w+5];
                const auto cur7=f[w+7];
                f[w]=lastop+cur1;
                f[w+2]=cur1+cur3;
                f[w+4]=cur3+cur5;
                f[w+6]=cur5+cur7;
                lastop=cur7;
            }else{
                
                const auto cur0=f[w];
                const auto cur2=f[w+2];
                const auto cur4=f[w+4];
                const auto cur6=f[w+6];
                const auto cur8=f[w+8];
                f[w+1]=cur0+cur2;
                f[w+3]=cur2+cur4;
                f[w+5]=cur4+cur6;
                f[w+7]=cur6+cur8;
            }
            for(;w<min(i+1,n-i)+1;++w){
                const auto cur=f[w];
                f[w]=lastop+f[w+1];
                lastop=cur;
            }
        }
        f[-1]=0;
    }
    const auto res=f[0];
    delete[] fs;
    return res;
}

void main() {
    int n;
    scanf("%d", &n);

    char *s = new char[n + 1];
    scanf("%s", s);

    u32 ans;
    ans = solve(n, s);

    printf("%u\n", ans);

    delete[] s;
}
}

int main() {
    int task_id;
    scanf("%d", &task_id);

    switch (task_id) {
        case 1:
            Sorting::main();
            break;
        case 2:
            Game::main();
            break;
        case 3:
            Parentheses::main();
            break;
    }

    return 0;
}

