/*
    src/plot.cpp -- Simple plot widget with four time series lines

    NanoGUI was developed by Wenzel Jakob <wenzel.jakob@epfl.ch>.
    The widget drawing code is based on the NanoVG demo application
    by Mikko Mononen.

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE.txt file.
*/

#include <nanogui/extended/plot.h>
#include <nanogui/theme.h>
#include <nanogui/opengl.h>
#include <nanogui/serializer/core.h>

#include <iostream>
#include <iomanip>

NAMESPACE_BEGIN(nanogui)

Plot::Plot(Widget *parent, const std::string &caption)
    : Widget(parent),
      mCaption(caption),
      mMajorTicks(0), 
      mMinorTicks(0), 
      mXTimeScale(1.0f),
      mYmin(-1.0f),
      mYmax(1.0f),
      mTimeStart(0.0f),
      mTimeEnd(0.0f),
      mIndexStart(0),
      mIndexEnd(0)
{
    mPlotColors[0] = Color(200,0,0,255);
    mPlotColors[1] = Color(0,200,0,255);
    mPlotColors[2] = Color(50,50,200,255);
    mPlotColors[3] = Color(200,200,0,255);

    mXTimeScale = 10; //ms per pixel
    
    for (int i = 0; i < MAX_PLOTS; i++)
    {
        mValuesFull[i] = false;
        mValuesHead[i] = 0;
        memset(mValues[i], 0, MAX_POINTS_PER_PLOT * sizeof(float));
    } 
    
    
}

Plot::~Plot()
{
}

Vector2i Plot::preferredSize(NVGcontext *) const {
    return Vector2i(180, 30);
}

void Plot::setLabel(const std::string text, const Color& color, int index)
{
    if (index >= 0 && index < MAX_PLOTS)
    {
        mPlotLabels[index] = text;
        mPlotColors[index] = color;        
    }
}

void Plot::setAxisTicks(float majorTicks, float minorTicks)
{
    mMajorTicks = majorTicks;
    mMinorTicks = minorTicks;
}

void Plot::addValue(const int &index, const float &value)
{
    if (index >= 0 && index < MAX_PLOTS)
    {
        mValues[index][mValuesHead[index]] = value;
        mValuesHead[index]++;
        if (mValuesHead[index] == MAX_POINTS_PER_PLOT)
        {
            mValuesHead[index] = 0;
            mValuesFull[index] = true;
        }
    }
}

void Plot::setYRange(float min, float max)
{
    mYmin = min;
    mYmax = max;    
}

void Plot::setXTimeScale(float scale)
{
    mXTimeScale = scale;   
}

void Plot::draw(NVGcontext *ctx) {
    Widget::draw(ctx);

    nvgBeginPath(ctx);
    nvgRect(ctx, mPos.x(), mPos.y(), mSize.x(), mSize.y());
    nvgFillColor(ctx, mTheme->mPlotBackgroundColor);
    nvgFill(ctx);

    calcTimeRange();
    drawAxes(ctx);

    for (int i=0; i<MAX_PLOTS; i++)
    {
        if ((mValuesHead[i] > 0) || mValuesFull[i])
        {
            drawPlotline(ctx, i) ;       
        }
    }
    drawLabels(ctx);
}

void Plot::calcTimeRange() {
    mIndexEnd = mValuesFull[0] ? MAX_POINTS_PER_PLOT : mValuesHead[0];
    mTimeEnd = mIndexEnd * mXTimeScale;
    mIndexStart = 0;
    if (mIndexEnd > mSize.x())
    {
        mIndexStart = mIndexEnd - mSize.x();
    }     
    mTimeStart = mIndexStart * mXTimeScale;
}

std::string format(double value) {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(2) << value;
    return ss.str();    
}


void Plot::drawAxes(NVGcontext *ctx) {
    nvgBeginPath(ctx);
    nvgMoveTo(ctx, mPos.x(), mPos.y() + mSize.y()/2.0);
    nvgLineTo(ctx, mPos.x() + mSize.x(), mPos.y() + mSize.y()/2.0);
    nvgStrokeColor(ctx, Color(43, 73, 96, 255));
    nvgStroke(ctx); 
    
    
    nvgFontSize(ctx, 14.0f);
    nvgTextAlign(ctx, NVG_ALIGN_LEFT | NVG_ALIGN_TOP);
    nvgFillColor(ctx, mTheme->mPlotTextColor);
    nvgText(ctx, mPos.x() + 3, mPos.y() + 3, format(mYmax).c_str(), NULL); 
    nvgText(ctx, mPos.x() + 3, mPos.y() + mSize.y() / 2, format((mYmax + mYmin) / 2.0).c_str(), NULL); 
    nvgText(ctx, mPos.x() + 3, mPos.y() + mSize.y() - 14, format(mYmin).c_str(), NULL);

    drawAxisTicks(ctx, mMinorTicks, mTheme->mPlotMinorTickColor);
    drawAxisTicks(ctx, mMajorTicks, mTheme->mPlotMajorTickColor);
}

