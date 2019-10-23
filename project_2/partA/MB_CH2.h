//
// Created by Wbs on 2019-10-22.
//

#ifndef PARTA_MB_CH2_H
#define PARTA_MB_CH2_H
#include"geometry_base.h"
#include<vector>
#include<cmath>
#define MAX_D 1e9
#define MIN_D -1e9
vector<point> mbch2_upper(vector<point> ps){
    int sz = ps.size();
    if (sz <= 2){
        return ps;
    }
    vector<point> res;
    vector<point> pl,pr;
    double xm;
    for (int i = 0; i < 3; i ++) {
        if ((ps[i].x >= ps[(i + 1) % 3].x && ps[i].x <= ps[(i + 2) % 3].x) ||
            (ps[i].x <= ps[(i + 1) % 3].x && ps[i].x >= ps[(i + 2) % 3].x)) {
            xm = ps[i].x;
            break;
        }
    }

    for (int i = 0; i < sz; i ++){
        if (ps[i].x < xm){
            pl.push_back(ps[i]);
        } else{
            pr.push_back(ps[i]);
        }
    }
    int epl = 0, epr = 0;
    int szl = pl.size(),szr = pr.size();
    if (szl == 0){
        return ps;
    }
    //cout << sz << " " << szl << " " << szr << "\n";
    for (int i = 0;i < szl; i ++) {
        if (i != epl && cmp(det(pr[epr] - pl[epl],pl[i] - pl[epl])) == 1){
            epl = i;
            for (int j = 0;j < szr; j ++){
                if (j != epr && cmp(det(pr[epr] - pl[epl],pr[j] - pl[epl])) == 1){
                    epr = j;
                }
            }
        }
    }
    for (int j = 0;j < szr; j ++) {
        if (j != epr && cmp(det(pr[epr] - pl[epl],pr[j] - pl[epl])) == 1){
            epr = j;
            for (int i = 0;i < szl; i ++){
                if (i != epl &&cmp(det(pr[epr] - pl[epl],pl[i] - pl[epl])) == 1){
                    epl = i;
                }
            }
        }
    }

    vector<point> pll,prr;
    for (int i = 0;i < szl; i ++){
        if (pl[i].x <= pl[epl].x){
            pll.push_back(pl[i]);
        }
    }
    for (int i = 0;i < szr; i ++){
        if (pr[i].x >= pr[epr].x){
            prr.push_back(pr[i]);
        }
    }
    //cout << sz << " " << szl << " " << szr << " " << pll.size() << " " << prr.size() << "\n";
    vector<point> resl = mbch2_upper(pll);
    vector<point> resr = mbch2_upper(prr);
    res.insert(res.end(),resl.begin(),resl.end());
    res.insert(res.end(),resr.begin(),resr.end());
    sz = res.size();
    bool fl = true,fr = true;
    for (int i = 0; i < sz; i ++){
        if (cmp(res[i].x - pl[epl].x) == 0 && cmp(res[i].y - pl[epl].y) == 0){
            fl = false;
            break;
        }
    }
    for (int i = 0; i < sz; i ++){
        if (cmp(res[i].x - pr[epr].x) == 0 && cmp(res[i].y - pr[epr].y) == 0){
            fr = false;
            break;
        }
    }
    if (fl) res.push_back(pl[epl]);
    if (fr) res.push_back(pr[epr]);
    return res;
}

vector<point> mbch2_below(vector<point> ps){
    int sz = ps.size();
    if (sz <= 2){
        return ps;
    }
    vector<point> res;
    vector<point> pl,pr;
    double xm;
    for (int i = 0; i < 3; i ++) {
        if ((ps[i].x >= ps[(i + 1) % 3].x && ps[i].x <= ps[(i + 2) % 3].x) ||
            (ps[i].x <= ps[(i + 1) % 3].x && ps[i].x >= ps[(i + 2) % 3].x)) {
            xm = ps[i].x;
            break;
        }
    }
    for (int i = 0; i < sz; i ++){
        if (ps[i].x < xm){
            pl.push_back(ps[i]);
        } else{
            pr.push_back(ps[i]);
        }
    }
    int epl = 0, epr = 0;
    int szl = pl.size(),szr = pr.size();
    if (szl == 0){
        return ps;
    }
    for (int i = 0;i < szl; i ++) {
        if (i != epl && cmp(det(pr[epr] - pl[epl], pl[i] - pl[epl])) == -1) {
            epl = i;
            for (int j = 0; j < szr; j++) {
                if (j != epr && cmp(det(pr[epr] - pl[epl], pr[j] - pl[epl])) == -1) {
                    epr = j;
                }
            }
        }
    }
    for (int j = 0;j < szr; j ++) {
        if (j != epr && cmp(det(pr[epr] - pl[epl],pr[j] - pl[epl])) == -1){
            epr = j;
            for (int i = 0;i < szl; i ++){
                if (i != epl && cmp(det(pr[epr] - pl[epl],pl[i] - pl[epl])) == -1){
                    epl = i;
                }
            }
        }
    }
    vector<point> pll,prr;
    for (int i = 0;i < szl; i ++){
        if (pl[i].x <= pl[epl].x){
            pll.push_back(pl[i]);
        }
    }
    for (int i = 0;i < szr; i ++){
        if (pr[i].x >= pr[epr].x){
            prr.push_back(pr[i]);
        }
    }
    vector<point> resl = mbch2_below(pll);
    vector<point> resr = mbch2_below(prr);
    res.insert(res.end(),resl.begin(),resl.end());
    res.insert(res.end(),resr.begin(),resr.end());

    sz = res.size();
    bool fl = true,fr = true;
    for (int i = 0; i < sz; i ++){
        if (res[i] == pl[epl]){
            fl = false;
            break;
        }
    }
    for (int i = 0; i < sz; i ++){
        if (res[i] == pr[epr]){
            fr = false;
            break;
        }
    }
    if (fl) res.push_back(pl[epl]);
    if (fr) res.push_back(pr[epr]);
    return res;
}
polygon_convex MB_CH2(vector<point> ps){
    ps.erase(unique(ps.begin(),ps.end()),ps.end());
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
        else{
            pb.push_back(ps[i]);
        }
    }
    //cout << pu.size() << " " << pb.size() << "\n";
    vector<point> hull_upper = mbch2_upper(pu);
    //cout << hull_upper.size() << "\n";
    vector<point> hull_below = mbch2_below(pb);
    //cout << hull_below.size() << "\n";
    vector<point> hull;
    hull.insert(hull.end(),hull_upper.begin(),hull_upper.end());
    hull.insert(hull.end(),hull_below.begin(),hull_below.end());
    hull.erase(unique(hull.begin(),hull.end()),hull.end());
    polygon_convex res;
    res.P = hull;
    return res;
}
#endif //PARTA_MB_CH2_H
