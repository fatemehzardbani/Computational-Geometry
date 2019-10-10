//
// Created by Wbs on 2019-10-09.
//

#ifndef PARTA_TESTCASE_GENERATOR_H
#define PARTA_TESTCASE_GENERATOR_H
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<queue>
#include<vector>
#include"geometry_base.h"
using namespace std;

void generate_random(int n,vector<point> & ps)
{
    ps.clear(); ps.resize(0);
    for(int i=0;i<n;i++){
        double x = (random()%1000000), y=(random()%1000000);
        point pn(x,y);
        ps.push_back(pn);
    }

}
#endif //PARTA_TESTCASE_GENERATOR_H
