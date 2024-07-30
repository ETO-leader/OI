#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,q;cin>>n>>q;vector<int> a(n);
    for(auto&i:a) cin>>i;
    cir(c,0,q) [&](){
        int l,r;cin>>l>>r;--l;--r;
        if(r-l+1>80) return cout<<"YES"<<'\n',void();
        vector ax(a.begin()+l,a.begin()+r+1);
        ranges::sort(ax);
        cir(i,0,(int)(ax.size())-2){
            if(ax[i]+ax[i+1]<ax[i+2]+1) continue;
            cir(j,i+3,(int)(ax.size())-2){
                if(ax[j]+ax[j+1]<ax[j+2]+1) continue;
                return cout<<"YES"<<'\n',void();
            }
        }
        cir(p,0,(int)(ax.size())-5){
            vector qx(ax.begin()+p,ax.begin()+p+6);
            cir(i,0,6) cir(j,i+1,6) cir(k,j+1,6){
                if(qx[i]+qx[j]<qx[k]+1) continue;
                set px({0,1,2,3,4,5});
                for(auto x:{i,j,k}) px.extract(x);
                const auto xi=*px.begin(),xj=*next(px.begin()),xk=*next(px.begin(),2);
                if(qx[xi]+qx[xj]<qx[xk]+1) continue;
                return cout<<"YES"<<'\n',void();
            }
        }
        cout<<"NO"<<'\n';
    }();
    return 0;
}
