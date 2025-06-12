#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lf=long double;
using point=complex<lf>;
using vector_t=complex<lf>;
static constexpr auto eps=1e-10l;
lf dot(vector_t a,vector_t b){
    return real(a*conj(b));
}
lf cross(vector_t a,vector_t b){
    return imag(a*conj(b));
}
class sign_t{
private:
    bool neg,pos,any;
public:
    bool operator==(const sign_t y) const{
        if(any||y.any) return true;
        if(pos&&y.pos) return true;
        if(neg&&y.neg) return true;
        return false;
    }
    bool is_any() const{return any;}
    static sign_t neg_v(){return sign_t(true,false,false);}
    static sign_t pos_v(){return sign_t(false,true,false);}
    static sign_t any_v(){return sign_t(false,false,true);}
    sign_t(bool _x,bool _y,bool _z):neg(_x),pos(_y),any(_z){}
};
const sign_t sign(lf x){
    if(abs(x)<eps) return sign_t::any_v();
    return x>0?sign_t::pos_v():sign_t::neg_v();
}
istream&operator>>(istream&is,complex<lf>&u){
    lf x,y;is>>x>>y;
    u=complex<lf>(x,y);
    return is;
}
// auto convex(vector<point> px){
//     ranges::sort(px,[](auto&a,auto&b){
//         if(abs(real(a)-real(b))<eps) return imag(a)>imag(b);
//         return real(a)<real(b);
//     });
//     vector<point> lower;
//     vector<lf> args;
//     for(auto&u:px){
//         if(lower.empty()){
//             lower.emplace_back(u);
//         }else{
//             while(lower.size()>1){
//                 const auto argu=arg(u-lower.back());
//                 if(argu>args.back()) break;
//                 lower.pop_back();args.pop_back(); 
//             }
//             args.emplace_back(arg(u-lower.back()));
//             lower.emplace_back(u);
//         }
//     }
//     args.clear();
//     vector<point> upper;
//     for(auto&u:views::reverse(px)){
//         if(upper.empty()){
//             upper.emplace_back(u);
//         }else{
//             while(upper.size()>1){
//                 const auto argu=arg(u-upper.back());
//                 if(argu<args.back()) break;
//                 upper.pop_back();args.pop_back(); 
//             }
//             args.emplace_back(arg(u-upper.back()));
//             upper.emplace_back(u);
//         }
//     }
//     auto res=lower;
//     upper.erase(upper.begin());
//     if(!upper.empty()) upper.pop_back();
//     for(auto&u:upper) res.emplace_back(u);
//     return res;
// }
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;vector<point> cheese(n);
    for(auto&u:cheese) cin>>u;
    int m;cin>>m;
    vector<point> chili(m);
    for(auto&u:chili) cin>>u;
    const auto conv=chili;// convex(chili);
    const auto k=(int)(conv.size());
    auto vaild=[&](point u,int id){
        const auto prv=(id+k-1)%k;
        const auto nxt=(id+1)%k;
        const auto ln=conv[id]-u;
        const auto prv_v=conv[prv]-u;
        const auto nxt_v=conv[nxt]-u;
        return sign(cross(ln,prv_v))==sign(cross(ln,nxt_v));
    };
    auto check=[&](point u,point v){
        const auto ln=v-u;
        for(auto&x:conv){
            if(sign(cross(x-u,ln))==sign_t::neg_v()) return false;
        }
        return true;
    };
    auto cur=0.0l,ans=0.0l;
    auto p=0;
    cir(i,0,n){
        while(check(cheese[i],cheese[(p+1)%n])){
            cur+=cross(cheese[p],cheese[(p+1)%n]);
            (++p)%=n;
        }
        const auto siz=cur+cross(cheese[p],cheese[i]);
        ans=max(ans,-siz);
        cur-=cross(cheese[i],cheese[(i+1)%n]);
    }
    cout<<(int64_t)(roundl(ans))<<'\n';
    return 0;
}
