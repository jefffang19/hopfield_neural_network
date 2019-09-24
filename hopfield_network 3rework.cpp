/*
1.input each weights and threshold
2.will test all of the possible inputs
*/

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#define NUM 5  //number of neurons
#define TIMES 50 //update hopfield network for "TIMES" time
using namespace std;

//get weight and threshold from the user
void get_weight_threshold(double weight[NUM][NUM], double thres[]);

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
    int input[NUM]={1,0,0,1,1};  //initial input
    double weight[NUM][NUM];  //weight of each input
    double threshold[NUM];
    get_weight_threshold(weight,threshold);
    hop(input,threshold,weight);
    return 0;
}

void get_weight_threshold(double weight[NUM][NUM], double thres[]){
    cout << "weights:\n";
    for(int i=0;i<NUM;++i){
        for(int j=0;j<NUM;++j){
            if(j<i) weight[i][j]=weight[j][i];
            else if(j==i) weight[i][j]=0;
            else{
                cout << "weight[" << i+1 << "][" << j+1 << "]:";
                cin >> weight[i][j];
            }
        }
    }
    cout << "Thresholds:\n";
    for(int i=0;i<NUM;++i){
        cout << "Threshold[" << i+1 << "]:";
        cin >> thres[i];
    }
}


int hop(int input[], double thres[], double weight[NUM][NUM]){
    int r, rv, temp[NUM], tempE; //r:which neural to update.  rv:calculate the updated value
    cout << endl <<  "\ninitial input: ";
    for(int i=0;i<NUM;++i){
        cout << input[i] << " ";
        temp[i]=input[i];
    }
    for(int k=0;k<TIMES;++k){
        r=rand()%NUM; rv=update(r,temp,thres,weight);
    }
    tempE=E(temp,thres,weight);
    cout << "\nLowest E= " << tempE << endl;
    for(int i=0;i<NUM;++i) cout << temp[i] << " ";
    cout << endl;
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
