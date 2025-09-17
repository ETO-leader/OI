#include<bits/stdc++.h>
using namespace std;
const int maxn=100005;
int N,M,L[maxn],R[maxn];
char A[maxn],B[maxn];
typedef unsigned long long ull;
struct BIT{
    vector<ull> s;
    void reset(){vector<ull>().swap(s);}
    void init(int len){s.resize((len+63)>>6);}
    void set(int x){s[x>>6]|=1ull<<(x&63);}
    void operator |=(const BIT &B){
        int p=min(s.size(),B.s.size());
        for(int i=0;i<p;i++) s[i]|=B.s[i];
    }
    BIT operator &(const BIT &B){
        BIT C;C.s.clear();
        int p=min(s.size(),B.s.size());C.s.resize(p);
        for(int i=0;i<p;i++) C.s[i]=s[i]&B.s[i];
        return C;
    }
    BIT operator >>(int x){
        if(!x) return *this;
        int tt=x>>6;x&=63;
        BIT b,c;c.s.resize(s.size());b.s.resize(s.size());
        for(int i=0;i+tt<b.s.size();i++) b.s[i]=s[i+tt];
        ull p=(1ull<<x)-1;
        for(int i=0;i+1<s.size();i++) c.s[i]=(b.s[i]>>x)|((b.s[i+1]&p)<<64-x);
        c.s[s.size()-1]=b.s[s.size()-1]>>x;
        return c;
    }
    BIT operator <<(int x){
        if(!x) return *this;
        BIT c;c.s.resize(s.size());
        for(int i=0;i<s.size();i++) c.s[i]|=s[i]<<x,c.s[i+1]|=s[i]>>(64-x);
        return c;
    }
    bool check(int x){
        return s[x>>6]>>(x&63)&1;
    }
}F[maxn],G[30],H;
void solve(){
    scanf("%s%s",A+1,B+1);
    N=strlen(A+1),M=strlen(B+1);
    if(N>M) return puts("NO"),void();
    for(int i=0;i<=M;i++) L[i]=max(0,i-(M-N)),R[i]=min(i,N);
    for(int i=0;i<=M;i++) F[i].reset(),F[i].init(R[i]-L[i]+1);
    for(int i=0;i<26;i++) G[i].reset(),G[i].init(N+1);
    for(int i=1;i<=N;i++) G[A[i]-'a'].set(i);
    F[0].set(0);
    for(int i=0;i<M;i++){
        if(i+2<=M&&B[i+1]==B[i+2]) F[i+2]|=F[i]>>(L[i+2]-L[i]);
        int w=L[i+1]-L[i]-1;
        if(w>=0) F[i+1]|=(F[i]>>w)&(G[B[i+1]-'a']>>L[i+1]);
        if(w<0) F[i+1]|=(F[i]<<-w)&(G[B[i+1]-'a']>>L[i+1]);
        F[i].reset();
    }
    if(F[M].check(N-L[M])) puts("YES");else puts("NO");
}
int main(){
    freopen("string.in","r",stdin);
    freopen("string.out","w",stdout);
    int T,id;scanf("%d%d",&T,&id);
    while(T--) solve();
    return 0;
}