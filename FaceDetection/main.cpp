#define DELAY 30
#define ESC_KEY 27

#include <iostream>

#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/core.hpp"

using namespace cv;
using namespace std;

/*
 * Путь к камере: /dev/video0
 */

const char* helper = "02_FaceDetection.exe <model_file> [<video>]\n\
        \t<model_file> - полное имя файла с моделью\n\
        \t<video> - путь до видеофайла (по умолчанию \n\
        видеопоток принимается с камеры)\n";

int main(int argc, char *argv[])
{
    /*Путь к файлу модели*/
    char *modelFileName = "/home/blackhand/demilaris/proj/FaceDetection/haarcascade_frontalface_default.xml",
    *videoFileName = 0;

/* 
 * 
 * 
 *
    if (argc <2)
    {
        printf("%s",helper);
        return 1;
    }
    modelFileName = argv[1];
    {
        if (argc > 2)
        videoFileName = argv[2];
    }
 */
    CascadeClassifier cascade;
    cascade.load(modelFileName);

    VideoCapture capture;

    if (videoFileName == 0)
    {
        capture.open(0);
    }
     else
        {
            capture.open(videoFileName);
        }
    if (!capture.isOpened())
    {
        printf ("Incorrect capture name.\n");
        return 1;
    }

    const char* winName = "video";
    namedWindow(winName);


    char key = -1;
    Mat image,gray;
    vector<Rect> objects;

    capture >> image;

    while (image.data !=0 && key != ESC_KEY)
    {
        cvtColor(image,gray,COLOR_BGR2GRAY);
        cascade.detectMultiScale(gray, objects);
        for (int i = 0;i <objects.size(); i++)
        {
            rectangle(image,
                   Point (objects[i].x,objects[i].y),
                   Point(objects[i].x+objects[i].width,
                        objects[i].y+objects[i].height),
                   CV_RGB(255,0,0),2);


        }
        imshow(winName,image);
                key = waitKey(DELAY);
                capture >>image;
        gray.release();
        objects.clear();
    }

    capture.release();



}
