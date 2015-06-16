#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    //main setup
    ofBackground(0);
    ofSetVerticalSync(true);
	ofEnableSmoothing();

    ofEnableAlphaBlending();

    // timeline setup
    ofxTimeline::removeCocoaMenusFromGlut("AllTracksExample");
	timeline.setup();
	timeline.setDurationInSeconds(60);
    timeline.addFlags("screen 1");
	timeline.addFlags("screen 2");
	timeline.addFlags("screen 3");
	timeline.addFlags("screen 4");
    timeline.setPageName("Page 1");
	timeline.setCurrentPage(0);
    timeline.enableSnapToOtherKeyframes(false);
	timeline.setLoopType(OF_LOOP_NORMAL);
	timeline.loadTracksFromFolder(ofToDataPath("seq1/"));

	numClear = 0;

	ofAddListener(timeline.events().bangFired, this, &ofApp::bangFired);
    //gui stuff

    wichUI = 0;
    guiFont.loadFont("Square.ttf", 16);
    buttonXpad = 20;
    buttonYpad = 2;
    radioPadX = 10;
    radioPadY = 20;

    buttonsNames[0] = "LOAD";
    buttonsNames[1] = "RECT";
    buttonsNames[2] = "SWITCH";
    buttonsNames[3] = "MAP";
    buttonsNames[4] = "SAVE";
    buttonsNames[5] = "CLEAR";

    for(int i = 0; i<sizeof(radioButtons)/sizeof(ofRectangle); i++){

        radioButtons[i].x = radioPadX+(timeline.getWidth()/6)*i;
        radioButtons[i].y = timeline.getHeight()+radioPadY;
        radioButtons[i].width = timeline.getWidth()/10;
        radioButtons[i].height = 20;
    }

    //osc setup
    ctlz[0].setup(HOST1, CTLPORT);
    ctlz[1].setup(HOST2, CTLPORT);
    ctlz[2].setup(HOST3, CTLPORT);
    ctlz[3].setup(HOST4, CTLPORT);
    //ctlz[4].setup(HOST5, CTLPORT);

    mess1.setAddress("/NUMVID");
    mess2.setAddress("/NUMVID");
    mess3.setAddress("/NUMVID");
    mess4.setAddress("/NUMVID");

    //preview setup

    previewScreens[0].x = 240;
    previewScreens[0].y = 135;

    previewScreens[1].x = 220;
    previewScreens[1].y = 115;

    previewScreens[2].x = 200;
    previewScreens[2].y = 95;

    sliceZone.x = 0;//5;
    sliceZone.y = 360;
    sliceZone.width = (ofGetWidth()/2);
    sliceZone.height = 350;

    //13"
    videoProjections[0].set(previewScreens[0].x,  previewScreens[0].y);
    videoProjections[0].setPosition(ofGetWidth()/2+(previewScreens[0].x/2)*1.2, timeline.getHeight()+(previewScreens[0].y/2)*2.4, 0);
    videoProjections[0].setResolution(8, 8);
    //10"
    videoProjections[1].set(previewScreens[1].x,  previewScreens[1].y);
    videoProjections[1].setPosition(ofGetWidth()/2+(previewScreens[1].x/2)*4, timeline.getHeight()+(previewScreens[1].y/2)*2.4,  0);
    videoProjections[1].setResolution(8, 8);
    //10"
    videoProjections[2].set(previewScreens[1].x,  previewScreens[1].y);
    videoProjections[2].setPosition(ofGetWidth()/2+(previewScreens[1].x/2)*1.2, timeline.getHeight()+(previewScreens[1].y/2)*5.5, 0);
    videoProjections[2].setResolution(8, 8);
    //8"
    videoProjections[3].set(previewScreens[2].x, previewScreens[2].y);
    videoProjections[3].setPosition(ofGetWidth()/2+(previewScreens[2].x/2)*4, timeline.getHeight()+(previewScreens[1].y/2)*4.5, 0);
    videoProjections[3].setResolution(8, 8);


    devices[0].x = ofGetWidth()/2+(previewScreens[0].x/2)*1.2 - previewScreens[0].x/2;
    devices[0].y = timeline.getHeight()+(previewScreens[0].y/2)*2.4 - previewScreens[0].y/2;
    devices[0].width = previewScreens[0].x;
    devices[0].height = previewScreens[0].y;

    devices[1].x = ofGetWidth()/2+(previewScreens[1].x/2)*4 - previewScreens[1].x/2;
    devices[1].y = timeline.getHeight()+(previewScreens[1].y/2)*2.4 - previewScreens[1].y/2;
    devices[1].width = previewScreens[1].x;
    devices[1].height = previewScreens[1].y;

    devices[2].x = ofGetWidth()/2+(previewScreens[1].x/2)*1.2 - previewScreens[1].x/2;
    devices[2].y = timeline.getHeight()+(previewScreens[1].y/2)*5.5 - previewScreens[1].y/2;
    devices[2].width = previewScreens[1].x;
    devices[2].height = previewScreens[1].y;

    devices[3].x = ofGetWidth()/2+(previewScreens[2].x/2)*4 - previewScreens[2].x/2;
    devices[3].y = timeline.getHeight()+(previewScreens[2].y/2)*5.5 - previewScreens[2].y/2;
    devices[3].width = previewScreens[2].x;
    devices[3].height = previewScreens[2].y;

    numLoaded = 0;
    wichSel = 0;
    wichMedia = 0;
    maxSel = 4;

    for(int i = 0; i<maxSel;i++){

        selections[i].x = sliceZone.x;
        selections[i].y = sliceZone.y;
        selections[i].width = sliceZone.width;
        selections[i].height = sliceZone.height;
    }
    loadPath = "/home/ekko/wall_box/Dropbox/wall_box/";
    //wall_files.loadFile(loadPath+"wall.xml");


    seq_Receive.setup(SEQPORT);


}

