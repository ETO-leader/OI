namespace IO{
	char ibuf[(1<<20)+1],*iS,*iT;
	#if ONLINE_JUDGE
	#define gh() (iS==iT?iT=(iS=ibuf)+fread(ibuf,1,(1<<20)+1,stdin),(iS==iT?EOF:*iS++):*iS++)
 	#else
	#define gh() getchar()
	#endif
	inline long long read(){
		char ch=gh();
		long long x=0;
		bool t=0;
		while(ch<'0'||ch>'9')   t|=ch=='-',ch=gh();
		while(ch>='0'&&ch<='9') x=x*10+(ch^48),ch=gh();
		return t?-x:x;
	}
}
using IO::read;
