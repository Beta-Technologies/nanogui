/*
    nanogui/rpy.h -- display roll, pitch or yaw in a circular widget.

    NanoGUI was developed by Wenzel Jakob <wenzel.jakob@epfl.ch>.
    The widget drawing code is based on the NanoVG demo application
    by Mikko Mononen.

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE.txt file.
*/
/** \file */

#pragma once

#include <nanogui/widget.h>

NAMESPACE_BEGIN(nanogui)

#define DEG2RAD 3.141592653589793f / 180.0f

/**
 * \class RpyWidget RpyWidget.h nanogui/RpyWidget.h
 *
 * \brief Display motor value as a sized circle
 */
class NANOGUI_EXPORT RpyWidget : public Widget {
public:

    enum Mode {ROLL, PITCH, YAW };

    RpyWidget(Widget *parent, const Color& color = Color(1.0f, 0.0f, 0.0f, 1.0f));

    /// Set the change callback
    std::function<void(const Color &)> callback() const                  { return mCallback;     }
    void setCallback(const std::function<void(const Color &)> &callback) { mCallback = callback; }

    Color color() const;
    void setColor(const Color& color);

    int mode() const {return mMode;}
    void setMode(int m) {mMode = m;}

    float angle() const;
    void setAngle(float v);

    virtual Vector2i preferredSize(NVGcontext *ctx) const override;
    virtual void draw(NVGcontext *ctx) override;

    virtual void save(Serializer &s) const override;
    virtual bool load(Serializer &s) override;
private:
    enum Region {
        None = 0,
        InnerTriangle = 1,
        OuterCircle = 2,
        Both = 3
    };

protected:
    Color mColor;
    Color mOuterColor;
    std::function<void(const Color &)> mCallback;
    float mAngle; 
    int mMode;   

};

NAMESPACE_END(nanogui)
