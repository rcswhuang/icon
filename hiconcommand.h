#ifndef HICONCOMMAND_H
#define HICONCOMMAND_H
/*
 * 撤销、删除类
*/
#include <QUndoCommand>
class HIconMgr;
class HIconCommand : public QUndoCommand
{
public:
    enum Type{
        New = 0,            //新建
        Delete = 1,         //删除
        Paste = 2,          //粘贴
        Move = 3,           //移动
        Group = 4,          //组合
        UnGroup = 5,        //解除
        Rotate = 6,         //旋转
        Trun = 7,           //翻转
        Resize = 8,         //改变大小
        PatternSwitch = 9   //显示方案切换
    };

    HIconCommand(HIconMgr* iconMgr);
    ~HIconCommand();
public:
    virtual int id() const;
    virtual void redo();
    virtual void undo();
protected:
    HIconMgr* pIconMgr;
};

#endif // HICONCOMMAND_H
