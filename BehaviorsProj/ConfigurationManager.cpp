/*
 * ConfigurationManager.cpp
 *
 *  Created on: Jun 12, 2015
 *      Author: colman
 */

#include "ConfigurationManager.h"

using namespace std;

map<string, string> ConfigurationManager::_configs;

std::string trim(std::string const& source, char const* delims = " \t\r\n") {
  std::string result(source);
  std::string::size_type index = result.find_last_not_of(delims);
  if(index != std::string::npos)
    result.erase(++index);

  index = result.find_first_not_of(delims);
  if(index != std::string::npos)
    result.erase(0, index);
  else
    result.erase();
  return result;
}

ConfigurationManager::ConfigurationManager() {
	ifstream file("/home/colman/Desktop/parameters.txt");

	  string line;
	  string name;
	  string value;
	  int posEqual;
	  while (std::getline(file,line)) {

	    if (! line.length()) continue;

	    posEqual=line.find(':');
	    name  = trim(line.substr(0,posEqual));
	    value = trim(line.substr(posEqual+1));
	    _configs.insert(make_pair(name, value));
	    cout << name << " : " << value << endl;
	  }
}
string ConfigurationManager::getMapLocation() {
	return (_configs.find("map")->second);
}

void ConfigurationManager::getStartLocation(int& x, int& y, int& yaw) {
	vector<string> v = split(_configs.find("startLocation")->second, ' ');
	x = atoi(((string)(v[0])).c_str());
	y = atoi(((string)(v[1])).c_str());
	yaw = atoi(((string)(v[2])).c_str());
}

void ConfigurationManager::getGoal(int &x, int &y) {
	vector<string> v = split(_configs.find("goal")->second, ' ');
	x = atoi(((string)(v[0])).c_str());
	y = atoi(((string)(v[1])).c_str());
}

void ConfigurationManager::getRobotSize(int& x, int& y) {
	vector<string> v = split(_configs.find("robotSize")->second, ' ');
	x = atoi(((string)(v[0])).c_str());
	y = atoi(((string)(v[1])).c_str());
}

int ConfigurationManager::getMapResolution() {
	return(atoi(((string)(_configs.find("MapResolutionCM")->second)).c_str()));
}

int ConfigurationManager::getGridResolution() {
	return(atoi(((string)(_configs.find("GridResolutionCM")->second)).c_str()));
}

vector<string> ConfigurationManager::split(string str, const char delim) {
    vector<string> v;
    string tmp;
    string::const_iterator i;

    for(i = str.begin(); i <= str.end(); ++i) {
        if(*i != delim && i != str.end()) {
            tmp += *i;
        } else {
            v.push_back(tmp);
            tmp = "";
        }
    }

    return v;
}

ConfigurationManager::~ConfigurationManager() {
	// TODO Auto-generated destructor stub
}
