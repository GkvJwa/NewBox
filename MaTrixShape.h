// MaTrixShape.h: interface for the MaTrixShape class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MATRIXSHAPE_H__DCA57210_EEDF_4F97_A389_17E470DFD645__INCLUDED_)
#define AFX_MATRIXSHAPE_H__DCA57210_EEDF_4F97_A389_17E470DFD645__INCLUDED_

#define     COLOR     8
#define     TYPE      7
#define     CTRL      4

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

struct MaTrix
{
	int m_ttype[2];//¸÷ÖÖ
	int m_tshape[2];//ÐÎ×´
};

class MaTrixShape  
{
private:
	static int MTType[];
	MaTrix mt;

public:
	MaTrixShape();
	~MaTrixShape();

public:
	void IteratShape();
	void GetShape();
	void ChangeType();

	int * GetIteratorShape();
	int * GetNewShape();
	int * GetMTShape();
};

#endif // !defined(AFX_MATRIXSHAPE_H__DCA57210_EEDF_4F97_A389_17E470DFD645__INCLUDED_)
