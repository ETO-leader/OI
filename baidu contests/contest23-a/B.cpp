#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,abm,mmx,avx,avx2")
#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using VI=vector<int>;
const int _inf=1e9+7;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,k;cin>>n>>k;
    vector<VI> ck(n,VI(n)),sum(n,VI(n));
    for(auto&i:ck) for(auto&j:i) cin>>j;
    int mx=0;
    cir(i,0,n){
        int sumi=0;
        cir(j,0,n){
            sumi+=ck[i][j];
            sum[i][j]=(i?sum[i-1][j]:0)+sumi;
            mx=max(mx,ck[i][j]);
        }
    }
    vector<VI> sizx(n);
    cir(i,0,(1<<(n-1))){
        sizx[__builtin_popcount(i)
            ].push_back(i+(1<<(n-1)));
    }
    int l=mx,r=sum[n-1][n-1],ans=_inf;
    while(r>=l){
        const int mid=(l+r)/2;
        [&](){
            cir(st,0,min(n,k+1)){
                for(auto&s:sizx[st]) if([&]{
                    vector<int> bid(n);
                    int lp=0,cnx=0;
                    cir(p,0,n) if(s&(1<<p)){
                        cir(x,lp,p+1) bid[x]=cnx;
                        ++cnx;lp=p+1;
                    }
                    //Check
                    cir(i,0,n){
                        vector<int> c(cnx);
                        cir(j,0,n)
                            c[bid[j]]+=ck[i][j];
                        if(*max_element(c.begin(),c.end())>mid)
                            return false;
                    }
                    //Run
                    int use=0;
                    vector<int> c(cnx);
                    cir(i,0,n){
                        cir(j,0,n){
                            c[bid[j]]+=ck[i][j];
                        }
                        if(*max_element(c.begin(),c.end())>mid){
                            ++use;
                            fill(c.begin(),c.end(),0);
                            cir(j,0,n) c[bid[j]]+=ck[i][j];
                        }
                    }
                    return use+st<k+1;
                }()) return true;
            }
            return false;
        }()?((r=mid-1),(ans=mid)):(l=mid+1);
    }
    cout<<ans<<'\n';
    return 0;
}
