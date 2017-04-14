#include "ofxKuFileTime.h"

//--------------------------------------------------------------
bool ofxKuFileTime::isNewerThan(string fileName1, string fileName2) {
	if (ofFile::doesFileExist(fileName1) && ofFile::doesFileExist(fileName2)) {
		ofFile file1(fileName1, ofFile::ReadOnly, true);
		ofFile file2(fileName2, ofFile::ReadOnly, true);

		Poco::Timestamp created1 = file1.getPocoFile().created();
		Poco::Timestamp created2 = file2.getPocoFile().created();
		return (created1 > created2);
	}
	return true;
}

//--------------------------------------------------------------
/*bool Filetime_is_file_older_hours(string fileName, int hours) {
	ofFile file(fileName, ofFile::ReadOnly, true);
	Poco::Timestamp created = file.getPocoFile().created();
	Poco::Timestamp now = Poco::Timestamp::Timestamp();

	std::time_t created_sec = created.epochTime();
	std::time_t now_sec = now.epochTime();

	//cout << "created " << created_sec << " now " << now_sec << endl;
	//cout << "time_diff " << (now_sec - created_sec)/(60*60) << endl;
	//if (now_sec > created_sec + 60*60*hours) cout << "OLD" << endl;

	return (now_sec > created_sec + 60*60*hours);
	//return (created.isElapsed(hours*60*60*1000000));
}
*/
//--------------------------------------------------------------
