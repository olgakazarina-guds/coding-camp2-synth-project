#include "ofAPP"
#include "ofMain"


int main(){
    ofGLFWWindowSettings windowSettings;
    windowSettings.setSize(1024,  700);
    windowSettings.setGLVersion(3, 2);
    ofCreateWindow(windowSettings);

    ofRunApp(new ofAPP);
}