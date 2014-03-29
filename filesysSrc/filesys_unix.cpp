#include "filesys.h"

#include <iostream>




bool Filesys::changeDir(const std::string & dir) {
    
	if (chdir(dir.c_str()) == -1)
		return false;
	currentPath = dir;

	// clear out old directory objects

	int numFiles;
	currentPathObjs.clear();


	// gather new path objects
	dirent **ls;

	numFiles = scandir(currentPath.c_str(),
						   &ls, NULL,
						   alphasort);

	// dump file names in base vector;
	for(int i = 0; i < numFiles; ++i) {
		Object newObj;
		if (ls[i]->d_type == DT_DIR)  // directory detected
			newObj.file = false;
		else
			newObj.file = true	;

		newObj.name = ls[i]->d_name;
		//newObj->size = ls[i]->d_reclen;
		currentPathObjs.push_back(newObj);
	}
    
	return true;

}

Filesys::Directory Filesys::queryDirectory() {
	Directory out(currentPathObjs);
	return out;
}

std::string Filesys::getCWD() {
	char dir[DIRECTORY_SIZE_LIMIT];
	currentPath = getcwd(dir, sizeof(dir));

	return currentPath;
}

bool Filesys::goToParent() {
	
	std::string d = getCWD();
	int index = d.length() - 1;
	while (d[index] != '/') index--;
	d = d.substr(0, index);
	return changeDir(d);
}

bool Filesys::goToChild(const std::string & target) {
	return changeDir(getCWD() + "/" + target);
}

bool Filesys::createDir(const std::string & dir) {
	std::string newDir = getCWD() + "/" + dir;
	return mkdir(newDir.c_str(), 0777);
}
