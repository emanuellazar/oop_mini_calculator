#include "NagyEgesz.h"
#include <iostream>

using namespace std;

NagyEgesz::NagyEgesz()
{
	n = 1;
	elojel = 0;
	szamjegyek = new int[n];
	szamjegyek[0] = 0;
}

NagyEgesz::NagyEgesz(int elojel, int n, const int* szamjegyek)
{
	NagyEgesz::elojel = elojel;
	NagyEgesz::n = n;
	NagyEgesz::szamjegyek = new int[n];
	for (int i = 0; i < n; i++)
	{
		NagyEgesz::szamjegyek[i] = szamjegyek[i];
	}
}

NagyEgesz::NagyEgesz(const NagyEgesz& c)
{
	elojel = c.elojel;
	n = c.n;
	szamjegyek = szamjegyek = new int[n];
	for (int i = 0; i < n; i++)
	{
		szamjegyek[i] = c.szamjegyek[i];
	}
}

NagyEgesz::NagyEgesz(int szam)
{
	if (szam < 0)
	{
		elojel = -1;
		szam *= -1;
	}
	else if (szam > 0)
	{
		elojel = 1;
	}
	else
	{
		elojel = 0;
	}

	int m = 0;
	long long uj = 0;
	while (szam != 0)
	{
		m++;
		uj *= 10;
		uj += szam % 10;
		szam /= 10;
	}
	n = m;
	szamjegyek = new int[n];
	int i = 0;
	while (uj > 0)
	{
		szamjegyek[i] = uj % 10;
		m--;
		i++;
		uj /= 10;
	}
	while (m > 0)
	{
		szamjegyek[i] = 0;
		i++;
		m--;
	}
}

NagyEgesz::NagyEgesz(long szam)
{
	if (szam < 0)
	{
		elojel = -1;
		szam *= -1;
	}
	else if (szam > 0)
	{
		elojel = 1;
	}
	else
	{
		elojel = 0;
	}

	int m = 0;
	long long uj = 0;
	while (szam != 0)
	{
		m++;
		uj *= 10;
		uj += szam % 10;
		szam /= 10;
	}
	n = m;
	szamjegyek = new int[n];
	int i = 0;
	while (uj > 0)
	{
		szamjegyek[i] = uj % 10;
		m--;
		i++;
		uj /= 10;
	}
	while (m > 0)
	{
		szamjegyek[i] = 0;
		i++;
		m--;
	}
}

NagyEgesz::~NagyEgesz()
{
	delete[] szamjegyek;
}

NagyEgesz NagyEgesz::osszeg_elojel_nelkul(const NagyEgesz& b, const NagyEgesz& a) const
{
	int meret = max(b.n, a.n) + 1;

	int* osszeg = new int[meret];
	for (int i = 0; i < meret; i++)
	{
		osszeg[i] = 0;
	}

	int i, j, m;
	m = meret - 1;
	i = b.n - 1;
	j = a.n - 1;
	while (i >= 0 && j >= 0)
	{
		osszeg[m] += b.szamjegyek[i] + a.szamjegyek[j];
		if (osszeg[m] > 9)
		{
			osszeg[m - 1]++;
			osszeg[m] %= 10;
		}
		i--;
		j--;
		m--;
	}
	while (i >= 0)
	{
		osszeg[m] += b.szamjegyek[i];
		if (osszeg[m] > 9)
		{
			osszeg[m - 1]++;
			osszeg[m] %= 10;
		}
		m--;
		i--;
	}
	while (j >= 0)
	{
		osszeg[m] += a.szamjegyek[j];
		if (osszeg[m] > 9)
		{
			osszeg[m - 1]++;
			osszeg[m] %= 10;
		}
		m--;
		j--;
	}

	i = 0;
	while (osszeg[i] == 0)
	{
		i++;
	}
	int h = meret - i;
	if (i > 0)
	{
		j = 0;
		for (int l = 0; l < h; l++)
		{
			osszeg[j] = osszeg[i];
			j++;
			i++;
		}
	}
	NagyEgesz k(1, h, osszeg);
	delete[] osszeg;
	return k;
}

