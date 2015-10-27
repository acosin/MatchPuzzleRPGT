//
//  EnemyNode.cpp
//  MatchPuzzleRPGT
//

#include "EnemyNode.h"

EnemyNode::EnemyNode() :
mapEnemy(nullptr),
hpBar(nullptr)
{
    
}

EnemyNode::~EnemyNode()
{
    
}

bool EnemyNode::init()
{
    if (!Node::init())
    {
        return false;
    }
    
    auto node = CSLoader::createNode("ui/MapEnemyNode.csb");
    
    _panel_icon = dynamic_cast<ui::Layout*>(node->getChildByName("Panel_icon"));
    _panel_hp = dynamic_cast<ui::Layout*>(node->getChildByName("Panel_hp"));
    
    this->setContentSize(node->getContentSize());
    this->addChild(node);


    return true;
}

EnemyNode* EnemyNode::createNode(const std::string &enemyImage)
{
    auto node = EnemyNode::create();
    
    //auto texture = Director::getInstance()->getTextureCache()->getTextureForKey(enemyImage);
    //node->mapEnemy = Sprite::createWithTexture(texture);
    
    auto icon = Sprite::create(enemyImage);
    if (icon == nullptr) {
        return nullptr;
    }
    node->mapEnemy = icon;
    icon->setPosition(node->_panel_icon->getPosition());
    auto tempSize = node->_panel_icon->getContentSize();
    icon->setScale(tempSize.width/(icon->getContentSize().width),
                   tempSize.height/(icon->getContentSize().height));
    //node->_panel_icon->addChild(icon);
    node->addChild(icon, 1, 1);
    
    auto hpbar = HealthBar::create();
    node->hpBar = hpbar;
    tempSize = node->_panel_hp->getContentSize();
    hpbar->setPosition(node->_panel_hp->getPosition());
    hpbar->scaleSize(tempSize);
    //node->_panel_hp->addChild(node->hpBar);
    node->addChild(hpbar, 2,2);
    
    return node;
}


void EnemyNode::setPercentage(float percentage)
{
    hpBar->setPercentage(percentage);
    
}

float EnemyNode::getPercentage()
{
    return hpBar->getPercentage();
}

void EnemyNode::animateFromTo(float duration, float fromPercentage, float toPercentage)
{
    hpBar->animateFromTo(duration, fromPercentage, toPercentage);
}

