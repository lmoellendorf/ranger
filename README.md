h1. API

See https://lmoellendorf.gitlab.io/ranger
or https://lmoellendorf.github.io/ranger/
for a description of the Application Programming Interface, i.e. how to code
with this library.

h1. Hardware

h2. RJ25 Cables

Makeblock mBot uses standard RJ25 cables to attach sensors and motors to the
controller.

Since LEGO Mindstorms NXT, LEGO also uses customized RJ25 cables to attach
sensors and motors to the controller "brick".
Those cables are similiar to those used by Makeblock with 2 crucial
differences.

1) Both the standard RJ25 cables and the customized LEGO cables have a plastic
tab to provide a latching mechanism that secures the physical connection. On
standard RJ25 cable plugs this tab is centered, where on LEGO cables this tab
is on the left side of the plug.

2) The pins of the plugs are used differently.

h2. Sensor Cables

The sensors cables of both vendors provide wires for

- analog input
- ground (GND)
- power supply, aka Voltage common collector (VCC)
- I2C serial communication bus (SCL/SDA)

The table below maps the pinout of LEGO Mindstorms cables to the pinout ouf
Makeblock mBot cables.


|_. Pin |_. Color |_. LEGO       |_. Makeblock    |
| 1     | white   | analog input | analog input 1 |
| 2     | black   | GND          | analog input 2 |
| 3     | red     | GND          | VCC            |
| 4     | green   | VCC          | GND            |
| 5     | yellow  | SCL          | SDA            |
| 6     | blue    | SDA          | SCL            |

Therefore to use LEGO Mindstorms sensors and motors on Makeblock
mBot we have to produce adapter cables.

We do this by replacing one plug of a LEGO Mindstorms cable by a standard RJ25
plug, using a standard RJ25 crimp tool.
To match the different pinouts we twist each color pair once so the order of
the colors in our standard plug becomes:

|_. Pin |_. Color |
| 1     | black   |
| 2     | white   |
| 3     | green   |
| 4     | red     |
| 5     | blue    |
| 6     | yellow  |
