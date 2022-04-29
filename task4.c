#include "task.h"

static int biSearch_a(const Row * rows, int lo, int hi, int e)//根据a值进行二分查找
{
    int mid;
    while(lo < hi)
    {
        mid = (lo + hi) / 2;
        if((rows + mid)->a >= e)
        {
            hi = mid;
        }
        else
        {
            lo = mid + 1;
        }
    }
    return lo;
}
static int biSearch_b(const Row * rows, int lo, int hi, int e)//根据b值进行二分查找
{
    int mid;
    while(lo < hi)
    {
        mid = (lo + hi) / 2;
        if((rows + mid)->b >= e)
        {
            hi = mid;
        }
        else
        {
            lo = mid + 1;
        }
    }
    return lo;
}
static void merge(Row *arr, int lo, int mid, int hi)//根据b值归并
{
    Row *B = malloc(sizeof(Row)*(mid + 1 - lo));
    int i, j, k;
    for(i = lo; i < mid + 1; i ++)
    {
        (B + i - lo)->a = (arr + i)->a;
        (B + i - lo)->b = (arr + i)->b;
    }
    for(i = 0 , k = lo, j = mid + 1; i < mid + 1 - lo;)
    {
        if(j > hi || (B + i)->b < (arr + j)->b)
        {
            (arr + k)->a = (B + i)->a;
            (arr + k)->b =(B + i)->b;  
            k ++;          
            i ++;
        }
        else
        {
            (arr + k)->a = (arr + j)->a;
            (arr + k)->b =(arr + j)->b;  
            k ++;          
            j ++;            
        }
    }
    free(B);
}
static void mergesort(Row *arr, int lo, int hi)//归并排序
 {
     if(lo >= hi) return;
     int mid;
     mid = (lo + hi) >> 1;
     mergesort(arr, lo, mid);
     mergesort(arr, mid+1, hi);
     merge(arr, lo, mid, hi);
 }
