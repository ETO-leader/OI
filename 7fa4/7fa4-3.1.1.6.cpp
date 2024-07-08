#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
template<typename T>
struct dsu{
    vector<T> F;
    dsu(T _n):F(_n){iota(F.begin(),F.end(),0);}
    int findset(T x){return F[x]==x?x:F[x]=findset(F[x]);}
    void merge(T u,T v){F[findset(u)]=findset(v);}
};
const int asciinum=150;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    string s;int T;cin>>T;
    unordered_set<int> Ap;
    dsu<int> sets(asciinum);
    while(cin>>s){
        auto f=s.front();
        for(auto&i:s){
            Ap.insert(i);
            if(sets.findset(f)!=sets.findset(i))
                sets.merge(f,i);
        }
    }
    int cnt=0;
    cir(i,0,asciinum) cnt+=(sets.findset(i)==i&&Ap.count(i));
    cout<<cnt<<'\n';
    return 0;
}