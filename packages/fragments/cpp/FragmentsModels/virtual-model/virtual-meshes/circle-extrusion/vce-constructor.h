#ifndef VCE_CONSTRUCTOR_H
#define VCE_CONSTRUCTOR_H

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
#include "../../../../../Schema.h"
#include "../types.h"
#include "./types.h"
#include "./vce-utils.h"
#include "./vce-caster-utils.h"
#include "../../../model/model-types.h"

using namespace js;

// Forward declarations
class VceConstructor;

class VceConstructor {
public:
    VceConstructor() = default;
    virtual auto newTemplate(CircleExtrusion ce, js::number id, js::array<TileBasicData> templates);
    virtual auto construct(CircleExtrusion circleExtrusion, js::array<TileData> meshData);
private:
    auto _minLinkDistance;
    auto _first;
    auto _last;
    js::number _currentPoint;
    js::number _currentIndex;
    auto _v1;
    auto _v2;
    auto _v3;
    auto _v4;
    auto _tempLine;
    auto _total;
    auto _closest;
    auto _result;
    virtual auto getTemplateCreationData(TileBasicData data, js::any axisPartDimension, js::number vertexAmount);
    virtual auto generateTemplate(Axis axis, js::number id, js::number vertexAmount, TileBasicData data, js::array<TileBasicData> templates);
    virtual auto savePrevious(bool isStart, js::number id, js::number amount, TileBasicData data);
    virtual auto constructNewVce(TileData data, js::any axisPartSize, js::number pointAmount, js::number transvSize, js::array<TileData> meshData, js::number position, js::number id);
    virtual auto constructVce(js::number transvSize, LinkPoint linkPoint, TileData data, js::number pointAmount, js::number position, js::array<TileData> meshData, js::number width);
    virtual auto newTemplateData();
    virtual auto setupNewVceBuffers(TileData data);
    virtual auto clearOffset(js::number pointAmount);
    virtual auto getClone(TileData inp, TileData out, js::number last, js::number size);
    virtual auto manageAxisPartCreation(js::typed::Nullable<AxisPartClass> axisPartClass, Axis axis, js::number position, js::number radius, TileData virtualMesh, js::number vertexSize, LinkPoint linkPoint);
    virtual auto newWireSetStart(js::number i, TileData virtualMesh, js::number vertexSize, LinkPoint linkPoint);
    virtual void newWireSet(WireSet wireSet, js::number radius, TileData virtualMesh, js::number vertexSize, LinkPoint linkPoint);
    virtual auto fillWireSetData(js::number i, js::number length, LinkPoint linkPoint, TileData virtualMesh, js::number vertexSize);
    virtual auto setWireSetVector();
    virtual auto newCircleCurveBody(js::number count, js::number radius, TileData virtualMesh, js::number vertexSize);
    virtual auto newCircleCurveFinish(js::number count, js::number radius, TileData mesh, js::number vertexSize, LinkPoint linkPoint);
    virtual auto setupLink(js::number id, LinkPoint linkPoint);
    virtual auto newCircleCurveStart(js::number radius, TileData virtualMesh, js::number vertexSize, LinkPoint linkPoint);
    virtual auto getWireSetPoints(WireSet wireSet, js::number i);
    virtual auto finishWire(js::number radius, TileData mesh, js::number vertexSize, LinkPoint linkPoint);
    virtual void linkPaths(TileData mesh, js::number vertexSize, bool getLinked = false);
    virtual auto startWire(js::number radius, TileData mesh, js::number vertexSize, LinkPoint linkPoint);
    virtual auto setupWireVectors();
    virtual auto getLinkPathIndices(js::number p3, js::number i, js::number p1, js::number s, js::number i0, js::number p2);
    virtual auto fetchWirePoints(Wire wire);
    virtual auto findLinkedVertex(js::number selected, js::number limit, TileData mesh, js::number size, js::number offset);
    virtual auto newPath(js::any point, js::number radius, js::any rotation, TileData mesh, js::number vertexSize);
    virtual void linkStart(TileData mesh, js::number vertexSize, LinkPoint linkPoint, js::any position, AxisPartClass partClass);
    virtual auto setPathPosition(js::number id, js::number radius, js::any rotation, js::any point, TileData mesh);
    virtual void newWire(Wire wire, js::number radius, TileData mesh, js::number vertexSize, LinkPoint linkPoint);
    virtual void newCircleCurve(CircleCurve circleCurve, js::number radius, TileData mesh, js::number vertexSize, LinkPoint linkPoint);
    virtual auto newPathOrderData(TileData mesh, js::number vertexSize, bool reverse = false, bool past = false);
    virtual auto getPathPositions(js::number vertexSize, bool getLinked, TileData mesh);
    virtual void newAxisPart(Axis axis, js::number id, TileData virtualMesh, js::number radius, js::number vertexSize, LinkPoint linkPoint);
    virtual auto fetchLinkedVertex(js::number selected, TileData mesh, js::number size);
    virtual auto setPathNormal(js::number id, js::any rotation, TileData mesh);
    virtual auto point(js::number selected, TileData virtualMesh, js::any result);
};

#endif // VCE_CONSTRUCTOR_H