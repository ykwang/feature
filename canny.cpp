#include"cv.h"
#include"highgui.h"



void main()
{
	//TODO:Add your command handler code here
	//定义的变量
	IplImage * pImage=cvLoadImage("sd.jpg",1) ; //声明IplImage 变量
	IplImage * pImgCanny=NULL; //声明IplImage变量，用于灰度图像Canny检测
	IplImage * pImg8u=NULL;     //用于图像的格式转换
	IplImage * pImg8uSmooth=NULL;//用于存储平滑后的图像
	


	

	pImg8u=cvCreateImage(cvSize(pImage->width,pImage->height),IPL_DEPTH_8U,1);
	pImg8uSmooth=cvCreateImage(cvGetSize(pImage),IPL_DEPTH_8U,1);

    //把图像转化为灰度图像
	cvCvtColor(pImage,pImg8u,CV_BGR2GRAY);
	//对图像高斯滤波
	cvSmooth(pImg8u,pImg8uSmooth,CV_GAUSSIAN,3,0,0);
	pImgCanny=cvCreateImage(cvGetSize(pImage),IPL_DEPTH_8U,1);
	//计算一阶x方向的差分，可根据需要设置参数
	cvCanny(pImg8uSmooth,pImgCanny,100,200,3);
	//将图像格式转化回来用于显示
	//cvConvertScaleAbs(pImgCanny,pImg8u,1,0);


	cvNamedWindow("Canny image",1);
	cvShowImage("Canny image",pImgCanny);
	
	cvWaitKey(0);
	cvDestroyWindow("Canny image");
	cvDestroyWindow("Canny image");

	cvReleaseImage(&pImage);
	cvReleaseImage(&pImgCanny);
	cvReleaseImage(&pImg8u);
	cvReleaseImage(&pImg8uSmooth);

}