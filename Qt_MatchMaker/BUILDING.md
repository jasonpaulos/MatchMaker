# Building MatchMaker

The MatchMaker application uses the Qt library to provide a user interface that is consistant between different operating systems. Because of this, it is possible to compile the application for a variety of different systems and archetectuers. The steps for doing so are outlined below. It is assumed that you have already downloaded or cloned a copy of the GitHub repository.

1. __Installing Qt__
    * In order to build the application, you must first install Qt. It can be found here: http://qt-project.org/downloads. I used Qt 5.2.0 to develop the application, but other versions should work as well. It is important to install versions of the library for all the compiler variations that you intend to use. For example, if you're running Windows and want to compile for MinGW 32 bit and Visual Studio 2012 32 and 64 bit, you would install all three of those kits from the Qt online installer.

2. __Building the project__
    * Now that you have Qt installed, you can use it in two different ways to build the MatchMaker project, either through Qt Creator or through the command line.
        * __Using Qt Creator__
            * It's very simple to use Qt Creator to build the project. All you have to do is open Qt_MatchMaker/MatchMaker.pro with Qt Creator, configure the kits you would like to use, and then you should be able to immediately build the project in debug and release modes for every kit you have installed. This way is preferable to using the command line because you have more control over how the project is built.
        * __Using the command line__
            * The command line is the classic way to build any project. Thanks to Qt, the following process should work with minimal changes for all operating systems.
                1. For Windows users, Qt installs custom command prompts for each installed kit. Make sure to use the command prompt that corresponds to the desired kit you would like to build with for all of the following operations. For example, you would use the command prompt titled Qt 5.2.0 32-bit for Desktop (MSVC 2012) if you want to build a 32 bit binary with Visual Studio 2012.
                2. In addition to that, Visual Studio users may be required to call a special command before building anything, depending on how your system is setup. That command is:  
                `call "C:\Program Files (x86)\Microsoft Visual Studio 11.0\VC\vcvarsall.bat" x86`  
                This command simply sets up the command prompt for the Visual Studio features you request. Of course, depending on what version of Visual Studio you want to build with and what architecture you want to build for, the command would need to be modified accordingly.
                3. Now, you must find and cd to the Qt_MatchMaker directory.  
                `cd MatchMaker/Qt_MatchMaker`
                4. Next, you need to configure the project and generate makefiles. This can be done with the following command:  
                `qmake -o Makefile MatchMaker.pro`  
                If the command line cannot find qmake, then you may have to manually call the binary from your Qt installation's bin directory. For example, if you were building on Mac OSX, you might call qmake using something similar to the following:  
                `/Users/USERNAME/Qt/5.2.0/clang_64/bin/qmake -o Makefile MatchMaker.pro`  
                It is important to note that only the release version of the application can be built with the following command. If you also want to build a debug version, I suggest you use the Qt Creator method above.
                5. Now that qmake has generated the makefiles, all you need to do is call a make command that will compile the project. For Unix makefile installations, you would simply use:  
                `make`  
                If you're building with Visual Studio, you would use:  
                `nmake`  
                And if you're building with MinGW, you would use:  
                `mingw32-make`  
                And that's it. Now the project should be compiling, and if the Qt installation paths are set up successfully, there should be no errors, although there may be a few warnings.

3. __Gathering plugins__
    * Because the MatchMaker application interacts with MySQL and SQLite databases, you will need to also obtain copies of the MySQL and SQLite QtSql database drivers. If they were not included in your Qt installation (check /plugins/sqldrivers/), then you will have to build them in order to interact with those databases. Please see http://qt-project.org/doc/qt-5.0/qtsql/sql-driver.html for more information. In order to use the MySQL driver, you must also have a copy of the MySQL library (usually libmysql.dll for Windows or libmysqlclient_r.dylib for Mac OSX) available on the system PATH when running the MatchMaker application.
