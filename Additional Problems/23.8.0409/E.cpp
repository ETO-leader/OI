#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
template<typename T>
class bit{
private:
    vector<T> v;int n;
    int lowbit(int x) const{return x&(-x);}
public:
    void update(int p,T w){
        ++p;
        while(p<n) v[p]+=w,p+=lowbit(p);
    }
    T operator()(int p) const{
        T res=0;++p;
        while(p) res+=v[p],p-=lowbit(p);
        return res;
    }
    void resize(int _n){(*this)=bit(_n);}
    bit(int _n=0):n(_n),v(_n){}
};
class blocks{
private:
    struct node{
        int l,r;bit<int> cnx;
        node(int _l,int _r):l(_l),r(_r){}
    };
    vector<int> pav,arb,blc;
    vector<node> brc;
    void init(){
        const int n=arb.size();
        const int sqr=sqrt(n*log2(n));
        for(int i=0,c=0;i<n;i+=sqr,++c){
            brc.push_back(node(i,min(i+sqr-1,n-1)));
            brc.back().cnx.resize(n+1);
            cir(j,i,min(i+sqr,n)){
                brc.back().cnx.update(pav[arb[j]],1);
                blc.push_back(c);
            }
        }
    }
    int findblock(const int p) const{return blc[p];}
public:
    void swapvalue(int p1,int p2){
        int fb1=findblock(p1),fb2=findblock(p2);
        brc[fb1].cnx.update(pav[arb[p1]],-1);
        brc[fb2].cnx.update(pav[arb[p2]],-1);
        brc[fb1].cnx.update(pav[arb[p2]],1);
        brc[fb2].cnx.update(pav[arb[p1]],1);
        swap(arb[p1],arb[p2]);
    }
    int operator()(int l,int r,int ql,int qr) const{
        int fbl=findblock(l),fbr=findblock(r);
        int res=0;
        cir(i,l,min(brc[fbl].r+1,r+1))
            res+=(pav[arb[i]]>=ql&&pav[arb[i]]<=qr);
        if(fbl==fbr) return res;
        cir(i,fbl+1,fbr){
            res+=(brc[i].cnx(qr)-brc[i].cnx(ql-1));
        }
        cir(i,brc[fbr].l,r+1)
            res+=(pav[arb[i]]>=ql&&pav[arb[i]]<=qr);
        return res;
    }
    blocks(vector<int>&_a,vector<int>&_b):
        pav(_a),arb(_b){init();}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;cin>>n>>m;
    vector<int> pav(n+1),arb(n);
    cir(i,0,n){
        int w;cin>>w;pav[w]=i;
    }
    for(auto&i:arb) cin>>i;
    blocks blc(pav,arb);
    cir(i,0,m){
        int op;cin>>op;
        if(op==1){
            int l,r,ql,qr;cin>>ql>>qr>>l>>r;
            --ql,--qr,--l,--r;
            cout<<blc(l,r,ql,qr)<<'\n';
        }else{
            int x,y;cin>>x>>y;--x,--y;
            blc.swapvalue(x,y);
        }
    }
    return 0;
}
