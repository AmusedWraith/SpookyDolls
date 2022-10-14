import pygame
from transmitter.behavior import DollBehavior

# holds the dolls and other behaviors for a given scene

class Scene:
    def __init__(self):
        self.parts = [];
        self.music = "";

    def addPart(self, dollInfo, commandString):
        tempPart = DollBehavior(dollInfo, commandString)
        self.parts.append(tempPart)
        
    def addMusic(self, musicFileName):
        self.music = musicFileName;
        
    def playScene(self):
        for part in self.parts:
            part.doBehavior();
        
        if self.music != "":
            pygame.mixer.init()
            pygame.mixer.music.load(self.music)
            pygame.mixer.music.play()
            while pygame.mixer.music.get_busy() == True:
                continue
            
