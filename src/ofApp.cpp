#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    fingerMovie.loadMovie("test.mov", OF_QTKIT_DECODE_PIXELS_ONLY);
    fingerMovie.play();
    fingerMovie.firstFrame();
    
	svg.load("loadme.svg");
    svgSize.x = svg.getWidth();
    svgSize.y = svg.getHeight();
    vidSize.x = fingerMovie.getWidth();
    vidSize.y = fingerMovie.getHeight();
    float svgRatio = svgSize.x/svgSize.y;
    float vidRatio = vidSize.x/vidSize.y;
    if (svgRatio >= vidRatio){
        VidSample.x = 0;
        VidSample.width = 1;
        float apparentSvgHeight = vidSize.y * vidRatio / svgRatio;
        VidSample.height = apparentSvgHeight / vidSize.y;
        VidSample.y = (1 - VidSample.height) / 2;
    } else {
        VidSample.y = 0;
        VidSample.height = 1;
        float apparentSvgWidth = vidSize.x / vidRatio * svgRatio;
        VidSample.width = apparentSvgWidth / vidSize.x;
        VidSample.x = (1 - VidSample.width) / 2;
    }
    
	for (int i = 0; i < svg.getNumPath(); i++){
		ofPath p = svg.getPathAt(i);
        //p.setUseShapeColor(false);
		// svg defaults to non zero winding which doesn't look so good as contours
        //need to do this in order to get outlines!
		p.setPolyWindingMode(OF_POLY_WINDING_ODD);
        
        ofPoint currCenter;
        if (p.getOutline().size() > 0){
            currCenter = p.getOutline()[0].getCentroid2D() / svgSize;
            centers.push_back(ofPoint(
                    currCenter.x * VidSample.width + VidSample.x,
                    currCenter.y * VidSample.height + VidSample.y));
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
    ofPushMatrix();
    float scaleAmt = MIN(ofGetWidth() / svgSize.x, ofGetHeight() / svgSize.y);
    ofScale(scaleAmt, scaleAmt);
    for(int i = 0; i < svg.getNumPath(); i++){
        if (!ofGetMousePressed()){
            ofPixelsRef pix = fingerMovie.getPixelsRef();
            int ind = pix.getPixelIndex(
                    (int)(centers[i].x * vidSize.x),
                    (int)(centers[i].y * vidSize.y));
            ofSetColor(pix[ind], pix[ind+1], pix[ind+2]);
            ofPath p = svg.getPathAt(i);
            p.setUseShapeColor(false);
            //p.setFillColor(ofColor(ofRandom(255)));
            p.draw();
        } else {
            svg.getPathAt(i).draw();
        }
    }
    ofPopMatrix();
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
