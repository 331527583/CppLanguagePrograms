#include "Handle.h"
#include <iostream>
#include <list>
using namespace std;

int main(int argc, char *argv[])
{
    Handle *h1 = new ConcreteHandleA();
    Handle *h2 = new ConcreteHandleB();
    h1->SetSuccessor(h2);
    h1->HandleRequest();

    cout << "//--------------------------------------------------\n"; //lizheng 2011-11-15 15:32:30
    //����������ӵģ����ܶ�ĳ������д���������һ�������У�����������ʱ���ҵ�һ���ܴ��������������
    //�����ж��������Ӧ����¼�����һ�㵱����¼�����ʱֻ��һ��������������ɡ�
    list<Handle *> listHandle;
    listHandle.push_back(h1);
    listHandle.push_back(h2);
    listHandle.push_back(new DefaultHandle);
    //��������¼����ҵ�ĳ����������¼�
    for(list<Handle *>::const_iterator  p = listHandle.begin(); p != listHandle.end(); p++)
    {
        int rt = (*p)->HandleMouseClick();
        if(rt == 1) //�ҵ��ö��󣬸ô�����¼��ѱ�����
        {
            break;
        }
    }

    system("pause");
    return 0;
}