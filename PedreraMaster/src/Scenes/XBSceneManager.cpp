//
// Created by Miquel Àngel Soler on 24/12/15.
//

#include "XBSceneManager.h"
#include "ofxTweenzor.h"

#ifdef OF_DEBUG
const string GUI_FILENAME = "Settings/guiSettings.xml";
#endif

XBSceneManager::XBSceneManager()
{
    state = SCENESTATE_OnScene;
    currentSceneIndex = -1;
    nextSceneIndex = -1;
}

void XBSceneManager::addScene(XBBaseScene *scene)
{
    scenes.push_back(scene);
}

void XBSceneManager::setup(int initialScene)
{
    currentSceneIndex = nextSceneIndex = initialScene;
    Tweenzor::init();
}

void XBSceneManager::update()
{
    if (scenes.size() == 0) return;
    if (currentSceneIndex < 0) return;

    switch(state)
    {
        case SCENESTATE_OnScene:
        {
            scenes[currentSceneIndex]->update();
            break;
        }
        case SCENESTATE_Transitioning:
        {
            scenes[currentSceneIndex]->update();
            scenes[nextSceneIndex]->update();
            Tweenzor::update(ofGetElapsedTimeMillis());
            break;
        }
        default: break;
    }
//    cout << "State: " << state << endl;
}

void XBSceneManager::draw()
{
    if (scenes.size() == 0) return;
    if (currentSceneIndex < 0) return;

//    ofEnableBlendMode(OF_BLENDMODE_ALPHA);

    switch(state)
    {
        case SCENESTATE_OnScene:
        {
            drawSceneAtIndex(currentSceneIndex);
            break;
        }
        case SCENESTATE_Transitioning:
        {
//            cout << "SrcAlpha: " << scenes[currentSceneIndex]->fboAlpha << " - DstAlpha: " << scenes[nextSceneIndex]->fboAlpha << endl;
            drawSceneAtIndex(currentSceneIndex);
            drawSceneAtIndex(nextSceneIndex);
            break;
        }
        default: break;
    }

//    ofDisableBlendMode();
}

void XBSceneManager::exit()
{
}

void XBSceneManager::goToScene(unsigned int sceneIndex, SceneTransitionMode transitionMode, float timeInSeconds)
{
    if (sceneIndex >= scenes.size()) return;
    if (sceneIndex == currentSceneIndex) return;
    if (state == SCENESTATE_Transitioning)
    {
        cout << "Is transitioning: SKIP" << endl;
        return;
    }

    switch(transitionMode)
    {
        case SCENETRANSITION_Direct:
        {
            state = SCENESTATE_OnScene;
            currentSceneIndex = sceneIndex;
            scenes[currentSceneIndex]->setFBOAlpha(255.0f);
            break;
        }
        case SCENETRANSITION_Fade:
        {
            state = SCENESTATE_Transitioning;
            nextSceneIndex = sceneIndex;

            cout << "[START FADE TWEEN]" << endl;
            scenes[nextSceneIndex]->setFBOAlpha(0.0f);

            float tweenDelay = 0.0f;

            Tweenzor::add(scenes[currentSceneIndex]->getFBOAlpha(), *(scenes[currentSceneIndex]->getFBOAlpha()), 0.0f, tweenDelay, timeInSeconds);
            Tween *srcTween = Tweenzor::getTween(scenes[currentSceneIndex]->getFBOAlpha());
            srcTween->setRepeat(1, false);

            Tweenzor::add(scenes[nextSceneIndex]->getFBOAlpha(), *(scenes[nextSceneIndex]->getFBOAlpha()), 255.0f, tweenDelay, timeInSeconds);
            Tween *dstTween = Tweenzor::getTween(scenes[nextSceneIndex]->getFBOAlpha());
            dstTween->setRepeat(1, false);
            Tweenzor::addCompleteListener(dstTween, this, &XBSceneManager::onFadeComplete);

            break;
        }
        default: break;
    }
}

void XBSceneManager::goToNextScene(SceneTransitionMode transitionMode, float timeInSeconds)
{
    unsigned int sceneIndex = (unsigned int)((currentSceneIndex + 1) % scenes.size());
    goToScene(sceneIndex, transitionMode, timeInSeconds);
}

void XBSceneManager::goToPrevScene(SceneTransitionMode transitionMode, float timeInSeconds)
{
    unsigned int sceneIndex = (currentSceneIndex == 0) ? ((unsigned int)(scenes.size() - 1)) : ((unsigned int)(currentSceneIndex - 1));
    goToScene(sceneIndex, transitionMode, timeInSeconds);
}

void XBSceneManager::drawSceneAtIndex(int sceneIndex)
{
    if (sceneIndex >= scenes.size()) return;

    scenes[sceneIndex]->drawIntoFBO();
    const ofFbo &sceneFBO = scenes[sceneIndex]->getMainFBO();
    sceneFBO.draw(0, 0);
}

void XBSceneManager::onFadeComplete(float *arg)
{
    cout << "[END FADE TWEEN]" << endl;
    Tween *dstTween = Tweenzor::getTween(scenes[nextSceneIndex]->getFBOAlpha());
    Tweenzor::removeTween(scenes[nextSceneIndex]->getFBOAlpha());
    Tweenzor::removeCompleteListener(dstTween);

    state = SCENESTATE_OnScene;
    currentSceneIndex = nextSceneIndex;
}

// The code below is kept just as a reminder on how to create a GUI with ofxUI:
//void XBSceneManager::showAllScenes()
//{
//    gui = new ofxUISuperCanvas("SCENES", OFX_UI_FONT_MEDIUM);
//
//    gui->setColorBack(ofColor(0, 100, 127, 127));
//
//    gui->addSpacer();
//    for (int i=0; i<scenes.size(); ++i)
//    {
//        ofxUISlider *alphaSlider = gui->addSlider(scenes[i]->getName() + " alpha", 0.0, 255.0, scenes[i]->getFBOAlpha());
//        alphaSlider->setID(i);
//    }
//
//    gui->autoSizeToFitWidgets();
//
//    ofAddListener(gui->newGUIEvent, this, &XBSceneManager::handleGUIEvents);
//    gui->loadSettings(GUI_FILENAME);
//
//    gui->setVisible(true);
//}
//
//void XBSceneManager::handleGUIEvents(ofxUIEventArgs &e)
//{
//}
