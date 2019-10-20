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


#ifdef __unix__
#define CLOCK CLOCK_PROCESS_CPUTIME_ID
long timespec_diff(struct timespec* strt, struct timespec* stp) {
	return (stp->tv_sec - strt->tv_sec - 1) * 1000 + (1000000000 + stp->tv_nsec - strt->tv_nsec) / 1000000;
}


struct timespec ptim, ctim;
#endif
using namespace std;
using namespace std;
const double eps = 1e-9;

int dcmp(double x) {
	if (fabs(x) < eps)
		return 0;
	else
		return x > 0 ? 1 : -1;
}

class point {
public:
	double x, y;
	point() {}
	point(double a, double b) :x(a), y(b) {}
	point operator +(point& a) {
		return point(x + a.x, y + a.y);
	}
	point operator -(point& a) {
		return point(x - a.x, y - a.y);
	}
	bool operator ==(point& a) {
		return !dcmp(x - a.x) && !dcmp(y - a.y);
	}
	bool operator <(point& a) {
		return dcmp(x - a.x) == -1 || !dcmp(x - a.x) && dcmp(y - a.y) == -1;
	}
	point operator *(double& a)
	{
		return point(x * a, y * a);
	}

	point operator /(double& a)
	{
		return point(x / a, y / a);
	}

	double mo() {
		return sqrt(x * x + y * y);
	}
};

double dot(point& a, point& b) {
	return a.x * b.x + a.y * b.y;
}
double dist(point& a, point& b) {
	return (a - b).mo();
}
double cross(point& a, point& b) {
	return a.x * b.y - a.y * b.x;
}


class line {
public:
	point s, t;
	line() {}
	line(point a, point b) :s(a), t(b) {}
	int ccw(point& a) {
		point v1 = t - s;
		point v2 = a - s;
		return dcmp(cross(v1, v2));
	}
	double distance2point(point& a) {
		point v1 = t - s, v2 = a - s, v3 = a - t;
		if (dcmp(dot(v1, v2)) < 0)
			return v2.mo();
		else if (dcmp(dot(v1, v3)) > 0)
			return v3.mo();
		else
			return fabs(cross(v1, v2)) / v1.mo();
	}
};

vector<point> quickh(vector<point>& v, line& l) {
	vector<point> res;
	int id = -1;
	int sz = v.size();
	double max_dist = 0.0;
	for (int i = 0; i < sz; i++) {
		point& p = v[i];
		if (l.ccw(p) > 0) {
			double tmpd = l.distance2point(p);
			if (dcmp(tmpd - max_dist) > 0) {
				max_dist = tmpd;
				id = i;
			}
		}
	}
	res.push_back(l.t);
	if (id != -1) {
		point c = v[id];
		vector<point> lv, rv;
		line ll(l.s, c), rl(c, l.t);
		for (int i = 0; i < sz; i++) {
			point& p = v[i];
			if (ll.ccw(p) > 0) lv.push_back(p);
			if (rl.ccw(p) > 0) rv.push_back(p);
		}
		vector<point> left = quickh(lv, ll);
		vector<point> right = quickh(rv, rl);
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
vector<point> quick_hull(vector<point>& v) {
	int sz = v.size();
	point& min = v[0], max = v[0];
	for (int i = 1; i < sz; i++) {
		if (v[i] < min) {
			min = v[i];
		}
		if (max < v[i]) {
			max = v[i];
		}
	}
	line rl(min, max), ll(max, min);
	vector<point> upper_hull = quickh(v, rl);
	vector<point> lower_hull = quickh(v, ll);
	vector<point>& hull = upper_hull;
	hull.insert(hull.end(), lower_hull.begin() + 1, lower_hull.end() - 1);
	return hull;
}

int main(int argc, char** argv) {
	ifstream in;
	ofstream out;
	if (argc > 1) {
		in.open(argv[1], ios::in);
		out.open(argv[2], ios::trunc);
	}
	else {
		in.open("test_quickhull.in",ios::in);
		out.open("test_quickhull.out",ios::trunc);
	}
	int n;
	vector<point> ps;
	while (in>>n){
		double x, y;
		ps.clear();
		for (int i = 0; i < n; i++) {
			in >> x >> y;
			ps.push_back(point(x, y));
		}
#ifdef __unix__
		clock_gettime(CLOCK, &ptim);
#endif

		vector<point> ans = quick_hull(ps);
#ifdef __unix__
		clock_gettime(CLOCK, &ctim);

		out << " time Elapsed: " << timespec_diff(&ptim, &ctim) << " milliseconds\n";
#endif
		int sz = ans.size();
		out << sz << "\n";
		for (int i = 0; i < sz; i++) {
			out << ans[i].x << " " << ans[i].y << "\n";
		}
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}

