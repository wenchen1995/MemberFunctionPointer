#include "MemberFunctionPointer.h"
#include <iostream>

using namespace std;
using namespace Private;

#pragma region Classes
class Top
{
public:
	int Top_i = 222;
	int TopFunc(int i)
	{
		cout << "TopFunc    this:" << this << "  Top_i:" << Top_i << "  i:" << i << endl;
		return i;
	}
	virtual int TopVFunc(int i)
	{
		cout << "TopVFunc    this:" << this << "  Top_i:" << Top_i << "  i:" << i << endl;
		return i;
	}
};

class Left :public Top
{
public:
	int Left_i = 55555;
	int LeftFunc(int i)
	{
		cout << "LeftFunc    this:" << this << "  Left_i:" << Left_i << "  i:" << i << endl;
		return i;
	}
};

class Right :public Top
{
public:
	int Right_i = 77777;
	int RightFunc(int i)
	{
		cout << "RightFunc    this:" << this << "  Right_i:" << Right_i << "  i:" << i << endl;
		return i;
	}
};

class Bottom :public Left, public Right
{
public:
	int Bottom_i = 99999;
	int BottomFunc(int i)
	{
		cout << "BottomFunc    this:" << this << "  Bottom_i:" << Bottom_i << "  i:" << i << endl;
		return i;
	}
};

class VLeft :public virtual Top
{
public:
	int VLeft_i = 66666;
	int VLeftFunc(int i)
	{
		cout << "VLeftFunc    this:" << this << "  VLeft_i:" << VLeft_i << "  i:" << i << endl;
		return i;
	}
};

class VRight :public virtual Top
{
public:
	int VRight_i = 54321;
	int VRightFunc(int i)
	{
		cout << "VRightFunc    this:" << this << "  VRight_i:" << VRight_i << "  i:" << i << endl;
		return i;
	}
};

class Bottom2 :public virtual VLeft, public virtual VRight
{
public:
	int Bottom2_i = 12345;
	int Bottom2Func(int i)
	{
		cout << "Bottom2Func    this:" << this << "  Bottom2_i:" << Bottom2_i << "  i:" << i << endl;
		return i;
	}

	 void AAA()
	{

	}
};


typedef int(Top::*TopMFP)(int);
typedef int(Left::*LeftMFP)(int);
typedef int(Right::*RightMFP)(int);
typedef int(Bottom::*BottomMFP)(int);
typedef int(VLeft::*VLeftMFP)(int);
typedef int(VRight::*VRightMFP)(int);
typedef int(Bottom2::*Bottom2MFP)(int);

#pragma endregion


void SI_MFP_Test()
{
	cout << "====================SI_MFP_Test====================" << endl;

	Left bottom, *p_bottom = &bottom;


	LeftMFP bottommfp = &Left::LeftFunc;
	MemberFunctionPointer mfp = bottommfp;

	void * pthis1 = mfp.Addressing(p_bottom);
	void * pthis2 = mfp.AutoAddressing(p_bottom);
	LeftMFP bottommfp2;
	mfp.ToNativeMFP(&bottommfp2);

	cout << "对象实际地址:" << p_bottom << endl;

	cout << "寻址:" << pthis1 << endl;
	cout << "自动寻址:" << pthis2 << endl;

	cout << "C++原生指针调用:" << endl;
	(p_bottom->*bottommfp)(1);

	cout << "转换为C++原生指针调用:" << endl;
	(p_bottom->*bottommfp2)(3);

	cout << "Call:" << endl;
	mfp.Call<int>(p_bottom, 5);

	cout << "==================SI_MFP_Test End==================" << endl;
}

void MI_MFP_Test()
{
	cout << "====================MI_MFP_Test====================" << endl;

	Bottom bottom, *p_bottom = &bottom;


	BottomMFP bottommfp = &Bottom::RightFunc;
	MemberFunctionPointer mfp = bottommfp;

	void * pthis1 = mfp.Addressing(p_bottom);
	void * pthis2 = mfp.AutoAddressing(p_bottom);
	BottomMFP bottommfp2;
	mfp.ToNativeMFP(&bottommfp2);

	cout << "对象实际地址:" << p_bottom << endl;

	cout << "寻址:" << pthis1 << endl;
	cout << "自动寻址:" << pthis2 << endl;

	cout << "C++原生指针调用:" << endl;
	(p_bottom->*bottommfp)(1);

	cout << "转换为C++原生指针调用:" << endl;
	(p_bottom->*bottommfp2)(3);

	cout << "Call:" << endl;
	mfp.Call<int>(p_bottom, 5);

	cout << "==================MI_MFP_Test End==================" << endl;
}

void VI_MFP_Test()
{
	cout << "====================VI_MFP_Test====================" << endl;

	Bottom2 bottom, *p_bottom = &bottom;


	Bottom2MFP bottommfp = &Bottom2::TopFunc;
	MemberFunctionPointer mfp = bottommfp;
	mfp = bottommfp;

	void * pthis1 = mfp.Addressing(p_bottom);
	void * pthis2 = mfp.AutoAddressing(p_bottom);
	Bottom2MFP bottommfp2;
	mfp.ToNativeMFP(&bottommfp2);

	cout << "对象实际地址:" << p_bottom << endl;

	cout << "寻址:" << pthis1 << endl;
	cout << "自动寻址:" << pthis2 << endl;

	cout << "C++原生指针调用:" << endl;
	(p_bottom->*bottommfp)(1);

	cout << "转换为C++原生指针调用:" << endl;
	(p_bottom->*bottommfp2)(3);

	cout << "Call:" << endl;
	mfp.Call<int>(p_bottom, 5);

	cout << "==================VI_MFP_Test End==================" << endl;
}

void Full_MFP_Test()
{

}

int main()
{
	VI_MFP_Test();
	SI_MFP_Test();
	MI_MFP_Test();
	//更多单元测试正在更新...
	return 0;
}