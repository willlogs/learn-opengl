#include "engine/common.h"
#include "engine/engine.cpp"

using namespace std;

int main(){
	engine the_engine = engine();
	cout << "running main loop" << endl;
	the_engine.runloop();
}