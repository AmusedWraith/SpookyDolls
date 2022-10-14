import RPi.GPIO as GPIO
from NRF24L01.lib_nrf24 import NRF24
import time
import spidev

GPIO.setmode(GPIO.BOARD)

transmitAddr = [0xe2,0xe2,0xe2,0xe2,0xe2]
#transmitAddr = 0xe8e8e7e7e7


radio = NRF24(GPIO, spidev.SpiDev())
radio.begin(0, 17)
#radio.setPayloadSize(32)
radio.setChannel(115)

radio.setDataRate(NRF24.BR_250KBPS)
radio.setPALevel(NRF24.PA_MIN)
#radio.setAutoAck(True)
#radio.enableDynamicPayloads()
#radio.enableAckPayload()

#radio.openReadingPipe(1,transmitAddr)
#radio.startListening()
radio.openWritingPipe(transmitAddr)
radio.stopListening()
radio.printDetails()


message = list("Hello World");
radio.write(message);
print("we sent the message of {}".format(message))
    
#    if radio.isAckPayloadAvailable():
#        returnedPL = []
#        radio.read(returnedPL, radio.getDynamicPayloadSize())
#        print("Our returned payload was {}".format(returnedPL))
#    else:
#        print("No received acknowledgement.")
    
time.sleep(10)
  
GPIO.cleanup()
    
    