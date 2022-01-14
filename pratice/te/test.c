#include<stdio.h>
//计算区间和

//计算区间和
int interval(int *a,int k,int n)
{
    return k?a[n]-a[k-1]:a[n];
}

int minSubArrayLen(int target, int* nums, int numsSize){
//先计算前缀和
int sum[numsSize];
sum[0]=nums[0];
int i=1;
for(i=1;i<numsSize;i++)
{
    sum[i]=sum[i-1]+nums[i];
}
int j,k;
int len=0;
int min=target;
for(j=0;j<numsSize;j++)
{
    for(k=j;k<numsSize;k++)
    {

        int x=interval(sum,j,k);
        if(x>=min)
        {

if(len>k-j+1||len==0)
{
    len=k-j+1;
    min=x;
    break;
}

        }

    }

}
return len;
}
int main()
{
    int arr[6]={2,3,1,2,4,3};
    minSubArrayLen(7,arr,6);
    return 0;
}