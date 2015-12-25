//
// Created by Miquel Àngel Soler on 24/12/15.
//

#ifndef PEDRERAMASTER_XBSCENE3_H
#define PEDRERAMASTER_XBSCENE3_H

#include "XBBaseScene.h"

class XBScene3 : public XBBaseScene
{
public:

    XBScene3(const string &name) : XBBaseScene(name) {}

    virtual void setup();
    virtual void update();
    virtual void drawIntoFBO();

};


#endif //PEDRERAMASTER_XBSCENE3_H