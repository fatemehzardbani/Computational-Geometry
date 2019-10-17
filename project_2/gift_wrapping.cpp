#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <string>
#include <fstream>


using namespace std;

#define CLOCK CLOCK_PROCESS_CPUTIME_ID

// returns the difference in milliseconds. 
// You can change this if you want. 
long timespec_diff(struct timespec *strt, struct timespec *stp) {
    return (stp->tv_sec-strt->tv_sec-1)*1000+(1000000000+stp->tv_nsec-strt->tv_nsec)/1000000;
}

struct Point{
    int x, y;
};

struct LineSegment{
    Point start, end;
};

int POINT_COUNT = 100;
Point points[100];
int hullBitMap[100];
int hullIndexes[100];

int hullPointCount = 0, leftmostindex = 0;


void setPointsInASquare(){
    // in a square

    std::ifstream file("test_cases/square.txt");
    int x;
    int y, count =0;

    while(file >> x >> y) {
        
        points[count].x = x; points[count].y = y;
        hullBitMap[count] = 0;
        count++;
    }

    

    // init the hull
    for(int i = 0; i < POINT_COUNT; i++){
        hullIndexes[i] = -1;
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
    setPointsInASquare();
    printf("points\n");
    for(int i = 0; i < POINT_COUNT; i++){
        printf("%d, ", points[i].x);
    }
    printf("\n");
    printf("\n");
    printf("\n");
    for(int i = 0; i < POINT_COUNT; i++){
        printf("%d, ", points[i].y);
    }
    calculateConvexHull();
    
    printf("\n");
    printf("hull\n");
    printf("\n");
    printf("\n");
    for(int i = 0; i < POINT_COUNT; i++){
        if(hullBitMap[i] == 1){printf("%d, ", points[i].x);}
    }
    printf("\n");
    printf("\n");
    printf("\n");
    for(int i = 0; i < POINT_COUNT; i++){
        if(hullBitMap[i] == 1){printf("%d, ", points[i].y);}
    }

   

    return 0;
}


