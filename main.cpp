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
void print_cluster(std::ofstream&, int, int);

int main(int argc, char** argv) {
    
    std::ifstream ifs_train;
    std::ifstream ifs_test;
    std::ofstream ofs_train;
    std::ofstream ofs_test;
    // std::vector<vector<double>> clusters;
    std::vector<int> ans;

    if(argc < 9) {
        printf("\tWrong args.\n");
        printf("Use:\n ./ESOINN [train_file_name] [test_file_name] [train_file_size] [test_file_size] [output_train_set_name] [output_test_set_name] [age_max] [iter_thresh]\n");
        return 0;
    }
    soinn::ESOINN model(34671, atoi(argv[7]), atoi(argv[8]));
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
    std::cerr << "Training.." << std::endl;

    //train esoinn
    for(int t = 0; t < train_size; t++) {
        ifs_train >> num;
        // ans.push_back(num);
        for(int i = 0; i < 34671; i++) {
            ifs_train >> tmp;
            input(i) = tmp;
            // std::cerr << tmp;
        }
        fprintf(stderr, "\r%d   ", t);
        model.process(input);
        // std::cout<<t<<std::endl;
    }
    std::cerr << std::endl;

    model.classify();
    std::cout<<"number of classes: "<<model.getNumberOfClasses()<<std::endl;
    std::cout<<"number of vertices: "<<model.getNumberOfVertices()<<std::endl;

    ifs_train.close();
    ifs_train.open(argv[1]);
    struct soinn::VertexProperties vc;
    int class_count = model.getNumberOfClasses();

    ofs_train << train_size << ' ' << class_count << 2 << std::endl;

    std::cerr << "Generate output training set." << std::endl;
    //prepare output train set
    for(int t = 0; t < train_size; t++) {
        ifs_train >> num;
        // ans.push_back(num);
        for(int i = 0; i < 34671; i++) {
            ifs_train >> tmp;
            input(i) = tmp;
        }
        fprintf(stderr, "\r%d   ", t);
        vc = model.getBestMatch(input);
        print_cluster(ofs_train, vc.classId, class_count);
        print_cluster(ofs_train, num, 2);
        // std::cout<<t<<std::endl;
    }
    std::cerr << std::endl;
    ofs_train.close();
    ifs_train.close();

    ofs_test << test_size << ' ' << class_count << 2 << std::endl;
    std::cerr << "Generate output test set." << std::endl;
    //prepare output test set
    for(int t = 0; t < test_size; t++) {
        ifs_test >> num;
        // ans.push_back(num);
        for(int i = 0; i < 34671; i++) {
            ifs_test >> tmp;
            input(i) = tmp;
        }
        fprintf(stderr, "\r%d   ", t);
        vc = model.getBestMatch(input);
        print_cluster(ofs_test, vc.classId, class_count);
        print_cluster(ofs_test, num, 2);
        // std::cout<<t<<std::endl;
    }
    std::cerr << std::endl;
    ofs_test.close();
    ifs_test.close();
    return 0;
    
}

void print_cluster(std::ofstream& ofs, int current, int all) {
    for(int i = 0; i < all; i++) {
        if(i == current)
            ofs << 1;
        else 
            ofs << 0;
        ofs << ' ';
    }
    ofs << std::endl;
}

// void update_cluster_vectors(std::vector<vector<double>>& clusters, soinn::ESOINN& model) {
//     int cluster_count = model.getNumberOfClasses();
//     for(i=0; i<cluster_count; i++) {
//         clusters.push_back(model.)
//     }
// }