#include"cv.h"
#include"highgui.h"

void main()
{
	IplImage * pImage=cvLoadImage("lena.jpg",-1);
	IplImage * pImgErode=pImage;
	IplImage * pImgDilate=pImage;


	cvErode(pImgErode,pImgErode,0,2);
	cvDilate(pImgDilate,pImgDilate,0,2);
    cvNamedWindow("Image",0);
    cvShowImage("Image",pImage);
	cvNamedWindow("Erode",0);
	cvShowImage("Erode",pImgErode);
	cvNamedWindow("Dilate",0);
	cvShowImage("Dilate",pImgDilate);
	cvWaitKey(0);
	cvReleaseImage(&pImgErode);
	cvReleaseImage(&pImgDilate);
	cvDestroyWindow("Erode");
	cvDestroyWindow("Dilate");
	cvDestroyWindow("Image");
	
}