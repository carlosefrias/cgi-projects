
class RGB{
public:
	unsigned char r,g,b;
};

class RGBpixmap{
	public:
		int nRows, nCols;
		RGB *pixel;
	int readBMPFile(char * fname);
	void setTexture(GLuint textureName);

};