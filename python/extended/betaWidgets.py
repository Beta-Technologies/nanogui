# Beta UI Widgets
# (c) 2019 Beta Technologies
# written by Jeff Sprenger

# These widgets are used to display flight data from scale model and full-scale Alia 250.

import nanogui
from nanogui import *
import random

class ThemeColors():
    #theme colors (could be added to Theme.cpp)
    redErrorColor = Color(1.0, 0.368, 0.368, 1.0)
    orangeWarningColor = Color(1.0, 0.66, 0.22, 1.0)
    yellowAlertColor = Color(0.92, 0.92 , 0.49, 1.0)
    greenOKColor = Color(0.50, 0.93 , 0.52, 1.0)
    slateDefaultColor = Color(0.18, 0.28, 0.36, 1.0)
    darkWindowColor = Color(0.055, 0.089, 0.11, 1.0)
    focusColor = Color(0.50, 0.93 , 0.07, 1.0)    

#---- IMU Sensor output Pitch, Roll, Yaw: angle and rate 

class ImuSensor(Window):
    imu_pitch_angle = 10.0
    imu_pitch_rate  = 11.0
    imu_roll_angle  = 20.0
    imu_roll_rate   = 21.0
    imu_yaw_angle   = 30.0
    imu_yaw_rate    = 31.0

    def __init__(self, parent):
        super(ImuSensor, self).__init__(parent)          
        self.setTitle("IMU Sensor")        
        self.setSize((400,300))
        layout = GridLayout(Orientation.Horizontal, 3,
                            Alignment.Middle, 15, 0)
        layout.setSpacing(0, 10)
        self.setLayout(layout)

        # row 1
        Label(self, "")
        Label(self, "Angle")
        Label(self, "Rate")

        # row 1
        Label(self, "Pitch")
        txtbox = TextBox(self).setValue(str(self.imu_pitch_angle))
        txtbox = TextBox(self).setValue(str(self.imu_pitch_rate))

        # row 2
        Label(self, "Roll")
        txtbox = TextBox(self).setValue(str(self.imu_roll_angle))
        txtbox = TextBox(self).setValue(str(self.imu_roll_rate))

        # row 3
        Label(self, "Yaw Rate")
        txtbox = TextBox(self).setValue(str(self.imu_yaw_angle))
        txtbox = TextBox(self).setValue(str(self.imu_yaw_rate))


#---- ECU Stick Input (Pitch, Roll, Yaw rate    

class EcuStickInput(Window):
    ecu_pitch  = 25.62
    ecu_roll   = 24.97 
    ecu_yaw    = 25.24
    ecu_throttle = 0.64

    def __init__(self, parent):
        super(EcuStickInput, self).__init__(parent)         
        self.setTitle("ECU Inputs") 
        self.setSize((400,300))               
        self.setLayout(BoxLayout(Orientation.Vertical, Alignment.Minimum, 0, 5))

        panel = Widget(self)
        layout = GridLayout(Orientation.Horizontal, 2,
                            Alignment.Middle, 15, 0)
        layout.setSpacing(0, 10)
        panel.setLayout(layout)        

        Label(panel, "Pitch")
        self.txtboxPitch = TextBox(panel)

        Label(panel, "Roll")
        self.txtboxRoll = TextBox(panel)

        Label(panel, "Yaw Rate")
        self.txtboxYaw = TextBox(panel)

        Label(panel, "Throttle")
        self.txtboxThrottle = TextBox(panel)

        self.update()

    def update(self):
        self.txtboxPitch.setValue(str(self.ecu_pitch))
        self.txtboxRoll.setValue(str(self.ecu_roll))
        self.txtboxYaw .setValue(str(self.ecu_yaw))
        self.txtboxThrottle.setValue(str(self.ecu_throttle))

#---- Sensor Fault Display (Triple Sensor Voting)

class SensorFaultPanel(Window):

    def __init__(self, parent):
        super(SensorFaultPanel, self).__init__(parent)          
        self.setTitle("Sensor Faults")
 
        layout = BoxLayout(Orientation.Horizontal, Alignment.Middle, 5, 5)
        self.setLayout(layout)

        panel = Widget(self)
        layout = GridLayout(Orientation.Horizontal, 4,
                            Alignment.Middle, 15, 5)
        layout.setSpacing(0, 10)
        panel.setLayout(layout)

        for i in range(10):
            Label(panel, "Sensor " + str(i))

            for j in range(3):
                fault = random.randint(0,10) == 1
                color = ThemeColors.redErrorColor if fault else ThemeColors.greenOKColor
                led = Led(panel);
                led.setColor(color)
                led.setOn(True)

