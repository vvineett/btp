#include <iostream>
#include <vector>

#include "Vector.h"

using namespace std;


int main(int argc, char** argv) {
	
	int num = 10;

	vector<Vector> position(num);
	vector<Vector> velocity(num);

	double timeInterval = 0.01;

	

	vector<Vector> positionN(num);
	vector<Vector> positionNplus1(num);
	vector<Vector> velocityN(num);
	vector<Vector> velocityNhalf(num);

	vector<double> masses(num);
	vector<vector<Vector> > forces(num);

	

	return 0;
}