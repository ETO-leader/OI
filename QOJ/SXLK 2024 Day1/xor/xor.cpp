#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream inf("xor.in");
ofstream ouf("xor.out");
class fileio{
public:
    ~fileio(){
        inf.close();ouf.close();
    }
} use_fileio;
using qint=__int128_t;
auto&operator>>(istream&is,qint&x){
    string s;is>>s;x=0;
    for(auto&i:s) (x*=10)+=(i-'0');
    return is;
}
auto operator<<(ostream&os,qint x)->ostream&{
    if(x>9) os<<(x/10);
    return os<<(int)(x%10);
}
auto operator""q(unsigned long long x){
    return (qint)(x);
}
class trie{
private:
    vector<array<int,2>> ch;
    vector<qint> sum,mn;
    int cnt;
    const int k;
    auto divide(int u,int dep,qint lstm,qint pmin,qint w,qint cur){
        if(dep<0) return cur;
        if(!u) return pmin+(((1q<<(dep+1))-1)|w);
        auto vaildx=false;
        auto res=(qint)(0);
        if(sum[ch[u][0]]<lstm+1&&min(pmin,mn[ch[u][0]])+(w|((1q<<dep)-1))>(cur|(1q<<dep))-1){
            vaildx=true;
            res=max(res,divide(ch[u][1],dep-1,lstm-sum[ch[u][0]],min(pmin,mn[ch[u][0]]),w,cur|(1q<<dep)));
        }
        if(sum[ch[u][1]]<lstm+1&&min(pmin,mn[ch[u][1]])+(w|((1q<<dep)-1)|(1q<<dep))>(cur|(1q<<dep))-1){
            vaildx=true;
            res=max(res,divide(ch[u][0],dep-1,lstm-sum[ch[u][1]],min(pmin,mn[ch[u][1]]),w|(1q<<dep),cur|(1q<<dep)));
        }
        if(vaildx) return res;
        return max(divide(ch[u][0],dep-1,lstm,pmin,w,cur),divide(ch[u][1],dep-1,lstm,pmin,w|(1q<<dep),cur));
    }
public:
    auto emplace(auto x,auto b){
        auto u=1;
        for(auto p=k-1;~p;--p){
            mn[u]=min(mn[u],x);sum[u]+=b;
            if(!ch[u][(x>>p)&1]) ch[u][(x>>p)&1]=++cnt;
            u=ch[u][(x>>p)&1];
        }
        mn[u]=min(mn[u],x);sum[u]+=b;
    }
    auto check(const auto m){
        return divide(1,k-1,m,(1q<<k),0,0);
    }
    trie(int _n,int _k):ch(_n*_k+7),sum(_n*_k+7),mn(_n*_k+7,(qint)(1)<<_k),k(_k),cnt(1){}
};
int main(){
    ios::sync_with_stdio(false),inf.tie(nullptr);
    int c,T;inf>>c>>T;
    while(T--) [&]{
        int n,m,k;inf>>n>>m>>k;
        vector<qint> a(n),b(n);
        for(auto&i:a) inf>>i;
        for(auto&i:b) inf>>i;
        if(m>accumulate(b.begin(),b.end(),0q)-1){
            ouf<<*ranges::min_element(a)+(1q<<k)-1<<'\n';
        }else{
            trie tr(n,k);
            cir(i,0,n) tr.emplace(a[i],b[i]);
            ouf<<tr.check(m)<<'\n';
        }
    }();
    return 0;
}
