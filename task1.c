#include "task.h"
void task1(const Row *rows, int nrows)//依次扫描数据然后输出
{
    int i;
    for (i = 0; i < nrows; i++)
    {
        if (((rows + i)->b >= 10 && (rows + i)->b < 50) && ((rows + i)->a == 1000 || (rows + i)->a == 2000 || (rows + i)->a == 3000))
        {
            printf("a:%d, b:%d\n", (rows + i)->a,(rows + i)->b);
        }
    }
}
