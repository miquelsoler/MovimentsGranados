//
// Created by Miquel Àngel Soler on 12/1/16.
//

#include "XBScene3GUI.h"

XBScene3GUI::XBScene3GUI() : XBBaseGUI()
{
    sceneSettingsFilename = "scene3.xml";
    colorSettingsFilename = "colors3.xml";
}

void XBScene3GUI::setup()
{
    XBBaseGUI::setup();

    creaturesGroup.setup("Violin & cello");
    creaturesGroup.add(maxSpeed.setup("Speed", 4.0, 0.0, 10));
    creaturesGroup.add(maxForce.setup("Force", 0.10, 0.00, 1.00));
    creaturesGroup.add(pathSpeed.setup("Path increment", 1.0, 0.0, 5.0));
    creaturesGroup.add(stiffness.setup("stiffness", 0.05, 0.00, 0.50));
    creaturesGroup.add(damping.setup("damping", 0.75, 0.00, 1.00));
    creaturesGroup.add(mass.setup("mass", 1.0, 0.0, 10.0));

    sceneGui.add(&creaturesGroup);
    
    particlesGroup.setup("Particles");
    particlesGroup.add(particleSize.setup("Particle size", 10, 2, 40));
    particlesGroup.add(particleLife.setup("Particle life", 30, 1, 60));
    particlesGroup.add(particleVelocity.setup("Particle velocity", ofVec2f(0,50), ofVec2f(0,0), ofVec2f(150,150)));
    particlesGroup.add(particleSpread.setup("Particle spread", ofVec2f(80,5), ofVec2f(0,0), ofVec2f(150,150)));
    sceneGui.add(&particlesGroup);
    
    pianoGroup.setup("Paino");
    pianoGroup.add(stoneGrowFactor.setup("stone grow speed", 0.025, 0.000, 0.5));
    pianoGroup.add(stoneAlphaDecrease.setup("stone alpha speed", 2.3, 1, 20));
    pianoGroup.add(stoneTime.setup("stone time", 2, 0.0, 4.0));
    sceneGui.add(&pianoGroup);
    
    directorGroup.setup("Director");
    directorGroup.add(lineWidth.setup("Line width", 4.0f, 1.0f, 40.0f));
    directorGroup.add(minPeriod.setup("Min wave period", 800.0f, 200.0f, 2000.0f));
    directorGroup.add(maxPeriod.setup("Max wave period",  1600, 200.0, 3000.0));
    
    directorGroup.add(attractorStrength.setup("attractorStrength",  7, 0.0, 10.0));
    directorGroup.add(attractorRadius.setup("attractorRadius", 10.0f, 0.00, 14.00));
    sceneGui.add(&directorGroup);

    sceneGui.add(blurAmount.setup("Blur amount", 1., 0, 8.));

    loadSettings();
}
