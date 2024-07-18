#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto _infl=(lint)(1e15l);
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--) [&](){
        int n,k;cin>>n>>k;string s;cin>>s;
        vector<int> cnt;
        [&](){
            auto ci=0;
            cir(i,0,n){
                if(i&&s[i]!=s[i-1]) cnt.push_back(ci),ci=0;
                ++ci;
            }
            cnt.push_back(ci);
        }();
        auto cntx=0;
        cir(i,0,(int)(cnt.size()-1)) cntx+=(cnt[i]!=k);
        if(cntx>1) return cout<<-1<<'\n',void();
        if(!cntx) return cout<<(cnt.back()==k?min((s[0]==s[n-1]?k*2:k),n):-1)<<'\n',void();
        auto p=0,pre=0,prep=0;
        cir(i,0,(int)(cnt.size())-1){
            if(cnt[i]!=k) p=i,prep=pre;
            pre+=cnt[i];
        }
        auto check=[&](string s){
            if(*max_element(s.begin(),s.begin()+k)!=
                *min_element(s.begin(),s.begin()+k)) return false;
            cir(i,0,n-k) if(s[i]==s[i+k]) return false;
            return true;
        };
        const auto px=prep+min(cnt.back()>k-1?k:k-cnt.back(),cnt[p]);
        auto sx=s.substr(0,px);
        auto sy=s.substr(px,n-px);
        ranges::reverse(sx);
        if(!check(sy+sx)) return cout<<-1<<'\n',void();
        cout<<px<<'\n';
    }();
    return 0;
}
