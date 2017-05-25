#include "ofxKuPreset.h"
#include "ofxKuFile.h"

#include <map>

//--------------------------------------------------------------
ofxKuPreset::ofxKuPreset() {
	trans_ = false;
	trans_time_ = 0.5;
	trans_value_ = 0;
}

//--------------------------------------------------------------
void ofxKuPreset::add_int(string name, int *var) {
	var_.push_back(Var(name, var));
	name_to_map(name, var_.size()-1);
}

//--------------------------------------------------------------
void ofxKuPreset::add_float(string name, float *var) {
	var_.push_back(Var(name, var));
	name_to_map(name, var_.size()-1);
}

//--------------------------------------------------------------
void ofxKuPreset::name_to_map(string name, int i) {
	var_map_[name] = i;
}

//--------------------------------------------------------------
void ofxKuPreset::load(string file_name) {
	vector<string> file = ofxKuFileReadStrings(file_name);
	int n = file.size()/2;
	preset_.resize(n);
	for (int i=0; i<n; i++) {
		preset_[i] = file[i*2+1];
	}
	file_name_ = file_name;
}

//--------------------------------------------------------------
void ofxKuPreset::save(string file_name) {
	int n = preset_.size();
	vector<string> file(n*2);
	for (int i=0; i<n; i++) {
		file[2*i] = "========   " + ofToString(i,4,'0') + "   =============================";
		file[2*i+1] = preset_[i];
	}
	ofxKuFileWriteStrings(file, file_name);
	file_name_ = file_name;
}

//--------------------------------------------------------------
void ofxKuPreset::load() {
	if (file_name_ != "") {
		load(file_name_);
	}
}

//--------------------------------------------------------------
void ofxKuPreset::save() {
	if (file_name_ != "") {
		save(file_name_);
	}
}

//--------------------------------------------------------------
void ofxKuPreset::store(int id) {
	if (id < 0) return;
	if (id >= preset_.size()) {
		preset_.resize(id+1);
	}
	string pr;
	for (int i=0; i<var_.size(); i++) {
		if (i>0) pr += " ";
		pr += var_[i].name + " " + ofToString(var_[i].value());
	}
	preset_[id] = pr;
}

//--------------------------------------------------------------
ofxKuPreset::Var *ofxKuPreset::findVar(const string &name) {
	map<string, int>::iterator p = var_map_.find( name );
	if (p != var_map_.end()) {
		return &var_[p->second];
	}
	return 0;
}

//--------------------------------------------------------------
void ofxKuPreset::recall(int id) {		//one-step transition to preset
	if (id >= 0 && id < preset_.size()) {
		vector<string> item = ofSplitString(preset_[id], " ");
		int n = item.size();
		if (n % 2 == 0) {
			for (int i=0; i<n; i+=2) {
				Var *var = findVar(item[i]);
				if (var) {
					var->set_value(ofToDouble(item[i+1]));
				}
			}
		}
		trans_ = false;
	}
}

//--------------------------------------------------------------
void ofxKuPreset::trans_to(int id, float trans_time) { //slow transition between presets
	if (id >= 0 && id < preset_.size()) {
		//default value
		for (int i=0; i<var_.size(); i++) {
			var_[i].trans_start(var_[i].value());
		}

		//preset value
		vector<string> item = ofSplitString(preset_[id], " ");
		int n = item.size();
		if (n % 2 == 0) {
			for (int i=0; i<n; i+=2) {
				Var *var = findVar(item[i]);
				if (var) {
					var->trans_start(ofToDouble(item[i+1]));						
				}
			}
			//enable transition mode
			trans_ = true;
			trans_start_ = ofGetElapsedTimef();
			trans_time_ = trans_time;
		}
	}
}

//--------------------------------------------------------------
void ofxKuPreset::update_manual(float t) {	//instead update, call this for manual morphing between presets, t==0 - start, t==1 - end
	t = t*t*(3-2*t);		//non-linear transform, such that F(0)=F'(0)=F'(1)=0, F(1)=1.
	for (int i=0; i<var_.size(); i++) {
		var_[i].trans(t);
	}
}

//--------------------------------------------------------------
void ofxKuPreset::update() {
	if (trans_) {
		float time = ofGetElapsedTimef();
		float delta = time - trans_start_;
		trans_value_ = (trans_time_>0)?delta/trans_time_:1;
		if (trans_value_ >= 1) trans_ = false;
		trans_value_ = ofClamp(trans_value_,0,1);

		update_manual(trans_value_);
	}
}


//--------------------------------------------------------------
bool ofxKuPreset::trans_is_going() {	//now is transition
	return trans_;
}

//--------------------------------------------------------------
float ofxKuPreset::trans_value() {	//0 - start, ... 1 - end
	if (trans_) return trans_value_;
	return 0;
}

//--------------------------------------------------------------
