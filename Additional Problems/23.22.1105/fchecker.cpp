#include<bits/stdc++.h>
#define cir(i,a,b) for(auto i=a;i<b;++i)
using namespace std;
ifstream fcin("fraction.in");
ofstream fcout("fraction.ans");
class fileio{
public:
    ~fileio(){
        fcin.close();fcout.close();
    }
} use_fileio;
using __int=__int128;
using VI=vector<__int>;
istream&operator>>(istream&is,__int&x){
    x=0;string s;is>>s;
    for(auto&i:s) (x*=10)+=(i-'0');
    return is;
}
ostream&operator<<(ostream&os,__int x){
    if(x>9) os<<(x/10);
    return os<<(int)(x%10);
}
int main(){
    ios::sync_with_stdio(false),fcin.tie(0);
    __int n,ans=0;fcin>>n;
    auto getpre=[&](__int x){
        __int res=0;
        for(__int k=1;k<x+1;k*=2){
            for(__int w=1;w*k<x+1;w*=5){
                ++res;
            }
        }
        return res;
    };
    cir(i,__int(1),n+1) if((i%2)&&(i%5)){
        ans+=(n/i)*getpre(n/i);
    }
    fcout<<ans<<'\n';
    return 0;
}
