#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;

#ifndef NSTDIO

namespace Stage1{
    void Stage1(int);
}
namespace Stage2{
    void Stage2(std::vector<int>);
}

auto answer(const int x){
    println(cout,"{}",x);
    cout.flush();
}

auto guess(const int u,const int v){
    println(cout,"{} {}",u,v);
    cout.flush();
}

auto currentHouse(){
    int u;cin>>u;
    return u;
}

int main(){
    int P,n;cin>>P>>n;
    if(P==1){
        Stage1::Stage1(n);
    }else{
        vector<int> a(n);
        for(auto&i:a) cin>>i;
        Stage2::Stage2(a);
    }
}

#endif

namespace Stage1{

    class segment{
    private:
        vector<int> siz;
        constexpr auto ls(auto u){return u*2;}
        constexpr auto rs(auto u){return u*2+1;}
        auto update(int u,int l,int r,int rl,int rr,int p,int cur,int h,int k){
            ++siz[u];
            assert(l<r+1);
            if(siz[u]==r-l+1) cur=(cur<0?h:cur);
            if(rl==rr) return k-cur+1;
            const auto mid=midpoint(rl,rr);
            return p-1<mid?update(ls(u),l,min(mid,r),rl,mid,p,cur,h+1,k):update(rs(u),mid+1,r,mid+1,rr,p,cur,h+1,k);
        }
        int n;
    public:
        auto access(int u,int k){
            const auto rn=1<<(int)(ceil(log2(n)));
            return update(1,0,n-1,0,rn-1,u,-1,0,k);
        }
        segment(int _n):n(_n),siz(_n<<4){}
    };

    void Stage1(const int n){
        if(n>31){
            const auto k=7;
            const auto last=31;
            answer(k);
            segment sg(last+1);
            auto sum=0ll;
            cir(i,0,n) sum+=i;
            set<int> cur;
            cir(i,0,n) cur.emplace(i);
            cir(i,0,n-last-1){
                const auto u=currentHouse();
                answer(k);sum-=u;cur.extract(u);
            }
            map<int,int> valp;
            for(auto cnt=-1;auto&i:cur) valp[i]=++cnt;
            sum%=n;
            cir(i,0,last){
                const auto u=currentHouse();
                const auto val=sg.access(valp[u],k-2);
                if(val==1){
                    const auto bit=(sum>>(valp[u]/2))&1;
                    if(bit) answer(k-1);
                    else answer(1);
                }else{
                    answer(val);
                }
            }
        }else{
            const auto k=ceil(log2(n));
            answer(k);
            segment sg(n);
            cir(i,0,n-1){
                const auto u=currentHouse();
                answer(sg.access(u,k));
            }
        }
    }

}

namespace Stage2{

    class segment{
    private:
        vector<pair<int,int>> maxval;
        unordered_set<int> isleaf;
        constexpr auto ls(auto u){return u*2;}
        constexpr auto rs(auto u){return u*2+1;}
        auto build(int u,int l,int r,const auto maxr,vector<int>&a){
            if(l==r) return isleaf.emplace(u),maxval[u]=pair(a[l],l>maxr?-1:l);
            const auto mid=midpoint(l,r);
            maxval[u]=max(build(ls(u),l,mid,maxr,a),build(rs(u),mid+1,r,maxr,a));
            return maxval[u];
        }
        auto divide(int u){
            if(isleaf.count(u)) return pair(maxval[u].second,maxval[u].second);
            if(maxval[ls(u)].first==maxval[rs(u)].first){
                return pair(maxval[ls(u)].second,maxval[rs(u)].second);
            }
            if(maxval[rs(u)].second<0) return divide(ls(u));
            return divide((maxval[ls(u)].first>maxval[rs(u)].first)?rs(u):ls(u));
        }
    public:
        auto check(){
            return divide(1);
        }
        segment(vector<int> a):maxval(a.size()<<4){
            const auto sza=(int)(a.size());
            a.resize(1<<(int)(ceil(log2(a.size()))));
            build(1,0,(int)(a.size())-1,sza-1,a);
        }
    };

    void Stage2(vector<int> a){
        const auto n=(int)(a.size());
        if(n>31){
            const auto k=7;
            const auto last=31;
            auto cntless=n-ranges::count(a,k);
            if(cntless==last){
                vector<int> pos;
                cir(i,0,n) if(a[i]==1||a[i]==k-1){
                    pos.emplace_back(a[i]==k-1);
                }
                ranges::reverse(pos);
                auto sum=0;
                for(auto&i:pos) (sum<<=1)|=i;
                auto rsum=0;
                cir(i,0,n) if(a[i]<k) rsum+=i;
                vector<int> ans;
                cir(i,0,n) if((((rsum+i)%n)&65535)==((sum%n)&65535)) ans.emplace_back(i);
                if(ans.size()==1) ans.emplace_back(ans.back());
                guess(ans[0],ans[1]);
            }else{
                map<int,int> pos;
                for(auto cnt=-1,x=-1;auto&w:a) if(++x;w<k) pos[++cnt]=x;
                for(auto&w:a) if(w==k-1) w=1;
                vector<int> arr;
                for(auto&[id,p]:pos) arr.emplace_back(a[p]);
                const auto[ax,ay]=segment(arr).check();
                guess(pos[ax],pos[ay]);
            }
        }else{
            const auto[u,v]=segment(a).check();
            guess(u,v);
        }
    }

}


