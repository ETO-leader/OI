#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define pb push_back
auto chkmin(auto &a, auto b)
{
    a = min(a, b);
}

// const int MAXN = 5e6;
// int n, m, hd[MAXN + 5], to[MAXN + 5], nxt[MAXN + 5], val[MAXN + 5], ec = 1;
// vector<int> g[MAXN + 5];
// int typ[MAXN + 5];
// ll res;
// void adde(int u, int v, int w)
// {
//     to[++ec] = v;
//     val[ec] = w;
//     nxt[ec] = hd[u];
//     hd[u] = ec;
//     to[++ec] = u;
//     val[ec] = w;
//     nxt[ec] = hd[v];
//     hd[v] = ec;
// }
// int dfn[MAXN + 5], low[MAXN + 5], tim = 0, stk[MAXN + 5], tp = 0;
// int e_stk[MAXN + 5], e_top, ncnt, in[MAXN + 5];
// void tarjan(int x)
// {
//     dfn[x] = low[x] = ++tim;
//     stk[++tp] = x;
//     for (int e = hd[x]; e; e = nxt[e])
//     {
//         int y = to[e];
//         if (!dfn[y])
//         {
//             e_stk[++e_top] = e >> 1;
//             in[e >> 1] = 1;
//             tarjan(y);
//             chkmin(low[x], low[y]);
//             if (low[y] >= dfn[x])
//             {
//                 vector<int> V, E;
//                 int o;
//                 ++ncnt;
//                 do
//                 {
//                     o = stk[tp--];
//                     V.pb(o);
//                 } while (o ^ y);
//                 V.pb(x);
//                 do
//                 {
//                     o = e_stk[e_top--];
//                     in[o] = 0;
//                     E.pb(o);
//                 } while (o ^ (e >> 1));
//                 static int msk[MAXN + 5];
//                 for (int z : V)
//                     g[ncnt].pb(z), g[z].pb(ncnt), msk[z] = 0;
//                 int totmsk = 0, sum = 0;
//                 for (int z : E)
//                 {
//                     totmsk |= (1 << val[z << 1]);
//                     msk[to[z << 1]] |= (1 << val[z << 1]);
//                     msk[to[z << 1 | 1]] |= (1 << val[z << 1]);
//                 }
//                 typ[ncnt] = totmsk - 1;
//                 for (int z : V)
//                     sum += (msk[z] == 3);
//                 if (sum == 2)
//                     res--;
//             }
//         }
//         else
//         {
//             chkmin(low[x], dfn[y]);
//             if (dfn[y] < dfn[x] && !in[e >> 1])
//                 e_stk[++e_top] = e >> 1;
//         }
//     }
// }
// int f[MAXN + 5], siz[MAXN + 5];
// int find(int x) { return (!f[x]) ? x : f[x] = find(f[x]); }
// void merge(int x, int y)
// {
//     x = find(x);
//     y = find(y);
//     f[x] = y;
//     siz[y] += siz[x];
// }
// int main()
// {
//     scanf("%*d%d%d", &n, &m);
//     res = 1ll * n * (n - 1) / 2;
//     for (int i = 1, u, v; i <= m; i++)
//     {
//         static char buf[6];
//         scanf("%d%d%s", &u, &v, buf + 1);
//         adde(u, v, buf[1] == 'D');
//         adde(v, u, buf[1] == 'D');
//     }
//     ncnt = n;
//     tarjan(1);
//     for (int i = 1; i <= n; i++)
//         siz[i] = 1;
//     for (int i = n + 1; i <= ncnt; i++)
//         if (typ[i] == 0)
//             for (int y : g[i])
//                 merge(i, y);
//     for (int i = 1; i <= ncnt; i++)
//         if (find(i) == i)
//             res -= 1ll * siz[i] * (siz[i] - 1) / 2;
//     memset(f, 0, sizeof(f));
//     memset(siz, 0, sizeof(siz));
//     for (int i = 1; i <= n; i++)
//         siz[i] = 1;
//     for (int i = n + 1; i <= ncnt; i++)
//         if (typ[i] == 1)
//             for (int y : g[i])
//                 merge(i, y);
//     for (int i = 1; i <= ncnt; i++)
//         if (find(i) == i)
//             res -= 1ll * siz[i] * (siz[i] - 1) / 2;
//     printf("%lld\n", res);
//     return 0;
// }

