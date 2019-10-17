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
// Point hull[100];
int hullIndexes[100];

int hullPointCount = 0, leftmostindex = 0;


void setPointsInASquare(){
    // in a square

    std::ifstream file("test_cases/square.txt");
    int x;
    int y, count =0;

    while(file >> x >> y) {
        // std::cout << str << ' ' << i << std::endl;
        // printf("%d , %d \n", x, y);
        points[count].x = x; points[count].y = y;
        hullBitMap[count] = 0;
        count++;
    }

    // for(int i = 0; i < POINT_COUNT; i++){
    //     points[i].x = rand() % 10;
    //     points[i].y = rand() % 10;
    // }

    // init the hull
    for(int i = 0; i < POINT_COUNT; i++){
        // hull[i].x = -1;
        // hull[i].y = -1;
        hullIndexes[i] = -1;
    }

    // printf("finished generating points");
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
    printf("initial pivot x = %d, y = %d", pivot.x, pivot.y);
    // hull[hullPointCount] = pivot;
    hullIndexes[hullPointCount] = leftmostindex;
    hullBitMap[leftmostindex] = 0;
    hullPointCount ++;
    double currentAngle;
    double currentMin = 100000;
    int currentPivotIndex = leftmostindex, currentMinIndex;
    // bool alreadyInHull = false;
    
    // printf("just before do while");

    do
    {
        // Point currentMinAnglePoint;
        // printf("in while\n");
        currentMin =10000; 
        for(int i=0; i< POINT_COUNT; i++){
            if(hullBitMap[i] == 0 && !(pivot.x == points[i].x && pivot.y == points[i].y)){
                LineSegment pv = {pivot, points[i]};
                currentAngle = getAngleBetweenLines(r, pv);
                // printf("calc min anlge point: currentPivotIndex = %d,  i= %d, x=%d, y=%d, angle=%f, cmin=%f \n",currentPivotIndex, i, points[i].x, points[i].y, currentAngle, currentMin);
                if (currentAngle < currentMin){
                    // printf("switching\n");
                    
                    // currentMinAnglePoint = points[i];
                    currentMinIndex = i;
                    currentMin = currentAngle;
                }
            }
            // else{printf("already in hull\n");}
            
        }
        // currentPivotIndex = currentMinIndex;
        // printf("min angle point: %d, %d,\n", points[currentMinIndex].x, points[currentMinIndex].y);
        // printf("\n");
        // printf("\n");
        // printf("\n");
        // for(int i = 0; i < POINT_COUNT; i++){
        //     if(hullBitMap[i] == 1){printf("%d, ", points[i].x);}
        //     // printf("%d, ", points[hullIndexes[i]].x);
        // }
        // printf("\n");
        // printf("\n");
        // printf("\n");
        // for(int i = 0; i < POINT_COUNT; i++){
        //     if(hullBitMap[i] == 1){printf("%d, ", points[i].y);}
        //     // printf("%d, ", points[hullIndexes[i]].y);
        // }
        // hull[hullPointCount] = currentMinAnglePoint;
        // hullIndexes[hullPointCount] = currentMinIndex;
        // hullPointCount ++;

        hullBitMap[currentMinIndex] = 1;
        r.start = pivot;
        r.end = points[currentMinIndex];
        // printf("here here: %d, %d\n", r.start.x, r.start.y);
        pivot = points[currentMinIndex];
        // printf("here here here: %d, %d\n", r.start.x, r.start.y);
        // printf("pivothere here here: %d, %d\n", pivot.x, pivot.y);
        // printf("q1 here here here: %d, %d\n", q1.x, q1.y);
        
    } while ((pivot.x != q1.x) || (pivot.y != q1.y));

}



int main(){
    setPointsInASquare();
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
    printf("\n");
    printf("\n");
    for(int i = 0; i < POINT_COUNT; i++){
        if(hullBitMap[i] == 1){printf("%d, ", points[i].x);}
        // printf("%d, ", points[hullIndexes[i]].x);
    }
    printf("\n");
    printf("\n");
    printf("\n");
    for(int i = 0; i < POINT_COUNT; i++){
        if(hullBitMap[i] == 1){printf("%d, ", points[i].y);}
        // printf("%d, ", points[hullIndexes[i]].y);
    }

    // Point pi = {18, 95};
    // Point p_corr = {0, 91}, p_chosen = {7,91};
    // LineSegment rv = {{48, 99}, pi};
    // LineSegment ppcorr = {pi, p_corr};
    // LineSegment ppchosen = {pi, p_chosen};

    // float ang1 = getAngleBetweenLines(rv, ppcorr), ang2 = getAngleBetweenLines(rv, ppchosen);

    // printf("corr: %f, chosen: %f", ang1, ang2);

    return 0;
}


