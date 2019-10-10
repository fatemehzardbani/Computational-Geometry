#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<queue>
#include<vector>
#include <time.h>

#include"geometry_base.h"
#include "testcase_generator.h"

#define CLOCK CLOCK_PROCESS_CPUTIME_ID

long timespec_diff(struct timespec *strt, struct timespec *stp) {
    return (stp->tv_sec-strt->tv_sec-1)*1000+(1000000000+stp->tv_nsec-strt->tv_nsec)/1000000;
}

using namespace std;

struct timespec ptim,ctim;




int main()
{//freopen("t.txt","r",stdin);

    vector<point> ps;
    int n;
    cin>>n;
    generate_random(n,ps);


    clock_gettime(CLOCK,&ptim);

    polygon_convex ans =convex_hull(ps);

    clock_gettime(CLOCK,&ctim);

    printf(" time Elapsed: %ld milliseconds\n",
           timespec_diff(&ptim,&ctim));
    ans.print();
    return 0;
}

























