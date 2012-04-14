#include <cv.h>
#include <cvaux.h>
#include <highgui.h>
#include "cvgabor.h"

int main(int argc, char* argv[])
{
	IplImage* img = cvLoadImage(argv[1]);
	IplImage *luv, *gabor, *gabor2, *gray, *final;
	int numOrientations = 4;
	if(!img)
	{
		printf("Could not load %s\n", argv[1]);
		exit(0);
	}

	printf("Width: %d\nHeight: %d\n", img->width, img->height);

	//Set luv to the be same size as img
	luv = cvCreateImage(cvGetSize(img), img->depth, img->nChannels);
	printf("depth: %d\n channels: %d\n", img->depth, img->nChannels);
	gray = cvCreateImage(cvGetSize(img), img->depth, 1);
	gabor = cvCreateImage(cvGetSize(img), img->depth, 1);
	final = cvCreateImage(cvGetSize(img), img->depth, 1);

	cvCvtColor(img, luv, CV_RGB2Luv);
	cvSaveImage("CIELUV.jpg", luv);

	cvCvtColor(luv, gray, CV_BGR2GRAY);
	cvSaveImage("gray.jpg", gray);
	for(int i = 0; i < numOrientations; i++)
	{
		CvGabor gaborFilter;
		gaborFilter.Init(PI * i / numOrientations, 1, 2 * 3.14, sqrt(2.0));
		gaborFilter.conv_img(gray, gabor, CV_GABOR_MAG);
		for(int x = 0; x < img->width; x++)
			for(int y = 0; y < img->height; y++)
			{
				CV_IMAGE_ELEM(final, uchar, y, x) += CV_IMAGE_ELEM(gabor, uchar, y, x) / 4;
			}

	}

	cvSaveImage("Gabor.jpg", final);
}
