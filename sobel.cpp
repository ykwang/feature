#include"cv.h"
#include"highgui.h"



void main()
{
	//TODO:Add your command handler code here
	//定义的变量
	IplImage * pImage=cvLoadImage("lena.jpg",1) ; //声明IplImage 变量
	IplImage * pImgSobelgray=NULL; //声明IplImage变量，用于灰度图像Sobel变换
	IplImage * pImg8u=NULL;     //用于图像的格式转换
	IplImage * pImg8uSmooth=NULL;//用于存储平滑后的图像
	IplImage * pImgColor=NULL;//用于Sobel变换
	IplImage * pImgSobelcolor=NULL;//用于彩色图像Sobel变换


	IplImage * pImgPlanes[3]={0,0,0};

	pImg8u=cvCreateImage(cvSize(pImage->width,pImage->height),IPL_DEPTH_8U,1);
	pImg8uSmooth=cvCreateImage(cvGetSize(pImage),IPL_DEPTH_8U,1);

    //把图像转化为灰度图像
	cvCvtColor(pImage,pImg8u,CV_BGR2GRAY);
	//对图像高斯滤波
	cvSmooth(pImg8u,pImg8uSmooth,CV_GAUSSIAN,3,0,0);
	//cvSobel函数要求图像必须是16位图像
	pImgSobelgray=cvCreateImage(cvGetSize(pImage),IPL_DEPTH_16S,1);
	//计算一阶x方向的差分，可根据需要设置参数
	cvSobel(pImg8uSmooth,pImgSobelgray,0,1,3);
	//将图像格式转化回来用于显示
	cvConvertScaleAbs(pImgSobelgray,pImg8u,1,0);


	cvNamedWindow("Sobel gray image",1);
	cvShowImage("Sobel gray image",pImg8u);

	int i;
	for(i=0;i<3;i++)
		pImgPlanes[i]=cvCreateImage(cvGetSize(pImage),8,1);
	pImgSobelcolor=cvCreateImage(cvGetSize(pImage),IPL_DEPTH_16S,1);

	pImgColor=cvCreateImage(cvGetSize(pImage),8,3);

	//将图像分成3个单通道图像
	cvCvtPixToPlane(pImage,pImgPlanes[0],pImgPlanes[1],pImgPlanes[2],0);
	for(i=0;i<3;i++)
	{
		cvSobel(pImgPlanes[i],pImgSobelcolor,0,1,3);
		cvConvertScaleAbs(pImgSobelcolor,pImgPlanes[i],1,0);

	}
	//将各通道图像进行合并
	cvCvtPlaneToPix(pImgPlanes[0],pImgPlanes[1],pImgPlanes[2],0,pImgColor);

	cvNamedWindow("Sobel color image",1);
	cvShowImage("Sobel color image",pImgColor);
	cvWaitKey(0);
	cvDestroyWindow("Sobel gray image");
	cvDestroyWindow("Sobel color image");

	cvReleaseImage(&pImage);
	cvReleaseImage(&pImgSobelgray);
	cvReleaseImage(&pImgSobelcolor);
	cvReleaseImage(&pImg8u);
	cvReleaseImage(&pImg8uSmooth);

}