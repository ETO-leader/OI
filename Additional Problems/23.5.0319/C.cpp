#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using VI=vector<int>;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m,mx,a,b;cin>>n>>m>>mx>>a>>b;
    vector<VI> v(n,VI(m));
    vector<vector<VI>> apt(n,vector<VI>(m,VI(mx)));
    unordered_map<int,int> cx;
    for(auto&i:v) for(auto&j:i) cin>>j,--j,cx[j]++;
    cir(i,0,n){
        VI nm(mx);
        cir(j,0,m){
            nm[v[i][j]]++;
            cir(k,0,mx) apt[i][j][k]=
                (i?apt[i-1][j][k]:0)+nm[k];
        }
    }
    cir(i,0,n-a+1){
        cir(j,0,m-b+1){
            int ix=i+a-1,jx=j+b-1,cnx=0;
            cir(k,0,mx) cnx+=[&](){
                return ((apt[ix][jx][k]-(i?apt[i-1][jx][k]:0)
                    -(j?apt[ix][j-1][k]:0)+(i&&j?
                        apt[i-1][j-1][k]:0))==cx[k]);
            }();
            cout<<cx.size()-cnx<<' ';
        }
        cout<<'\n';
    }
    return 0;
}
