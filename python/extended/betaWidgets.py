import nanogui
from nanogui import *
import random
import math


class ThemeColors():
    # theme colors (could be added to Theme.cpp)
    redErrorColor = Color(1.0, 0.368, 0.368, 1.0)
    orangeWarningColor = Color(1.0, 0.66, 0.22, 1.0)
    yellowAlertColor = Color(0.92, 0.92, 0.49, 1.0)
    greenOKColor = Color(0.50, 0.93, 0.52, 1.0)
    slateDefaultColor = Color(0.18, 0.28, 0.36, 1.0)
    darkWindowColor = Color(0.055, 0.089, 0.11, 1.0)
    focusColor = Color(0.50, 0.93, 0.07, 1.0)


# ---- IMU Sensor output Pitch, Roll, Yaw: angle and rate
class ImuSensor(Window):
    imu_pitch_angle = 10.0
    imu_pitch_rate = 11.0
    imu_roll_angle = 20.0
    imu_roll_rate = 21.0
    imu_yaw_angle = 30.0
    imu_yaw_rate = 31.0

    def __init__(self, parent):
        super(ImuSensor, self).__init__(parent)
        self.setTitle("IMU Sensor")
        self.setFixedSize((200, 200))
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
        self.pitch_angle = TextBox(self)
        self.pitch_angle.setValue(str(self.imu_pitch_angle))
        self.pitch_rate = TextBox(self)
        self.pitch_rate.setValue(str(self.imu_pitch_rate))

        # row 2
        Label(self, "Roll")
        self.roll_angle = TextBox(self)
        self.roll_angle.setValue(str(self.imu_roll_angle))
        self.roll_rate = TextBox(self)
        self.roll_rate.setValue(str(self.imu_roll_rate))

        # row 3
        Label(self, "Yaw")
        self.yaw_angle = TextBox(self)
        self.yaw_angle.setValue(str(self.imu_yaw_angle))
        self.yaw_rate = TextBox(self)
        self.yaw_rate.setValue(str(self.imu_yaw_rate))

    def set_imu_vals(self, roll, pitch, yaw):
        self.imu_roll_angle, self.imu_roll_rate = int(roll[0]), int(roll[1])
        self.imu_pitch_angle, self.imu_pitch_rate = int(pitch[0]), int(pitch[1])
        self.imu_yaw_angle, self.imu_yaw_rate = int(yaw[0]), int(yaw[1])

        self.update()

    def update(self):
        self.pitch_angle.setValue(str(self.imu_pitch_angle))
        self.pitch_rate.setValue(str(self.imu_pitch_rate))
        self.roll_angle.setValue(str(self.imu_roll_angle))
        self.roll_rate.setValue(str(self.imu_roll_rate))
        self.yaw_angle.setValue(str(self.imu_yaw_angle))
        self.yaw_rate.setValue(str(self.imu_yaw_rate))


class PIDErrors(Window):
    error_pitch_angle = 0
    error_pitch_rate = 0
    error_roll_angle = 0
    error_roll_rate = 0
    error_yaw_angle = 0
    error_yaw_rate = 0

    def __init__(self, parent):
        super(PIDErrors, self).__init__(parent)
        self.setTitle("PID Errors")
        self.setFixedSize((420, 200))
        layout = GridLayout(Orientation.Horizontal, 3,
                            Alignment.Middle, 15, 0)
        layout.setSpacing(0, 0)
        self.setLayout(layout)

        # row 1
        Label(self, "")
        Label(self, "Angle")
        Label(self, "Rate")

        # row 1
        Label(self, "Pitch")
        self.pitch_angle = TextBox(self)
        self.pitch_angle.setValue(str(self.error_pitch_angle))
        self.pitch_angle.setFixedSize((120, 30))
        self.pitch_rate = TextBox(self)
        self.pitch_rate.setValue(str(self.error_pitch_rate))
        self.pitch_rate.setFixedSize((120, 30))

        # row 2
        Label(self, "Roll")
        self.roll_angle = TextBox(self)
        self.roll_angle.setValue(str(self.error_roll_angle))
        self.roll_angle.setFixedSize((120, 30))
        self.roll_rate = TextBox(self)
        self.roll_rate.setValue(str(self.error_roll_rate))
        self.roll_rate.setFixedSize((120, 30))

        # row 3
        Label(self, "Yaw")
        self.yaw_angle = TextBox(self)
        self.yaw_angle.setValue(str(self.error_yaw_angle))
        self.yaw_angle.setFixedSize((120, 30))
        self.yaw_rate = TextBox(self)
        self.yaw_rate.setValue(str(self.error_yaw_rate))
        self.yaw_rate.setFixedSize((120, 30))

    def set_pid_error_vals(self, roll, pitch, yaw):
        self.error_roll_angle, self.error_roll_rate = roll[0], roll[1]
        self.error_pitch_angle, self.error_pitch_rate = pitch[0], pitch[1]
        self.error_yaw_angle, self.error_yaw_rate = yaw[0], yaw[1]

        self.update()

    def update(self):
        self.pitch_angle.setValue(str(round(self.error_pitch_angle, 2)))
        self.pitch_rate.setValue(str(round(self.error_pitch_rate, 2)))
        self.roll_angle.setValue(str(round(self.error_roll_angle, 2)))
        self.roll_rate.setValue(str(round(self.error_roll_rate, 2)))
        self.yaw_angle.setValue(str(round(self.error_yaw_angle, 2)))
        self.yaw_rate.setValue(str(round(self.error_yaw_rate, 2)))


