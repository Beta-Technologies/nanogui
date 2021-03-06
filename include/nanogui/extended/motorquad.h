/*
    nanogui/motorquad.h -- widget to display four motor values

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
 * \class MotorQuad motorquad.h nanogui/motorquad.h
 *
 * \brief A widget that displays four motor values, one per quadrant
 */
class NANOGUI_EXPORT MotorQuad : public Widget {
public:
    MotorQuad(Widget *parent, const Color& color = Color(1.0f, 0.0f, 0.0f, 1.0f));

    /// Set the change callback
    std::function<void(const Color &)> callback() const                  { return mCallback;     }
    void setCallback(const std::function<void(const Color &)> &callback) { mCallback = callback; }


    Color color() const;
    void setColor(const Color& color);

    float value(int idx) const;
    void setValue(float v, int idx);

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
    float mValue;
    float mValues[4] = {0.0f, 0.0f, 0.0f, 0.0f};
    std::function<void(const Color &)> mCallback;    

};

NAMESPACE_END(nanogui)
