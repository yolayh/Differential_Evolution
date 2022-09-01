#include <iostream>
#include <cmath>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <random>
#include <algorithm>
#include <chrono>

using namespace std;

typedef vector<double> vec;


//變數
vector<vec> solution;                   
vec group_best_solution;
double best_result;

//function
double evaluation(vec);
void initialization(int, int);
vector<vec> mutation(double);
vector<int> mutate_choose(int);
bool check_bound(double);
void find_best();
vector<vec> crossover(double, vector<vec>);
void selection(vector<vec>);
void execution(int, int, int, double, double);
void print_vec_group(vector<vec>);

//Ackley function 
//  (2維: 變數為x跟y)
//  -20.0 * exp(-0.2 * sqrt(0.5 * (x**2 + y**2)))-
//  exp(0.5 * (cos(2 * pi * x)+cos(2 * pi * y)))  +
//  exp(1) +
//  20

//r_min, r_max = -32.768, 32.768

// f(x)= -20*exp(-0.2*sqrt(1/d)sum(pow(xi,2))) - exp(1/d*cos(2*pi*xi)) + exp(1) + 20


double evaluation(vec a){
    double value = 0;
    double quadratic = 0;
    double cos_sum = 0;
    int size = a.size();

    for(int i = 0; i < size; i++){
        quadratic += pow(a[i], 2);
    }

    for(int i = 0; i < size; i++){
        cos_sum += cos(2*M_PI*a[i]);
    }

    value = - (20*exp(-0.2*sqrt((1.0/size)*quadratic))) - (exp ((1.0/size)*cos_sum)) + exp(1) + 20;

    return value;
}


void initialization(int dimension, int pop_size){
    double max = 32.768;
    double min = -32.768;
    vec v;

    //設定初始值(position)
    for(int k =0; k < pop_size; k++){
        v.clear();
        for(int i =0; i<dimension; i++){
            double rand_num = (max - min) * (rand() / (RAND_MAX + 1.0)) + min;
            v.push_back(rand_num);
        }
        solution.push_back(v);
    }

    //初始值找最佳解
    best_result = 99999.999;
    find_best();

}

//Mutation
vector<vec> mutation(double F){
    int pop_size = solution.size();
    int dimension = solution[0].size();
    vector<vec> after_mutate;
    vector<int> mutate_list;
    vec temporary;
    for (int i = 0; i < pop_size; i++){

        temporary.clear();
        mutate_list.clear();;
        mutate_list = mutate_choose(i); 

        // cout << "---mutate----" << i << endl;
        // for (auto p:mutate_list){
        //     cout << p << " ";
        // }
        // cout << endl;

        for(int k = 0; k<dimension; k++){
            double mutate_num = solution[mutate_list[0]][k] + F*(solution[mutate_list[1]][k]-solution[mutate_list[2]][k]);
            if(check_bound(mutate_num)){
                if (mutate_num < -32.768){
                    mutate_num = -32.768;
                }
                else{
                    mutate_num = 32.768;
                }
            }
            temporary.push_back(mutate_num);
        }
        after_mutate.push_back(temporary);
    }
    return after_mutate;
}


//choose three int and check repeat or not
vector<int> mutate_choose(int num){

    unsigned mutate_seed = rand();

    vector<int> choosen;
    vector<int> all_numbers;

    for(int k = 0;k < solution.size();k++){
        if(k!=num){
            all_numbers.push_back(k);
        }
    }


    shuffle(all_numbers.begin(), all_numbers.end(), default_random_engine(mutate_seed));
    

    for(int i = 0; i < 3; i++){
        choosen.push_back(all_numbers[i]);
    }

    
    return choosen;
}


//check position is in the boundary or not
bool check_bound(double num){
    double max = 32.768;
    double min = -32.768;
    if (num > max or num < min){
        return true;
    }

    return false;
}


//從 solution 找最佳解
void find_best(){
    int pop_size = solution.size();
    for(int i =0; i < pop_size; i++){
        if ( evaluation(solution[i]) < best_result){
            best_result = evaluation(solution[i]);
            group_best_solution = solution[i];
        }
    }
}


vector<vec> crossover(double cr_rate, vector<vec> mutated){
    int pop_size = solution.size();
    int dimension = solution[0].size();
    vec temp;
    vector<vec> new_solution;
    for (int k = 0;k < pop_size; k++){
        temp.clear();
        for (int i = 0; i < dimension; i++){
            double rand_num = rand() / (RAND_MAX + 1);
            if ( rand_num < cr_rate){
                temp.push_back(mutated[k][i]);
            }
            else{
                temp.push_back(solution[k][i]);
            }
        }
        new_solution.push_back(temp);
    }

    return new_solution;
}

void selection(vector<vec> new_solution){
    int pop_size = solution.size();
    int dimension = solution[0].size();
    for (int k = 0;k < pop_size; k++){
        double origine_value = evaluation(solution[k]);
        double new_value = evaluation(new_solution[k]);
        if (new_value < origine_value){
            solution[k] = new_solution[k];
        }
    }
}


void execution(int iteration, int dimension, int pop_size, double F, double cr_rate){
    
    unsigned seed = time(NULL);
    srand(seed); 

    initialization(dimension, pop_size);

    
    for(int i =0; i<iteration; i++){
        print_vec_group(solution);
        //cout << "------iteration-" << i << endl;
        vector<vec> mutated = mutation(F);

        //cout << "---after mutated" << endl;
        //print_vec_group(mutated);

        vector<vec> new_vec = crossover(cr_rate, mutated);
        
        selection(new_vec);
        cout << "---end" << endl;
        print_vec_group(solution);
        
        find_best();
    }

    cout << endl;
    cout << "******ending******" << endl;
    cout << "best answer:" << endl;
    
    for(auto y:group_best_solution){
        cout << y << " ";
    }

    cout << "\n" << best_result << endl;
}


void print_vec_group(vector<vec> v){
    for (int i = 0; i<v.size(); i++){
        for (int k = 0; k <v[i].size(); k++){
            cout << v[i][k] << " ";
        }
        cout << endl;
    }
}


