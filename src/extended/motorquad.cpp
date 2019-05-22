/*
    src/motorquad.cpp -- Draw four arcs to represent the RPM or torque of the motors.
*/

#include <nanogui/extended/motorquad.h>
#include <nanogui/theme.h>
#include <nanogui/opengl.h>
#include <nanogui/serializer/core.h>
//#include <Eigen/QR>
//#include <Eigen/Geometry>

NAMESPACE_BEGIN(nanogui)

MotorQuad::MotorQuad(Widget *parent, const Color& rgb)
    : Widget(parent), mValue(0.0f) {
    setColor(rgb);
    mOuterColor = Color(80,80,80, 255);
}

Vector2i MotorQuad::preferredSize(NVGcontext *) const {
    return { 100, 100. };
}

void MotorQuad::draw(NVGcontext *ctx) {
    Widget::draw(ctx);

    if (!mVisible)
        return;

    float x = mPos.x(),
          y = mPos.y(),
          w = mSize.x(),
          h = mSize.y();

    NVGcontext* vg = ctx;

    float r0, r1, cx, cy;
    cx = x + w*0.5f;
    cy = y + h*0.5f;
    r1 = (w < h ? w : h) * 0.5f - 5.0f;
    r0 = r1 * .75f;

    //there are four values [0..3]
    //we draw a filled arc for each one
    // positions of the motors are:
    // 2 1
    // 3 4

    nvgSave(vg);

    //outer ring at 1.0
    nvgBeginPath(vg);
    nvgCircle(vg, cx, cy, r1+1.5f);
    nvgStrokeColor(vg, mOuterColor);
    nvgStrokeWidth(vg, 2.0f);
    nvgStroke(vg);
    nvgClosePath(vg); 

    //draw the center axes
    nvgBeginPath(vg);
    nvgMoveTo(vg, cx-r1, cy);
    nvgLineTo(vg, cx+r1, cy);
    nvgMoveTo(vg, cx,    cy-r1);    
    nvgLineTo(vg, cx,    cy+r1);
    nvgClosePath(vg);
    nvgStrokeColor(vg, mOuterColor);
    nvgStrokeWidth(vg, 2.0f);
    nvgStroke(vg);       

    // Creates new circle arc shaped sub-path. The arc center is at cx,cy, the arc radius is r,
    // and the arc is drawn from angle a0 to a1, and swept in direction dir (NVG_CCW, or NVG_CW).
    // Angles are specified in radians.
    float angles[] = {0.0f, -90.0f, -180.0f, -270.0f, -360.0f};
    float xdir[] = { 1, -1, -1, 1};
    float ydir[] = {-1, -1,  1, 1};
    float Deg2Rad = 3.14159265359f / 180.0f;
    float sin45 = 0.707;

    //Color innerColor = Color(180, 180, 0, 255);
    //Color innerColor = Color(mColor.x()*0.5, mColor.y()*0.5, mColor.z()*0.5, 255);
    Color innerColor = Color(mColor.r(), mColor.g(), mColor.b(), mColor.w()*0.5);

    for (int i=0; i<4; i++)
    {
        float rad = r1 * mValues[i];
        float sx = cx + xdir[i]*2;
        float sy = cy + ydir[i]*2;

        nvgBeginPath(vg);
        nvgMoveTo(vg, sx, sy);
        //nvgLineTo(vg, sx+ xdir[i]*r1, sy);
        nvgArc(vg,  sx, sy, rad-1, angles[i]*Deg2Rad, angles[i+1]*Deg2Rad, NVG_CCW);
        //nvgLineTo(vg, sx, sy+ ydir[i]*r1);
        nvgClosePath(vg);

        float xOuter = sx+xdir[i]*sin45*rad;
        float yOuter = sy+ydir[i]*sin45*rad;

        NVGpaint paintColor  = nvgLinearGradient(vg, sx, sy, xOuter, yOuter, innerColor, mColor);

        // nvgStrokeColor(vg, mColor);
        // nvgStrokeWidth(vg, 2.0f);
        // nvgStroke(vg);
        //nvgFillColor(vg, mColor);
        //nvgFill(vg);
        nvgFillPaint(vg, paintColor);
        nvgFill(vg);
    }

    nvgRestore(vg);
}

Color MotorQuad::color() const {
    return mColor;
}

void MotorQuad::setColor(const Color &rgb) {
    mColor = rgb;
}

float MotorQuad::value(int idx) const {
    if (idx < 4)
        return mValues[idx];
}

void MotorQuad::setValue(float v, int idx) {
    if (idx < 4)
        mValues[idx] = v;
}

void MotorQuad::save(Serializer &s) const {
    Widget::save(s);
    s.set("color", mColor);
}

bool MotorQuad::load(Serializer &s) {
    if (!Widget::load(s)) return false;
    if (!s.get("color", mColor)) return false;
    return true;
}

NAMESPACE_END(nanogui)