//--------------------------------------------------------------
void ofApp::bangFired(ofxTLBangEventArgs& args){

	int num = args.track->getName()[7] - 48;

    switch(num){

    case 1:
            mess1.clear();
            mess1.setAddress("/NUMVID");

            mess1.addIntArg(ofToInt(args.flag));
            ctlz[num - 1].sendMessage(mess1);

    break;
    case 2:
            mess2.clear();
            mess2.setAddress("/NUMVID");

            mess2.addIntArg(ofToInt(args.flag));
            ctlz[num - 1].sendMessage(mess2);
    break;
    case 3:
            mess3.clear();
            mess3.setAddress("/NUMVID");

            mess3.addIntArg(ofToInt(args.flag));
            ctlz[num - 1].sendMessage(mess3);
    break;
    case 4:
            mess4.clear();
            mess4.setAddress("/NUMVID");

            mess4.addIntArg(ofToInt(args.flag));
            ctlz[num - 1].sendMessage(mess4);
    break;
    }
}

//--------------------------------------------------------------
void ofApp::update(){

    while(seq_Receive.hasWaitingMessages()){

		ofxOscMessage m;
		seq_Receive.getNextMessage(&m);

        if(m.getAddress() == "/PLAY"){
            cout<<"play received"<<endl;
            timeline.setCurrentFrame(0);
            timeline.play();

        }else if(m.getAddress() == "/STOP"){
            cout<<"stop received"<<endl;
            timeline.stop();
        }else if(m.getAddress() == "/SEQ"){

            cout<<"load received"<<endl;

            switch(m.getArgAsInt32(0)){

            case 0:
                timeline.loadTracksFromFolder(ofToDataPath("seq1/"));
            break;
            case 1:
                timeline.loadTracksFromFolder(ofToDataPath("seq2/"));
            break;
            case 2:
                timeline.loadTracksFromFolder(ofToDataPath("seq3/"));
            break;
            }

        }
    }
}

