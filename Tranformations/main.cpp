//
//  main.cpp
//  Tranformations
//
//  Created by mwl on 2017/8/24.
//  Copyright © 2017年 loong6. All rights reserved.
//
/**
 矩阵  向量 于数字进行运算  直接作用于每个元素上
 向量点乘  两个向量的模相乘再乘以夹角的余弦值  相当于一条向量在另一条向量上的投影
 向量叉乘  结果是同时正交于两个向量的向量  
    计算方法 ： （意会吧。。。。。。）
        a   d    bf - ce
        b * e  = cd - af
        c   f    ae - bd
 矩阵相乘：👻👻👻👻👻👻👻👻
 限制条件：
    1.乘号左边矩阵的列数等于右边矩阵的行数时  可以相乘
    2.不满足交换律
 方法：
    乘积C的第m行第n列的元素等于矩阵A的第m行的元素与矩阵B的第n列对应元素乘积之和。
 结果
    维度是左边行* 右边列的矩阵
 */
#include <iostream>


int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
