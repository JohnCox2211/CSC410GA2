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


// NEW TESTS *********************************

// test setmRate and getmRate
void testMutationRate(){
  genome g;

  g.setmRate(0.5);
  assert(g.getmRate() == 0.5);

  // invalid val shouldnt change it
  g.setmRate(2.0);
  assert(g.getmRate() == 0.5);

  cout << "testMutationRate passed" << endl;
}

// test setPixel and getPixel
void testSetGetPixel(){
  genome g;
  g.allocate(2);

  Pixel p = {100, 150, 200};
  g.setPixel(0, p);

  Pixel result = g.getPixel(0);
  assert(result.red == 100);
  assert(result.green == 150);
  assert(result.blue == 200);

  // invalid index returns default pixel
  Pixel invalid = g.getPixel(10);
  assert(invalid.red == 0);
  assert(invalid.green == 0);
  assert(invalid.blue == 0);

  cout << "testSetGetPixel passed" << endl;
}

// tests mutateGene
void testMutateGene(){
  genome g;
  g.allocate(1);

  Pixel p = {10, 20, 30};
  g.setPixel(0, p);

  g.setmRate(1.0); // force mutation
  g.mutateGene(0);

  Pixel result = g.getPixel(0);

  // at least one value should change
  bool changed = (result.red != 10 || result.green != 20 || result.blue != 30);
  assert(changed);

  cout << "testMutateGene passed" << endl;
}

// tests mutate (entire genome)
void testMutate(){
  genome g;
  g.allocate(3);

  g.setmRate(1.0); // force mutation

  Pixel before[3];
  for(int i = 0; i < 3; i++){
    before[i] = g.getPixel(i);
  }

  g.mutate();

  bool changed = false;

  for(int i = 0; i < 3; i++){
    Pixel after = g.getPixel(i);
    if(after.red != before[i].red || after.green != before[i].green || after.blue != before[i].blue){
      changed = true;
    }
  }

  assert(changed);

  cout << "testMutate passed" << endl;
}

// tests calcGeneFitness
void testCalcGeneFitness(){
  genome g;
  g.allocate(1);

  Pixel p = {0, 0, 0};
  g.setPixel(0, p);

  // perfect match
  assert(g.calcGeneFitness(0, p) == 0.0);

  Pixel diff = {255, 255, 255};
  assert(g.calcGeneFitness(0, diff) > 0.0);

  cout << "testCalcGeneFitness passed" << endl;
}

// tests calcOverallFitness
void testCalcOverallFitness(){
  genome g;
  g.allocate(2);

  Pixel target[2] = {
    {0,0,0},
    {0,0,0}
  };

  g.setPixel(0, target[0]);
  g.setPixel(1, target[1]);

  // perfect match
  assert(g.calcOverallFitness(target, 2) == 0.0);

  // invalid input
  assert(g.calcOverallFitness(target, 1) == -1.0);

  cout << "testCalcOverallFitness passed" << endl;
}

// partial mismatch test
void testCalcOverallFitnessMismatch(){
  genome g;
  g.allocate(2);

  g.setPixel(0, {0,0,0});
  g.setPixel(1, {255,255,255});

  Pixel target[2] = {
    {0,0,0},
    {0,0,0}
  };

  double fitness = g.calcOverallFitness(target, 2);

  assert(fitness > 0.0);

  cout << "testCalcOverallFitnessNonPerfect passed" << endl;
}

// MAIN *****************************************

int main(){
  // PROG 1 TESTS
  cout << "GA1 TESTS..." << endl;
  testAllocateInit();
  testSettersGetters();
  testOOBaccess();
  testRandomize();
  testDeallocate();

  // PROG 2 TESTS *********************

  cout << "GA2 TESTS..." << endl;
  testMutationRate();
	testSetGetPixel();
	testMutateGene();
	testMutate();
	testCalcGeneFitness();
	testCalcOverallFitness();
	testCalcOverallFitnessMismatch();

  cout << "All tests passed" << endl;
  return 0;
}