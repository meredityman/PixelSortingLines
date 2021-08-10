#pragma once

#include "ofMain.h"

namespace Sorters {
	static vector<vector<glm::ivec2>> patches(const ofImage & img){
		vector<vector<glm::ivec2>> lines;
		for( int y = 0; y < img.getHeight(); y++){
			if(  fmod(y, 20.0) < 6 ) continue;
			vector<glm::ivec2> coords;
			for( int x = 0; x < img.getWidth(); x++){
				coords.push_back(glm::ivec2(x,y));
			} 
			lines.push_back(coords);
		} 
		for( int x = 0; x < img.getWidth(); x++){
			if( fmod(x, 20.0) < 6 ) continue;
			vector<glm::ivec2> coords;
			for( int y = 0; y < img.getHeight(); y++){
				coords.push_back(glm::ivec2(x,y));
			} 
			lines.push_back(coords);
		} 

		std::random_shuffle(lines.begin(), lines.end());
		return lines;
	}

	static vector<vector<glm::ivec2>> lines(const ofImage & img){
		vector<vector<glm::ivec2>> lines;
		for( int y = 0; y < img.getHeight(); y+=20){
			if(  fmod(y, 20.0) < 6 ) continue;
			vector<glm::ivec2> coords;
			for( int x = 0; x < img.getWidth(); x++){
				coords.push_back(glm::ivec2(x,y));
			} 
			lines.push_back(coords);
		} 

		return lines;
	}

	static vector<vector<glm::ivec2>> curves(const ofImage & img){
		const int height = 50;
		float t = (float)ofGetFrameNum() * 2;

		vector<vector<glm::ivec2>> lines;
		for( int y = -height; y < img.getHeight(); y++ ){

			if(fmod( (y + t * 10) + 10 * ofRandom(0.0, 1.0), 40.0) < 4 ) continue;

			vector<glm::ivec2> line;
			ofPolyline pline;


			ofPoint str  = ofPoint(0                    , y - 0.5 * height * sin(t/10));
			ofPoint cpt1 = ofPoint(img.getWidth() * 0.25, y + 1.0 * ofRandomf());
			ofPoint cpt2 = ofPoint(img.getWidth() * 0.75, y + 1.0 * ofRandomf());
			ofPoint end  = ofPoint(img.getWidth()       , y + 0.5 * height * sin(t/10));

			pline.addVertex(str);


			pline.bezierTo(cpt1, cpt2,end );

			pline = pline.getResampledBySpacing(.5);

			if(pline.size() != 0){
				line.clear();
				for( size_t i = 0; i < pline.size(); i++){
					auto & p = pline[i];
					if(p.x > 0 && p.x < img.getWidth() && p.y > 0 && p.y < img.getHeight())
					line.push_back(p);
				}
				//ofLogNotice("curves") << "Num pts: " << line.size();		
				lines.push_back(line);
			}
		} 

		return lines;
	}

	static vector<vector<glm::ivec2>> circles(const ofImage & img){
		const int height = 50;
		float t = (float)ofGetFrameNum() * 2;

		vector<vector<glm::ivec2>> lines;
		for( int i = 50; i < img.getHeight(); i++ ){

			//if(fmod( (i + t * 10) + 10 * ofRandom(0.0, 1.0), 40.0) < 4 ) continue;

			vector<glm::ivec2> line;
			ofPolyline pline;

			pline.arc(
				ofPoint(0.5 * img.getWidth(), 0.5 * img.getHeight()), (float)i , (float)i, 90, 360.0 + 90, true
			);

			pline = pline.getResampledBySpacing(1.0);

			if(pline.size() != 0){
				line.resize(pline.size());
				for( size_t i = 0; i < pline.size(); i++){
					line[i] = pline[i];
				}
				ofLogNotice("curves") << "Num pts: " << line.size();		
				lines.push_back(line);
			}
		} 

		return lines;
	}
	
}


