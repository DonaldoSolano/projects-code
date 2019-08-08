#!/usr/bin/python3
import serial
import time
from xbee import XBee, ZigBee

serial_port = serial.Serial('COM5', 9600)

def print_data(data):
	"""
	This method is called whenever data is received
	from the associated XBee device. Its first and
	only argument is the data contained within the
	frame.
	"""
	rxFrom = data['source_addr']
	payload = data['rf_data']
	print('Receive from ' + hex(int.from_bytes(rxFrom, byteorder='big'))+': ' + str(int.from_bytes(payload, byteorder='big')))
	#print(data)
	
xbee = ZigBee(serial_port, escaped=True, callback=print_data)

while True:
	try:
		time.sleep(1)
		#xbee.send('tx', frame_id=b'A', dest_addr_long=b'\x00\x00\x00\x00\x00\x00\x00\x00',data=b'hola from device')
	except KeyboardInterrupt:
		break

xbee.halt()
serial_port.close()

