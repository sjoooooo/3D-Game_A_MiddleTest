#ifndef __IUPDATER_H__
#define __IUPDATER_H__

class IUpdater
{
public:
	virtual void Update(IUpdater* Iupdater) = 0;
};

#endif // !__IUPDATER_H__