class PixelSortLine {
public:

	PixelSortLine(){

	}


	PixelSortLine(const std::vector<glm::ivec2> & _coords) : PixelSortLine() {
		setCoords(_coords);
	}

	void setCoords(const std::vector<glm::ivec2> & _coords){
		coords = _coords;
	}

//private:

	void copy(const ofPixels & pixels){
		colors.clear();
		colors.reserve(coords.size());
		for( size_t i = 0; i < coords.size(); i++){
			const glm::vec2 & coord = coords[i];
			if(coord.x >= 0 && coord.x < pixels.getWidth() && coord.y >=0 && coord.y < pixels.getHeight())
				colors.push_back( pixels.getColor( coords[i].x, coords[i].y));
			else
				colors.push_back( ofColor::black);			
		}
	}

	void sort(bool reverse = false, bool mirror = false){
		// std::sort(colors.begin(), colors.end(), [](ofColor a, ofColor b) { 
		// 			return a.getBrightness() < b.getBrightness();
		// } );
		if(reverse){
			std::sort(colors.begin(), colors.end(), [](ofColor a, ofColor b) { 
						return a.getBrightness() < b.getBrightness();
			} );
		} else {
			std::sort(colors.begin(), colors.end(), [](ofColor a, ofColor b) { 
						return a.getBrightness() < b.getBrightness();
			} );	
		}

		if(mirror) {
			std::vector<ofColor> colors_l, colors_r;

			for( size_t i = 0; i < (colors.size() - 1); i+=2){
				colors_l.push_back(colors[i]);
				colors_r.push_back(colors[i + 1]);
			}
			if(colors.size() % 2) colors_l.push_back(colors.back());

			std::copy(colors_l.begin(), colors_l.end(),   colors.begin());
			std::copy(colors_l.rbegin(), colors_l.rend(), colors.begin() + colors_l.size());
		}
	};

	void paste(ofPixels & pixels){
		for( size_t i = 0; i < coords.size(); i++){
			const glm::vec2 & coord = coords[i];
			if(coord.x >= 0 && coord.x < pixels.getWidth() && coord.y >=0 && coord.y < pixels.getHeight())
				pixels.setColor(coord.x, coord.y, colors[i]);
		}
	}

	static vector<vector<glm::ivec2>> curves(const ofImage & img){
		const int height = 50;
		float t = (float)ofGetFrameNum() * 2;

		vector<vector<glm::ivec2>> lines;
		for( int y = -height; y < img.getHeight(); y++ ){

			if(fmod( (y + t * 10) + 10 * ofRandom(0.0, 1.0), 40.0) < 4 ) continue;

			vector<glm::ivec2> line;
			ofPolyline pline;


			ofPoint str  = ofPoint(0                    , y - 0.5 * height * sin(t/10));
			ofPoint cpt1 = ofPoint(img.getWidth() * 0.25, y + 1.0 * ofRandomf());
			ofPoint cpt2 = ofPoint(img.getWidth() * 0.75, y + 1.0 * ofRandomf());
			ofPoint end  = ofPoint(img.getWidth()       , y + 0.5 * height * sin(t/10));

			pline.addVertex(str);


			pline.bezierTo(cpt1, cpt2,end );

			pline = pline.getResampledBySpacing(1.0);

			if(pline.size() != 0){
				line.resize(pline.size());
				for( size_t i = 0; i < pline.size(); i++){
					line[i] = pline[i];
				}
				//ofLogNotice("curves") << "Num pts: " << line.size();		
				lines.push_back(line);
			}
		} 

		return lines;
	}
	std::vector<glm::ivec2> coords;
	std::vector<ofColor> colors;

};


class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		
		void loadImage();
		void sortPixels();


		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		ofImage img, outImg;
		std::string filepath;

		bool reverse = false;
		bool mirror  = false;

		ofDirectory dir;
		bool saving = false;
};


