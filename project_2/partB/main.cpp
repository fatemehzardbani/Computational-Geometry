//
// Created by Administrator on 2019/10/22.
//

#include "quick_hull.h"
#include "../partA/geometry_base.h"
#include "../partA/testcase_generator.h"

using namespace std;

int main(){
    vector<point> ps;

    for( int n=64; n<= (20000000);n=n*5/4) {
        generate_random_on2curve(n, ps, 50000);
        cout<< n<<endl;
        polygon_convex ans = Quick_Hull(ps);
        cout << ans.P.size() << "\n";
        // ans.print();
    }

    return 0;

    return 0;
}