#include<iostream>
#include<fstream>


using namespace std;

struct Particle {
	int c;
	float px, py, pz;
	};

struct Event {
	int id, n;
	float x, y, z;
	Particle** pp;
	};

const Event* read (ifstream& file1);
void dump (const Event& ev);
void clear (const Event* ev);

int main ( int argc, char* argv[] ) {

const Event* ev;

const char* file = argv[1];
ifstream inputfile (file);

while ((ev = read (inputfile)) ) {
	if (!ev) return 0;	
	
	dump (*ev);
	clear(ev);
	
	}

return 0;
}

const Event* read (ifstream& file1) {

Event* ev1;

int id1, n1;
float x1, y1, z1;

if (file1 >> id1 >> x1 >> y1 >> z1 >> n1)
	ev1 = new Event;
	
else return 0;

ev1 -> id = id1;
ev1 -> x = x1;
ev1 -> y = y1;
ev1 -> z = z1;
ev1 -> n = n1;

int c[n1];
float px[n1], py[n1], pz[n1];

ev1 -> pp = new Particle*[n1];
for (int i=0; i<n1; i++) {
	ev1 -> pp[i] = new Particle;
	file1 >> c[i] >> px[i] >> py[i] >> pz[i];	
	ev1 -> pp[i] -> c = c[i];
	ev1 -> pp[i] -> px = px[i];
	ev1 -> pp[i] -> py = py[i];	
	ev1 -> pp[i] -> pz = pz[i];
	}

return ev1;
}

void dump (const Event& ev1) {

cout << ev1.id << endl;
cout << ev1.x <<  ' ' << ev1.y << ' ' << ev1.z << endl;
cout << ev1.n << endl;

for (int i=0; i<ev1.n; i++) 
	cout << ev1.pp[i]-> c << ' ' << ev1.pp[i]-> px << ' ' << ev1.pp[i]-> py << ' ' << ev1.pp[i]-> pz << endl;
}

void clear (const Event* ev) {

for (int i=0; i<ev->n; i++) 
	delete ev->pp[i];
	
delete[] ev->pp;
delete ev;	
	

}