# ---- ECU Stick Input (Pitch, Roll, Yaw rate
class EcuStickInput(Window):
    ecu_pitch = 25.62
    ecu_roll = 24.97
    ecu_yaw = 25.24
    ecu_throttle = 0.64

    ECU_PITCH_SCALE = 32767.0
    ECU_ROLL_SCALE = 32767.0
    ECU_YAW_SCALE = 32767.0
    ECU_THROTTLE_SCALE = 65535.0

    def __init__(self, parent):
        super(EcuStickInput, self).__init__(parent)
        self.setTitle("ECU Inputs")
        self.setFixedSize((200, 220))
        self.setLayout(BoxLayout(Orientation.Vertical, Alignment.Minimum, 0, 5))

        panel = Widget(self)
        layout = GridLayout(Orientation.Horizontal, 2,
                            Alignment.Middle, 15, 0)
        layout.setSpacing(0, 10)
        panel.setLayout(layout)

        Label(panel, "Pitch")
        self.txtboxPitch = TextBox(panel)

        self.pitch_slider = Slider(panel)
        self.pitch_slider.setValue(0.5)
        self.pitch_slider.setFixedWidth(100)
        Label(panel, "")

        Label(panel, "Roll")
        self.txtboxRoll = TextBox(panel)

        self.roll_slider = Slider(panel)
        self.roll_slider.setValue(0.5)
        self.roll_slider.setFixedWidth(100)
        Label(panel, "")

        Label(panel, "Yaw")
        self.txtboxYaw = TextBox(panel)

        self.yaw_slider = Slider(panel)
        self.yaw_slider.setValue(0.5)
        self.yaw_slider.setFixedWidth(100)
        Label(panel, "")

        Label(panel, "Throttle")
        self.txtboxThrottle = TextBox(panel)

        self.update()

    def set_ecu_vals(self, roll, pitch, yaw, throttle):
        # self.ecu_roll = int((roll / self.ECU_ROLL_SCALE) * 100)
        # self.ecu_pitch = int((pitch / self.ECU_PITCH_SCALE) * 100)
        # self.ecu_yaw = int((yaw / self.ECU_YAW_SCALE) * 100)
        self.ecu_roll = roll
        self.ecu_pitch = pitch
        self.ecu_yaw = yaw
        self.ecu_throttle = int((throttle / self.ECU_THROTTLE_SCALE) * 100)
        self.update()

    def update(self):
        self.txtboxPitch.setValue(str(int((self.ecu_pitch / self.ECU_PITCH_SCALE) * 100)))
        self.pitch_slider.setValue((self.ecu_pitch + self.ECU_PITCH_SCALE) / (self.ECU_PITCH_SCALE * 2))
        self.txtboxRoll.setValue(str(int((self.ecu_roll / self.ECU_ROLL_SCALE) * 100)))
        self.roll_slider.setValue((self.ecu_roll + self.ECU_ROLL_SCALE) / (self.ECU_ROLL_SCALE * 2))
        self.txtboxYaw.setValue(str(int((self.ecu_yaw / self.ECU_YAW_SCALE) * 100)))
        self.yaw_slider.setValue((self.ecu_yaw + self.ECU_YAW_SCALE) / (self.ECU_YAW_SCALE * 2))
        self.txtboxThrottle.setValue(str(self.ecu_throttle))


