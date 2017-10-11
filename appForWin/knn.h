#ifndef KNN_H
#define KNN_H

#include <string>
#include <vector>
#include "common.h"
using namespace std;

class knn
{
public:
    knn(vector<Features>train, Features test);
    ~knn() {}

    inline
    bool cmp(sample &sOne, sample &sTwo)
    {
        return sOne.distance<sTwo.distance;
    }

    double max(int s[],int n);
    double getdist(double newx, double data);
    double sortknn(vector<sample>&traindata,
                   sample &testdata);
    void runknn(sample newx,
                vector<sample>&traindata,
                vector<sample> &nearestsample);

};

#endif // KNN_H
