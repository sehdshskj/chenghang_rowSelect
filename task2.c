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
static void Search_print(const Row *rows, int nrows, int a_value)//搜索符合条件的值然后输出
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
    for (i = pos_b_left; i <= pos_b_right; i++)//在确定范围内顺序遍历
    {
        if (((rows + i)->b >= 10 && (rows + i)->b < 50) && ((rows + i)->a == a_value || (rows + i)->a == 2000 || (rows + i)->a == 3000))
        {
            printf("a:%d, b:%d\n", (rows + i)->a,(rows + i)->b);
        }
    }
}
void task2(const Row *rows, int nrows)
{
    Search_print(rows, nrows, 1000);
    Search_print(rows, nrows, 2000);
    Search_print(rows, nrows, 3000);
}   