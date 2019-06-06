/*
    src/rpy.cpp -- Draw a circle with radius factor from 0.0 to 1.0
                          Has positive and negative color (green, red)
*/

#include <nanogui/extended/rpy.h>
#include <nanogui/theme.h>
#include <nanogui/opengl.h>
#include <nanogui/serializer/core.h>
#include <math.h>
//#include <Eigen/QR>
//#include <Eigen/Geometry>

#define ROLL 0
#define PITCH 1
#define YAW 2

NAMESPACE_BEGIN(nanogui)

RpyWidget::RpyWidget(Widget *parent, const Color& rgb)
    : Widget(parent),
      mColor(rgb),
      mAngle(0.0f)
{
    mOuterColor = Color(80,80,80, 255);
    mMode = 1;
}

Vector2i RpyWidget::preferredSize(NVGcontext *) const {
    return { 100, 100. };
}

void RpyWidget::draw(NVGcontext *ctx) {
    Widget::draw(ctx);

    if (!mVisible)
        return;

    float x = mPos.x(),
          y = mPos.y(),
          w = mSize.x(),
          h = mSize.y();

    NVGcontext* vg = ctx;

    float r0, r1, rBar, cx, cy;
    float zeroAngle = 0;

    cx = x + w*0.5f;
    cy = y + h*0.5f;
    r1 = (w < h ? w : h) * 0.5f - 5.0f;
    r0 = r1 * .75f;

    //todo: clean up redundant mode if statements.
    if (mMode == PITCH || mMode == YAW) //roll
    {
        rBar = r1 * 0.6;
        if (mMode == YAW)
        {
            zeroAngle = 90;
        }
    }
    else
    {
        rBar = r1 * 0.8;
    }

    nvgSave(vg);

    //outer ring at 1.0
    nvgBeginPath(vg);
    float circleRadius = r1 + 0.5f;
    nvgCircle(vg, cx, cy, circleRadius);
    nvgStrokeColor(vg, mOuterColor);
    nvgStrokeWidth(vg, 2.0f);
    nvgStroke(vg);

    //center lines
    nvgBeginPath(vg);
    nvgMoveTo(vg, cx - circleRadius, cy);
    nvgLineTo(vg, cx + circleRadius, cy); //horizontal mid-line

    nvgMoveTo(vg, cx, cy - circleRadius);
    nvgLineTo(vg, cx, cy + circleRadius); //vertical mid-line

    nvgStrokeColor(vg, mOuterColor);
    nvgStrokeWidth(vg, 1.0f);
    nvgStroke(vg);    

    //translate and rotate the current coordinate system
    //draw, then rotate and translate back

    //float angleRad = mAngle * deg2rad;

    // Translate to middle, rotate by angle (ccw)
    nvgTranslate(vg, cx, cy);
    nvgRotate(vg, -(zeroAngle + mAngle) * DEG2RAD);    

    // horizontal bar rotated
    nvgBeginPath(vg);
    nvgMoveTo(vg, -rBar, 0); //y is flipped (so +/- instead of -/+)
    nvgLineTo(vg, +rBar, 0);
    nvgStrokeWidth(vg, 6.0);   
    nvgStrokeColor(vg, mColor);
    nvgStroke(vg);

    //triangle basd on mode (rpy)

    //rpy modes: 0,1,2

    Vector2i p1, p2, p3;
    float rTri = r1 * 0.3f; //px


    if (mMode == PITCH || mMode == YAW) //pitch, yaw
    {
        //end of horizontal bar pointing outward
        p1(0) = rBar;
        p1(1) = -rTri/2.0; 
        
        p2(0) = rBar+rTri;
        p2(1) = 0; 

        p3(0) = rBar;
        p3(1) = rTri/2.0;

        if (mMode == YAW)
        {
            zeroAngle = 90.0; //pointing straight up.
        }
    }
    else //roll
    {
        //middle of bar pointing up
        p1(0) = -rTri/2.0;
        p1(1) = 0; 
        
        p2(0) = 0;
        p2(1) = -rTri; 

        p3(0) = rTri/2.0;
        p3(1) = 0;

        zeroAngle = 0;        
    }

    //draw the triangle
    nvgBeginPath(vg);
    nvgMoveTo(vg, p1.x(), p1.y()); //y is flipped (so +/- instead of -/+)
    nvgLineTo(vg, p2.x(), p2.y()); 
    nvgLineTo(vg, p3.x(), p3.y()); 
    nvgLineTo(vg, p1.x(), p1.y()); //y is flipped (so +/- instead of -/+)
    nvgFillColor(vg, mColor);
    nvgFill(vg);    
   
    //rotate and translate back
    nvgRotate(vg, (zeroAngle + mAngle) * DEG2RAD);
    nvgTranslate(vg, -cx, -cy);         

    //circle for the pivot point
    // nvgBeginPath(vg);
    // nvgCircle(vg, cx, cy, 8);
    // nvgFillColor(vg, mOuterColor);
    // nvgFill(vg);     

    nvgRestore(vg);
}

Color RpyWidget::color() const {
    return mColor;
}

void RpyWidget::setColor(const Color &rgb) {
    mColor = rgb;
}

float RpyWidget::angle() const {
 return mAngle;
}

void RpyWidget::setAngle(float v) {
    mAngle = v;
}

void RpyWidget::save(Serializer &s) const {
    Widget::save(s);
    s.set("color", mColor);
}

bool RpyWidget::load(Serializer &s) {
    if (!Widget::load(s)) return false;
    if (!s.get("color", mColor)) return false;
    return true;
}

NAMESPACE_END(nanogui)

