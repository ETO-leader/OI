#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) []{
        int n;cin>>n;
        vector<pair<int,int>> q(n);
        for(auto&[l,r]:q) cin>>l>>r;
        vector<int> invaild(n*2+7);
        for(auto&[l,r]:q) if(l==r) ++invaild[l];
        vector<int> ok(n*2+7);
        cir(i,0,n*2+7) ok[i]=(i?ok[i-1]:0)+(bool)(invaild[i]);
        for(auto&[l,r]:q) if(l==r){
            print("{}",(int)(invaild[l]==1));
        }else{
            print("{}",(int)((ok[r]-ok[l-1])!=r-l+1));
        }
        println("");
    }();
    return 0;
}
