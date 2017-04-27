#include "ofxKuFile.h"

//--------------------------------------------------------------------------------
bool ofxKuFileExists( string fileName )
{
	fileName = ofToDataPath(fileName);
	ifstream inp;
	inp.open(fileName.c_str(), ifstream::in);
	inp.close();
	return !inp.fail();
}

//--------------------------------------------------------------------------------
int ofxKuFileSize( string fileName )
{
	fileName = ofToDataPath(fileName);
	FILE *file = fopen( fileName.c_str(), "rb" );
	fseek( file, 0, SEEK_END );
	int size = ftell( file );	//TODO use size_t for big files
	fclose( file );
	return size;
}

//--------------------------------------------------------------------------------
vector<string> ofxKuFileReadStrings( string fileName )
{
	fileName = ofToDataPath(fileName);
	vector<string> list;
	if ( ofxKuFileExists( fileName ) ) {
		ifstream f(fileName.c_str(),ios::in);
		string line;
		while (getline(f,line)) {
			list.push_back( line );
		}
	}                              
	return list;                   
}

//--------------------------------------------------------------------------------
bool ofxKuFileWriteStrings( const vector<string> &list, string fileName )
{
	fileName = ofToDataPath(fileName);
	ofstream f(fileName.c_str(),ios::out);
	for ( int i=0; i<list.size(); i++ ) {
		f << list[i] << endl;
	}
	return true;
}

//--------------------------------------------------------------------------------
/*vector<string> pbFiles::readStringsFilterAndNotEmpty( const string &fileName )
{
	vector<string> list = readStrings( fileName );
	vector<string> res;
	for (int i=0; i<list.size(); i++) {
		string s = Converter::filterString( list[i] );
		if ( s != "" ) {
			res.push_back( s ); 
		}	
	}
	return res;
}



//--------------------------------------------------------------------------------
vector<float> pbFiles::readFloats( const string &fileName )
{
	vector<string> sv = readStrings( fileName );
	return Converter::vectorStringToFloat( sv );
}

//--------------------------------------------------------------------------------
bool pbFiles::writeFloats( const vector<float> &list, const string &fileName )
{
	vector<string> sv = Converter::vectorFloatToString( list );
	return writeStrings( sv, fileName );
}

//--------------------------------------------------------------------------------
vector<int> pbFiles::readInts( const string &fileName )
{
	vector<string> sv = readStrings( fileName );
	return Converter::vectorStringToInt( sv );
}

//--------------------------------------------------------------------------------
bool pbFiles::writeInts( const vector<int> &list, const string &fileName )
{
	vector<string> sv = Converter::vectorIntToString( list );
	return writeStrings( sv, fileName );
}

//--------------------------------------------------------------------------------
string pbFiles::readOneString( const string &fileName )
{
	string res = "";
	if ( fileExists( fileName ) ) {
		vector<string> list;
		list = readStrings( fileName );
		if ( list.size() >= 1 ) {
			res = list[0];
		}
	}
	return res;
}

//--------------------------------------------------------------------------------
void pbFiles::writeOneString( const string &fileName, const string &s )
{
	vector<string> list;
	list.push_back( s );
	writeStrings( list, fileName );
}

//--------------------------------------------------------------------------------
string pbFiles::getExtension( const string &fileName, bool lowerCase )
{
	string result = "";
	std::string::size_type idx;
	idx = fileName.rfind('.');
    if(idx != std::string::npos){
        result = fileName.substr(idx+1);
    }
	if ( lowerCase ) {
		 transform( result.begin(), result.end(), result.begin(), ::tolower );
	}
	return result;
}

//--------------------------------------------------------------------------------
vector<pbFiles::PairFloat> pbFiles::readPairs( const string &fileName )
{
	vector<PairFloat>  res;
	vector<string> sv = readStrings( fileName );
	for (int i=0; i<sv.size(); i++) {
		vector<string> line = Parsing::split( Converter::filterString( sv[i] ), "=" );
		if ( line.size() >= 2 ) {
			res.push_back( pbFiles::PairFloat( line[0], Converter::strToDouble( line[1] ) ) );
		}		
	}
	return res;
}

//--------------------------------------------------------------------------------
void pbFiles::writePairs( const vector<pbFiles::PairFloat> &list, const string &fileName )
{
	vector<string> sv;
	for (int i=0; i<list.size(); i++) {
		string s = list[i].name + "=" + Converter::doubleToStr( list[i].value );
		sv.push_back( s );
	}
	writeStrings( sv, fileName );

}

//--------------------------------------------------------------------------------
float pbFiles::findValue( const vector<PairFloat> &list, string name, float defValue )
{
	for (int i=0; i<list.size(); i++) {
		if ( list[i].name == name ) return list[i].value;
	}
	return defValue;
}
*/
//--------------------------------------------------------------------------------
