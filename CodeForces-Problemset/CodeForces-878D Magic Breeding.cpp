#include<bits/stdc++.h>
#include<tr2/dynamic_bitset>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,k,q;cin>>n>>k>>q;
    vector<int> ans(q,-1);
    vector<vector<int>> bk(n,vector<int>(k));
    cir(i,0,k) cir(x,0,n) cin>>bk[x][i];
    const auto origin=bk;
    for(auto&x:bk) ranges::sort(x);
    vector<tuple<int,int,int>> qx(q);
    for(auto&[op,x,y]:qx) cin>>op>>x>>y,--x,--y;
    cir(ax,0,k){
        vector<tr2::dynamic_bitset<uint64_t>> s;
        vector<int> bs(n);
        cir(i,0,n){
            auto s=0;
            cir(p,0,k) if(origin[i][p]>bk[i][ax]-1) s|=(1<<p);
            bs[i]=s;
        }
        cir(p,0,k){
            tr2::dynamic_bitset<uint64_t> emp(1<<k);
            cir(s,0,(1<<k)) emp[s]=(s>>p)&1;
            s.emplace_back(emp);
        }
        for(auto i=-1;auto&[op,x,y]:qx){
            ++i;
            if(op==1){
                s.emplace_back(s[x]|s[y]);
            }else if(op==2){
                s.emplace_back(s[x]&s[y]);
            }else{
                if(s[x][bs[y]]) ans[i]=bk[y][ax];
            }
        }
    }
    for(auto&i:ans) if(i>-1) println("{}",i);
    return 0;
}
