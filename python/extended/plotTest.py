# Alia Telemetry Python GUI
#
# Example Code
# (c) 2019 Beta Technologies Inc.
#
# written by Jeff Sprenger

import nanogui
from nanogui import *
from betaWidgets import *
import time
import math

class AppUI(Screen):
    count = 0
    exchangeCount = 0

    def __init__(self):
        super(AppUI, self).__init__((800, 300), "Beta CAN Monitor")
        self.setBackground(Color(0,0,0,0));

        self.start_time = time.time()
        #a test to modify the current theme

        theme = self.theme()
        theme.mStandardFontSize = 20

        self.plotwin = MotorPlot(self)
        self.plotwin.setTitle("Torque Plot")
        self.plotwin.setFixedSize((600,150))
        self.plotwin.setPosition((20,20))

        self.plotdata = [];
        for i in range(4):
            self.plotdata.append([]);
            self.plotwin.setValues(self.plotdata[i], i)

        # for i in range(100):
        #     x[i] = 0.5 * (0.5 * math.sin(i / 10.0) + 0.5 * math.cos(i / 23.) + 1);            
        # plotwin.setValues(x);

        self.performLayout()

    def draw(self, ctx):
        self.exchange()
        super(AppUI, self).draw(ctx)

    def addPlotDatum(self, y, index):
        self.plotdata[index].append(y)
        self.plotwin.update()

    def exchange(self):
        self.exchangeCount += 1
        elapsed_time = time.time() - self.start_time
        #self.plotwin.setCaption("t: " + "{:.1f}".format(elapsed_time))

if __name__ == "__main__":
    nanogui.init()
    ui = AppUI()
    ui.drawAll()
    ui.setVisible(True)

    print("Detach UI")
    h = nanogui.mainloop(detach=ui)

    print("Back to Python Context")

    done = False
    while(not done):
        ui.count += 1
        time.sleep(0.01)
        if not nanogui.active():
            break
        if ui.count < 12000:
            x = ui.count
            #y = 0.5 * (0.5 * math.sin(x / 5.0) + 0.5 * math.cos(x / 20.) + 1);
            #ui.addPlotDatum(y,0)

            # y1 = 0.5 * (math.sin(x/11.0) + 1)
            # y2 = 0.3 * (math.sin(x/23.0) + 1)
            # y3 = 0.4 * (math.sin(x/37.0) + 1)
            # y4 = 0.2 * (math.sin(x/53.0) + 1)

            y1 = 1.0 * math.sin(x/11.0)
            y2 = 0.6 * math.sin(x/23.0)
            y3 = 0.8 * math.sin(x/37.0)
            y4 = 0.45 * math.sin(x/53.0) - 0.45

            ui.addPlotDatum(y1, 0)
            ui.addPlotDatum(y2, 1)
            ui.addPlotDatum(y3, 2)
            ui.addPlotDatum(y4, 3)

        else:
            done = True     

    print("Rejoined main")
    h.join()
    nanogui.shutdown()
