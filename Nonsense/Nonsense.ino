//This sketch uses 4 potentiometers and a Speakjet IC to babble a constant stream of syllables.
//
//The Speakjet should be wired up as per the datasheet at https://www.sparkfun.com/datasheets/Components/General/speakjet-usermanual.pdf. I connected pin 12 to V+ 
//through a 1k resistor. The 5V output from the Arduino is fine for power. Set up the output from pin 18 as shown in the datasheet, including 2-pole filter. It doesn't 
//seem to matter exactly which values you use there - I didn't have the right capacitors - but just get as close as you can.
//
//Data out from the Arduino is on output 11. Input from the potentiometers is on analog ins 0 - 3 (see https://www.arduino.cc/en/Tutorial/ReadAnalogVoltage if you need help)
//
//I found it useful to add a momentary switch that would connect the Speakjet reset pin (11) to Gnd in case it needed resetting. I also added LEDs (with resistors in series)
//on the 3 data out pins of the Speakjet (15,16,17) as they give a good bit of visual feedback about the state of the chip.
//
//I ended up having to send the values to the Speakjet as hex values and couldn't get it to work any other way. If anyone knows how to make it work without doing this I'd
//be interested to hear from them!
#include <SoftwareSerial.h>
SoftwareSerial speakJet(0, 11); // RX, TX - we're not receiving so set RX to pin 0
void setup() {
  //Set the output pin as an output. Not sure if this is actually required but whatevs.
  pinMode(11, OUTPUT);
  // set the data rate for the SoftwareSerial port
  speakJet.begin(9600);
  //The following line sends the sync character to the Speakjet. Put the Speakjet in sync mode and uncomment the line if you need to set the baud rate.
  //speakJet.print(0x55);
}

void loop() {
  int delayLength = 100;
  int phoneme = random(138, 180); //This range seemed to sound best but feel free to tweak.
  int pitch = map(analogRead(1),0,1023,0,255); //Mapped to range of available pitch values.
  int bend = map(analogRead(2),0,1023,0,15); //Mapped to range of available bend values.
  int speechSpeed = map(analogRead(0),0,1023,0,127); //Mapped to range of available speedvalues.
  speakJet.write(0x15); //Send speed command
  speakJet.write(map(speechSpeed,0,127,0x7F,0x0)); //Send speed value mapped to hex
  speakJet.write(0x16); //Send pitch command
  speakJet.write(map(pitch,0,255,0xFF,0x0)); //Send pitch value mapped to hex
  speakJet.write(0x17); //Send bend command
  speakJet.write(map(bend,0,15,0x0,0xF)); //Send bend value mapped to hex
  speakJet.write(map(phoneme,0,255,0x0,0xFF)); //Send phoneme value mapped to hex
  delay(delayLength); //Delay for however long the delay length is
  }

