/*
    src/motorwheel.cpp -- Draw a circle with radius factor from 0.0 to 1.0
                          Has positive and negative color (green, red)
*/

#include <nanogui/extended/motorwheel.h>
#include <nanogui/theme.h>
#include <nanogui/opengl.h>
#include <nanogui/serializer/core.h>
//#include <Eigen/QR>
//#include <Eigen/Geometry>

NAMESPACE_BEGIN(nanogui)

MotorWheel::MotorWheel(Widget *parent, const Color& rgb)
    : Widget(parent), mValue(0.0f) {
    setColor(rgb);
    mOuterColor = Color(80,80,80, 255);
}

Vector2i MotorWheel::preferredSize(NVGcontext *) const {
    return { 100, 100. };
}

void MotorWheel::draw(NVGcontext *ctx) {
    Widget::draw(ctx);

    if (!mVisible)
        return;

    float x = mPos.x(),
          y = mPos.y(),
          w = mSize.x(),
          h = mSize.y();

    NVGcontext* vg = ctx;

    float r0, r1, cx, cy;
    //NVGpaint paint;

    nvgSave(vg);

    cx = x + w*0.5f;
    cy = y + h*0.5f;
    r1 = (w < h ? w : h) * 0.5f - 5.0f;
    r0 = r1 * .75f;

    //outer ring at 1.0
    nvgBeginPath(vg);
    nvgCircle(vg, cx, cy, r1+0.5f);
    nvgStrokeColor(vg, mOuterColor);
    nvgStrokeWidth(vg, 2.0f);
    nvgStroke(vg);    

    //inner circle : radius is based on value 0.0 .. 1.0f
    nvgBeginPath(vg);
    //nvgCircle(vg, cx, cy, r0-0.5f);
    nvgCircle(vg, cx, cy, r1 * mValue);    
    nvgFillColor(vg, mColor);
    nvgFill(vg);

    nvgRestore(vg);
}

Color MotorWheel::color() const {
    return mColor;
}

void MotorWheel::setColor(const Color &rgb) {
    mColor = rgb;
}

float MotorWheel::value() const {
 return mValue;
}

void MotorWheel::setValue(float v) {
    mValue = v;
}

void MotorWheel::save(Serializer &s) const {
    Widget::save(s);
    s.set("color", mColor);
}

bool MotorWheel::load(Serializer &s) {
    if (!Widget::load(s)) return false;
    if (!s.get("color", mColor)) return false;
    return true;
}

NAMESPACE_END(nanogui)

