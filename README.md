This sketch uses 3 potentiometers, a button and a Speakjet IC to babble syllables.

The Speakjet should be wired up as per the datasheet at https:www.sparkfun.com/datasheets/Components/General/speakjet-usermanual.pdf. I connected pin 12 to V+ 
through a 1k resistor. The 5V output from the Arduino is fine for power. Set up the output from pin 18 as shown in the datasheet, including 2-pole filter. It doesn't 
seem to matter exactly which values you use there - I didn't have the right capacitors - but just get as close as you can.

Data out from the Arduino is on output 11. Input from the potentiometers is on analog ins 0 - 2 (see https:www.arduino.cc/en/Tutorial/ReadAnalogVoltage if you need help)
The button is on pin 2 (see https:www.arduino.cc/en/Tutorial/Button if you need help). Data is sent to the Speakjet while the button is held.

I found it useful to add a momentary switch that would connect the Speakjet reset pin (11) to Gnd in case it needed resetting. I also added LEDs (with resistors in series)
on the 3 data out pins of the Speakjet (15,16,17) as they give a good bit of visual feedback about the state of the chip.

I ended up having to send the values to the Speakjet as hex values and couldn't get it to work any other way. If anyone knows how to make it work without doing this I'd
be interested to hear from them!