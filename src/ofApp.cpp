#include "ofApp.h"

void ofApp::setup(){
    grabber.initGrabber(640,480);
    grabberAsGray.allocate(640, 480, OF_IMAGE_GRAYSCALE);
    bitPlane.allocate(640, 480, OF_IMAGE_GRAYSCALE);
    duckheight = ofGetHeight()/2;
    bitposition = ofGetWidth()/2;
    bits = 8;
    number = 0;
}

void ofApp::update(){
    grabber.update();
    
    if (grabber.isFrameNew()){
        
        unsigned char * colorPix = grabber.getPixels();
        unsigned char * grayPix = grabberAsGray.getPixels();
        
        for (int i = 0; i < 640*480; i++){
            grayPix[i] = colorPix[i*3];
            bitPlane.getPixels()[i] = (grayPix[i] >> significantdigit) & 0x01 ? 255 : 0;
        }

        significantdigit = bits - 1 - (bitposition * bits / ofGetWidth());

        number = 0;
        for(int bit=0; bit<bits; bit++)
            if(sectionSignificant(bit))
                number += powf(2,bit);
    }

    grabberAsGray.update();
    bitPlane.update();
}

void ofApp::draw(){
    // flip camera so that its not a mirror
    glPushMatrix();
    glTranslated(ofGetWidth(), 0, 0);
    glScalef(-1, 1, 0);
        bitPlane.draw(0,0);
    glPopMatrix();

    ofSetColor(0,255,255);
    ofLine(0,duckheight,ofGetWidth(),duckheight);
    ofSetColor(255,0,255);
    ofLine(bitposition,0,bitposition,ofGetHeight());
    ofSetColor(255,255,0);
    for(int i=0;i<bits;i++)
        ofLine(i*ofGetWidth()/bits,0,i*ofGetWidth()/bits,ofGetHeight());


    ofDrawBitmapStringHighlight(ofToString(significantdigit), 20, 20);
    ofDrawBitmapStringHighlight(ofToString(number), ofGetWidth()-40, ofGetHeight()-40);
    ofDrawBitmapStringHighlight(ofToString(duckheight), ofGetWidth()-40, 20);

    for(int i=0;i<bits;i++)
        ofDrawBitmapStringHighlight(ofToString(number >> (7-i) & 0x01), i*ofGetWidth()/bits + (ofGetWidth()/bits/2), ofGetHeight()/2);
    ofSetColor(255,255,255);
}

void ofApp::mouseDragged(int x, int y, int button){
    bitposition = x;
    duckheight = y;
}

void ofApp::mousePressed(int x, int y, int button){
    bitposition = x;
    duckheight = y;
}

void ofApp::mouseReleased(int x, int y, int button){
    duckheight = y;
}

bool ofApp::sectionSignificant(int section) {
    int pixels=0;
    int width=ofGetWidth()/bits;
    int color=0;
    int offset=section * width;
    for(int y=0; y<duckheight; y++){
        for(int x = offset; x < offset + width; x++){
            pixels += bitPlane.getPixels()[x+(y*bitPlane.width)] > 0 ? 1 : -1;
        }
    }
    return pixels < 0;
}