#pragma once
#ifndef NAGYEGESZ_H
#define NAGYEGESZ_H

#include <iostream>

using namespace std;

class NagyEgesz
{
public:
	NagyEgesz();
	NagyEgesz(int, int, const int*);
	NagyEgesz(const NagyEgesz&);
	NagyEgesz(int);
	NagyEgesz(long);
	~NagyEgesz();
	NagyEgesz operator =(const NagyEgesz&);
	NagyEgesz operator +(const NagyEgesz&) const;
	NagyEgesz operator -(const NagyEgesz&) const;
	NagyEgesz& operator +=(const NagyEgesz&);
	NagyEgesz& operator -=(const NagyEgesz&);
	NagyEgesz& operator ++();
	NagyEgesz operator ++(int);
	NagyEgesz& operator --();
	NagyEgesz operator --(int);
	NagyEgesz operator *(const NagyEgesz&) const;
	NagyEgesz& operator *=(const NagyEgesz&);
	class NullavalValoOsztas {};
	NagyEgesz operator /(const NagyEgesz&) const;
	NagyEgesz& operator /=(const NagyEgesz&);
	NagyEgesz operator- () const
	{
		return NagyEgesz(*this * -1);
	}
	ostream& kiir(ostream& s) const;

private:
	NagyEgesz osszeg_elojel_nelkul(const NagyEgesz&, const NagyEgesz&) const;
	NagyEgesz kivonas_elojel_nelkul(const NagyEgesz&, const NagyEgesz&) const;
	bool operator <(const NagyEgesz&) const;

	int n, elojel;
	int* szamjegyek;
};

ostream& operator<<(ostream& s, const NagyEgesz& x);

#endif // !NAGYEGESZ_H
