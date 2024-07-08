#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
static constexpr size_t maxm=1e5+7;
using bst=bitset<maxm>;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;cin>>n>>m;
    unordered_map<int,int> opid;
    cir(i,0,n){
        int p;cin>>p;opid[p]=i;
    }
    string mv;cin>>mv;
    vector<int> ops(m,-1);bst sta;
    auto endpos=[&](){
        int p=0,cur=-1;
        for(auto&i:mv){
            ++cur;
            if(i=='F'){
                if(opid.count(p)){
                    if(sta.test(opid[p])) continue;
                    ops[cur]=opid[p];
                    sta.set(opid[p]);
                }
            }else{
                p+=(i=='L'?-1:1);
            }
        }
        return p;
    }();
    auto ans=sta.count();
    auto ins_shoot=[&](int mvs){
        auto p=endpos+mvs;
        auto check=[&](int pos){
            return (mv[pos]=='L'&&mvs>0)||
                (mv[pos]=='R'&&mvs<0);
        };
        auto cpst=sta,nst=bst();
        for(int i=m-1;~i;--i){
            if(ops[i]>-1) cpst.reset(ops[i]);
            if(check(i)){
                bool flg=false;
                if(opid.count(p)){
                    flg=(!nst.test(opid[p]));
                    nst.set(opid[p]);
                }
                ans=max(ans,(cpst|nst).count());
                if(opid.count(p)&&flg){
                    nst.reset(opid[p]);
                }
            }
            if(mv[i]=='F'){
                if(opid.count(p)) nst.set(opid[p]);
            }else{
                p+=(mv[i]=='R'?-1:1);
            }
        }
    };
    auto rmv_shoot=[&](int mvs){
        auto p=endpos+mvs;
        auto check=[&](int pos){
            return mv[pos]=='F';
        };
        auto cpst=sta,nst=bst();
        for(int i=m-1;~i;--i){
            if(ops[i]>-1) cpst.reset(ops[i]);
            if(check(i)){
                ans=max(ans,(cpst|nst).count());
                //if(((cpst|nst).count())==11) clog<<"ers'F'\n";
            }
            if(mv[i]=='F'){
                if(opid.count(p)) nst.set(opid[p]);
            }else{
                p+=(mv[i]=='R'?-1:1);
            }
        }
    };
    auto chg_direct=[&](int mvs){
        auto p=endpos+mvs;
        auto check=[&](int pos){
            return (mv[pos]=='L'&&mvs>0)||
                (mv[pos]=='R'&&mvs<0);
        };
        auto cpst=sta,nst=bst();
        for(int i=m-1;~i;--i){
            if(ops[i]>-1) cpst.reset(ops[i]);
            if(check(i)){
                ans=max(ans,(cpst|nst).count());
                //if(((cpst|nst).count())==11) clog<<mvs<<' '<<mv[i]<<' '<<"chg'D'\n";
            }
            if(mv[i]=='F'){
                if(opid.count(p)) nst.set(opid[p]);
            }else{
                p+=(mv[i]=='R'?-1:1);
            }
        }
    };
    ins_shoot(-1);ins_shoot(1);
    rmv_shoot(-1);rmv_shoot(1);
    chg_direct(-2);chg_direct(2);
    cout<<ans<<'\n';
    return 0;
}