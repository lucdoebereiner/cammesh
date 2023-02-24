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
		// mesh.setMode(OF_PRIMITIVE_LINES);
		mesh.setMode(OF_PRIMITIVE_TRIANGLES);
		mesh.enableColors();
		mesh.enableIndices();

		// Create the vertices
		width = 40;	 // webcam.getWidth();
		height = 40; // webcam.getHeight();
		dist = 20;
		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				mesh.addVertex(ofVec3f(x * dist, y * dist, 0));
				mesh.addColor(ofColor(255, 255, 255));
			}
		}

		// Create the indices
		for (int y = 0; y < height - 1; y++)
		{
			for (int x = 0; x < width - 1; x++)
			{
				int i1 = x + y * width;
				int i2 = (x + 1) + y * width;
				int i3 = x + (y + 1) * width;
				int i4 = (x + 1) + (y + 1) * width;
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
			ofPixels pixs = webcam.getPixels();
			pixs.resize(width, height, OF_INTERPOLATE_BICUBIC);

			for (int y = 0; y < height; y++)
			{
				for (int x = 0; x < width; x++)
				{
					int i = x + y * width;
					ofVec3f pos = mesh.getVertex(i);
					int bright = pixs.getColor(x, y).getBrightness();
					pos.z = ofMap(bright, 0, 255, -100, 100);
					mesh.setVertex(i, pos);
					mesh.setColor(i, pixs.getColor(x, y));
					// mesh.setColor(i, ofColor(bright, bright, bright));
				}
			}

			// pixs.resize(240, 240);
			// image.setFromPixels(pixs);
			//  webcam.update();
			//   webcam.getPixels().resize(640, 480);
			//   webcam.update();
			//    Update the mesh vertices based on the webcam pixels
			/*int w = webcam.getWidth();
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
			*/
		}
	}

	void draw()
	{
		ofEnableDepthTest();
		// ofPushMatrix();
		// ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2, 0);
		// ofRotateX(180);
		// webcam.draw(0, 0);

		// ofPushMatrix();
		// ofTranslate(640, 0, 0);
		easyCam.begin();
		ofPushMatrix();
		ofTranslate(-ofGetWidth() / 2, -ofGetHeight() / 2);
		mesh.draw();
		ofPopMatrix();
		easyCam.end();

		// mesh.draw();
		// ofPopMatrix();

		// image.draw(640, 0);
		//  ofPopMatrix();
		ofDisableDepthTest();
	}

private:
	ofVideoGrabber webcam;
	ofMesh mesh;
	ofImage image;
	ofEasyCam easyCam;
	int width;
	int height;
	int dist;
};

int main()
{
	std::cout << "starting" << std::endl;
	ofSetupOpenGL(1000, 480, OF_WINDOW);
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