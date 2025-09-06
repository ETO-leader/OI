#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream inf("power.in");
ofstream ouf("power.out");
class dsu{
private:
    vector<int> f;
public:
    auto findset(int u)->int{
        return f[u]==u?u:f[u]=findset(f[u]);
    }
    auto merge(int u,int v){
        f[findset(u)]=findset(v);
    }
    dsu(int _n):f(_n){iota(f.begin(),f.end(),0);}
};
int main(){
    ios::sync_with_stdio(false),inf.tie(nullptr);
    int n,k;inf>>n>>k;
    string ty;inf>>ty;
    vector<int> sn(n);
    for(auto&x:sn) inf>>x;
    vector<int> indsn(n+1);
    cir(i,0,n) indsn[sn[i]]=i;
    dsu qwq(n);
    vector<int> uf(n,n+7);
    cir(i,1,n+1) cir(j,0,k+1) if((i^j)<n+1&&(i^j)>0&&ty[indsn[i]]=='S'&&ty[indsn[i^j]]=='S'){
        qwq.merge(indsn[i],indsn[i^j]);
    }
    cir(i,1,n+1) if(ty[indsn[i]]=='S'){
        for(auto j=i;j<n+1;j+=i) if(ty[indsn[j]]=='M') uf[indsn[i]]=min(uf[indsn[i]],j);
    }
    vector<int> ansst(n,n+7);
    cir(i,0,n) if(ty[i]=='S'&&ansst[qwq.findset(i)]>n){
        if(uf[i]<n) ansst[qwq.findset(i)]=indsn[uf[i]];
    }
    cir(i,0,n){
        if(ty[i]=='M'){
            ouf<<"Master Station"<<'\n';
        }else if(ansst[qwq.findset(i)]>n-1){
            ouf<<"Not connected to any Master Station"<<'\n';
        }else{
            ouf<<"Connected to "<<ansst[qwq.findset(i)]+1<<'\n';
        }
    }
    return 0;
}