static void Search_print(const Row *rows, int left,int right, int a_value, Row **ret, int *retsize, int *pos_a_left, int *pos_a_right)
{   //搜索符合条件的值然后输出并确定下一次搜索的范围
    //如果a值a_value对应的树节点内没有左孩子或右孩子，传进来的这两个值为空
    if(pos_a_left == NULL)
    {
        pos_a_left = malloc(sizeof(int));
    }
    if(pos_a_right == NULL)
    {
        pos_a_right = malloc(sizeof(int));
    }
    int oldposleft = left;
    int oldposright = right;
    *pos_a_left = 0, 
    *pos_a_right = 0;
    int pos_b_left = 0, pos_b_right = 0;
    int i;
    //根据a值确定的范围
    *pos_a_left = biSearch_a(rows, left, right, a_value - 1);
    *pos_a_right = biSearch_a(rows, left, right, a_value + 1);
    while((rows + *pos_a_left)->a != a_value && *pos_a_left <= right)
    {
        (*pos_a_left) ++;
    }
    while((rows + *pos_a_right)->a != a_value && *pos_a_right >= 0)
    {
        (*pos_a_right) --;
    }
    if(*pos_a_left > right || *pos_a_right < 0) 
    {
        *pos_a_left = oldposleft;
        *pos_a_right = oldposright;
        return ;//如果查找失败
    }
    //在a值确定范围的基础上根据b值进一步搜索
    pos_b_left = biSearch_b(rows, *pos_a_left,*pos_a_right,9);
    pos_b_right = biSearch_b(rows, *pos_a_left,*pos_a_right,51);
    for (i = pos_b_left; i <= pos_b_right; i++)
    {//在确定范围内顺序遍历然后将结果存到*ret确定的内存空间内
        if (((rows + i)->b >= 10 && (rows + i)->b < 50) && ((rows + i)->a == a_value || (rows + i)->a == 2000 || (rows + i)->a == 3000))
        {
            (*retsize) += 1;
            *ret = realloc(*ret, (*retsize) * sizeof(Row));
            (*ret + *retsize - 1)->a = (rows + i)->a;
            (*ret + *retsize - 1)->b = (rows + i)->b;
        }
    }
}
void visit(const Row *rows,struct TreeNode *root,Row **ret, int *retsize)
{   //遍历访问树中的节点
    if(root == NULL) return;
    root->left = NULL;
    root->right = NULL;
    if(root->value_a != root->interval_left)//如果该节点有左孩子
    {
        root->left = malloc(sizeof(struct TreeNode));
        if((root->value_a - root->interval_left) >= 2000)
        {//如果该节点的左孩子能再往下划分区间
            root->left->value_a = (root->value_a + root->interval_left) / 2000 * 1000;
            //区间长度更新
            root->left->interval_left = root->interval_left;
            root->left->interval_right = root->value_a - 1000;
            root->left->searchpos_left = root->searchpos_left;
        }
        else//如果该节点的左孩子没法再往下划分区间
        {
            root->left->value_a = root->interval_left;
            //把区间长度置为零
            root->left->interval_left = root->left->value_a;
            root->left->interval_right = root->left->value_a;
            root->left->searchpos_left = root->searchpos_left;           
        }
    }
    if(root->value_a != root->interval_right)//该节点有右孩子
    {
        root->right = malloc(sizeof(struct TreeNode));
        if( root->interval_right - root->value_a  >= 2000)
        {//如果该节点的右孩子能再往下划分区间
            root->right->value_a = (root->value_a + root->interval_right) /2000 * 1000;
            //区间长度更新
            root->right->interval_left = root->value_a + 1000;
            root->right->interval_right = root->interval_right;
            root->right->searchpos_right = root->searchpos_right;
        }   
        else//如果该节点的右孩子没法再往下划分区间
        {
            root->right->value_a = root->interval_right;
            //把区间长度置为零
            root->right->interval_left = root->right->value_a;
            root->right->interval_right = root->right->value_a;
            root->right->searchpos_right = root->searchpos_right;            
        }
    }
    if(root->left && root->right)
    {   //搜索该节点确定的区间
        Search_print(rows, root->searchpos_left, root->searchpos_right,root->value_a, ret, retsize,&root->right->searchpos_left,&root->left->searchpos_right);
        //访问左右孩子
        visit(rows,root->left,ret,retsize);
        visit(rows,root->right,ret,retsize);
    }
    else if(root->left)
    {   //只有左孩子
        Search_print(rows, root->searchpos_left, root->searchpos_right,root->value_a, ret, retsize,NULL,&root->left->searchpos_right);
        visit(rows,root->left,ret,retsize);
    }
    else if(root->right)
    {   //只有右孩子
        Search_print(rows, root->searchpos_left, root->searchpos_right,root->value_a, ret, retsize,&root->right->searchpos_left,NULL);
        visit(rows,root->right,ret,retsize);
    }
    else
    {
        Search_print(rows, root->searchpos_left, root->searchpos_right,root->value_a, ret, retsize,NULL,NULL);
    }
    free(root);
}
void task4(const Row *rows,int nrows)
{
    Row *ret = malloc(sizeof(Row));
    int retszie = 0;
    int i;   
    if(nrows < 1) return;
    //初始化根节点
    struct TreeNode *root = malloc(sizeof(struct TreeNode));
    root->interval_left = 1000;
    root->interval_right = 99000;
    root->value_a = (root->interval_left + root->interval_right) / 2000 * 1000;
    root->searchpos_left = 0;
    root->searchpos_right = nrows - 1;
    //访问根节点
    visit(rows,root,&ret,&retszie);
    //归并排序
    mergesort(ret, 0, retszie - 1);
    //输出
    for(i = 0; i <retszie; i ++)
    {
        printf("a:%d, b:%d\n", (ret + i)->a,(ret + i)->b);
    }
    free(ret);    
}
