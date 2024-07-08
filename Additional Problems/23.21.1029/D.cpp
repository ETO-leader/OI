#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using VI=vector<int>;
struct seg{int l,r;};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,q;cin>>n>>q;
    string s,st;cin>>s>>st;
    const int ups=log2(n)+2;
    for(auto&i:st) i-='0';
    vector<VI> upl((n<<1),VI(ups)),
        upr((n<<1),VI(ups))
        ,upw((n<<1),VI(ups));
    VI prel(n<<1),prer(n<<1);
    vector<seg> alsegs;
    //init
    [&](){
        queue<int> ls,rs;int cnx=0;
        cir(i,0,n*2){
            if(s[i]=='L') ls.push(i);
            upl[i][0]=ls.front();
            if(s[i]=='R'){
                alsegs.push_back({ls.front(),i});
                if(st[cnx++]){
                    ++prel[ls.front()];
                    ++prer[i];
                }
                ls.pop();
            }
            cir(x,1,ups){
                upl[i][x]=upl[upl[i][x-1]][x-1];
            }
        }
        for(int i=n*2-1;~i;--i){
            if(s[i]=='R') rs.push(i);
            upr[i][0]=rs.front();
            if(s[i]=='L') rs.pop();
            cir(x,1,ups){
                upr[i][x]=upr[upr[i][x-1]][x-1];
            }
        }
        cir(i,1,(n<<1)){
            prel[i]+=prel[i-1];
            prer[i]+=prer[i-1];
        }
        cir(i,0,(n<<1)){
            upw[i][0]=prel[i]-prer[upl[upr[i][0]][0]];
            cir(x,1,ups){
                upw[i][x]=upw[upl[i][x-1]][x-1]
                    +upw[i][x-1];
            }
        }
    }();
    auto getdis=[&](int a,int b){
        int res=1;
        if(a>b-1) return res;
        for(int i=ups-1;~i;--i) if(upr[a][i]<b)
            a=upr[a][i],res+=(1<<i);
        return res+(a<b);
    };
    auto getans=[&](int a,int b){
        int res=0;
        for(int i=ups-1;~i;--i) if(upl[b][i]>a)
            res+=upw[b][i],b=upl[b][i];
        return res+upw[b][0]*(a<b);
    };
    while(q--){
        int a,b;cin>>a>>b;
        int ad=st[a-1]+st[b-1];
        auto s=alsegs[a-1].r,t=alsegs[b-1].l;
        auto dist=getdis(s,t);
        cout<<dist<<' '<</*[&](){
            int res=0;
            for(auto&[l,r]:segs){
                if(l==b||r==a){
                    ++res;continue;
                }
                res+=(getdis(a,l)+getdis(
                    r,b))==getdis(a,b);
            }
            return res;
        }()*/getans(a,b)+ad<<'\n';
    }
    return 0;
}
