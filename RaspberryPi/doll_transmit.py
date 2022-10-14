import RPi.GPIO as GPIO
from NRF24L01.lib_nrf24 import NRF24
import time
import spidev

GPIO.setmode(GPIO.BCM)

transmitAddr = [0x31,0x30,0x30,0x30,0x30]
#transmitAddr = 0xe8e8e7e7e7


radio = NRF24(GPIO, spidev.SpiDev())
GPIO.setup (27,GPIO.OUT)
GPIO.output(27,False)
radio.begin(0, 27)
#radio.setPayloadSize(32)
radio.setChannel(76)

radio.setDataRate(NRF24.BR_1MBPS)
radio.setPALevel(NRF24.PA_MIN)
#radio.setAutoAck(True)
#radio.enableDynamicPayloads()
#radio.enableAckPayload()

#radio.openReadingPipe(1,transmitAddr)
#radio.startListening()
radio.openWritingPipe(transmitAddr)

radio.printDetails()
radio.stopListening()

time.sleep(5)

#message = list("Hello World");
radio.write("Your Button State is High");
print("SENT")
    
#    if radio.isAckPayloadAvailable():
#        returnedPL = []
#        radio.read(returnedPL, radio.getDynamicPayloadSize())
#        print("Our returned payload was {}".format(returnedPL))
#    else:
#        print("No received acknowledgement.")
    
time.sleep(10)
  
GPIO.cleanup()
    
    
