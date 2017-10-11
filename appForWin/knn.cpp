#include "knn.h"
#include <vector>
#include <math.h>
#include "common.h"

using namespace std;

knn::knn(vector<Features>train, Features test)
{
    vector<sample> traindata;
    sample testdata;
    for(auto item:train)
    {
        sample news;
        news.features.push_back(item.FreqMean);
    }
}

double knn::max(int s[],int n)
{
    int maximum=s[0];
    int maxindex=0;
    for(int i=1;i<n;i++)
    {
        if(s[i]>maximum)
        {
            maximum=s[i];
            maxindex=i;
        }
    }
    //return maxindex;
    return maximum;
}

double knn::getdist(double newx, double data)
{
    return sqrt((newx-data)*(newx-data));
}

void knn::runknn(sample newx, vector<sample>&traindata,
            vector<sample> &nearestsample)
{
    int m=traindata.size();
    int n=traindata[0].features.size();
    double distance=0.0;
    for(int i=0;i<m;i++)
    {
        distance=0.0;
        for(int j=0;j<n;j++)
            distance=getdist(newx.features[i],traindata[i].features[j]);

        traindata[i].distance=distance;
    }
    int k=nearestsample.size();
    for(int i=0;i<k;i++)
        nearestsample[i]=traindata[i];
}

double knn::sortknn(vector<sample>&traindata,
                    sample &testdata)
{
   vector<sample>nearestsample;
   int label[5]={0};
   runknn(testdata,traindata,nearestsample);

   for(int j=0;j<5;j++)
   {
       switch (nearestsample[j].label) {
       case 0:
           label[0]++;
           break;
       case 1:
           label[1]++;
           break;
       case 2:
           label[2]++;
           break;
       case 3:
           label[3]++;
           break;
       case 4:
           label[4]++;
           break;
       default:
           break;
       }
   }
   testdata.result=max(label,5);
   return testdata.result;
}






























































