/*
    nanogui/toggleswitch.h -- A toggle switch button (left-right)

    added by Jeff Sprenger - April 2019

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
 * \class CheckBox checkbox.h nanogui/checkbox.h
 *
 * \brief Two-state check box widget.
 */
class NANOGUI_EXPORT ToggleSwitch : public Widget {
public:
    ToggleSwitch(Widget *parent, 
             const std::function<void(bool)> &callback = std::function<void(bool)>());

    const bool &checked() const { return mChecked; }
    void setChecked(const bool &checked) { mChecked = checked; }

    const bool &pushed() const { return mPushed; }
    void setPushed(const bool &pushed) { mPushed = pushed; }

    std::function<void(bool)> callback() const { return mCallback; }
    void setCallback(const std::function<void(bool)> &callback) { mCallback = callback; }

    virtual bool mouseButtonEvent(const Vector2i &p, int button, bool down, int modifiers) override;
    virtual Vector2i preferredSize(NVGcontext *ctx) const override;
    virtual void draw(NVGcontext *ctx) override;

    virtual void save(Serializer &s) const override;
    virtual bool load(Serializer &s) override;
protected:
    bool mPushed, mChecked;
    std::function<void(bool)> mCallback;
public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
};

NAMESPACE_END(nanogui)
