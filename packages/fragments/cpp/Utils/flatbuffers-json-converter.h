#ifndef FLATBUFFERS_JSON_CONVERTER_H
#define FLATBUFFERS_JSON_CONVERTER_H

#include "index_generated.h"


#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <map>
#include <optional>
#include <initializer_list>
#include "runtime/core.h"

using namespace js;

auto getObject(js::any obj, js::any result);

#endif // FLATBUFFERS_JSON_CONVERTER_H