NagyEgesz NagyEgesz::kivonas_elojel_nelkul(const NagyEgesz& a, const NagyEgesz& b) const
{
	int* kiv = new int[a.n];
	for (int i = 0; i < a.n; i++)
	{
		kiv[i] = a.szamjegyek[i];
	}
	int mer = a.n;

	int j = a.n - 1;
	for (int i = b.n - 1; i >= 0 && j >= 0; i--)
	{
		kiv[j] -= b.szamjegyek[i];
		if (kiv[j] < 0)
		{
			kiv[j] += 10;
			kiv[j - 1]--;
		}
		j--;
	}
	while (kiv[j] < 0 && j >= 0)
	{
		kiv[j] += 10;
		kiv[j - 1]--;
		j--;
	}
	int i = 0;
	while (kiv[i] == 0)
	{
		i++;
	}
	if (i == mer)
	{
		NagyEgesz k(0, mer, kiv);
		delete kiv;
		return k;
	}
	if (i > 0)
	{
		j = 0;
		int h = mer = a.n - i;
		for (int l = 0; l < h; l++)
		{
			kiv[j] = kiv[i];
			j++;
			i++;
		}
	}

	NagyEgesz k(1, mer, kiv);
	delete kiv;
	return k;
}

NagyEgesz NagyEgesz::operator+ (const NagyEgesz& a) const
{
	if (elojel == 0)
	{
		return a;
	}
	if (a.elojel == 0)
	{
		return *this;
	}

	if (elojel == 1 && a.elojel == -1)
	{
		if (*this < a)
		{
			NagyEgesz s = kivonas_elojel_nelkul(a, *this);
			s.elojel = -1;
			return s;
		}
		else
		{
			NagyEgesz s = kivonas_elojel_nelkul(*this, a);
			s.elojel = 1;
			return s;
		}
	}
	if (elojel == -1 && a.elojel == 1)
	{
		if (*this < a)
		{
			NagyEgesz s = kivonas_elojel_nelkul(a, *this);
			s.elojel = 1;
			return s;
		}
		else
		{
			NagyEgesz s = kivonas_elojel_nelkul(*this, a);
			s.elojel = -1;
			return s;
		}
	}
	if (elojel == -1 && a.elojel == -1)
	{
		NagyEgesz s = osszeg_elojel_nelkul(a, *this);
		s.elojel = -1;
		return s;
	}

	NagyEgesz k = osszeg_elojel_nelkul(*this, a);

	return k;
}

NagyEgesz NagyEgesz::operator- (const NagyEgesz& a) const
{
	NagyEgesz eredmeny;
	if (elojel == 1 && a.elojel == -1)
	{
		eredmeny = osszeg_elojel_nelkul(*this, a);
		eredmeny.elojel = 1;
	}
	else if (elojel == -1 && a.elojel == 1)
	{
		eredmeny = osszeg_elojel_nelkul(*this, a);
		if (*this < a)
		{
			eredmeny.elojel = 1;
		}
		else
		{
			eredmeny.elojel = -1;
		}
	}
	else if (elojel == 1 && a.elojel == 1)
	{
		if (*this < a)
		{
			eredmeny = kivonas_elojel_nelkul(a, *this);
			eredmeny.elojel = -1;
		}
		else
		{
			eredmeny = kivonas_elojel_nelkul(*this, a);
			eredmeny.elojel = 1;
		}
	}
	else
	{
		if (*this < a)
		{
			eredmeny = kivonas_elojel_nelkul(a, *this);
			eredmeny.elojel = 1;
		}
		else
		{
			eredmeny = kivonas_elojel_nelkul(*this, a);
			eredmeny.elojel = -1;
		}
	}
	if (eredmeny.szamjegyek[0] == 0)
	{
		eredmeny.elojel = 0;
	}
	return eredmeny;
}

NagyEgesz& NagyEgesz::operator+=(const NagyEgesz& a)
{
	(*this) = *this + a;
	return *this;
}

NagyEgesz& NagyEgesz::operator-=(const NagyEgesz& a)
{
	(*this) = *this - a;
	return *this;
}

NagyEgesz& NagyEgesz::operator++()
{
	return *this += 1;
}

NagyEgesz NagyEgesz::operator++(int)
{
	NagyEgesz a(elojel, n, szamjegyek);
	*this += 1;
	return a;
}

NagyEgesz& NagyEgesz::operator--()
{
	return *this -= 1;
}

