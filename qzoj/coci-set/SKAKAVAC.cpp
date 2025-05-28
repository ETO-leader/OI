#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
static constexpr auto maxv=(int)(1e6+7);
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,r,c;cin>>n>>r>>c;--r;--c;
    vector<vector<pair<int,int>>> ord(maxv);
    cir(i,0,n) cir(j,0,n){
        int w;cin>>w;ord[w].emplace_back(i,j);
    }
    vector f(n,vector<int>(n,-maxv));
    vector<multiset<pair<int,int>>> ln(n),col(n);
    for(auto&x:ln) cir(i,0,4) x.emplace(0,-7);
    for(auto&x:col) cir(i,0,4) x.emplace(0,-7);
    for(auto w=maxv-1;~w;--w){
        for(auto&[x,y]:ord[w]){
            // Type 1: x - 1
            if(x){
                for(auto&[w,p]:ln[x-1]) if(abs(y-p)>1){
                    f[x][y]=max(f[x][y],w+1);
                }
            }
            // Type 2: x + 1
            if(x+1<n){
                for(auto&[w,p]:ln[x+1]) if(abs(y-p)>1){
                    f[x][y]=max(f[x][y],w+1);
                }
            }
            // Type 3: y - 1
            if(y){
                for(auto&[w,p]:col[y-1]) if(abs(x-p)>1){
                    f[x][y]=max(f[x][y],w+1);
                }
            }
            // Type 4: y + 1
            if(y+1<n){
                for(auto&[w,p]:col[y+1]) if(abs(x-p)>1){
                    f[x][y]=max(f[x][y],w+1);
                }
            }
        }
        for(auto&[x,y]:ord[w]){
            // Update x
            ln[x].emplace(f[x][y],y);
            ln[x].erase(ln[x].begin());
            // Update y
            col[y].emplace(f[x][y],x);
            col[y].erase(col[y].begin());
        }
    }
    cout<<f[r][c]<<'\n';
    return 0;
}
