import cv2
import datetime
import argparse
from transmitter.play import Play
import serial
import time
import warnings
import json
import imutils
#import numpy as np
#import matplotlib.pyplot as plt

# construct the argument parser and parse the arguments
#ap = argparse.ArgumentParser()
#ap.add_argument("-c", "--conf", required=True,
#    help="path to the JSON configuration file")
#args = vars(ap.parse_args())

warnings.filterwarnings("ignore")
#conf = json.load(open(args["conf"]))

conf = json.load(open("conf.json"))

cap = cv2.VideoCapture(0)
if not cap.isOpened():
	print("Cannot open camera")
	exit()

#cap.set(cv2.CAP_PROP_FOURCC, cv2.VideoWriter_fourcc('M', 'J', 'P', 'G')) # depends on fourcc available camera
cap.set(cv2.CAP_PROP_FRAME_WIDTH, conf["frame_width"])
cap.set(cv2.CAP_PROP_FRAME_HEIGHT, conf["frame_height"])
#cap.set(cv2.CAP_PROP_FPS, 60)

frameRate = conf["fps"]
prevFrameTime = 0
prevTriggerTime = 0
minFrames = 10
minTimeBetweenTriggers = 60
motionCounter = 0
mode = "AUTO"

mog = cv2.createBackgroundSubtractorMOG2()

serialLink = serial.Serial(port='/dev/ttyUSB0',   baudrate=9600, timeout=.1)
time.sleep(5)

thePlay = Play(serialLink)

myScene = thePlay.getTestScene()
myScene.playScene()

while (cap.isOpened()):

	time_elapsed = time.time() - prevFrameTime
	res, frame = cap.read()

	if time_elapsed > 1. / frameRate:
		prevFrameTime = time.time()

		motionDetected = False
		gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

		fgmask = mog.apply(gray)

		kernel = cv2.getStructuringElement(cv2.MORPH_ELLIPSE, (5, 5))
		fgmask = cv2.erode(fgmask, kernel, iterations=1)
		fgmask = cv2.dilate(fgmask, kernel, iterations=1)

		contours, hierarchy = cv2.findContours(fgmask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

		for contour in contours:
			# Ignore small contours
			if cv2.contourArea(contour) < conf["min_area"]:
				continue

			# Draw bounding box around contour
			motionDetected = True
			motionCounter=motionCounter+1
			print("MotionCounter: " + str(motionCounter))
			x, y, w, h = cv2.boundingRect(contour)
			cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 255, 0), 2)

		if motionDetected == False:
			motionCounter = 0

		if mode == "AUTO":
			cv2.putText(frame, "Automatic Mode", (10, 20),
				cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 0, 255), 2)
		else:
			cv2.putText(frame, "Manual Mode", (10, 20),
						cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 0, 255), 2)

		if motionDetected:
			cv2.putText(frame, "Motion Detected", (10, 40),
				cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 0, 255), 2)
		else:
			cv2.putText(frame, "No Motion Detected", (10, 40),
				cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 0, 255), 2)

		cv2.imshow('Motion Detection', frame)

		key = cv2.waitKey(1)

		if key == ord('q'):
			break

		if key == ord('t'):
			if mode == "MANUAL":
				mode = "AUTO"
			else:
				mode = "MANUAL"
			continue

		if key == ord('0') and mode == "MANUAL":
			myScene = thePlay.getScene(0)
			myScene.playScene()

		if key == ord('1') and mode == "MANUAL":
			myScene = thePlay.getScene(1)
			myScene.playScene()

		if key == ord('2') and mode == "MANUAL":
			myScene = thePlay.getScene(2)
			myScene.playScene()

		if key == ord('3') and mode == "MANUAL":
			myScene = thePlay.getScene(3)
			myScene.playScene()

		if key == ord('4') and mode == "MANUAL":
			myScene = thePlay.getScene(4)
			myScene.playScene()

		if key == ord('5') and mode == "MANUAL":
			myScene = thePlay.getScene(5)
			myScene.playScene()

		if key == ord('6') and mode == "MANUAL":
			myScene = thePlay.getScene(6)
			myScene.playScene()


		if mode == "AUTO" and motionCounter > minFrames and ((time.time() - prevTriggerTime) > minTimeBetweenTriggers):
			prevTriggerTime = time.time()
			myScene = thePlay.getRandomScene()
			myScene.playScene()

		# accumulate the weighted average between the current frame and
		# previous frames, then compute the difference between the current	`1
		# frame and running average
		#cv2.accumulateWeighted(gray, avg, 0.5)
		#frameDelta = cv2.absdiff(gray, cv2.convertScaleAbs(avg))

		# threshold the delta image, dilate the thresholded image to fill
		# in holes, then find contours on thresholded image
		#thresh = cv2.threshold(frameDelta, conf["delta_thresh"], 255,
		#					   cv2.THRESH_BINARY)[1]
		#thresh = cv2.dilate(thresh, None, iterations=2)
		#cnts = cv2.findContours(thresh.copy(), cv2.RETR_EXTERNAL,
			#					cv2.CHAIN_APPROX_SIMPLE)
		#cnts = imutils.grab_contours(cnts)

		# loop over the contours
		#for c in cnts:
			# if the contour is too small, ignore it
		#	if cv2.contourArea(c) < conf["min_area"]:
		#		continue

			# compute the bounding box for the contour, draw it on the frame,
			# and update the text
		#	print("Why")
	#		(x, y, w, h) = cv2.boundingRect(c)
#			print(x)
#			print(y)
#			print(w)
#			print(h)
#			cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 255, 0), 2)
#			text = "Occupied"
		#	blocks += 1

		#if text == "Occupied":
		#	outputText = "Occupied: " + str(blocks) + " blocks"

		# draw the text and timestamp on the frame
		#ts = timestamp.strftime("%A %d %B %Y %I:%M:%S%p")
		#cv2.putText(frame, "Status: {}".format(text), (10, 20),
		#			cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 0, 255), 2)
		#cv2.putText(frame, ts, (10, frame.shape[0] - 10), cv2.FONT_HERSHEY_SIMPLEX,
		#			0.35, (0, 0, 255), 1)




	#time.sleep(5)

	#myScene = thePlay.getScene(1)
	#myScene.playScene()


cap.release()
cv2.destroyAllWindows()
