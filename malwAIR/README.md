# MalwAIR
---
MalwAIR is an in-progress malware (for research purposes) designed specifically to leak data from an air gapped computer, a computer that is isolated from unsecured networks, such as the Internet. At the high level, MalwAIR outputs data in the form of ultrasound from the speaker of a computer. The plan for MalwAIR is also to read in ultrasound from the microphone of a computer in order to allow bi-directional communication with an external system.  


### Dependencies
---
  - [RtAudio](https://www.music.mcgill.ca/~gary/rtaudio/) - A set of C++ classes that provide a common API for realtime audio input/output across a variety of operating systems
### Installation and Running
---
#### Linux 
Install the dependencies. 
[Download RtAudio](http://www.music.mcgill.ca/~gary/rtaudio/release/rtaudio-5.1.0.tar.gz)
```sh
$ tar -xvf rtaudio-5.1.0.tar.gz
$ cd rtaudio-5.1.0
$ ./configure
$ make install
```
Clone the main repo and change directory to here.
```sh
$ git clone https://github.com/jCorralesLozano/Hacking-The-Air-Gap.git
$ cd Hacking-The-Air-Gap/MalwAIR
```
Compile this project. See Makefile for details.
```sh
$ make
```
The libraries for RtAudio were by default installed in /usr/local/lib. Before running, add the path to environment variable.
```sh
$ LD_LIBRARY_PATH=/usr/local/lib
$ export LD_LIBRARY_PATH
```
Run program.
```sh
$ make run
```
#### Windows
Install [MinGW](https://osdn.net/projects/mingw/releases/)
* According to RtAudio's installation documentation, RtAudio can be compiled with MinGW compiler or MS Visual Studio. However, we had trouble with compiling it with MS Visual Studio.
* When installing MinGW, the pakages we selected for the install were mingw32-gcc-g++\-bin (necessary), msys-base-bin (necessary), mingw-developer-toolkit-bin (probably not necessary), and mingw32-base-bin (probably not necessary) 

[Download RtAudio](http://www.music.mcgill.ca/~gary/rtaudio/release/rtaudio-5.1.0.tar.gz)

Launch MSYS command line (default path is C:\MinGW\msys\1.0\msys.bat). From now on, everything is executed inside MSYS.
Navigate to the location of where RtAudio is downloaded and execute the following commands:
```sh
$ tar -xvf rtaudio-5.1.0.tar.gz
$ cd rtaudio-5.1.0
$ ./configure
$ make install
```
Clone the main repo and change directory to here.
```sh
$ git clone https://github.com/jCorralesLozano/Hacking-The-Air-Gap.git
$ cd Hacking-The-Air-Gap/MalwAIR
```
Compile this project. See Makefile for details.
```sh
$ make
```
The libraries for RtAudio were by default installed in /usr/local/lib. Before running, add the path to environment variable.
```sh
$ LD_LIBRARY_PATH=/usr/local/lib
$ export LD_LIBRARY_PATH
```
Run program.
```sh
$ make run
```

