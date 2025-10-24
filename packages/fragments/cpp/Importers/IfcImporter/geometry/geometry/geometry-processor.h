#ifndef GEOMETRY_PROCESSOR_H
#define GEOMETRY_PROCESSOR_H

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
#include "./points.h"
#include "./edge.h"
#include "./faces.h"
#include "./profiles.h"
#include "./bbox.h"
#include "./plane.h"
#include "../../../../../Schema.h"

using namespace js;

auto getRawShellData(js::Uint32Array index, js::Float32Array position, js::any bbox);
ShellData getShellData(js::any geometry);

#endif // GEOMETRY_PROCESSOR_H