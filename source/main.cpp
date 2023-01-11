#include "engine/common.h"
#include "engine/engine.cpp"

using namespace std;

int main(){
	engine the_engine = engine();
	the_engine.runloop();
}