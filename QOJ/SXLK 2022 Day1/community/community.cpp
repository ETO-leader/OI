#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) []{
        int n,m;cin>>n>>m;
        unordered_set<string> usr;
        cir(i,0,n){
            string s;cin>>s;
            usr.emplace(s);
        }
        auto cnt=0;
        cir(i,0,m){
            string s1,s2,s3;cin>>s1>>s2>>s3;
            if(s3=="loushang"||s3=="louxia"){
                if(usr.count(s2)) ++cnt;
            }
        }
        cout<<cnt<<'\n';
        vector<int> a(m);
        iota(a.begin(),a.end(),1);
        for(auto&i:a) cout<<i<<' ';
        cout<<'\n';
    }();
    return 0;
}
