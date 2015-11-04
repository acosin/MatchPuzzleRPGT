//
//  ScoreBoard.cpp
//  MatchPuzzleRPGT
//

#include "ScoreBoard.h"

ScoreBoard::ScoreBoard()
{
    
}

ScoreBoard::~ScoreBoard()
{
    
}

bool ScoreBoard::init()
{
    if (!Node::init())
    {
        return false;
    }
    
    auto node = CSLoader::createNode("ui/ScoreBoard.csb");
    _text = dynamic_cast<ui::Text*>(node->getChildByName("Text"));
    
    setScore(0);
    
    
    
    
    auto size = node->getContentSize();
    this->setContentSize(size);
    this->addChild(node);
    
    
    return true;

}

ScoreBoard* ScoreBoard::createScoreBoard(const std::string &enemyImage)
{
    
}

void ScoreBoard::setScore(int score)
{
    _score = score;
    
    _text->setString("Score: "+Value(_score).asString());
}

int ScoreBoard::getScore()
{
    return _score;
}
