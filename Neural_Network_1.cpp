#include <iostream>
#include <stdlib.h>
#include <time.h>
#define THRESHOLD 1
using namespace std;

//get inputs from the user
//input: number of initial value, an array to store initial value
void get_inputs(int num, int input[]);
//generate random weights
//input: number of initial value, an array to store weight
void rand_weight(int num, double weight[]);
//McCulloch-Pitts module
int mcCullochPitts(int num, int input[], double weight[]);

int main(){
    srand(time(NULL));
    int num_of_inputs;
    cout << "Let threshold be " << THRESHOLD << endl;
    cout << "How many initail values: ";
    cin >> num_of_inputs;
    int input[num_of_inputs];  //initial input
    double weight[num_of_inputs];  //weight of each input
    get_inputs(num_of_inputs,input);
    rand_weight(num_of_inputs,weight);
    cout << "output: " << mcCullochPitts(num_of_inputs,input,weight) << endl;
    system("pause");
    return 0;
}

void get_inputs(int num, int input[]){
    cout << "Initail values: ";
    for(int i=0;i<num;++i) cin >> input[i];
}

void rand_weight(int num,double weight[]){
    double r;
    cout << "random weight: ";
    for(int i=0;i<num;++i) {
        r=(rand()%10)/10.0;
        weight[i]=r;
        cout << r << "   ";
    }
    cout << endl;
}

int mcCullochPitts(int num, int input[], double weight[]){
    double output=0;  //the output
    for(int i=0;i<5;++i)
        output+=input[i]*weight[i];
    if(output<THRESHOLD) return 0;
    else return 1;
}
