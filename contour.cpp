#include"cv.h"
#include"highgui.h"
#include<stdlib.h>


#define ARRAY 1
void main(int argc,char  * argv)
{
	IplImage * img=cvCreateImage(cvSize(500,200),8,3);
	cvNamedWindow("hull",1);
# if ! ARRAY
	    CvMemStorage *storage=cvCreateMemStorage();
#endif
		for(;;)
		{
			int i,count=rand()%100+1,hullcount;
			CvPoint pt0;
#if !ARRAY 
			CvSeq* ptseq=cvCreateSeq(CV_SEQ_KIND_GENERIC|CV_32SC2,sizeof(CvContour),sizeof(CvPoint),storage);
			CvSeq * hull;
			for(i=0;i<count;i++)
			{
				pt0.x=rand()%(img->width/2)+img->width/4;
				pt0.y=rand()%(img->height/2)+img->height/4;
				cvSeqPush(ptseq,&pt0);
			}
			hull=cvConvexHull2(ptseq,0,CV_CLOCKWISE,0);
			hullcount=hull->total;
#else
			CvPoint * points=(CvPoint *)malloc(count*sizeof(points[0]));
			int * hull=(int *)malloc(count *sizeof(hull[0]));
			CvMat point_mat=cvMat(1,count,CV_32SC2,points);
			CvMat hull_mat=cvMat(1,count,CV_32SC1,hull);

			for(i=0;i<count;i++)
			{
                pt0.x=rand()%(img->width/2)+img->width/4;
				pt0.y=rand()%(img->height/2)+img->height/4;
				points[i]=pt0;
			}
			cvConvexHull2(&point_mat,&hull_mat,CV_CLOCKWISE,0);
			hullcount=hull_mat.cols;
#endif
			cvZero(img);
			for(i=0;i<count;i++)
			{
#if!ARRAY
				pt0=*CV_GET_SEQ_ELEM(CvPoint,ptseq,i);
#else
				pt0=points[i];
#endif
				cvCircle(img,pt0,2,CV_RGB(255,0,0),CV_FILLED);
			}
#if!ARRAY
			pt0=**CV_GET_SEQ_ELEM(CvPoint*,hull,hullcount-1);
#else
			pt0=points[hull[hullcount-1]];
#endif
				for(i=0;i<hullcount;i++)
			{
#if!ARRAY
				CvPoint pt=**CV_GET_SEQ_ELEM(CvPoint*,hull,i);
#else
				CvPoint pt=points[hull[i]];
#endif
				cvLine(img,pt0,pt,CV_RGB(0,255,0));
				pt0=pt;

			}
				cvShowImage("hull",img);

				int key=cvWaitKey(0);
				if(key==27)
					break;
#if!ARRAY
				cvClearMemStorage(storage);
#else
				free(points);
				free(hull);
#endif

		}
}