# ---- Sensor Fault Display (Triple Sensor Voting)
class SensorFaultPanel(Window):
    prop_spin_sensor_value = False

    def __init__(self, parent):
        super(SensorFaultPanel, self).__init__(parent)
        self.setTitle("Sensors")

        layout = BoxLayout(Orientation.Horizontal, Alignment.Middle, 5, 5)
        self.setLayout(layout)

        panel = Widget(self)
        layout = GridLayout(Orientation.Horizontal, 4,
                            Alignment.Middle, 15, 5)
        layout.setSpacing(0, 10)
        panel.setLayout(layout)

        items = 9

        rows = math.ceil(items / 2)

        item_index = 0
        for index in range(rows):
            Label(panel, "Sensor " + str(item_index + 1))
            Led(panel).setColor(ThemeColors.greenOKColor)
            item_index += 1
            Led(panel).setColor(ThemeColors.redErrorColor)
            Label(panel, "Sensor " + str(item_index + 1))
            item_index += 1

        # Label(panel, "Prop Spin Enabled")
        # self.prop_spin_sensor = Led(panel)
        # self.prop_spin_sensor.setColor(ThemeColors.redErrorColor if not self.prop_spin_sensor_value else ThemeColors.greenOKColor)
        # self.prop_spin_sensor.setColor(ThemeColors.greenOKColor)
        # self.prop_spin_sensor.setOn(self.prop_spin_sensor_value)

        # Led(panel).setColor(ThemeColors.greenOKColor)
        # Label(panel, "Prop Spin Enabled")

    # def init_panel(self, sensors):
    #
    #     for i, sensor in enumerate(sensors):
    #         Label(panel, "Sensor " + str(i))
    #
    #         for j in range(2):
    #             fault = random.randint(0,10) == 1
    #             color = ThemeColors.redErrorColor if fault else ThemeColors.greenOKColor
    #             led = Led(panel)
    #             led.setColor(color)
    #             led.setOn(True)
    #
    #         Label(panel, "Sensor")

    def set_prop_spin_value(self, prop_spin):
        self.prop_spin_sensor_value = prop_spin
        self.update()

    def update(self):
        self.prop_spin_sensor.setOn(self.prop_spin_sensor_value)


# ---- Battery energy and signal level display
class BatterySignalPanel(Window):
    MAX_BATTERY_VOLTAGE = 800.0
    batteryLevel_1 = 0.56
    batteryLevel_2 = 0.56
    signalLevel = 0.47

    def __init__(self, parent):
        super(BatterySignalPanel, self).__init__(parent)
        self.setTitle("Battery")
        self.setFixedSize((200, 200))

        layout = BoxLayout(Orientation.Vertical, Alignment.Middle, 5, 5)
        layout.setSpacing(10)
        self.setLayout(layout)

        batterylabel_1 = Label(self, "Battery Bus 1")
        self.battery_1 = ColorBar(self)
        self.battery_1.setWidth(200)
        self.battery_1.setValue(self.batteryLevel_2)

        batterylabel_2 = Label(self, "Battery Bus 2")
        self.battery_2 = ColorBar(self)
        self.battery_2.setWidth(200)
        self.battery_2.setValue(self.batteryLevel_2)

        # self.signalLabel = Label(self, "Radio Signal " + str(self.signalLevel*100) + "%" )
        # self.signal = ColorBar(self)
        # self.signal.setColor(Color(0.0, 1.0, 0.0, 1.0), 3)
        # self.signal.setWidth(180)
        # self.signal.setValue(self.signalLevel);

        # this does not really belong here
        self.exitButton = Button(self, "Exit")

        def cb2():
            # parent.data_running = False
            parent.setVisible(False)

        self.exitButton.setCallback(cb2)

    def setBatteryLevel(self, bl, b2):
        self.batteryLevel_1 = bl / self.MAX_BATTERY_VOLTAGE
        self.batteryLevel_2 = b2 / self.MAX_BATTERY_VOLTAGE
        self.update()

    # def setSignalLevel(self, sl):
    #     self.signalLevel = sl
    #     self.update()

    def update(self):
        self.battery_1.setValue(self.batteryLevel_1)
        self.battery_2.setValue(self.batteryLevel_2)
        # self.signal.setValue(self.signalLevel)


class TogglePanel(Window):

    def __init__(self, parent, title, label):
        super(TogglePanel, self).__init__(parent)
        self.setTitle(title)
        self.setFixedSize((125, 125))

        layout = BoxLayout(Orientation.Vertical, Alignment.Middle, 5, 5)
        layout.setSpacing(10)
        self.setLayout(layout)

        self.toggle_label = Label(self, label)

        self.toggle_logging_switch = ToggleSwitch(self)


