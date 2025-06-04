#include<bits/stdc++.h>
using namespace std;
long long A,p;
mt19937_64 rnd(time(0));
inline long long inc(long long x){//传入两个 [0,p) 内的数的加法结果，对其取模 
	return x>=p? x-p:x;
}
inline long long dec(long long x){//传入两个 [0,p) 内的数的减法结果，对其取模
	return x<0? x+p:x;
}
unsigned long long mul(long long a,long long b){//传入两个 [0,p) 内的数，计算模意义下乘法  
	unsigned long long c=(unsigned long long)a*b-((unsigned long long)((long double)a/p*b+0.5L))*p;
	return c<p? c:c+p;
}
long long ksm(long long a,long long b){//求幂 
	long long res=1;
	while(b){
		if(b&1)
			res=mul(res,a);
		a=mul(a,a),b>>=1;
	}
	return res;
}
long long inv(long long a){//求逆 
	return ksm(a%p,p-2);
}
struct pr{//表示 x+y lambda 
	long long x,y;
};
pr prmul(long long II,pr a,pr b){//传入两个 pr 计算其乘积，需传入 II 表示 a^2-n 
	return pr{inc(mul(a.x,b.x)+mul(II,mul(a.y,b.y))),inc(mul(a.x,b.y)+mul(a.y,b.x))};
}
long long sqt(long long A){//Cipolla 算法开根 
	assert(ksm(A,(p-1)/2)==1);//需保证 A 是二次剩余 
	long long x=rnd()%p,y=dec(mul(x,x)-A);
	while(ksm(y,(p-1)/2)!=p-1)
		x=rnd()%p,y=dec(mul(x,x)-A);
	pr a=pr{x,1},res=pr{1,0};
	long long b=(p+1)/2;
	while(b){
		if(b&1)
			res=prmul(y,res,a);
		a=prmul(y,a,a),b>>=1;
	}
	return res.x;
}
int main(){
	scanf("%lld%lld",&A,&p);
	printf("%lld\n",sqt(A));
	return 0;
}