NagyEgesz NagyEgesz::operator--(int)
{
	NagyEgesz a(elojel, n, szamjegyek);
	*this -= 1;
	return a;
}

NagyEgesz NagyEgesz::operator =(const NagyEgesz& x)
{
	if (this != &x)
	{
		delete[] szamjegyek;

		n = x.n;
		szamjegyek = new int[n];
		for (int i = 0; i < n; i++)
		{
			szamjegyek[i] = x.szamjegyek[i];
		}
	}
	return *this;
}

NagyEgesz NagyEgesz::operator*(const NagyEgesz& x) const
{
	int e;
	if (elojel == x.elojel)
	{
		e = 1;
	}
	else {
		e = -1;
	}
	int meret = n + x.n;
	int* szorzat = new int[meret];
	for (int k = 0; k < meret; k++)
	{
		szorzat[k] = 0;
	}
	int j = x.n - 1, l = 0;
	meret--;
	while (j >= 0)
	{
		int m = meret;
		for (int i = n - 1; i >= 0; i--)
		{
			szorzat[m - l] += (szamjegyek[i] * x.szamjegyek[j]);
			if (szorzat[m - l] > 9)
			{
				szorzat[m - 1 - l] += szorzat[m - l] / 10;
				szorzat[m - l] %= 10;
			}
			m--;
		}
		j--;
		l++;
	}
	int i = 0;
	while (szorzat[i] == 0)
	{
		i++;
	}
	int h = meret - i;
	if (i > 0)
	{
		j = 0;
		for (int l = 0; l <= h; l++)
		{
			szorzat[j] = szorzat[i];
			j++;
			i++;
		}
	}
	NagyEgesz v(e, h + 1, szorzat);
	return v;
}

NagyEgesz& NagyEgesz::operator*=(const NagyEgesz& a)
{
	(*this) = *this * a;
	return *this;
}

NagyEgesz NagyEgesz::operator /(const NagyEgesz& o) const
{
	if (o.elojel == 0)
	{
		throw(NullavalValoOsztas());
	}
	NagyEgesz eredmeny(1, 0, 0);

	NagyEgesz oszto = o;
	oszto.elojel = 1;
	NagyEgesz osztando = *this;

	if (osztando < oszto)
	{
		return 0;
	}

	int k = 0;
	NagyEgesz s(osztando.szamjegyek[k++]);

	while (s < oszto + 1 && k < n)
	{
		s *= 10;
		s += osztando.szamjegyek[k++];
	}

	NagyEgesz h = oszto;
	eredmeny++;
	while (h + oszto < s)
	{
		eredmeny++;
		h += oszto;
	}
	s -= h;

	while (k < n)
	{
		eredmeny *= 10;
		while (s < oszto + 1 && k < n)
		{
			s *= 10;
			s += osztando.szamjegyek[k++];
		}

		NagyEgesz h = oszto;
		eredmeny++;
		while (h + oszto < s)
		{
			eredmeny++;
			h += oszto;
		}
		s -= h;
	}
	if (oszto - 1 < s)
	{
		eredmeny++;
	}

	if (elojel == o.elojel)
	{
		eredmeny.elojel = 1;
	}
	else
	{
		eredmeny.elojel = -1;
	}
	return eredmeny;
}

NagyEgesz& NagyEgesz::operator/=(const NagyEgesz& a)
{
	(*this) = *this / a;
	return *this;
}

ostream& NagyEgesz::kiir(ostream& s) const
{
	if (elojel == 0)
	{
		s << "0";
	}
	else
	{
		if (elojel < 0) s << "-";
		for (int i = 0; i < n; i++)
		{
			s << szamjegyek[i];
		}
	}
	s << endl;
	return s;
}

ostream& operator<<(ostream& s, const NagyEgesz& x)
{
	return x.kiir(s);
}

bool NagyEgesz::operator<(const NagyEgesz& a) const
{
	if (n < a.n)
	{
		return true;
	}
	else if (n > a.n)
	{
		return false;
	}
	int i = 0, j = 0;
	while (i < n && j < a.n)
	{
		if (szamjegyek[i] < a.szamjegyek[j]) {
			return true;
		}
		if (szamjegyek[i] > a.szamjegyek[j]) {
			return false;
		}
		++i;
		++j;
	}
	return false;
}
