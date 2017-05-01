#pragma once

//Presets maintaining system

#include "ofMain.h"


struct ofxKuPreset {
    ofxKuPreset();
    void add_int(string name, int *var);
	void add_float(string name, float *var);

	void load_file(string file_name);
	void save_file(string file_name);
	void save();

	void store(int id);
	void recall(int id);		//one-step transition to preset
	void trans_to(int id, float trans_time); //slow transition between presets
	void update();

	bool trans_is_going();	//now is transition
	float trans_value();	//0 - start, ... 1 - end

	struct Var {
		string name;
		int *vari;
		float *varf;
		double trans0, trans1;	//for transition
		
		Var() {
			vari = 0;
			varf = 0;
			trans0 = 0;
			trans1 = 0;
		}
		Var(string name0, int *vari0) {
			name = name0;
			vari = vari0;
			varf = 0;
			trans0 = *vari;
			trans1 = *vari;
		}
		Var(string name0, float *varf0) {
			name = name0;
			vari = 0;
			varf = varf0;
			trans0 = *varf;
			trans1 = *varf;
		}
		double value() {
			if (varf) return *varf;
			if (vari) return *vari;
			return 0;
		}
		void set_value(double v) {
			if (varf) *varf = v;
			if (vari) *vari = v;
		}
		void trans_start(double to) {
			trans0 = value();
			trans1 = to;
		}
		void trans(float t) {
			if (varf) *varf = ofLerp(trans0, trans1, t);
			if (vari) *vari = (t<0.5)?trans0:trans1;
		}

	};

private:
	vector<Var> var_;
	vector<string> preset_;
	string file_name_;

	Var *findVar(const string &name);
	map<string, int> var_map_;
	void name_to_map(string name, int i);


	bool trans_;
	float trans_time_;

	float trans_start_;
	float trans_value_;
};


