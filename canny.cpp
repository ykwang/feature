#include"cv.h"
#include"highgui.h"



void main()
{
	//TODO:Add your command handler code here
	//����ı���
	IplImage * pImage=cvLoadImage("sd.jpg",1) ; //����IplImage ����
	IplImage * pImgCanny=NULL; //����IplImage���������ڻҶ�ͼ��Canny���
	IplImage * pImg8u=NULL;     //����ͼ��ĸ�ʽת��
	IplImage * pImg8uSmooth=NULL;//���ڴ洢ƽ�����ͼ��
	


	

	pImg8u=cvCreateImage(cvSize(pImage->width,pImage->height),IPL_DEPTH_8U,1);
	pImg8uSmooth=cvCreateImage(cvGetSize(pImage),IPL_DEPTH_8U,1);

    //��ͼ��ת��Ϊ�Ҷ�ͼ��
	cvCvtColor(pImage,pImg8u,CV_BGR2GRAY);
	//��ͼ���˹�˲�
	cvSmooth(pImg8u,pImg8uSmooth,CV_GAUSSIAN,3,0,0);
	pImgCanny=cvCreateImage(cvGetSize(pImage),IPL_DEPTH_8U,1);
	//����һ��x����Ĳ�֣��ɸ�����Ҫ���ò���
	cvCanny(pImg8uSmooth,pImgCanny,100,200,3);
	//��ͼ���ʽת������������ʾ
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