void ofApp::drawGui(){
    //seperator
    ofPushMatrix();
        ofPushStyle();
            ofSetLineWidth(2);
            ofSetColor(255, 255, 255);
            ofLine(ofGetWidth()/2, timeline.getHeight(), ofGetWidth()/2, ofGetHeight());
            ofLine(0, timeline.getHeight()+(radioPadY*2)+5, ofGetWidth()/2,timeline.getHeight()+(radioPadY*2)+5);
        ofPopStyle();
    ofPopMatrix();
    //
    //radioButtons
    ofPushMatrix();
        ofPushStyle();
        ofNoFill();
        ofSetColor(0, 255, 0);
            for(int i = 0; i<sizeof(radioButtons)/sizeof(ofRectangle);i++){
                ofRect(radioButtons[i].x, radioButtons[i].y, radioButtons[i].width, radioButtons[i].height);
                ofPushStyle();
                    ofSetColor(255);
                    guiFont.drawString(buttonsNames[i], radioButtons[i].x+buttonXpad, radioButtons[i].y+radioPadY-buttonYpad);
                    ofRect(sliceZone.x, sliceZone.y, sliceZone.width, sliceZone.height);

                ofPopStyle();
            }
        ofPopStyle();
    ofPopMatrix();
    // ui for FILES/RECTANGLE/EFFECTS
    ofPushMatrix();

        for(int i = 0; i<sizeof(videoProjections)/sizeof(ofPlanePrimitive); i++){
            if(numLoaded > 0){
                //ofRect(devices[i].x, devices[i].y, devices[i].width, devices[i].height);
                images[wichMedia].getTextureReference().bind();
                    videoProjections[i].draw();
                images[wichMedia].getTextureReference().unbind();


            }
        }
    ofPopMatrix();
    switch(wichUI){
    case 0:
    ofPushMatrix();
        ofTranslate(0, timeline.getHeight()+(radioPadY*2)+20);
        for(int i = 0; i<fileNames.size(); i++){
            guiFont.drawString(ofToString(i) + " : " + fileNames[i], radioPadX, radioPadY+30*i);
        }
    ofPopMatrix();
    break;
    case 1:
        ofPushMatrix();
            ofTranslate(0, timeline.getHeight()+(radioPadY*2)+20);
            ofPushStyle();
                ofNoFill();
                ofSetLineWidth(2);
                ofSetColor(255);

        ofPopMatrix();
        ofPushStyle();
            ofNoFill();

            if(numLoaded>0){
                images[wichMedia].getFrameForTime(ofGetElapsedTimef())->draw(sliceZone.x,sliceZone.y, sliceZone.width, sliceZone.height);
            }
            ofRect(sliceZone.x, sliceZone.y, sliceZone.width, sliceZone.height);

        ofPushStyle();
        for(int i = 0; i<sizeof(selections)/sizeof(ofRectangle);i++){
                if(wichSel == i){

                        ofSetColor(255, 0, 0);
                        ofRect(selections[i].x, selections[i].y, selections[i].width, selections[i].height);
                }
                ofRect(selections[i].x, selections[i].y, selections[i].width, selections[i].height);
                ofSetColor(255);
        }

    break;
    }
}
//--------------------------------------------------------------
void ofApp::draw(){

    timeline.draw();
    drawGui();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    if(key == 's'){

        //saveToXML();
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

    if(sliceZone.inside(x, y)){
        selections[wichSel].width = x - selections[wichSel].x;
        selections[wichSel].height = y - selections[wichSel].y;
        m_selections[wichSel].width  = ofMap(selections[wichSel].width, 0, sliceZone.width, 0, images[wichMedia].getWidth());
        m_selections[wichSel].height = ofMap(selections[wichSel].height, 0, sliceZone.height,0, images[wichMedia].getHeight());

    }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

    if(sliceZone.inside(x, y)){
        selecting = true;

        selections[wichSel].x = x ;
        selections[wichSel].y = y ;
        m_selections[wichSel].x = ofMap(selections[wichSel].x - sliceZone.x, 0, sliceZone.width, 0, images[wichMedia].getWidth());
        m_selections[wichSel].y = ofMap(selections[wichSel].y - sliceZone.y, 0, sliceZone.height, 0, images[wichMedia].getHeight());

    }
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

    ofPoint mouseLoc;//play.spotify.com/artist/4mtHSXwIHihO6MWNq5Qoko
    mouseLoc.x = x;
    mouseLoc.y = y;
    int wichButt;

    if(sliceZone.inside(mouseLoc)){
            if(selections[wichSel].width>10 && selections[wichSel].height>10){

            cout<<"unmapped selections"<<endl;
            cout<<selections[wichSel].x<<endl;
            cout<<selections[wichSel].y<<endl;
            cout<<selections[wichSel].width<<endl;
            cout<<selections[wichSel].height<<endl;
            cout<<"mapped"<<endl;
            cout<<m_selections[wichSel].x<<endl;
            cout<<m_selections[wichSel].y<<endl;
            cout<<m_selections[wichSel].width<<endl;
            cout<<m_selections[wichSel].height<<endl;


            videoProjections[wichSel].mapTexCoords(m_selections[wichSel].x, m_selections[wichSel].y, m_selections[wichSel].x + m_selections[wichSel].width , m_selections[wichSel].y + m_selections[wichSel].height);

            selecting = false;

            //sending LOCS to CLIENTS
             ofLog(OF_LOG_NOTICE, "send osc");
            if(wichSel == 0){

                ofxOscMessage locMess1;
                locMess1.setAddress("/LOC");

                locMess1.addFloatArg(ofMap(m_selections[wichSel].x, 0, images[wichMedia].getWidth(), 0.0, 1.0));
                locMess1.addFloatArg(ofMap(m_selections[wichSel].y, 0, images[wichMedia].getHeight(), 0.0, 1.0));
                locMess1.addFloatArg(ofMap(m_selections[wichSel].width, 0, images[wichMedia].getWidth(), 0.0, 1.0));
                locMess1.addFloatArg(ofMap(m_selections[wichSel].height, 0,images[wichMedia].getHeight(), 0.0, 1.0));

                ctlz[wichSel].sendMessage(locMess1);
            }else if(wichSel == 1){

                ofxOscMessage locMess2;
                locMess2.setAddress("/LOC");

                locMess2.addFloatArg(ofMap(m_selections[wichSel].x, 0, images[wichMedia].getWidth(), 0.0, 1.0));
                locMess2.addFloatArg(ofMap(m_selections[wichSel].y, 0, images[wichMedia].getHeight(), 0.0, 1.0));
                locMess2.addFloatArg(ofMap(m_selections[wichSel].width, 0, images[wichMedia].getWidth(), 0.0, 1.0));
                locMess2.addFloatArg(ofMap(m_selections[wichSel].height, 0, images[wichMedia].getHeight(), 0.0, 1.0));

                ctlz[wichSel].sendMessage(locMess2);

            }else if(wichSel == 2){

                ofxOscMessage locMess3;
                locMess3.setAddress("/LOC");

                locMess3.addFloatArg(ofMap(m_selections[wichSel].x, 0, images[wichMedia].getWidth(), 0.0, 1.0));
                locMess3.addFloatArg(ofMap(m_selections[wichSel].y, 0, images[wichMedia].getHeight(), 0.0, 1.0));
                locMess3.addFloatArg(ofMap(m_selections[wichSel].width, 0, images[wichMedia].getWidth(), 0.0, 1.0));
                locMess3.addFloatArg(ofMap(m_selections[wichSel].height, 0, images[wichMedia].getHeight(), 0.0, 1.0));

                ctlz[wichSel].sendMessage(locMess3);
            }
            else if(wichSel == 3){

                ofxOscMessage locMess4;
                locMess4.setAddress("/LOC");

                locMess4.addFloatArg(ofMap(m_selections[wichSel].x, 0, images[wichMedia].getWidth(), 0.0, 1.0));
                locMess4.addFloatArg(ofMap(m_selections[wichSel].y, 0, images[wichMedia].getHeight(), 0.0, 1.0));
                locMess4.addFloatArg(ofMap(m_selections[wichSel].width, 0, images[wichMedia].getWidth(), 0.0, 1.0));
                locMess4.addFloatArg(ofMap(m_selections[wichSel].height, 0, images[wichMedia].getHeight(), 0.0, 1.0));

                ctlz[wichSel].sendMessage(locMess4);
            }
        }
    }
    for(int i = 0; i<sizeof(devices)/sizeof(ofRectangle); i++){

                if(devices[i].inside(x, y)){
                    wichSel = i;
                    cout<<wichSel<<endl;
                    /*
                    if(mapMode = true){
                        ofxOscMessage numVid;
                        numVid.setAddress("/NUMVID");
                        numVid.addIntArg(wichMedia);
                        ctlz[wichSel].sendMessage(numVid);
                        vidMap[wichSel] = wichMedia;
                        mapMode = false;
                    }
                    */
                }
            }

    for(int i = 0; i<sizeof(radioButtons)/sizeof(ofRectangle); i++){

            if(radioButtons[i].inside(mouseLoc)){
                    wichButt = i;
                    if(i == 0){
                        clicCount ++;
                    }
                }
            }

    switch(wichButt){

    case 0:
        cout<<"loading"<<endl;
        wichUI = 0;
        if(clicCount == 2){
            showDialog();
            clicCount = 0;
        }

    break;
    case 1:
        wichUI = 1;
    break;
    case 2:
        cout<<"switch"<<endl;
        wichMedia = (wichMedia+1)%numLoaded;
        cout<<wichMedia<<endl;
        switchMedia(wichMedia);
    break;
    case 3:
        mapMode = true;
    break;
    case 4:
        //saveToXML();
        showSaveDialog();
    break;
    case 5:
        images.clear();
        fileNames.clear();
        filePath.clear();
        numLoaded = 0;
        sendClear();

        switch(numClear){

        case 0:
                cout<<ofToString(numClear)<<endl;
                timeline.saveTracksToFolder(ofToDataPath("seq1/"));
                timeline.clear();

        break;
        case 1:
                cout<<ofToString(numClear)<<endl;
                timeline.saveTracksToFolder(ofToDataPath("seq2/"));
                timeline.clear();

        break;
        case 2:
                cout<<ofToString(numClear)<<endl;
                timeline.saveTracksToFolder(ofToDataPath("seq3/"));
                timeline.clear();

        break;
        }
        numClear = (numClear + 1)%3;
    break;

    }
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
void ofApp::getNumFilesInDir(string dir){

    ofDirectory dir2scan(dir);
    dir2scan.allowExt("jpg");
    dir2scan.listDir();

    ofxImageSequence *img = new ofxImageSequence();;
    img->loadSequence(dir+"/", "jpg", 0, dir2scan.size()-1);
    img->preloadAllFrames();
    img->setFrameRate(13);
    images.push_back(*img);
    //mediaType.push_back(1);
    //wichMedia++;
    switchMedia(wichMedia);
    numLoaded++;
    string split = ofSplitString(dir, loadPath)[1];
    sendWich2Load(split+"/", dir2scan.size()-1);

}


void ofApp::showSaveDialog(){

    ofFileDialogResult saveFileResult = ofSystemSaveDialog("channel.xml", "save to XML");

        if(saveFileResult.bSuccess){
            saveToXML(saveFileResult.getPath());
            cout<<"saved"<<endl;
        }

}

void ofApp::showDialog(){

    ofFileDialogResult openFileResult= ofSystemLoadDialog("Select Media", true, loadPath);
        if (openFileResult.bSuccess){

            cout<<openFileResult.getPath()<<endl;
            getNumFilesInDir(openFileResult.getPath());
            fileNames.push_back(openFileResult.getName());
            filePath.push_back(openFileResult.getPath());

		}else {
            cout<<"cancel"<<endl;
		}
}

void ofApp::processOpenFileSelection(ofFileDialogResult openFileResult){

    cout<< openFileResult.getName()<<endl;
	cout<< openFileResult.getPath()<<endl;

	ofFile file (openFileResult.getPath());

	if (file.exists()){
		ofLogVerbose("The file exists - now checking the type via file extension");
		string fileExtension = ofToUpper(file.getExtension());
		//checking for image or video
		if (fileExtension == "JPG" || fileExtension == "MP4") {

			//add it to list of files
			fileNames.push_back(openFileResult.getName());

			if(fileExtension == "JPG"){
                /*
                string split = ofSplitString(openFileResult.getPath(), "/home/ekko/wall_box/Dropbox/wall_box/")[1];
                cout<<split<<endl;
                ofImage *img = new ofImage();;
                img->loadImage(openFileResult.getPath());
                images.push_back(*img);
                mediaType.push_back(1);
                switchMedia(wichMedia);
                numLoaded++;

                sendWich2Load(split);
                */
            }else if(fileExtension == "MP4"){
                /*
                string split = ofSplitString(openFileResult.getPath(), "/home/ekko/wall_box/Dropbox/wall_box/")[1];
                cout<<split<<endl;
                ofVideoPlayer *img = new ofVideoPlayer();
                img->loadMovie(openFileResult.getPath());
                images.push_back(*img);
                mediaType.push_back(2);
                switchMedia(wichMedia);
                numLoaded++;
                */
            }
        }
    }
}

void ofApp::switchMedia(int wich){
    if(images.size() > 0){
    vHeight = images[wich].getHeight();
    vWidth = images[wich].getWidth();


    for(int i = 0; i<maxSel; i++){

        m_selections[i].x = (int)ofMap(selections[i].x, sliceZone.x, sliceZone.width, 0, vWidth);
        m_selections[i].y = (int)ofMap(selections[i].y, sliceZone.y, sliceZone.height, 0, vHeight);
        m_selections[i].width  = (int)ofMap(selections[i].width, sliceZone.x, sliceZone.width, 0, vWidth);
        m_selections[i].height = (int)ofMap(selections[i].height, sliceZone.y, sliceZone.height, 0, vHeight);
        }
        remapSel(vWidth, vHeight);
    }
}

void ofApp::remapSel(int vidW, int vidH){

    for(int i = 0; i<maxSel; i++){

        cout<<"mapping for selection: " + ofToString(i) <<endl;
        m_selections[i].x = ofMap(selections[i].x, sliceZone.x, sliceZone.width, 0, vidW);
        m_selections[i].y = ofMap(selections[i].y, sliceZone.y, sliceZone.height, 0, vidH);
        m_selections[i].width  = ofMap(selections[i].width, sliceZone.x, sliceZone.width, 0, vidW);
        m_selections[i].height = ofMap(selections[i].height, sliceZone.y, sliceZone.height, 0, vidH);
        cout<<"mapping textcoords"<<endl;
        videoProjections[i].mapTexCoords(m_selections[i].x, m_selections[i].y, m_selections[i].x + m_selections[i].width , m_selections[i].y + m_selections[i].height);
        }
}

void ofApp::sendWich2Load(string file, int numFiles){

    cout<<"sending load Message"<<endl;
    ofxOscMessage loadMess;
    loadMess.setAddress("/LOAD");
    loadMess.addStringArg(file);
    loadMess.addIntArg(numFiles);

    for(int i=0; i<4;i++){

        ctlz[i].sendMessage(loadMess);
    }
}

void ofApp::sendClear(){

    ofxOscMessage clearMess;
    clearMess.setAddress("/CLEAR");
    for(int i = 0; i<4;i++){


        ctlz[i].sendMessage(clearMess);
    }
}

void ofApp::saveToXML(string file2save){

    wall_files.load(file2save);

    wall_files.clear();
    wall_files.addTag("media");
    wall_files.pushTag("media");
    for(int i = 0; i<filePath.size(); i++){

        wall_files.addTag("file");
        wall_files.pushTag("file", i);
        wall_files.setValue("name", filePath[i]);
        wall_files.popTag();

    }
    wall_files.popTag();
    wall_files.saveFile(file2save);

}
