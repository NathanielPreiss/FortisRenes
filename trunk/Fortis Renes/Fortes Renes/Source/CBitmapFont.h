//////////////////////////////////////////////////////////////////////////////
// File: "CBitmapFont.h"
//
// Date Edited: 10/14/2010
//
// Purpose: Singleton class to provide the game with bitmap fonts 
//			usable by all classes
//
//////////////////////////////////////////////////////////////////////////////

// Standard header protection
#ifndef CBITMAPFONT_H_
#define CBITMAPFONT_H_

// Nessisary includes
#include "windows.h"

//////////////////////////////////////////////////////////////////////////////
//	Class: CBitmapFont
//
//	Notes: Automaticly loads in default font but using load function
//		   will let user change the font they want to use
//////////////////////////////////////////////////////////////////////////////
class CBitmapFont
{
private:

	int m_nImageID;		// Texture ID
	int m_nCharWidth;	// Each chars width
	int m_nCharHeight;	// Each chars height
	int m_nNumRows;		// Number of rows in the image
	int m_nNumCols;		// Number of columns in the image
	float m_fUpdateAmount; // Amount text is being shifted by
 
	char m_cCharWidths[100];	// Each chars width

	char m_cStartChar;
	RECT CellAlgorithm(int id);
	
	// Constructor
	CBitmapFont(void);
	// Destructor
	~CBitmapFont(void) { }

public:

	// Singleton accessor
	static CBitmapFont* GetInstance(void);
	// Set member vars from file
	void Load(const char* szFileName, int nCharWidth, int nCharHeight, int nNumRows, int nNumCols, char cStartChar);
	// Special Effect
	void Update(float fElapsedTime);
	// Print out the string
	void Draw(const char* szText, int nPosX, int nPosY, float fScale, DWORD dwColor = 0xFFFFFFFF, bool bAnimate = false);
	// Print string from middle point
	void DrawCenter(const char* szText, int nPosX, int nPosY, float fScale, DWORD dwColor = 0xFFFFFFFF, bool bAnimate = false);
	// Setters
	void SetCharWidth(int nCharWidth)   { m_nCharWidth = nCharWidth; }
	void SetCharHeight(int nCharHeight) { m_nCharHeight = nCharHeight; }
	void SetNumRows(int nNumRows)		{ m_nNumRows = nNumRows; }
	void SetNumCols(int nNumCols)		{ m_nNumCols = nNumCols; }
	void SetStartChar(char nStartChar)   { m_cStartChar = nStartChar; }

	// Getters
	int GetImageID(void)	{ return m_nImageID; }
	int GetCharWidth(void)  { return m_nCharWidth; }
	int GetCharHeight(void) { return m_nCharHeight; }
	int GetNumRows(void)	{ return m_nNumRows; }
	int GetNumCols(void)	{ return m_nNumCols; }
	char GetStartChar(void)	{ return m_cStartChar; }
};
#endif