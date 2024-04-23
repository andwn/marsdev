#include "graphics.h"

const static vu8 blankArray[8] = {0};

/*
* For a given details value 0 - 63 returns the equivalent
* of sin((d/10)). Precalculated.
*/
double xSinTable(const int details){
	double result;
	if(details == 0)
	{
		result = 0.000000; 
	}
	else if(details == 1)
	{
		result = 0.099833; 
	}
	else if(details == 2)
	{
		result = 0.198669; 
	}
	else if(details == 3)
	{
		result = 0.295520; 
	}
	else if(details == 4)
	{
		result = 0.389418; 
	}
	else if(details == 5)
	{
		result = 0.479426; 
	}
	else if(details == 6)
	{
		result = 0.564642; 
	}
	else if(details == 7)
	{
		result = 0.644218; 
	}
	else if(details == 8)
	{
		result = 0.717356; 
	}
	else if(details == 9)
	{
		result = 0.783327; 
	}
	else if(details == 10)
	{
		result = 0.841471; 
	}
	else if(details == 11)
	{
		result = 0.891207; 
	}
	else if(details == 12)
	{
		result = 0.932039; 
	}
	else if(details == 13)
	{
		result = 0.963558; 
	}
	else if(details == 14)
	{
		result = 0.985450; 
	}
	else if(details == 15)
	{
		result = 0.997495; 
	}
	else if(details == 16)
	{
		result = 0.999574; 
	}
	else if(details == 17)
	{
		result = 0.991665; 
	}
	else if(details == 18)
	{
		result = 0.973848; 
	}
	else if(details == 19)
	{
		result = 0.946300; 
	}
	else if(details == 20)
	{
		result = 0.909297; 
	}
	else if(details == 21)
	{
		result = 0.863209; 
	}
	else if(details == 22)
	{
		result = 0.808496; 
	}
	else if(details == 23)
	{
		result = 0.745705; 
	}
	else if(details == 24)
	{
		result = 0.675463; 
	}
	else if(details == 25)
	{
		result = 0.598472; 
	}
	else if(details == 26)
	{
		result = 0.515501; 
	}
	else if(details == 27)
	{
		result = 0.427380; 
	}
	else if(details == 28)
	{
		result = 0.334988; 
	}
	else if(details == 29)
	{
		result = 0.239249; 
	}
	else if(details == 30)
	{
		result = 0.141120; 
	}
	else if(details == 31)
	{
		result = 0.041581; 
	}
	else if(details == 32)
	{
		result = -0.058374; 
	}
	else if(details == 33)
	{
		result = -0.157746; 
	}
	else if(details == 34)
	{
		result = -0.255541; 
	}
	else if(details == 35)
	{
		result = -0.350783; 
	}
	else if(details == 36)
	{
		result = -0.442520; 
	}
	else if(details == 37)
	{
		result = -0.529836; 
	}
	else if(details == 38)
	{
		result = -0.611858; 
	}
	else if(details == 39)
	{
		result = -0.687766; 
	}
	else if(details == 40)
	{
		result = -0.756802; 
	}
	else if(details == 41)
	{
		result = -0.818277; 
	}
	else if(details == 42)
	{
		result = -0.871576; 
	}
	else if(details == 43)
	{
		result = -0.916166; 
	}
	else if(details == 44)
	{
		result = -0.951602; 
	}
	else if(details == 45)
	{
		result = -0.977530; 
	}
	else if(details == 46)
	{
		result = -0.993691; 
	}
	else if(details == 47)
	{
		result = -0.999923; 
	}
	else if(details == 48)
	{
		result = -0.996165; 
	}
	else if(details == 49)
	{
		result = -0.982453; 
	}
	else if(details == 50)
	{
		result = -0.958924; 
	}
	else if(details == 51)
	{
		result = -0.925815; 
	}
	else if(details == 52)
	{
		result = -0.883455; 
	}
	else if(details == 53)
	{
		result = -0.832267; 
	}
	else if(details == 54)
	{
		result = -0.772764; 
	}
	else if(details == 55)
	{
		result = -0.705540; 
	}
	else if(details == 56)
	{
		result = -0.631267; 
	}
	else if(details == 57)
	{
		result = -0.550686; 
	}
	else if(details == 58)
	{
		result = -0.464602; 
	}
	else if(details == 59)
	{
		result = -0.373877; 
	}
	else if(details == 60)
	{
		result = -0.279415; 
	}
	else if(details == 61)
	{
		result = -0.182163; 
	}
	else if(details == 62)
	{
		result = -0.083089; 
	}else{
		result = 0.0;
	}
	return result;
}


