/*
    src/toggleswitch.cpp -- A slide toggle switch

    NanoGUI was developed by Wenzel Jakob <wenzel.jakob@epfl.ch>.
    The widget drawing code is based on the NanoVG demo application
    by Mikko Mononen.

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE.txt file.
*/

#include <nanogui/extended/toggleswitch.h>
#include <nanogui/opengl.h>
#include <nanogui/theme.h>
#include <nanogui/entypo.h>
#include <nanogui/serializer/core.h>

NAMESPACE_BEGIN(nanogui)

ToggleSwitch::ToggleSwitch(Widget *parent, 
                   const std::function<void(bool) > &callback)
    : Widget(parent), mPushed(false), mChecked(false),
      mCallback(callback) 
      {
        setFixedSize( Vector2i(20,40) ); 
      }

bool ToggleSwitch::mouseButtonEvent(const Vector2i &p, int button, bool down,
                                int modifiers) {
    Widget::mouseButtonEvent(p, button, down, modifiers);
    if (!mEnabled)
        return false;

    if (button == GLFW_MOUSE_BUTTON_1) {
        if (down) {
            mPushed = true;
        } else if (mPushed) {
            if (contains(p)) {
                mChecked = !mChecked;
                if (mCallback)
                    mCallback(mChecked);
            }
            mPushed = false;
        }
        return true;
    }
    return false;
}

Vector2i ToggleSwitch::preferredSize(NVGcontext * /* ctx */) const {
    if (mFixedSize != Vector2i::Zero())
        return mFixedSize;
    return Vector2i(20,40);
}

void ToggleSwitch::draw(NVGcontext *ctx) {
    Widget::draw(ctx);

    NVGpaint bg = nvgBoxGradient(ctx, mPos.x() + 1.5f, mPos.y() + 1.5f,
                                 2 * mSize.y() - 2.0f, mSize.y() - 2.0f, 3, 3,
                                 Color(0, 32), Color(0, 0, 0, 180));

    //Back ground for the switch
    nvgBeginPath(ctx);
    //nvgRoundedRect(ctx, mPos.x() + 1.0f, mPos.y() + 1.0f, 2 * mSize.y() - 2.0f,
    //               mSize.y() - 2.0f, 3);
    nvgRoundedRect(ctx, mPos.x() + 1.0f, mPos.y() + 1.0f, mSize.x() - 2.0f,
                   2*mSize.y() - 2.0f, 3);    
    nvgFillPaint(ctx, bg);
    nvgFill(ctx);

    //foreground rectangle
    int yOffset = mChecked ? mPos.y() : mPos.y() + mSize.x();

    nvgBeginPath(ctx);
    nvgRoundedRect(ctx, mPos.x() + 1.0f, yOffset + 1.0f, mSize.x() - 2.0f,
                   mSize.x() - 2.0f, 3);    

    //todo: use theme colors here
    Color offColor = Color(45,71,92, 255);  //default
    Color onColor = Color(127, 236, 133, 255); //green

    Color fillColor = mChecked ? onColor : offColor;    
    nvgFillColor(ctx, fillColor);  
    nvgFill(ctx);    
}

void ToggleSwitch::save(Serializer &s) const {
    Widget::save(s);
    s.set("pushed", mPushed);
    s.set("checked", mChecked);
}

bool ToggleSwitch::load(Serializer &s) {
    if (!Widget::load(s)) return false;
    if (!s.get("pushed", mPushed)) return false;
    if (!s.get("checked", mChecked)) return false;
    return true;
}

NAMESPACE_END(nanogui)
