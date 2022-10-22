from transmitter.scene import Scene
from transmitter.doll import Doll
# takes in data about the motion detected and returns a scene which
# contains thes the addresses and commands to send out to dolls
class Play:
    def __init__(self, radio):
        self.nrf = radio
        
        self.actors = []

        self.actors.append( Doll(self.nrf,"00001") )  # Red eyes
        self.actors.append( Doll(self.nrf,"00002") )  # blue eyes
        self.actors.append( Doll(self.nrf,"00003") )  # green eyes
        self.actors.append( Doll(self.nrf,"00004") )  # yellow eyes
        self.actors.append( Doll(self.nrf,"00005") )  # red eyes

        self.scenes = []

        # Single glowing eyes for 30 seconds
        tempScene = Scene()
        tempScene.addPart(self.actors[0],"FADE")
        tempScene.addPart(self.actors[1],"FADE")
        tempScene.addPart(self.actors[2],"FADE")
        tempScene.addPart(self.actors[3],"FADE")
        tempScene.addPart(self.actors[4],"FADE")
        tempScene.addMusic("doll_quotes/singing_1.mp3")

        self.scenes.append (tempScene)
        
    def getScene(self, blocks):
        return self.scenes[0];



  
