#ifdef NANOGUI_PYTHON

#include "python.h"

DECLARE_WIDGET(MotorWheel);
DECLARE_WIDGET(MotorQuad);
DECLARE_WIDGET(ToggleSwitch);
DECLARE_WIDGET(ColorBar);
DECLARE_WIDGET(Led);

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

}

#endif
