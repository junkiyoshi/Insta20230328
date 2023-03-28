#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(0);
	ofSetLineWidth(1.5);
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);

	this->radius = 20;
	auto x_span = radius * sqrt(3);
	auto flg = true;
	for (float y = -650; y < 650; y += radius * 1.5) {

		for (float x = -650; x < 650; x += x_span) {

			glm::vec2 location;
			if (flg) {

				location = glm::vec2(x, y);
			}
			else {

				location = glm::vec2(x + (x_span / 2), y);
			}

			this->location_list.push_back(location);
		}
		flg = !flg;
	}
}
//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);
	ofRotateZ(ofGetFrameNum() * 0.6666666666666666);

	ofColor color;
	for (int i = 0; i < 8; i++) {

		color.setHsb(ofMap(i, 0, 8, 0, 255), 255, 255);
		auto noise_seed = ofRandom(1000);
		for (auto& location : this->location_list) {

			auto noise_y = ofMap(ofNoise(noise_seed, location.x * 0.0005 + ofGetFrameNum() * 0.0025), 0, 1, -400, 400);
			auto distance = abs(location.y - noise_y);

			if (distance < this->radius * 3) {

				vector<glm::vec2> vertices;
				for (int deg = 90; deg < 450; deg += 60) {

					vertices.push_back(location + glm::vec2(this->radius * cos(deg * DEG_TO_RAD), this->radius * sin(deg * DEG_TO_RAD)));
				}

				ofNoFill();
				ofSetColor(color, ofMap(distance, 0, this->radius * 3, 255, 0));

				ofBeginShape();
				ofVertices(vertices);
				ofEndShape(true);

				ofFill();
				ofSetColor(color, ofMap(distance, 0, this->radius * 3, 128, 0));

				ofBeginShape();
				ofVertices(vertices);
				ofEndShape(true);

			}
		}
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}