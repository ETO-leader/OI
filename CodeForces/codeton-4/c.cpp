#include<bits/extc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&]{
        int n;lint c,d;cin>>n>>c>>d;
        vector<int> a(n);
        map<int,int> cnt;
        for(auto&i:a){
            cin>>i;++cnt[i];
        }
        auto ans=0ll;
        for(auto&[a,b]:cnt) ans+=(b-1)*c;
        auto adw=numeric_limits<lint>::max();
        [&]{
            auto lcnt=(int)(cnt.size()),ucnt=0;
            auto las=0;
            for(auto&[a,b]:cnt){
                --lcnt;ucnt+=(a-las-1);
                adw=min(adw,ucnt*d+lcnt*c);
                las=a;
            }
        }();
        [&]{
            auto lcnt=(int)(cnt.size()),ucnt=0;
            cir(w,1,7){
                if(cnt.contains(w)) --lcnt;
                else ++ucnt;
                adw=min(adw,ucnt*d+lcnt*c);
            }
        }();
        cout<<adw+ans<<'\n';
    }();
    return 0;
}