#define  	  BB9/**/scanf("%d%d%s", /**/		&u,/**/		/**/&v,/**/	buf	/**//**//**//**/ 		 				+	/**//**/  /**/     /**/	/**//**/  	/**//**//**/  /**/ 	 1);
#define   		BB8/**/adde(u,	v, /**/	/**/buf[1]/**/== 		/**//**//**/'D');
#define/**//**/	 /**/	 BB7	 	  adde(v,			u,   buf[1]	      == /**/    		'D');
#define/**/ 	/**//**/	BB6		 /**/	scanf("%*d%d%d", /**/		  /**/	/**/ &n, /**/ 		  	 	 	&m);
#define 		/**//**//**/ /**/ BB5/**//**/	   printf("%lld\n",/**/ /**/  		/**/ /**/ 	/**/res);
#define /**/	/**//**//**/BB4/**/	/**/	e_stk[e_top--];
#define  BB3 chkmin(low[x],
#define/**/BB2		/**//**/g[ncnt].pb(z),
#define /**/BB1 /**/	/**//**/e_stk[++e_top]
#define  	  /**//**//**/  		BB0 		g[z].pb(ncnt),
#define 	BAF			sizeof(siz));
#define /**/BAE /**/ /**//**//**/find(f[x]);
#define/**//**/ 	BAD	memset(siz,
#define BAC 	vector<int>
#define/**/ BAB/**/   /**//**//**/	sizeof(f));
#define BAA   e_stk[MAXN
#define/**/ /**/	/**/BA9	 tarjan(y);
#define  /**/	 	/**/   BA8	/**/ tarjan(int
#define	 /**//**//**/ /**/ 				 				/**/ 	BA7	 		/**/ tarjan(1);
#define BA6	stk[tp--];
#define	 BA5/**/		  (!dfn[y])
#define /**/BA4	/**/ /**//**//**/ /**//**/memset(f,
#define/**/BA3						typ[ncnt]
#define	/**/ BA2	stk[++tp]
#define   /**/BA1/**/	 merge(int
#define/**//**//**/BA0 		/**//**/ msk[MAXN
#define  B9F /**//**/msk[to[z
#define	/**/B9E  /**/	nxt[MAXN
#define	B9D 	  dfn[MAXN
#define/**/B9C/**//**/ (find(i)
#define	/**/	  			/**/ /**/ 	 		B9B	siz[MAXN
#define /**/  	/**/B9A  /**//**/stk[MAXN
#define /**/B99 to[++ec]
#define 				  /**//**/		/**/B98	 /**//**/typ[MAXN
#define/**/	/**/	B97/**/	 	 /**/merge(i,
#define B96	 val[MAXN
#define/**/	B95/**//**/	find(int
#define	/**/  		 B94		/**//**/ /**/low[MAXN
#define/**/	B93 find(x);
#define	/**/  	/**/B92  	 		/**/E.pb(o);
#define/**/	  	 	/**//**/ 	B91/**/ 	 find(y);
#define 	/**/	/**/B90/**/		  	dfn[y]);
#define/**/B8F	V.pb(o);
#define/**/B8E	V.pb(x);
#define		B8D	 /**//**/ 	   adde(int
#define   /**/ /**/B8C/**/	low[y]);
#define B8B/**/(!f[x])
#define B8A	/**/siz[x];
#define	/**/ /**/B89	 	(dfn[y]
#define /**/	B88/**/	/**/hd[MAXN
#define	/**/B87	/**/(low[y]
#define	/**/	/**/ 	 	/**/B86/**/(msk[z]
#define	 	 B85/**/ buf[6];
#define/**//**//**/	/**/		  B84/**/		 (siz[i]
#define/**/	 /**/	/**/		 B83 (typ[i]
#define	B82/**/nxt[ec]
#define   /**/ 			  B81 ++ncnt;
#define B80   val[ec]
#define B7F/**/ 				nxt[e])
#define /**/B7E /**/ /**//**/ /**/ 	 /**//**//**/to[MAXN
#define	/**/B7D  	/**/	/**/		  /**//**/	 dfn[x])
#define/**/      /**/	/**//**//**/ /**/	/**//**/B7C   		in[MAXN
#define  B7B		/**/	 	/**//**/	msk[z]
#define/**//**/   /**/ 	/**/		/**//**//**/ /**/B7A/**//**//**/	/**/g[MAXN
#define/**/ /**/	/**/B79	  /**/   /**/  /**/		/**//**/ dfn[x]
#define/**/	/**/  /**/ /**//**/B78 	 	 	res--;
#define/**/	/**/  /**/ /**/	B77	/**//**//**/		 /**/	/**//**/	/**/++tim;
#define	B76 /**//**/return
#define	B75		hd[v];
#define	/**/	/**//**/	  B74  hd[x];
#define 	/**/   	 B73		siz[i]
#define	 	/**//**/ 	/**/B72	  siz[y]
#define	/**/ 	B71/**//**//**/	/**/	/**//**/ /**/	f[MAXN
#define B70/**//**/e_top,
#define  		/**/ /**//**/ /**/ 	B6F 	/**//**//**/ static
#define/**/B6E/**/	 	low[x]
#define/**/	/**//**/  			/**/ 	/**//**/	B6D /**/  /**/ 	/**/	/**/	main()
#define		/**/ /**/	  /**/B6C	hd[u];
#define B6B /**/ /**/to[e];
#define/**//**/ 	/**/	/**/	 		/**/		B6A/**/ 			 	 	/**/totmsk
#define						 /**/ /**//**//**/ /**/ 	/**/	/**//**/ 	B69/**/  const
#define /**/ 	/**/  /**//**/	/**/		   B68/**//**/ /**/ 		/**/ /**/	hd[v]
#define B67   	/**/in[o]
#define		/**//**/B66 g[i])
#define  B65 /**/	hd[u]
#define		B64	 /**/	 ncnt;
#define/**/  		/**/B63	 /**//**/	  /**/ !in[e
#define /**/B62  /**//**/	/**//**/ncnt,
#define /**//**/ /**/ B61/**/val[z
#define B60/**/ while
#define 	  	/**/   /**//**/	/**//**//**//**/ 	B5F	/**/	(int
#define /**//**/  		/**/B5E	in[e
#define						 /**//**/	/**/B5D  /**/ 	(sum
#define B5C  /**/	 /**//**/1));
#define		B5B 	  	 /**//**//**/i++)
#define B5A/**//**//**//**/1]);
#define 		/**//**/	 	 	/**//**/B59	char
#define  		 	 /**//**/ B58/**/ 	/**//**/ 5e6;
#define		/**//**/	/**/ B57/**//**//**/f[x]
#define /**/	B56/**/ncnt
#define /**//**/		    	B55/**/		/**/ 	res;
#define	 /**/ B54		 /**/	 else
#define    /**/	/**/B53		  MAXN
#define/**//**/  /**/ 	/**/B52	   void
#define	 /**//**/ /**/			  B51/**/  	 /**/1]]
#define/**/B50 /**/1ll
#define /**/  /**/		 /**//**//**/ /**/ B4F	 res
#define	/**/B4E /**/  	  	/**/5];
#define	/**/ B4D 	 /**/ 5],
#define/**/   	/**/			 B4C/**/  sum
#define B4B/**/		 			int
#define/**/		B4A /**/		/**/  	   /**/	  /**//**//**/	for
#define	B49 			 3);
#define	  /**/ 	B48/**/ 	ec;
#define 	  B47  1])
#define	 		B46/**/		tim
#define	 	/**//**/ /**/	 B45 	y);
#define	  	 B44 o;
#define		 	 B43  /**/ 		  <<
#define B42  ==
#define		/**/  	     /**/		 	B41	>=
#define/**/ 		B40						/**//**/		  /**//**/  >>
#define/**/	 B3F E)
#define	 	/**/B3E	E;
#define  /**/			B3D/**//**/ /**//**/ V)
#define/**//**/ 	/**/	B3C /**/V,
#define	  B3B/**/ 	/**/	do
#define 	/**/ B3A	 	e;
#define	B39 ec
#define	/**/	/**/	B38  	/**/<=
#define	/**//**//**/ B37	i)
#define  B36/**/  if
#define	B35	   /**/		 /**/	/**//**//**/ll
#define		/**//**/	B34 	  /**/ 	/**/&&
#define B33 (1
#define	 		/**/	B32/**/ /**//**/	/**/m,
#define 	/**/ /**//**//**/B31/**/	m;
#define  	 /**/		B30/**//**//**/	 	/**/	/**//**/(e
#define		/**/B2F/**//**//**/ (n
#define		B2E /**//**/(o
#define	 	/**//**//**/B2D /**/ 	+=
#define/**//**/ 	B2C/**/-=
#define/**/	 	  	B2B /**/0)
#define  B2A	/**//**/0,
#define 	B29  	/**/ tp
#define B28    	  /**/	 /**/  /**/ 0;
#define/**/	 /**//**/B27		/**//**/	n,
#define	B26	 /**/  /**/	 	u,
#define/**/B25 u;
#define	B24 	/**/v,
#define  /**/B23/**/v;
#define	  /**/		B22/**//**/		/**/n;
#define	 /**//**/   		/**//**/				/**/	 		/**/			B21 1)
#define   /**//**//**/ B20 1,
#define	/**/B1F	/**/   	 1;
#define 	/**//**/  /**//**/	 	/**/B1E /**/	 	/**//**/1]
#define/**/	 /**//**//**/B1D  w)
#define	/**/	/**//**//**//**/			 		 	/**/  			 /**/   /**//**/ B1C		 w;
#define	 /**/  B1B/**/	 /**/ /**/ 	/**//**/ /**/ 2)
#define				/**/		/**/  B1A  	x)
#define	 /**/B19 /**/     /**/	  /**/x,
#define/**//**/B18/**//**//**/		   		 /**//**/   /**/		/**/x;
#define/**/	 /**/   /**//**/ B17	/**/	/**/ /**/ y)
#define	 B16/**//**/2;
#define	/**//**/	B15/**//**/y;
#define   	  B14	/**/	 |=
#define 	/**/B13 i
#define /**/	B12		  			/**/  	e
#define/**/	/**/	/**/ /**/   B11 			/**/<
#define/**/ 	/**/	 B10/**/	/**//**//**/ 	^
#define 	/**/	/**/   /**/BF /**//**//**/	/**/  /**/ 		 /**/:
#define   BE 1
#define  BD 		o
#define		BC/**/x
#define	/**/BB	/**/	/**/	/**/	 	/**/ -
#define 	/**/ 	/**//**/ /**//**//**//**/BA	/**/	/**/	/**//**//**//**/	/**/+
#define/**/	 B9	/**//**/?
#define	/**/ /**//**//**/B8/**/	 y
#define		/**//**/ 			/**/		/**/B7 *
#define/**/B6  /**/ 	n
#define B5/**/  =
#define 	  B4/**/	 /**//**//**/  /**/  	z
#define	B3 {
#define/**//**/		 /**/  /**/B2/**//**/|
#define/**/B1 		/
#define /**/B0			/**/ 	/**//**/}
#define			/**/ BBA	B69	B4B	/**/ /**/ B53 /**//**/	/**/ 					 	  	 B5		B58 /**/	 	/**//**/	/**/B4B/**/	B27 		/**/ 			/**/ 	  B32	B88	BA
#define/**//**/BBB /**/	B4D B7E  BA/**/	/**/	 B4D  B9E		 /**/   BA	 B4D/**/ B96/**/	/**/ 	BA	 	 B4D
#define			 BBC/**/B39  /**//**/	    /**/	/**/ 	 	  	B5 B1F			 /**/BAC	B7A BA		 B4E/**/ B4B 	/**//**/	/**/	/**//**/B98/**//**/ 	/**/BA
#define /**/ BBD	B4E  		 	B35	/**/				/**//**/B55/**/B52  B8D	B26 B4B	 /**/ 	 	 B24  /**/  B4B B1D
#define /**//**/ 	BBE/**//**//**//**/B3/**/ 	  	B99 /**/ B5 B23	B80		B5/**//**/	 B1C/**/  /**//**/B82/**/  /**/				B5 B6C
#define  BBF  /**//**//**/			B65  B5 B48/**//**/	/**/B99   	B5 /**/B25	/**/ /**/	/**/	/**/B80	  B5/**/	B1C  /**/	/**//**//**//**/		B82
#define 	BC0 /**//**/B5 B75	/**/	 		B68/**/	/**/B5/**/B48/**/  B0	/**/		B4B B9D BA/**//**/B4D
#define	/**/	/**//**/  /**/BC1	B94    	/**/ 	  BA	/**/ B4D/**/ B46 	 B5	  /**/	B2A 	B9A  BA		/**/		 /**/ 	B4D	B29
#define/**//**/BC2							 	B5	 /**/	/**/B28	/**//**/B4B				 		BAA  	 	 BA	B4D		B70	B62 /**/  		B7C/**//**//**/			 BA
#define/**/ /**/		BC3 	 /**//**/ B4E	/**//**/		/**/  /**/		/**/		B52 BA8 		B1A	B3/**//**/ 				/**/B79   /**/		/**//**/	 B5/**//**//**/			 	B6E /**/	B5		/**/  		/**//**//**//**/ /**/B77
#define/**/	 BC4/**/ 	BA2					B5  	/**/ B18 /**/B4A/**//**/	 	B5F B12	 	/**//**/B5 B74/**/B3A		/**/ /**/B12
#define/**/ BC5/**/B5/**/		/**/B7F/**/ /**//**/B3/**/  	/**/B4B			 B8 	/**/			/**/ B5/**/ 	B6B/**/	 	  B36/**//**/	 	/**/ 	/**//**/	  /**/	  		 		BA5/**/	  /**/  	B3
#define BC6/**/ 	/**/	/**/ BB1	 	/**/B5 /**/		B12	 /**/				/**/ /**//**/B40	B1F/**//**/  /**//**/B5E		B40 	/**/   B1E	B5	   /**//**/  B1F
#define	 /**//**/ /**/		BC7  /**/ /**/ /**/ /**//**//**/BA9		BB3  /**/B8C	 	 	 B36 	B87/**/	/**/ 	/**/ B41  	 /**/			B7D B3/**/	/**/	 /**//**/ BAC/**/B3C
#define /**/	/**/	/**/ BC8	B3E /**/		  		/**/		 /**//**//**/    B4B	/**/ 	B44		/**/	 /**//**/ B81/**/ 			/**//**/B3B/**/  B3 /**/BD	 	B5/**/	/**/	/**//**/ 	/**/	BA6 B8F
#define/**//**//**/	 /**/  BC9	 	/**/	/**/B0	 /**/ 	/**//**//**//**//**/ 	   /**/B60 	 /**/ /**/B2E	/**/     /**/		/**//**/	  /**//**/	/**//**/B10	B45	 	/**/ B8E B3B  	B3/**/	/**/ /**/	/**/ BD/**/	B5
#define/**/	/**//**/	BCA   /**/	 BB4/**//**/	B67/**//**/	 		 B5	    /**/B28	B92/**/ 	B0/**//**/	 B60/**//**//**//**/ 	B2E  /**/B10	/**//**/B30
#define/**/BCB 	/**/ B40	 	B5C/**/B6F/**/ B4B /**/	/**//**/		/**/BA0	 BA 		/**//**//**/	B4E	 /**//**//**/B4A /**/B5F /**//**/ /**//**//**//**//**/ 	 /**/ 	/**//**/	/**/ 	/**/	B4
#define  	BCC	BF /**/ B3D	BB2/**/			/**/	 BB0 /**//**/	B7B/**/ B5 /**//**//**/B28   /**/ /**//**/	/**/ 	    	/**//**/ B4B	/**//**/	/**/ 	B6A 	B5
#define/**/		BCD  		B2A 	B4C	B5  B28	  /**/B4A	/**/ /**/   B5F/**/B4	/**/	/**/BF 	/**//**//**/ 		 		/**/B3F  B3
#define/**/ 	BCE	/**//**/B6A /**/B14 /**//**/ 	B33 /**/	/**//**/	/**/B43  	  B61/**/	/**/	/**//**/B43	  /**/B5A/**/ 	/**/	B9F /**//**/	 	 B43		/**//**//**//**/	/**/B51
#define /**/BCF  B14 /**/  	 /**/ 	B33	B43/**//**/B61  	B43/**/			 /**//**/  B5A	/**/		B9F/**/ /**/ B43 /**//**/ BE	/**/ /**/	/**//**//**/	B2
#define 	/**//**/ /**/  /**/ 	BD0/**/B51  /**/B14  	B33/**/  	 B43/**/	B61/**//**/ 	/**/ 	B43			/**/B5A/**/			/**//**/ B0/**//**/	 /**/ /**/	/**/BA3	B5
#define		/**/	BD1 /**//**/		B6A	BB /**/  /**//**/B1F	/**/	 /**//**/  /**/	B4A		/**/ B5F/**//**/B4/**/ BF	 B3D 	/**/		/**//**/ 	 B4C/**/ /**/  	/**/B2D
#define BD2	/**//**//**/ 		/**/	/**/B86/**/B42/**/	B49  	/**/ 	B36 B5D/**//**//**//**//**/B42	 	B1B		/**/ B78 	/**/B0 B0
#define		/**//**/   BD3/**//**/B54	/**/   /**/ B3 /**/BB3/**/B90	/**/			B36/**/ /**/			B89   /**//**/				/**/B11 /**/	/**/ B79	B34		 	 B63
#define	 /**/  /**/ /**/	 			/**/  		/**/BD4 B40		B47 BB1		B5	 /**/ /**//**//**/	B12	/**//**/  B40 /**/	/**/ /**/B1F /**/ 		B0/**/			  			 B0/**/B0
#define/**//**/ /**//**//**/BD5/**//**/	  B4B 	B71			   /**/BA/**/B4D	/**/B9B	 	BA/**/	B4E/**/ 	B4B B95 	 /**/  		  B1A
#define/**//**/BD6/**/B3  B76	/**//**/B8B 	/**/ 	 /**/ /**/		/**//**/ /**//**//**/B9  	 	/**/ /**/		 	/**/	  	 /**/ BC  /**/BF	 /**//**/ /**/ /**//**//**/		/**//**//**/ 	 B57/**//**/	B5	BAE B0
#define	BD7		 /**/  /**/			B52/**/		/**/BA1		  	B19 			  /**//**/  /**/ 		   	/**/B4B B17 /**//**/ 	B3/**//**/  BC /**/   /**//**/ 	/**/	/**//**//**/ B5 B93/**//**/B8
#define	 /**/	BD8		/**/   /**/	  /**/B5 /**/ 				B91 /**//**//**//**/B57	/**/B5  	 		 	/**//**/ /**/B15/**/ 	 	/**/ B72	/**/   /**/	B2D B8A	B0	 	/**/B4B
#define		BD9	/**/ /**/   B6D/**/	 /**/ /**/ /**//**/B3/**/	/**/	BB6	/**/B4F/**/B5	 B50 		 /**//**/	/**/B7	 B6 	/**/	/**/ B7/**//**/	B2F
#define		BDA	/**/	/**/  	BB /**/	B21/**/B1	/**/B16	B4A	B5F			/**/	B13 /**/	 B5/**/B20 B26
#define		BDB	/**/ 	  B23 		 	  /**//**/ /**/B13 /**/	  		 	B38/**/		B31	 /**/	/**/ B5B   /**//**//**/	/**/B3/**/	 	B6F B59/**/	 B85	  /**/ /**/BB9
#define/**//**/BDC	BB8	/**//**//**/ /**//**/	/**/					 			/**//**//**/		 /**/		 BB7		 /**/	 /**/ 	B0 B56/**/  	/**/ 	/**/	B5	B22 			 /**/ BA7	/**/ B4A/**/	 		B5F/**/	  	/**/  B13
#define/**//**/BDD B5 	 	 B1F /**//**/ /**/		 /**/  	B13/**/ /**/  		/**/ 		/**/B38/**//**/   /**/		B22	B5B	B73		 /**/B5	/**/		/**//**/	/**/	B1F/**//**/ /**/	  	 B4A
#define	 /**/	 /**/BDE	B5F				 	/**/	B13		B5 	B6	/**/ 		 /**/BA /**/ 	B1F		   			B13	B38    	/**/	/**/ B64 /**/  B5B
#define  /**/ /**/		 	/**/  BDF/**/  	/**/	/**/ 		/**//**/	/**/ /**/	B36/**/ B83  	/**/  	 B42		  B2B B4A/**//**//**/B5F	/**/	B8  BF 	 B66	B97
#define  BE0 /**/	  B45 /**/B4A 					 /**//**/  B5F/**/B13	/**//**/B5		/**/		    /**//**//**/		   		 /**/		B1F	B13 	B38	/**/	/**/	B64/**//**/	/**/ /**/B5B
#define/**/ /**/  		BE1 /**/	B36				/**/			B9C/**/ 		 /**/   B42 			 /**/	/**/		/**/ B37/**/  	 /**/ B4F	B2C 	 /**/	 B50 /**/	B7	/**/ /**//**/	B73  			/**/B7
#define/**/ 	/**//**/							 /**/	 /**/BE2 		  B84		/**//**/	/**//**/BB	B21  			 	  /**/			/**//**//**/ 	  B1 B16/**//**/		BA4/**/	 	B2A	/**/	 	 /**//**/	 	 		  /**/	BAB	  BAD /**/ /**//**/B2A
#define/**/BE3/**/	BAF/**/B4A	 B5F 	 /**/ /**/ /**/ 	/**//**/	/**//**/ B13			 B5	/**/		 			B1F			B13	/**/B38  			 /**/  /**/ B22		B5B
#define  	   	BE4	 B73/**/B5	/**/ /**/			B1F		    	/**/B4A 	   B5F	B13	B5	/**//**//**/ 	 B6/**/		 BA /**/B1F
#define	  		/**//**//**/	BE5	 /**/	B13/**/	/**//**/	/**//**/	B38	B64/**/ B5B/**/ /**/ /**//**//**/	 /**/	/**/B36/**/B83 /**//**//**/		B42/**/	 /**/	/**/	/**/	/**/  		 	/**/ /**/B21 		/**/ /**/	 /**//**/B4A	B5F
#define			 /**/BE6  	  B8/**//**/  	 /**/BF	B66/**//**/B97 B45   B4A/**/B5F/**/B13	B5	B1F
#define	 		 /**/BE7		B13/**//**//**/	/**//**/  /**/B38		/**/	 /**/   B64/**/B5B		 B36 /**//**/B9C		/**/ 	/**//**/B42 B37		B4F /**//**/B2C
#define	  /**//**//**//**/BE8/**/ B50/**//**/ B7  B73 	B7 B84/**/	 	/**/  BB /**/B21	/**/	 	 	 /**/    B1/**//**/	 /**/	/**//**/ B16	/**//**/ /**/	BB5
#define 	BE9	B76 /**/B28  B0/**//**/		 
#define/**/ 				/**/	/**/ /**/ 	BEA	BBA /**//**/ BBB/**/BBC/**/			/**/   /**/BBD/**/		BBE/**/			 	BBF  /**//**/BC0/**/	/**//**/		/**/		/**/BC1 /**/BC2  	BC3
#define	 	  BEB/**//**/  /**/ /**/	 BC4	/**//**/  /**/BC5/**/ 	  /**/ /**/BC6/**//**/ 		BC7	 BC8  /**/		 BC9     	/**//**/BCA			BCB/**//**//**/	 /**/BCC			BCD
#define	  /**/			/**/	/**/ BEC	  /**/ /**/	/**/BCE /**/	 /**//**//**/ 	  	/**/BCF	BD0/**/ /**/BD1/**/BD2 /**/		BD3/**/ 	/**/ /**/ 	 		 /**/BD4	 BD5 BD6	 		/**/BD7
#define BED /**/ BD8/**//**/BD9/**/BDA	/**/ /**/ 		 	/**/ 	  /**/	 	 BDB		/**/ /**/	 /**/   BDC	BDD/**/ BDE /**//**/ BDF	/**/	 	/**/	 BE0/**/	 /**/ 	  BE1
#define	/**/	     /**/BEE/**/BE2/**/ 	  BE3		/**/ BE4		 		BE5 	 		/**/ BE6  /**/BE7  BE8/**//**/  /**/	BE9/**/ 
#define			BEF			 		/**/BEA/**/		BEB/**/BEC /**/	BED/**/ /**/ /**/	/**//**/	/**//**/BEE/**/	/**/
#define		BF0(__FOX__) /**/__FOX__
BF0(BEF)
