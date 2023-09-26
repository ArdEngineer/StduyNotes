# NOJ作业第11到20题易错点总结以及经验分享

## NOJ Question 11 (输出数字矩阵)
关键点：找到row和column输出数字之间的关系

设矩阵中某一位置为(row, column) = (i, j)

i<j => print j-i; i = j => print 0; i > j => print i - j

通过循环实现即可

## NOJ Question 12 (快速幂模算法的实现)
关于取模运算的性质：

(a + b) mod m = ((a mod m) + (b mod m)) mod m;

(a * b) mod m = ((a mod m) * (b mod m)) mod m;

(a ^ b) mod m = ((a mod m) ^ b) mod m;

基于该性质设计算法，应该考虑到a^b的越界的可能性比较大，所以可以采用

分治的思想解决问题，同时考虑将数据类型设置为unsigned long long(uint32).

``` C++
//quickPowerMod algorithm
typedef unsigned long long uint64;

uint64 fastPowerMod(uint64 a,uint64 b,uint64 m){
    uint64 ans = 1;
    while(b) {
        if((b % 2) == 1){
            ans = (1LL * ans * a) % m;
        }
        a = (1LL * a * a) % m;
        b /= 2;
    }
    return ans;
}
```

另一个同学的做法
``` C++
typedef unsigned long long uint64;

uint64 fastPowerMod (uint64 t, uint64 e, uint64 m){
    uint64 r = 1;
    while (e){
        if (e&1){
            r = (1LL*r*t)%m;
        }
        t = (1LL*t*t)%m;
        e >>= 1;
    }
    return r;
}
```

两份代码从本质上看没区别，区别在于第二位同学采用位运算，速度更快，

不妨分析一下：第一份代码时间复杂度为O(4n)，第二份为O(2n)，尽管同阶，但是第二份代码会快一些？？？（doge）

## NOJ Question 13 (将小数转换成比率输出)
涉及到的知识点：求最大公约数算法，判断是否为整数的函数floor()

上代码！

``` C++
//辗转相除法求两数的最大公约数
int gcd(int a,int b){
    if (b == 0) return a;
    else return gcd(b, a % b);
}
```

``` C++
/*程序求解主体部分*/
int main(){
    double usrnum = 0.0f;            //用户输入的数字
    scanf("%lf", &usrnum);

    int downnum = 1;                 //比率表示的分母

    /*分子分母扩大十倍之后再进行约分*/
    while(usrnum != floor(usrnum)){
        usrnum *= 10 ;            
        downnum *=10 ;
    }

    int max_index = gcd((int)usrnum, downnum);
    usrnum /= max_index;
    downnum /= max_index;
    printf("%d/%d", (int)usrnum, downnum);
    return 0;
}
```

## NOJ Question 17 (n项的级数和)

涉及到的知识点：用%g实现浮点数只输出有效数字（既不输出没有意义的0）

算法设计：当数字小于9的时候，加一再除以10得到小数部分，反之则除以100

``` C++
int n = 0;
scanf("%d", &n);

double ans = 0.0f;
for(int i = 1; i <= n; i++){
    double tmp = i < 9 ? (i + (i + 1) / 10.0f) : (i + (i + 1) / 100.0f);
    ans += tmp;
    if(i == n){
        //最后一个加数的末尾不用输出加号
        printf("%g", tmp);
    }
    printf("%g+", tmp);
}

printf("=%g", ans);
```

## NOJ Question 16 (减去各位数之和并统计操作次数)
用取模运算（%）实现取得各位数字的操作，

用（/10）操作实现小数点左移的操作

``` C++
int main(){
    int n = 0;
    scanf("%d", &n);

    int count = 0;
    while (n > 0){             //当被减数小于等于0的时候停止操作
        int asum = 0;          //用来存储每一次运算中的各位数之和
        int tmp = n;           //临时使用的操作数
        while(tmp != 0){
            asum += (tmp % 10);
            tmp = tmp / 10;
        }
        n = n - asum;          //减去各位数之和
        count++;               //每减去一次操作次数加一
    }
    printf("%d", count);
    return 0;
}
```

## NOJ Question 20 (分数的加减乘除输出)
输入的注意点：使用getchar()将输入缓冲区中的/丢弃可取得数字

这道题还涉及到NOJ缓冲区输出的规则

由于NOJ是从输出缓冲区中一次性读取结果的，所以按照下面这样子写没办法过

尽管从分析上还有本地运行的结果都是对的

``` C++
//使用函数将加减乘除封装起来使用
#include <stdio.h>
typedef unsigned long long uint16;

uint16 gcd(uint16 a,uint16 b){
    if (b == 0) return a;
    else return gcd(b,a%b);
}

void f1(uint16 u1, uint16 u2, uint16 d1, uint16 d2){
    uint16 dans = d1 * d2;
    uint16 uans = u1 * d2 + u2 * d1;

    uint16 maxindex = gcd(dans, uans);

    dans = dans / maxindex;
    uans = uans / maxindex;

    printf("(%d/%d)+(%d/%d)=%d/%d\n", u1, d1, u2, d2, uans, dans);
}

...
//中间还有f2,f3,f4函数，就是f1函数里面改一改就行

int main(){
    uint16 u1, u2, d1, d2;
    scanf("%d", &u1);
    getchar();
    scanf("%d", &u2);
    scanf("%d", &d1);
    getchar();
    scanf("%d", &d2);

    f1(u1, u2, d1, d2);
    f2(u1, u2, d1, d2);
    f3(u1, u2, d1, d2);
    f4(u1, u2, d1, d2);

    return 0;
}
```

上面的代码是把加减乘除的结果用不同函数体进行输出

但是把加减乘除放在一个函数的内部，在一个函数的内部进行printf输出提交

到NOJ上是AC的，我猜NOJ测试时只读取了一个函数栈帧输出缓冲区的结果，因

而有可能因此导致WA（真的离谱在这些地方），我写的代码可不背这锅

总之就是在NOJ作业平台上提交的代码尽量不要在其他函数中进行结果输出。。