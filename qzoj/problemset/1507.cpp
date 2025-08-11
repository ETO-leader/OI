#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
class bigint:public vector<int>{
public:
    auto operator*(const lint x) const{
        auto res=*this;
        auto w=0ll;
        cir(i,0,20) res.emplace_back(0);
        for(auto&i:res){
            (w/=10)+=i*x;
            i=w%10;
        }
        while(res.size()>1&&(!res.back())) res.pop_back();
        return res;
    }
    auto operator/(const lint x) const{
        auto info=*this;
        auto res=bigint("");
        auto w=0ll;
        reverse(info.begin(),info.end());
        for(auto&i:info){
            res.emplace_back(((w*=10)+=i)/x);
            w%=x;
        }
        reverse(res.begin(),res.end());
        while(res.size()>1&&(!res.back())) res.pop_back();
        return res;
    }
    auto operator+(bigint a) const{
        auto res=*this;
        res.resize(max(res.size(),a.size())+20);
        cir(i,0,(int)(a.size())) res[i]+=a[i];
        auto w=0ll;
        for(auto&x:res) x=((w/=10)+=x)%10;
        while(res.size()>1&&(!res.back())) res.pop_back();
        return res;
    }
    auto operator<(bigint a) const{
        if(this->size()<a.size()) return true;
        if(this->size()>a.size()) return false;
        for(auto i=(int)(this->size())-1;~i;--i){
            if((*this)[i]<a[i]) return true;
            if((*this)[i]>a[i]) return false;
        }
        return false;
    }
    auto str(){
        auto res=(string)("");
        for(auto&x:*this) res+=x+'0';
        reverse(res.begin(),res.end());
        return res;
    }
    bigint(string s){
        reverse(s.begin(),s.end());
        cir(i,0,(int)(s.size())) this->emplace_back(s[i]-'0');
    }
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;
    vector<pair<lint,lint>> a(n);
    int u,v;cin>>u>>v;
    for(auto&[x,y]:a) cin>>x>>y;
    sort(a.begin(),a.end(),[](auto&a,auto&b){
        return a.first*a.second<b.first*b.second;
    });
    auto pw=bigint(to_string(u)),ans=bigint("0");
    for(auto&[x,y]:a){
        ans=ans<(pw/y)?(pw/y):ans;
        pw=pw*x;
    }
    cout<<ans.str()<<'\n';
    return 0;
}
