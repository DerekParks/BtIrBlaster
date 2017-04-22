#!/usr/bin/env python

from flask import Flask

import serial
import os
import os.path
import time

app = Flask(__name__)

DEV="/dev/rfcomm0"
BAUD=9600
POWER_ON=b'0xC1AA09F6'
RECONNECT_CMD='./'


def checkRfConn():
	if not os.path.exists(DEV):
		os.system("./connentrfComm.sh")
		time.sleep(2)

@app.route('/on')
def turn_them_shits_on():

	checkRfConn()

	with serial.Serial(DEV, BAUD, timeout=10) as ser:
		if not ser.isOpen():
			ser.open()
		ser.write(POWER_ON)
		print ser.read(10)
		

	return 'OK'
