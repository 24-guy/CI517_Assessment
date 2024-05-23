
//
//  XCube2d.cpp
//  GameEngineBase
//
// all code resources are taken from https://github.com/AlmasB/xcube2d/tree/master
//

#include "XCube2d.h"
#include <stdio.h>
#include <iostream>
using namespace std;


std::shared_ptr<XCube2Engine> XCube2Engine::instance = nullptr;

XCube2Engine::XCube2Engine()
{
    std::cout << "Initializing X-CUBE 2D v" << _ENGINE_VERSION_MAJOR << "." << _ENGINE_VERSION_MINOR << std::endl;

#ifdef __DEBUG
#if defined(_WIN32)
    debug("WIN32");
#elif defined(__linux__)
    debug("LINUX");
#elif defined(__APPLE__)
    debug("MACOSX");
#endif
#endif

    gfxInstance = std::shared_ptr<GraphicsEngine>(new GraphicsEngine());
#ifdef _DEBUG
    debug("GraphicsEngine() successful");
#endif
    
    eventInstance = std::shared_ptr<EventEngine>(new EventEngine());
#ifdef _DEBUG
    debug("EventEngine() successful");
#endif

    physicsInstance = std::shared_ptr<PhysicsEngine>(new PhysicsEngine());
#ifdef _DEBUG
    debug("PhysicsEngine() successful");
#endif

    menuInstance = std::shared_ptr<MyMenuSubsystem>(new MyMenuSubsystem()); //Custom Subsystem
#ifdef _DEBUG
    debug("MyMenuSubsystem() successful");
#endif

}

XCube2Engine::~XCube2Engine()
{
#ifdef __DEBUG
    debug("XCube2Engine::~XCube2Engine() started");
#endif
      

    gfxInstance.reset();
    eventInstance.reset();
    physicsInstance.reset();
    menuInstance.reset(); //Custom Subsystem

#ifdef __DEBUG
    debug("XCube2Engine::~XCube2Engine() finished");
#endif
}

void XCube2Engine::quit()
{
    if (instance)
        instance.reset();
}

std::shared_ptr<XCube2Engine> XCube2Engine::getInstance()
{
    if (!instance)
        instance = std::shared_ptr<XCube2Engine>(new XCube2Engine());
    return instance;
}
