#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
template<const int bits>
class bigint{
private:
    vector<int64_t> w;
    void check(){
        auto cur=0ll;
        cir(i,0,bits){
            w[i]+=cur;
            cur=w[i]/10;
            w[i]%=10;
            if(w[i]<0) --cur,w[i]+=10;
        }
    }
public:
    bigint<bits>&operator*=(int x){
        for(auto&p:w) p*=x;
        check();
        return*this;
    }
    bigint<bits>&operator+=(bigint<bits> x){
        cir(i,0,bits) w[i]+=x.w[i];
        check();
        return*this;
    }
    string str(){
        string res;
        auto prt=w;
        while((int)(prt.size())>1&&(!prt.back())) prt.pop_back();
        reverse(prt.begin(),prt.end());
        for(auto&i:prt) res+=i+'0';
        return res;
    }
    bigint():w(bits){}
    bigint(int x):w(bits){
        w[0]=x;
        check();
    }
};
static constexpr auto maxlen=251;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,k;cin>>n>>k;
    if(k==2){
        cout<<(n==1||n==3||n==4||n==8)*2<<'\n';
    }else{
        const auto c=(int64_t)(k)*(k-1)*(k-2)/6;
        const auto d=(int64_t)(k)*(k-1)/2;
        if(n==1){
            auto ans=bigint<maxlen>(3);
            cir(i,0,19) ans*=2;
            ans+=-6;
            ans*=c;
            ans+=d*2;
            cout<<ans.str()<<'\n';
        }else if(n==2){
            auto ans=bigint<maxlen>(3);
            cir(i,0,5) ans*=2;
            ans*=c;
            cout<<ans.str()<<'\n';
        }else if(n==3){
            auto ans=bigint<maxlen>(3);
            cir(i,0,3) ans*=2;
            ans+=-6;
            ans*=c;
            ans+=d*2;
            cout<<ans.str()<<'\n';
        }else if(n==4){
            auto ans=bigint<maxlen>(3);
            cir(i,0,13) ans*=2;
            ans+=-6;
            ans*=c;
            ans+=d*2;
            cout<<ans.str()<<'\n';
        }else if(n==5){
            auto ans=bigint<maxlen>(3);
            cir(i,0,2) ans*=2;
            ans*=c;
            cout<<ans.str()<<'\n';
        }else if(n==6){
            const auto ans=c*6;
            cout<<ans<<'\n';
        }else if(n==7){
            auto ans=bigint<maxlen>(3);
            cir(i,0,5) ans*=2;
            ans*=c;
            cout<<ans.str()<<'\n';
        }else{
            auto ans=bigint<maxlen>(1073741820);
            ans*=c;
            ans+=d*2;
            cout<<ans.str()<<'\n';
        }
    }
    return 0;
} 
