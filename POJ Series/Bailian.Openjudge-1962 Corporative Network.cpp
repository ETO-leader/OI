#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
template<typename T>
struct valdset{
    template<typename Ty>
    struct edge{
        int f;Ty v;
        edge&operator+=(const edge&e){
            f=e.f;v+=e.v;return *this;
        }
    };
    vector<edge<T>> F;
    valdset(int _sz):F(_sz){cir(i,0,_sz) F[i]={i,0};}
    edge<T> findset(int x){
        return x==F[x].f?F[x]:F[x]+=findset(F[x].f);
    }
    void merge(int x,int y){
        F[x].v=abs(x-y)%1000;F[x]+=findset(y);
    }
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--){
        int n,x,y;cin>>n;valdset<int> ds(n+1);
        for(string s;cin>>s&&s[0]!='O';){
            if(s[0]=='E') cin>>x,cout<<ds.findset(x).v<<'\n';
            else cin>>x>>y,ds.merge(x,y);
        }
    }
    return 0;
}