#pragma once

#include "Position.h"
#include "Map.h"
#include "Button.h"
#include "Data.h"

//Tetris Map Editing Program

class TetrisMapMaker :
    public Panel
{
    bool        isCompleted;
    Map*        map;    // cache
    
public:
    TetrisMapMaker() 
        : Panel("", Position{ 1, 1 }, 77, 30, nullptr), 
        isCompleted(false)
    {      
        map = new Map{ Position{5,5}, 10, 20, this };
        
        new Button{ Position{0,0},EventType::saveGame,new Panel{"Save", Position{20,2}, 10, 2, this} };
        new Button{ Position{0,0},EventType::exitGame,new Panel{"Exit", Position{20,7}, 10,2, this} };
        new Button{ Position{0,0},EventType::loadData,new Panel{"Load", Position{20,12}, 10,2, this} };
    }

    bool isGameOver() const { return isCompleted; }

    void update() override {
        EventType eventType = eventsystem->getCurrentEvenetType();
        Position mousepos = input->getMousePosition();

        if (input->getMouseButtonDown(0))
        {
            if (!map->isValidRange(mousepos)) return;
            if (map->deleteObstacle(mousepos)) return;
            map->place(mousepos);
        }

        if (eventType != EventType::nothing) //Event가 들어오면,
        {     
            switch (eventType)
            {
            case EventType::exitGame:
                isCompleted = true;
                
                eventsystem->setCurrentEventType();
                break;
            case EventType::saveGame:
                saveMapdata(map->getShape(),10*20);
                eventsystem->setCurrentEventType();
                break;
            case EventType::loadData:
                //if (loadMapdata() == nullptr)break;
                map->setShape(loadMapdata());
                eventsystem->setCurrentEventType();
                break;
            }
        }
            
    }
};

