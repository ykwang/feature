#include <highgui.h>


int main(int argc,char**argv)
{
	IplImage*img=cvLoadImage("lena.jpg");
		
		cvNamedWindow("OPENCV",CV_WINDOW_AUTOSIZE);
		cvShowImage("OPENCV",img);
		cvWaitKey(0);
		cvReleaseImage(&img);
		cvDestroyWindow("OPENCV");
		return 0;
}

