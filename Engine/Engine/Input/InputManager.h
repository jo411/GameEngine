#pragma once
class InputManager
{
public:
	enum Key{A=0x41,B=0x42,C=0x43,D=0x44,E = 0x45,F = 0x46,G = 0x47,H = 0x48,I = 0x49,J = 0x4A,K = 0x4B,L = 0x4C,M = 0x4D,N = 0x4E,O = 0x4F,P = 0x50,Q = 0x51,R = 0x52,S = 0x53,T = 0x54,U = 0x55,V = 0x56,W = 0x57,X = 0x58,Y = 0x59,Z = 0x5A,NONE = 0x00};
	
	static Key lastKeyDown;//the last key that was pressed prior to this frame
	static Key lastKeyUp;//the last key released prior to this frame
	static bool isHeld;

	static void KeyCallback(unsigned int i_VKeyID, bool bWentDown);
	static inline bool isValidKey(int keyId);
};

