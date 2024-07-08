#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using VI=vector<int>;
struct result{int s,p;};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--){
        int m,n,t;cin>>m>>n>>t;
        vector<VI> v(m,VI(n));
        vector<result> vr;
        for(auto&i:v){
            for(auto&j:i) cin>>j;
            sort(i.begin(),i.end());
            int cnx=0,p=0,tcnx=0;
            for(auto&j:i){
                cnx+=j;
                if(cnx>t) break;
                ++p;tcnx+=cnx;
            }
            vr.push_back({p,tcnx});
        }
        auto rscore=vr.front();
        int cnx=0;
        sort(vr.begin(),vr.end(),[&](result&a,result&b){
            return a.s==b.s?a.p<b.p:a.s>b.s;});
        for(auto&i:vr){
            ++cnx;
            if(i.p==rscore.p&&i.s==rscore.s) break;
        }
        cout<<cnx<<'\n';
    }
    return 0;
}
