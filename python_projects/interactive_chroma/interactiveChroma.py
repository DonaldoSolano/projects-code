import numpy as np
import cv2
import time
import pygame

#Variable to control de video loop in each state
frame_counter = 0
retro_counter = 0
#pyGame mixer initialization to hear audio
pygame.mixer.init()
pygame.mixer.set_num_channels(8)
voice = pygame.mixer.Channel(2)
ultronVoice = pygame.mixer.Sound("ultron.wav")

#variable to controle the chroma states
state = 0

#variables to capture the user skin effect, camera, external camera, instructions image, and the invitation video repectively
camara = cv2.VideoCapture(1)
instructions = cv2.imread("standBy.jpg")

#bool to controle videoCapture
videoRead = False

#Kernel for chroma improve
kernel = np.ones((3,3),np.uint8)
kernel*=255
kernel.itemset((0,0),0)
kernel.itemset((0,2),0)
kernel.itemset((2,0),0)
kernel.itemset((2,2),0)

#HSV segmentation variables
Hmin = 0
Hmax = 0
Smin = 0
Smax = 0
desvH = 0
desvS = 0
hache = []
ese = []
frame = 100

#Image analizer function to determine wich thing it is (object, human, animal, etc...) by its compactness.
def analyze(img):
    global c
    global area
    global contours
    global cnt
    ret,thresh = cv2.threshold(img,127,255,0)
    contours = cv2.findContours(thresh,mode=cv2.RETR_EXTERNAL,method=cv2.CHAIN_APPROX_SIMPLE)[1]    
    try:
        cnt = contours[0]
    except (IndexError):
        print("Need a five men, come on")
    m = cv2.moments(img)
    area = m["m00"]
    perimetro = cv2.arcLength(cnt,True)
    try:    
        c= area/perimetro**2
    except (ZeroDivisionError,UnboundLocalError):
        pass
        print("Can't divide by zero!")
    

