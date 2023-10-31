# 数学字体、字号和空格
## 空格
> $3/18空\,格$
> $4/18空\:格$
> $5/18 空\;格$
> $9/18空\ 格$
> $1个空\quad格$
> $2个空\qquad格$
> $-3/18空\!格$
## 间距
> $\sqrt{A}\quad\sqrt{\smash[t]{A}}$               **\\smash** 公式用来调整围绕子公式的元素大小
## 字号
> $\displaystyle\sum_{i=0}^n a_i$ **\\displaystyle** ⾏间公式尺⼨
> $\textstyle\sum_{i=0}^n a_i$ **\\textstyle** ⾏内公式尺⼨
> $\scriptstyle\sum_{i=0}^n a_i$ **\\scriptstyle** 上下标尺寸
> $\scriptscriptstyle\sum_{i=0}^n a_i$ **\\scriptscriptstyle** 次上下标尺寸

## 数学字体
> $A \qquad \mathrm{A}$  **\\mathrm** 字体转为正体 **\\textrm** 保留空格
> $\boldsymbol{A}$ **\\boldsymbol** 数字粗体
> $\mathbb{A}$ **\\mathbb** 空心粗体

# 基本命令
> $$\sin \cos \tan \cot \arcsin \arccos \arctan \cot \sec \csc $$
> $$\sinh \cosh \tanh \coth \log \lg \ln \ker \exp \dim \arg \deg $$
>$$\lim \limsup \liminf \sup \inf \min \max \det \Pr \gcd \mathrm{可带上下限参数}$$

> $\mathop{max}\limits_{x}$ **\\mathop** 将符号转为数学操作符
> $0\mathbin{-}2$  **\\mathbin** 将普通符号转换为二元运算符
> $a\mathrel{=}b$ **\\mathrel** 将普通符号转为二元关系符

## 上下标与虚位
> $a^3_{ij} \quad a_{ij}{}^3$ 两种方式显示不一样
> ${}^{12}_{6}\mathrm{C}$  ${}^{12}_{\phantom{1} 6}\mathrm{C}$ **\\phantom** 虚位命令
> $\prescript{12}{6}{\mathrm{C}}$ **\\prescript** 可以自动调整
## 微分与积分
> $y'=x$  '导数
> $\dot{y}(t)=t\quad\ddot{y}(t)=t$ 用点号表示的导数
> $\iint_{D}f(x)=0$ 二重积分
> $\int_{0}^{1}f(x)=1$ 积分
> $\frac{\partial f}{\partial x}$ 偏导数
> $\oint$  环形积分

## 分式、根式与堆叠
> $\frac{x}{y}+\dfrac{x}{y}+\tfrac{x}{y}$ **\\dfrac** 行间公式大小 **\\tfrac**行内公式大小
> $\cfrac{1}{1+\cfrac{2}{1+x}}$ **\\cfrac** 连分式
> $\sqrt{A}\quad\surd$ **\\sqrt** 根式  **\\surd** 空根式