class HoverMotorPanel(Window):
    motorVal = [0.1, 0.3, 0.7, 0.4]
    motorLabels = ["A", "B", "C", "D"]
    MAX_RPM = 7000.0

    def __init__(self, parent):
        super(HoverMotorPanel, self).__init__(parent)
        # self.window = Window(parent, "Hover Motors")
        self.setTitle("Hover Motors")
        self.setFixedSize((200, 200))

        # panel = self.buttonPanel()
        # toolButton = ToolButton(panel, 0, "x")
        # toolButton.setBackgroundColor(Color(1,0,0,1))

        rotorColor = ThemeColors.greenOKColor

        self.motorWidget = MotorQuad(self)
        self.motorWidget.setColor(rotorColor)

        self.motorWidget.setPosition((55, 65))

        # grid 4 positions
        xposn = (20, 120)
        yposn = (40, 160)

        self.textTorq = []
        for i in range(4):
            self.textTorq.append(TextBox(self))
            self.textTorq[i].setPosition((xposn[int(i % 2)], yposn[int(i / 2)]))

        self.update()

    def setMotorVals(self, v0, v1, v2, v3):
        self.motorVal[0] = v0
        self.motorVal[1] = v1
        self.motorVal[2] = v2
        self.motorVal[3] = v3
        self.update()

    def getMotorVals(self):
        return self.motorVal

    def update(self):
        for i in range(4):
            self.motorWidget.setValue(self.motorVal[i] * 0.01, i)
        self.textTorq[0].setValue(str(round(self.motorVal[1], 2)))
        self.textTorq[1].setValue(str(round(self.motorVal[0], 2)))
        self.textTorq[2].setValue(str(round(self.motorVal[2], 2)))
        self.textTorq[3].setValue(str(round(self.motorVal[3], 2)))


class PushMotorPanel(Window):
    torque = 5500
    MAX_RPM = 7000.0

    def __init__(self, parent):
        super(PushMotorPanel, self).__init__(parent)
        self.setTitle("Push Motor")
        self.setFixedSize((200, 200))

        layout = BoxLayout(Orientation.Vertical, Alignment.Middle, 5, 5)
        self.setLayout(layout)

        self.pushMotor = MotorWheel(self)
        self.pushMotorTorque = TextBox(self)
        self.pushMotor.setColor(ThemeColors.greenOKColor)

        self.setValue(0.5)

    def setValue(self, val):
        self.torque = val
        self.pushMotor.setValue(self.torque / self.MAX_RPM)
        self.pushMotorTorque.setValue(str(self.torque))


class AirspeedSensor(Window):
    airspeed_pressure = .5
    MIN_PRESSURE = -145.0
    MAX_PRESSURE = 145.0

    def __init__(self, parent):
        super(AirspeedSensor, self).__init__(parent)
        self.setTitle("Pressure Sensor")
        self.setFixedSize((200, 120))
        layout = GridLayout(Orientation.Horizontal, 1,
                            Alignment.Middle, 5, 5)
        self.setLayout(layout)

        # row 2
        self.airspeed_pressure_display = TextBox(self)
        self.airspeed_pressure_display.setFixedSize((100, 30))
        self.airspeed_pressure_display.setUnits('Pa')
        self.airspeed_pressure_display.setValue(str(self.airspeed_pressure))

        self.airspeed_pressure_bar = ColorBar(self)
        # self.airspeed_pressure_bar.setWidth(50)
        self.airspeed_pressure_bar.setValue(self.airspeed_pressure)

    def set_airspeed_vals(self, airspeed_pressure):
        self.airspeed_pressure = airspeed_pressure
        self.update()

    def update(self):
        self.airspeed_pressure_display.setValue(str(round(self.airspeed_pressure, 2)))
        # Normalizes -145 to 145 between 0 and 1
        # self.airspeed_pressure_bar.setValue((self.airspeed_pressure - self.MIN_PRESSURE) / (self.MAX_PRESSURE - self.MIN_PRESSURE))
        # Takes the absolute value of the value and displays it, normalizing 0 to 145 between 0 and 1
        self.airspeed_pressure_bar.setValue(abs(self.airspeed_pressure) / self.MAX_PRESSURE)


class MotorPlot(Window):
    data = []

    def __init__(self, parent):
        super(MotorPlot, self).__init__(parent)

        self.plot = Plot(self)
        self.plot.setPosition((0, 30))
        self.plot.setHeader("Motor Torque Plot")
        self.plot.setFooter("time")
        self.plot.setForegroundColor(ThemeColors.greenOKColor)
        self.plot.setFixedSize((600, 120))
        self.plot.setXTimeScale(10)

        self.plot.setLabel("torq-1", Color(255, 0, 0, 255), 0)
        self.plot.setLabel("torq-2", Color(0, 255, 0, 255), 1)
        self.plot.setLabel("torq-3", Color(100, 100, 255, 255), 2)
        self.plot.setLabel("torq-4", Color(255, 255, 255, 255), 3)

        self.plot.setAxisTicks(1000, 100)

        self.plot.setYRange(-1.0, 1.0)

        for i in range(4):
            self.data.append([])

    def setValues(self, val, index):
        self.data[index] = val
        self.update()

    def setFixedSize(self, wh):
        print("plot fixed size")
        super(MotorPlot, self).setFixedSize(wh)
        self.plot.setFixedSize((wh[0], 0.8 * wh[1]))

    # def setCaption(self, text):
    #     self.plot.setFooter(text)

    def update(self):
        for i in range(4):
            self.plot.setValues(self.data[i], i)
