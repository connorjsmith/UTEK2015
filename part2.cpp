#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#define TOLERANCE -0.1
#define MULT_TOLERANCE 2
#define MAX_SIZE 10000

using namespace std;
/*
double* readFile(string fileName)
{
	double* closes = new double(MAX_SIZE);
	int index = 0;
	ifstream fs(fileName);
	while (index < 10000){
		fs>>closes[index];
		index++;
	}
	return closes;
}
*/

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
	int first_sign;
    if (all_delta_points[i].delta != 0){
    	first_sign = all_delta_points[i].delta/abs(all_delta_points[i].delta);
    } else {
    	first_sign = 1;
    }
    
    delta_struct return_struct;
    
    int n = all_delta_points.size();
    //cout << "Starting Loop"<<endl;
    while(i < n)
    {
        return_struct.start = i;
        while(first_sign*all_delta_points[i].delta >= 0 && i < n)
        {
            return_struct.delta += all_delta_points[i].delta;
            i++;
        }
        return_struct.end = i;
        merged.push_back(return_struct);
        
        return_struct.delta = 0;
        return_struct.start = i;
        while(first_sign*all_delta_points[i].delta < 0 && i < n)
        {
            return_struct.delta += all_delta_points[i].delta;
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
        if((iter->delta < 0) && (iter->delta >= tolerance))
        {
            delta_struct create;
            create.delta = (iter - 1)->delta + iter->delta + (iter + 1)->delta;
            create.start = (iter - 1)->start;
            create.end = (iter + 1)->end;
            
            auto in_iter = the_deltas.erase(iter - 1, iter + 2);
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
    double tolerance = TOLERANCE;
    
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
        tolerance *= MULT_TOLERANCE;
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
        vector<delta_struct> ret_vec(result.begin(), result.begin() + 5);
        return ret_vec;
    }
}



int main()
{
	double array [10000]; 
	int index = 0;
	ifstream fs("MSFT_closes.txt");
	while (fs>>array[index]){
		index++;
	}
	int j = 0;
	string dates[10000];
	ifstream dt("MSFT_dates.txt");
	while (dt>>dates[j])
		j++;
    vector<delta_struct> test;
    delta_struct s;
    for(int i = 0; i < index; i++)
    {
        s.delta = array[i+1]-array[i];
        s.start = i;
        s.end = i + 1;
        if (s.delta != 0) 
        	test.push_back(s);
    }

    vector<delta_struct> merged = merge_consecutive(test);
    vector<delta_struct> result = merge(merged);
    
    for(int i = 0; i < result.size(); i++){
        cout << result[i].delta << endl;
        cout << dates[result[i].start] << " -> "<< dates[result[i].end]<< endl;
    }
    
    return 0;

}