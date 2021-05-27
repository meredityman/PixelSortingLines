#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(1);
    filepath = "image.png";
    img.load(filepath);


    ofLogNotice("ofApp::setup") << img.getWidth() << ", " << img.getHeight();

    ofPixels & rawPixels = img.getPixels();

    vector<vector<ofColor>> pixels;

    for( int y = 0; y < img.getHeight(); y++){
        vector<ofColor> row;
        for( int x = 0; x < img.getWidth(); x++){
            row.push_back(rawPixels.getColor(x,y));
        } 
        pixels.push_back(row);
    } 


    for( int i = 0; i < pixels.size(); i++ ) {
        std::sort(pixels[i].begin(), pixels[i].end(), [](ofColor a, ofColor b) { 
            return a.getBrightness() < b.getBrightness();
        } );
    }


    ofPixels outputPixels;
    outputPixels.allocate(img.getWidth(), img.getHeight(), OF_PIXELS_RGBA);

    for( int y = 0; y < img.getHeight(); y++){
        for( int x = 0; x < img.getWidth(); x++){
            outputPixels.setColor(x, y, pixels[y][x]);
        } 
    } 
    outImg.setFromPixels(outputPixels);
}

//--------------------------------------------------------------
void ofApp::update(){

}

void ofApp::draw(){
    outImg.draw(0,0);
    //img.draw(0,0);


    std::ostringstream str;
    str << "Frame: " << ofGetFrameNum() << " | ";
    str << "Framerate: " << ofGetFrameRate() << " | ";
    ofSetWindowTitle(str.str());
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

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
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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