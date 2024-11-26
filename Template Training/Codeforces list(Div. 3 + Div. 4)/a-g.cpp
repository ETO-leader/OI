#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) []{
        int n;cin>>n;
        if(n<4) return println("-1");
        auto i=0;
        for(;n-i>8;i+=4) print("{} {} {} {} ",i+2,i+4,i+1,i+3);
        const auto las=i+3;
        vector<int> a;
        for(;i<n;++i) a.push_back(i+1);
        do{
            auto ok=true;
            cir(i,0,(int)(a.size())){
                const auto c=i?a[i-1]:las;
                if((abs(a[i]-c)<2||abs(a[i]-c)>4)&&(!((!i)&&las==3))) ok=false;
            }
            if(ok) break;
        }while(ranges::next_permutation(a).found);
        for(auto&i:a) print("{} ",i);
        println("");
    }();
    return 0;
}
