/*
    src/graph.cpp -- Simple graph widget for showing a function plot

    NanoGUI was developed by Wenzel Jakob <wenzel.jakob@epfl.ch>.
    The widget drawing code is based on the NanoVG demo application
    by Mikko Mononen.

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE.txt file.
*/

#include <nanogui/graph.h>
#include <nanogui/theme.h>
#include <nanogui/opengl.h>
#include <nanogui/serializer/core.h>

#include <iostream>

NAMESPACE_BEGIN(nanogui)

Graph::Graph(Widget *parent, const std::string &caption)
    : Widget(parent), mCaption(caption) {
    mBackgroundColor = Color(20, 128);
    mForegroundColor = Color(255, 192, 0, 128);
    mTextColor = Color(240, 192);
}

Vector2i Graph::preferredSize(NVGcontext *) const {
    return Vector2i(180, 45);
}

void Graph::draw(NVGcontext *ctx) {
    Widget::draw(ctx);

    nvgBeginPath(ctx);
    nvgRect(ctx, mPos.x(), mPos.y(), mSize.x(), mSize.y());
    nvgFillColor(ctx, mBackgroundColor);
    nvgFill(ctx);

    if (mValues.size() < 2)
        return;


    //time ranges for drawing the time-based plot
    float x_scale = 10; //ms per pixel

    float time_start = 0.0f;
    float time_end = mValues.size() * x_scale;
    float time_range = mSize.x() * x_scale;
    if (time_end > time_range)
    {
        time_start = time_end - time_range;
    }   
    

    //x axis - time
    nvgBeginPath(ctx);
    nvgMoveTo(ctx, mPos.x(), mPos.y() + mSize.y()/2.0);
    nvgLineTo(ctx, mPos.x() + mSize.x(), mPos.y() + mSize.y()/2.0);
    nvgStrokeColor(ctx, Color(100, 255));
    nvgStroke(ctx); 

    //x axis ticks
    float major_ticks = 0.0f; //1000.0f;
    float minor_ticks = 500.0f;

    float time_index = 0.0f;

    //major ticks
    nvgBeginPath(ctx); 
    if (minor_ticks > 0 && minor_ticks < mSize.x() * x_scale)
    {
        float r = fmod(time_start, minor_ticks);
        float t1 = time_start - r + minor_ticks;
        for (time_index = t1; time_index < time_end; time_index += minor_ticks)
        {
            float xOffset = (time_index-time_start) / x_scale;
            nvgMoveTo(ctx, mPos.x() + xOffset, mPos.y());
            nvgLineTo(ctx, mPos.x() + xOffset, mPos.y() + mSize.y());  
        }
    }
    nvgStrokeWidth(ctx, 1);
    nvgStrokeColor(ctx, Color(70, 255));
    nvgStroke(ctx);     

    //minor ticks
    nvgBeginPath(ctx);
    if (major_ticks > 0 && major_ticks < mSize.x() * x_scale)
    {
        float r = fmod(time_start, major_ticks);
        float t1 = time_start - r + major_ticks;
        for (time_index = t1; time_index < time_end; time_index += major_ticks)
        {
            float xOffset = (time_index-time_start) / x_scale;
            //std::cout << xOffset << " "; 
            nvgMoveTo(ctx, mPos.x() + xOffset, mPos.y());
            nvgLineTo(ctx, mPos.x() + xOffset, mPos.y() + mSize.y());  
        }
    }
    nvgStrokeWidth(ctx, 1);
    nvgStrokeColor(ctx, Color(130, 130, 130, 255));
    nvgStroke(ctx);        

    //draw data
    nvgBeginPath(ctx);
    nvgMoveTo(ctx, mPos.x(), mPos.y()+mSize.y()/2.0);

    //take the values at the end of the array and work back.
    size_t start_index = time_start / x_scale;
    size_t end_index = time_end / x_scale;

    //y_range: yMin, yMax : we expect yMin0 or yMin = -yMax.
    //         the axis is drawn at y=0.
    //major_ticks : ms  - vertical line, 2px thick. default 1000 (not drawn if o)
    //minor_tick  : ms  - vertical line, 1px think, default 500 (not drawn if 0)
    //x_scale: ms/pixel :  default 10
    //x_intervade: ms in between samples: default 10

    //we only draw the last N values, where N is the window width without scale applied.
    for (size_t i = start_index; i < end_index; i++) {
        float value = mValues[i];
        float scale = 1.0f;
        //float vx = mPos.x() + i * mSize.x() / (float) (mValues.size() - 1);
        float vx = mPos.x() + (i - start_index) * scale;
        float vy = mPos.y() + (1-value) * mSize.y();
        nvgLineTo(ctx, vx, vy);
    }

    // char sDots[20];
    // sprintf(sDots, "n: %ld", mValues.size());
    // mFooter = sDots;

    nvgStrokeColor(ctx, mForegroundColor);
    nvgStroke(ctx);

    nvgFontFace(ctx, "sans");

    if (!mCaption.empty()) {
        nvgFontSize(ctx, 14.0f);
        nvgTextAlign(ctx, NVG_ALIGN_LEFT | NVG_ALIGN_TOP);
        nvgFillColor(ctx, mTextColor);
        nvgText(ctx, mPos.x() + 3, mPos.y() + 1, mCaption.c_str(), NULL);
    }

    if (!mHeader.empty()) {
        nvgFontSize(ctx, 18.0f);
        nvgTextAlign(ctx, NVG_ALIGN_RIGHT | NVG_ALIGN_TOP);
        nvgFillColor(ctx, mTextColor);
        nvgText(ctx, mPos.x() + mSize.x() - 3, mPos.y() + 1, mHeader.c_str(), NULL);
    }

    if (!mFooter.empty()) {
        nvgFontSize(ctx, 15.0f);
        nvgTextAlign(ctx, NVG_ALIGN_RIGHT | NVG_ALIGN_BOTTOM);
        nvgFillColor(ctx, mTextColor);
        nvgText(ctx, mPos.x() + mSize.x() - 3, mPos.y() + mSize.y() - 1, mFooter.c_str(), NULL);
    }

    nvgBeginPath(ctx);
    nvgRect(ctx, mPos.x(), mPos.y(), mSize.x(), mSize.y());
    nvgStrokeColor(ctx, Color(100, 255));
    nvgStroke(ctx);
}

void Graph::save(Serializer &s) const {
    Widget::save(s);
    s.set("caption", mCaption);
    s.set("header", mHeader);
    s.set("footer", mFooter);
    s.set("backgroundColor", mBackgroundColor);
    s.set("foregroundColor", mForegroundColor);
    s.set("textColor", mTextColor);
    s.set("values", mValues);
}

bool Graph::load(Serializer &s) {
    if (!Widget::load(s)) return false;
    if (!s.get("caption", mCaption)) return false;
    if (!s.get("header", mHeader)) return false;
    if (!s.get("footer", mFooter)) return false;
    if (!s.get("backgroundColor", mBackgroundColor)) return false;
    if (!s.get("foregroundColor", mForegroundColor)) return false;
    if (!s.get("textColor", mTextColor)) return false;
    if (!s.get("values", mValues)) return false;
    return true;
}

NAMESPACE_END(nanogui)
