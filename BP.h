#ifndef __BP_IMG__
#define __BP_IMG__

#include <bits/stdc++.h>
using namespace std;

const int N = 500, L = 500, M = 15;
const double alpha = 0.2, epsilon = 0.03;
const double Subalgha = 0.3;

// 学习率 alpha  
// 全局误差 epsilon

double F(double x); // 激活函数
double Gen(double l, double r); // 随机一个数在l,r中间
void input_arg(); // 输入参数值
void rand_arg(); // 随机参数值
void init_arg(); // 初始化参数 
void calc_h(); // 计算隐含层输入
void calc_y(); // 计算输出层输出
void calc_delta_y(); // 计算y的误差值
void calc_delta_h(); // 计算h的误差值
void calc_delta_arg(); // 计算全部参数的调整值
void adjust_arg(); // 调整误差值 | 就是参数加上调整值
double calc_E(); // 计算输出的误差
void print_to_log(); // 打印参数到文件
void set_data(double *in, double *d); // 将输入向量和期望函数置位
double run_train(); // 整合训练
double cmp(double *in, double *d); // 单独比较一个输入和期望的误差

#endif
