#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--) [&](){
        int n,d;cin>>n>>d;
        vector<pair<int,int>> a(n);
        for(auto&[x,y]:a){
            cin>>x>>y;
            const auto lx=x,ly=y;
            x=lx+ly;y=lx-ly;
        }
        auto ans=tuple(0,0,0);
        [&](){
            cir(i,0,2){
                for(auto&[x,y]:a) swap(x,y);
                for(auto ax:{-1,1}) for(auto ay:{-1,1}){
                    auto qx=a;
                    for(auto&[x,y]:qx) x*=ax,y*=ay;
                    unordered_map<int,map<int,int>> mp;
                    for(auto c=0;auto&[x,y]:qx) mp[x][y]=++c;
                    for(auto idx=0;auto&[x,y]:qx){
                        ++idx;
                        if(!mp[x].count(y+d)) continue;
                        for(auto deltad:{-d,d}){
                            if(!mp.count(x+deltad)) continue;
                            const auto lb=mp[x+deltad].lower_bound(y);
                            if(lb==mp[x+deltad].end()) continue;
                            const auto&[p,id]=*lb;
                            if(p>y+d) continue;
                            return ans={idx,mp[x][y+d],id},void();
                        }
                    }
                }
            }
        }();
        const auto&[ax,bx,cx]=ans;
        cout<<format("{} {} {}",ax,bx,cx)<<'\n';
    }();
    return 0;
}
