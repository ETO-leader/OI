#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;
    vector<int> v(n),ans;iota(v.begin(),v.end(),1);
    int ansx=0;
    auto calc=[&](int l,int r){
        set<int> sx;
        cir(i,1,n+2) sx.insert(i);
        cir(i,l,r+1) if(sx.count(v[i]))
            sx.erase(v[i]);
        int p=*sx.begin();
        if(p<2) return false;
        cir(i,2,p) if(!(p%i)) return false;
        return true;
    };
    do{
        int ansi=0;
        cir(i,0,n) cir(j,i,n) ansi+=calc(i,j);
        if(ansi>ansx) ansx=ansi,ans=v;
        if(ansi==19){
            for(auto&i:v) cout<<i<<' ';
            cout<<'\n';
        }
    }while(next_permutation(v.begin(),v.end()));
    cout<<ansx<<":\n";
    for(auto&i:ans) cout<<i<<' ';
    cout<<'\n';
    return 0;
}