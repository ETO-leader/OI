#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
namespace math{
    using db=long double;
    class vector{
        db a,b;
    public:
        vector&operator+=(vector x){
            a+=x.a;b+=x.b;return *this;}
        vector&operator*=(db x){
            a*=x;b*=x;return *this;}
        vector operator+(vector x) const{
            return x+=(*this);}
        vector operator*(int x) const{
            return vector(*this)*=x;}
        db length() const{
            return std::sqrt(a*a+b*b);}
        void ___(){std::cerr<<a<<' '<<b<<'\n';}
        vector(db ax=0,db bx=0):a(ax),b(bx){}
    };
};
using namespace std;
using math::db;
static constexpr db mxl=1.5e6;
auto&operator>>(istream&is,math::vector&a){
    db ax,bx;is>>ax>>bx;a=math::vector(ax,bx);
    return is;
}
bool ckr(auto&x,stringstream&oup){
    random_shuffle(x.begin(),x.end());
    math::vector nwvec;
    vector<int> ans(x.size());
    for(auto&[i,id]:x){
        ans.at(id)=((nwvec+i).length()<
            (nwvec+i*-1).length()?1:-1);
        nwvec+=(i*ans.at(id));
    }
    if(nwvec.length()<mxl){
        for(auto&i:ans) oup<<i<<' ';
        return true;
    }
    return false;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;
    vector<pair<math::vector,int>> a(n);
    [&](){
        int c=0;
        for(auto&[i,id]:a) cin>>i,id=c++;
    }();
    stringstream prt;
    while(!ckr(a,prt)) rand();
    cout<<prt.str()<<'\n';
    return 0;
}