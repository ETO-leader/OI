#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--){
        lint s,n;cin>>s>>n;
        if(!(s%10)){
            cout<<s*n<<'\n';continue;
        }
        if((s%10)==5){
            cout<<max((s+5)*(n-1),s*n)<<'\n';
            continue;
        }
        if(n<2){
            cout<<s<<'\n';continue;
        }
        unordered_set<int> ap;
        vector<lint> bc;int w=s%10;
        while(!ap.count((w*=2)%=10)){           
            ap.insert(w);bc.push_back(w);
        }
        vector<lint> pre=bc;
        cir(i,1,bc.size()) pre[i]=pre[i-1]+bc[i];
        const lint ad=1,adw=(s%10);
        const lint cursum=20,curlen=4;
        auto calc=[&](lint cur){
            if(!cur) return s;
            if(cur>n) return 0LL;
            int res=adw;cur-=ad;
            return s+res+cursum*(cur/curlen)+
                ((cur%curlen)?pre[cur%curlen-1]:0LL);
        };
        auto calc_x=[&](lint c,int _i){
            lint res=0;c*=curlen;
            //cir(i,0,3) if((c+i)<=n)
            res=max(res,calc(c+_i)*(n-c-_i));
            return res;
        };
        lint ans=0;
        cir(i,0,4){
            lint l=0,r=n/curlen;
            while(r>l){
                const lint ml=l+(r-l)/3,mr=l+(r-l)/3*2;
                if(ml==mr) break;
                const lint cl=calc_x(ml,i),cr=calc_x(mr,i);
                cl<cr?l=ml+1:r=mr-1;
                //cerr<<l<<' '<<r<<":"<<ml<<' '<<mr<<" -> "<<cl<<' '<<cr<<' '<<(cl<=cr)<<'\n';
            }
            //cout<<calc_x(700)<<' '<<calc_x(697)<<' '<<calc_x(701)<<'\n';
            //cout<<max({calc_x(l),calc_x(r),calc_x(0)})<<'\n';
            cir(x,l,r+1) ans=max(ans,calc_x(x,i));
            cir(x,0,50) ans=max(ans,calc_x(x,i));
        }
        cout<<ans<<'\n';
        //pair<lint,int> ans={0,0};
        //cir(i,0,n/curlen) ans=max(ans,make_pair(calc_x(i),i));
        //cout<<ans.second<<":"<<ans.first<<'\n';
    }
    return 0;
}
