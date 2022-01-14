#include<stdio.h>


//位或的应用
//位或，任何数和1进行位或都得到1,任何数和0进行位或都得任何数不变
/*int main()
{
//1.将第5位置为1，
//设计标记位
int x;
scanf("%d",&x);
x|=(0b10000);
printf("%d",x);
    return 0;
}*/



/*int main()
{
    //设置空标记位，如将第5位制空0,
    //因为1和任何数或都是1,0和任何数或后都不变
    //先和10000或，将第5位变成1,再-10000,这样无论他是0还是1都可以变成0
    //不能直接减，要保证第5位是1才可以
    int x=0b0100010;
    printf("%d",x|(0b10000)-0b10000);

    return 0;
}*/


/*int main()
{
    //如果一个数的二进制有且只有一个1,低位三连续的0,我们要将其中的0全部变成1
    int c=0b1000;
    printf("%d",c|(c-1));
    return 0;
}*/

int bestodd(int x)//find the best operation if x is odd
{
    //x is odd
    int m=x+1;
    int n=x-1;
    int c=x+1;
int d=x-1;
int cnt=0;
int dnt=0;
while(c)
{
    if(c%2==0)
    {
        cnt++;
    }
    cnt>>=1;
}
while(d)
{
    if(d%2==0)
    {
        dnt++;
    }
    dnt>>=1;
}
return cnt>dnt?m:n;
}



int integerReplacement(int n){
int cnt=0;
while(n!=1)
{
    if(n&1==0)//n is even
    {
        n/=2;
        cnt++;
    }
    if(n&1)
    {
n=bestodd(n);
cnt++;
    }
}
return cnt;
}