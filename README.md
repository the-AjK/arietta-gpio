# arietta-gpio

**arietta-gpio** is a sysfs **G**eneral **P**urpose **I**nput **O**utput 
wrapper for node.js. It gives you the ability to control GPIO of the Acmesystems Arietta board in a 
simple object orientated manner.
Visit [AcmeSystems official site](http://www.acmesystems.it/arietta) for more informations about this hardware.

## Installation

Install **arietta-gpio** with [npm](http://npmjs.org):

    $ npm install arietta-gpio

## Preview

    var arietta = require('arietta-gpio');

    var button = new arietta.GPIO(81);  //81 is the kernel ID for the onboard pushbutton
	var led = new arietta.GPIO(64);		//64 is the kernel ID for pin 39 (PC0)
	
    led
        .direction(arietta.GPIO.OUT)
        .value(arietta.GPIO.LOW)
        ;
		  
	button
        .direction(arietta.GPIO.IN)
        ;
		
	while(true){	
		if(button.value() != arietta.GPIO.HIGH){
			led.value(arietta.GPIO.HIGH);
		}else{
			led.value(arietta.GPIO.LOW);
		}
	}

## Documentation

### Class: GPIO 

The `GPIO` function prototype is a C++ add-on which abstracts a GPIO device as
instancable object. There are some class constants defined which should be used
for setting values (see below).

#### GPIO.IN

Direction constant used to determinate that our GPIO device listens for 
incoming signals. While a device is set to `IN` we can only read and not write 
to it.

#### GPIO.OUT

Direction constant used to determinate that our GPIO device writes outgoing
signals. While a device is set to `OUT` we can read and set the current value.

#### GPIO.LOW

Value constant for off state of a GPIO device.

#### GPIO.HIGH

Value constant for on state of a GPIO device.

#### new GPIO(id)

    var gpio23 = new GPIO(23);

Creates a new instance of the GPIO class. Internally it will do a GPIO export
if neccessary and open the GPIO's value and direction file descriptor to 
reduce syscalls. The C++ deconstructor ensures that the file descriptors are 
closed and the GPIO device is getting unexported (this would not have been
possible with plain JavaScript).

#### gpio.direction([value])

    if (gpio23.direction() === GPIO.OUT)
        gpio23.direction(GPIO.IN);

Returns the current GPIO direction mode if no arguments supplied else it will
check if the first argument is a valid constant and then will set this as
GPIO direction.

#### gpio.activeLow([value])

    if (gpio23.activeLow() === GPIO.HIGH)
        gpio23.activeLow(GPIO.LOW);

Some circuits use a GPIO the other way around: This means the GPIO enables the
circuit when it switches to `LOW`. In order to keep semantics of value you can
switch the active mode by using `activeLow` with either `LOW` or `HIGH`.

#### gpio.value([value])

    while (gpio23.value() != GPIO.HIGH)
        // wait until GPIO value changes to HIGH

    // use GPIO as output device
    gpio23.direction(GPIO.OUT).value(GPIO.LOW);

Returns the current GPIO value if no arguments supplied else it will check if
the first argument is a valid constant and then will use this as GPIO value.

## License

Copyright © 2013 Bodo Kaiser <i@bodokaiser.io>

Copyright © 2015 Alberto Garbui <alberto.garbui@gmail.com>

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.