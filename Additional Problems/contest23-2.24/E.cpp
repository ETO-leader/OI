#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;string s;
    function<void(int,int)> prt=[&](int p,int pre){
        if(p==n) return cout<<s<<'\n',void();
        cir(i,'a','a'+pre+2){
            s.push_back(i);
            prt(p+1,max(pre,i-'a'));
            s.pop_back();
        }
    };
    prt(0,-1);
    return 0;
}
