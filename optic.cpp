#include <cv.h>
#include <highgui.h>
#include <iostream>
using namespace std;
int const MAX_CORNERS = 1000;
int main (int argc, char **argv)
{ 
 CvCapture* capture = 0;
 capture = cvCaptureFromAVI(  "qw1.avi" );  //get frame

 IplImage *src_img1;  //the previous frame (gray)
 IplImage *src_img2;  //the current frame(gray)

 IplImage *dst_img;   //the result
 IplImage *cur_img;  
 IplImage *pre_img;

 CvPoint2D32f * move_old_point = new CvPoint2D32f[ MAX_CORNERS];
 CvPoint2D32f * move_new_point = new CvPoint2D32f[ MAX_CORNERS];
 char *features_found = new char[MAX_CORNERS];
 float *features_error = new float[MAX_CORNERS];
 CvTermCriteria criteria;
 criteria = cvTermCriteria (CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 64, 0.01);
 while(1)
 {
  int i,j;
  int dx, dy;
  int p = 0;
  int rows, cols;
  int countn = MAX_CORNERS;
  pre_img = cvQueryFrame(capture);

  CvSize img_sz = cvGetSize(pre_img);
  src_img1 = cvCreateImage(img_sz, IPL_DEPTH_8U, 1);
  cvCvtColor(pre_img, src_img1, CV_RGB2GRAY);

  cur_img = cvQueryFrame(capture);
  src_img2 = cvCreateImage(img_sz, IPL_DEPTH_8U, 1);
  cvCvtColor(cur_img, src_img2, CV_RGB2GRAY);
  dst_img = (IplImage *)cvClone(cur_img);
 // cvCopy(cur_img,dst_img,0);
  IplImage *move_img = cvCreateImage(img_sz, IPL_DEPTH_8U, 1);
  cvZero(move_img);
  //cvAbsDiff(src_img1, src_img2,move_img);
  cols = src_img1->width; 
  rows = src_img1->height;
  for (i = 0; i <cols; i++)
  {
   for (j = 0; j<rows; j++)
   {
    double a = abs(cvGet2D(src_img1, j, i).val[0]-cvGet2D(src_img2, j, i).val[0]);
    CvScalar b = cvScalar(a, 0, 0,0);
    cvSet2D(move_img, j, i,b);
    if (a>40)
    {
     if (p<MAX_CORNERS-1)
     {
      int d = ++p;
      move_old_point[d].x = i;
      move_old_point[d].y = j;
     }

    }
   }
  }
        cvNamedWindow("moving object", 1);
  cvShowImage("moving object", move_img);

  CvSize Pyrsize = cvSize(src_img1->width +8, src_img1->height/3);
  IplImage * pyrA = cvCreateImage(Pyrsize, IPL_DEPTH_32F, 1); //pyrA是需要寻找的点，不是没有初始化的
  IplImage * pyrB = cvCreateImage(Pyrsize, IPL_DEPTH_32F, 1);

  cvCalcOpticalFlowPyrLK(src_img1,
        src_img2,
        pyrA,
        pyrB,
        move_old_point,
        move_new_point,
        countn,
        cvSize(10, 10),
        3,
        features_found,
        features_error,
        criteria,
        0
        );
  for (i = 0; i < countn; i++)
  {  
   int x1 = (int)move_new_point[i].x;
   int x2 = (int)move_old_point[i].x;
   int y1 = (int)move_new_point[i].y;
   int y2 = (int)move_old_point[i].y;
 
   dx =(int) abs(x1 - x2) ;
   dy = (int)abs(y1 - y2);
   if (dx >= 5&& dy >= 5)
   {
    cvLine (dst_img, cvPoint(x2, y2),cvPoint(x2+5, y2+5) , CV_RGB (255, 0, 0), 1, CV_AA, 0);
   }
  }


  cvNamedWindow ("ImagePyrLK", 1); 
  cvShowImage ("ImagePyrLK", dst_img);
  cvWaitKey (1);
  cvReleaseImage (&dst_img);
  cvReleaseImage(&pyrA);
  cvReleaseImage(&pyrB);
  cvReleaseImage(&move_img);


 }

 cvDestroyWindow("moving object");
 cvDestroyWindow ("ImagePyrLK"); 
 cvReleaseImage (&src_img1);
 cvReleaseImage (&src_img2);

 cvReleaseImage (&pre_img);
 cvReleaseImage (&cur_img);

 return 0;
}

  