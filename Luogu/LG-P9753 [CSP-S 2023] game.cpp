#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using ull=unsigned long long;
class arrhash{
private:
    static constexpr auto hashc=251ull;
    stack<ull> cur;
public:
    auto emplace(char c){
        cur.push(cur.top()*hashc+c);
    }
    auto pop(){
        cur.pop();
    }
    auto get(){return cur.top();}
    arrhash(){cur.push(0);}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;string s;cin>>s;
    arrhash arc;
    stack<char> las;
    unordered_map<ull,int> cnt;
    ++cnt[0];
    auto ans=0ll;
    cir(i,0,n){
        if(las.empty()||las.top()!=s[i]) las.push(s[i]),arc.emplace(s[i]);
        else las.pop(),arc.pop();
        ans+=cnt[arc.get()];
        ++cnt[arc.get()];
    }
    cout<<ans<<'\n';
    return 0;
}
