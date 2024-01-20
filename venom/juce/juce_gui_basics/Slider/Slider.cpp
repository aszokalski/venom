#include "Slider.h"
#include <juce_gui_basics/juce_gui_basics.h>

class PySlider : public juce::Slider, juce::Component
{
public:
    /* Inherit the constructors */
    using juce::Slider::Slider;

    explicit PySlider (const juce::String& componentName) : juce::Slider(componentName) {};
    PySlider (juce::Slider::SliderStyle style, juce::Slider::TextEntryBoxPosition textBoxPosition) : juce::Slider(style, textBoxPosition) {};
    
    void setRange(double newMinimum, double newMaximum, double newInterval) {
        PYBIND11_OVERRIDE(
            void,                       /* Return type */
            juce::Slider,       /* Parent class */
            setRange,              /* Name of function in C++ (must match Python name) */
            newMinimum, newMaximum, newInterval
        );
    }

    double getValue() const {
        PYBIND11_OVERRIDE(
            double,                       /* Return type */
            juce::Slider,       /* Parent class */
            getValue,              /* Name of function in C++ (must match Python name) */
        );
    }

    void setSliderStyle (juce::Slider::SliderStyle newStyle) {
        PYBIND11_OVERRIDE(
            void,                       /* Return type */
            juce::Slider,       /* Parent class */
            setSliderStyle,              /* Name of function in C++ (must match Python name) */
            newStyle
        );
    }

    juce::Slider::SliderStyle getSliderStyle() const noexcept {
        PYBIND11_OVERRIDE(
            juce::Slider::SliderStyle,                       /* Return type */
            juce::Slider,       /* Parent class */
            getSliderStyle,              /* Name of function in C++ (must match Python name) */
        );
    }

    void setTextBoxStyle (juce::Slider::TextEntryBoxPosition newPosition,
                          bool isReadOnly,
                          int textEntryBoxWidth,
                          int textEntryBoxHeight) {
        PYBIND11_OVERRIDE(
            void,                       /* Return type */
            juce::Slider,       /* Parent class */
            setTextBoxStyle,              /* Name of function in C++ (must match Python name) */
            newPosition, isReadOnly, textEntryBoxWidth, textEntryBoxHeight
        );
    }

    void setVisible (bool shouldBeVisible) {
        PYBIND11_OVERRIDE(
            void,                       /* Return type */
            juce::Slider,       /* Parent class */
            setVisible,              /* Name of function in C++ (must match Python name) */
            shouldBeVisible
        );
    }

    void setBounds (int x, int y, int w, int h) {
        PYBIND11_OVERRIDE(
            void,                       /* Return type */
            juce::Slider,       /* Parent class */
            setBounds,              /* Name of function in C++ (must match Python name) */
            x, y, w, h
        );
    }

    void setSize (int newWidth, int newHeight) {
        PYBIND11_OVERRIDE(
            void,                       /* Return type */
            juce::Slider,       /* Parent class */
            setSize,              /* Name of function in C++ (must match Python name) */
            newWidth, newHeight
        );
    }
};

void init_Slider(py::module& m) {
        auto slider = py::class_<juce::Slider, PySlider>(m, "Slider", py::dynamic_attr())
        .def(py::init<>())
        .def(py::init([](const juce::String& componentName)
                { return new PySlider(componentName); }))
        .def(py::init([](juce::Slider::SliderStyle style, juce::Slider::TextEntryBoxPosition textBoxPosition)
                { return new PySlider(style, textBoxPosition); }))
        .def("setRange", [](juce::Slider &self, double newMinimum, double newMaximum, double newInterval)
            { self.setRange(newMinimum, newMaximum, newInterval); })
        .def("getValue", [](juce::Slider &self)
            { return self.getValue(); })
        .def("setSliderStyle", [](juce::Slider &self, juce::Slider::SliderStyle newStyle)
            { self.setSliderStyle(newStyle); })
        .def("getSliderStyle", [](juce::Slider &self)
            { return self.getSliderStyle(); })
        .def("setTextBoxStyle", [](juce::Slider &self, juce::Slider::TextEntryBoxPosition newPosition,
                          bool isReadOnly,
                          int textEntryBoxWidth,
                          int textEntryBoxHeight)
            { self.setTextBoxStyle(newPosition, isReadOnly, textEntryBoxWidth, textEntryBoxHeight); })
        .def("setVisible", [](juce::Slider &self, bool shouldBeVisible)
            { self.setVisible(shouldBeVisible); })
        .def("setBounds", [](juce::Slider &self, int x, int y, int w, int h)
            {  self.setBounds(x, y, w, h); })
        .def("setSize", [](juce::Slider &self, int newWidth, int newHeight)
            {  self.setSize(newWidth, newHeight); });
        
        py::enum_<juce::Slider::SliderStyle>(slider, "SliderStyle")
            .value("LinearHorizontal", juce::Slider::SliderStyle::LinearHorizontal)
            .value("LinearVertical", juce::Slider::SliderStyle::LinearVertical)
            .value("LinearBar", juce::Slider::SliderStyle::LinearBar)
            .value("LinearBarVertical", juce::Slider::SliderStyle::LinearBarVertical)
            .value("Rotary", juce::Slider::SliderStyle::Rotary)
            .value("RotaryHorizontalDrag", juce::Slider::SliderStyle::RotaryHorizontalDrag)
            .value("RotaryVerticalDrag", juce::Slider::SliderStyle::RotaryVerticalDrag)
            .value("RotaryHorizontalVerticalDrag", juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag)
            .value("IncDecButtons", juce::Slider::SliderStyle::IncDecButtons)
            .value("TwoValueHorizontal", juce::Slider::SliderStyle::TwoValueHorizontal)
            .value("TwoValueVertical", juce::Slider::SliderStyle::TwoValueVertical)
            .value("ThreeValueHorizontal", juce::Slider::SliderStyle::ThreeValueHorizontal)
            .value("ThreeValueVertical", juce::Slider::SliderStyle::ThreeValueVertical)
            .export_values();
        
        py::enum_<juce::Slider::TextEntryBoxPosition>(slider, "TextEntryBoxPosition")
            .value("NoTextBox", juce::Slider::TextEntryBoxPosition::NoTextBox)
            .value("TextBoxLeft", juce::Slider::TextEntryBoxPosition::TextBoxLeft)
            .value("TextBoxRight", juce::Slider::TextEntryBoxPosition::TextBoxRight)
            .value("TextBoxAbove", juce::Slider::TextEntryBoxPosition::TextBoxAbove)
            .value("TextBoxBelow", juce::Slider::TextEntryBoxPosition::TextBoxBelow)
            .export_values();
}