#---- Battery energy and signal level display
class BatterySignalPanel(Window):
    batteryLevel = 0.56
    signalLevel = 0.47

    def __init__(self, parent):
        super(BatterySignalPanel, self).__init__(parent)           
        self.setTitle("Battery & Signal")
        self.setFixedSize((200, 200))
       
        layout = BoxLayout(Orientation.Vertical, Alignment.Middle, 5, 5)
        layout.setSpacing(10)
        self.setLayout(layout)

        batterylabel = Label(self, "Energy")
    
        self.battery = ColorBar(self)
        self.battery.setWidth(200)
        self.battery.setValue(self.batteryLevel)

        self.signalLabel = Label(self, "Radio Signal " + str(self.signalLevel*100) + "%" )   
        self.signal = ColorBar(self)
        self.signal.setColor(Color(0.0, 1.0, 0.0, 1.0), 3)
        self.signal.setWidth(180)
        self.signal.setValue(self.signalLevel);

        # this does not really belong here
        self.exitButton = Button(self, "Exit")
        def cb2():
            parent.setVisible(False)
        self.exitButton.setCallback(cb2)

    def setBatteryLevel(self, bl):
        self.batteryLevel = bl
        self.update()

    def setSignalLevel(self, sl):
        self.signalLevel = sl
        self.update()

    def update(self):
        self.battery.setValue(self.batteryLevel)
        self.signal.setValue(self.signalLevel);        


#------ Hover Motors Display Panel - displays a quad arrangement
class HoverMotorPanel(Window):
    motorVal = [0.1, 0.3, 0.7, 0.4]
    motorLabels = ["A", "B", "C", "D"]
    MAX_RPM = 4000;

    def __init__(self, parent):
        super(HoverMotorPanel, self).__init__(parent)            
        #self.window = Window(parent, "Hover Motors")
        self.setTitle("Hover Motors")
        self.setFixedSize((210, 200))

        panel = self.buttonPanel();
        toolButton = ToolButton(panel, 0, "x");
        toolButton.setBackgroundColor(Color(1,0,0,1));

        rotorColor = ThemeColors.greenOKColor

        self.motorWidget = MotorQuad(self);
        self.motorWidget.setColor(rotorColor)

        self.motorWidget.setPosition((55, 65))

        # grid 4 positions
        xposn = (20, 120)
        yposn = (40, 160)

        self.textTorq = []
        for i in range(4):
            self.textTorq.append(TextBox(self))
            self.textTorq[i].setPosition((xposn[int(i%2)],yposn[int(i/2)]))

        self.update()

    def setMotorVals(self, v0, v1, v2, v3):
        self.motorVal[0] = v0
        self.motorVal[1] = v1
        self.motorVal[2] = v2
        self.motorVal[3] = v3
        self.update()
         

    def update(self):
        for i in range(4):
            self.motorWidget.setValue(self.motorVal[i], i)     
            self.textTorq[i].setValue(str(self.MAX_RPM*self.motorVal[0]))

class PushMotorPanel(Window):
    torque = 0

    def __init__(self, parent):
        super(PushMotorPanel, self).__init__(parent)        
        self.setTitle("Push Motor")
        self.setFixedSize((210, 180))

        layout = BoxLayout(Orientation.Vertical, Alignment.Middle, 5, 5)
        self.setLayout(layout)

        self.pushMotor = MotorWheel(self)
        self.pushMotorTorque = TextBox(self)
        self.pushMotor.setColor(ThemeColors.greenOKColor)

        self.setValue(0.5)        

    def setValue(self, val):
        self.torque = val
        self.pushMotor.setValue(self.torque)
        self.pushMotorTorque.setValue(str(self.torque*100) + " Nm")


class MotorPlot(Window):
    data = []

    def __init__(self, parent):
        super(MotorPlot, self).__init__(parent)
                              
        self.plot = Plot(self)
        self.plot.setPosition((0,30))
        self.plot.setHeader("Motor Torque Plot")
        self.plot.setFooter("time")
        self.plot.setForegroundColor(ThemeColors.greenOKColor)
        self.plot.setFixedSize((600, 120))
        self.plot.setXTimeScale(10)

        self.plot.setLabel("torq-1", Color(255,  0,  0, 255), 0)
        self.plot.setLabel("torq-2", Color(0  ,255,  0, 255), 1)
        self.plot.setLabel("torq-3", Color(100,100,255, 255), 2)
        self.plot.setLabel("torq-4", Color(255,255,255, 255), 3)

        self.plot.setYRange(-1.0, 1.0);

        for i in range(4):
            self.data.append([])


    def setValues(self, val, index):
        self.data[index] = val
        self.update()

    def setFixedSize(self, wh):
        print ("plot fixed size")
        super(MotorPlot, self).setFixedSize(wh)
        self.plot.setFixedSize((wh[0], 0.8 * wh[1]))

    # def setCaption(self, text):
    #     self.plot.setFooter(text)

    def update(self):
        for i in range(4):
            self.plot.setValues(self.data[i], i)


#--- Under-developed UI widgets
        # fsize = 20
        # Label(panel, "Distance").setFontSize(fsize)
        # distanceLabel = Label(panel, "0.317 nm" )
        # distanceLabel.setColor(Color(0.2, 0.8, 0.2, 1.0))
        # distanceLabel.setFontSize(fsize)      
        # deg = unichr(0x00b0)

        # Label(panel, "Direction").setFontSize(fsize)
        # directionLabel = Label(panel, "138" + deg )
        # directionLabel.setColor(Color(0.2, 0.8, 0.2, 1.0))
        # directionLabel.setFontSize(fsize)        

        # Label(panel, "Heading").setFontSize(fsize)
        # headingLabel = Label(panel, "196" + deg )
        # headingLabel.setColor(Color(0.2, 0.8, 0.2, 1.0))         
        # headingLabel.setFontSize(fsize)          