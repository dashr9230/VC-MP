/* -*- mode: c++; c-file-style: raknet; tab-always-indent: nil; -*- */
/**
 * @file AES128.h
 * @brief 128-bit Advanced Encryption Standard (Rjindael)
 *
 * Provide class AES128 for data encryption of 16 byte 
 * length block. 
 *
 * catid(cat02e@fsu.edu)
 *
 * 7/18/2004 Moved from old code
 * 9/5/2004 Created
 * 
 * Tabs: 4 spaces
 * Dist: public
 */
#ifndef AES_H
#define AES_H

/**
 * @brief 128-bit Advanced Encryption Standard.
 * 
 * A class providing encryption facilities. It provide 128-bits Advanced Encryption Standard. 
 */

class AES128
{

public:
	/**
	 * Set the current key 
	 * @param in_key The key to use for encryption 
	 */
	void set_key( const unsigned char in_key[ 16 ] );
	/**
	 * Crypt 16 byte of data 
	 * @param buffer 16 byte length buffer of data to crypt 
	 */
	void encrypt16( unsigned char buffer[ 16 ] );
	/**
	 * Decrypt 16 byte of data 
	 * @param buffer 16 byte length buffer of data to decrypt 
	 */
	void decrypt16( unsigned char buffer[ 16 ] );
	
protected:
	unsigned char GF2M( unsigned char k, unsigned char b );
	void AddRoundKey( unsigned char *m, unsigned char *rk );
	void ShiftRows( unsigned char *m );
	void iShiftRows( unsigned char *m );
	void Substitution( unsigned char *m );
	void iSubstitution( unsigned char *m );
	void MixColumns( unsigned char *m );
	void iMixColumns( unsigned char *m );
	unsigned int RolSubByte( unsigned int n );
	
private:
	unsigned char key_schedule[ 11 ][ 16 ];
	
};

#endif // AES_H
