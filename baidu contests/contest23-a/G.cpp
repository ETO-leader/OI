#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using ull=unsigned long long;
template<typename T>
class hashing{
private:
    const T hashc=127;
    vector<T> hsh,pw;
    void initpw(int n){
        cir(i,1,n) pw[i]=pw[i-1]*hashc;
    }
public:
    T range(int l,int r){
        return hsh[r]-(l?hsh[l-1]*pw[r-l+1]:0);
    }
    T hash(){return hsh.back();}
    hashing(string s):hsh(s.size()),pw(s.size(),1){
        hsh[0]=s[0];initpw(s.size());
        cir(i,1,s.size())
            hsh[i]=hsh[i-1]*hashc+s[i];
    }
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,k;cin>>n>>k;
    string s;cin>>s;
    hashing<ull> hsh(s);
    const int anslen=n-k;
    int l=0,r=anslen-1;
    cir(i,1,n-anslen+1){
        //bound
        auto pos=[&](){
            int ql=0,qr=anslen-1,res=-1;
            while(ql<=qr){
                const int mid=(ql+qr)/2;
                [&](){
                    return hsh.range(l,l+mid)==
                        hsh.range(i,i+mid);
                }()?(ql=mid+1):((qr=mid-1),(res=mid));
            }
            return res;
        }();
        if(pos<0) continue;
        if(s[i+pos]>s[l+pos]) l=i,r=i+anslen-1;
    }
    vector<int> ans(n);
    cir(i,l,r+1) ans[i-l]=(s[r-i+l]-'0');
    int w=0,wx=0,p=0;
    cir(i,0,l) w+=(s[i]-'0');
    cir(i,r+1,n) w+=(s[i]-'0');
    while(w||wx){
        ans[p]+=(w%10)+wx;w/=10;
        wx=ans[p]/10;ans[p]%=10;
        ++p;
    }
    while(!ans.back()) ans.pop_back();
    reverse(ans.begin(),ans.end());
    for(auto&i:ans) cout<<i;
    cout<<'\n';
    return 0;
}
