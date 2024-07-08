#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
class dsu{
private:
    vector<int> f;
public:
    int findset(int x){
        return f[x]==x?x:(f[x]=findset(f[x]));}
    void merge(int x,int y){
        f[findset(x)]=findset(y);}
    dsu(int x):f(x){iota(f.begin(),f.end(),0);}
};
void stderrf(int extcode){
    cout<<"-1\n";exit(extcode);
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;dsu ds(n+1);
    vector<int> v(n);
    for(auto&i:v) cin>>i;
    v.insert(v.begin(),114514);
    int m;cin>>m;
    cir(i,0,m){
        int x,y;cin>>x>>y;
        ds.merge(x,y);
    }
    cir(i,1,n+1) cir(j,i,n+1){
        if(v[i]>v[j]&&ds.findset(i)!=
            ds.findset(j)) stderrf(0);
    }
    return 0;
}
