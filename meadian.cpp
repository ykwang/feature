    #include <cv.h>   
    #include <highgui.h>  
   
      
    void main()  
    {  
        IplImage * image = cvLoadImage("qq.jpg");  
        assert(image != NULL);  
        cvNamedWindow("before");  
        cvShowImage("before",image);  
       IplImage * im_gray = cvCreateImage(cvSize(image->width,image->height), IPL_DEPTH_8U, 1);  
        cvCvtColor(image, im_gray, CV_BGR2GRAY);  
        IplImage * im_median_filter = cvCreateImage(cvSize(image->width,image->height), IPL_DEPTH_8U, 1);  
        cvSmooth(im_gray, im_median_filter, CV_MEDIAN);//默认窗口大小为3*3  
        cvNamedWindow("after");  
        cvShowImage("after",im_median_filter); 
		cvWaitKey(0);
		cvReleaseImage(&image);
		cvReleaseImage(&im_gray);
		cvReleaseImage(&im_median_filter);
		cvDestroyWindow("before");

		cvDestroyWindow("after");
    }  