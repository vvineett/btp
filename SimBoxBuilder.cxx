#include <fstream>
#include <string>

#include "SimBoxBuilder.h"

vector<string> tokenize(string& str);
vector<Particle> fromXYZ(string fileXYZ);

using namespace std;

SimBoxBuilder::SimBoxBuilder() {

}

SimBoxBuilder::SimBoxBuilder(const SimBoxBuilder& other) {

}

SimBoxBuilder::~SimBoxBuilder() {

}

Box SimBoxBuilder::fromParamFile(string fileName, bool random) {
	ifstream in;
	in.open(fileName.c_str());
	
	string fileXYZ;
	Vector a(10,0,0), b(0,10,0), c(0,0,10);

	string line;

	while(getline(in, line)) { 
		vector<string> tokens = tokenize(line);

		if(tokens[0].find(string("topolfile")) != string::npos) {
			fileXYZ = tokens[1];
		}
		else if(tokens[0].find(string("BoxVectors")) != string::npos) {
			double  ai = stod(tokens[1]),
					aj = stod(tokens[2]),
					ak = stod(tokens[3]);
			a = Vector(ai, aj, ak);

			double	bi = stod(tokens[4]),
					bj = stod(tokens[5]),
					bk = stod(tokens[6]);
			b = Vector(bi, bj, bk);

			double	ci = stod(tokens[7]),
					cj = stod(tokens[8]),
					ck = stod(tokens[9]);
			c = Vector(ci, cj, ck);

		}
		else {

		}
	}

	in.close();

	Box box = Box().boxWithEdges(a, b, c);
	if(fileXYZ.compare(string()) == 0 && !random) {
		std::cerr << "No topology file provided!" << std::endl;
		exit(1);
	}
	else if(random) {
		box.addParticles(10, 101);
	}
	else 
		box.addParticles(fromXYZ(fileXYZ));

	return box;
}

vector<Particle> fromXYZ(string fileXYZ) {
	ifstream in;
	in.open(fileXYZ.c_str());

	int numParticles;
	in >> numParticles;

	string comment;
	in >> comment;

	vector<Particle> particles;
	for(int i = 0; i< numParticles; i++) {
		string symbol;
		in >> symbol;

		double x, y, z;
		in >> x >> y >> z;
		Vector pos(x,y,z);
		Vector vel;
		Vector a;

		Particle p(symbol,1,0,0.5, pos, vel, a);
		particles.push_back(p);
	}

	return particles;
}

// int stoi(string& str) {
// 	int num = 0;
// 	bool neg = false;
// 	for(string::iterator it = str.begin(); it!= str.end(); it++) {
// 		if(*it <= '9' && *it >= '0') {
// 			num = (int)(*it - '0') + 10*num;
// 		}
// 		else if(*it == '-') {
// 			neg = true;
// 		}
// 	}

// 	if(neg)
// 		num = -num;

// 	return num;
// }

vector<string> tokenize(string& str) {
	vector<string> tokens;
	string temp;

	// cerr << str <<endl;
	for(string::iterator it = str.begin(); it!=str.end(); it++) {
		// cerr << (int)*it<< "    "<<*it << endl;
		if(*it != '=' && *it != ' ') {
			temp.push_back(*it);
		}
		else if(temp.size() != 0) {
			tokens.push_back(temp);
			temp = string();
		}

	}

	if(tokens.size() == 0) {
		tokens.push_back(string(" "));
	}
	else {
		tokens.push_back(temp);
	}

	return tokens;
}