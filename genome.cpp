#include "genome.h"
#include <iostream>
#include <cstdlib>
using namespace std;

// constructor
genome::genome(){
	genes = NULL;
	nGenes = 0;
}

// Destructer
genome::~genome(){
	deallocate();
}

// memory allocation
void genome::allocate(int nGenes){
	if(genes != NULL){
		deallocate();
	}
	
	if(nGenes <= 0) return;

	genes = new Pixel[nGenes];
	this->nGenes = nGenes;

	// init pixels
	for (int i = 0; i < nGenes; i++){
		genes[i].red = 0;
		genes[i].green = 0;
		genes[i].blue = 0;
	}
}

// free memory
void genome::deallocate(){
	if(genes == NULL) return;

	delete[] genes;
	genes = NULL;
	nGenes = 0;
}

// random RGB values
void genome::randomize(){
	for (int i = 0; i < nGenes; i++){
		genes[i].red = rand() % 256;
        	genes[i].green = rand() % 256;
        	genes[i].blue = rand() % 256;
	}
}

//setters
void genome::setRed(int index, int value){
	if(index >= 0 && index < nGenes){
		genes[index].red = value;
	}
}

void genome::setGreen(int index, int value){
        if(index >= 0 && index < nGenes){
                genes[index].green = value;
        }
}

void genome::setBlue(int index, int value){
        if(index >= 0 && index < nGenes){
                genes[index].blue = value;
        }
}


// getters
int genome::getRed(int index){
        if(index >= 0 && index < nGenes){
                return genes[index].red;
        }
	return -1;
}

int genome::getGreen(int index){
        if(index >= 0 && index < nGenes){
                return genes[index].green;
        }
        return -1;
}

int genome::getBlue(int index){
        if(index >= 0 && index < nGenes){
                return genes[index].blue;
        }
        return -1;
}

//print genes
void genome::print() {
    for (int i = 0; i < nGenes; i++) {
        cout << "Pixel " << i << ": ("
             << genes[i].red << ", "
             << genes[i].green << ", "
             << genes[i].blue << ")" << endl;
    }
}

