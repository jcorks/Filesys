#include "../filesysSrc/filesys.h"


#include <iostream>

using namespace std;

bool Filesys::changeDir(const std::string & dir) {
    if (!SetCurrentDirectory(dir.c_str())) {
        return false;
    }
    currentPath = dir; 
	// clear out old directory objects

	int numFiles = currentPathObjs.size();
	for(int i = 0; i < numFiles; ++i) {
		delete currentPathObjs[i];
	}
	currentPathObjs.clear();
    
    
    // gather new objects
    
    WIN32_FIND_DATA objData;
    HANDLE dirHandle = INVALID_HANDLE_VALUE;
    TCHAR szDir[DIRECTORY_SIZE_LIMIT];
    std::string sDir = dir + "\\*";
    for(int i = 0; i < sDir.length(); ++i) {
	    szDir[i] = sDir[i];
    }
    szDir[sDir.length()] = '\0';
    LARGE_INTEGER fileSize;
    
    dirHandle = FindFirstFile(szDir, &objData); 
    Object * newObj = new Object();
    newObj->name = objData.cFileName;
    newObj->file = !(objData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY);
    fileSize.LowPart = objData.nFileSizeLow;
    fileSize.HighPart = objData.nFileSizeHigh;
    newObj->size = fileSize.QuadPart;
    currentPathObjs.push_back(newObj);
    
    while(FindNextFile(dirHandle, &objData)) {
        newObj = new Object();
        newObj->name = objData.cFileName;
        newObj->file = !(objData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY);
        fileSize.LowPart = objData.nFileSizeLow;
        fileSize.HighPart = objData.nFileSizeHigh;
        newObj->size = fileSize.QuadPart;
        currentPathObjs.push_back(newObj);
    }
   
	
	return true;
}

Filesys::Directory Filesys::queryDirectory() {
	Directory out(currentPathObjs);
	return out;
}

std::string Filesys::getCWD() {
	char str[DIRECTORY_SIZE_LIMIT];
	GetCurrentDirectory(DIRECTORY_SIZE_LIMIT, str);
	currentPath = str;
	return currentPath;
}

bool Filesys::goToParent() {
	std::string d = getCWD();
	int index = d.length() - 1;
	while(d[index] != '\\') index--;
	d = d.substr(0, index);
	return changeDir(d);
}

bool Filesys::goToChild(const std::string & target) {
	return changeDir(getCWD() + "\\" + target);
}

bool Filesys::createDir(const std::string & dir) {
	std::string newDir = getCWD() + "\\" + dir;
	return CreateDirectory(newDir.c_str(), NULL);
}
