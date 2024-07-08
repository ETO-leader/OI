#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using db=long double;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;cin>>n>>m;vector<db> v(n);
    for(auto&i:v) cin>>i;
    auto ck=[&](db mid){
        int l=0,r=0;
        db cnt=0,ret=0;
        deque<db> qu;
        while(r<n){
            qu.push_back(v[r]);cnt+=v[r];
            while(cnt/qu.size()<mid&&r>l)
                cnt-=qu.front(),qu.pop_front(),++l;
            cout<<l<<' '<<r<<":  -> "<<cnt<<endl;
            if(cnt/qu.size()>=mid) ret=max(ret,1.0L*qu.size());
            ++r;
        }
        return ret;
    };
    db l=0,r=*max_element(v.begin(),v.end());
    cir(i,0,100){
        db mid=(l+r)/2;cout<<mid<<endl;
        ck(mid)>=m?l=mid:r=mid;
    }
    cout<<fixed<<setprecision(10)<<l<<endl;
    return 0;
}