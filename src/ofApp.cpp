#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    fingerMovie.loadMovie("test.mov", OF_QTKIT_DECODE_PIXELS_ONLY);
    fingerMovie.play();
    fingerMovie.firstFrame();
    
	svg.load("loadme.svg");
    ofPoint svgSize(svg.getWidth(), svg.getHeight());
    
	for (int i = 0; i < svg.getNumPath(); i++){
		ofPath p = svg.getPathAt(i);
		// svg defaults to non zero winding which doesn't look so good as contours
        //need to do this in order to get outlines!
		p.setPolyWindingMode(OF_POLY_WINDING_ODD);
        
        if (p.getOutline().size() > 0){
            centers.push_back(p.getOutline()[0].getCentroid2D() / svgSize);
        } else {
            ofLogNotice() << "oops";
            centers.push_back(ofPoint(0, 0));
        }
	}
    ofLogNotice() << svg.getWidth() << "x" << svg.getHeight();
}

//--------------------------------------------------------------
void ofApp::update(){
    fingerMovie.nextFrame();
    fingerMovie.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofPoint svgSize(svg.getWidth(), svg.getHeight());
    for(int i = 0; i < svg.getNumPath(); i++){
        if (ofGetMousePressed()){
            ofSetColor(ofRandom(255));
            ofCircle(centers[i] * svgSize, 1);
        } else {
            svg.getPathAt(i).draw();
        }
    }
    /*
	if(ofGetMousePressed()) {
		ofNoFill();
		for (int i = 0; i < (int)outlines.size(); i++){
			ofPolyline & line = outlines[i];
            
			int num = step * line.size();
            
			ofBeginShape();
			for (int j = 0; j < num; j++){
				ofVertex(line[j]);
			}
			ofEndShape();
		}
	} else {
		svg.draw();
	}
     */
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
