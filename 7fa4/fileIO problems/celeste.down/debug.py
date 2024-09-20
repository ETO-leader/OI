import sys
import matplotlib.pyplot as pl
pl.figure(figsize=(10.0,10.0),dpi=400)
pl.xlim(9000,14000)
pl.ylim(-6000000,500)
t = 0
m = int(input())
for i in range(m):
	X = []; Y = []
	a, b, x, y = list(map(float, input().split(' ')))
	y = -y; b = -b
	X = [ a, x, x, a, a ]
	Y = [ b, b, y, y, b ]
	pl.plot(X, Y)

x, y = list(map(float, input().split(' ')))
X = []; Y = []
X.append(0); Y.append(0)
X[t], Y[t] = x, -y
T = int(input())
for i in range(T):
	x, y = list(map(float, input().split(' ')))
	t = t + 1
	X.append(0)
	Y.append(0)
	X[t], Y[t] = x, -y
pl.plot(X, Y)
pl.savefig(sys.argv[1]+'.png')
