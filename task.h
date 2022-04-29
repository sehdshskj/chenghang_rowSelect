#ifndef _TASK_H_
#define _TASK_H
#include <stdio.h>
#include <stdlib.h>
typedef struct Row
{
    int a;
    int b;
} Row;
struct TreeNode//用于task4的树节点定义
{
    int value_a;//要搜索的a的值
    int interval_left;//该值所在的区间1000~99000
    int interval_right;
    int searchpos_left;//搜索该值在数组中的范围0~nrows-1
    int searchpos_right;
    struct TreeNode *left;//该节点的左右孩子
    struct TreeNode *right;
};
void task1(const Row *rows, int nrows);
void task2(const Row *rows, int nrows);
void task3(const Row *rows, int nrows);
void task4(const Row *rows, int nrows);

#endif