#Code loop to in real time proccess frame by frame
while(True):
    disponible,fotograma = camara.read()
    if(disponible==True):
        fotograma = cv2.resize(fotograma,(1366,768))
        hsv = cv2.cvtColor(fotograma, cv2.COLOR_BGR2HSV)
        h,s,v=cv2.split(hsv)
        
        if(state == 0):
            if(frame>=0):
                hache.append(h)
                ese.append(s)
                frame = frame-1
            if(frame==0):
                totalH = 0
                totalS = 0
                totalAVGh = 0
                totalAVGs = 0
                for i in range(0,len(hache)):
                    a,desvH = cv2.meanStdDev(h)
                    b,desvS = cv2.meanStdDev(s)
                    totalAVGh += a
                    totalAVGs += b
                    totalH += desvH
                    totalS += desvS
                totalAVGh= totalAVGh/len(hache)
                totalH = totalH/len(hache)
                totalAVGs= totalAVGs/len(ese)
                totalS = totalS/len(ese)
                
                tolerancia = 3.5
                Hmin = int(totalAVGh - totalH*tolerancia)
                Hmax = int(totalAVGh + totalH*tolerancia)
                Smin = int(totalAVGs - totalS*tolerancia)
                Smax = int(totalAVGs + totalS*tolerancia)
                        
                frame=-1
        
            if(frame == -1):
                state = 1
                print("Calibration finished!")
                
        lower_values = np.array([Hmin,Smin,20])
        upper_values = np.array([Hmax,Smax,255])
        iteration = 3
        Resultado = cv2.inRange(hsv,lower_values,upper_values)
        erosion= cv2.erode(Resultado,kernel,iterations = iteration)
        dilatacion= cv2.dilate(erosion,kernel,iterations = iteration)
        noiseLessMask= cv2.dilate(dilatacion,kernel,iterations = 1)
        erosionDos= cv2.erode(noiseLessMask,kernel,iterations = 5)
        dilatacionDos= cv2.dilate(noiseLessMask,kernel,iterations = 5)
        bordes = cv2.absdiff(dilatacionDos,erosionDos)
        analyze(255-noiseLessMask)
        
        
        if(state == 1):
            if videoRead == False: 
                invitation = cv2.VideoCapture("invitation.mp4")
                videoRead = True
            i,inviteFrame = invitation.read()
            frame_counter += 1
            if i == True:
                inviteFrame=cv2.resize(inviteFrame,(1366,768))
                if frame_counter == 1:
                    voice.play(ultronVoice)
                if frame_counter == invitation.get(cv2.CAP_PROP_FRAME_COUNT):
                    frame_counter = 0 #Or whatever as long as it is the same as next line
                    invitation.set(cv2.CAP_PROP_POS_FRAMES, 0)
                cv2.imshow('Chroma',inviteFrame)
                cv2.waitKey(15)
            print("Compasidad es:",c)
            print("Area es:",area)
            cv2.imshow('noiseLessMask',noiseLessMask)
            if(area>40000000):
                print("¡Detecté algo!")
                voice.stop()
                videoRead = False
                x=0
                y=0
                frame_counter = 0
                start_time = time.time()
                state = 2
             
        if(state == 2):
            instructions=cv2.resize(instructions,(1366,768))
            cv2.imshow('Chroma',instructions)
            elapsedTime=time.time()-start_time
            print(elapsedTime)
            if(elapsedTime>10):
                print("TIEMPO!")
                state = 3
                
        if(state ==3):
            if(area>40000000):
                if videoRead == False:
                    matrixSkin = cv2.VideoCapture("matrixSkin.mp4")
                    retroLoop = cv2.VideoCapture("retroLoop.mp4")
                    videoRead = True
                m,matrixFrame = matrixSkin.read()
                r,retroFrame = retroLoop.read()
                frame_counter += 1
                retro_counter += 1
                if m == True and r == True:
                    matrixFrame=cv2.resize(matrixFrame,(1366,768))
                    retroFrame=cv2.resize(retroFrame,(1366,768))
                    if frame_counter == matrixSkin.get(cv2.CAP_PROP_FRAME_COUNT):
                        frame_counter = 0 #Or whatever as long as it is the same as next line
                        matrixSkin.set(cv2.CAP_PROP_POS_FRAMES, 0)
                    if retro_counter == retroLoop.get(cv2.CAP_PROP_FRAME_COUNT):
                        retro_counter = 0 #Or whatever as long as it is the same as next line
                        retroLoop.set(cv2.CAP_PROP_POS_FRAMES, 0)
                    newBorde = cv2.addWeighted(matrixFrame,0.1,retroFrame, 0.9,0)
                    bitwiseBorde = cv2.bitwise_and(newBorde,newBorde,mask=bordes)
                    dst = cv2.bitwise_and(retroFrame,retroFrame,mask=noiseLessMask) 
                    dsp = cv2.bitwise_and(matrixFrame,matrixFrame,mask=noiseLessMask-255)
                    dpr = dst + dsp
                    dsz = cv2.bitwise_and(dpr,dpr,mask=bordes-255)
                    resultado = cv2.add(bitwiseBorde,dsz)
                    resultado = cv2.GaussianBlur(resultado,(5,5),0)
                    cv2.imshow('Chroma',resultado)
            else:
                frame_counter = 0
                retro_counter = 0
                videoRead = False
                state = 1
        
        if(cv2.waitKey(1) & 0xFF == ord('r')):
            frame_counter = 0
            retro_counter = 0
            Hmin = 0
            Hmax = 0
            Smin = 0
            Smax = 0
            desvH = 0
            desvS = 0
            hache = []
            ese = []
            frame = 100
            state = 0
            videoRead = False
            
            
    else:
        print("Cámara no disponible")
        
    if(cv2.waitKey(1) & 0xFF == ord('q')):
        break
    
camara.release()
cv2.destroyAllWindows()