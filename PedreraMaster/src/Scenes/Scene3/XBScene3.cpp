//
// Created by Miquel Àngel Soler on 24/12/15.
//

#include "XBScene3.h"

void XBScene3::setup()
{
    XBBaseScene::setup();

    int w = 200;
    int h = 250;
    colorPickerV.setSize(10, ofGetHeight() - h - 20, w, h);
    colorPickerX.setSize(10, ofGetHeight() - 2 * (h + 20), w, h);
    violinColor.set(72, 92, 81);
    celloColor.set(207, 87, 60);
    colorPickerV.setColor(violinColor);
    colorPickerX.setColor(celloColor);

    v.setup(ofGetWidth() / 2, ofGetHeight() / 2);
    x.setup(ofGetWidth() / 2, ofGetHeight() / 2);
}

void XBScene3::update()
{
    XBBaseScene::update();

    v.update();
    x.update();

    colorPickerV.update();
    colorPickerX.update();

    v.setColor(colorPickerV.getColor());
    x.setColor(colorPickerX.getColor());
}

void XBScene3::drawIntoFBO()
{
    fbo.begin();
    {
        ofBackground(0);
        v.draw();
        x.draw();

        drawGUI();

        drawFadeRectangle();
    }
    fbo.end();
}

void XBScene3::drawGUI()
{
    XBBaseScene::drawGUI();

    if (showGUI) {
        colorPickerV.draw();
        colorPickerX.draw();
    }
}
