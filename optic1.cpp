#include <cv.h>
#include <highgui.h>

int main (int argc, char **argv)
{ 
 CvCapture* capture = 0;
 capture = cvCaptureFromAVI( "qw1.avi" ); 

 
 int i;

 int corner_count = 1000; 

 CvTermCriteria criteria; 
 criteria = cvTermCriteria (CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 64, 0.01);

 IplImage *src_img1;
 IplImage *src_img2;

 IplImage *dst_img;
 IplImage *pre_img;
 

 IplImage *eig_img;
 IplImage *temp_img;

 IplImage *prev_pyramid;
 IplImage *curr_pyramid;

 CvPoint2D32f *corners1;
 CvPoint2D32f *corners2; 
 corners1 = (CvPoint2D32f *) cvAlloc (corner_count * sizeof (CvPoint2D32f)); 
 corners2 = (CvPoint2D32f *) cvAlloc (corner_count * sizeof (CvPoint2D32f));
 cvNamedWindow ("Image", 1);
 char *status;
 status = (char *) cvAlloc (corner_count); 
 while (1)
 {
  
  pre_img = cvQueryFrame(capture);

  CvSize img_sz = cvGetSize(pre_img);
  src_img1 = cvCreateImage(img_sz, IPL_DEPTH_8U, 1);
  cvCvtColor(pre_img, src_img1, CV_RGB2GRAY);

  dst_img = cvQueryFrame(capture);
  src_img2 = cvCreateImage(img_sz, IPL_DEPTH_8U, 1);
  cvCvtColor(dst_img, src_img2, CV_RGB2GRAY);
  
  eig_img = cvCreateImage (img_sz, IPL_DEPTH_32F, 1);
  temp_img = cvCreateImage (img_sz, IPL_DEPTH_32F, 1);

 

  prev_pyramid = cvCreateImage (cvSize (src_img1->width + 8, src_img1->height / 3), IPL_DEPTH_8U, 1); 
  curr_pyramid = cvCreateImage (cvSize (src_img1->width + 8, src_img1->height / 3), IPL_DEPTH_8U, 1);


   
  cvGoodFeaturesToTrack (src_img1, eig_img, temp_img, corners1, &corner_count, 0.001, 5, NULL);

  cvCalcOpticalFlowPyrLK (src_img1, src_img2, prev_pyramid, curr_pyramid,                      
   corners1, corners2, corner_count, cvSize (10, 10), 4, status, NULL, criteria, 0); 

  for (i = 0; i < corner_count; i++)
  {   
   if (status[i])     
    cvLine (dst_img, cvPointFrom32f (corners1[i]), cvPointFrom32f (corners2[i]), CV_RGB (255, 0, 0), 1, CV_AA, 0); 
  } 
  
  cvShowImage ("Image", dst_img); 
  cvWaitKey (1);
  cvReleaseImage (&src_img1); 
  cvReleaseImage (&src_img2);
  cvReleaseImage (&eig_img);
  cvReleaseImage (&temp_img); 
  cvReleaseImage (&prev_pyramid); 
  cvReleaseImage (&curr_pyramid);

 }

 cvDestroyWindow ("Image");
 cvReleaseImage (&dst_img);
 cvReleaseImage(&pre_img);
 return 0;
}