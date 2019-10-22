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

void generate_random_square(int n,vector<point> & ps, long  l, long h)
{
    ps.clear(); ps.resize(0);
    for(int i=0;i<n;i++){
        double x = (((random()+17)+2*l)%l), y=((random()+2*h)%h);
        point pn(x,y);
        ps.push_back(pn);
    }
}

void generate_random_incircle (int n, vector<point> & ps, long  r)
{
    ps.clear(); ps.resize(0);
    for(int i=0;i<n;i++){
        double x = ((random()+2*r)%r); double y= (random()% int(sqrt( double (r*r)- x*x)));
        point pn(x,y);
        ps.push_back(pn);
    }

}

void generate_random_on2curve (int n, vector<point> & ps, long  r)
{
    ps.clear(); ps.resize(0);
    for(int i=0;i<n;i++){
        double x = ((random()+2*r)%r); double y= x*x;
        if( int(x) % 2 ==1) x= x*(-1);
        point pn(x,y);
        ps.push_back(pn);
    }

}
#endif //PARTA_TESTCASE_GENERATOR_H
