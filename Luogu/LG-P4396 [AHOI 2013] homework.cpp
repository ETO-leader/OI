#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using VI=vector<int>;
const int maxa=1e5+7;
class blocks{
private:
    int blcsiz;
    struct node{int l,r,sum;};
    vector<node> blc;VI b,arr;
    void initblocks(int n){
        blcsiz=sqrt(n)+7;
        for(int l=0;l<n;l+=blcsiz){
            blc.push_back({l,min(l+blcsiz-1,n),0});
            cir(i,l,l+blcsiz) b[i]=blc.size()-1;
        }
    }
    int bfcalc(int l,int r){
        return accumulate(
            arr.begin()+l,arr.begin()+r+1,0);
    }
public:
    void update(int p,int w){
        arr[p]+=w;blc[b[p]].sum+=w;
    }
    int operator()(int l,int r){
        if(b[l]==b[r]) return bfcalc(l,r);
        int res=bfcalc(l,blc[b[l]].r)+
            bfcalc(blc[b[r]].l,r);
        cir(i,b[l]+1,b[r]) res+=blc[i].sum;
        return res;
    }
    size_t size(){return arr.size();}
    blocks(int n):b(n),arr(n){initblocks(n);}
};
struct query{int l,r,a,b,id;};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,q;cin>>n>>q;
    const int sqr=sqrt(n*2)+1;
    VI v(n);vector<query> qry(q);
    for(auto&i:v) cin>>i;
    [&](){
        int cnx=0;
        for(auto&[l,r,a,b,id]:qry){
            cin>>l>>r>>a>>b;--l,--r;
            id=cnx;++cnx;
        }
    }();
    sort(qry.begin(),qry.end(),[&](query&a,query&b){
        return a.l/sqr==b.l/sqr?a.r<b.r:a.l<b.l;
    });
    blocks sum(maxa),cx(maxa);
    unordered_map<int,int> cnx;
    int lx=0,rx=-1;
    auto updatei=[&](int p,int adx){
        sum.update(v[p],adx);
        cnx[v[p]]+=adx;
        if(cnx[v[p]]==1&&adx==1) cx.update(v[p],1);
        if((!cnx[v[p]])&&adx==-1) cx.update(v[p],-1);
    };
    vector<pair<int,int>> ans(q);
    for(auto&[l,r,a,b,id]:qry){
        //cout<<l<<' '<<r<<'\n';
        while(rx<r) updatei(++rx,1);
        while(lx<l) updatei(lx++,-1);
        while(rx>r) updatei(rx--,-1);
        while(lx>l) updatei(--lx,1);
        ans[id]={sum(a,b),cx(a,b)};
    }
    for(auto&[a,b]:ans) cout<<a<<' '<<b<<'\n';
    return 0;
}
