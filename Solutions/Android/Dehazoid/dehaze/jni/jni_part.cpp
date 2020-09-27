#include <jni.h>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/features2d.hpp>
#include <vector>
#include "dehaze.h"
#include <jni.h>
#include <opencv2/opencv.hpp>


using namespace std;
using namespace cv;
DeHaze *deHaze;
extern "C" {
JNIEXPORT void JNICALL
Java_org_opencv_samples_tutorial2_PreviewActivity_FindFeatures(JNIEnv *, jobject, jlong addrGray,
                                                                 jlong addrRgba);
JNIEXPORT void JNICALL Java_org_opencv_samples_tutorial2_DeHaze_n_1createHazeRemoveModel
        (JNIEnv *, jclass, jint r, jdouble t0, jdouble omega, jdouble eps, jint width,
         jint height);
JNIEXPORT void JNICALL Java_org_opencv_samples_tutorial2_DeHaze_n_1deleteHazeRemoveModel
        (JNIEnv *, jclass);
JNIEXPORT void JNICALL
Java_org_opencv_samples_tutorial2_DeHaze_n_1videoHazeRemove(JNIEnv *env, jclass type, jlong
src,
                                                            jlong dst);

JNIEXPORT void JNICALL Java_org_opencv_samples_tutorial2_PreviewActivity_FindFeatures(JNIEnv *,
                                                                                        jobject,
                                                                                        jlong addrGray,
                                                                                        jlong addrRgba) {
    Mat &mGr = *(Mat *) addrGray;
    Mat &mRgb = *(Mat *) addrRgba;
    vector<KeyPoint> v;

    Ptr<FeatureDetector> detector = FastFeatureDetector::create(50);
    detector->detect(mGr, v);
    for (unsigned int i = 0;
         i < v.size();
         i++) {
        const KeyPoint &kp = v[i];
        circle(mRgb, Point(kp.pt.x, kp.pt.y), 10, Scalar(255, 0, 0, 255));
    }
}

JNIEXPORT void JNICALL Java_org_opencv_samples_tutorial2_DeHaze_n_1createHazeRemoveModel
        (JNIEnv *, jclass, jint r, jdouble t0, jdouble omega,
         jdouble eps, jint width, jint height) {
    if (deHaze != NULL) {
        delete deHaze;
        deHaze = NULL;
    }
    deHaze = new DeHaze(r, t0, omega, eps, width, height);
    deHaze->setFPS(15);
}

JNIEXPORT void JNICALL Java_org_opencv_samples_tutorial2_DeHaze_n_1deleteHazeRemoveModel
        (JNIEnv *, jclass) {
    if (deHaze != NULL) {
        delete deHaze;
        deHaze = NULL;
    }
}

JNIEXPORT void JNICALL
Java_org_opencv_samples_tutorial2_DeHaze_n_1videoHazeRemove(JNIEnv *env, jclass type, jlong src,
                                                            jlong dst) {

    Mat &srcImage = *(Mat *) src;
    Mat &recover = *(Mat *) dst;
    recover = deHaze->videoHazeRemove(srcImage);
}
JNIEXPORT void JNICALL
Java_org_opencv_samples_tutorial2_PreviewActivity_n_1Equahist(JNIEnv *env, jobject instance,
                                                                jlong inputAddr) {

    Mat &srcImage = *(Mat *) inputAddr;
    cvtColor(srcImage,srcImage,COLOR_RGBA2RGB);
    vector<Mat> channels;
    split(srcImage,channels);
    for (int i = 0; i < srcImage.channels(); i++) {
        equalizeHist(channels[i], channels[i]);
    }
    merge(channels,srcImage);
}
}
