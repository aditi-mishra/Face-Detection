# Face-Detection


Image processing is a method to convert an image into digital form and perform some operations on it, in order to get an enhanced image or to extract some useful information from it. 
It is among rapidly growing technologies today, with its applications in various aspects of a business. 
Image Processing includes four steps- 
1. Image Capture 
2. Image Sharpening and Restoration 
3. Image retreival - Seek for the image of interest. 
4. Image Recognition - Distinguish the objects in an image 

In our Project, We have made a Face detection Model. In this , we studied about processing of image using Open Source Library, OpenCV (Open Computer Vision) . We first did Image processing on our digital image by using in-built OpenCv computer Algorithms. Then, to detect the face, we passed our image to the in-built OpenCV classifier , LBP based Classifier. This pretrained model works on our image , and detects the face. Then, this face area is further preproccessed , and smoothed to get us just our face in a  new Window. 

The libraries , we used are - 

1. Core Module -> Its a compact module defining basic data structures, including the dense multi- dimensional array Mat and basic functions used by all other modules. 

2. Image Processing -> Its an image processing module that includes linear and non- linear image filtering, geometrical image transformations (resize, affine and perspective warping , generic table - based remapping), color space conversion, histograms etc. 

3. features2d - > It has salient feature detectors, descriptors and descriptor matches. 

4. Highgui -> Its an easy to use interface to simple UI capabilities. 

5. Video I/O -> Its an easy to use interface to video capturing and video codecs. 

6. objdetect -> It helps in detection of objects and instances of the predefined classes.for example, faces, eyes, mugs etc. 

We captured the videostream from our webcam. The, we stored each frame of our video stream into a mat object. We converted the Mat color object into gray object. The, we scaled our gray image to a constant width of 320. For a width of 320, we also scaled our height appropriately. This was done for our cascade classifier to run better. As , we are using pre- built classifier, it works better on small width images, but not too small. So, we chose a medium Size image.
Now coming to the classifier part which will detect face:
In 2001 Viola and Jones invented the Haar based cascade classifier for object detection and in 2002 in was improved by Heinhart and Maydt. The result is an object detector that is both fast and reliable (detects approx. 95% of frontal face correctly).
It works not only for frontal faces but also side view faces, eyes, mouth etc. however in our project we have used only frontal face classifier.
We have used LBP based detector as it is several times faster than Haar based detector.
Haar based detector: it performs detection by doing comparison like; if we look at frontal face, region with eye should be darker than forehead and cheeks, and region with mouth darker than cheeks.
But, for LBP based face detector It performs comparison but uses histograms of pixel intensity comparison such as edges, corners and flat regions.
Then, face preprocessing is performed to give final result Separate histogram equalization for left and right sides
This process standardizes the brightness and contrast on both the left and right hand sides of face independently.
Smoothening - It reduces the image noise using a bilateral filter.

