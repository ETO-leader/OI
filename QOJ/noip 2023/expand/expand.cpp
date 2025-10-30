#include<bits/stdc++.h>
#define cir(i,a,b) for(auto i=a;i<b;++i)
using namespace std;
static constexpr auto ups=21;
auto calc(vector<int> a,vector<int> b,auto&upl,auto&upr){
    if(a[0]<b[0]+1&&a.back()+1>b.back()) return false;
    if(a[0]>b[0]) return calc(b,a,upl,upr);
    auto las=0;
    const auto n=(int)(b.size());
    stack<int> pos;
    pos.emplace(-1);
    cir(i,0,n){
        while((~pos.top())&&b[pos.top()]<b[i]) pos.pop();
        upl[0][i]=pos.top();
        pos.emplace(i);
    }
    while(!pos.empty()) pos.pop();
    pos.emplace(n);
    for(auto i=n-1;~i;--i){
        while((pos.top()<n)&&b[pos.top()]>b[i]) pos.pop();
        upr[0][i]=pos.top();
        pos.emplace(i);
    }
    cir(c,1,ups) cir(i,0,n){
        upl[c][i]=(~upl[c-1][i])?upl[c-1][upl[c-1][i]]:-1;
        upr[c][i]=(upr[c-1][i]<n)?upr[c-1][upr[c-1][i]]:n;
    }
    for(auto&x:a){
        if(b[las]<x+1){
            for(auto p=ups-1;~p;--p) if(upl[p][las]>-1&&b[upl[p][las]]<x+1) las=upl[p][las];
            las=upl[0][las];
        }
        if(!(~las)) return false;
        if(b[las]>x){
            for(auto p=ups-1;~p;--p) if(upr[p][las]<n&&b[upr[p][las]]>x) las=upr[p][las];
            las=upr[0][las]-1;
        }
    }
    return las==(int)(b.size())-1;
}
auto calc(vector<int> a,vector<int> b){
    if(a[0]<b[0]+1&&a.back()+1>b.back()) return false;
    if(a[0]>b[0]) return calc(b,a);
    auto las=0;
    for(auto&x:a){
        while((~las)&&b[las]<x+1) --las;
        if(!(~las)) return false;
        while(las+1<(int)(b.size())&&b[las+1]>x) ++las;
    }
    return las==(int)(b.size())-1;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int c,n,m,q;cin>>c>>n>>m>>q;
    vector<int> a(n),b(m);
    for(auto&x:a) cin>>x;
    for(auto&x:b) cin>>x;
    if(c>14){
        vector<vector<int>> upl(ups,vector<int>(max(n,m))),upr(ups,vector<int>(max(n,m)));
        cout<<calc(a,b,upl,upr);
        cir(i,0,q){
            auto ax=a,bx=b;
            int kx,ky;cin>>kx>>ky;
            cir(i,0,kx){
                int p,w;cin>>p>>w;--p;
                ax[p]=w;
            }
            cir(i,0,ky){
                int p,w;cin>>p>>w;--p;
                bx[p]=w;
            }
            cout<<calc(ax,bx,upl,upr);
        }
        cout<<'\n';
    }else{
        cout<<calc(a,b);
        cir(i,0,q){
            auto ax=a,bx=b;
            int kx,ky;cin>>kx>>ky;
            cir(i,0,kx){
                int p,w;cin>>p>>w;--p;
                ax[p]=w;
            }
            cir(i,0,ky){
                int p,w;cin>>p>>w;--p;
                bx[p]=w;
            }
            cout<<calc(ax,bx);
        }
        cout<<'\n';
    }
    return 0;
}
