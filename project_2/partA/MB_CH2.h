//
// Created by Wbs on 2019-10-22.
//

#ifndef PARTA_MB_CH2_H
#define PARTA_MB_CH2_H
#include"geometry_base.h"
#include<vector>
#include<cmath>

vector<point> mbch2_upper(vector<point> ps, int xm){
    vector<point> res;
    int sz = ps.size();
    int ep1,ep2;
    double a = (ps[0].y - ps[1].y) / (ps[0].x - ps[1].x);
    double b = ps[0].y - ps[0].x * a;
    double ym = a * xm + b;
    for (int i = 2; i < sz; i ++) {
        if (ps[i].y > a * ps[i].x + b){
            double tmpep,tmpa,tmpb,tmpym,tmpmin = 1000000.0;
            for (int j = 0; j < i; j ++) {
                tmpa = (ps[j].y - ps[i].y) / (ps[j].x - ps[i].x);
                tmpb = (ps[i].y - ps[i].x * a);
                tmpym = tmpa * xm + tmpb;
                if (tmpym > ym && tmpym < tmpmin) {
                    tmpmin = tmpym;
                    tmpep = j;
                }
            }
            a = tmpa;
            b = tmpb;
            ym = tmpym;
            ep1 = i;
            ep2 = tmpep;
        }
    }
    if (comp_less(ps[ep2],ps[ep1])){
        ep1 ^= ep2;
        ep2 ^= ep1;
        ep1 ^= ep2;
    }
    vactor<point> pr,pl;
    for (int i = 0;i < sz; i ++) {
        if (ps[i].x < ps[ep1].x){
            pl.push_back(ps[i]);
        }
        else if (ps[i].x > ps[ep2].x){
            pr.push_back(ps[i]);
        }
    }
    pl.push_back(ps[ep1]);
    pr.push_back(ps[ep2]);
    res.push_back(ps[ep1]);
    res.push_back(ps[ep2]);
    double xml,xmr;
    if (pl.size() > 2) {

        for (int i = 0; i < 3; i ++){
            if (pl[i].x >= pl[(i + 1) % 3].x && pl[i].x <= pl[(i+2) %3].x || pl[i].x <= pl[(i + 1) % 3].x && pl[i].x >= pl[(i+2) %3].x){
                xml = pl[i].x;
                break;
            }
        }
        vector<point> resl = mbch2_upper(pl, xml);
        res.insert(res.end(),resl.begin(),resl.end());
    } else{
        res.push_back(pl[0]);
    }
    if (pr.size() > 2) {
        for (int i = 0; i < 3; i ++){
            if (pr[i].x >= pr[(i + 1) % 3].x && pr[i].x <= pr[(i+2) %3].x || pr[i].x <= pr[(i + 1) % 3].x && pr[i].x >= pr[(i+2) %3].x){
                xmr= pr[i].x;
                break;
            }
        }
        vector<point> resr = mbch2_upper(pr, xmr);
        res.insert(res.end(),resr.begin(),resr.end());
    } else{
        res.push_back(pr[0]);
    }
    res.erase(unique(res.begin(),res.end()),res.end());
    return res;
}

vector<point> mbch2_below(vector<point> ps, int xm){
    vector<point> res;
    int sz = ps.size();
    int ep1,ep2;
    double a = (ps[0].y - ps[1].y) / (ps[0].x - ps[1].x);
    double b = ps[0].y - ps[0].x * a;
    double ym = a * xm + b;
    for (int i = 2; i < sz; i ++) {
        if (ps[i].y < a * ps[i].x + b){
            double tmpep,tmpa,tmpb,tmpym,tmpmin = 1000000.0;
            for (int j = 0; j < i; j ++) {
                tmpa = (ps[j].y - ps[i].y) / (ps[j].x - ps[i].x);
                tmpb = (ps[i].y - ps[i].x * a);
                tmpym = tmpa * xm + tmpb;
                if (tmpym < ym && tmpym > tmpmin) {
                    tmpmin = tmpym;
                    tmpep = j;
                }
            }
            a = tmpa;
            b = tmpb;
            ym = tmpym;
            ep1 = i;
            ep2 = tmpep;
        }
    }
    if (comp_less(ps[ep2],ps[ep1])){
        ep1 ^= ep2;
        ep2 ^= ep1;
        ep1 ^= ep2;
    }
    vactor<point> pr,pl;
    for (int i = 0;i < sz; i ++) {
        if (ps[i].x < ps[ep1].x){
            pl.push_back(ps[i]);
        }
        else if (ps[i].x > ps[ep2].x){
            pr.push_back(ps[i]);
        }
    }
    pl.push_back(ps[ep1]);
    pr.push_back(ps[ep2]);
    res.push_back(ps[ep1]);
    res.push_back(ps[ep2]);
    double xml,xmr;
    if (pl.size() > 2) {

        for (int i = 0; i < 3; i ++){
            if (pl[i].x >= pl[(i + 1) % 3].x && pl[i].x <= pl[(i+2) %3].x || pl[i].x <= pl[(i + 1) % 3].x && pl[i].x >= pl[(i+2) %3].x){
                xml = pl[i].x;
                break;
            }
        }
        vector<point> resl = mbch2_upper(pl, xml);
        res.insert(res.end(),resl.begin(),resl.end());
    } else{
        res.push_back(pl[0]);
    }
    if (pr.size() > 2) {
        for (int i = 0; i < 3; i ++){
            if (pr[i].x >= pr[(i + 1) % 3].x && pr[i].x <= pr[(i+2) %3].x || pr[i].x <= pr[(i + 1) % 3].x && pr[i].x >= pr[(i+2) %3].x){
                xmr= pr[i].x;
                break;
            }
        }
        vector<point> resr = mbch2_upper(pr, xmr);
        res.insert(res.end(),resr.begin(),resr.end());
    } else{
        res.push_back(pr[0]);
    }
    res.erase(unique(res.begin(),res.end()),res.end());
    return res;
}

polygon_convex MB_CH2(vector<point> ps){
    int sz = ps.size();
    int maxp = 0,minp = 0;
    for (int i = 1; i < sz; i ++) {
        if (comp_less(ps[i], ps[minp])) {
            minp = i;
        }
        if (comp_less(ps[maxp], ps[i])) {
            maxp = i;
        }
    }
    double midx = (ps[maxp].x + ps[minp].x) / 2;
    int mid = 0;
    double dism = fabs(ps[0].x - midx);
    for (int i = 1; i < sz; i ++){
        if (fabs(ps[i].x - ps[mid].x) < dism) {
            dism = fabs(ps[i].x - ps[mid].x);
            mid = i;
        }
    }
    line l(ps[minp],ps[maxp]);
    vector<point> pu,pb;
    for (int i = 0; i < sz; i ++){
        if (det(ps[maxp] - ps[minp], ps[i] - ps[minp]) >= 0){
            pu.push_back(ps[i]);
        }
        else if (det(ps[maxp] - ps[minp], ps[i] - ps[minp]) < 0){
            pb.push_back(ps[i]);
        }

    }
    vector<point> hull_upper = mbch2_upper(pu,ps[mid].x);
    vector<point> hull_below = mbch2_below(pb,ps[mid].x);
    vector<point> hull;
    hull.insert(hull.end(),hull_upper.begin(),hull_upper.end());
    hull.insert(hull.end(),hull_below.begin(),hull_below.end());
    hull.erase(unique(hull.begin(),hull.end()),hull.end());
    polygon_convex res;
    res.P = hull;
    return res;
}
#endif //PARTA_MB_CH2_H
