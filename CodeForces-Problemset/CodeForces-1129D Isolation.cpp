#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,abm,mmx")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4")
#pragma GCC target("tune=native")
#include<bits/stdc++.h>
#include<ext/pb_ds/hash_policy.hpp>
#include<ext/pb_ds/assoc_container.hpp>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr int MOD=998244353;
template<class Key,class T>
class blocks{
private:
    enum movetags{leftm,rightm};
    struct node{
        vector<T> bw;T w;
        vector<int> aps;
        Key tag;
        int l,r;
        void move(movetags tagx,Key k){
            if(tagx){
                ++tag;
                if(k+tag>-1) w+=bw[k+tag];
            }else{
                if(k+tag>-1) w-=bw[k+tag];
                --tag;
            }
        }
        void clear(){
            for(auto&i:aps) bw[i]=0;
            w=0;aps.clear();tag=0;
        }
        node(int lx,int rx,int siz):bw(siz+1),
            w(0),tag(0),l(lx),r(rx){}
    };
    struct node_t{Key k;T w;};
    vector<node> blc;
    vector<int> blcid;
    vector<node_t> state;
    int sqr;
    void init(int n){
        sqr=sqrt(n*4)+1;
        for(int i=0;i<n;i+=sqr){
            blc.push_back(
                node(i,min(n-1,i+sqr-1),n*2+7));
            cir(x,i,min(n,i+sqr)){
                blcid[x]=blc.size()-1;
            }
        }
    }
    void exprt(int l,int r){
        cir(i,l,r+1){
            state[i].k-=blc[blcid[i]].tag;
        }
    }
    node&rebuild(int l,int r){
        node&res=blc[blcid[l]];
        res.clear();
        cir(i,l,r+1){
            res.bw[state[i].k]+=state[i].w;
            res.aps.push_back(state[i].k);
            res.w+=state[i].w*(state[i].k<k+1);
        }
        return res;
    }
    auto bf_calc(int l,int r){
        T res=0;
        const int b=blcid[l];
        exprt(blc[b].l,blc[b].r);
        cir(i,l,r+1){
            (res+=(state[i].k<k+1)*
                (state[i].w))%=MOD;
        }
        blc[b]=rebuild(blc[b].l,blc[b].r);
        return res;
    }
    auto calc(int l,int r){
        const auto gl=blcid[l],gr=blcid[r];
        if(gl==gr) return bf_calc(l,r);
        T res=0;
        cir(i,gl+1,gr) res+=blc[i].w;
        return (bf_calc(l,blc[gl].r)+
            bf_calc(blc[gr].l,r)+res)%MOD;
    }
    void bfupd(int l,int r,T w){
        const int b=blcid[l];
        exprt(blc[b].l,blc[b].r);
        cir(i,l,r+1) state[i].k+=w;
        blc[b]=rebuild(blc[b].l,blc[b].r);
    }
    void update(int l,int r,T w){
        const auto gl=blcid[l],gr=blcid[r];
        if(gl==gr) return bfupd(l,r,w);
        bfupd(l,blc[gl].r,w);
        bfupd(blc[gr].l,r,w);
        cir(i,gl+1,gr){
            blc[i].move(((w>0)?
                leftm:rightm),k);
        }
    }
    void updpos(int p,Key x,T w){
        const auto b=blcid[p];
        exprt(blc[b].l,blc[b].r);
        state[p]={x,w};
        blc[b]=rebuild(blc[b].l,blc[b].r);
    }
    Key k;
public:
    void set(int p,Key x,T w){
        updpos(p,x,w);
    }
    void chgkrng(int l,int r,Key w){
        update(l,r,w);
    }
    T get(int r){return calc(0,r-1);}
    blocks(int n,Key kx):blcid(n),
        state(n),k(kx){init(n);}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,k;cin>>n>>k;
    blocks<int,lint> blc(n+1,k);
    vector<int> a(n);
    for(auto&i:a) cin>>i;
    vector<lint> D(n+1);
    blc.set(0,0,1);
    __gnu_pbds::gp_hash_table<int,int> lst,llst;
    cir(i,1,n+1){
        if(lst[a[i-1]]){
            blc.chgkrng(llst[a[i-1]],
                lst[a[i-1]]-1,-1);
        }
        blc.chgkrng(lst[a[i-1]],i-1,1);
        D[i]=blc.get(i);
        blc.set(i,0,D[i]);
        swap(lst[a[i-1]],llst[a[i-1]]);
        lst[a[i-1]]=i;
    }
    cout<<D[n]<<'\n';
    return 0;
}