from time import sleep
from pySerialTransfer import pySerialTransfer as txfer



if __name__ == '__main__':
    try:

        dollCommandString = "FADE    ;00002";

        dollCommand = list(dollCommandString);

        link = txfer.SerialTransfer('/dev/ttyUSB0')

        link.open()
        sleep(5)

        while True:
            sendSize = 0

            sendSize = link.tx_obj(dollCommand, start_pos=sendSize)

            link.send(sendSize)

            if link.available():
                recSize = 0
                address = link.rx_obj(obj_type=str,
                        start_pos=recSize,
                        obj_byte_size=5)
                print(address)


            elif link.status < 0:
                if link.status == txfer.CRC_ERROR:
                    print('ERROR: CRC_ERROR')
                elif link.status == txfer.PAYLOAD_ERROR:
                    print('ERROR: PAYLOAD_ERROR')
                elif link.status == txfer.STOP_BYTE_ERROR:
                    print('ERROR: STOP_BYTE_ERROR')
                else:
                    print('ERROR: {}'.format(link.status))

    except KeyboardInterrupt:
        link.close()