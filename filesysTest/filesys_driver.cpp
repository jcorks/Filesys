#include "../filesysSrc/filesys.h"
#include <iostream>
#include <cassert>

using namespace std;

int main() {
	Filesys f;
	
	cout << "CWD:" << f.getCWD() << endl;
	Filesys::Directory d = f.queryDirectory();
	cout << "Number of items? " << d.size() << endl;
	cout << "OS: ";
	__OS os = f.getType();
	if (os == WINDOWS) {
		cout << "WINDOWS" << endl;
	} else if (os == UNIX_VARIANT) {
		cout << "UNIX VARIANT" << endl;
	} else {
		cout << "????" << endl;
	}

	if (!d.size()) return 1;
	string name;
	while(!d.atEnd()) {
		d >> name;
		cout << name << "\t" << (d.isFile(name) ? " " : "<DIR>") << endl;
	}

	cout << "changing to parent directory..." << endl;
	assert(f.goToParent());
	cout << f.getCWD() << endl;
	d = f.queryDirectory();
	while(!d.atEnd()) {
		d >> name;
		cout << name << "\t" << (d.isFile(name) ? " " : "<DIR>") << endl;
	}

	cout << "Searching for first directory..." << endl;
	d = f.queryDirectory();
	while(!d.atEnd()) {
		d >> name;
		if (!d.isFile(name) && name != "." && name != "..") {
			cout << " Found directory: " << name << ", switching to it." << endl;
			assert(f.goToChild(name));
			break;
		}
	}

	cout << f.getCWD() << endl;
	d = f.queryDirectory();
	while(!d.atEnd()) {
		d >> name;
		cout << name << "\t" << (d.isFile(name) ? " " : "<DIR>") << endl;
	}

	
	



	return 0;
}
