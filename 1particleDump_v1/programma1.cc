#include<iostream>
#include<fstream>

using namespace std;

int read (ifstream& file1, float& x1,
	 float& y1, float& z1, int c1[10],
	float px1[10], float py1[10], float pz1[10]);

void dump (int id2, int n2, float x2, float y2,
	float z2, int c2[10], float px2[10], float py2[10], float pz2[10]);

int main ( int argc, char* argv[] ) {

const char* file = argv[1];
ifstream inputfile (file);

int id;
float x;
float y;
float z;
int n;
int c[10];
float px[10];
float py[10];
float pz[10];

while (inputfile >> id) {
	n = read(inputfile, x, y, z, c, px, py, pz);
	dump(id, n, x, y, z, c, px, py, pz);
	}

return 0;
}

int read (ifstream& file1, float& x1,
	 float& y1, float& z1, int c1[10],
	float px1[10], float py1[10], float pz1[10]) {

int n1, id1;
file1 >> id1 >> x1 >> y1 >> z1 >> n1;
for (int k=0; k<n1; k++) 
	file1 >> c1[k] >> px1[k] >> py1[k] >> pz1[k];

return n1;
}

void dump (int id2, int n2, float x2, float y2,
	float z2, int c2[10], float px2[10], float py2[10], float pz2[10]) {

cout << id2 << endl;
cout << x2 <<  ' ' << y2 << ' ' << z2 << endl;
cout << n2 << endl;

for(int k=0; k<n2; k++) 
	cout << c2[k] << ' ' << px2[k] << ' ' << py2[k] << ' ' << pz2[k] << endl;
}
















	
