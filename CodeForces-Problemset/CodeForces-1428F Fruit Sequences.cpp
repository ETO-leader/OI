#include<bits/stdc++.h>
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;string s;cin>>n>>s;
    cout<<[&](){
        vector<int> nx(n,n);int nw=-1;
        lint res=0,cnx=0;
        for(int i=n-1;~i;--i){
            if(s[i]-'0'){
                ++nw;cnx+=nx[nw]-i;
            }else{
                while(~nw) nx[nw]=i+nw+1,--nw;
            }
            res+=cnx;
        }
        return res;
    }()<<'\n';
    return 0;
}
