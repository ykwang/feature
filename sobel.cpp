#include"cv.h"
#include"highgui.h"



void main()
{
	//TODO:Add your command handler code here
	//����ı���
	IplImage * pImage=cvLoadImage("lena.jpg",1) ; //����IplImage ����
	IplImage * pImgSobelgray=NULL; //����IplImage���������ڻҶ�ͼ��Sobel�任
	IplImage * pImg8u=NULL;     //����ͼ��ĸ�ʽת��
	IplImage * pImg8uSmooth=NULL;//���ڴ洢ƽ�����ͼ��
	IplImage * pImgColor=NULL;//����Sobel�任
	IplImage * pImgSobelcolor=NULL;//���ڲ�ɫͼ��Sobel�任


	IplImage * pImgPlanes[3]={0,0,0};

	pImg8u=cvCreateImage(cvSize(pImage->width,pImage->height),IPL_DEPTH_8U,1);
	pImg8uSmooth=cvCreateImage(cvGetSize(pImage),IPL_DEPTH_8U,1);

    //��ͼ��ת��Ϊ�Ҷ�ͼ��
	cvCvtColor(pImage,pImg8u,CV_BGR2GRAY);
	//��ͼ���˹�˲�
	cvSmooth(pImg8u,pImg8uSmooth,CV_GAUSSIAN,3,0,0);
	//cvSobel����Ҫ��ͼ�������16λͼ��
	pImgSobelgray=cvCreateImage(cvGetSize(pImage),IPL_DEPTH_16S,1);
	//����һ��x����Ĳ�֣��ɸ�����Ҫ���ò���
	cvSobel(pImg8uSmooth,pImgSobelgray,0,1,3);
	//��ͼ���ʽת������������ʾ
	cvConvertScaleAbs(pImgSobelgray,pImg8u,1,0);


	cvNamedWindow("Sobel gray image",1);
	cvShowImage("Sobel gray image",pImg8u);

	int i;
	for(i=0;i<3;i++)
		pImgPlanes[i]=cvCreateImage(cvGetSize(pImage),8,1);
	pImgSobelcolor=cvCreateImage(cvGetSize(pImage),IPL_DEPTH_16S,1);

	pImgColor=cvCreateImage(cvGetSize(pImage),8,3);

	//��ͼ��ֳ�3����ͨ��ͼ��
	cvCvtPixToPlane(pImage,pImgPlanes[0],pImgPlanes[1],pImgPlanes[2],0);
	for(i=0;i<3;i++)
	{
		cvSobel(pImgPlanes[i],pImgSobelcolor,0,1,3);
		cvConvertScaleAbs(pImgSobelcolor,pImgPlanes[i],1,0);

	}
	//����ͨ��ͼ����кϲ�
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