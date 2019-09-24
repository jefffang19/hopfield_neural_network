/*updated:
1.now can input any number of inputs
2.now can input each threshold
3.now E() uses loop
*/

#include <iostream>
#include <stdlib.h>
#include <time.h>
#define NUM 6  //number of neurons
#define TIMES 20 //update hopfield network for "TIMES" time
using namespace std;

//get inputs from the user
//input: number of initial value, an array to store initial value
void get_inputs(int input[], double thres[]);

//generate random weights
//input: number of initial value, an array to store weight
void rand_weight(double weight[NUM][NUM]);

//Hopfield network module
//input: 1.how many neural in this network 2.the input neurals 3.the weights
int hop(int input[], double thres[], double weight[NUM][NUM]);

//update the hopfield network's neural
//input: 1.which number of neural to update 2.the input neurals 3.the weights
int update(int randn, int input[], double thres[], double weight[NUM][NUM]);

//calculate the energy of hopfield network
//input: 1.the weights 2.the input neurals
double E(int input[], double thres[], double weight[NUM][NUM]);

int main(){
    //freopen("result.txt","w",stdout);
    srand(time(NULL));
    cout << "How many initail values: " << NUM << endl;
    int input[NUM];  //initial input
    double weight[NUM][NUM];  //weight of each input
    double threshold[NUM];
    get_inputs(input,threshold);
    rand_weight(weight);
    hop(input,threshold,weight);
    return 0;
}

void get_inputs(int input[], double thres[]){
    cout << "Initail values: ";
    for(int i=0;i<NUM;++i) cin >> input[i];
    cout << "Thresholds: ";
    for(int i=0;i<NUM;++i) cin >> thres[i];
}

void rand_weight(double weight[NUM][NUM]){
    double r;
    for(int i=0;i<NUM;++i)
        for(int j=0;j<NUM;++j){
            if(i==j) weight[i][j]=0;
            else if(i>j) weight[i][j]=weight[j][i];
            else{
                r=rand()/(RAND_MAX*1.0);
                weight[i][j]=r;
            }
        }
    cout << "random weight:\n";
    for(int i=0;i<NUM;++i){
        for(int j=0;j<NUM;++j)
            cout << "w[" << i << "][" << j << "]=" << weight[i][j] << "\t";
        cout << endl;
    }
}

int hop(int input[], double thres[], double weight[NUM][NUM]){
    int r, rv; //r:which neural to update.  rv:calculate the updated value
    for(int k=0;k<TIMES;++k){
        cout << endl <<  "\ninput: ";
        for(int i=0;i<NUM;++i) cout << input[i] << " ";
        cout << "\nE= " << E(input,thres,weight) << endl;
        r=rand()%NUM; rv=update(r,input,thres,weight);
        cout << "update: input no." << r << " to " << rv << endl;
        cout << "output: ";
        for(int i=0;i<NUM;++i) cout << input[i] << " ";
    }
}

double E(int input[], double thres[], double weight[NUM][NUM]){
    double sum1=0, sum2=0;
    for(int i=0;i<NUM;++i)
        for(int j=0;j<NUM;++j)
            sum1+=(-0.5)*(weight[i][j]*input[i]*input[j]);
    for(int i=0;i<NUM;++i)
        sum2+=thres[i]*input[i];
    return sum1+sum2;
}

int update(int randn, int input[], double thres[], double weight[NUM][NUM]){
    double updated_v=0;
    for(int i=0;i<NUM;++i)
        updated_v+=weight[randn][i]*input[i];
    if(updated_v<thres[randn]) input[randn]=0;
    else input[randn]=1;
    return input[randn];
}
