// x3py framework: https://github.com/rhcad/x3py
#ifndef X3_CORE_IPLUGINS_H
#define X3_CORE_IPLUGINS_H

#include "x3manager.h"
#include <vector>
#include <string>

BEGIN_NAMESPACE_X3

class IPlugins : public IObject
{
    X3DEFINE_IID(IPlugins);
    virtual int getPluginCount() const = 0;
    virtual void getPluginFiles(std::vector<std::string>& files) const = 0;

    virtual int loadExtraPlugins(const char* folder) = 0;
    virtual int unloadExtraPlugins() = 0;
};

END_NAMESPACE_X3
#endif