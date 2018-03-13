#include"cv.h"
#include"highgui.h"



void main()
{
	//TODO:Add your command handler code here
	//定义的变量
	IplImage * pImage=cvLoadImage("lena.jpg",1) ; //声明IplImage 变量
	IplImage * pImgLaplace=NULL; //声明IplImage变量，用于灰度图像Sobel变换
	IplImage * pImg8u=NULL;     //用于图像的格式转换
	IplImage * pImg8uSmooth=NULL;//用于存储平滑后的图像
	

	pImg8u=cvCreateImage(cvSize(pImage->width,pImage->height),IPL_DEPTH_8U,1);
	pImg8uSmooth=cvCreateImage(cvGetSize(pImage),IPL_DEPTH_8U,1);

    //把图像转化为灰度图像
	cvCvtColor(pImage,pImg8u,CV_BGR2GRAY);
	//对图像高斯滤波
	cvSmooth(pImg8u,pImg8uSmooth,CV_GAUSSIAN,3,0,0);
	//cvLaplace函数要求图像必须是16位图像
	pImgLaplace=cvCreateImage(cvGetSize(pImage),IPL_DEPTH_16S,1);
	//拉普拉斯变换
	cvLaplace(pImg8uSmooth,pImgLaplace,3);
	//将图像格式转化回来用于显示
	cvConvertScaleAbs(pImgLaplace,pImg8u,1,0);


	

	cvNamedWindow("Laplace gray image",1);
	cvShowImage("Laplace gray image",pImg8u);
	cvWaitKey(0);
	cvDestroyWindow("Laplace gray image");
	

	cvReleaseImage(&pImage);
	cvReleaseImage(&pImgLaplace);
	cvReleaseImage(&pImg8u);
	cvReleaseImage(&pImg8uSmooth);

}