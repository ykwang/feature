#include"cv.h"
#include"highgui.h"

void main()
{

	IplImage * pImage=cvLoadImage("sd.jpg",1);
	IplImage * pImg8u=NULL;
	IplImage * pImgCanny=NULL;
	CvMemStorage * storage=NULL;
	CvSeq * lines=NULL;
	pImg8u=cvCreateImage(cvGetSize(pImage),IPL_DEPTH_8U,1);
	pImgCanny=cvCreateImage(cvGetSize(pImage),IPL_DEPTH_8U,1);

	cvCvtColor(pImage,pImg8u,CV_BGR2GRAY);
	storage=cvCreateMemStorage(0);

	cvCanny(pImg8u,pImgCanny,50,500,3);
	lines=cvHoughLines2(pImgCanny,storage,CV_HOUGH_PROBABILISTIC,1,CV_PI/180,80,30,10);

	int i;
	for(i=0;i<lines->total;i++){
	CvPoint * line=(CvPoint *)cvGetSeqElem(lines,i);
	cvLine(pImage,line[0],line[1],CV_RGB(255,0,0),1,4);

	}

	cvNamedWindow("hough",1);
	cvShowImage("hough",pImage);
	cvWaitKey(0);
	cvDestroyWindow("hough");
	cvReleaseImage(&pImage);
	cvReleaseImage(&pImgCanny);
	cvReleaseImage(&pImg8u);
}