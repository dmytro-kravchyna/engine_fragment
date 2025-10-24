#ifndef CIVIL_READER_H
#define CIVIL_READER_H

#include "index_generated.h"


#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <map>
#include <optional>
#include <initializer_list>
#include "runtime/core.h"
#include <web-ifc.h>
#include "../../../../../Schema.h"
#include "../../../../../FragmentsModels.h"

using namespace js;

// Forward declarations
class CivilReader;

class CivilReader {
public:
    CivilReader() = default;
    virtual auto read(js::any webIfc);
private:
    virtual auto getCurveType(js::string data);
};

#endif // CIVIL_READER_H