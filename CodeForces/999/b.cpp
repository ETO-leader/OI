#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&]{
        int n;cin>>n;map<int,int> cnt;
        vector<int> a;
        cir(i,0,n){
            int l;cin>>l;++cnt[l];
            a.emplace_back(l);
        }
        vector<int> gr;
        for(auto&[l,c]:cnt) if(c>1) gr.emplace_back(l);
        if(gr.empty()) return println("-1");
        if(gr.size()>1){
            println("{} {} {} {}",gr[0],gr[0],gr[1],gr[1]);
        }else{
            const auto w=gr[0];
            a.erase(ranges::find(a,w));
            a.erase(ranges::find(a,w));
            ranges::sort(a);
            cir(i,0,(int)(a.size())-1){
                if(a[i+1]-a[i]<w*2){
                    return println("{} {} {} {}",a[i],a[i+1],w,w);
                }
            }
            println("-1");
        }
    }();
    return 0;
}