/*
* For a given details value 0 - 63 returns the equivalent
* of sin((d/10)+(pi/2)). Precalculated.
*/
double ySinTable(const int details){
	double result;
	if(details == 0)
	{
		result = 1.000000; 
	}
	else if(details == 1)
	{
		result = 0.995004; 
	}
	else if(details == 2)
	{
		result = 0.980067; 
	}
	else if(details == 3)
	{
		result = 0.955336; 
	}
	else if(details == 4)
	{
		result = 0.921061; 
	}
	else if(details == 5)
	{
		result = 0.877583; 
	}
	else if(details == 6)
	{
		result = 0.825336; 
	}
	else if(details == 7)
	{
		result = 0.764842; 
	}
	else if(details == 8)
	{
		result = 0.696707; 
	}
	else if(details == 9)
	{
		result = 0.621610; 
	}
	else if(details == 10)
	{
		result = 0.540302; 
	}
	else if(details == 11)
	{
		result = 0.453596; 
	}
	else if(details == 12)
	{
		result = 0.362358; 
	}
	else if(details == 13)
	{
		result = 0.267499; 
	}
	else if(details == 14)
	{
		result = 0.169967; 
	}
	else if(details == 15)
	{
		result = 0.070737; 
	}
	else if(details == 16)
	{
		result = -0.029200; 
	}
	else if(details == 17)
	{
		result = -0.128844; 
	}
	else if(details == 18)
	{
		result = -0.227202; 
	}
	else if(details == 19)
	{
		result = -0.323290; 
	}
	else if(details == 20)
	{
		result = -0.416147; 
	}
	else if(details == 21)
	{
		result = -0.504846; 
	}
	else if(details == 22)
	{
		result = -0.588501; 
	}
	else if(details == 23)
	{
		result = -0.666276; 
	}
	else if(details == 24)
	{
		result = -0.737394; 
	}
	else if(details == 25)
	{
		result = -0.801144; 
	}
	else if(details == 26)
	{
		result = -0.856889; 
	}
	else if(details == 27)
	{
		result = -0.904072; 
	}
	else if(details == 28)
	{
		result = -0.942222; 
	}
	else if(details == 29)
	{
		result = -0.970958; 
	}
	else if(details == 30)
	{
		result = -0.989992; 
	}
	else if(details == 31)
	{
		result = -0.999135; 
	}
	else if(details == 32)
	{
		result = -0.998295; 
	}
	else if(details == 33)
	{
		result = -0.987480; 
	}
	else if(details == 34)
	{
		result = -0.966798; 
	}
	else if(details == 35)
	{
		result = -0.936457; 
	}
	else if(details == 36)
	{
		result = -0.896758; 
	}
	else if(details == 37)
	{
		result = -0.848100; 
	}
	else if(details == 38)
	{
		result = -0.790968; 
	}
	else if(details == 39)
	{
		result = -0.725932; 
	}
	else if(details == 40)
	{
		result = -0.653644; 
	}
	else if(details == 41)
	{
		result = -0.574824; 
	}
	else if(details == 42)
	{
		result = -0.490261; 
	}
	else if(details == 43)
	{
		result = -0.400799; 
	}
	else if(details == 44)
	{
		result = -0.307333; 
	}
	else if(details == 45)
	{
		result = -0.210796; 
	}
	else if(details == 46)
	{
		result = -0.112153; 
	}
	else if(details == 47)
	{
		result = -0.012389; 
	}
	else if(details == 48)
	{
		result = 0.087499; 
	}
	else if(details == 49)
	{
		result = 0.186512; 
	}
	else if(details == 50)
	{
		result = 0.283662; 
	}
	else if(details == 51)
	{
		result = 0.377978; 
	}
	else if(details == 52)
	{
		result = 0.468517; 
	}
	else if(details == 53)
	{
		result = 0.554374; 
	}
	else if(details == 54)
	{
		result = 0.634693; 
	}
	else if(details == 55)
	{
		result = 0.708670; 
	}
	else if(details == 56)
	{
		result = 0.775566; 
	}
	else if(details == 57)
	{
		result = 0.834713; 
	}
	else if(details == 58)
	{
		result = 0.885520; 
	}
	else if(details == 59)
	{
		result = 0.927478; 
	}
	else if(details == 60)
	{
		result = 0.960170; 
	}
	else if(details == 61)
	{
		result = 0.983268; 
	}
	else if(details == 62)
	{
		result = 0.996542; 
	}else{
		result = 1.0;
	}
	return result;
}



void circle(const int r, const int f, vu8 *spriteBuffer)
{	
	int width = 32;
	int height = 26;
	int rx = 15;
	int ry = 13;
	int x,y;
	int bufCnt = 0;
	int newx,newy;
	for(y=0; y<height; y++){
		for(x=0; x<width; x++){
			bufCnt = (y * 32) + x;
			newx = x - rx;
			newy = y - ry;
			if ( (((newx*newx)+(newy*newy))>(r*r)-(f/2)) && (((newx*newx)+(newy*newy))<(r*r)+(f/2)) ) 
				spriteBuffer[bufCnt] = 129;
			else{
				spriteBuffer[bufCnt] = 0;
			}
		}
	}
}

/*
* Draws an elipse
*/
void circle2(const int16 height, const int16 width, const int16 rx,const int16 ry,const int16 r,vu8 *spriteBuffer, int16 colorIndex)
{
	int16 x,y;
	//int width = 64;
	//int height = 32;
	int16 size = width * height;
	int16 bufCnt = 0;
	int16 d = 0;//double d;//detail
	//const double pi = 3.14159265; //more or less
	//const double halfpi = pi/2;
	//const double twopi = 2*pi;
	
	//clear buffer 8 bytes at a time
	for(bufCnt = 0; bufCnt < (width*height); bufCnt+=8){
		//spriteBuffer[bufCnt] = 0;
		word_8byte_copy((void *)(spriteBuffer+bufCnt), (void *)(blankArray), 8);
	}
	
	bufCnt=0;
	for(d = 0; d <= 63; d++) //you can play with the value to be added to d
	{
		x=rx+(2*xSinTable(d))*r;
		y=ry+(ySinTable(d))*r;
		bufCnt = (y * width) + x;
		if(bufCnt < size){
			spriteBuffer[bufCnt] = colorIndex;
		}
	}
}
