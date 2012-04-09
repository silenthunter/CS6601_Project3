#include <cv.h>
#include <cvaux.h>
#include <highgui.h>

int main(int argc, char* argv[])
{
	IplImage* img = cvLoadImage(argv[1]);
	if(!img)
	{
		printf("Could not load %s\n", argv[1]);
		exit(0);
	}
}
