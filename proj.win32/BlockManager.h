#ifndef __BLOCK_MANAGER_H__
#define __BLOCK_MANAGER_H__

#include "cocos2d.h"
#include "Block.h"
#include "DisplayManager.h"

#define CELL_MATRIX_WIDTH 10
#define CELL_MATRIX_HEIGHT 15
#define DEFAULT_REFRESH_TIME 80

using namespace cocos2d;

class BlockManager:public CCNode
{
public: //系统调用
	
	BlockManager();
	~BlockManager();
	
	CREATE_FUNC(BlockManager);
	virtual bool init();

	virtual void update(float delta); //定时刷新函数

	virtual void pressedLeft();
	virtual void pressedRight();
	virtual void pressedDown();
	virtual void pressedUp();

public: //公有自定义函数
	int getUpdateTime(); //获取更新时间
	void bindDisplayManager(DisplayManger* manager);
	virtual CCPoint convertBlockToPixel(CCPoint blockPoint); //把网格坐标转化为实际坐标（右下角）
	
public:
	typedef enum
	{
		Empty,
		Dropping,
		Dead
	}CellState;

private: //私有自定义函数
	virtual Block* _createNewBlock(); //生成新的方块
	virtual void _pushNewBlock(); //生成新的nextBlock 修改Stage矩阵 并把原nextBlock推上舞台

	virtual bool _shouldBlockTryDrop(); //判断当前方块是否应该下落一次
	virtual void _donotTryDrop(); //不尝试下落
	virtual void _doTryDrop(); //尝试下落

	virtual bool _currentBlockCanMove(Block::Direction direction); //判断方块是否可以向特定方向移动
	virtual void _currentBlockDoMove(Block::Direction direction); //使当前方块移动
	virtual void _currentBlockStopDrop(); //停止当前方块下落

	virtual void _updateCellMatrixForMove(Block::Direction direction); //为Block移动更新单元矩阵
	virtual void _updateCellMatrixForDie(); //为Block死亡更新单元矩阵
	virtual int _eliminateLines(); //尝试消除
	virtual bool _canGameContinue(); //判断游戏可否继续进行，方块合法则修改单元矩阵
	virtual void _endGame(); //结束游戏

	virtual void _eliminateSingleLine(int lineNum); //消除单行（动画效果,清除数据等）
	virtual inline bool _isLineFilled(int linNum)
	{
		for (int i = 0; i < CELL_MATRIX_WIDTH; i++)
		{
			if (this->m_cellMatrix[linNum][i] != BlockManager::CellState::Dead)
			{
				return false;
			}
		}
		return true;
	} //判断该行是否已满
	virtual void _eliminateMultiLine(int startLine); //多行连续消除的动画
	virtual void _isTetris(int startLine); //Tetris动画
	virtual void _rePaintDeadBlocks(); //重绘dead blocks
	

private:
	int m_updateTime;

	Block* m_currentBlock;
	Block* m_nextBlock;

	CellState m_cellMatrix[CELL_MATRIX_WIDTH][CELL_MATRIX_HEIGHT];
	DisplayManger* m_displayManager;
	CCSpriteBatchNode* m_deadBlockBatch;

}; //class BlockManager

#endif //!__BLOCK_MANAGER_H__