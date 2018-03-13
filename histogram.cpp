#include"cv.h"
#include"highgui.h"
#include<iostream>
//#include<string.h>
// #include <afx.h>
void main()
{
	
	int hist_size=255;                              //直方图的针数
	float range_0[]={0,256};                        //第0维数值的变化范围
	float * ranges[]={range_0};                     //第1维数值的变化范围
	int i,bin_w;                                    //下标号
	float max_value=0,min_value=0;                  //直方图数值的最大和最小
	int min_idx=0,max_idx=0;                        //对应上述最大和最小的下标号

	double mean=0,variance=0;                        //用于存放平均值和变化量的变量

	IplImage * pImage=cvLoadImage("hf.png",1);
	IplImage * pImgGray=NULL;

	pImgGray=cvCreateImage(cvGetSize(pImage),IPL_DEPTH_8U,1);

	cvCvtColor(pImage,pImgGray,CV_BGR2GRAY);
  //创建一个矩形区域
	CvRect rect=cvRect(0,0,500,600);
	//把矩形作用于图形以建立一个感兴趣区域(region of interest,ROI)

	cvSetImageROI(pImgGray,rect);
	//创建一个图形用于存放直方图
	IplImage * histImage=cvCreateImage(cvSize(320,200),8,1);
	//创建一个指定尺寸的直方图，用于存放从图像获得信息
	CvHistogram *  hist=cvCreateHist(1,&hist_size,CV_HIST_ARRAY,ranges,1);
	//计算直方图并作用到hist变量
	cvCalcHist(&pImgGray,hist,0,NULL);
	//得到直方图中的最大最小值及其标号
	cvGetMinMaxHistValue(hist,&min_value,&max_value,&min_idx,&max_idx);

	//缩放这些最大最小以容入图像内
	cvScale(hist->bins,hist->bins,((double)histImage->height)/max_value,0);
	//设所有直方图的数值为255
	cvSet(histImage,cvScalarAll(255),0);
	//建立一个比例因子以沿宽度缩放
	bin_w=cvRound((double)histImage->width/hist_size);
	
	for(i=0;i<hist_size;i++){
		//把直方图画到图像中
		cvRectangle(histImage,cvPoint(i*bin_w,histImage->height),cvPoint((i+1)*bin_w,histImage->height-cvRound(cvGetReal1D(hist->bins,i))),
			cvScalarAll(0),-1,8,0);
		
		float * bins=cvGetHistValue_1D(hist,i);

		mean+=bins[0];

	}

	mean/=hist_size;

	for(i=0;i<hist_size;i++){
		float*bins=cvGetHistValue_1D(hist,i);
		variance+=pow((bins[0]-mean),2);
	}
variance/=hist_size;

std::cout<<"Histogram Mean:"<<mean<<std::endl;
std::cout<<"Variance:"<<variance<<std::endl;
std::cout<<"standard Deviation:"<<sqrt(variance)<<std::endl;


cvNamedWindow("Original",0);
cvShowImage("Original",pImage);
cvNamedWindow("Gray",0);
cvShowImage("Gray",pImgGray);
cvNamedWindow("Histogram",0);
cvShowImage("Histogram",histImage);
//CvFont * pfont=new CvFont;
//cvInitFont(pfont,CV_FONT_HERSHEY_SIMPLEX,0.8f,0.8f,0,2);
//std::string Result="Histogram mean:";
//CString str;str.Format("%f",mean);

//Result=str+"\n";
//cvPutText(histImage,Result,cvPoint(80,80),pfont,CV_RGB(255,0,0));

//delete pfont;

cvWaitKey(0);
cvReleaseImage(&histImage);
cvReleaseImage(&pImgGray);

cvDestroyWindow("Original");
cvDestroyWindow("Gray");
cvDestroyWindow("Histogram");


}

	