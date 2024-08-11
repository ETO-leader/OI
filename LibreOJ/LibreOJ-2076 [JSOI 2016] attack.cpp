#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
static constexpr auto eps=1e-12;
class randomdevice{
private:
    mt19937 eng;
public:
    auto randint(int l,int r){
        return uniform_int_distribution<int>(l,r)(eng);
    }
    auto randreal(double l,double r){
        return uniform_real_distribution<double>(l,r)(eng);
    }
    randomdevice():eng(random_device().operator()()){}
} rnd;
class individual{
private:
    double x,y,r;
    int fitness;
    function<double(double,double)> maxr;
    function<int(double,double,double)> clcfitness;
public:
    auto crossover(const double mdelta) const{
        return individual(
            x+rnd.randreal(-mdelta,mdelta),
            y+rnd.randreal(-mdelta,mdelta),
            maxr,
            clcfitness
        );
    }
    individual()=delete;
    individual(double _x,double _y,auto mxr,auto cf):
        x(_x),y(_y),maxr(mxr),clcfitness(cf){
        r=maxr(x,y);fitness=clcfitness(x,y,r);
    }
    template<const int mpopulation,const double liveprob,const double mdeltachg,const double mnlimrange>
    friend class environment;
};
template<const int mpopulation,const double liveprob,const double mdeltachg,const double mnlimrange>
class environment{
private:
    vector<complex<double>> bld,enemy;
    vector<double> rbld;
    vector<individual> population;
    double lim,limr;
    auto initfuncs(){
        return pair(
            [this](double x,double y){
                auto res=1e18;
                for(auto r=rbld.begin();auto&i:bld) res=min(res,abs(i-complex(x,y))-*r),++r;
                return min(res,limr);
            },
            [this](double x,double y,double r){
                auto res=0;
                for(auto&i:enemy) res+=abs(i-complex(x,y))<r+eps;
                return res;
            }
        );
    }
public:
    auto generate(const int gen){
        ranges::sort(population,[](auto&a,auto&b){
            return a.fitness>b.fitness;
        });
        const auto live=(int)(mpopulation*liveprob);
        vector<individual> ngen(population.begin(),population.begin()+live);
        while(ngen.size()<mpopulation){
            const auto chs=population[rnd.randint(0,mpopulation-1)];
            const auto child=chs.crossover(lim);
            if(child.fitness>chs.fitness){
                ngen.push_back(child);
            }else if(exp((child.fitness-chs.fitness)/gen)>rnd.randreal(0,1)){
                ngen.push_back(child);
            }
        }
        population=ngen;
        lim*=mdeltachg;
    }
    auto best(){
        ranges::sort(population,[](auto&a,auto&b){
            return a.fitness>b.fitness;
        });
        return population[0].fitness;
    }
    environment(vector<complex<double>> bd,vector<double> rbd,vector<complex<double>> emy,double lr):
        bld(bd),rbld(rbd),enemy(emy),limr(lr){
        auto[maxrange,clcfitness]=initfuncs();
        lim=0.01;
        for(auto&i:bd) lim=max({lim,abs(real(i)),abs(imag(i))});
        for(auto&i:emy) lim=max({lim,abs(real(i)),abs(imag(i))});
        cir(i,0,mpopulation){
            population.push_back(
                individual(
                    rnd.randreal(-lim,lim),
                    rnd.randreal(-lim,lim),
                    maxrange,
                    clcfitness
                )
            );
        }
        lim=max(lim,mnlimrange);
    }
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m,r;cin>>n>>m>>r;
    vector<complex<double>> bld(n),emy(m);
    vector<double> rg(n);
    cir(i,0,n){
        double x,y;cin>>x>>y>>rg[i];
        bld[i]=complex<double>(x,y);
    }
    for(double x,y;auto&i:emy) cin>>x>>y,i=complex(x,y);
    environment<350,0.05,0.80,5.0e4> env(bld,rg,emy,r);
    const auto gencount=50;
    cir(i,0,gencount) env.generate(i+1);
    cout<<env.best()<<'\n';
    return 0;
}
