# Hacking the Air Gap
In today’s digital ecosystem, hackers are a concerning threat. It is widely known that any system connected to the Internet is vulnerable. But what about an “air-gapped” computer? One that is not directly connected to the Internet or any other system that is connected to the Internet. The goal of this project is to demonstrate data leakage from an air-gapped computer via ultrasound. We envision an external system with WiFi for outside access that can bidirectionally communicate with the hacked computer efficiently and accurately. We hope that our ultrasound communication protocol will have other usages too.
## Design

![](miscellaneous/images/diagram.JPG?raw=true "diagram")

## Ultrasound Communication Protocol
![](/miscellaneous/images/ultrasound_communication_protocol.jpg?raw=true "protocol")
Digital information are stored as bytes. A byte most commonly consists of eight bits. Therefore, to represent a byte in hexadecimal, two hex values are needed. The first hex value makes up the four most siginificant bits of a byte, and the second hex value makes up the four least significant bits. 16 different tones are needed to map to each hexadecimal value. An extra tone is used to differentiate between the hex being the 4 MSBs or the 4 LSBs. 
#### Advantages 
- Quick
 - No delay needed after each tone representing a hex value is sent
 - Encoding in hexadecimal is 4x faster than in binary
#### Disadvantages
- Inaccurate 
- The electret microphone we are using is only rated up to 20 kHz. Since ultrasound is above 20 kHz, the more frequencies, the more difficult it is for the microphone to tell apart those frequencies. We also notice that for sounds above 21 kHz, the microphone can barely detect anything. 

