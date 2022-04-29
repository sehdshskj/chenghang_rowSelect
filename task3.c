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
static void Search_print(const Row *rows, int nrows, int a_value, Row **ret, int *retsize)
{
    int pos_a_left = 0, pos_a_right = 0;
    int pos_b_left = 0, pos_b_right = 0;
    int i;
    //根据a值确定的范围
    pos_a_left = biSearch_a(rows, 0, nrows - 1, a_value - 1);
    pos_a_right = biSearch_a(rows, 0, nrows - 1, a_value + 1);
    while((rows + pos_a_left)->a != a_value)
    {
        pos_a_left ++;
    }
    while((rows + pos_a_right)->a != a_value)
    {
        pos_a_right --;
    }
    //在a值确定范围的基础上根据b值进一步搜索
    pos_b_left = biSearch_b(rows, pos_a_left,pos_a_right,9);
    pos_b_right = biSearch_b(rows, pos_a_left,pos_a_right,51);
    for (i = pos_b_left; i <= pos_b_right; i++)//在确定范围内顺序遍历然后将结果存到*ret确定的内存空间内
    {
        if (((rows + i)->b >= 10 && (rows + i)->b < 50) && ((rows + i)->a == a_value || (rows + i)->a == 2000 || (rows + i)->a == 3000))
        {
            (*retsize) += 1;
            *ret = realloc(*ret, (*retsize) * sizeof(Row));
            (*ret + *retsize - 1)->a = (rows + i)->a;
            (*ret + *retsize - 1)->b = (rows + i)->b;
        }
    }
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
void task3(const Row *rows, int nrows)
{
    Row *ret = malloc(sizeof(Row));
    int retsize = 0;
    int i;
    Search_print(rows, nrows, 1000, &ret, &retsize);
    Search_print(rows, nrows, 2000, &ret, &retsize);
    Search_print(rows, nrows, 3000, &ret, &retsize);
    mergesort(ret, 0, retsize - 1);
    for(i = 0; i <retsize; i ++)
    {
        printf("a:%d, b:%d\n", (ret + i)->a,(ret + i)->b);
    }
    free(ret);
}