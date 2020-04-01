/*
    src/inputquad.cpp -- Draw four arcs to represent the RPM or torque of the motors.
*/

#include <nanogui/extended/inputquad.h>
#include <nanogui/theme.h>
#include <nanogui/opengl.h>
#include <nanogui/serializer/core.h>
//#include <Eigen/QR>
//#include <Eigen/Geometry>

NAMESPACE_BEGIN(nanogui)

InputQuad::InputQuad(Widget *parent, const Color& rgb, bool levels)
    : Widget(parent) {
    mDrawLevels = levels;
    setColor(rgb);
    mOuterColor = Color(255,255,255, 255);
}

Vector2i InputQuad::preferredSize(NVGcontext *) const {
    return { 100, 100. };
}

void InputQuad::draw(NVGcontext *ctx) {
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
    r1 = (w < h ? w : h) * 0.4f;

    nvgSave(vg);

    //outer ring at 1.0
    nvgBeginPath(vg);
    nvgCircle(vg, cx, cy, r1);
    nvgClosePath(vg); 
    nvgStrokeColor(vg, mOuterColor);
    nvgStrokeWidth(vg, 3.0f);
    nvgStroke(vg);

    //draw the center axes
    nvgBeginPath(vg);
    nvgMoveTo(vg, cx-r1, cy);
    nvgLineTo(vg, cx+r1, cy);
    nvgMoveTo(vg, cx,    cy-r1);    
    nvgLineTo(vg, cx,    cy+r1);
    nvgClosePath(vg);
    nvgStrokeColor(vg, mOuterColor);
    nvgStrokeWidth(vg, 3.0f);
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
    Color innerColor = Color(mColor.r(), mColor.g(), mColor.b(), mColor.w()*0.3);

    for (int i=0; i<4; i++)
    {
        float rad = r1 * mTorqueValues[i];
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

    if (mDrawLevels) {
        // draw the level markers
        // 25%
        nvgBeginPath(vg);
        nvgCircle(vg, cx, cy, r1*0.25f);
        nvgText(vg, cx + r1*0.25f, cy + (r1*0.02f), "25%", NULL);
        nvgFontSize(vg, 20);
        nvgClosePath(vg); 
        nvgStrokeColor(vg, Color(23, 255, 62, 255));
        nvgStrokeWidth(vg, 3.0f);
        nvgStroke(vg);

        // 50%
        nvgBeginPath(vg);
        nvgCircle(vg, cx, cy, r1*0.5f);
        nvgText(vg, cx + r1*0.5f, cy + (r1*0.02f), "50%", NULL);
        nvgFontSize(vg, 20);
        nvgClosePath(vg); 
        nvgStrokeColor(vg, Color(255, 213, 46, 255));
        nvgStrokeWidth(vg, 3.0f);
        nvgStroke(vg);

        // 75%
        nvgBeginPath(vg);
        nvgCircle(vg, cx, cy, r1*0.75f);
        nvgText(vg, cx + r1*0.75f, cy + (r1*0.02f), "75%", NULL);
        nvgFontSize(vg, 20);
        nvgClosePath(vg); 
        nvgStrokeColor(vg, Color(255, 46, 46, 255));
        nvgStrokeWidth(vg, 3.0f);
        nvgStroke(vg);
    }

    float rollDist = r1 * mRoll;
    float pitchDist = r1 * mPitch;
    float yawDist = r1 * mYaw / 2;

    // draw roll/pitch bubble
    nvgBeginPath(vg);
    nvgCircle(vg, cx+rollDist, cy, r1 * 0.05);
    nvgClosePath(vg);
    nvgFillColor(vg, mColor);
    nvgFill(vg);

    nvgBeginPath(vg);
    nvgCircle(vg, cx, cy+pitchDist, r1 * 0.05);
    nvgClosePath(vg);
    nvgFillColor(vg, mColor);
    nvgFill(vg);

    // draw yaw slider
    nvgBeginPath(vg);
    nvgMoveTo(vg, cx - (r1 / 2), cy - (r1 * 1.2));
    nvgLineTo(vg, cx + (r1 / 2), cy - (r1 * 1.2));
    nvgStrokeColor(vg, mOuterColor);
    nvgStrokeWidth(vg, 3.0f);
    nvgStroke(vg);
    nvgClosePath(vg);

    // draw yaw bubble
    nvgBeginPath(vg);
    nvgCircle(vg, cx + yawDist, cy - (r1 * 1.2), r1 * 0.05);
    nvgClosePath(vg);
    nvgFillColor(vg, mColor);
    nvgFill(vg);

    nvgRestore(vg);
}

Color InputQuad::color() const {
    return mColor;
}

void InputQuad::setColor(const Color &rgb) {
    mColor = rgb;
}

float InputQuad::getInputValue(int axis) const {
    switch (axis) {
        case 0: return mRoll;
        case 1: return mPitch;
        case 2: return mYaw;
    }
    return 0;
}

void InputQuad::setInputValue(int axis, float value) {
    switch (axis) {
        case 0: mRoll = value; return;
        case 1: mPitch = value; return;
        case 2: mYaw = value; return;
    }
}

float InputQuad::getTorqueValue(int motor) const {
    return mTorqueValues[motor];
}

void InputQuad::setTorqueValue(int motor, float value) {
    mTorqueValues[motor] = value;
}

void InputQuad::save(Serializer &s) const {
    Widget::save(s);
    s.set("color", mColor);
}

bool InputQuad::load(Serializer &s) {
    if (!Widget::load(s)) return false;
    if (!s.get("color", mColor)) return false;
    return true;
}

NAMESPACE_END(nanogui)

