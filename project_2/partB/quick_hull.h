//
// Created by Administrator on 2019/10/22.
//

#ifndef TEST_QUICK_HULL_H
#define TEST_QUICK_HULL_H

#include<iostream>
#include<fstream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<queue>
#include<vector>
#include<ctime>
#include "../partA/geometry_base.h"

using namespace std;
const double EPS = 1e-9;

int dcmp(double x) {
    if (fabs(x) < EPS)
        return 0;
    else
        return x > 0 ? 1 : -1;
}

class Point {
public:
    double x, y;
    Point() {}
    Point(double a, double b) :x(a), y(b) {}
    Point operator +(Point& a) {
        return Point(x + a.x, y + a.y);
    }
    Point operator -(Point& a) {
        return Point(x - a.x, y - a.y);
    }
    bool operator ==(Point& a) {
        return !dcmp(x - a.x) && !dcmp(y - a.y);
    }
    bool operator <(Point& a) {
        return dcmp(x - a.x) == -1 || !dcmp(x - a.x) && dcmp(y - a.y) == -1;
    }
    Point operator *(double& a)
    {
        return Point(x * a, y * a);
    }

    Point operator /(double& a)
    {
        return Point(x / a, y / a);
    }

    double mo() {
        return sqrt(x * x + y * y);
    }
};

double Dot(Point& a, Point& b) {
    return a.x * b.x + a.y * b.y;
}
double Dist(Point& a, Point& b) {
    return (a - b).mo();
}
double cross(Point& a, Point& b) {
    return a.x * b.y - a.y * b.x;
}


class Line {
public:
    Point s, t;
    Line() {}
    Line(Point a, Point b) :s(a), t(b) {}
    int ccw(Point& a) {
        Point v1 = t - s;
        Point v2 = a - s;
        return dcmp(cross(v1, v2));
    }
    double Distance2Point(Point& a) {
        Point v1 = t - s, v2 = a - s, v3 = a - t;
        if (dcmp(Dot(v1, v2)) < 0)
            return v2.mo();
        else if (dcmp(Dot(v1, v3)) > 0)
            return v3.mo();
        else
            return fabs(cross(v1, v2)) / v1.mo();
    }
};

vector<Point> quickh(vector<Point>& v, Line& l) {
    vector<Point> res;
    int id = -1;
    int sz = v.size();
    //cout << sz << "\n";
    double max_Dist = 0.0;
    for (int i = 0; i < sz; i++) {
        Point& p = v[i];
        //cout << p.x << " " << p.y << " " << l.ccw(p) << "\n";
        if (l.ccw(p) > 0) {
            double tmpd = l.Distance2Point(p);
            if (dcmp(tmpd - max_Dist) > 0) {
                max_Dist = tmpd;
                id = i;
            }
        }
    }
    res.push_back(l.t);
    if (id != -1) {
        Point c = v[id];
        vector<Point> lv, rv;
        Line ll(l.s, c), rl(c, l.t);
        for (int i = 0; i < sz; i++) {
            Point& p = v[i];
            if (ll.ccw(p) > 0) lv.push_back(p);
            if (rl.ccw(p) > 0) rv.push_back(p);
        }
        vector<Point> left = quickh(lv, ll);
        vector<Point> right = quickh(rv, rl);
        if (right.size() > 2) {
            res.insert(res.end(), right.begin() + 1, right.end() - 1);
        }
        res.push_back(c);
        if (left.size() > 2) {
            res.insert(res.end(), left.begin() + 1, left.end() - 1);
        }
    }
    res.push_back(l.s);
    return res;
}
vector<Point> quick_hull(vector<Point>& v) {
    int sz = v.size();
    Point min = v[0], max = v[0];
    for (int i = 1; i < sz; i++) {
        if (v[i] < min) {
            min = v[i];
        }
        if (max < v[i]) {
            max = v[i];
        }
    }
    Line rl(min, max), ll(max, min);
    vector<Point> upper_hull = quickh(v, rl);
    vector<Point> lower_hull = quickh(v, ll);
    vector<Point>& hull = upper_hull;
    hull.insert(hull.end(), lower_hull.begin() + 1, lower_hull.end() - 1);
    return hull;
}

polygon_convex Quick_Hull(vector<point> &v){
    vector<Point> in,out;
    int sz = v.size();
    for (int i = 0;i < sz;i++){
        in.push_back(Point(v[i].x,v[i].y));
    }
    out = quick_hull(in);
    sz = out.size();
    polygon_convex res;
    for (int i = 0; i < sz;i++ ){
        res.P.push_back(point(out[i].x,out[i].y));
    }
    return res;
}

#endif //TEST_QUICK_HULL_H
