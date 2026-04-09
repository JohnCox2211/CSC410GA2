#include "genome.h"
#include "cassert"
#include "iostream"
using namespace std;

// tests allocate and initialization
void testAllocateInit(){
  genome g;
  g.allocate(5);

  // should init all values to 0
  for(int i = 0; i < 5; i++){
    assert(g.getRed(i) == 0);
    assert(g.getGreen(i) == 0);
    assert(g.getBlue(i) == 0);
  }

  cout << "testAllocateInit passed" << endl;
}

// tests allocating no space
void testAllocateZero(){
  genome g;
  g.allocate(0);

  assert(g.getBlue(0) == -1);

  cout << "testAllocateZero passed" << endl;
}

// tests setter and getter methods
void testSettersGetters(){
  genome g;
  g.allocate(3);

  g.setRed(0, 100);
  g.setGreen(1, 150);
  g.setBlue(2, 200);

  assert(g.getRed(0) == 100);
  assert(g.getGreen(1) == 150);
  assert(g.getBlue(2) == 200);

  cout << "testSettersGetters passed" << endl;
}

// tests out of bounds access
void testOOBaccess() {
  genome g;
  g.allocate(2);

  // invalid indices return -1
  assert(g.getRed(-1) == -1);
  assert(g.getGreen(5) == -1);
  assert(g.getBlue(100) == -1);

  // setters should be fine
  g.setRed(-1, 50);
  g.setGreen(10, 60);
  g.setBlue(20, 70);

  cout << "testOOBaccess passed" << endl;
}

// test number range from randomize method
void testRandomize(){
  genome g;
  g.allocate(10);
  g.randomize();

  for(int i = 0; i < 10; i++){
    int red = g.getRed(i);
    int green = g.getGreen(i);
    int blue = g.getBlue(i);

    assert(red >= 0 && red <= 255);
    assert(green >= 0 && green <= 255);
    assert(blue >= 0 && blue <= 255);
  }

  cout << "testRandomize passed" << endl;
}

// tests deallocate method
void testDeallocate(){
  genome g;
  g.allocate(5);
  g.deallocate();

  // should fail safely
  assert(g.getRed(0) == -1);

  //make sure allocate still works
  g.allocate(3);
  assert(g.getRed(0) == 0);

  cout << "testDeallocate passed" << endl;
}

int main(){
  testAllocateInit();
  testSettersGetters();
  testOOBaccess();
  testRandomize();
  testDeallocate();

  cout << "All tests passed" << endl;
  return 0;
}
