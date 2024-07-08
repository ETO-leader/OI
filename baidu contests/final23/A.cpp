#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using VI=vector<char>;
static VI mx={1,-1,0,0},my={0,0,1,-1};
struct qnode{int x,y,dir,trn;};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;cin>>n>>m;vector<string> a(n);
    for(auto&i:a) cin>>i;
    auto ans=false;
    auto calc=[&](){
        int sx=-1,sy=-1;
        cir(i,0,n) cir(j,0,m) if(a[i][j]=='S')
        sx=i,sy=j;
        vector<pair<int,int>> rg;
        cir(j,0,m){
            int x=sx;
            while(x&&a[x-1][j]!='#') --x;
            int nx=sx;
            while(nx+1<n&&a[nx+1][j]!='#') ++nx;
            rg.push_back({x,nx});
        }
        cir(i,0,n) if(i!=sx){
            int lx=sy,rx=sy;
            while((~lx)&&(rg[lx].first>i||rg[lx].second<i))
                --lx;
            while((rx<m)&&(rg[rx].first>i||rg[rx].second<i))
                ++rx;
            if(lx!=rx) [&](){
                if(lx<0||rx>m-1) return;
                bool tgs=true;
                cir(j,lx,rx) if(a[i][j]=='#'||a[sx][j]=='#'){
                    tgs=false;
                }
                if(tgs){
                    ans=true;return;
                }
            }();else{
                auto cl=lx,cr=rx;
                ++rx;
                while((~lx)&&(rg[lx].first>i||rg[lx].second<i))
                    --lx;
                while((rx<m)&&(rg[rx].first>i||rg[rx].second<i))
                    ++rx;
                [&](){
                    if(lx<0||rx>m-1) return;
                    bool tgs=true;
                    cir(j,lx,rx+1) if(a[i][j]=='#'||a[sx][j]=='#'){
                        tgs=false;
                    }
                    if(tgs){
                        ans=true;return;
                    }
                }();
                lx=cl;rx=cr;--lx;
                while((~lx)&&(rg[lx].first>i||rg[lx].second<i))
                    --lx;
                while((rx<m)&&(rg[rx].first>i||rg[rx].second<i))
                    ++rx;
                [&](){
                    if(lx<0||rx>m-1) return;
                    bool tgs=true;
                    cir(j,lx,rx+1) if(a[i][j]=='#'||a[sx][j]=='#'){
                        tgs=false;
                    }
                    if(tgs){
                        ans=true;return;
                    }
                }();
            }
        }
    };
    calc();
    auto ca=a;
    a.clear();a.assign(m,string(n,'.'));
    cir(i,0,m) cir(j,0,n){
        a[i][j]=ca[j][i];
    }
    swap(n,m);
    calc();
    cout<<(ans?"Yes":"No")<<'\n';
    return 0;
}
