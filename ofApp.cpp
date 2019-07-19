#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetColor(39);
	ofSetLineWidth(2);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateY(ofGetFrameNum() * 0.5);

	vector<glm::vec3> locations;

	int len = 500;
	for (auto i = 0; i < 500; i++) {

		auto z = ofRandom(-len * 0.5, len * 0.5);
		auto param = ofRandom(100) + ofGetFrameNum() * ofRandom(0.2, 0.5);

		auto point = this->make_point(len, param);
		auto location = ofRandom(1) < 0.5 ? glm::vec3(point.x, point.y, z) : glm::vec3(z, point.x, point.y);

		locations.push_back(location);
	}


	for (auto& location : locations) {

		ofDrawSphere(location, 5);
		for (auto& other : locations) {

			if (location == other) { continue; }
			float distance = glm::distance(location, other);
			if (distance < 50) {

				ofDrawLine(location, other);
			}
		}
	}

	this->cam.end();
}

//--------------------------------------------------------------
glm::vec2 ofApp::make_point(int len, int param) {

	param = param % 100;
	if (param < 25) {

		return glm::vec2(ofMap(param, 0, 25, -len * 0.5, len * 0.5), -len * 0.5);
	}
	else if (param < 50) {

		return glm::vec2(len * 0.5, ofMap(param, 25, 50, -len * 0.5, len * 0.5));
	}
	else if (param < 75) {

		return glm::vec2(ofMap(param, 50, 75, len * 0.5, -len * 0.5), len * 0.5);
	}
	else {

		return glm::vec2(-len * 0.5, ofMap(param, 75, 100, len * 0.5, -len * 0.5));
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}