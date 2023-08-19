# ESP8266_Alarm-Clock
It's somekind of project using WEMOS D1 Mini as digital Clock that can produce ringtone as alarm sound, use network time protocol to get the datetime data and storing the .mp3 file on SPIFFS, but there are still many bugs in this code

# Component 
1. WEMOS D1 Mini
2. LCD 16x2 I2C
3. LM386 Amplifier Module + 2W Speaker

# Bugs 
Still dealing with IRAM ran out at certain process i.e. when I use two or more sound to produce it get error. (currently I just use one), Then when I move the audio generator process to loop function it get error again and stuck at setup function or when I use Bigfont to display the time, the sound won't come out, but the display working.

# Reference
1. https://github.com/earlephilhower/ESP8266Audio
2. https://github.com/schmurtzm/MrDiy-Audio-Notifier
3. https://cplusplus.com/reference/ctime/strftime/
4. https://www.martyncurrey.com/wp-content/uploads/2017/03/LCDs_12_CharSet_01.jpg

# Personal Note
I know that my English is still awful. But trust me that I learn this language diligently, even though just at writing
