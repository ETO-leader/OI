#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
const int mxai=5e5+7;
using VI=vector<int>;
class blocks{
private:
    int blcsiz;
    struct node{int l,r,sum;};
    vector<node> blc;VI b,arr,vpos,cx;
    vector<VI> ax,cnx;
    void initblocks(int n){
        blcsiz=sqrt(n)+7;
        for(int l=0;l<n;l+=blcsiz){
            blc.push_back({l,min(l+blcsiz-1,n-1),0});
            cir(i,l,min(l+blcsiz,n)) b[i]=blc.size()-1;
        }
    }
    void initcnx(int n,int block){
        VI cnxi(mxai);int mx=0;
        const int sblock=block;
        cir(i,blc[block].l,n){
            mx=max(mx,++cnxi[arr[i]]);
            if(i==blc[block].r){
                cnx[sblock][block]=mx;++block;
            }
        }
    }
    void init(int n){
        initblocks(n);
        cnx.assign(blc.size(),VI(blc.size()));
        cir(i,0,n){
            vpos[i]=ax[arr[i]].size();
            ax[arr[i]].push_back(i);
        }
        cir(i,0,(int)(blc.size())) initcnx(n,i);
    }
    int ckmax(int l,int r){
        int mx=0;
        cir(i,l,r+1) mx=max(mx,(++cx[arr[i]]));
        cir(i,l,r+1) cx[arr[i]]=0;
        return mx;
    }
public:
    int operator()(int l,int r){
        if(b[l]==b[r]) return ckmax(l,r);
        int ans=cnx[b[l]+1][b[r]-1];
        for(int i=blc[b[l]].r;i>l-1;--i){
            auto&axi=ax[arr[i]];
            ans+=(axi.size()>vpos[i]+ans
                &&axi[vpos[i]+ans]<r+1);
        }
        cir(i,blc[b[r]].l,r+1){
            auto&axi=ax[arr[i]];
            ans+=(vpos[i]>ans-1
                &&axi[vpos[i]-ans]>l-1);
        }
        return ans;
    }
    blocks(VI&v):b(v.size()),arr(v),
        ax(mxai),cx(mxai),vpos(v.size()){
        init(v.size());}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,q;cin>>n>>q;
    vector<int> v(n);
    for(auto&i:v) cin>>i;
    blocks blc(v);int lans=0;
    cir(i,0,q){
        int l,r;cin>>l>>r;
        l^=lans;r^=lans;--l,--r;
        cout<<(lans=blc(l,r))<<'\n';
    }
    return 0;
}
