class DR966:
    def __init__(self):
        self.is_on = False

    def turnOn(self):
        if not self.is_on:
            self.is_on = True

    def turnOff(self):
        if self.is_on:
            self.is_on = False

    def getStatus(self):
        return self.is_on