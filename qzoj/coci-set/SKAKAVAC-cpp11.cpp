#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,qr,qc;cin>>n>>qr>>qc;--qr;--qc;
    vector<uint64_t> ord;
    ord.reserve(n*n);
    cir(i,0,n) cir(j,0,n){
        int w;cin>>w;ord.emplace_back((uint64_t)(w)<<22|((i<<11)|j));
    }
    sort(ord.begin(),ord.end(),greater<uint64_t>());
    auto ans=0;
    vector<multiset<pair<int,int>>> ln(n),col(n);
    for(auto&x:ln) cir(i,0,4) x.emplace(0,-7);
    for(auto&x:col) cir(i,0,4) x.emplace(0,-7);
    cir(l,0,n*n){
        auto r=l;
        while(r+1<n*n&&(((ord[r+1]>>22)&1048575)==((ord[l]>>22)&1048575))) ++r;
        cir(i,l,r+1){
            const auto _u=ord[i];
            auto x=(int)(_u>>11)&2047;
            auto y=(int)(_u&2047);
            auto uf=0;
            // Type 1: x - 1
            if(x){
                for(auto&[w,p]:ln[x-1]) if(abs(y-p)>1){
                    uf=max(uf,w+1);
                }
            }
            // Type 2: x + 1
            if(x+1<n){
                for(auto&[w,p]:ln[x+1]) if(abs(y-p)>1){
                    uf=max(uf,w+1);
                }
            }
            // Type 3: y - 1
            if(y){
                for(auto&[w,p]:col[y-1]) if(abs(x-p)>1){
                    uf=max(uf,w+1);
                }
            }
            // Type 4: y + 1
            if(y+1<n){
                for(auto&[w,p]:col[y+1]) if(abs(x-p)>1){
                    uf=max(uf,w+1);
                }
            }
            ord[x*n+y]|=((uint64_t)(uf)<<42);
        }
        cir(i,l,r+1){
            const auto _u=ord[i];
            auto x=(int)(_u>>11)&2047;
            auto y=(int)(_u&2047);
            auto uf=(ord[x*n+y]>>42);
            // Update x
            ln[x].emplace(uf,y);
            ln[x].erase(ln[x].begin());
            // Update y
            col[y].emplace(uf,x);
            col[y].erase(col[y].begin());
            if(x==qr&&y==qc) ans=uf;
        }
        l=r;
    }
    cout<<ans<<'\n';
    return 0;
}
