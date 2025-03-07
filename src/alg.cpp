#include "alg.h"
using namespace std;

void ALG::Iterate()
{
    int count = 0;
    double obj_func = CalWL() + lambda * CalDensity();;
    double pre_obj_func;
    do
    {
        count++;
        DiffWL();
        DiffDensity();
        for(auto cell : cell_vec) // update cell
        {
            cell->x -= cell->gradient_wl_x + lambda * cell->gradient_density_x;
            cell->y -= cell->gradient_wl_y + lambda * cell->gradient_density_y;
        }
        pre_obj_func = obj_func;
        obj_func = CalWL() + lambda * CalDensity();
        cout << "pre " << pre_obj_func << "\n";
        cout << "cur " << obj_func << "\n";
        cout << "Iteration count " << count << "\n";
    } while(obj_func < pre_obj_func);
}
void ALG::DiffWL()
{
    for(auto net : net_vec)
    {
        for(auto pin_cell : net->pin_cell_vec)
        {
            net->sum_exp_x_p += exp(pin_cell->x / gamma);
            net->sum_exp_x_n += exp(-pin_cell->x / gamma);
            net->sum_exp_y_p += exp(pin_cell->y / gamma);
            net->sum_exp_y_n += exp(-pin_cell->y / gamma);
        }
        for(auto pin_pad : net->pin_pad_vec)
        {
            net->sum_exp_x_p += exp(pin_pad->x / gamma);
            net->sum_exp_x_n += exp(-pin_pad->x / gamma);
            net->sum_exp_y_p += exp(pin_pad->y / gamma);
            net->sum_exp_y_n += exp(-pin_pad->y / gamma);
        }
    }
    for(auto cell : cell_vec)
    {
        for(auto pin_net : cell->pin_net_vec)
        {
            cell->gradient_wl_x += exp(cell->x / gamma) / pin_net->sum_exp_x_p - exp(-cell->x / gamma) / pin_net->sum_exp_x_n;
            cell->gradient_wl_y += exp(cell->y / gamma) / pin_net->sum_exp_y_p - exp(-cell->y / gamma) / pin_net->sum_exp_y_n;
        }
    }
}
double ALG::CalWL()
{
    double WL = 0;
    double lse_x_max;
    double lse_x_min;
    double lse_y_max;
    double lse_y_min;
    for(auto net : net_vec)
    {
        lse_x_max = -numeric_limits<double>::infinity();
        lse_x_min = -numeric_limits<double>::infinity();
        lse_y_max = -numeric_limits<double>::infinity();
        lse_y_min = -numeric_limits<double>::infinity();
        for(auto pin_cell : net->pin_cell_vec)
        {
            lse_x_max = log(exp(pin_cell->x / gamma) + exp(lse_x_max));
            lse_x_min = log(exp(-pin_cell->x / gamma) + exp(lse_x_min));
            lse_y_max = log(exp(pin_cell->y / gamma) + exp(lse_y_max));
            lse_y_min = log(exp(-pin_cell->y / gamma) + exp(lse_y_min));
        }
        for(auto pin_pad : net->pin_pad_vec)
        {
            lse_x_max = log(exp(pin_pad->x / gamma) + exp(lse_x_max));
            lse_x_min = log(exp(-pin_pad->x / gamma) + exp(lse_x_min));
            lse_y_max = log(exp(pin_pad->y / gamma) + exp(lse_y_max));
            lse_y_min = log(exp(-pin_pad->y / gamma) + exp(lse_y_min));
        }
        WL += gamma * (lse_x_max - lse_x_min);
        WL += gamma * (lse_y_max - lse_y_min);
    }
    cout << "WL " << WL << "\n";
    return WL;
}
void ALG::DiffDensity()
{
    for(auto cell : cell_vec)
    {
        for(auto nbr : cell_vec)
        {
            if(cell == nbr)
                continue;
            double kqq = cell->width * cell->height * nbr->width * nbr->height;
            double dx = (cell->x + cell->width / 2) - (nbr->x + nbr->width / 2);
            double dy = (cell->y + cell->height / 2) - (nbr->y + nbr->height / 2);
            double r = dx * dx + dy * dy;
            cell->gradient_density_x += -2 * kqq * dx / r / r;
            cell->gradient_density_y += -2 * kqq * dy / r / r;
        }
    }
}
double ALG::CalDensity()
{
    double density = 0;
    for(auto cell : cell_vec)
    {
        for(auto nbr : cell_vec)
        {
            if(cell == nbr)
                continue;
            double kqq = cell->width * cell->height * nbr->width * nbr->height;
            double dx = abs((cell->x + cell->width / 2) - (nbr->x + nbr->width / 2));
            double dy = abs((cell->y + cell->height / 2) - (nbr->y + nbr->height / 2));
            double r = sqrt(dx * dx + dy * dy);
            density += kqq / r / r;
        }
    }
    cout << "Density " << density << "\n";
    return density;
}