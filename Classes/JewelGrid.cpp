//
//  JewelGrid.cpp
//  MatchPuzzleRPGT
//
//

#include "JewelGrid.h"

#include "Jewel.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

const std::string JewelsGrid::eventNameStatusChange = "event_JewelGridStatusChange";
const std::string JewelsGrid::EventName_FinishCrushingMatches = "event_FinishCrushingMatches";
const std::string JewelsGrid::EventName_FinishCrushingMatches_End = "event_FinishCrushingMatches_End";
const std::string JewelsGrid::EventName_FinishComboes = "event_FinishComboes";
const std::string JewelsGrid::EventName_FinishComboes_End = "event_FinishComboes_End";

JewelsGrid::~JewelsGrid()
{
    removeEventStatusChange();
    removeEventFinishComboesEnd();
}

// [TODO] may need modification to fulfill the latest style of memory management
JewelsGrid* JewelsGrid::create(int row, int col)
{
    auto jewelsgrid = new JewelsGrid();
    if (jewelsgrid && jewelsgrid->init(row, col))
    {
        jewelsgrid->autorelease();
        return jewelsgrid;
    }
    else
    {
        CC_SAFE_DELETE(jewelsgrid);
        return nullptr;
    }
}

bool JewelsGrid::init(int row, int col)
{
    Node::init();
    
    m_row = row;
    m_col = col;
    
    m_jewelSelected = nullptr;
    m_jewelSwapped = nullptr;
    
    //TODO: may add more operation here
    m_status = new JewelGridStatus();
    
    m_JewelsBox.resize(m_row);
    for (auto &vec : m_JewelsBox)
        vec.resize(m_col);
    
    //Create the jewel box according to the grid size
    //TODO: here create jewels randomly, may need other strategies
    //TODO: should use a factory method here
    for (int x = 0; x < m_col; x++)
    {
        for (int y = 0; y < m_row; y++)
        {
            m_JewelsBox[x][y] = createAJewel(x, y);
        }
    }
    
    while (isDeadMap())
    {
        //log("dead map! need to update");
        updateMap();
    }
    
    //加入触摸监听
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(JewelsGrid::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(JewelsGrid::onTouchMoved, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    regEventStatusChange();
    regEventFinishComboesEnd();
    
    log("JewelsGrid init!");
    return true;
}

//TODO: only for debug
void JewelsGrid::updateMap()
{
    for (int x = 0; x < m_col; x++)
    {
        for (int y = 0; y < m_row; y++)
        {
            m_JewelsBox[x][y]->removeFromParent();
            m_JewelsBox[x][y] = createAJewel(x, y);
        }
    }
    
    log("update a new map!");
}

//TODO: may not use later
bool JewelsGrid::isDeadMap()
{
    //simulate swapping, check isDeadMap by whether swappable
    //模拟交换，判断交换后是否能消除，如不能，那么就是个死图
    auto swap = [](Jewel** a, Jewel** b)
    {
        auto temp = *a;
        *a = *b;
        *b = temp;
    };
    
    bool isDeadMap = true;
    
    //traverse all jewels
    for (int x = 0; x < m_col; x++)
    {
        for (int y = 0; y < m_row; y++)
        {
            //swap with the left
            if (x > 0)
            {
                swap(&m_JewelsBox[x][y], &m_JewelsBox[x-1][y]);
                if (canCrush())
                    isDeadMap = false;
                swap(&m_JewelsBox[x][y], &m_JewelsBox[x-1][y]);
            }
            
            //swap with the right
            if (x < m_col - 1)
            {
                swap(&m_JewelsBox[x][y], &m_JewelsBox[x+1][y]);
                if (canCrush())
                    isDeadMap = false;
                swap(&m_JewelsBox[x][y], &m_JewelsBox[x+1][y]);
            }
            
            //swap with the one above
            if (y < m_row - 1)
            {
                swap(&m_JewelsBox[x][y], &m_JewelsBox[x][y+1]);
                if (canCrush())
                    isDeadMap = false;
                swap(&m_JewelsBox[x][y], &m_JewelsBox[x][y+1]);
            }
            
            //swap with the one below
            if (y > 0)
            {
                swap(&m_JewelsBox[x][y], &m_JewelsBox[x][y-1]);
                if (canCrush())
                    isDeadMap = false;
                swap(&m_JewelsBox[x][y], &m_JewelsBox[x][y-1]);
            }
        }
    }
    
    //canCrush would store jewels that can be crushed, for we just simulate here, clear operation is need
    //canCrush会存储能消除的宝石进去，由于是模拟交换，所以还要清空
    m_crushJewelBox.clear();
    tempComboes.clear();
    
    return isDeadMap;
}

// [TODO] random generation of jewel may results in the time and frame problems?
Jewel* JewelsGrid::createAJewel(int x, int y)
{
    //1. create a jewel according to x,y, random ElementType here
    //2. check isJewelLegal
    //3. set Pixel pos of the jewel
    //4, add to rendering node
    //1.根据布局坐标创建一颗宝石，类型随机
    //2.判断该宝石是否合法（不会三消）
    //3.设置该宝石的世界坐标
    //4.将该宝石加入渲染节点
    Jewel* jewel = nullptr;
    
    while(1)
    {
        jewel = Jewel::createByType(ElementType(random(FIRST_JEWEL_ID, LAST_JEWEL_ID)), x, y);
        
        if (isJewelLegal(jewel, x, y))
        {
            break;
        }
    }
    
    setJewelPixPos(jewel, x, y);
    addChild(jewel);
    
    //log("add a jewel!---type:%d---x:%d---y:%d", jewel->getType(), x, y);
    
    return jewel;
}

//TODO: may need modification of STEP 2!
bool JewelsGrid::isJewelLegal(Jewel* jewel, int x, int y)
{
    //1. check whether new jewel may match 3 in x/y direction
    //2. because we only add new jewel from the positive direction, check only need in the negative direction
    //3. x,y <= 1 discard (NOTE: need logic check!)
    //4. should be legal in both x and y axis
    
    //1.分别判断新加入的宝石在x轴y轴方向是否会三消
    //2.由于是从正方向加入宝石，因此只需往负方向判断
    //3.x，y坐标小于等于1不必判断
    //4.两轴同时合法方合法
    bool isXLegal = true;
    bool isYLegal = true;
    
    if (x > 1)
    {
        //check x axis in the negative direction
        if (jewel->getType() == m_JewelsBox[x-1][y]->getType() &&
            jewel->getType() == m_JewelsBox[x-2][y]->getType()
            )
        {
            isXLegal = false;
        }
        else
            isXLegal = true;
    }
    
    if (y > 1)
    {
        //check y axis in the negative direction
        if (jewel->getType() == m_JewelsBox[x][y-1]->getType() &&
            jewel->getType() == m_JewelsBox[x][y-2]->getType())
        {
            isYLegal = false;
        }
        else
            isYLegal = true;
    }
    
    return isXLegal && isYLegal;
}

void JewelsGrid::setJewelPixPos(Jewel* jewel, float x, float y)
{
    jewel->setPosition(x * GRID_WIDTH, y * GRID_WIDTH);
}

bool JewelsGrid::onTouchBegan(Touch* pTouch, Event* pEvent)
{
    if (!m_touchable) {
        return false;
    }
    
    auto pos = this->convertToNodeSpace(pTouch->getLocation());
    
    if (Rect(0, 0, m_col*GRID_WIDTH, m_row*GRID_WIDTH).containsPoint(pos))
    {
        int x = pos.x / GRID_WIDTH;
        int y = pos.y / GRID_WIDTH;
        
        m_jewelSelected = m_JewelsBox[x][y];
        
        //log("touch coordinate: x=%d,y=%d jewel's type:%d", x, y, m_jewelSelected->getType());
        
        return true;
    }
    else
    {
        return false;
    }
}

void JewelsGrid::onTouchMoved(Touch* pTouch, Event* pEvent)
{
    if (!m_jewelSelected)
    {
        return;
    }
    
    int startX = m_jewelSelected->getX();
    int startY = m_jewelSelected->getY();
    
    auto pos = this->convertToNodeSpace(pTouch->getLocation());
    int touchX = pos.x / GRID_WIDTH;
    int touchY = pos.y / GRID_WIDTH;
    
    //if touchPoint not in the grid || the same one as selected, return
    if (!Rect(0, 0, m_col*GRID_WIDTH, m_row*GRID_WIDTH).containsPoint(pos) || Vec2(touchX, touchY) == Vec2(startX, startY))
    {
        return;
    }
    
    //check if touch one and selected one are neighbourhood
    //TODO: may modify the logic here!s
    //判断已选宝石的布局坐标与触摸点的布局坐标是否直角相隔一个单位
    if (abs(startX - touchX) + abs(startY - touchY) != 1)
    {
        //log("touch pos not on border");
        return;
    }
    
    //the rest conditions are trying to swap jewels
    //余下的情况，触摸点上面的宝石就是欲进行交换的宝石
    //通过坐标索引，获取欲交换的宝石
    m_jewelSwapped = m_JewelsBox[touchX][touchY];
    
    //start swapping
    //交换宝石，开启交换状态捕捉函数（在交换完成后，判断是否可以消除）
    swapJewels(m_jewelSelected, m_jewelSwapped);
    schedule(schedule_selector(JewelsGrid::onJewelsSwaping));
}

void JewelsGrid::swapJewels(Jewel *jewelA, Jewel *jewelB)
{
    // start swapping, pauseTouchEvent
    _eventDispatcher->pauseEventListenersForTarget(this); //交换开始，关闭触摸监听
    
    //1. swap the jewel pointer in the m_JewelsBox
    //2. swap the coordinates of the jewels
    //3. move the jewel to new position
    
    //1.交换宝石容器内的宝石指针
    //2.交换宝石坐标
    //3.宝石移动到新的位置
    auto temp = m_JewelsBox[jewelA->getX()][jewelA->getY()];
    m_JewelsBox[jewelA->getX()][jewelA->getY()] = m_JewelsBox[jewelB->getX()][jewelB->getY()];
    m_JewelsBox[jewelB->getX()][jewelB->getY()] = temp;
    
    auto tempX = jewelA->getX();
    jewelA->setX(jewelB->getX());
    jewelB->setX(tempX);
    
    auto tempY = jewelA->getY();
    jewelA->setY(jewelB->getY());
    jewelB->setY(tempY);
    
    swapJewelToNewPos(jewelA);
    swapJewelToNewPos(jewelB);
}

void JewelsGrid::swapJewelToNewPos(Jewel* jewel)
{
    jewel->setSwapingState(true);
    auto move = MoveTo::create(MOVE_SPEED, Vec2(jewel->getX() * GRID_WIDTH, jewel->getY() * GRID_WIDTH));
    auto call = CallFunc::create([jewel](){
        jewel->setSwapingState(false);
    });
    jewel->runAction(Sequence::create(move, call, nullptr));
}

bool JewelsGrid::canCrush()
{
    //combo count
    int count = 0; //连续数
    Jewel *JewelBegin = nullptr; //起始遍历的宝石
    Jewel *JewelNext = nullptr; //从起始宝石开始往前遍历的宝石
    
    //TODO: release later
    auto matchCombo = new MatchCombo();
    
    //traversal every col
    for (int x = 0; x < m_col; x++)
    {
        for (int y = 0; y < m_row - 1;)
        {
            count = 1;
            JewelBegin = m_JewelsBox[x][y];
            JewelNext = m_JewelsBox[x][y + 1];
            
            while (JewelBegin->getType() == JewelNext->getType())
            {
                count++;
                int nextIndex = y + count;
                if (nextIndex > m_row - 1)
                    break;
                JewelNext = m_JewelsBox[x][nextIndex];
            }
            if (count >= 3)
            {
                // TODO: Update JewelGridStatus(match a col)
                auto colMatch = MatchedJewels::createMatchCol(x, y, y+count-1, JewelBegin->getType());
                matchCombo->addMatch(colMatch);
                for (int n = 0; n < count; n++)
                {
                    auto jewel = m_JewelsBox[x][y+n];
                    m_crushJewelBox.pushBack(jewel);
                }
            }
            y += count;
        }
    }
    
    //travese every row
    for (int y = 0; y < m_row; y++)
    {
        for (int x = 0; x < m_col - 1;)
        {
            count = 1;
            JewelBegin = m_JewelsBox[x][y];
            JewelNext = m_JewelsBox[x+1][y];
            
            while (JewelBegin->getType() == JewelNext->getType())
            {
                count++;
                int nextIndex = x + count;
                if (nextIndex > m_col - 1)
                    break;
                JewelNext = m_JewelsBox[nextIndex][y];
            }
            if (count >= 3)
            {
                // TODO: Update JewelGridStatus(match a row)
                auto rowMatch = MatchedJewels::createMatchRow(y, x, x+count-1, JewelBegin->getType());
                matchCombo->addMatch(rowMatch);

                for (int n = 0; n < count; n++)
                {
                    auto jewel = m_JewelsBox[x+n][y];
                    //there may be some jewels crush in both row and col, need check
                    //有可能有宝石同时行列可消除，那么不能重复存储到消除宝石盒子，故需添加一次判断
                    if (m_crushJewelBox.find(jewel) != m_crushJewelBox.end())
                    {
                        continue;
                    }
                    m_crushJewelBox.pushBack(jewel);
                }
            }
            x += count;
        }
    }
    
    if (!m_crushJewelBox.empty())
    {
        if (matchCombo->getMatchedCount() > 0) {
            tempComboes.push_back(matchCombo);
        }
        return true;
    }
    else
    {
        return false;
    }
}

void JewelsGrid::goCrush()
{
    for (auto combo : tempComboes)
    {
        m_status->addCombo(combo);
    }
    tempComboes.clear();
    
    for (auto jewel : m_crushJewelBox)
    {
        //generate new jewel with random type, initial pos is above the top row
        //生成新的宝石，类型随机，初始位置在最上面一行的上边一行（布局外一格）
        auto newJewel = Jewel::createByType((ElementType)random(FIRST_JEWEL_ID, LAST_JEWEL_ID), jewel->getX(), m_row);
        setJewelPixPos(newJewel, newJewel->getX(), m_row);
        addChild(newJewel);
        
        m_newJewelBox.pushBack(newJewel);
        
        m_JewelsBox[jewel->getX()][jewel->getY()] = nullptr;
        
        jewel->crush();
    }
    
    //TODO: dispatch here for every combo now!!!!
    //dispatchEventStatusChange();

}

void JewelsGrid::refreshJewelsGrid()
{
    for (int x = 0; x < m_col; x++)
    {
        int empty_count = 0; //empty count of a row
        
        for (int y = 0; y < m_row; y++)
        {
            auto jewel = m_JewelsBox[x][y];
            if (!jewel)
                empty_count++;
        }
        if (empty_count > 0)
        {
            //log("the %d col has %d empty", x, empty_count);
            refreshJewelsToNewPos(x);
        }
    }
}

void JewelsGrid::refreshJewelsToNewPos(int col)
{
    //刷新该列上面的宝石
    //refresh jewel above the col
    
    //empty count of current traversal
    int n = 0; //当前遍历到的空位数
    auto pJewelsbox = &m_JewelsBox; //保存一个宝石盒子的指针，这是为了让其能传入lamda
    
    //drop existing jewels
    //先让现有的宝石下落
    for (int y = 0; y < m_row; y++)
    {
        auto jewel = m_JewelsBox[col][y];
        
        if (!jewel)
        {
            n++;
            continue;
        }
        else if (n != 0)
        {
            jewel->setY(jewel->getY() - n);
            auto move = MoveBy::create(0.2, Vec2(0, -n*GRID_WIDTH));
            auto call = CallFunc::create([pJewelsbox, jewel](){
        
                (*pJewelsbox)[jewel->getX()][jewel->getY()] = jewel;
            });
            
            jewel->runAction(Sequence::create(move, call, nullptr));
        }
    }
    
    //drop new jewels
    //再让新宝石下落
    int i = n;
    int delta = 1;
    
    for (auto jewel : m_newJewelBox)
    {
        if (jewel->getX() == col)
        {
            jewel->setY(m_row - i);
            
            auto delay = DelayTime::create(0.2);
            //speed down the jewels which drop later
            //后下落的速度设置慢一些
            auto move = MoveBy::create(0.2*delta++, Vec2(0, -i--*GRID_WIDTH));
            auto call = CallFunc::create([jewel, pJewelsbox, this](){
                (*pJewelsbox)[jewel->getX()][jewel->getY()] = jewel;
                //从新宝石盒子中移除该宝石
                m_newJewelBox.eraseObject(jewel);
            });
            
            jewel->runAction(Sequence::create(delay, move, call, nullptr));
        }
    }
}

void JewelsGrid::onJewelsSwaping(float dt)
{
    //捕捉两个正在交换的宝石的交换动作是否已经停止，如果没停止，返回继续捕捉
    if (m_jewelSelected->isSwaping() || m_jewelSwapped->isSwaping())
    {
        return;
    }
    // if swapping action finished
    //如果宝石交换动作执行完毕
    else
    {
        unschedule(schedule_selector(JewelsGrid::onJewelsSwaping));
        
        //log("swap over!");
        
        //log("is it can crush?");
        
        //check if current state can crush
        //判断是否当前状态可以消除
        if (canCrush())
        {
            //log("yes,crush!");
            
            m_jewelSelected = nullptr;
            
            // start crushing
            //开始消除，开启消除状态捕捉函数(捕捉到消除完毕后，刷新布局)，这一轮消除正式开始
            //SimpleAudioEngine::getInstance()->playEffect("crush.ogg");
            goCrush();
            schedule(schedule_selector(JewelsGrid::onJewelsCrushing));
        }
        else
        {
            //log("no, cant crush!");
            //cannot crush
            //不能消除，交换回去，开启交换返回时的捕捉函数(捕捉到消除完毕后，开启触摸接听)
            //SimpleAudioEngine::getInstance()->playEffect("swapback.ogg");
            swapJewels(m_jewelSelected, m_jewelSwapped);
            schedule(schedule_selector(JewelsGrid::onJewelsSwapingBack));
        }
    }
}

void JewelsGrid::onJewelsSwapingBack(float dt)
{
    if (m_jewelSelected->isSwaping() || m_jewelSwapped->isSwaping())
    {
        return;
    }
    else
    {
        unschedule(schedule_selector(JewelsGrid::onJewelsSwapingBack));
        
        //log("swap back!");
        
        m_jewelSelected = nullptr;
        
        _eventDispatcher->resumeEventListenersForTarget(this);
    }
}

void JewelsGrid::onJewelsCrushing(float dt)
{
    for (auto jewel : m_crushJewelBox)
    {
        if (jewel->isCrushing())
        {
            //log("crushing");
            return;
        }
    }
    
    //if (!m_isFinishCrushingMatches_End) {
      //  return;
    //}
    
    
    // if all jewels finish crushing, stop the catch function
    //如果全部宝石已经消除完毕，停止捕捉函数
    unschedule(schedule_selector(JewelsGrid::onJewelsCrushing));
    
    dispatchEventStatusChange();
    
    
    /*
    m_crushJewelBox.clear();
    
    //log("crush over!");
    //log("begin to refresh!");
    
    
    //刷新宝石阵列，并开启刷新状态捕捉函数（刷新一遍结束，重新判断新阵列是否可消除）
    refreshJewelsGrid();
    schedule(schedule_selector(JewelsGrid::onJewelsRefreshing));
    */
    
}

void JewelsGrid::onJewelsRefreshing(float dt)
{
    if (m_newJewelBox.size() != 0)
    {
        //log("refreshing!");
        return;
    }
    else
    {
        unschedule(schedule_selector(JewelsGrid::onJewelsRefreshing));
        
        //log("refresh over!");
        //log("and now, is it can crush?");
        
        if (canCrush())
        {
            //log("yes, crush again!");
            
            //SimpleAudioEngine::getInstance()->playEffect("crush.ogg");
            goCrush();
            schedule(schedule_selector(JewelsGrid::onJewelsCrushing));
        }
        else
        {
            //log("no, cant crush! over!");
            
            // check if isDeadMap, if it is, update
            //判断是否为死图，如果是，则执行一段文字动画，提示即将更新地图
            if (isDeadMap())
            {
                //log("cant crush any more, updating a new map!");
                
                auto winSize = Director::getInstance()->getWinSize();
                auto label = Label::createWithTTF("Cant Crush Any More, Change!", "fonts/Marker Felt.ttf", 24);
                label->setTextColor(Color4B::BLACK);
                label->setPosition(winSize.width / 2, winSize.height / 2);
                label->setOpacity(0);
                this->getParent()->addChild(label);
                
                //提示文字淡入淡出后，更新地图，再开启触摸监听
                auto fadein = FadeIn::create(0.5);
                auto fadeout = FadeOut::create(0.5);
                
                auto call = CallFunc::create([this, label](){
                    do
                    {
                        updateMap();
                    } while (isDeadMap());
                    
                    label->removeFromParent();
                    
                    _eventDispatcher->resumeEventListenersForTarget(this);
                });
                
                label->runAction(Sequence::create(fadein, DelayTime::create(2), fadeout, call, nullptr));
            }
            else
            {
                // if not a dead map
                
                
                
                //NOTE: should make sure that here only be called only once!!!
                dispatchEventFinishComboes();
                
                m_status->clearCombo();
                
                //如果不是死图，那么就直接开启触摸监听，等待下一轮的交互操作
                _eventDispatcher->resumeEventListenersForTarget(this);
            }
        }
    }
}

void JewelsGrid::dispatchEventStatusChange(CallFunc *callback)
{
    if (!isDispatchStatusChange)
        return;
    
    //m_isFinishCrushingMatches_End = false;
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    dispatcher->dispatchCustomEvent(JewelsGrid::EventName_FinishCrushingMatches, callback);
}

void JewelsGrid::startDispatchStatusChange()
{
    isDispatchStatusChange = true;
}
void JewelsGrid::stopDispatchStatusChange()
{
    isDispatchStatusChange = false;
}

int JewelsGrid::getStatusYCombo()
{
    if (!m_status) {
        return -1;
    } else {
        return m_status->getRowCount();
    }
}

int JewelsGrid::getStatusXCombo()
{
    if (!m_status) {
        return -1;
    } else {
        return m_status->getColCount();
    }
}


PuzzleStatusChangeData* JewelsGrid::createPuzzleStatusChangeData()
{
    if (!m_status) {
        return nullptr;
    } else {
        return PuzzleStatusChangeData::create(m_status);
    }
}

void JewelsGrid::disableTounch()
{
    m_touchable = false;
}

void JewelsGrid::enableTouch()
{
    m_touchable = true;
}

void JewelsGrid::regEventStatusChange()
{
    auto listenner =EventListenerCustom::create(JewelsGrid::EventName_FinishCrushingMatches_End,
                                                CC_CALLBACK_1(JewelsGrid::onEventName_FinishCrushingMatches_End, this));
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    dispatcher->addEventListenerWithFixedPriority(listenner, 100);
}

void JewelsGrid::removeEventStatusChange()
{
    getEventDispatcher()->removeCustomEventListeners(JewelsGrid::EventName_FinishCrushingMatches_End);
}

void JewelsGrid::onEventName_FinishCrushingMatches_End(EventCustom* pEvent)
{
   // m_isFinishCrushingMatches_End = true;
    m_crushJewelBox.clear();
    //log("crush over!");
    //log("begin to refresh!");
    //刷新宝石阵列，并开启刷新状态捕捉函数（刷新一遍结束，重新判断新阵列是否可消除）
    refreshJewelsGrid();
    schedule(schedule_selector(JewelsGrid::onJewelsRefreshing));
    
}

void JewelsGrid::dispatchEventFinishComboes(CallFunc *callback)
{
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    dispatcher->dispatchCustomEvent(JewelsGrid::EventName_FinishComboes, callback);

}

void JewelsGrid::regEventFinishComboesEnd()
{
    auto listenner =EventListenerCustom::create(JewelsGrid::EventName_FinishComboes_End,
                                                CC_CALLBACK_1(JewelsGrid::onEventName_FinishComboes_End, this));
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    dispatcher->addEventListenerWithFixedPriority(listenner, 100);
}

void JewelsGrid::removeEventFinishComboesEnd()
{
    getEventDispatcher()->removeCustomEventListeners(JewelsGrid::EventName_FinishComboes_End);
}

void JewelsGrid::onEventName_FinishComboes_End(EventCustom* pEvent)
{
    // TODO: show damage animation
}


