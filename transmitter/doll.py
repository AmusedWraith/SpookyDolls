import time

class Doll:
    def __init__(self, mySerial, addressString):
        self.serialLink = mySerial
        self.address = addressString


    def sendBehavior(self, command):
        
        self.sendSignal(command.ljust(8))
        

    def sendSignal(self, payload):
        # Send the payload to the address specified above.
        print("Sending Signal")
        print(payload)

        commandPacket = "<" + self.address + ";" + payload + ";;>"

        self.serialLink.write(str.encode(commandPacket))



        #self.nrf.set_address_bytes(len(self.address))
        #self.nrf.open_writing_pipe(self.address)
        
        
        #self.nrf.reset_packages_lost()
        #self.nrf.send(payload)
        #try:
        #    self.nrf.wait_until_sent()
                
        #except TimeoutError:
        #    print("Timeout waiting for transmission to complete.")
        #    time.sleep(10)
        #    return
            
        #if self.nrf.get_packages_lost() == 0:
            #print("Success")
        #    print(f"Success: lost={self.nrf.get_packages_lost()}, retries={self.nrf.get_retries()}")
        #else:
        #    #print("Error")
        #    print(f"Error: lost={self.nrf.get_packages_lost()}, retries={self.nrf.get_retries()}")

        # Wait 10 seconds before sending the next reading.
       # time.sleep(10)
