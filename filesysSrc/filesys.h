/*  Filesys:
 *  A lightweight, cross platform solution to accessing filesystems.
 *
 *  Johnathan Corkery, 2014
 *
 */

#ifndef FILESYS_H_INCLUDED
#define FILESYS_H_INCLUDED


const int DIRECTORY_SIZE_LIMIT 		= 256;


#include <string>
#include <vector>




enum __OS {
	UNIX_VARIANT,
	WINDOWS,
	UNKNOWN
};

class Filesys {

/* Private members. */
 	struct Object {
		bool file;
		int size;
		std::string name;
		Object();
	};

	__OS type;


	std::string currentPath;
	std::vector<Object> currentPathObjs;
	std::string home;
	void _init();
	std::string FFH(const std::string &, const std::string &);
	std::vector<std::string> FAFH(const std::string &, 
				      const std::string &,
				      std::vector<std::string>);










  public:


	// The container for managing directory objects.
	class Directory {
		std::vector<Object> vec;
		int numFiles;
		int pos;


	  public:
	  	std::string getNextName();
	  	void resetPosition();
	  	int size();

	  	// pulls the next directory name from the gathered list
	  	Directory & operator >> (std::string & str);

	  	// returns if all files have been exhausted
	  	bool atEnd();
	  	bool operator()();


  		// returns whether or not target exists
  		bool query(const std::string & target);

	  	// return whther or nor obj is a file.
	  	// PROTIP: if the Filesys::Object is not a file,
	  	// it is most likely a directory!
	  	bool isFile(const std::string & obj);

	 	Directory(const std::vector<Object> & src);
	};

  	Filesys();
  	Filesys(const std::string & initDir);

  	// change to the specified directory.
  	// Returns true on success.
  	bool changeDir(const std::string &);

	// change to the specified child directory
	// NOTICE: you only need to specify the name of the directory
	// Ex) if you query the directory and it returns true, then
	// this function will succeed as well.
	bool goToChild(const std::string &);


	// change to the parent directory.
	bool goToParent();

  	// return the current working directory.
  	std::string getCWD();

	// creates a directory with the given name
	// relative to the current working directory
	bool createDir(const std::string &);


  	// return all the object names in the current working directory
  	// as a directory instance.
  	Directory queryDirectory();
	
	// Searthes for the file of the specified name in the
	// current directory and all subdirectories.
	// If successful, return the full path of the
	// file, else returns an empty string.
	std::string findFile(const std::string & name);

	// Similar to findFile, but returns a vector of paths
	// coresponding to all instances of name that exist in
	// the current and sub-directories
	std::vector<std::string> findAllFiles(const std::string & name);

	

  	__OS getType();



};


#include "filesys_preprocessor.h"

#endif

