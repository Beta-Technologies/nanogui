/*
    src/led.cpp -- A colored LED indicator

    NanoGUI was developed by Wenzel Jakob <wenzel.jakob@epfl.ch>.
    The widget drawing code is based on the NanoVG demo application
    by Mikko Mononen.

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE.txt file.
*/

#include <nanogui/extended/led.h>
#include <nanogui/opengl.h>
#include <nanogui/serializer/core.h>

NAMESPACE_BEGIN(nanogui)

Led::Led(Widget *parent)
    : Widget(parent), mIsOn(false) {}

Vector2i Led::preferredSize(NVGcontext *) const {
    return Vector2i(20, 20);
}

void Led::draw(NVGcontext* ctx) {
    Widget::draw(ctx);

    //default disabled color is just gray
    // NVGpaint paint = nvgBoxGradient(
    //     ctx, mPos.x() + 1, mPos.y() + 1,
    //     mSize.x(), mSize.y(), 3, 4, Color(120, 32), Color(120, 92));

    float radius = mSize.x()/2.0f;
    nvgBeginPath(ctx);
    nvgCircle(ctx, mPos.x() + mSize.x()/2, mPos.y() + mSize.y()/2, radius);
    nvgFillColor(ctx, Color(120, 32));
    //nvgFillPaint(ctx, paint);
    nvgFill(ctx);

    if (mIsOn)
    {
        Color fadeColor = mColor;
        fadeColor[3] = 100; //more transparent

        // paint = nvgBoxGradient(
        // ctx, mPos.x(), mPos.y(),
        // mSize.x()-1, mSize.y()-1, 3, 4,
        // mColor, fadeColor);    

        nvgBeginPath(ctx);
        nvgCircle( ctx, mPos.x() + mSize.x()/2, mPos.y() + mSize.y()/2, radius);
        //nvgFillPaint(ctx, paint);
        nvgFillColor(ctx, mColor);
        nvgFill(ctx);       
    }
}

void Led::save(Serializer &s) const {
    Widget::save(s);
    s.set("on", mIsOn);
    s.set("color", mColor);
}

bool Led::load(Serializer &s) {
    if (!Widget::load(s))
        return false;
    if (!s.get("isOn", mIsOn))
        return false;
    if (!s.get("color", mColor))
        return false;    
    return true;
}

NAMESPACE_END(nanogui)
