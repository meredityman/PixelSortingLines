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

    vector<vector<glm::ivec2>> lines = Sorters::circles(img);
	ofLogNotice("curves") << "Num Lines: " << lines.size();

    ofPixels outputPixels = rawPixels;
    for( size_t i = 0; i < lines.size(); i++){
        PixelSortLine line = PixelSortLine(lines[i]);

        line.copy(rawPixels);
        line.sort(reverse);
        line.paste(outputPixels);
    }

    outImg.setFromPixels(outputPixels);

    if(saving)
        outImg.save((dir.path()  + '/' + ofGetTimestampString() + ".png"));
}

//--------------------------------------------------------------
void ofApp::draw(){


    if( !outImg.isAllocated()) return;
    outImg.draw(0,0);
    //img.draw(0,0);

    std::ostringstream str;
    str << "Frame: " << ofGetFrameNum() << " | ";
    str << "Framerate: " << ofGetFrameRate() << " | ";
    str << "Recording: " << (saving ? "Yes" : "No") << " | ";
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
    if( key == OF_KEY_CONTROL){
        dir.open("");
        outImg.save((dir.path() + '/' + ofGetTimestampString() + ".png"));
    }
    if( key == ' '){
        if(!saving){
            saving = true;
            dir.open(ofGetTimestampString());
            ofDirectory::createDirectory(dir.path());
            outImg.save((dir.path()  + '/' + ofGetTimestampString() + ".png"));
        } else {
            saving = false;
        }
    }
    if( key == 'r'){
         reverse = !reverse;
    }
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
        rect.scaleTo(ofRectangle(0, 0, 720, 720));
        img.resize(rect.width, rect.height);
    }
}