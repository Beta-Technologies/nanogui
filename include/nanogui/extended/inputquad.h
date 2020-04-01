/*
    nanogui/inputquad.h -- widget to display four motor values and pilot input

    Adapted from a widget by Dmitriy Morozov.

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

/**
 * \class InputQuad inputquad.h nanogui/inputquad.h
 *
 * \brief A widget that displays pilot input
 */
class NANOGUI_EXPORT InputQuad : public Widget {
public:
    InputQuad(Widget *parent, const Color& color = Color(0, 208, 255, 255), bool levels = false);

    /// Set the change callback
    std::function<void(const Color &)> callback() const                  { return mCallback;     }
    void setCallback(const std::function<void(const Color &)> &callback) { mCallback = callback; }

    Color color() const;
    void setColor(const Color& color);

    // axis: 0=roll, 1=pitch, 2=yaw
    float getInputValue(int axis) const;
    void setInputValue(int axis, float v);

    // motor torque values
    float getTorqueValue(int motor) const;
    void setTorqueValue(int motor, float v);

    virtual Vector2i preferredSize(NVGcontext *ctx) const override;
    virtual void draw(NVGcontext *ctx) override;

    virtual void save(Serializer &s) const override;
    virtual bool load(Serializer &s) override;
private:

protected:
    bool mDrawLevels;
    Color mColor;
    Color mOuterColor;
    float mTorqueValues[4];
    float mPitch = 0, mRoll = 0, mYaw = 0;
    std::function<void(const Color &)> mCallback;
};

NAMESPACE_END(nanogui)
