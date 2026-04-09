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

private:
	Pixel* genes;
	int nGenes;
};

