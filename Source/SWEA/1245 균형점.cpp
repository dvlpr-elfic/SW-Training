
/**
 * @author : Jihoon Jang
 */

#include <stdio.h>
#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

typedef struct BALANCEDPOINT
{
	double point;
	double mass;
	BALANCEDPOINT(double _p, double _m)
	{
		point = _p;
		mass = _m;
	}

}BP;

double findBalance(double m1, double m2, double low, double high, vector<BP> &v, int pos)
{
	int k = 100;
	double x1 = low, x2 = high;
	double mid = 0;
	while(k--){
		mid = (high+low)/2.0;
		double FL = 0;
		double FR = 0;
		for(int i=0; i<=pos; i++){
			double d1 = mid - v[i].point;
			FL += (v[i].mass)/(d1*d1);
		}
		for(int i=pos+1; i<v.size(); i++){
			double d2 = v[i].point - mid;
			FR += (v[i].mass)/(d2*d2);
		}
		if(FL > FR)
			low = mid;
		else if(FL < FR)
			high = mid;
		else
			return mid;
	}
	return mid = (high+low)/2.0;
}

int main(void)
{
	setbuf(stdout, NULL);
	//freopen("input.txt", "r", stdin);
	int t;
	scanf("%d", &t);
	for(int tc=1; tc<=t; tc++){
		int n;
		scanf("%d", &n);
		vector<BP> v;
		for(int i=0; i<n; i++){
			double p;
			scanf("%lf", &p);
			v.push_back(BALANCEDPOINT(p, 0.0));
		}
		for(int i=0; i<n; i++)
			scanf("%lf", &(v[i].mass));
		printf("#%d ", tc);
		for(int i=0; i<n-1; i++){
			double ans = findBalance(v[i].mass, v[i+1].mass, v[i].point, v[i+1].point, v, i);
			//cout<<ans<<" ";
			printf("%.10lf ", ans);
		}
		printf("\n");
	}

	return 0;
}
