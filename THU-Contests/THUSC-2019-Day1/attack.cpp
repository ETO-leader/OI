#include"attack.h"
#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;

namespace MatrixOp{

    static auto cost=0;
    int P;
    static inline auto count_bit(int x){
        return x?32-__builtin_clz(x):1;
    }
    static inline auto mul(int x,int y,int&local_cost){
        local_cost+=count_bit(x)*count_bit(y);
        return (long long)x*y%P;
    }
    auto operator*(const Matrix&x,const Matrix&y){
        auto z=Matrix();
        auto local_cost=cost;
    #define CALC(i,j,k) z.a[i][j]=(mul(x.a[i][k],y.a[k][j],local_cost)+z.a[i][j])%P;
    #define CALC1(i,j) z.a[i][j]=0;CALC(i,j,0);
    #define CALC2(i,j) CALC1(i,j);CALC(i,j,1);
        CALC2(0, 0);CALC2(0,1);
        CALC2(1, 0);CALC2(1,1);
        cost=local_cost;
    #undef CALC2
    #undef CALC1
    #undef CALC
        return z;
    }
    auto unit(){
        Matrix x;
        cir(i,0,2) cir(j,0,2) x.a[i][j] = (i == j);
        return x;
    }
    auto power(Matrix x,auto Q){
        auto ans=unit();
        cir(i,0,31){
            if(Q>>i&1) ans=ans*x;
            x=x*x;
        }
        return ans;
    }

}

#ifdef STABLE
    mt19937_64 rnd(251);
#endif

void attack(int N,int P,int&U,int&V,int*Qs){
    if(N==1){
        U=V=0;
        cir(i,0,500) Qs[i]=i;
    }else if(P>(1<<16)){
        while(![&]{
            Matrix x;
            for(auto&w:x.a) for(auto&i:w) i=
            #ifdef STABLE
                rnd()%P;
            #else
                random_device().operator()()%P;
            #endif
            const auto basic=get_time(x);
            auto cnt=0;
            cir(i,0,2) cir(j,0,2){
                const auto las=x.a[i][j];
                if(las!=0) x.a[i][j]=0;
                if(get_time(x)==basic){
                    U=i;V=j;++cnt;
                }
                x.a[i][j]=las;
            }
            return cnt==1;
        }());
        const auto ansQ=get_q();
        cir(i,0,500) Qs[i]=ansQ;
    }else{
        MatrixOp::P=P;
        while(![&]{
            Matrix x;
            for(auto&w:x.a) for(auto&i:w) i=
            #ifdef STABLE
                rnd()%P;
            #else
                random_device().operator()()%P;
            #endif
            const auto basic=get_time(x);
            auto cnt=0;
            cir(i,0,2) cir(j,0,2){
                const auto las=x.a[i][j];
                if(las!=0) x.a[i][j]=0;
                if(get_time(x)==basic){
                    U=i;V=j;++cnt;
                }
                x.a[i][j]=las;
            }
            return cnt==1;
        }());
        const auto w=get_w(),y=get_y();
        set<int> vaild;
        cir(i,0,P) vaild.emplace(i);
        Matrix x;
        while(vaild.size()>500){
            for(auto&w:x.a) for(auto&i:w) i=
            #ifdef STABLE
                rnd()%P;
            #else
                random_device().operator()()%P;
            #endif
            auto sum=0;
            cir(i,0,2) cir(j,0,2) if((i!=U)&&(j!=V)) (sum+=x.a[i][j])%=P;
            x.a[U][V]=((int64_t)(sum)*w+y)%P;
            for(auto&w:x.a){
                for(auto&i:w) clog<<i<<' ';
                clog<<'\n';
            }
            const auto T=get_time(x); //-MatrixOp::count_bit(sum)*MatrixOp::count_bit(w);
            cir(c,0,P) if(MatrixOp::cost=0,MatrixOp::power(x,c);MatrixOp::cost!=T&&vaild.count(c)){
                vaild.extract(c);
                if(c==1928) clog<<MatrixOp::cost<<": "<<T<<'\n';
            }
        }
        auto c=-1;
        for(auto&i:vaild) Qs[++c]=i;
        cir(i,c+1,500) Qs[i]=0;
    }
}
