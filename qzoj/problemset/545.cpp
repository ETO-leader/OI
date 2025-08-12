#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;
    string s;cin>>s;
    if(n&1){
        const auto l=n/2;
        if(s.substr(0,l)==s.substr(l+1,l)){
            cout<<s.substr(0,l)<<'\n';
        }else{
            auto w=[&]{
                auto p=l;
                auto fl=false;
                cir(u,0,l){
                    while(s[u]!=s[p]){
                        if(fl) return 0;
                        fl=true;++p;
                    }
                    ++p;
                }
                if(fl) return 1;
                return s[n-2]==s[n-1]?2:1;
            }();
            auto nw=[&]{
                auto p=0;
                auto fl=false;
                cir(u,l+1,n){
                    while(s[u]!=s[p]){
                        if(fl) return 0;
                        fl=true;++p;
                    }
                    ++p;
                }
                if(fl) return 1;
                return s[l-1]==s[l]?2:1;
            }();
            if(w&&nw) cout<<"NOT UNIQUE"<<'\n';
            else if(w){
                if(w==1) cout<<s.substr(0,l)<<'\n';
                else cout<<"NOT UNIQUE"<<'\n';
            }else{
                if(nw==1) cout<<s.substr(l+1,l)<<'\n';
                else if(nw==2) cout<<"NOT UNIQUE"<<'\n';
                else cout<<"NOT POSSIBLE"<<'\n';
            }
        }
    }else{
        cout<<"NOT POSSIBLE"<<'\n';
    }
    return 0;
}
