Filesys
=======
A lightweight, cross platform solution to accessing filesystems.
Johnathan Corkery (jcorkery@umich.edu)





Introduction
============

Filesys provides a very simple and lightweight way to give projects
access to the target operating system's filesystem. Namely this provides
a lighter alternative option to more bulky installations, such as 
Boost::filesystem

Installation
============

Simply add the contents in /filesysSrc/ to your project. If the operating system
that you are compiling the project for is a Unix variant, include all the
source except the filesys_win.cpp. Likewise, if the target OS is
a version of Windows, include all files except for filesys_unix.cpp.

Usage
=====

Using Filesys was designed to be very intuitive. To get started, instantiate an 
Filesys object:

	Filesys fs;

This will initialize Filesys to your current writing directory. 
You may specify a different directory:

	Filesys fs("/mynewDir/");

Once Filesys is initialized, you may query the contents of the directory. 
Querying a directory returns a Filesys::Directory object which ontains all the
directory

	Filesys::Directory thisDir = fs.queryDirectory();

To retrieve the next directory object, you may either use the extraction 
operator (>>) or use the method getNextName().

Here is a full example that will display the contents of the directory of
the binary running the code:


	Filesys fs;
	Filesys::Directory dir = fs.queryDirectory();

	while(!dir.atEnd()) {
		std::cout << dir.getNextName() << std::endl;
	}






Filesys::Directory is not just for retrieving object names; you may also query if the 
object is a file or directory, search of an object name with the directory, and more.


	
	



	
	

*Refer to filesys.h for more details on usage*



