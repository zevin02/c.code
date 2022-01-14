#include<stdio.h>

#include<stdlib.h>

void _mergesort(int *a,int left,int right,int *tmp)
{
//1个就不用分了
if(left>=right)
{
    return;
}

int mid=(left+right)/2;
//[left,mid]有序[mid+1,right],有序就可以进行归并了
//左边和右边都有序了就可以进行归并了
_mergesort(a,left,mid,tmp);
_mergesort(a,mid+1,right,tmp);
//后序
//开始归并了
int begin1=left,end1=mid;
int begin2=mid+1,end2=right;
int i=left;//i不是0而是left，这样返回原数组就可以
while(begin1<=end1&&begin2<=end2)//有一个结束了就可以把另一个全部都接起来
{
if(a[begin1]<a[begin2])
{
tmp[i++]=a[begin1];
begin1++;
}
else
{
    tmp[i++]=a[begin2];
    begin2++;
}
}
//不知道谁结束了
while(begin1<=end1)
{
    tmp[i++]=a[begin1];
begin1++;
}
while(begin2<=end2)
{
   tmp[i++]=a[begin2];
    begin2++; 
}
//tmp还要拷贝回a，这样才可以回去进行归并
for(int j=left;j<=right;j++)
{
    a[j]=tmp[j];
}

}



void mergesort(int *a,int n)
{

    int *tmp=(int *)malloc(sizeof(int)*n);
    if(tmp==NULL)
    {
printf("malloc fail");
    return;
    }
_mergesort(a,0,n-1,tmp);//在这里容易递归，子函数
free(tmp);
tmp=NULL;

}


//归并非递归循环写法
void mergesortnonr(int *a,int n)//n为个数
{
 int *tmp=(int *)malloc(sizeof(int)*n);
    if(tmp==NULL)
    {
printf("malloc fail");
    return;
    }
   
   int gap=1;//一个一个归
  
   while(gap<n)
   {
   for(int i=0;i<n;i+=2*gap)
   {
//这个循环里面就变成归并
//[i,i+gap-1],[i+gap,i+2*gap-1]
//[0,     0 ],[1    , 1       ]
int index=i;//tmp数组的起始位置是i相当于递归里面的left

int begin1=i,end1=i+gap-1;
int begin2=i+gap,end2=i+gap*2-1;

//第一组越界,end1越界，【begin2,end2】不存在
if(end1>=n)//等于n就已经越界了//先end1
{
    end1=n-1;//进行修正
}

//第2组不存在,begin2,end2不存在，再被begin2
if(begin2>=n)
{
    //让这个区间不存在
    begin2=n;
    end2=n-1;

}

if(end2>=n)
{
    end2=n-1;//再修正一下
}
//如果begin1=end1=begin2=end2=n-1的话，tmp就会越界，重复的index++，后free多的未开辟的空间，index越界，进取一次出来又一次+




//将其进行归并
while(begin1<=end1&&begin2<=end2)
{
    if(a[begin1]<a[begin2])
    {
        tmp[index++]=a[begin1++];
    }
else
{

    tmp[index++]=a[begin2++];
}

}
while(begin1<=end1)
{
    tmp[index++]=a[begin1++];
}
while(begin2<=end2)
{
     tmp[index++]=a[begin2++];
}

}
//把归并数组拷贝回原数组
//整段拷贝回去
for(int i=0;i<n;i++)
{
    a[i]=tmp[i];
}
gap*=2;
   }

free(tmp);
tmp=NULL;

   }


void mergesortnonr2(int *a,int n)//n为个数
{
 int *tmp=(int *)malloc(sizeof(int)*n);
    if(tmp==NULL)
    {
printf("malloc fail");
    return;
    }
   
   int gap=1;//一个一个归
  
   while(gap<n)
   {
   for(int i=0;i<n;i+=2*gap)
   {
//这个循环里面就变成归并
//[i,i+gap-1],[i+gap,i+2*gap-1]
//[0,     0 ],[1    , 1       ]
int index=i;//tmp数组的起始位置是i相当于递归里面的left

int begin1=i,end1=i+gap-1;
int begin2=i+gap,end2=i+gap*2-1;

//end1越界 或者 begin2都不需要处理归并
if(end1>=n||begin2>=n)
{
     break;//进行修正
}
//end2越界就需要归，就修正end2就可以
if(end2>=n)
{
    end2=n-1;//再修正一下
}
//如果begin1=end1=begin2=end2=n-1的话，tmp就会越界，重复的index++，后free多的未开辟的空间，index越界，进取一次出来又一次+


//将其进行归并
while(begin1<=end1&&begin2<=end2)
{
    if(a[begin1]<a[begin2])
    {
        tmp[index++]=a[begin1++];
    }
else
{

    tmp[index++]=a[begin2++];
}

}
while(begin1<=end1)
{
    tmp[index++]=a[begin1++];
}
while(begin2<=end2)
{
     tmp[index++]=a[begin2++];
}
for(int j=begin1;j<=end1;j++)
{
    a[j]=tmp[j];
}
}
//把归并数组拷贝回原数组
//整段拷贝回去

gap*=2;
   }

free(tmp);
tmp=NULL;

   }




void print(int *a,int n)
{
    int i=0;
    for(i=0;i<n;i++)
    {
printf("%d ",a[i]);

    }
}



int main()
{
    //归并排序
    int arr[10]={10,6,7,1,3,4,2,0,11,12};
    //mergesort(arr,sizeof(arr)/sizeof(int));
   // mergesortnonr(arr,sizeof(arr)/sizeof(int));
    mergesortnonr2(arr,sizeof(arr)/sizeof(int));
    print(arr,sizeof(arr)/sizeof(int));
    return 0;
}