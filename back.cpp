#include <stdio.h>
#include <cv.h>
#include <cxcore.h>
#include <highgui.h>

#define WIDTH 640 // �D�񌒶�

#define HEIGHT 480 // �߶�

#define THRESHOLD_MAX_VALUE 255 //��ֵ�����ȡֵ


int main( int argc, char **argv ) {
 int key;       

 CvCapture *capture = NULL;   

 IplImage *frameImage;    
 
 // �D������

 IplImage *backgroundImage = cvCreateImage( cvSize(WIDTH, HEIGHT), IPL_DEPTH_8U, 3); // ����������IplImage
 IplImage *grayImage = cvCreateImage( cvSize(WIDTH, HEIGHT), IPL_DEPTH_8U, 3 );  // gray������IplImage
 IplImage *differenceImage = cvCreateImage( cvSize(WIDTH, HEIGHT), IPL_DEPTH_8U,3 ); // ��ֻ�����IplImage
 

//��������
 char windowNameCapture[] = "Capture";    

 char windowNameDifference[] = "Difference";  

    
 // �z���^��ʼ��

 if ( ( capture = cvCaptureFromAVI("qw1.avi") ) == NULL ) {
  // �o�z���^�r

  printf( "NO CAMERA!\n" );
  return -1;
 }

 // ���ɴ���

 cvNamedWindow( windowNameCapture, CV_WINDOW_AUTOSIZE );
 cvNamedWindow( windowNameDifference, CV_WINDOW_AUTOSIZE );
   
 // �@�ó�ʼ�D��
backgroundImage = cvQueryFrame( capture );
 // ����ʼ�D���D����ڰ׈D�񣬲�����鱳���D��
 
// cvCvtColor( frameImage, backgroundImage, CV_BGR2GRAY );
    
 

 while ( 1 ) {
  frameImage = cvQueryFrame( capture );
  

  //cvCvtColor( frameImage, grayImage, CV_BGR2GRAY );
  // grayImage�ͱ����D����Ӌ�㣬����ʾ��differenceImage��
  cvAbsDiff( frameImage, backgroundImage, differenceImage );
  

//���D��ֈD��

/*if ( differenceImage->origin == 0 ) {
   cvFlip( differenceImage, differenceImage, 0 );
  }*/
  //  ��ֵ��̎��
 // cvThreshold( differenceImage, differenceImage, 100, THRESHOLD_MAX_VALUE, CV_THRESH_BINARY );

  // �@ʾ����
  cvShowImage( windowNameCapture, frameImage );
  cvShowImage( windowNameDifference, differenceImage );

  

  key = cvWaitKey( 1 );
  if ( key == 'q' ) {
   // 'q'�˳�
   break;
  } else if ( key == 'b' ) {
   // 'b'ȡ���r����鱳���D��
    //  frameImage = cvQueryFrame( capture );
    //  cvCvtColor( frameImage, backgroundImage, CV_BGR2GRAY );
  }
 }

 

 cvReleaseCapture( &capture );


 // ጷ�memory
 cvReleaseImage( &backgroundImage );
 cvReleaseImage( &grayImage );
 cvReleaseImage( &differenceImage );


 // �����N��

 cvDestroyWindow( windowNameCapture );
 cvDestroyWindow( windowNameDifference );

 

 return 0;
}