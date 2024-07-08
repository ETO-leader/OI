#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
const lint _inf=1e15+7;
struct sci{lint t,w;};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--) [&]{
        int p,k;cin>>p>>k;
        if(!k)
            return cout<<"0\n",void();
        if(p==1)
            return cout<<"1\n",void();
        int l=1,r=k,ans=-1;
        while(r>=l){
            const int mid=(l+r)/2;
            [&](){
                int cnx=mid,w=cnx;
                while(w>p-1){
                    cnx+=(w/p);
                    if(cnx>k-1) return true;
                    w=((w%p)+(w/p));
                }
                return cnx>k-1;
            }()?((r=mid-1),(ans=mid)):(l=mid+1);
        }
        cout<<ans<<'\n';
    }();
    return 0;
}
