#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <string>
#include <fstream>
#include<iostream>
#include<algorithm>
#include<queue>
#include<vector>
#include "partA/geometry_base.h"
#include "partA/testcase_generator.h"

int S = 100;

using namespace std;

#define CLOCK CLOCK_PROCESS_CPUTIME_ID

// returns the difference in milliseconds. 
// You can change this if you want. 
long timespec_diff(struct timespec *strt, struct timespec *stp) {
    return (stp->tv_sec-strt->tv_sec-1)*1000+(1000000000+stp->tv_nsec-strt->tv_nsec)/1000000;
}

struct timespec ptim,ctim;

struct Point{
    double x, y;
};

struct LineSegment{
    Point start, end;
};

// int POINT_COUNT = 1000;
// Point points[1000];
// int hullBitMap[1000];
// int hullIndexes[1000];
int POINT_COUNT;
Point *points;
int *hullBitMap;
int *hullIndexes;

int hullPointCount = 0, leftmostindex = 0;

void setPointsInASquare2(){
    double x, y;
    for(int i=0; i <POINT_COUNT; i++ ){
        x = rand() % S; y = rand() % S;
        points[i].x = x; points[i].y = y;
        hullBitMap[i] = 0;
        hullIndexes[i] = -1;
    }
}

void setPointsOnxx22(){
    double x, y;
    for(int i=0; i <POINT_COUNT; i++ ){
        x = rand() % S; y = x * x;
        points[i].x = x; points[i].y = y;
        hullBitMap[i] = 0;
        hullIndexes[i] = -1;
    }
}

void setPointsInACircle2(){
    double x, y;
    int count = 0;
    for(int i=0; i <POINT_COUNT; i++ ){
        hullIndexes[i] = -1;
    }
    while(count < POINT_COUNT){
        x = rand() % S; y = rand() % S;
        if((x * x + y * y) < 10000){
            points[count].x = x; points[count].y = y;
            hullBitMap[count] = 0;
            count++;
        }
    }
}

void init(vector<point> ps){
    POINT_COUNT = ps.size();
    points = new Point[POINT_COUNT];
    hullBitMap = new int[POINT_COUNT]; hullIndexes = new int[POINT_COUNT];

    for(int i=0; i <ps.size(); i++ ){
        hullIndexes[i] = -1;
        hullBitMap[i] = 0;
        points[i].x = ps[i].x; points[i].y = ps[i].y;
    }
}


double getAngleBetweenLines(LineSegment ls1, LineSegment ls2){
    double angle1 = atan2((ls1.start.y - ls1.end.y), (ls1.start.x - ls1.end.x));
    double angle2 = atan2((ls2.start.y - ls2.end.y), (ls2.start.x - ls2.end.x));
    // double result = (angle2 - angle1) * 180 / 3.14;
    double result = angle2 - angle1;
    if(result < 0) result += 6.28319;
    // if(result > 180) result = 360 - result;
    
    return result;
}

Point getLeftmostPoint(){
    Point current_min = {100000000, 0};
    for(int i=0; i < POINT_COUNT; i++){
        if(points[i].x < current_min.x){
            current_min.x = points[i].x;
            current_min.y = points[i].y;
            leftmostindex = i;
        }
    }
    return current_min;
}

void calculateConvexHull(){
    Point q1 = getLeftmostPoint();
    Point temp_r = {q1.x, 500};
    LineSegment r = {q1, temp_r};
    Point pivot = q1;
    hullIndexes[hullPointCount] = leftmostindex;
    hullBitMap[leftmostindex] = 0;
    hullPointCount ++;
    double currentAngle;
    double currentMin = 100000;
    int currentPivotIndex = leftmostindex, currentMinIndex;

    do
    {
        currentMin =10000; 
        for(int i=0; i< POINT_COUNT; i++){
            if(hullBitMap[i] == 0 && !(pivot.x == points[i].x && pivot.y == points[i].y)){
                LineSegment pv = {pivot, points[i]};
                currentAngle = getAngleBetweenLines(r, pv);
                if (currentAngle < currentMin){
                    
                    currentMinIndex = i;
                    currentMin = currentAngle;
                }
            }
            
        }
        

        hullBitMap[currentMinIndex] = 1;
        r.start = pivot;
        r.end = points[currentMinIndex];
        pivot = points[currentMinIndex];
    } while ((pivot.x != q1.x) || (pivot.y != q1.y));

}



int main(){

    vector<point> ps;
    int n;
    cin>>n;
    generate_random(n,ps);

    init(ps);

    clock_gettime(CLOCK,&ptim);
    calculateConvexHull();
    clock_gettime(CLOCK,&ctim);
    int number_of_points_on_hull = 0;
    for(int i=0; i< POINT_COUNT; i++) number_of_points_on_hull += hullBitMap[i];
    printf("\n time Elapsed: %ld milliseconds hull_points: %d\n", timespec_diff(&ptim,&ctim), number_of_points_on_hull);


    // printf("square:\n");
    // setPointsInASquare2();
    // clock_gettime(CLOCK,&ptim);
    // calculateConvexHull();
    // clock_gettime(CLOCK,&ctim);
    // printf("\n time Elapsed: %ld milliseconds\n", timespec_diff(&ptim,&ctim));


    // printf("y = x2:\n");
    // setPointsOnxx22();
    // clock_gettime(CLOCK,&ptim);
    // calculateConvexHull();
    // clock_gettime(CLOCK,&ctim);
    // printf("\n time Elapsed: %ld milliseconds\n", timespec_diff(&ptim,&ctim));

    // printf("circle:\n");
    // setPointsInACircle2();
    // clock_gettime(CLOCK,&ptim);
    // calculateConvexHull();
    // clock_gettime(CLOCK,&ctim);
    // printf(" time Elapsed: %ld milliseconds\n", timespec_diff(&ptim,&ctim));

    return 0;
}


