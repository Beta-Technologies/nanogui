/*
    src/colorbar.cpp -- a bar showing an energy level in selected colors.

    NanoGUI was developed by Wenzel Jakob <wenzel.jakob@epfl.ch>.
    The widget drawing code is based on the NanoVG demo application
    by Mikko Mononen.

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE.txt file.
*/

#include <nanogui/extended/colorbar.h>
#include <nanogui/opengl.h>
#include <nanogui/serializer/core.h>

NAMESPACE_BEGIN(nanogui)

ColorBar::ColorBar(Widget *parent)
    : Widget(parent), mValue(0.0f) 
{
    //default color settings
    mLevels[0] = 0.00f;
    mLevels[1] = 0.25f;
    mLevels[2] = 0.50f;
    mLevels[3] = 0.75f;

    mColors[0] = Color(255, 94, 94, 255);   //red
    mColors[1] = Color(255, 169, 55, 255);  //orange
    mColors[2] = Color(234, 236, 127, 255); //yellow
    mColors[3] = Color(127, 236, 133, 255); //green
}

Vector2i ColorBar::preferredSize(NVGcontext *) const {
    return Vector2i(150, 20);
}

void ColorBar::draw(NVGcontext* ctx) {
    Widget::draw(ctx);

    NVGpaint paint = nvgBoxGradient(
        ctx, mPos.x() + 1, mPos.y() + 1,
        mSize.x()-2, mSize.y(), 3, 4, Color(120, 32), Color(120, 92));
    nvgBeginPath(ctx);
    nvgRoundedRect(ctx, mPos.x(), mPos.y(), mSize.x(), mSize.y(), 3);
    nvgFillPaint(ctx, paint);
    nvgFill(ctx);

    float value = std::min(std::max(0.0f, mValue), 1.0f);
    int barPos = (int) std::round((mSize.x() - 2) * value);

    //paint = nvgBoxGradient(
    //    ctx, mPos.x(), mPos.y(),
    //    barPos+1.5f, mSize.y()-1, 3, 4,
    //    Color(220, 100), Color(128, 100));

    //color is based on the value and the levels.
    Color barColor = mColors[3];
    for(int i=0; i<MAX_LEVELS; i++)
    {
        if (mValue > mLevels[i])
            barColor = mColors[i];
    }
    //barColor[3] = 200;
    Color fadeBarColor = barColor;
    //fadeBarColor[3]=100;

    paint = nvgBoxGradient(
        ctx, mPos.x(), mPos.y(),
        barPos+1.5f, mSize.y()-1, 3, 4,
        barColor, fadeBarColor);    

    nvgBeginPath(ctx);
    nvgRoundedRect(
        ctx, mPos.x()+1, mPos.y()+1,
        barPos, mSize.y()-2, 3);
    nvgFillPaint(ctx, paint);
    nvgFill(ctx);
}

Color ColorBar::color(int level) const
{
    if (level < MAX_LEVELS)
        return mColors[level];
    else
        return Color(0,0,0,255); //black  
}

void ColorBar::setColor(const Color &c, int level) {
    if (level < MAX_LEVELS)
        mColors[level] = c;
}

void ColorBar::save(Serializer &s) const {
    Widget::save(s);
    s.set("value", mValue);
}

bool ColorBar::load(Serializer &s) {
    if (!Widget::load(s))
        return false;
    if (!s.get("value", mValue))
        return false;
    return true;
}

NAMESPACE_END(nanogui)
