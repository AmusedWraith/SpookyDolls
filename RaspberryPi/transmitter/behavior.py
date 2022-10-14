
class DollBehavior:
    def __init__(self, doll, command):
        self.doll = doll;
        self.commandString = command;

    def doBehavior(self):
        self.doll.sendBehavior(self.commandString);

   