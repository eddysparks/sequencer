#pragma once

#include "ofMain.h"
#include "ofxTimeline.h"
#include "ofxOsc.h"
#include "ofxImageSequence.h"
#include "ofxXmlSettings.h"
#include "ofxUI.h"

#define HOST1 "192.168.1.15"
#define HOST2 "192.168.1.11"
#define HOST3 "192.168.1.24"
#define HOST4 "192.168.1.17"
//#define HOST5 "192.168.1.10"
#define CTLPORT 9999
#define SEQPORT 9393
class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

        //timeline stuff
		ofxTimeline timeline;
		void bangFired(ofxTLBangEventArgs& args);
        void stopSequence();
        void startSequence();
        void loadSequence();

        int numClear;

        //oscstuff
        ofxOscSender ctlz[4];
        ofxOscMessage mess1, mess2, mess3, mess4;
        ofxOscReceiver seq_Receive;

        //gui stuff
        int wichUI, clicCount;
        vector<string> fileNames;
        vector<string> filePath;
        string buttonsNames[6];
        int buttonXpad, buttonYpad, radioPadX, radioPadY;
        ofTrueTypeFont guiFont;
        ofRectangle radioButtons[6];
        //ofRectangle clearBut;
        void drawGui();
        void showDialog();
        void showSaveDialog();
        void processOpenFileSelection(ofFileDialogResult openFileResult);


        //media handling stuff
        void getNumFilesInDir(string dir);

        vector<ofxImageSequence> images;
        //vector<int>mediaType;
        int wichMedia, numLoaded;
        void sendWich2Load(string file, int numFiles);
        void sendClear();

        //wall preview
        ofPoint previewScreens[3];

        int vWidth, vHeight;
        void switchMedia(int wich);
        void remapSel(int vidW, int vidH);
        ofPlanePrimitive  videoProjections[4];

        ofRectangle selections[4];
        ofRectangle pre_m_selections[4];
        ofRectangle m_selections[4];
        ofRectangle sliceZone;
        ofRectangle devices[4];
        int wichSel, maxSel;
        bool selecting;
        bool mapMode;
        int vidMap[4];

        //XML
        string loadPath;
        ofxXmlSettings wall_files;
        void saveToXML(string file2save);




};
