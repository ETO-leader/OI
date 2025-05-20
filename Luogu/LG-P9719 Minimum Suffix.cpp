#include<bits/stdc++.h>
#define cir(i,a,b) for(auto i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) []{
        int n;cin>>n;vector<int> a(n);
        for(auto&i:a) cin>>i,--i;
        vector<int> val(n),lef(n),pre(n),ans(n);
        auto vpos=[&](int r,int p){
            if(p>n-1) return -1;
            if(lef[p]!=r+1) return -1;
            return ans[p];
        };
        auto laslen=-1;
        for(auto r=n-1,l=a[r];~r;l=a[max((r=l-1),0)]){
            ans[r]=l;
            cir(i,l,r+1) lef[i]=l;
            cir(p,l,r+1) if(a[p]<l) return cout<<"-1"<<'\n',void();
            auto len=1;
            val[l]=1;
            cir(i,l+1,r+1){
                pre[i]=i-len;
                if(a[i]==l){
                    val[i]=1;
                    len=i-l+1;
                }else if(i-a[i]!=i-len-a[i-len]){
                    return cout<<"-1"<<'\n',void();
                }
            }
            auto ckd=false;
            ans[l]=max(vpos(r,r+1),1);
            cir(i,1,r-l+1){
                ans[l+i]=ans[pre[l+i]]+val[l+i];
                if(ans[l+i]>vpos(r,r+1+i)) ckd=true;
                if((!ckd)&&ans[l+i]<vpos(r,r+1+i)){
                    if(val[l+i]){
                        ans[l+i]=vpos(r,r+1+i);
                    }else{
                        auto pos=l+i;
                        while(!val[pos]) --pos;
                        ++ans[pos];ckd=true;
                        i=pos-l;
                    }
                }
            }
            if((!ckd)&&r-l+1<laslen){
                auto i=r;
                while(i>l-1&&(!val[i])) --i;
                ++ans[i];
                for(++i;i<r+1;++i) ans[i]=ans[pre[i]]+val[i];
            }
            laslen=r-l+1;
        }
        for(auto&i:ans) cout<<i<<' ';
        cout<<'\n';
    }();
    return 0;
}
