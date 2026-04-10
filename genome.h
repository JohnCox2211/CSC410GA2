struct Pixel {
	int red;
	int green;
	int blue;
};

class genome{
public:
	genome();
	~genome();
	void allocate(int nGenes);
	void deallocate();
	void randomize();

	//setters
	void setRed(int index, int value);
	void setGreen(int index, int value);
	void setBlue(int index, int value);

	//getters
	int getRed(int index);
	int getGreen(int index);
	int getBlue(int index);

	void print(); // for display

	// NEW FUNCTIONS****************
	void setmRate(double val);
	double getmRate();

	void mutateGene(int index);
	void mutate();

	double calcGeneFitness(int index, Pixel targetPixel);
	double calcOverallFitness(Pixel* target, int nPixels);

	void setPixel(int index, Pixel newPixel);
	Pixel getPixel(int index);

private:
	Pixel* genes;
	int nGenes;

	//NEW VARIABLES
	double mRate;
};

