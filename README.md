# pt6964
A display based on the PT6964 7 segment controller get a new life! muahahah! 
Salvaged display with keys from a old sat receiver, connected it to attiny2313 and wrote this little code to give the display a new purpose.
![Pinout](https://raw.githubusercontent.com/ringo2k/pt6964/master/doc/pt6964doku.jpg)
Maybe someone is also finding a pt6964 based display module or similar and try to give it a new life :-)
# adapt
You can change the pins in the pt6964.h file if your using another hardware. The communication is done bit banging style and every call i blocking till it is finished. 

# caution
The connection of the segments are not as mentioned in the pt6964 datasheet. I think the designers used other connection to the 7 segment display and LEDs to get a better layout (single layer PCB). But after a little try and error i got the signals right.



