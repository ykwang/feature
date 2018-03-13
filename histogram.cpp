#include"cv.h"
#include"highgui.h"
#include<iostream>
//#include<string.h>
// #include <afx.h>
void main()
{
	
	int hist_size=255;                              //ֱ��ͼ������
	float range_0[]={0,256};                        //��0ά��ֵ�ı仯��Χ
	float * ranges[]={range_0};                     //��1ά��ֵ�ı仯��Χ
	int i,bin_w;                                    //�±��
	float max_value=0,min_value=0;                  //ֱ��ͼ��ֵ��������С
	int min_idx=0,max_idx=0;                        //��Ӧ����������С���±��

	double mean=0,variance=0;                        //���ڴ��ƽ��ֵ�ͱ仯���ı���

	IplImage * pImage=cvLoadImage("hf.png",1);
	IplImage * pImgGray=NULL;

	pImgGray=cvCreateImage(cvGetSize(pImage),IPL_DEPTH_8U,1);

	cvCvtColor(pImage,pImgGray,CV_BGR2GRAY);
  //����һ����������
	CvRect rect=cvRect(0,0,500,600);
	//�Ѿ���������ͼ���Խ���һ������Ȥ����(region of interest,ROI)

	cvSetImageROI(pImgGray,rect);
	//����һ��ͼ�����ڴ��ֱ��ͼ
	IplImage * histImage=cvCreateImage(cvSize(320,200),8,1);
	//����һ��ָ���ߴ��ֱ��ͼ�����ڴ�Ŵ�ͼ������Ϣ
	CvHistogram *  hist=cvCreateHist(1,&hist_size,CV_HIST_ARRAY,ranges,1);
	//����ֱ��ͼ�����õ�hist����
	cvCalcHist(&pImgGray,hist,0,NULL);
	//�õ�ֱ��ͼ�е������Сֵ������
	cvGetMinMaxHistValue(hist,&min_value,&max_value,&min_idx,&max_idx);

	//������Щ�����С������ͼ����
	cvScale(hist->bins,hist->bins,((double)histImage->height)/max_value,0);
	//������ֱ��ͼ����ֵΪ255
	cvSet(histImage,cvScalarAll(255),0);
	//����һ�������������ؿ������
	bin_w=cvRound((double)histImage->width/hist_size);
	
	for(i=0;i<hist_size;i++){
		//��ֱ��ͼ����ͼ����
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

	