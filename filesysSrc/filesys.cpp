#include "filesys.h"

using namespace std;

Filesys::Filesys() {
	_init();
	changeDir(getCWD());
}

Filesys::Filesys(const std::string & initDir) {
	_init();
	changeDir(initDir);
}

void Filesys::_init() {
	home = getCWD();
	type = __FSYS__;
}
Filesys::Object::Object() {
	file = false;
	size = 0;
	name = "";
}

__OS Filesys::getType() {
	return type;
}


Filesys::Directory::Directory(const std::vector<Object> & src) {
	vec.assign(src.begin(), src.end());
	numFiles = src.size();
	pos = 0;

}

std::string Filesys::Directory::getNextName() {
	if (!atEnd())
		return vec[pos++].name;
	else
		return "";
}

bool Filesys::Directory::operator()() {
	return atEnd();
}

bool Filesys::Directory::atEnd() {
	return(pos >= numFiles);
}
void Filesys::Directory::resetPosition() {
	pos = 0;
}

Filesys::Directory & Filesys::Directory::operator>>(std::string & str) {
	str = getNextName();
	return (*this);
}

int Filesys::Directory::size() {
	return numFiles;
}

bool Filesys::Directory::query(const std::string & target) {
	for(int i = 0; i < numFiles; ++i) {
		if (vec[i].name == target)
			return true;
	}
	return false;
}

bool Filesys::Directory::isFile(const std::string & obj) {
	for(int i = 0; i < numFiles; ++i) {
		if (vec[i].name == obj)
			return vec[i].file;
	}
	return false;
}


string Filesys::findFile(const string & name) {
    string originalDir = getCWD();
    string out = FFH(name, ".");
    changeDir(originalDir); // return to n
    return out;
}

string Filesys::FFH(const string & target, const string & entryPoint) {
    string path = "";

    bool canChange = changeDir(entryPoint);
	if (!canChange) return path;


    Filesys::Directory d = queryDirectory();
    string current;
    for(int i = 0; i < d.size(); ++i) {
        current = d.getNextName();

        // get the file is the one we are looking for
        if (d.isFile(current) && current == target) {
            path = getCWD() + "/" + current;
            return path;
        }

        // search recursively on subdirectories
        if (!d.isFile(current) && current != "." &&
                                  current != "..") {


            string oldPath = getCWD();
            string res = FFH(target, getCWD() + "/" + current);
            if (res != "") return res;
            changeDir(oldPath);

        }

    }

    return ""; // the case where it was not found
}

vector<string> Filesys::findAllFiles(const string & name) {
    string originalDir = getCWD();
    vector<string> out = FAFH(name, ".", vector<string>());
    changeDir(originalDir); // return to n
    return out;
}

#include <iostream>
vector<string> Filesys::FAFH(const string & target,
			     const string & entryPoint,
			     vector<string> paths) {
    string path = "";

    std::cout << endl << entryPoint;
    bool canChange = changeDir(entryPoint);
	if (!canChange) return paths;


    Filesys::Directory d = queryDirectory();
    string current;
    for(int i = 0; i < d.size(); ++i) {
        current = d.getNextName();

        // get the file is the one we are looking for
        if (d.isFile(current) && current == target) {
            path = getCWD() + "/" + current;
            paths.push_back(path);
        }

        // search recursively on subdirectories
        if (!d.isFile(current) && current != "." &&
                                  current != "..") {
            string oldPath = getCWD();
            paths =              FAFH(target,
                                      getCWD() + "/" + current,
                                      paths);
            changeDir(oldPath);

        }

    }

    return paths; // the case where it was not found
}

