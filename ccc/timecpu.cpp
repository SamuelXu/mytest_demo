
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


double CalcMean ( std::vector<double> & v )
{
    double mean = 0;

    for(int i = 0; i < (int)v.size(); i++)
    {
        mean += v[i];
    }

    mean /= double(v.size());

    return mean;
}

double CalcMean ( std::vector<double> & v, int a, int b )
{
    double mean = 0;

    for(int i = a; i <= b; i++)
    {
        mean += v[i];
    }

    mean /= (b-a+1);
    return mean;
}

double CalcStdv ( std::vector<double> & v, int a, int b )
{
    double mean = CalcMean(v,a,b);

    double stdv = 0;

    for(int i = a; i <= b; i++)
    {
        double x = v[i] - mean;

        stdv += x*x;
    }

    stdv = sqrt(stdv / (b-a+1));

    return stdv;
}

// Return true if the largest value in v[0,len) is more than three
// standard deviations from the mean

bool ContainsOutlier ( std::vector<double> & v, size_t len )
{
    double mean = 0;

    for(size_t i = 0; i < len; i++)
    {
        mean += v[i];
    }

    mean /= double(len);

    double stdv = 0;

    for(size_t i = 0; i < len; i++)
    {
        double x = v[i] - mean;
        stdv += x*x;
    }

    stdv = sqrt(stdv / double(len));

    double cutoff = mean + stdv*3;

    return v[len-1] > cutoff;
}

// Do a binary search to find the largest subset of v that does not contain
// outliers.

void FilterOutliers ( std::vector<double> & v )
{
    std::sort(v.begin(),v.end());

    size_t len = 0;

    for(size_t x = 0x40000000; x; x = x >> 1 )
    {
        if((len | x) >= v.size()) continue;

        if(!ContainsOutlier(v,len | x))
        {
            len |= x;
        }
    }

    v.resize(len);
}

// Iteratively tighten the set to find a subset that does not contain
// outliers. I'm not positive this works correctly in all cases.

void FilterOutliers2 ( std::vector<double> & v )
{
    std::sort(v.begin(),v.end());

    int a = 0;
    int b = (int)(v.size() - 1);

    for(int i = 0; i < 10; i++)
    {
        //printf("%d %d\n",a,b);

        double mean = CalcMean(v,a,b);
        double stdv = CalcStdv(v,a,b);

        double cutA = mean - stdv*3;
        double cutB = mean + stdv*3;

        while((a < b) && (v[a] < cutA)) a++;
        while((b > a) && (v[b] > cutB)) b--;
    }

    std::vector<double> v2;

    v2.insert(v2.begin(),v.begin()+a,v.begin()+b+1);

    v.swap(v2);
}

__inline__ unsigned long long int rdtsc()
{
#ifdef __x86_64__
    unsigned int a, d;
    __asm__ volatile ("rdtsc" : "=a" (a), "=d" (d));
    return (unsigned long)a | ((unsigned long)d << 32);
#elif defined(__i386__)
    unsigned long long int x;
    __asm__ volatile ("rdtsc" : "=A" (x));
    return x;
#else
#define NO_CYCLE_COUNTER
    return 0;
#endif
}

int main(int argc, char* argv[])
{
    int trials = atoi(argv[1]);

    vector<double> times;
    times.reserve(trials);
    double t = 0;

    volatile register int64_t begin,end;

    for(int i=0;i<trials;i++) {
        begin = rdtsc();
        usleep(1000000);
        end = rdtsc();
        t = end - begin;
        if(t>0) times.push_back(t);
    }
    sort(times.begin(),times.end());

    FilterOutliers(times);

    double cycles = CalcMean(times);

    printf("%8.2f cycles/sec\n",cycles);
}

