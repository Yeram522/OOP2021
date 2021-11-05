#pragma once

#include "Position.h"
#include "Block.h"
#include "Score.h"
#include "Map.h"
#include "ConfirmationPanel.h"
#include "Button.h"


class TetrisGame :
    public Panel
{
    bool        isCompleted;
    bool        isPause;
    ConfirmationPanel* confirmationpanel;
    Score*      score;  // cache
    Map*        map;    // cache
    

public:
    TetrisGame() 
        : Panel("", Position{ 1, 1 }, 77, 30, nullptr), 
        isCompleted(false), isPause(false), score(nullptr), confirmationpanel(nullptr)
    {
        
        map = new Map{ Position{5,5}, 10, 20, this };
       
        auto block = new Block{ " \xdb \xdb\xdb\xdb", 
            Position{5,0},
            Dimension{3, 2},
            map
        }; // make a block to be a child of map object
        new Panel{ " Next", Position{25, 5}, 10, 5, this };
        score = new Score{ Position{4, 2}, 
            new Panel{ " Score", Position{25, 20}, 10, 5, this } 
        }; // create a ScorePanel and make a "score" its child.

        

        map->setScore(score);
        block->setMap(map);
    }

    bool isGameOver() const { return isCompleted; }
    bool isGameStop() const { return isPause; }
    void loadData()
    {
        map->loadMapData();
    }

    void update() override {
        EventType eventType = eventsystem->getCurrentEvenetType();

        if (isPause == true)
        {
            map->getfirstChild()->stop();
        }
        if (map->isDone()) {
            isCompleted = true;
            return;
        }
        
        if (input->getKey(VK_ESCAPE))
        {
            
            if (confirmationpanel != nullptr)
            {
                confirmationpanel->setActive(true);
                confirmationpanel->getParent()->setActive(true);
                isPause == true;
                return;
            }
            confirmationpanel = new ConfirmationPanel(Position{ 0,0 }, new Panel{ "ConfirmationPanel", Position{25,10 },  20, 10, this });
            new Button{Position{0,0},EventType::exitGame,new Panel{"==Exit", Position{5,2}, 10,2, confirmationpanel}};
            new Button{Position{0,0},EventType::continueGame,new Panel{"Continue", Position{5,7}, 10, 2, confirmationpanel}};

            isPause = true;
        }

        if (eventType != EventType::nothing) //Event가 들어오면,
        {     
            switch (eventType)
            {
            case EventType::exitGame:
                isCompleted = true;
                confirmationpanel->setActive(false);
                confirmationpanel->getParent()->setActive(false);
                eventsystem->setCurrentEventType();
                break;
            case EventType::continueGame:
                isPause = false;
                map->getfirstChild()->move();
                confirmationpanel->setActive(false);
                confirmationpanel->getParent()->setActive(false);
                eventsystem->setCurrentEventType();
                break;
            }
        }
            
    }
};

