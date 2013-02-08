#include "ofMain.h"
#include <PvApi.h>

class mantaThread : public ofThread {


    public:



    int camFrameSize;

    tPvUint32       camCount, camConnect;
    tPvCameraInfoEx   cameraList[MAX_CAM];

    unsigned long   cameraNum;
    unsigned long   cameraRle;

    unsigned long   cameraUID;
    tPvHandle       cameraHandle;
    tPvFrame        cameraFrame;


    ofImage   mantaImage;
    ofTexture camText;

    unsigned char* pixels;

    mantaThread() {

        /*
        add initCapture here
        */

        mantaImage.allocate(656, 492, OF_IMAGE_GRAYSCALE);
        //pixels = new unsigned char[656*492];

        if(PvInitialize() == ePvErrSuccess){
        cout<<"api initialized"<<endl;
    }

        while( PvCameraCount() < 1 ) {
            ofSleepMillis(250);
    }

    camCount = PvCameraListEx(cameraList,1,&camConnect, sizeof(cameraList));

    cout<<cameraList[0].ModelName<<endl;

    cout<<"opening camera"<<endl;

    cameraUID = cameraList[0].UniqueId;

    if(PvCameraOpen( cameraUID, ePvAccessMaster, &cameraHandle ) == ePvErrSuccess){

        cout<<"camera opened"<<endl;
    }

    unsigned long FrameSize = 0;

    cout<<"settings BPF"<<endl;
    if(PvAttrUint32Get( cameraHandle, "TotalBytesPerFrame", &FrameSize )==ePvErrSuccess){

            cameraFrame.ImageBuffer = new char[FrameSize];
            cameraFrame.ImageBufferSize = FrameSize;

            camFrameSize = FrameSize;
            pixels = new unsigned char[FrameSize];

        cout<<"BPF set"+ofToString(FrameSize)<<endl;
    }

    cout<<"setting cap mod"<<endl;

    if(PvCaptureStart(cameraHandle) == ePvErrSuccess){

        cout<<"cap mod set"<<endl;
    }

    cout<<"setting free run mode"<<endl;

    if(PvAttrEnumSet(cameraHandle,"FrameStartTriggerMode","Freerun")==ePvErrSuccess){

        cout<<"cam set to FreeRun"<<endl;
    }

    cout<<"setting acquisition"<<endl;

    if(PvCommandRun(cameraHandle,"AcquisitionStart")==ePvErrSuccess){

        cout<<"acquisition started"<<endl;
        }

    }

    void stopThread(){

        PvCaptureEnd(cameraHandle) ;

        PvCameraClose(cameraHandle);
        cout<<"closing camera"<<endl;

        PvUnInitialize();
        cout<<"closing api"<<endl;
    }

   // the thread function
    void threadedFunction() {

        // start

        while(isThreadRunning()) {

            /*
            add all capturefunc here.
            */
            if( PvCaptureQueueFrame( cameraHandle, &cameraFrame, NULL) == ePvErrSuccess ){
              if(PvCaptureWaitForFrameDone(cameraHandle, &cameraFrame, PVINFINITE) == ePvErrSuccess){
                     //lock();
                    memcpy(pixels, cameraFrame.ImageBuffer, 656*492);
                    lock();
                    mantaImage.setFromPixels(pixels, 656, 492, OF_IMAGE_GRAYSCALE );
                    unlock();
                }
            } else {

                }
            }
        }
};















