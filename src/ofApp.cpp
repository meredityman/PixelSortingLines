#include "ofApp.h"



//--------------------------------------------------------------
void ofApp::setup(){

    img.load("image.png");
}

//--------------------------------------------------------------
void ofApp::update(){

    if( !img.isAllocated()) return;

    ofPixels rawPixels;
    rawPixels = img.getPixels();

    vector<vector<glm::ivec2>> lines = Sorters::curves(img);
	ofLogNotice("curves") << "Num Lines: " << lines.size();

    ofPixels outputPixels = rawPixels;
    for( size_t i = 0; i < lines.size(); i++){
        PixelSortLine line = PixelSortLine(lines[i]);
        ofLogNotice("ofApp::update") << "Line:" << i;

        line.copy(rawPixels);
        line.sort();
        line.paste(outputPixels);
    }

    outImg.setFromPixels(outputPixels);
}

//--------------------------------------------------------------
void ofApp::draw(){


    if( !outImg.isAllocated()) return;
    outImg.draw(0,0);
    //img.draw(0,0);

    std::ostringstream str;
    str << "Frame: " << ofGetFrameNum() << " | ";
    str << "Framerate: " << ofGetFrameRate() << " | ";
    ofSetWindowTitle(str.str());
}

//--------------------------------------------------------------
void ofApp::loadImage(){
    filepath = "image.png";
    img.load(filepath);
    ofLogNotice("ofApp::setup") << img.getWidth() << ", " << img.getHeight();
}
//--------------------------------------------------------------
void ofApp::sortPixels(){

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
    for( auto & path : dragInfo.files){
        ofFile file(path);

        img.load(path);

        ofRectangle rect(0, 0, img.getWidth(), img.getHeight());
        rect.scaleTo(ofRectangle(0, 0, 512, 512));
        img.resize(rect.width, rect.height);
    }
}