/*
    nanogui/colorbar.h -- a bar showing an energy level in selected colors.

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
 * \class ColorBar colorbar.h nanogui/colorbar.h
 *
 * \brief Standard widget for visualizing progress.
 */
class NANOGUI_EXPORT ColorBar : public Widget {
public:
    ColorBar(Widget *parent);

    float value() { return mValue; }
    void setValue(float value) { mValue = value; }

    Color color(int level) const;
    void setColor(const Color &c, int level);

    virtual Vector2i preferredSize(NVGcontext *ctx) const override;
    virtual void draw(NVGcontext* ctx) override;

    virtual void save(Serializer &s) const override;
    virtual bool load(Serializer &s) override;

    static const int MAX_LEVELS = 4;

protected:
    float mValue;
    float mLevels[MAX_LEVELS];
    Color mColors[MAX_LEVELS];
public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW

};

NAMESPACE_END(nanogui)
