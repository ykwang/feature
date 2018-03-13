#include"cv.h"
#include"highgui.h"


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include<math.h>
#include<float.h>
#include<limits.h>
#include<time.h>
#include<ctype.h>




#ifdef _EiC
#define WIN32
#endif


static CvMemStorage *storage=0;
static CvHaarClassifierCascade*cascade=0;


void detect_and_draw(IplImage * image);
const char *cascade_name="palm.xml";


int main(int argc,char**argv)
{
	CvCapture*capture=0;
	IplImage*frame,*frame_copy=0;
	//int optlen=strlen("--cascade=");
	const char* input_name="cam1.avi";
	 CvVideoWriter * video=0;
     int n=0;

	/*if(argc>1&&strncmp(argv[1],"--cascade=",optlen)==0)
	{
		cascade_name=argv[1]+optlen;
		input_name=argc>2?argv[2]:0;
	}
	else
	{*/
		cascade_name="fist.xml";
	//	input_name=argc>1?argv[1]:0;
	//}
	cascade=(CvHaarClassifierCascade*)cvLoad(cascade_name,0,0,0);

	if(!cascade)
	{
		fprintf(stderr,"ERROR:Could not load classifier cascade\n");
		fprintf(stderr,"usage:facedetect--cascade=\"<cascade_path>\"[filename|camera_index]\n");
		return -1;
	}
	storage=cvCreateMemStorage(0);
	if(!input_name||(isdigit(input_name[0])&&input_name[1]=='\0'))
		capture=cvCaptureFromCAM(!input_name?0:input_name[0]-'0');
	else
		capture=cvCaptureFromAVI(input_name);
	cvNamedWindow("result",1);
	if(capture)
	{
		if(!cvGrabFrame(capture))
				return -1;
			frame=cvRetrieveFrame(capture);
			if(!frame)
				return -1;
		video=cvCreateVideoWriter("camera1.avi",CV_FOURCC('X','V','I','D'),21,cvSize(frame->width,frame->height),1);
		for(;;)
		{
			if(!cvGrabFrame(capture))
				break;
			frame=cvRetrieveFrame(capture);
			if(!frame)
				break;
			if(!frame_copy)
				frame_copy=cvCreateImage(cvSize(frame->width,frame->height),IPL_DEPTH_8U,frame->nChannels);
		//	if(frame->origin=IPL_ORIGIN_TL)
				cvCopy(frame,frame_copy,0);
		//	else
		//		cvFlip(frame,frame_copy,0);
			detect_and_draw(frame_copy);
			 n=cvWriteFrame(video,frame_copy);
			//cvShowImage("result",frame_copy);
			if(cvWaitKey(10)>=0)
				break;
		}
		cvReleaseImage(&frame_copy);
		cvReleaseVideoWriter(&video);
		cvReleaseCapture(&capture);
	}
	else
	{
		const char * filename=input_name?input_name:(char*)"2.jpg";
		IplImage* image=cvLoadImage(filename,1);
		if(image)
		{
			detect_and_draw(image);
			cvWaitKey(0);
			cvReleaseImage(&image);
		}
		else
		{
			/*assume it is a text file containing the list of the image filenames to be processed-one per line*/
			FILE*f=fopen(filename,"rt");
			if(f)
			{char buf[1000+1];
			 while(fgets(buf,1000,f));
			 {
				int len=(int)strlen(buf);
				while(len>0&&isspace(buf[len-1]))len--;
				buf[len]='\0';
				image=cvLoadImage(buf,1);
				if(image)
				{
					detect_and_draw(image);
					cvWaitKey(0);
					cvReleaseImage(&image);
				}
			  }
			 fclose(f);
			}
		}
	}
	cvDestroyWindow("result");
	return 0;
}
void detect_and_draw(IplImage*img)
{
  
	static CvScalar colors[]=
	{
		{{0,0,255}},
		{{0,128,255}},
		{{0,255,255}},
		{{0,255,0}},
		{{255,128,0}},
		{{255,255,}},
		{{255,0,0}},
		{{255,0,255}},
	};
	double scale=1.3;
	IplImage*gray=cvCreateImage(cvSize(img->width,img->height),8,1);
	IplImage*small_img=cvCreateImage(cvSize(cvRound(img->width/scale),cvRound(img->height/scale)),8,1);
	int i;

	cvCvtColor(img,gray,CV_BGR2GRAY);
     cvResize(gray,small_img,CV_INTER_LINEAR);
	 cvEqualizeHist(small_img,small_img);
	 cvClearMemStorage(storage);
	 if(cascade)
	 {
		 double t=(double)cvGetTickCount();
		 CvSeq*faces=cvHaarDetectObjects(small_img,cascade,storage,2,2,0/*CV_HAAR_DO_CANNY_PRUNING*/,cvSize(40,40));
		 t=(double)cvGetTickCount()-t;
		 printf("dection time=%gms\n",t/((double)cvGetTickFrequency()*1000));
		 for(i=0;i<(faces?faces->total:0);i++)
		 {
			 CvRect*r=(CvRect*)cvGetSeqElem(faces,i);
			 CvPoint center;
			 int radius;
			 center.x=cvRound((r->x+r->width*0.5)*scale);
			 center.y=cvRound((r->y+r->height*0.5)*scale);
			 radius=16;//cvRound((r->width+r->height)*0.25*scale);
			 
			 cvCircle(img,center,radius,colors[i%8],3,8,0);
		 }
	 }
	
	cvShowImage("result",img);
	 cvReleaseImage(&gray);
	 
	 cvReleaseImage(&small_img);
}