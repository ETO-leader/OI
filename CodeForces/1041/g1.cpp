#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) []{
        int n;cin>>n;
        const auto k=(n-3)/4+1;
        cout<<k+1<<'\n';
        cout.flush();
        vector<int> ans(n);
        cir(i,0,n){
            set<int> vaild;
            cir(w,0,n) if(w!=i) vaild.emplace(w);
            auto check=[&]{
                vector<int> a(k,-1),b(n-k*2-1,-1),c(k,-1);
                const auto lr=max(min((int)(a.size()+c.size()),(int)(vaild.size()+1)/2),(int)(vaild.size())-(int)(b.size()));
                auto ok=vector(vaild.begin(),vaild.end());
                cir(i,0,min((int)(a.size()),lr)) a[i]=ok[i];
                cir(i,0,lr-(int)(a.size())) c[i]=ok[i+(int)(a.size())];
                cir(i,0,(int)(vaild.size())-lr) b[i]=ok[i+lr];
                vector<int> nv;
                cir(w,0,n) if(w!=i&&(!vaild.contains(w))) nv.emplace_back(w);
                for(auto&x:a) if(x<0) x=nv.back(),nv.pop_back();
                for(auto&x:b) if(x<0) x=nv.back(),nv.pop_back();
                for(auto&x:c) if(x<0) x=nv.back(),nv.pop_back();
                cout<<"? ";
                for(auto&x:a) cout<<x+1<<' ';
                cout<<i+1<<' ';
                for(auto&x:b) cout<<x+1<<' ';
                for(auto&x:c) cout<<x+1<<' ';
                cout<<'\n';
                cout.flush();
                int ca;cin>>ca;
                cout<<"? ";
                for(auto&x:views::reverse(c)) cout<<x+1<<' ';
                cout<<i+1<<' ';
                for(auto&x:views::reverse(b)) cout<<x+1<<' ';
                for(auto&x:views::reverse(a)) cout<<x+1<<' ';
                cout<<'\n';
                cout.flush();
                int cb;cin>>cb;
                if(ca+cb!=n-1) vaild=set(ok.begin()+lr,ok.end());
                else vaild=set(ok.begin(),ok.begin()+lr);
            };
            while(vaild.size()>1) check();
            ans[*vaild.begin()]=i;
        }
        cout<<"! ";
        for(auto&i:ans) cout<<i+1<<' ';
        cout<<'\n';
        cout.flush();
    }();
    return 0;
}
