这个问题中，我们需要先构造点D，使得三角形BCD的周长为1919810。

设$\overrightarrow{BC}=a$，$\overrightarrow{CA}=b$，$\overrightarrow{AB}=c$，则三角形ABC的面积为：

$$ S_{ABC}=\frac{1}{2}|\overrightarrow{AB}\times\overrightarrow{AC}|=\frac{1}{2}|c\times b| $$

我们可以用向量叉积的方法求出$\overrightarrow{AB}\times\overrightarrow{AC}$的模长，从而得到$c\times b$的模长：

$$ |c\times b|=2S_{ABC}=229028 $$

因为$c\times b$的方向垂直于平面ABC，所以我们可以用$c\times b$来确定一个与平面ABC垂直的向量，即：

$$ n=c\times b $$

接下来，我们需要找到一个点D，使得$\overrightarrow{CD}=k\cdot n$，其中$k$为常数。这样，我们就可以通过向量加减法来计算出$\overrightarrow{BD}$和$\overrightarrow{BC}$，从而得到三角形BCD的周长。

为了使$\overrightarrow{CD}$与平面ABC垂直，我们可以将$\overrightarrow{CD}$表示为：

$$ \overrightarrow{CD}=\lambda\cdot a+\mu\cdot b $$

其中$\lambda$和$\mu$为常数。因为$\overrightarrow{CD}$与平面ABC垂直，所以：

$$ \overrightarrow{CD}\cdot n=0 $$

代入$\overrightarrow{CD}$的表达式中，得到：

$$ (\lambda\cdot a+\mu\cdot b)\cdot (c\times b)=0 $$

展开后可以得到：

$$ \lambda(c\cdot b)^2+\mu(b\cdot b)(c\cdot a)=0 $$

这是一个一元二次方程，解得：

$$ \lambda=\frac{b\cdot b}{c\cdot b}\cdot\frac{-c\cdot a}{b\cdot b-c\cdot b} $$

$$ \mu=\frac{c\cdot b}{b\cdot b}\cdot\frac{-c\cdot a}{b\cdot b-c\cdot b} $$

因为$\overrightarrow{CD}=k\cdot n$，所以$k=\frac{|\overrightarrow{CD}|}{|n|}$。代入$\overrightarrow{CD}$的表达式中，得到：

$$ k=\frac{\sqrt{\lambda^2|a|^2+\mu^2|b|^2}}{|n|}=\frac{\sqrt{(c\cdot a)^2}}{|c\times b|}=10 $$

因此，$\overrightarrow{CD}=10n$，所以：

$$ \overrightarrow{BD}=\overrightarrow{BC}+\overrightarrow{CD}=a+(10n)=a+10c\times b $$

$$ |\overrightarrow{BD}|=\sqrt{|a|^2+20(a\cdot c\times b)+100|c\times b|^2} $$

因为$a\cdot c\times b=|\overrightarrow{AB}\times\overrightarrow{BC}|=2S_{ABC}=229028$，$|c\times b|=229028/2=114514$，所以：

$$ |\overrightarrow{BD}|=\sqrt{|a|^2+2290280+11451400}=1919810 $$

因此，三角形BCD的周长为1919810，证毕