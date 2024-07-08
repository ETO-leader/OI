#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
class trie{
private:
    vector<array<int,2>> ch;
    vector<int> siz;
    int cnt;
    static constexpr auto bit=32;
    auto allocm(){return ++cnt;}
public:
    auto insert(uint x){
        for(auto i=bit-1,u=0;~i;--i){
            const auto bi=(x>>i)&1;
            if(!ch[u][bi]) ch[u][bi]=allocm();
            ++siz[u=ch[u][bi]];
        }
    }
    auto query(uint x,int k){
        auto res=0u;++k;
        for(auto i=bit-1,u=0;~i;--i){
            const auto bi=(x>>i)&1;
            auto gx=!bi;
            if(siz[ch[u][gx]]<k){
                assert(k-siz[ch[u][gx]]>0);
                k-=siz[ch[u][gx]];gx^=true;
            }
            res|=((bi^gx)<<i);
            u=ch[u][gx];
        }
        return res;
    }
    trie(int c):ch((c<<5)+7),siz((c<<5)+7),cnt(0){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,k;cin>>n>>k;k*=2;
    vector<uint> a(n);
    trie tr(n+1);
    for(auto las=0;auto&i:a) cin>>i,tr.insert(i=(las^=i));
    tr.insert(0);
    a.insert(a.begin(),0);
    auto ans=0ul;
    priority_queue<tuple<uint,int,int>> pq;
    cir(i,0,n+1) pq.push({tr.query(a[i],0),i,0});
    cir(i,0,k){
        auto[aw,p,ci]=pq.top();pq.pop();
        ans+=aw;pq.push({tr.query(a[p],ci+1),p,ci+1});
    }
    cout<<ans/2<<'\n';
    return 0;
}
