#ifndef PARSER_HELPER_H
#define PARSER_HELPER_H

#include "index_generated.h"


#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <map>
#include <optional>
#include <initializer_list>
#include "runtime/core.h"
#include <three.h>
#include "../../../../Schema.h"
#include "../misc.h"

using namespace js;

// Forward declarations
class ParserHelper;

class ParserHelper {
public:
    ParserHelper() = default;
    auto parseMaterial(Material material);
    auto parseBox(BoundingBox data, js::any box);
    auto parseTransform(Transform transform, js::any result);
private:
    auto _temp;
    auto _doubleVector;
    auto _floatVector;
    auto setTransform(js::any result);
    auto getBox(BoundingBox data, js::any box, js::any point);
    auto getVector(Transform transform, js::any name, js::any vector);
    auto computeZVector();
};

#endif // PARSER_HELPER_H