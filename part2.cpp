#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

double array[] = {1, 4, -3, -3, 1, 5, -2, 5, -2, 10, 15, 11, -2, -1, -2, 5, 6, 7, -1, 8};

struct delta_struct
{
    double delta;
    int start;
    int end;
};

vector<delta_struct> merge_consecutive(vector<delta_struct> all_delta_points)
{
    vector<delta_struct> merged;
    int i = 0;
    double total = 0;
    int first_sign = array[i]/abs(array[i]);
    
    delta_struct return_struct;
    
    int n = all_delta_points.size();
    
    while(i < n)
    {
        return_struct.start = i;
        
        while(first_sign*array[i] >= 0 && i < n)
        {
            return_struct.delta += array[i];
            i++;
        }
        return_struct.end = i;
        merged.push_back(return_struct);
        
        return_struct.delta = 0;
        return_struct.start = i;
        while(first_sign*array[i] < 0 && i < n)
        {
            return_struct.delta += array[i];
            i++;
        }
        return_struct.end = i;
        
        if((i < n) || ((i == n) && (return_struct.delta != 0)))
        {
            merged.push_back(return_struct);
        }
        
        return_struct.delta = 0;
    }
    
    return merged;
}

bool operator<(const delta_struct& s1, const delta_struct& s2)
{
    return !(s1.delta < s2.delta);
}

vector<delta_struct> merge_tolerance(vector<delta_struct> the_deltas, double tolerance)
{
    for(auto iter = the_deltas.begin(); iter != the_deltas.end(); iter++)
    {
        if(iter->delta < 0 && iter->delta >= tolerance)
        {
            delta_struct create;
            create.delta = (iter - 1)->delta + iter->delta + (iter + 1)->delta;
            create.start = (iter - 1)->start;
            create.end = (iter + 1)->end;
            
            auto in_iter = the_deltas.erase(iter, iter + 3);
            the_deltas.insert(in_iter, create);
            
            iter = (in_iter - 1);
        }
    }
    
    return the_deltas;
}

int count_positives(vector<delta_struct> the_deltas)
{
    int pos_count = 0;
    for(int i = 0; i < the_deltas.size(); i++)
    {
        if(the_deltas[i].delta >= 0)
            pos_count += 1;
    }
    
    return pos_count;
}

vector<delta_struct> merge(vector<delta_struct> the_deltas)
{
    vector<delta_struct> result;
    double tolerance = -1;
    
    if(the_deltas[0].delta < 0)
    {
        the_deltas.erase(the_deltas.begin());
    }
    
    if(the_deltas[the_deltas.size() - 1].delta < 0)
    {
        the_deltas.pop_back();
    }
    
    vector<delta_struct> prev;
    
    do
    {
        prev = result;
        result = merge_tolerance(the_deltas, tolerance);
        tolerance *= 1.5;
        cout << "in" << endl;
    }while(count_positives(result) > 5);
    
    if(count_positives(result) < 5)
    {
        sort(prev.begin(), prev.end());
        vector<delta_struct> ret_vec(prev.begin(), prev.begin() + 5);
        return ret_vec;
    }
    else
    {
        sort(result.begin(), result.end());
        vector<delta_struct> ret_vec(result.begin(), prev.begin() + 5);
        return result;
    }
}

int main()
{
    vector<delta_struct> test;
    delta_struct s;
    for(int i = 0; i < 20; i++)
    {
        s.delta = array[i];
        s.start = i;
        s.end = i + 1;
        test.push_back(s);
    }
    
    vector<delta_struct> merged = merge_consecutive(test);
    
    vector<delta_struct> result = merge(merged);
    
    for(int i = 0; i < merged.size(); i++)
        cout << merged[i].delta << endl;
    
    cout << endl;
    
    for(int i = 0; i < result.size(); i++)
        cout << result[i].delta << endl;
    
    return 0;
}