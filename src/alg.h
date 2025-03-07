#ifndef _ALG_H_
#define _ALG_H_

#include <bits/stdc++.h>
using namespace std;

#define boundry_o 0
#define lambda 0.07
#define gamma 10

class NET;
class CELL
{
public:
    vector<NET *> pin_net_vec;
    double x, y, width, height;
    // diff wl
    double gradient_wl_x = 0;
    double gradient_wl_y = 0;
    // diff density
    double gradient_density_x = 0;
    double gradient_density_y = 0;

    CELL(double x, double y, double width, double height)
    : x(x), y(y), width(width), height(height) {}
};
class NET
{
public:
    vector<CELL *> pin_cell_vec;
    vector<CELL *> pin_pad_vec;
    // diff wl
    double sum_exp_x_p = 0;
    double sum_exp_x_n = 0;
    double sum_exp_y_p = 0;
    double sum_exp_y_n = 0;
};
class ALG
{
public:
    vector<CELL *> lib_vec;
    vector<CELL *> cell_vec;
    vector<CELL *> pad_vec;
    vector<NET *> net_vec;
    void Iterate();
    void DiffWL();
    double CalWL();
    void DiffDensity();
    double CalDensity();
private:
        
};

#endif