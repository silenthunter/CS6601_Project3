#include <cv.h>
#include <cvaux.h>
#include <highgui.h>

int main(int argc, char* argv[])
{
	IplImage* img = cvLoadImage(argv[1]);
	IplImage* luv;
	if(!img)
	{
		printf("Could not load %s\n", argv[1]);
		exit(0);
	}

	printf("Width: %d\nHeight: %d\n", img->width, img->height);

	//Set luv to the be same size as img
	luv = cvCreateImage(cvGetSize(img), img->depth, img->nChannels);

	cvCvtColor(img, luv, CV_RGB2Luv);
	cvSaveImage("CIELUV.jpg", luv);
}
