#include"cv.h"
#include"highgui.h"



void main()
{
	//TODO:Add your command handler code here
	//����ı���
	IplImage * pImage=cvLoadImage("lena.jpg",1) ; //����IplImage ����
	IplImage * pImgLaplace=NULL; //����IplImage���������ڻҶ�ͼ��Sobel�任
	IplImage * pImg8u=NULL;     //����ͼ��ĸ�ʽת��
	IplImage * pImg8uSmooth=NULL;//���ڴ洢ƽ�����ͼ��
	

	pImg8u=cvCreateImage(cvSize(pImage->width,pImage->height),IPL_DEPTH_8U,1);
	pImg8uSmooth=cvCreateImage(cvGetSize(pImage),IPL_DEPTH_8U,1);

    //��ͼ��ת��Ϊ�Ҷ�ͼ��
	cvCvtColor(pImage,pImg8u,CV_BGR2GRAY);
	//��ͼ���˹�˲�
	cvSmooth(pImg8u,pImg8uSmooth,CV_GAUSSIAN,3,0,0);
	//cvLaplace����Ҫ��ͼ�������16λͼ��
	pImgLaplace=cvCreateImage(cvGetSize(pImage),IPL_DEPTH_16S,1);
	//������˹�任
	cvLaplace(pImg8uSmooth,pImgLaplace,3);
	//��ͼ���ʽת������������ʾ
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