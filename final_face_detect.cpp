#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include <iostream>
#include <algorithm>

using namespace std;

using namespace cv;

int main(){
Mat colorimage;
Mat grayimage;
//Mat hsvimage;

VideoCapture capture(0);

if(!capture.isOpened()){
cout<<"Failed to open webcam";
}
capture.set(CV_CAP_PROP_FRAME_WIDTH,640);
capture.set(CV_CAP_PROP_FRAME_HEIGHT,480);

char key =0;
while(key !='q'){

//Capture a frame and store it in imag variable
capture >>colorimage;

CascadeClassifier faceDetector;
  try{
     faceDetector.load("../Desktop/OpenCV_tutorial/OpenCV/opencv-3.3.0/data/lbpcascades/lbpcascade_frontalface.xml");
     namedWindow("Color Image",CV_WINDOW_NORMAL);
     imshow("Color Image", colorimage);

      Mat gray;
       if(colorimage.channels()==3)
       cvtColor(colorimage,gray,CV_BGR2GRAY);
       else if (colorimage.channels()==4){
         cvtColor(colorimage,gray,CV_BGR2GRAY);
         }
          else
          gray = colorimage;

     //Gray Image - Converting Color To Gray Image
     //namedWindow("Gray Image",CV_WINDOW_NORMAL);
    // imshow("GrayScale Image",gray);


const int Detect_width = 320;
Mat smallImg;
//cout <<gray.cols<<" "<<"320"<<endl;
// proportional way reduction of pic
float scale = gray.cols/(float)Detect_width;
//cout<<scale <<" ";
if(gray.cols > Detect_width){
int ScaledHeight = cvRound(gray.rows/scale);
resize(gray, smallImg, Size(Detect_width, ScaledHeight));
}
else
smallImg = gray;

// Resized Image -> Re sizing Image
//namedWindow("Re-Sized Image",CV_WINDOW_NORMAL);
//imshow("Re-Sized image",smallImg);

//Standardize the brightness and contrast
Mat equalizedImg;
equalizeHist(smallImg, equalizedImg);
//namedWindow("Histogram Image",CV_WINDOW_NORMAL);
//imshow(" Histogram Image ", equalizedImg);

int flags = CASCADE_SCALE_IMAGE;
Size minFeatureSize(20,20);
float searchScaleFactor = 1.1f;
int minNeighbors = 4;
//int scale = 1;
//Detect Objects in the small grayscale image
vector<Rect> faces;
faceDetector.detectMultiScale( equalizedImg , faces,searchScaleFactor,
       minNeighbors, flags, minFeatureSize);

cout<<"the number of faces is "<<faces.size()<<endl;
int scaledWidth = Detect_width;
//Enlarge the results if the image was temporarily shrunk.
cout<<scale<<endl;
if( equalizedImg.cols > scaledWidth){  //used the width of the frame
  for( int i=0;i < (int)faces.size(); i++){
          faces[i].x = cvRound( faces[i].x * scale);
          faces[i].y = cvRound( faces[i].y * scale);
          faces[i].width = cvRound( faces[i].width * scale);
          faces[i].height = cvRound( faces[i].height *scale);
          }
          }

//If the object is on a border, keep it on the image.
for(int i=0;i<(int)faces.size();i++){
 if(faces[i].x <0)
faces[i].x =0;
if (faces[i].y<0)
faces[i].y =0;
if (faces[i].x + faces[i].width > equalizedImg.cols)
faces[i].x = equalizedImg.cols - faces[i].width;
if(faces[i].y + faces[i].height >  equalizedImg.rows)
faces[i].y = equalizedImg.rows - faces[i].height;
}
int g = (int)faces.size();
Mat  faceImg;
faceImg = equalizedImg;
Rect rect_crop ;
 for (int  i = 0; i < g; i++)
        {
			Rect rect = faces[i];
            rectangle(equalizedImg, faces[i], Scalar(0,255,255),5);
            rect_crop =  Rect(rect.x,rect.y,rect.width,rect.height);
        
        }
        Mat image_roi =  Mat(faceImg , rect_crop);
faceImg = image_roi;
namedWindow("Detected Frontal Face",CV_WINDOW_NORMAL);
if(equalizedImg.rows >0 && equalizedImg.cols >0)
  imshow("Detected Frontal Face",equalizedImg);
  
 /*
  vector<string> algorithms;
Algorithm::getList(algorithms);
int kl = (int)algorithms.size();
cout <<"Algorithms :";
cout<< kl<<endl;
for(int i=0;i<kl;i++){
	cout<< algorithms[i] <<endl;
}
*/
int w = faceImg.cols;
int h = faceImg.rows;
Mat wholeFace;
equalizeHist(faceImg, wholeFace);
int midX = w/2;
Mat leftSide = faceImg(Rect(0,0,midX,h));
Mat rightSide = faceImg(Rect(midX, 0, w-midX,h));

equalizeHist(leftSide,leftSide);
equalizeHist(rightSide, rightSide);
if(leftSide.rows >0 && leftSide.cols >0)
imshow("Left side face",leftSide);
if(rightSide.rows >0 && rightSide.cols >0)
imshow("Right Side face",rightSide);
/*
if (leftSide.width >0 && rightSide.width >0 && rightSide.height >0 && leftSide.height >0){
namedWindow("Left side face",CV_WINDOW_NORMAL);
imshow("Left side face",leftSide);
namedWindow("Right Side face",CV_WINDOW_NORMAL);
imshow("Right Side face",rightSide);
}
*/
// To Combine the three images together
for (int y =0;y <h;y++){
	for(int x=0;x<w;x++){
		int v;
		if(x<w/4){
			v = leftSide.at<uchar>(y,x);
		}
		else if(x < w*1/2){
			int lv = leftSide.at<uchar>(y,x);
			int wv = wholeFace.at<uchar>(y,x);
			//Bland more of a face 
			float f = (x-w*1/4)/(float)(w/4);
			v = cvRound((1.0f - f)*lv + (f)*wv);
		}
		else if(x < w*3/4){
			int rv = rightSide.at<uchar>(y,x-midX);
			int wv = wholeFace.at<uchar>(y,x);
			float f = (x-w*2/4)/(float)(w/4);
			v = cvRound((1.0f-f)*wv + (f)*rv);
		}
		else{
		v = rightSide.at<uchar>(y,x-midX);
	}
	faceImg.at<uchar>(y,x) = v;
	}
}
if (faceImg.rows>0 && faceImg.cols>0)
imshow("final face",faceImg);
// Smoothing
Mat filtered = Mat(faceImg.size(),CV_8U);
bilateralFilter(faceImg,filtered, 0,20.0,2.0);
if(filtered.cols >0 && filtered.rows >0)
imshow("Filtered",filtered);


}catch(Exception e){
	continue;
cerr<<"ERROR : Couldn't load face Detection ";
cerr<<"OOPSS!!"<<endl;
exit(1);

}




key = waitKey(25);
}
return 0;
}
