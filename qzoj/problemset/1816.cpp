#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
static constexpr auto maxv=(int)(1e6+7);
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    vector<int> isp(maxv,true),p;
    cir(i,2,maxv) if(isp[i]){
        p.emplace_back(i);
        for(auto x=(int64_t)(i)*i;x<maxv;x+=i) isp[x]=false;
    }
    int x;
    while(cin>>x&&x){
        for(auto&w:p) if(isp[x-w]){
            cout<<x<<" = "<<w<<" + "<<x-w<<'\n';
            break;
        }
    }
    return 0;
}
