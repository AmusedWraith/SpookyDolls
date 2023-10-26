from transmitter.scene import Scene
from transmitter.doll import Doll
import random
# takes in data about the motion detected and returns a scene which
# contains thes the addresses and commands to send out to dolls
class Play:
    def __init__(self, mySerial):
        self.serialLink = mySerial
        
        self.actors = []

        self.actors.append( Doll(self.serialLink,"00001") )  # Red eyes
        self.actors.append( Doll(self.serialLink,"00002") )  # blue eyes
        self.actors.append( Doll(self.serialLink,"00003") )  # green eyes
        self.actors.append( Doll(self.serialLink,"00004") )  # yellow eyes
        self.actors.append( Doll(self.serialLink,"00005") )  # red eyes
        self.actors.append( Doll(self.serialLink,"00006") )  # background lighting
        self.actors.append( Doll(self.serialLink,"00007") )  # big red eyes
        
        #Test Schene
        tempScene = Scene()
        tempScene.addPart(self.actors[0],"TEST  30")
        tempScene.addPart(self.actors[1],"TEST  30")
        tempScene.addPart(self.actors[2],"TEST  30")
        tempScene.addPart(self.actors[3],"TEST  30")
        tempScene.addPart(self.actors[4],"TEST  30")
        tempScene.addPart(self.actors[5],"GNGLW 30")
        tempScene.addPart(self.actors[6],"TEST  30")
        tempScene.addMusic("doll_quotes/music_1.mp3")
        
        self.testScene = tempScene
        
        self.scenes = []

        #0
        # Single glowing eyes for 30 seconds
        tempScene = Scene()
        tempScene.addPart(self.actors[0],"FADE  30")
        tempScene.addPart(self.actors[1],"FADE  30")
        tempScene.addPart(self.actors[2],"FADE  30")
        tempScene.addPart(self.actors[3],"FADE  30")
        tempScene.addPart(self.actors[4],"FADE  30")
        tempScene.addPart(self.actors[5],"RDGLW 30")
        tempScene.addPart(self.actors[6],"FADE  30")
        tempScene.addMusic("doll_quotes/whispers_1.mp3")

        self.scenes.append (tempScene)

        #1
        tempScene = Scene()
        tempScene.addPart(self.actors[0],"FADE  45")
        tempScene.addPart(self.actors[5],"RDGLW 45")
        tempScene.addMusic("doll_quotes/singing_1.mp3")

        self.scenes.append (tempScene)

        #2
        tempScene = Scene()
        tempScene.addPart(self.actors[2],"FADE  45")
        tempScene.addPart(self.actors[5],"GNGLW 45")
        tempScene.addMusic("doll_quotes/talking_2.mp3")

        self.scenes.append (tempScene)

        #3
        tempScene = Scene()
        tempScene.addPart(self.actors[1],"FADE  45")
        tempScene.addPart(self.actors[5],"GNGLW 45")
        tempScene.addMusic("doll_quotes/talking_8.mp3")

        self.scenes.append (tempScene)

        #4
        tempScene = Scene()
        tempScene.addPart(self.actors[3],"FADE  45")
        tempScene.addPart(self.actors[5],"RDGLW 45")
        tempScene.addMusic("doll_quotes/talking_6.mp3")

        self.scenes.append (tempScene)

        #5
        tempScene = Scene()
        tempScene.addPart(self.actors[4],"FADE  45")
        tempScene.addPart(self.actors[5],"RDGLW 45")
        tempScene.addMusic("doll_quotes/talking_5.mp3")

        self.scenes.append (tempScene)

        #6
        tempScene = Scene()
        tempScene.addPart(self.actors[6],"FLASH 30")
        tempScene.addPart(self.actors[5],"RDGLW 30")
        tempScene.addMusic("doll_quotes/talking_1.mp3")

        self.scenes.append (tempScene)
        
    def getRandomScene(self):
        sceneNum = random.randint(0, 6)
        return self.scenes[sceneNum];

    def getScene(self, index):

        if(index < len(self.scenes)):
            return self.scenes[index];

        print("[ERROR] Invalid Index")
        return self.scenes[0]


    def getTestScene(self):
        return self.testScene;



  
