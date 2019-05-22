/*
    nanogui/extended/led.h -- A colored LED indicator

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
 * \class Led led.h nanogui/extended/led.h
 *
 * \brief A colored LED indicator
 */
class NANOGUI_EXPORT Led : public Widget {
public:
    Led(Widget *parent);

    bool isOn() { return mIsOn; }
    void setOn(bool b) { mIsOn = b; }

    Color color() const {return mColor; }
    void setColor(const Color &color) { mColor = color;}

    virtual Vector2i preferredSize(NVGcontext *ctx) const override;
    virtual void draw(NVGcontext* ctx) override;

    virtual void save(Serializer &s) const override;
    virtual bool load(Serializer &s) override;
protected:
    bool mIsOn;
    Color mColor;
public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
};

NAMESPACE_END(nanogui)
