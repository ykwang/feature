#include <stdio.h>
#include <cv.h>
#include <cxcore.h>
#include <highgui.h>

#define WIDTH 640 // 圖像寬度

#define HEIGHT 480 // 高度

#define THRESHOLD_MAX_VALUE 255 //二值化最大取值


int main( int argc, char **argv ) {
 int key;       

 CvCapture *capture = NULL;   

 IplImage *frameImage;    
 
 // 圖像生成

 IplImage *backgroundImage = cvCreateImage( cvSize(WIDTH, HEIGHT), IPL_DEPTH_8U, 3); // 背景画像用IplImage
 IplImage *grayImage = cvCreateImage( cvSize(WIDTH, HEIGHT), IPL_DEPTH_8U, 3 );  // gray画像用IplImage
 IplImage *differenceImage = cvCreateImage( cvSize(WIDTH, HEIGHT), IPL_DEPTH_8U,3 ); // 差分画像用IplImage
 

//命名窗口
 char windowNameCapture[] = "Capture";    

 char windowNameDifference[] = "Difference";  

    
 // 攝像頭初始化

 if ( ( capture = cvCaptureFromAVI("qw1.avi") ) == NULL ) {
  // 無攝像頭時

  printf( "NO CAMERA!\n" );
  return -1;
 }

 // 生成窗口

 cvNamedWindow( windowNameCapture, CV_WINDOW_AUTOSIZE );
 cvNamedWindow( windowNameDifference, CV_WINDOW_AUTOSIZE );
   
 // 獲得初始圖像
backgroundImage = cvQueryFrame( capture );
 // 將初始圖像轉化為黑白圖像，并儲存為背景圖像
 
// cvCvtColor( frameImage, backgroundImage, CV_BGR2GRAY );
    
 

 while ( 1 ) {
  frameImage = cvQueryFrame( capture );
  

  //cvCvtColor( frameImage, grayImage, CV_BGR2GRAY );
  // grayImage和背景圖像查分計算，并表示在differenceImage中
  cvAbsDiff( frameImage, backgroundImage, differenceImage );
  

//旋轉差分圖像

/*if ( differenceImage->origin == 0 ) {
   cvFlip( differenceImage, differenceImage, 0 );
  }*/
  //  二值化處理
 // cvThreshold( differenceImage, differenceImage, 100, THRESHOLD_MAX_VALUE, CV_THRESH_BINARY );

  // 顯示畫像
  cvShowImage( windowNameCapture, frameImage );
  cvShowImage( windowNameDifference, differenceImage );

  

  key = cvWaitKey( 1 );
  if ( key == 'q' ) {
   // 'q'退出
   break;
  } else if ( key == 'b' ) {
   // 'b'取即時畫像為背景圖像
    //  frameImage = cvQueryFrame( capture );
    //  cvCvtColor( frameImage, backgroundImage, CV_BGR2GRAY );
  }
 }

 

 cvReleaseCapture( &capture );


 // 釋放memory
 cvReleaseImage( &backgroundImage );
 cvReleaseImage( &grayImage );
 cvReleaseImage( &differenceImage );


 // 窗口銷毀

 cvDestroyWindow( windowNameCapture );
 cvDestroyWindow( windowNameDifference );

 

 return 0;
}