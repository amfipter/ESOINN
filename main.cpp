#include <iostream>
#include <fstream>
#include <random>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "ESOINN.h"
#include <boost/numeric/ublas/vector.hpp>
#include <stdlib.h>

// typedef boost::numeric::ublas ub;
using namespace boost::numeric::ublas;

// void update_cluster_vectors(std::vector<vector<double>>&, soinn::ESOINN&);

int main(int argc, char** argv) {
    soinn::ESOINN model(34671, 10, 30);
    std::ifstream ifs_train;
    std::ifstream ifs_test;
    std::ofstream ofs_train;
    std::ofstream ofs_test;
    // std::vector<vector<double>> clusters;
    std::vector<int> ans;

    if(argc < 7) {
        printf("\tWrong args.\n");
        printf("Use:\n ./ESOINN [train_file_name] [test_file_name] [train_file_size] [test_file_size] [output_train_set_name] [output_test_set_name]\n");
        return 0;
    }

    ifs_train.open(argv[1]);
    ifs_test.open(argv[2]);
    ofs_train.open(argv[5]);
    ofs_test.open(argv[6]);
    // ifs.open("iris.txt");
    vector<double> input(34671);
    int num;
    double tmp;
    int train_size = atoi(argv[3]);
    int test_size = atoi(argv[4]);
    for(int t = 0; t < train_size; t++) {
        ifs >> num;
        ans.push_back(num);
        for(int i = 0; i < 34671; i++) {
            ifs >> tmp;
            input(i) = tmp;
        }
        fprintf(stderr, "\r%d   ", t);
        model.process(input);
        // std::cout<<t<<std::endl;
    }
    model.classify();
    std::cout<<"number of classes: "<<model.getNumberOfClasses()<<std::endl;
    std::cout<<"number of vertices: "<<model.getNumberOfVertices()<<std::endl;

    ifs_train.close();
    ifs_train.open(argv[1]);
    
}

// void update_cluster_vectors(std::vector<vector<double>>& clusters, soinn::ESOINN& model) {
//     int cluster_count = model.getNumberOfClasses();
//     for(i=0; i<cluster_count; i++) {
//         clusters.push_back(model.)
//     }
// }