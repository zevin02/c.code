#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
typedef char btdata;
typedef struct BinaryTreeNode
{
    struct BinaryTreeNode *left;
    struct BinaryTreeNode *right;
    btdata data;
}btnode;



//前中后序遍历就是对根遍历的顺序不一样，但是在本质上都是对左子树，根，右子树这三部分进行的
//开辟节点
btnode* buynode(btdata x)
{
    

    btnode*node=malloc(sizeof(btnode));
    if(node==NULL)
    {
        exit(-1);
    }

node->data=x;
node->left=NULL;
node->right=NULL;
}

//暴力造一个树
btnode*creatbinarytree()
{
    btnode*nodeA=buynode('A');
    btnode*nodeB=buynode('B');
    btnode*nodeC=buynode('C');
    btnode*nodeD=buynode('D');
    btnode*nodeE=buynode('E');
    btnode*nodeF=buynode('F');
    nodeA->left=nodeB;
    nodeB->left=nodeD;
    nodeA->right=nodeC;
    nodeC->left=nodeE;
    nodeC->right=nodeF;
    return nodeA;//返回的是根节点
}

//前序
void preorder(btnode*root)
{
    //如果当前三一个空树
    if(root==NULL)
    {
        printf("NULL->");
        return ;
    }
//不是一个空树
printf("%c->",root->data);//根
preorder(root->left);//左子树
preorder(root->right);//右子树

}

//中序   左根右
void inorder(btnode*root)
{
    //如果当前三一个空树
    if(root==NULL)
    {
        printf("NULL->");
        return ;
    }
//不是一个空树

inorder(root->left);//左子树
printf("%c->",root->data);//根
inorder(root->right);//右子树
}

//后序   左右根
void postorder(btnode*root)
{
    //如果当前三一个空树
    if(root==NULL)
    {
        printf("NULL->");
        return ;
    }
//不是一个空树

postorder(root->left);//左子树
postorder(root->right);//右子树
printf("%c->",root->data);//根

}
//计算节点的个数
//错误方法
int binarytreesize(btnode*root)
{
    if(root==NULL)
    {
        return 0;
    }
    static int count=0;//用了static的话，每次调用都会在原来的基础上对count进行++，
    //如果不加static的话，cout在栈上开辟，调用完就会销毁
    count++;
    binarytreesize(root->left);
    binarytreesize(root->right);
    return count;//这样计算出来的结果永远都是1
}

void binarytreesize2(btnode*root,int*x)
{
    if(root==NULL)
    {
        return;
    }
    ++(*x);//对地址进行操作就不会出现static和销毁的情况了
    binarytreesize2(root->left,x);
    binarytreesize2(root->right,x);
}

int binarytreesize3(btnode*root)
{
    return root==NULL?0:binarytreesize3(root->left)+binarytreesize3(root->right)+1;//把问题分为了左右子树，和自己，不断的细分
}


//计算叶子节点的个数，就是没有子树节点的个数，度为0的个数
int binaryleafsize2(btnode*root)//左子树的叶子节点和右子树的叶子节点加起来
{
if(root==NULL)//并非一定整个树都是空，后面递归可能三左子树或右子树是空
{
return 0;
}

    return (root->left==NULL)&&(root->right==NULL)?1:binaryleafsize2(root->left)+binaryleafsize2(root->right);//为叶子就返回一，不为叶子就继续把左右子树的叶子加起来
}

//计算第k层节点的个数
//如，要求第4层，就求的3层的左子树节点数量加上右子树第3层的节点

//这里我们用了一个相对距离的概念
int binarytreelevelsize(btnode*root,int k)
{
 if(root==NULL)//没有节点，就通通返回0
 {
     return 0;
 }
 if(k<1)
 {
     return 0;
 }
 //走到了这里，就不为空
 else if(k==1)
 {
     return 1;//如果要我们求第一层就返回1,不用求了
 }
//root不为空，k大于1
//说明root第k层的节点在子树里面，
//就转化为了左右子树的第k-1层节点的数量
//如要求我的第4层，相当于求为左子树的第三层和右子树的第3层
return binarytreelevelsize(root->left,k-1)+binarytreelevelsize(root->right,k-1);
}

//计算树的深度（高度），层次，我们一般规定第一层为1，空树就算0,从1开始
//计算深度就是左子树深度和右子树深度中大的+1
int binarytreedepth(btnode*root)
{
if(root==NULL)
{
    return 0;
}
//这样写会重复计算，因为前面比较的时候已经算出结果了，但因为没有保存结果，严重的浪费了，
//return binarytreedepth(root->left)>binarytreedepth(root->right)?binarytreedepth(root->left)+1:binarytreedepth(root->right)+1;//大的那个+1

//用一个变量来记录
int leftdepth=binarytreedepth(root->left);//一层一层留一个大的返回区
int rightdepth=binarytreedepth(root->right);
//相当于后序
return leftdepth>rightdepth?leftdepth+1:rightdepth+1;

}

//二叉树中查找值为x的节点
//找到了就返回他的地址
btnode* binarytreefind(btnode*root,btdata x)
{
//根左右的遍历
//先找根
if(root==NULL)
{
    return NULL;//返回null是为了告诉上一层我没找到
}
if(root->data==x)//找到了
{
    return root;
}
      btnode*leftret=binarytreefind(root->left,x);
      if(leftret)//不为空，也就是左边找到了
      {
            return leftret;
      }
    btnode*rightret=binarytreefind(root->right,x);
     if(rightret)//没走上面的就走下面的，右边找到了
     {
      return rightret;
     }
return NULL;//左边没找到，右边也没找到
}

//层序遍历
//用队列实现，
//1.先入根，2.当前节点出来，再把他的孩子带进去，这样上一层出来的时候，又带入下一层，当队列为空，说明没有节点，就结束了




int main()
{
    btnode*root=creatbinarytree();//造一个树
   // preorder(root);//前序遍历，根，左子树，右子树
    //用分治，：分而治之，大事化小，小事化了
    //如校长想知道学校有多少人，让10个院报人数，院让专业老师统计人数，老师叫班长，一步一步化小，
   //inorder(root);
     postorder(root);
     int n1=0;
     binarytreesize2(root, &n1);//把n1地址传过去，每次都对这个地址进行操作，就没有销毁的问题了
     printf("\n");
     printf("n1=%d\n",n1);
     int n2=0;
    printf("n2=%d\n",binarytreesize3(root));
     int leafn=0;;
    printf("leafn=%d\n",leafn);
    printf("leaf2=%d\n",binaryleafsize2(root));
    int n3=0;
    printf("levelk=%d\n",binarytreelevelsize(root,3));
    printf("depth=%d\n",binarytreedepth(root));

    return 0;
}

