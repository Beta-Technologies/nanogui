#ifdef NANOGUI_PYTHON

#include "python.h"

DECLARE_WIDGET(MotorWheel);
DECLARE_WIDGET(MotorQuad);
DECLARE_WIDGET(ToggleSwitch);
DECLARE_WIDGET(ColorBar);
DECLARE_WIDGET(Led);
DECLARE_WIDGET(Plot);
DECLARE_WIDGET(RpyWidget);
DECLARE_WIDGET(InputQuad);

void register_beta(py::module &m) {
	py::class_<MotorWheel, Widget, ref<MotorWheel>, PyMotorWheel>(m, "MotorWheel", D(MotorWheel))
		.def(py::init<Widget *>(), py::arg("parent"), D(MotorWheel, MotorWheel))
		.def(py::init<Widget *, const Color &>(), py::arg("parent"), py::arg("Color"))
		.def("color", &MotorWheel::color, D(MotorWheel, color))
		.def("setColor", &MotorWheel::setColor, D(MotorWheel, setColor))
		.def("value", &MotorWheel::value, D(MotorWheel, value))
		.def("setValue", &MotorWheel::setValue, D(MotorWheel, setValue))
		.def("callback", &MotorWheel::callback, D(MotorWheel, callback))
		.def("setCallback", &MotorWheel::setCallback, D(MotorWheel, setCallback));

    py::class_<MotorQuad, Widget, ref<MotorQuad>, PyMotorQuad>(m, "MotorQuad", D(MotorQuad))
        .def(py::init<Widget *>(), py::arg("parent"), D(MotorQuad, MotorQuad))
        .def(py::init<Widget *, const Color &>(), py::arg("parent"), py::arg("Color"))
        .def("color", &MotorQuad::color, D(MotorQuad, color))
        .def("setColor", &MotorQuad::setColor, D(MotorQuad, setColor))
        .def("value", &MotorQuad::value, D(MotorQuad, value))
        .def("setValue", &MotorQuad::setValue, D(MotorQuad, setValue))        
        .def("callback", &MotorQuad::callback, D(MotorQuad, callback))
        .def("setCallback", &MotorQuad::setCallback, D(MotorQuad, setCallback));

    py::class_<ToggleSwitch, Widget, ref<ToggleSwitch>, PyToggleSwitch>(m, "ToggleSwitch", D(ToggleSwitch))  
        .def(py::init<Widget *>(), py::arg("parent"),
             D(ToggleSwitch, ToggleSwitch))
        .def(py::init<Widget *, const std::function<void(bool)>&>(),
             py::arg("parent"), py::arg("callback"),
             D(ToggleSwitch, ToggleSwitch))
        .def("checked", &ToggleSwitch::checked, D(ToggleSwitch, checked))
        .def("setChecked", &ToggleSwitch::setChecked, D(ToggleSwitch, setChecked))
        .def("pushed", &ToggleSwitch::pushed, D(ToggleSwitch, pushed))
        .def("setPushed", &ToggleSwitch::setPushed, D(ToggleSwitch, setPushed))
        .def("callback", &ToggleSwitch::callback, D(ToggleSwitch, callback))
        .def("setCallback", &ToggleSwitch::setCallback, D(ToggleSwitch, setCallback));

    py::class_<ColorBar, Widget, ref<ColorBar>, PyColorBar>(m, "ColorBar", D(ColorBar))
        .def(py::init<Widget *>(), py::arg("parent"), D(ColorBar, ColorBar))
        .def("value", &ColorBar::value, D(ColorBar, value))
        .def("setValue", &ColorBar::setValue, D(ColorBar, setValue))
        .def("color", &ColorBar::color, D(ColorBar, color))
        .def("setColor", &ColorBar::setColor, D(ColorBar, setColor)); 

    py::class_<Led, Widget, ref<Led>, PyLed>(m, "Led", D(Led))
        .def(py::init<Widget *>(), py::arg("parent"), D(Led, Led))
        .def("isOn", &Led::isOn, D(Led, isOn))
        .def("setOn", &Led::setOn, D(Led, setOn))
        .def("color", &Led::color, D(Led, color))
        .def("setColor", &Led::setColor, D(Led, setColor));

    py::class_<Plot, Widget, ref<Plot>, PyPlot>(m, "Plot", D(Plot))
        .def(py::init<Widget *, const std::string &>(), py::arg("parent"),
             py::arg("caption") = std::string(""), D(Plot, Plot))
        .def("caption", &Plot::caption, D(Plot, caption))
        .def("setCaption", &Plot::setCaption, D(Plot, setCaption))
        .def("header", &Plot::header, D(Plot, header))
        .def("setHeader", &Plot::setHeader, D(Plot, setHeader))
        .def("footer", &Plot::footer, D(Plot, footer))
        .def("setFooter", &Plot::setFooter, D(Plot, setFooter))
        .def("backgroundColor", &Plot::backgroundColor, D(Plot, backgroundColor))
        .def("setBackgroundColor", &Plot::setBackgroundColor, D(Plot, setBackgroundColor))
        .def("foregroundColor", &Plot::foregroundColor, D(Plot, foregroundColor))
        .def("setForegroundColor", &Plot::setForegroundColor, D(Plot, setForegroundColor))
        .def("textColor", &Plot::textColor, D(Plot, textColor))
        .def("setTextColor", &Plot::setTextColor, D(Plot, setTextColor))        
        .def("addValue", &Plot::addValue, D(Plot, addValue))
        .def("setLabel", &Plot::setLabel, D(Plot, setLabel))
        .def("setAxisTicks", &Plot::setAxisTicks, D(Plot, setAxisTicks))
        .def("setYRange", &Plot::setYRange, D(Plot, setYRange))
        .def("setXTimeScale", &Plot::setXTimeScale, D(Plot, setXTimeScale));

    py::class_<RpyWidget, Widget, ref<RpyWidget>, PyRpyWidget>(m, "RpyWidget", D(RpyWidget))
        .def(py::init<Widget *>(), py::arg("parent"), D(RpyWidget, RpyWidget))
        .def(py::init<Widget *, const Color &>(), py::arg("parent"), py::arg("Color"))
        .def("mode", &RpyWidget::mode, D(RpyWidget, mode))
        .def("setMode", &RpyWidget::setMode, D(RpyWidget, setMode))        
        .def("color", &RpyWidget::color, D(RpyWidget, color))
        .def("setColor", &RpyWidget::setColor, D(RpyWidget, setColor))
        .def("angle", &RpyWidget::angle, D(RpyWidget, angle))
        .def("setAngle", &RpyWidget::setAngle, D(RpyWidget, setAngle))        
        .def("callback", &RpyWidget::callback, D(RpyWidget, callback))
        .def("setCallback", &RpyWidget::setCallback, D(RpyWidget, setCallback));

    py::class_<InputQuad, Widget, ref<InputQuad>, PyInputQuad>(m, "InputQuad", D(InputQuad))
        .def(py::init<Widget *>(), py::arg("parent"), D(InputQuad, InputQuad))
        .def(py::init<Widget *, const Color &>(), py::arg("parent"), py::arg("Color"))
        .def(py::init<Widget *, const Color &, bool>(), py::arg("parent"), py::arg("Color"), py::arg("levels"))
        .def("color", &InputQuad::color, D(InputQuad, color))
        .def("setColor", &InputQuad::setColor, D(InputQuad, setColor))
        .def("getInputValue", &InputQuad::getInputValue, D(InputQuad, getValue))
        .def("setInputValue", &InputQuad::setInputValue, D(InputQuad, setValue))
        .def("getTorqueValue", &InputQuad::getTorqueValue, D(InputQuad, getValue))
        .def("setTorqueValue", &InputQuad::setTorqueValue, D(InputQuad, setValue))        
        .def("callback", &InputQuad::callback, D(InputQuad, callback))
        .def("setCallback", &InputQuad::setCallback, D(InputQuad, setCallback));
}

#endif