void Plot::drawAxisTicks(NVGcontext *ctx, float tick_interval, const Color &tick_color) {

    nvgBeginPath(ctx); 
    float time_index = 0.0f;

    if (tick_interval > 0 && tick_interval < mSize.x() * mXTimeScale)
    {
        float r = fmod(mTimeStart, tick_interval);
        float t1 = mTimeStart - r + tick_interval;
        for (time_index = t1; time_index < mTimeEnd; time_index += tick_interval)
        {
            float xOffset = (time_index-mTimeStart) / mXTimeScale;
            nvgMoveTo(ctx, mPos.x() + xOffset, mPos.y());
            nvgLineTo(ctx, mPos.x() + xOffset, mPos.y() + mSize.y());  
        }
    }
    nvgStrokeWidth(ctx, 1);
    nvgStrokeColor(ctx, tick_color);
    nvgStroke(ctx);     
}


void Plot::drawPlotline(NVGcontext *ctx, const int &index) {

    // check the range
    if (mYmax == mYmin)
    {
        return; //scaling is zero, nothing to draw.
    }

    //draw data
    nvgBeginPath(ctx);
    nvgMoveTo(ctx, mPos.x(), mPos.y()+mSize.y()/2.0);

    //take the values at the end of the array and work back.
    size_t start_index = mTimeStart / mXTimeScale;
    size_t end_index = mTimeEnd / mXTimeScale;

    //we only draw the last N values
    for (size_t i = start_index; i < end_index; i++) {

        // get data point out of mValues based on queing position
        float value = mValuesFull[index] ?
                        (mValues[index][(mValuesHead[index] + i) % MAX_POINTS_PER_PLOT]) : 
                        mValues[index][i];
        

        //transform from (mYmax mYmin) to (1 0)
        value = (value - mYmin)/(mYmax - mYmin);
        float vx = mPos.x() + (i - start_index);
        float vy = mPos.y() + (1-value) * mSize.y();
        nvgLineTo(ctx, vx, vy);
    }

    nvgStrokeColor(ctx, mPlotColors[index]);
    nvgStroke(ctx);
}

void Plot::drawLabels(NVGcontext *ctx) {

    nvgFontFace(ctx, "sans");

    if (!mCaption.empty()) {
        nvgFontSize(ctx, 14.0f);
        nvgTextAlign(ctx, NVG_ALIGN_CENTER | NVG_ALIGN_TOP);
        nvgFillColor(ctx, mTheme->mPlotTextColor);
        nvgText(ctx, mPos.x() + mSize.x()/2, mPos.y() + 1, mCaption.c_str(), NULL);
    }

    if (!mHeader.empty()) {
        nvgFontSize(ctx, 18.0f);
        nvgTextAlign(ctx, NVG_ALIGN_RIGHT | NVG_ALIGN_TOP);
        nvgFillColor(ctx, mTheme->mPlotTextColor);
        nvgText(ctx, mPos.x() + mSize.x() - 3, mPos.y() + 1, mHeader.c_str(), NULL);
    }

    if (!mFooter.empty()) {
        nvgFontSize(ctx, 15.0f);
        nvgTextAlign(ctx, NVG_ALIGN_RIGHT | NVG_ALIGN_BOTTOM);
        nvgFillColor(ctx, mTheme->mPlotTextColor);
        nvgText(ctx, mPos.x() + mSize.x() - 3, mPos.y() + mSize.y() - 1, mFooter.c_str(), NULL);
    }




    nvgBeginPath(ctx);
    nvgRect(ctx, mPos.x(), mPos.y(), mSize.x(), mSize.y());
    nvgStrokeColor(ctx, Color(100, 255));
    nvgStroke(ctx);    
}

void Plot::save(Serializer &s) const {
    Widget::save(s);
    s.set("caption", mCaption);
    s.set("header", mHeader);
    s.set("footer", mFooter);
    s.set("backgroundColor", mTheme->mPlotBackgroundColor);
    s.set("foregroundColor", mTheme->mPlotForegroundColor);
    s.set("textColor", mTheme->mPlotTextColor);
    //s.set("values", mValues);
}

bool Plot::load(Serializer &s) {
    if (!Widget::load(s)) return false;
    if (!s.get("caption", mCaption)) return false;
    if (!s.get("header", mHeader)) return false;
    if (!s.get("footer", mFooter)) return false;
    if (!s.get("backgroundColor", mTheme->mPlotBackgroundColor)) return false;
    if (!s.get("foregroundColor", mTheme->mPlotForegroundColor)) return false;
    if (!s.get("textColor", mTheme->mPlotTextColor)) return false;
    //if (!s.get("values", mValues)) return false;
    return true;
}


NAMESPACE_END(nanogui)
