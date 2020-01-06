# README #

This is LAB 07

### What is this repository for? ###

* Lab 07 Experiment with a Cube

### How do I get set up? ###

* Clone repository
* Ensure `SFML_SDK` environment variable exits
* Ensure SFML Version SFML 2.3.2 Visual C++ 14 (2015) - 32-bit is installed 
http://www.sfml-dev.org/files/SFML-2.3.2-windows-vc14-32-bit.zip "SFML-2.3.2-windows-vc14-32-bit.zip"
* To check environment variable is set correctly open a command prompt and type `echo %SFML_SDK%` the path to SFML sdk should be show.
* Select a project default target `x86` when running executable
* If the project builds but does not `xcopy` the required dll's try moving your project to a directory you have full access to, see http://tinyurl.com/SFMLStarter for a guide on post build events.
* Alternatively set the Environment Variable in Configuration Properties | Debugging | Environment to `PATH=%PATH%;%SFML_SDK%\bin` this will ensure DLL's are discoverable when running in debug mode with copying the DLL's to the executable directory

### Cloning Repository ###
* Run GitBash and type the Follow commands into GitBash

* Check Present Working Directory `pwd`

* Change to the C drive or other drive `cd c:`

* Make a projects Directory `mkdir projects`

* Change to the projects directory by `cd projects`

* Clone the project `git clone https://MuddyGames@bitbucket.org/MuddyGames/gameplay-programming-i-lab-07.git`

* Change to the project directory `cd projects gameplay-programming-i-lab-07`

* List files that were downloaded `ls`

### Who do I talk to? ###

* philip.bourke@itcarlow.ie