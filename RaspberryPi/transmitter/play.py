from transmitter.scene import Scene
from transmitter.doll import Doll
# takes in data about the motion detected and returns a scene which
# contains thes the addresses and commands to send out to dolls
class Play:
    def __init__(self, radio):
        self.nrf = radio
        
        self.actors = []

        self.actors.append( Doll(self.nrf,"00001") )  # Red eyes
        self.actors.append( Doll(self.nrf,"00002") )  # Red eyes

        self.scenes = []

        # Single glowing eyes for 30 seconds
        tempScene = Scene()
        tempScene.addPart(self.actors[0],"FADE")
        tempScene.addPart(self.actors[1],"FADE")
        tempScene.addMusic("doll_quotes/laughing_1.mp3")

        self.scenes.append (tempScene)
        
    def getScene(self, wideBlocks, tallBlocks):
        return self.scenes[0];



  
