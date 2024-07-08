#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
template<typename T>
class blocks{
private:
    struct node{
        int l,r,lrise,rrise,ldrop,rdrop,w;
        int length(){return r-l+1;}
    };
    vector<T> arr;
    vector<node> blc;
    int findblock(int w){
        cir(i,0,blc.size())
            if(blc[i].r>=w) return i;
        return -1;
    }
    node initblock(int l,int r){
        int lx=l,rx=r;node res;
        res.l=l;res.r=r;
        while(lx<rx&&arr[lx]<=arr[lx+1]) ++lx;
        res.lrise=lx-l+1;lx=l;
        while(lx<rx&&arr[lx]>=arr[lx+1]) ++lx;
        res.ldrop=lx-l+1;lx=l;
        while(rx>lx&&arr[rx]>=arr[rx-1]) --rx;
        res.rrise=r-rx+1;rx=r;
        while(rx>lx&&arr[rx]<=arr[rx-1]) --rx;
        res.rdrop=r-rx+1;rx=r;
        vector<array<int,2>> D(r-l+1);
        D[0][0]=D[0][1]=1;
        int mx=1;
        cir(i,l+1,r+1){
            const int lid=i-l;
            D[lid][0]=D[lid][1]=1;
            if(arr[i-1]<=arr[i])
                D[lid][0]=D[lid-1][0]+1;
            if(arr[i-1]>=arr[i])
                D[lid][1]=D[lid-1][1]+1;
            mx=max({mx,D[lid][0],D[lid][1]});
        }
        res.w=mx;
        return res;
    }
    void init(){
        const int sqr=sqrt(arr.size())+1;
        for(int i=0;i*sqr<arr.size();++i){
            blc.push_back(initblock(i*sqr,
                min<int>((i+1)*sqr-1,arr.size()-1)));
        }
    }
public:
    int operator()(int l,int r){
        int drop=0,rise=0,res=0;
        int fl=findblock(l),fr=findblock(r);
        const auto lb=initblock(l,min(blc[fl].r,r));
        const auto rb=initblock(max(blc[fr].l,l),r);
        if(fl==fr) return lb.w;
        res=lb.w;drop=lb.rdrop,rise=lb.rrise;
        cir(i,fl+1,fr){
            int risei=(arr[blc[i].l]>=arr[blc[i-1].r]?
                rise:0)+blc[i].lrise;
            int dropi=(arr[blc[i].l]<=arr[blc[i-1].r]?
                drop:0)+blc[i].ldrop;
            rise=(blc[i].lrise==blc[i].length()?
                risei:blc[i].rrise);
            drop=(blc[i].ldrop==blc[i].length()?
                dropi:blc[i].rdrop);
            res=max({res,blc[i].w,risei,dropi});
        }
        [&](){
            int risei=(arr[rb.l]>=arr[blc[fr-1].r]?
                rise:0)+rb.lrise;
            int dropi=(arr[rb.l]<=arr[blc[fr-1].r]?
                drop:0)+rb.ldrop;
            res=max({res,rb.w,risei,dropi});
        }();
        return res;
    }
    void print(){
        cout<<blc.size()<<'\n';
        for(auto&[l,r,lr,rr,ld,rd,w]:blc){
            cout<<l<<' '<<r<<' '<<lr<<' '<<rr<<' '<<ld<<' '<<rd<<' '<<w<<'\n';
        }
    }
    blocks(vector<T>&v){arr=v;init();}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;vector<int> arr(n);
    for(auto&i:arr) cin>>i;
    blocks<int> blc(arr);
    //blc.print();
    int q;cin>>q;
    cir(i,0,q){
        int l,r;cin>>l>>r;--l,--r;
        cout<<blc(l,r)<<'\n';
    }
    return 0;
}
