# MalwAIR
MalwAIR is an in-progress malware (for research purposes) designed specifically to leak data from an air gapped computer. An air gapped computer is one that is isolated from unsecured networks, such as the Internet. How MalwAIR works is that it captures data and ouputs it through the physical quantities of a computer. Currently, MalwAIR can transmit data through a computer's speaker. By outputting the data through ultrasound, humans would not be able to hear it!
### Dependencies
  - [RtAudio](https://www.music.mcgill.ca/~gary/rtaudio/) - A set of C++ classes that provide a common API for realtime audio input/output across a variety of operating systems
### Installation and Running
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
