#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
vector<map<vector<int>,lint>> f;
class checker{
private:
    vector<int> a;
    auto dfs(int u,vector<int> s,bool lim,bool pre){
        if(u<0){
            return max<lint>(*max_element(s.begin(),s.end()),1);
        }
        if((!lim)&&(!pre)){
            sort(s.begin(),s.end());
            if(f[u].count(s)) return f[u][s];
        }
        auto res=0ll;
        cir(i,0,(lim?a[u]+1:10)){
            if(i||(!pre)) ++s[i];
            res+=dfs(u-1,s,lim&&(i==a[u]),pre&&(!i));
            if(i||(!pre)) --s[i];
        }
        if((!lim)&&(!pre)) f[u][s]=res;
        return res;
    }
public:
    auto check(lint x){
        if(x<0) return 0ll;
        auto ad=0;
        if(x==1e18l) --x,ad+=18;
        cir(i,0,18) a.push_back(x%10),x/=10;
        if(f.empty()) f.resize(a.size());
        return ad+dfs((int)(a.size())-1,vector<int>(10),true,true);
    }
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--) [](){
        lint l,r;cin>>l>>r;
        cout<<checker().check(r)-checker().check(l-1)<<'\n';
    }();
    return 0;
}
