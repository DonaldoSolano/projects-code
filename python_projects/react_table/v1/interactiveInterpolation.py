import numpy as np
import cv2
import time
import pygame

#pyGame mixer initialization to hear audio
pygame.mixer.init()
pygame.mixer.set_num_channels(8)
voice = pygame.mixer.Channel(2)
#ultronVoice = pygame.mixer.Sound("ultron.wav")

#variable to controle the chroma states
state = 0

#variables to capture the user skin effect, camera, external camera, instructions image, and the invitation video repectively
camara = cv2.VideoCapture(0)

#bool to controle image read
imageRead = False

#Kernel for frame blending improve
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
                
                tolerancia = 3.2
                Hmin = int(totalAVGh - totalH*tolerancia)
                Hmax = int(totalAVGh + totalH*tolerancia)
                Smin = int(totalAVGs - totalS*tolerancia)
                Smax = int(totalAVGs + totalS*tolerancia)
                        
                frame=-1
        
            if(frame == -1):
                imageRead = False
                state = 1
                print("Calibration finished!")
                
        lower_values = np.array([Hmin,Smin,20])
        upper_values = np.array([Hmax,Smax,255])
        iteration = 3
        Resultado = cv2.inRange(hsv,lower_values,upper_values)
        erosion= cv2.erode(Resultado,kernel,iterations = iteration)
        dilatacion= cv2.dilate(erosion,kernel,iterations = iteration)
        noiseLessMask= cv2.dilate(dilatacion,kernel,iterations = 1)
        ret, thresh = cv2.threshold(noiseLessMask,0,255,cv2.THRESH_BINARY_INV+cv2.THRESH_OTSU)
        erosionDos= cv2.erode(noiseLessMask,kernel,iterations = 5)
        dilatacionDos= cv2.dilate(noiseLessMask,kernel,iterations = 5)
        bordes = cv2.absdiff(dilatacionDos,erosionDos)
        analyze(255-noiseLessMask)
            
        if(state == 1):
            if imageRead == False:
                toMedellin = cv2.imread("toMedellin.jpg")
                imageRead = True
            if imageRead == True:
                toMedellin=cv2.resize(toMedellin,(1366,768))
                cv2.imshow('mainWindow',toMedellin)
            print("Compasidad es:",c)
            print("Area es:",area)
            cv2.imshow('thresh',thresh)
            """if(area>40000000):
                print("¡Detecté algo!")
                voice.stop()
                imageRead = False
                x=0
                y=0
                frame_counter = 0
                start_time = time.time()
                state = 2
             
        if(state == 2):
            if imageRead == False:
                instructions = cv2.imread("standBy.jpg")
                imageRead = True
            if imageRead == True:
                instructions=cv2.resize(instructions,(1366,768))
                cv2.imshow('mainWindow',instructions)
                elapsedTime=time.time()-start_time
                print(elapsedTime)
                if(elapsedTime>10):
                    print("TIEMPO!")
                    state = 3
                
        if(state ==3):
            if(area>40000000):
                if imageRead == False:
                    map1 = cv2.imread("mapa1.jpg")
                    map2 = cv2.imread("mapa2.jpg")
                    imageRead = True
                if  imageRead == True:
                    map1=cv2.resize(map1,(1366,768))
                    map2=cv2.resize(map2,(1366,768))
                    
                    newBorde = cv2.addWeighted(map1,0.1,map2, 0.9,0)
                    bitwiseBorde = cv2.bitwise_and(newBorde,newBorde,mask=bordes)
                    dst = cv2.bitwise_and(map1,map1,mask=noiseLessMask) 
                    dsp = cv2.bitwise_and(map2,map2,mask=noiseLessMask-255)
                    dpr = dst + dsp
                    dsz = cv2.bitwise_and(dpr,dpr,mask=bordes-255)
                    resultado = cv2.add(bitwiseBorde,dsz)
                    resultado = cv2.GaussianBlur(resultado,(5,5),0)
                    cv2.imshow('mainWindow',resultado)
            else:
                imageRead = False
                state = 1
        
        if(cv2.waitKey(1) & 0xFF == ord('r')):
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
            imageRead = False"""
            
            
    else:
        print("Cámara no disponible")
        
    if(cv2.waitKey(1) & 0xFF == ord('q')):
        break
    
camara.release()
cv2.destroyAllWindows()