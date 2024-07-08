#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--) [&](){
        int n;lint x,y;cin>>n>>x>>y;
        string s1,s2;cin>>s1>>s2;
        vector<int> diff;
        //check
        if(![&](){
            bool _ok=true;
            cir(i,0,n) if(s1[i]!=s2[i]){
                _ok^=1;
                diff.push_back(i);
            }
            return _ok;
        }()) return cout<<"-1\n",void();
        if(diff.empty())
            return cout<<"0\n",void();
        if(x<y){
            vector<long double> D(diff.size()+1);
            D[1]=y/2.0L;
            cir(i,2,(int)(diff.size())+1){
                D[i]=min<long double>(D[i-1]+y/2.0L,
                    D[i-2]+(diff[i-1]-diff[i-2])*x);
            }
            cout<<(lint)(round(D.back()))<<'\n';
        }else{
            if(diff.size()>2){
                cout<<diff.size()/2*y<<'\n';
            }else if(!diff.empty()){
                cout<<(diff[0]+1==diff[1]?
                    min(x,y*2):y)<<'\n';
            }
        }
    }();
    return 0;
}
