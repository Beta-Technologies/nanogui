/*
    nanogui/plot.h -- Simple plot widget with four time series lines

    NanoGUI was developed by Wenzel Jakob <wenzel.jakob@epfl.ch>.
    The widget drawing code is based on the NanoVG demo application
    by Mikko Mononen.

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE.txt file.
*/
/** \file */

#pragma once

#include <nanogui/widget.h>

#define MAX_PLOTS 4

NAMESPACE_BEGIN(nanogui)

/**
 * \class Plot plot.h nanogui/plot.h
 *
 * \brief Simple plot widget with four time series lines.
 */
class NANOGUI_EXPORT Plot : public Widget {
public:
    Plot(Widget *parent, const std::string &caption = "Plot");
    virtual ~Plot();

    const std::string &caption() const { return mCaption; }
    void setCaption(const std::string &caption) { mCaption = caption; }

    const std::string &header() const { return mHeader; }
    void setHeader(const std::string &header) { mHeader = header; }

    const std::string &footer() const { return mFooter; }
    void setFooter(const std::string &footer) { mFooter = footer; }

    const Color &backgroundColor() const { return mBackgroundColor; }
    void setBackgroundColor(const Color &backgroundColor) { mBackgroundColor = backgroundColor; }

    const Color &foregroundColor() const { return mForegroundColor; }
    void setForegroundColor(const Color &foregroundColor) { mForegroundColor = foregroundColor; }

    const Color &textColor() const { return mTextColor; }
    void setTextColor(const Color &textColor) { mTextColor = textColor; }

    virtual Vector2i preferredSize(NVGcontext *ctx) const override;

    virtual void draw(NVGcontext *ctx) override;

    virtual void save(Serializer &s) const override;
    virtual bool load(Serializer &s) override;    

    void setLabel(const std::string text, const Color& color, int index);
    void setAxisTicks(float majorTicks=0, float minorTicks=0);

    void setYRange(float min, float max);
    void setXTimeScale(float scale);
    void setValues(const VectorXf &values, int index);


protected:
    void calcTimeRange();
    void drawAxes(NVGcontext *ctx);   
    void drawAxisTicks(NVGcontext *ctx, float tick_interval, const Color &tick_color);
    void drawPlotline(NVGcontext *ctx, const VectorXf &data, const Color &line_color);
    void drawLabels(NVGcontext *ctx);

protected:
    std::string mCaption, mHeader, mFooter;
    Color mBackgroundColor, mForegroundColor, mTextColor;

    VectorXf mValues[MAX_PLOTS];
    Color mPlotColors[MAX_PLOTS];
    std::string mPlotLabels[MAX_PLOTS];

    float mMajorTicks;
    float mMinorTicks;
    float mXTimeScale;    
    float mYmin;
    float mYmax;

    float mTimeStart;
    float mTimeEnd;

public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
};

NAMESPACE_END(nanogui)
