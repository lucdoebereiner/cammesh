#include "ofMain.h"
#include <iostream>
// #include "ofApp.h"

// #include "ofMain.h"
class ofApp : public ofBaseApp
{
public:
	void setup()
	{
		std::cout << "starting up" << endl;
		ofBackground(0);
		ofSetFrameRate(30);

		// Initialize the webcam
		webcam.setDeviceID(0);
		webcam.setup(640, 480);
		// webcam.videoSettings();

		// Initialize the mesh
		mesh.setMode(OF_PRIMITIVE_TRIANGLES);
		mesh.enableColors();

		// Create the vertices
		int w = webcam.getWidth();
		int h = webcam.getHeight();
		for (int y = 0; y < h; y++)
		{
			for (int x = 0; x < w; x++)
			{
				mesh.addVertex(ofVec3f(x - w / 2, y - h / 2, 0));
				mesh.addColor(ofColor(255, 255, 255));
			}
		}

		// Create the indices
		for (int y = 0; y < h - 1; y++)
		{
			for (int x = 0; x < w - 1; x++)
			{
				int i1 = x + y * w;
				int i2 = (x + 1) + y * w;
				int i3 = x + (y + 1) * w;
				int i4 = (x + 1) + (y + 1) * w;
				mesh.addIndex(i1);
				mesh.addIndex(i2);
				mesh.addIndex(i3);
				mesh.addIndex(i2);
				mesh.addIndex(i4);
				mesh.addIndex(i3);
			}
		}
	}

	void update()
	{
		webcam.update();
		if (webcam.isFrameNew())
		{
			// Update the mesh vertices based on the webcam pixels
			int w = webcam.getWidth();
			int h = webcam.getHeight();
			for (int y = 0; y < h; y++)
			{
				for (int x = 0; x < w; x++)
				{
					int i = x + y * w;
					ofVec3f pos = mesh.getVertex(i);
					pos.z = ofMap(webcam.getPixels().getColor(x, y).getBrightness(), 0, 255, -100, 100);
					mesh.setVertex(i, pos);
					mesh.setColor(i, webcam.getPixels().getColor(x, y));
				}
			}
		}
	}

	void draw()
	{
		ofEnableDepthTest();
		// ofPushMatrix();
		// ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2, 0);
		// ofRotateX(180);
		// mesh.draw();
		webcam.draw(0, 0);
		// ofPopMatrix();
		ofDisableDepthTest();
	}

private:
	ofVideoGrabber webcam;
	ofMesh mesh;
};

int main()
{
	std::cout << "starting" << std::endl;
	ofSetupOpenGL(640, 480, OF_WINDOW);
	ofRunApp(new ofApp());
}
/*
//========================================================================
int main( ){

	//Use ofGLFWWindowSettings for more options like multi-monitor fullscreen
	ofGLWindowSettings settings;
	settings.setSize(1024, 768);
	settings.windowMode = OF_WINDOW; //can also be OF_FULLSCREEN

	auto window = ofCreateWindow(settings);

	ofRunApp(window, make_shared<ofApp>());
	ofRunMainLoop();

}
*/