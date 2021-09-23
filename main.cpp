#include <iostream>
#include "ScreenRecorder.h"

using namespace std;

int main() {

    ScreenRecorder screen_record;

    screen_record.openCamera();
    screen_record.init_outputfile();
    screen_record.CaptureVideoFrames();

    cout<<"\nprogram executed successfully\n";

    return 0;}
