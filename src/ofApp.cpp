#include "ofApp.h"

//--------------------------------------------------------------
struct Portion{
    int xAxis;
    int yAxis;
    int width;
    int height;
    int size;
};

//--------------------------------------------------------------
void ofApp::setup(){
    imageWidth = 720;
    imageHeight = 480;
    imageColors = 3;
    numberRecorded = 0;
    numberOfFramesToRecord = 40;
    numberOfPortions = 40;
    maximumNumberOfFramesToRecord = 1000;
    maximumNumberOfPortions = imageHeight;
    zoom = 1;
    //----------------------------------------------------------
    videoData = new unsigned char * [maximumNumberOfFramesToRecord];
    for(int i = 0; i < maximumNumberOfFramesToRecord; i++){
        videoData[i] = new unsigned char[imageWidth * imageHeight * imageColors];
    }
    //----------------------------------------------------------
    Portions = new Portion * [maximumNumberOfPortions];
    for(int i = 0; i < maximumNumberOfPortions; i++){
        Portions[i] = new Portion;
        Portions[i]-> width = imageWidth;
    }
    //----------------------------------------------------------
    videoStream.setVerbose(true);
    videoStream.initGrabber(imageWidth, imageHeight);
    //----------------------------------------------------------
    delayed.allocate(imageWidth, imageHeight, GL_RGB);
    //----------------------------------------------------------
    Verdana.loadFont("Verdana.ttf", 8, false, true);
    //----------------------------------------------------------
    horizontalWidth = imageWidth;
    horizontalHeight = imageHeight;
    slitYAxis = new unsigned char [imageWidth * imageHeight * imageColors];
    horizontalTexture.allocate(imageWidth, imageHeight, GL_RGB);
}

//--------------------------------------------------------------
void ofApp::update(){
    videoStream.update();
    if(videoStream.isFrameNew()){
        memcpy(videoData[numberRecorded],
               videoStream.getPixels(),
               imageWidth * imageHeight * imageColors);
        portionWidth = imageWidth;
        portionHeight = imageHeight / numberOfPortions;
        portionModulus = imageHeight % numberOfPortions;
        int tempYAxis = imageHeight;
        int tempSize, tempHeight;
        int frameDifferance = (numberOfFramesToRecord / numberOfPortions);
        int portionFrame;
        for(int i = 0; i < numberOfPortions; i++){
            tempHeight = portionHeight;
            if(portionModulus > 0){
                tempHeight++;
                portionModulus--;
            }
            tempSize = portionWidth * tempHeight * imageColors;
            portionFrame = (numberRecorded - (i * frameDifferance)) % numberOfFramesToRecord;
            if(portionFrame < 0){
                portionFrame = numberOfFramesToRecord + portionFrame;
            }
            horizontalWidth = imageWidth / numberOfPortions;
            for(int j = 0; j < horizontalHeight; j++){
                memcpy((horizontalWidth * i * 3) + slitYAxis + j * imageWidth * 3, (horizontalWidth * i * 3) + videoData[portionFrame] + j * imageWidth * 3, horizontalWidth * 3);
            }
        }
        horizontalTexture.loadData(slitYAxis, imageWidth, imageHeight, GL_RGB);
        numberRecorded++;
        numberRecorded %= numberOfFramesToRecord;
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(230, 230, 255);
    ofBackground(1, 1, 1);
    horizontalTexture.draw(300, 50, imageWidth * zoom, imageHeight * zoom);
    char tempString[255];
    sprintf(tempString, "[ a/z ] --> portions: %i           \n[ s/x ] --> frames in buffer: %i            \n[ d/c ] --> zoom: %i", numberOfPortions, numberOfFramesToRecord, zoom);
    ofDrawBitmapString(tempString, 10, 600);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key=='a') {
        if (numberOfPortions < maximumNumberOfPortions && numberOfPortions < numberOfFramesToRecord) {
            numberOfPortions++;
        }
    }
    if (key=='z') {
        if (numberOfPortions > 1) {
            numberOfPortions--;
        }
    }
    if (key == 's') {
        if (numberOfFramesToRecord < maximumNumberOfFramesToRecord) {
            numberOfFramesToRecord++;
        }
    }
    if (key == 'x') {
        if (numberOfFramesToRecord > numberOfPortions) {
            numberOfFramesToRecord--;
        }
    }
    if (key == 'd') {
        if (zoom < 5) {
            zoom ++;
        }
    }
    if (key == 'c') {
        if (zoom > 1) {
            zoom --;
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}
