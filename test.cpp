#include "DE.hpp"

void printt(vector<int>);
vector<int> shuff(vector<int>, unsigned int);

int main(){

    // unsigned int seed;
    // seed = time (NULL);
    // srand(seed);

    // vector<int> qwe= {1,2,3,4,5,6,7,8,9};
    
    // qwe = shuff(qwe,seed);
    // printt(qwe);

    // qwe = shuff(qwe,seed);
    // printt(qwe);

    // qwe = shuff(qwe,seed);
    // printt(qwe);
    
    // initialization(2, 6);
    // print_vec_group(solution);
    // cout << "best:" << endl;
    // for (auto i : group_best_solution){
    //     cout << i << " " ;
    // }
    // cout << endl;
    // cout << best_result << endl;

    // cout << "-------" << endl;

    //vector<vec> after = mutation(0.5);

    // vector<vec> new_mutate = mutation(0.7, seed);
    // print_vec_group(new_mutate);

    // print_vec_group(after);

    execution(1000, 2, 20, 0.7, 0.5);

    return 0;
}

 void printt (vector<int> qwe){
    
    for(auto i : qwe){
        cout << i << " " ;
    }

    cout << endl;
 }

vector<int> shuff(vector<int> zxc, unsigned int seed){
    shuffle(zxc.begin(), zxc.end(), default_random_engine(seed));
 
    return zxc;
}