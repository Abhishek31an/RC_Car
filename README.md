# RC_Car
A feature-rich RC car built with an Arduino, controlled by a multi-channel Flysky RC receiver. The code reads PWM signals from the receiver for proportional steering and throttle control. It also uses auxiliary channels to manage accessories like dimmable headlights, ground/back LEDs, and a buzzer with horn and siren modes.

## 🤖 Hardware Connections

### Flysky Receiver Channels (Inputs)
* **Arduino Pin 9** &larr; Receiver Channel 1 (Steering)
* **Arduino Pin A1** &larr; Receiver Channel 3 (Throttle)
* **Arduino Pin 12** &larr; Receiver Channel 7 (Buzzer Mode)
* **Arduino Pin 8** &larr; Receiver Channel 8 (Ground LED)
* **Arduino Pin 13** &larr; Receiver Channel 10 (Headlight Brightness)

### Motor Driver (e.g., L298N) (Outputs)
* **Arduino Pin 5 (PWM)** &rarr; Enable A (enable1)
* **Arduino Pin 6 (PWM)** &rarr; Enable B (enable2)
* **Arduino Pin 2** &rarr; Input 1 (in1)
* **Arduino Pin 3** &rarr; Input 2 (in2)
* **Arduino Pin 4** &rarr; Input 3 (in3)
* **Arduino Pin 7** &rarr; Input 4 (in4)

### Accessories (Outputs)
* **Arduino Pin 10 (PWM)** &rarr; Headlight LED (hled)
* **Arduino Pin 11** &rarr; Buzzer (buzzer)
* **Arduino Pin A0** &rarr; Ground LED (gled)
* **Arduino Pin A2** &rarr; Back LED (bled)
