//////////////////////////////////////////////////////////////////////////////
// File: "CBitmapFont.cpp"
//
// Date Edited: 10/14/2010
//
// Purpose: Fill fucntions declared in "CBitmapFont.h"
//
//////////////////////////////////////////////////////////////////////////////

#include "DirectX Wrappers/CSGD_TextureManager.h"
#include "CBitmapFont.h"

////////////////////////////////////////////////////////
// Function: CBitmapFont
// Paramaters: void
// Returns: void
////////////////////////////////////////////////////////
CBitmapFont::CBitmapFont(void)
{
	m_nImageID = CSGD_TextureManager::GetInstance()->LoadTexture("Resource/Graphics/Font.png");
	m_nCharWidth = 32;
	m_nCharHeight = 32;
	m_nNumRows = 10;
	m_nNumCols = 10;
	m_cStartChar = 28;
	m_fUpdateAmount = 0;

	char temp[100] =			  {0, 0, 0, 0, 0, 8, 0, 0, 21, 0,
								  26, 0, 13, 12, 18, 24, 12, 10, 10, 16,
								  19, 14, 20, 19, 21, 20, 21, 20, 20, 20,
								  10, 0, 0, 0, 0, 18, 0, 32, 29, 26,
								  28, 27, 23, 29, 30, 15, 18, 30, 27, 26,
								  30, 27, 25, 29, 29, 23, 28, 28, 31, 
								  30, 29, 27, 0, 0, 0, 0, 0, 0, 0, 20,
								  20, 19, 21, 18, 20, 22, 23, 15, 14, 24,
								  13, 32, 24, 21, 21, 22, 17, 16, 15, 23,
								  21, 28, 26, 21, 23, 0, 0, 0, 0, 0};
	for(int i = 0; i < 100; i++)
		m_cCharWidths[i] = temp[i];

}
////////////////////////////////////////////////////////
// Function: Load
// Paramaters: const char* szFileName - File to load
//			   int nCharWidth - Width of char
//			   int nCharHeight - Height of char
//			   int nNumRows - Number of rows of chars
//			   int nNumCols - Number of columns of chars
//			   char cStartChar - What character the image starts at
//
// Returns: void
////////////////////////////////////////////////////////
void CBitmapFont::Load(const char* szFileName, int nCharWidth, int nCharHeight, int nNumRows, int nNumCols, char cStartChar)
{
	CSGD_TextureManager::GetInstance()->UnloadTexture(m_nImageID);
	m_nImageID = CSGD_TextureManager::GetInstance()->LoadTexture(szFileName);
	m_nCharWidth = nCharWidth;
	m_nCharHeight = nCharHeight;
	m_nNumRows = nNumRows;
	m_nNumCols = nNumCols;
	m_cStartChar = cStartChar;
}
////////////////////////////////////////////////////////
// Function: Update
// Paramaters: float fElapsedTime - Time since last update
// Returns: void
////////////////////////////////////////////////////////
void CBitmapFont::Update(float fElapsedTime)
{
	// Static amount to update by (Pixels/Second)
	static float fUpdateBy = 15.0f;		

	// Update amount
	m_fUpdateAmount += fUpdateBy * fElapsedTime;
	
	// Changes direction of update
	if(m_fUpdateAmount > 5.0f)
	{
		m_fUpdateAmount = 5;
		fUpdateBy = -15;
	}
	else if(m_fUpdateAmount < -10.0f)
	{
		m_fUpdateAmount = -10.0f;
		fUpdateBy = 15;
	}
}
////////////////////////////////////////////////////////
// Function: GetInstance
// Paramaters: void
// Returns: CBitmapFont* instance - Singleton instance of the class
////////////////////////////////////////////////////////
CBitmapFont* CBitmapFont::GetInstance(void)
{
	static CBitmapFont instance;
	return &instance;
}
////////////////////////////////////////////////////////
// Function: Draw
// Paramaters:  const char* szText - Text to render to the screen
//				int nPosX - Left position to render the text
//				int nPosY - Top position to render the text
//				float fScale - Amount to scale the text by
//				DWORD dwColor - Color to make invisible
//				bool bAnimate - Wether or not animate text
// Returns: void
////////////////////////////////////////////////////////
void CBitmapFont::Draw(const char* szText, int nPosX, int nPosY, float fScale, DWORD dwColor, bool bAnimate)
{
	int nOrigonalX = nPosX;

	if(bAnimate)
		nPosY += (int)m_fUpdateAmount;

	// Go through string one char at a time
	int nLength = strlen(szText);
	for(int i = 0; i < nLength; i++ )
	{
		// Get the har
		char ch = szText[i];
		// check for special chars
		if(ch == ' ')
		{
			nPosX += (int)((m_nCharHeight/2)*fScale);
			continue;
		}
		else if(ch == '\n')
		{
			nPosX = nOrigonalX;
			nPosY += (int)(m_nCharHeight*fScale);
			continue;
		}
		// Make the char an ID
		int id = ch - m_cStartChar;
		// Get the letter rect based on the ID
		RECT rLetter = CellAlgorithm(id);

		CSGD_TextureManager::GetInstance()->Draw(m_nImageID, nPosX, nPosY, fScale, fScale,
												 &rLetter, 0, 0, 0, dwColor);

		nPosX += (int)((m_cCharWidths[id])*fScale);
	}
}
void CBitmapFont::DrawCenter(const char* szText, int nPosX, int nPosY, float fScale, DWORD dwColor, bool bAnimate)
{
	int nLength = strlen(szText);

	int nOrigonalX = nPosX;
	for(int i = 0; i < nLength; i++)
	{
		char ch = szText[i];
		if( ch == '\n')
			break;
		if( ch == ' ')
		{
			nOrigonalX -= (int)((m_nCharWidth/2)*fScale);
			continue;
		}
		int id = ch - m_cStartChar;
		nOrigonalX -= (int)((m_cCharWidths[id]*fScale)*0.5f);
	}
	nPosX = nOrigonalX;

	if(bAnimate)
		nPosY += (int)m_fUpdateAmount;

	// Go through string one char at a time
	for(int i = 0; i < nLength; i++ )
	{
		// Get the har
		char ch = szText[i];
		// check for special chars
		if(ch == ' ')
		{
			nPosX += (int)(m_nCharWidth*fScale);
			continue;
		}
		else if(ch == '\n')
		{
			nPosX = nOrigonalX;
			nPosY += (int)(m_nCharHeight*fScale);
			continue;
		}
		// Make the char an ID
		int id = ch - m_cStartChar;
		// Get the letter rect based on the ID
		RECT rLetter = CellAlgorithm(id);

		CSGD_TextureManager::GetInstance()->Draw(m_nImageID, nPosX, nPosY, fScale, fScale,
												 &rLetter, 0, 0, 0, dwColor);

		nPosX += (int)(m_cCharWidths[id]*fScale);
	}
}
////////////////////////////////////////////////////////
// Function: CellAlgorithm 
// Paramaters: int id - Character value to get image rect for
// Returns: RECT tLetterBox - Area of image the text resides
////////////////////////////////////////////////////////
RECT CBitmapFont::CellAlgorithm(int id)
{
	RECT tLetterBox;

	tLetterBox.left = (id % m_nNumCols) * m_nCharWidth;
	tLetterBox.top  = (id / m_nNumCols) * m_nCharHeight;
	tLetterBox.right = tLetterBox.left + m_nCharWidth;
	tLetterBox.bottom = tLetterBox.top + m_nCharHeight;

	return tLetterBox;
}