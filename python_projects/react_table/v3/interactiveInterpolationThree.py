# import the necessary packages
from imutils.video import VideoStream
import argparse
import datetime
import imutils
import time
import cv2

#counter to control the video reproductions
frame_counter = 0

#gesture detector
hand_cascade = cv2.CascadeClassifier('fist.xml')

#variable to controle the chroma states
state = 0

#bool to controle image read
imageRead = False

# construct the argument parser and parse the arguments
ap = argparse.ArgumentParser()
ap.add_argument("-v", "--video", help="path to the video file")
ap.add_argument("-a", "--min-area", type=int, default=500, help="minimum area size")
args = vars(ap.parse_args())

# if the video argument is None, then we are reading from webcam
if args.get("video", None) is None:
    vs = VideoStream(src=1).start()
    time.sleep(2.0)
# otherwise, we are reading from a video file
else:
    vs = cv2.VideoCapture(args["video"])

# initialize the first frame in the video stream
firstFrame = None

# loop over the frames of the video
while True:    
    # grab the current frame and initialize the occupied/unoccupied
    # text
    frame = vs.read()
    frame = frame if args.get("video", None) is None else frame[1]
    frame = cv2.flip(frame,1)
    text = "Unoccupied"
    # resize the frame, convert it to grayscale, and blur it
    frame = imutils.resize(frame, width=1920)
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    gray = cv2.GaussianBlur(gray, (21, 21), 0)
    
    #create de regions of interest
    roi=frame[200:600, 200:600]
    roiTwo=frame[700:1000, 700:1000]
    """roiThree=frame[200:600, 200:600]"""
    
    #make the regions of interest gray to pass them as parameters to the gesture initializers respectively
    grayROI = cv2.cvtColor(roi,cv2.COLOR_BGR2GRAY)
    grayROITwo = cv2.cvtColor(roiTwo,cv2.COLOR_BGR2GRAY)
    #initialize de detector
    hands = hand_cascade.detectMultiScale(grayROI,1.1,5)
    handsTwo = hand_cascade.detectMultiScale(grayROITwo,1.1,5)
    	# if the first frame is None, initialize it
    if firstFrame is None:
        firstFrame = gray
        continue
    # compute the absolute difference between the current frame and
    # first frame
    frameDelta = cv2.absdiff(firstFrame, gray)
    thresh = cv2.threshold(frameDelta, 25, 255, cv2.THRESH_BINARY)[1]
    # dilate the thresholded image to fill in holes, then find contours
	# on thresholded image
    thresh = cv2.dilate(thresh, None, iterations=2)
    cnts = cv2.findContours(thresh.copy(), cv2.RETR_EXTERNAL,cv2.CHAIN_APPROX_SIMPLE)
    cnts = cnts[0] if imutils.is_cv2() else cnts[1]
    for c in cnts:
        # if the contour is too small, ignore it
        if cv2.contourArea(c) < args["min_area"]:
            continue

		# compute the bounding box for the contour, draw it on the frame,
		# and update the text
        
        (x, y, w, h) = cv2.boundingRect(c)
        cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 255, 0), 2)
        contourArea=cv2.contourArea(c)
        print(contourArea)
        text = "Occupied"
        	# show the frame and record if the user presses a key
    cv2.imshow("Security Feed", frame)
    cv2.imshow("Thresh", thresh)
    cv2.imshow("Frame Delta", frameDelta)
    cv2.namedWindow('mainWindow', cv2.WND_PROP_FULLSCREEN)
    if(state == 0):
            if imageRead == False:
                instruct=cv2.VideoCapture('toMedellinInteractiveProductAnimation.mov')
                imageRead = True
            t, instructFrame = instruct.read()
            frame_counter += 1
            if t == True:
                instructFrame=cv2.resize(instructFrame,(1920,1080))
                if frame_counter == instruct.get(cv2.CAP_PROP_FRAME_COUNT):
                    frame_counter = 0
                    instruct.set(cv2.CAP_PROP_POS_FRAMES, 0)
                cv2.imshow('mainWindow',instructFrame)
            if text=="Occupied":
                state = 1
                start_time = time.time()
                imageRead = False
                
    if(state == 1):
            if imageRead == False:
                reloj=cv2.VideoCapture('Reloj2025.mov')
                imageRead = True
            r, relojFrame = reloj.read()
            frame_counter += 1
            if r == True:
                relojFrame=cv2.resize(relojFrame,(1920,1080))
                cv2.imshow('mainWindow',relojFrame)
                if frame_counter == reloj.get(cv2.CAP_PROP_FRAME_COUNT):
                    print("TIEMPO!")
                    imageRead = False
                    frame_counter = 0
                    state = 3
                    
    if(state ==3):
        if(text=="Occupied"):
            if imageRead == False:
                overlay = cv2.imread('cit.jpg',3)
                overlayTwo = cv2.imread('cit2.jpg',3)
                map1 = cv2.imread("mapa1.jpg",3)
                map2 = cv2.imread("mapa2.jpg",3)
                overlay = cv2.resize(overlay,(300,300))
                overlayTwo = cv2.resize(overlayTwo,(300,300))
                width,height,channels = overlay.shape
                widthTwo,heightTwo,channelsTwo = overlayTwo.shape
                imageRead = True
            if  imageRead == True:
                map1=cv2.resize(map1,(1920,1080))
                map2=cv2.resize(map2,(1920,1080))
                thresh=cv2.resize(thresh,(1920,1080))
                
                dst = cv2.bitwise_and(map2,map2,mask=thresh) 
                dsp = cv2.bitwise_and(map1,map1,mask=thresh-255)
                resultado = dst + dsp
                cv2.rectangle(resultado,(200,200),(600,600),(0,255,0),0)
                cv2.rectangle(resultado,(700,700),(1000,1000),(0,255,0),0)
                cv2.rectangle(resultado,(700,200),(600,600),(0,255,0),0)
                for(x,y,w,h) in hands:
                    cv2.rectangle(resultado,(x,y),(x+w,y+h),(0,255,0),2)
                    overlay=cv2.addWeighted(resultado[200:200+width,200:200+height],0,overlay,1,0)
                    resultado[200:200+width,200:200+height] = overlay
                for(x1,y1,w1,h1) in handsTwo:
                    cv2.rectangle(resultado,(x1,y1),(x1+w1,y1+h1),(0,255,0),2)
                    overlayTwo=cv2.addWeighted(resultado[700:700+widthTwo,700:700+heightTwo],0,overlayTwo,1,0)
                    resultado[700:700+widthTwo,700:700+heightTwo] = overlayTwo
                cv2.imshow('mainWindow',resultado)
        else:
            imageRead = False
            state = 0
	# if the `q` key is pressed, break from the lop
    if(cv2.waitKey(1) & 0xFF == ord('q')):
            break

# cleanup the camera and close any open windows
vs.stop() if args.get("video", None) is None else vs.release()
cv2.destroyAllWindows()

    
    