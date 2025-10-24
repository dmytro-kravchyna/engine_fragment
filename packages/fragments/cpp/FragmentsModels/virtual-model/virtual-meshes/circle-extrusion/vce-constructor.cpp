#include "index_generated.h"
#include "vce-constructor.h"

using namespace js;

auto VceConstructor::newTemplate(CircleExtrusion ce, js::number id, js::array<TileBasicData> templates) {
    {
            const js::any width = ce["radius"](id);
            const js::any axis = ce["axes"](id, VceUtils::temp::axis);
            const js::any vertexAmount = VceUtils::vertexLength(width);
            const js::number lastIndex = (templates.length() - js::number(1));
            js::any data = templates[lastIndex];
            const js::any count = axis["orderLength"]();
            for (js::number i = js::number(0); (i < count); i++) {
                        {
                                        data = this->generateTemplate(axis, i, vertexAmount, data, templates);
                        }
            }
    }
}

auto VceConstructor::construct(CircleExtrusion circleExtrusion, js::array<TileData> meshData) {
    {
            const js::any linkPoint = []() {
                  js::object obj_temp_0;
                  return js::any(obj_temp_0);
                }();
            const TileData data = js::undefined;
            const js::number position = js::number(0);
            js::number pointAmount = js::number(0);
            for (js::number i = js::number(0);
            js::any l = circleExtrusion->axesLength(); (i < l); i++) {
                        {
                                        const js::any width = circleExtrusion->radius(i);
                                        circleExtrusion->axes(i, VceUtils::temp::axis);
                                        const js::any transvSize = VceUtils::vertexLength(width);
                                        pointAmount = this->constructVce(transvSize, linkPoint, data, pointAmount, position, meshData, width);
                        }
            }
    }
}

auto VceConstructor::getTemplateCreationData(TileBasicData data, js::any axisPartDimension, js::number vertexAmount) {
    {
            const js::any isStart = !data;
            bool fits = false;
            if (!isStart) {
                        {
                                        const js::number pointAmount = (data->positionCount / js::number(3));
                                        const js::any extraPoints = axisPartDimension->verticesLength;
                                        fits = VceUtils::validSize(pointAmount, extraPoints, vertexAmount);
                        }
            }
            return []() {
                  js::object obj_temp_1;
                  obj_temp_1.set("isStart", isStart);
                  obj_temp_1.set("fits", fits);
                  return js::any(obj_temp_1);
                }();
    }
}

auto VceConstructor::generateTemplate(Axis axis, js::number id, js::number vertexAmount, TileBasicData data, js::array<TileBasicData> templates) {
    {
            const js::any axisPartDimension = VceUtils::getAxisPartSize(axis, id, vertexAmount);
            auto _temp914 = this->getTemplateCreationData(data, axisPartDimension, vertexAmount);
            const auto isStart = _temp914["isStart"];
            const auto fits = _temp914["fits"];
            const js::any needsToGenerateNew = (isStart || !fits);
            if (needsToGenerateNew) {
                        {
                                        data = this->newTemplateData();
                                        templates.push(data);
                                        this->savePrevious(isStart, id, vertexAmount, data);
                        }
            }
            data->positionCount += (axisPartDimension->verticesLength * js::number(3));
            data->normalCount += (axisPartDimension->verticesLength * js::number(3));
            data->indexCount += axisPartDimension->indicesLength;
            return data;
    }
}

auto VceConstructor::savePrevious(bool isStart, js::number id, js::number amount, TileBasicData data) {
    {
            const js::number vFactor = js::number(3);
            const js::number vOffset = js::number(2);
            const js::any needsSavePreviousData = (!isStart && id !== js::number(0));
            if (needsSavePreviousData) {
                        {
                                        const js::number extraIndices = ((amount - vOffset) * vFactor);
                                        data->positionCount += (amount * vFactor);
                                        data->normalCount += (amount * vFactor);
                                        data->indexCount += extraIndices;
                        }
            }
    }
}

auto VceConstructor::constructNewVce(TileData data, js::any axisPartSize, js::number pointAmount, js::number transvSize, js::array<TileData> meshData, js::number position, js::number id) {
    {
            const js::any isStart = !data;
            bool fits = false;
            if (!isStart) {
                        {
                                        const js::any extraPoints = axisPartSize->verticesLength;
                                        fits = VceUtils::validSize(pointAmount, extraPoints, transvSize);
                        }
            }
            const js::any needsNew = (isStart || !fits);
            if (needsNew) {
                        {
                                        data = meshData->position++;
                                        this->setupNewVceBuffers(data);
                                        const js::any pastOffset = this->_currentPoint;
                                        pointAmount = this->clearOffset(pointAmount);
                                        const js::any needsCopyPastData = (!isStart && id !== js::number(0));
                                        if (needsCopyPastData) {
                                                            {
                                                                                    const js::any pastData = meshData->(position - js::number(2));
                                                                                    this->getClone(pastData, data, pastOffset, transvSize);
                                                                                    pointAmount += transvSize;
                                                            }
                                        }
                        }
            }
            return []() {
                  js::object obj_temp_2;
                  obj_temp_2.set("data", data);
                  obj_temp_2.set("pointAmount", pointAmount);
                  obj_temp_2.set("position", position);
                  return js::any(obj_temp_2);
                }();
    }
}

auto VceConstructor::constructVce(js::number transvSize, LinkPoint linkPoint, TileData data, js::number pointAmount, js::number position, js::array<TileData> meshData, js::number width) {
    {
            const js::any count = VceUtils::temp::axis::orderLength();
            for (js::number i = js::number(0); (i < count); i++) {
                        {
                                        const js::any axis = VceUtils::temp::axis;
                                        const js::any axisPartSize = VceUtils::getAxisPartSize(axis, i, transvSize);
                                        this->setupLink(i, linkPoint);
                                        []() {
                                              js::object obj_temp_3;
                                              obj_temp_3.set("data", data);
                                              obj_temp_3.set("pointAmount", pointAmount);
                                              obj_temp_3.set("position", position);
                                              return js::any(obj_temp_3);
                                            }() = this->constructNewVce(data, axisPartSize, pointAmount, transvSize, meshData, position, i);
                                        this->newAxisPart(VceUtils::temp::axis, i, data, width, transvSize, linkPoint);
                                        pointAmount += axisPartSize->verticesLength;
                        }
            }
            return pointAmount;
    }
}

auto VceConstructor::newTemplateData() {
    {
            return []() {
                  js::object obj_temp_4;
                  obj_temp_4.set("objectClass", ObjectClass::SHELL);
                  obj_temp_4.set("indexCount", js::number(0));
                  obj_temp_4.set("positionCount", js::number(0));
                  obj_temp_4.set("normalCount", js::number(0));
                  return js::any(obj_temp_4);
                }();
    }
}

auto VceConstructor::setupNewVceBuffers(TileData data) {
    {
            data->positionBuffer = std::make_shared<Float32Array>(data->positionCount);
            data->normalBuffer = std::make_shared<Int16Array>(data->normalCount);
            data->indexBuffer = std::make_shared<Uint16Array>(data->indexCount);
    }
}

auto VceConstructor::clearOffset(js::number pointAmount) {
    {
            this->_currentPoint = js::number(0);
            this->_currentIndex = js::number(0);
            pointAmount = js::number(0);
            return pointAmount;
    }
}

auto VceConstructor::getClone(TileData inp, TileData out, js::number last, js::number size) {
    {
            const js::number start = (size * -js::number(3));
            for (js::any i = start; (i < js::number(0)); i++) {
                        {
                                        const js::any oPoints = out["positionBuffer"];
                                        const js::any iPoints = inp["positionBuffer"];
                                        const js::any oNorm = out["normalBuffer"];
                                        const js::any iNorm = inp["normalBuffer"];
                                        oPoints->this->_currentPoint = iPoints->(last + i);
                                        oNorm->this->_currentPoint = iNorm->(last + i);
                                        this->_currentPoint++;
                        }
            }
    }
}

auto VceConstructor::manageAxisPartCreation(js::typed::Nullable<AxisPartClass> axisPartClass, Axis axis, js::number position, js::number radius, TileData virtualMesh, js::number vertexSize, LinkPoint linkPoint) {
    {
            if (axisPartClass === AxisPartClass::CIRCLE_CURVE) {
                        {
                                        const js::any current = axis["circleCurves"](position);
                                        this->newCircleCurve(current, radius, virtualMesh, vertexSize, linkPoint);
                                        return;
                        }
            }
            if (axisPartClass === AxisPartClass::WIRE_SET) {
                        {
                                        const js::any current = axis["wireSets"](position);
                                        this->newWireSet(current, radius, virtualMesh, vertexSize, linkPoint);
                                        return;
                        }
            }
            if (axisPartClass === AxisPartClass::WIRE) {
                        {
                                        const js::any current = axis["wires"](position);
                                        this->newWire(current, radius, virtualMesh, vertexSize, linkPoint);
                        }
            }
    }
}

auto VceConstructor::newWireSetStart(js::number i, TileData virtualMesh, js::number vertexSize, LinkPoint linkPoint) {
    {
            if (i === js::number(1)) {
                        {
                                        this->linkStart(virtualMesh, vertexSize, linkPoint, this->_first, AxisPartClass::WIRE_SET);
                        }
            } else {
                        {
                                        this->newPathOrderData(virtualMesh, vertexSize);
                        }
            }
    }
}

void VceConstructor::newWireSet(WireSet wireSet, js::number radius, TileData virtualMesh, js::number vertexSize, LinkPoint linkPoint) {
    {
            for (js::number i = js::number(1);
            js::any length = wireSet->psLength(); (i < length); i++) {
                        {
                                        const js::any rot = VceUtils::temp::rotation;
                                        this->getWireSetPoints(wireSet, i);
                                        this->setWireSetVector();
                                        this->newPath(this->_first, radius, rot, virtualMesh, vertexSize);
                                        this->newWireSetStart(i, virtualMesh, vertexSize, linkPoint);
                                        this->newPath(this->_last, radius, rot, virtualMesh, vertexSize);
                                        this->fillWireSetData(i, length, linkPoint, virtualMesh, vertexSize);
                                        this->linkPaths(virtualMesh, vertexSize);
                        }
            }
    }
}

auto VceConstructor::fillWireSetData(js::number i, js::number length, LinkPoint linkPoint, TileData virtualMesh, js::number vertexSize) {
    {
            if ((i !== (length - js::number(1)) || linkPoint->last)) {
                        {
                                        this->newPathOrderData(virtualMesh, vertexSize, true);
                        }
            } else {
                        {
                                        linkPoint->placement = this->_last;
                                        linkPoint->axisClass = AxisPartClass::WIRE_SET;
                        }
            }
    }
}

auto VceConstructor::setWireSetVector() {
    {
            VceUtils::temp::vector::copy(this->_last);
            VceUtils::temp::vector::sub(this->_first);
            VceUtils::temp::vector::normalize();
            VceUtils::temp::rotation::setFromUnitVectors(VceUtils::up, VceUtils::temp::vector);
    }
}

auto VceConstructor::newCircleCurveBody(js::number count, js::number radius, TileData virtualMesh, js::number vertexSize) {
    {
            const js::number amount = (count - js::number(2));
            for (js::number i = js::number(0); (i < amount); i++) {
                        {
                                        const js::any c1 = VceUtils::circleCurves[i];
                                        const js::any c2 = VceUtils::circleCurves[(i + js::number(1))];
                                        const js::any c3 = VceUtils::circleCurves[(i + js::number(2))];
                                        const js::any vec = VceUtils::temp::vector;
                                        vec["copy"](c3);
                                        vec["sub"](c1);
                                        vec["normalize"]();
                                        VceUtils::temp::rotation::setFromUnitVectors(VceUtils::up, vec);
                                        this->newPath(c2, radius, VceUtils::temp::rotation, virtualMesh, vertexSize);
                                        this->linkPaths(virtualMesh, vertexSize, true);
                        }
            }
    }
}

auto VceConstructor::newCircleCurveFinish(js::number count, js::number radius, TileData mesh, js::number vertexSize, LinkPoint linkPoint) {
    {
            const js::number pos1 = (count - js::number(2));
            const js::number pos2 = (count - js::number(1));
            const js::any c1 = VceUtils::circleCurves[pos1];
            const js::any c2 = VceUtils::circleCurves[pos2];
            const js::any vec = VceUtils::temp::vector;
            vec["copy"](c2);
            vec["sub"](c1);
            vec["normalize"]();
            VceUtils::temp::rotation::setFromUnitVectors(VceUtils::up, vec);
            this->newPath(c2, radius, VceUtils::temp::rotation, mesh, vertexSize);
            if (linkPoint->last) {
                        {
                                        this->newPathOrderData(mesh, vertexSize, true);
                                        return;
                        }
            }
            linkPoint->placement = VceUtils::circleCurves[pos2];
            linkPoint->axisClass = AxisPartClass::CIRCLE_CURVE;
    }
}

auto VceConstructor::setupLink(js::number id, LinkPoint linkPoint) {
    {
            if (id === js::number(0)) {
                        {
                                        linkPoint->first = true;
                        }
            }
            const js::any count = VceUtils::temp::axis::orderLength();
            if (id === (count - js::number(1))) {
                        {
                                        linkPoint->last = true;
                        }
            }
    }
}

auto VceConstructor::newCircleCurveStart(js::number radius, TileData virtualMesh, js::number vertexSize, LinkPoint linkPoint) {
    {
            const js::any c1 = VceUtils::circleCurves[js::number(0)];
            const js::any c2 = VceUtils::circleCurves[js::number(1)];
            const js::any vec = VceUtils::temp::vector;
            vec["copy"](c2);
            vec["sub"](c1);
            vec["normalize"]();
            VceUtils::temp::rotation::setFromUnitVectors(VceUtils::up, vec);
            this->newPath(c1, radius, VceUtils::temp::rotation, virtualMesh, vertexSize);
            const js::any aClass = AxisPartClass::CIRCLE_CURVE;
            this->linkStart(virtualMesh, vertexSize, linkPoint, c1, aClass);
    }
}

auto VceConstructor::getWireSetPoints(WireSet wireSet, js::number i) {
    {
            const js::any p1 = wireSet->ps((i - js::number(1)));
            this->_first.set(p1["x"](), p1["y"](), p1["z"]());
            const js::any p2 = wireSet->ps(i);
            this->_last.set(p2["x"](), p2["y"](), p2["z"]());
    }
}

auto VceConstructor::finishWire(js::number radius, TileData mesh, js::number vertexSize, LinkPoint linkPoint) {
    {
            this->newPath(this->_last, radius, VceUtils::temp::rotation, mesh, vertexSize);
            if (linkPoint->last) {
                        {
                                        this->newPathOrderData(mesh, vertexSize, true);
                        }
            } else {
                        {
                                        linkPoint->placement = this->_last;
                                        linkPoint->axisClass = AxisPartClass::WIRE;
                        }
            }
            this->linkPaths(mesh, vertexSize);
    }
}

void VceConstructor::linkPaths(TileData mesh, js::number vertexSize, bool getLinked) {
    {
            const js::any s = vertexSize;
            auto _temp1868 = this->getPathPositions(s, getLinked, mesh);
            const auto p1 = _temp1868["p1"];
            const auto p2 = _temp1868["p2"];
            const auto p3 = _temp1868["p3"];
            const js::any index = mesh["indexBuffer"];
            for (js::number i = js::number(0); (i < s); i++) {
                        {
                                        const js::number i0 = ((i + js::number(1)) % s);
                                        auto _temp2213 = this->getLinkPathIndices(p3, i, p1, s, i0, p2);
                                        const auto i3 = _temp2213["i3"];
                                        const auto i4 = _temp2213["i4"];
                                        const auto i1 = _temp2213["i1"];
                                        const auto i2 = _temp2213["i2"];
                                        index[this->_currentIndex++] = i3;
                                        index[this->_currentIndex++] = i4;
                                        index[this->_currentIndex++] = i1;
                                        index[this->_currentIndex++] = i1;
                                        index[this->_currentIndex++] = i4;
                                        index[this->_currentIndex++] = i2;
                        }
            }
    }
}

auto VceConstructor::startWire(js::number radius, TileData mesh, js::number vertexSize, LinkPoint linkPoint) {
    {
            this->newPath(this->_first, radius, VceUtils::temp::rotation, mesh, vertexSize);
            const js::any aClass = AxisPartClass::WIRE;
            this->linkStart(mesh, vertexSize, linkPoint, this->_first, aClass);
    }
}

auto VceConstructor::setupWireVectors() {
    {
            const js::any vec = VceUtils::temp::vector;
            vec["copy"](this->_last);
            vec["sub"](this->_first);
            vec["normalize"]();
            VceUtils::temp::rotation::setFromUnitVectors(VceUtils::up, vec);
    }
}

auto VceConstructor::getLinkPathIndices(js::number p3, js::number i, js::number p1, js::number s, js::number i0, js::number p2) {
    {
            js::number i1 = js::number(0);
            js::number i2 = js::number(0);
            js::number i3 = js::number(0);
            js::number i4 = js::number(0);
            if ((p3 + i) >= p1) {
                        {
                                        i1 = ((p3 + i) - s);
                        }
            } else {
                        {
                                        i1 = (p3 + i);
                        }
            }
            if ((p3 + i0) >= p1) {
                        {
                                        i2 = ((p3 + i0) - s);
                        }
            } else {
                        {
                                        i2 = (p3 + i0);
                        }
            }
            if ((p2 + i) >= (p1 + s)) {
                        {
                                        i3 = ((p2 + i) - s);
                        }
            } else {
                        {
                                        i3 = (p2 + i);
                        }
            }
            if ((p2 + i0) >= (p1 + s)) {
                        {
                                        i4 = ((p2 + i0) - s);
                        }
            } else {
                        {
                                        i4 = (p2 + i0);
                        }
            }
            return []() {
                  js::object obj_temp_5;
                  obj_temp_5.set("i3", i3);
                  obj_temp_5.set("i4", i4);
                  obj_temp_5.set("i1", i1);
                  obj_temp_5.set("i2", i2);
                  return js::any(obj_temp_5);
                }();
    }
}

auto VceConstructor::fetchWirePoints(Wire wire) {
    {
            const js::any p1 = wire["p1"]();
            const js::any p2 = wire["p2"]();
            this->_first.set(p1["x"](), p1["y"](), p1["z"]());
            this->_last.set(p2["x"](), p2["y"](), p2["z"]());
    }
}

auto VceConstructor::findLinkedVertex(js::number selected, js::number limit, TileData mesh, js::number size, js::number offset) {
    {
            for (js::any i = selected; (i < limit); i++) {
                        {
                                        this->point(i, mesh, this->_v1);
                                        const js::number pos = ((i - size) + offset);
                                        const js::any p1 = (js::null ? js::null : js::null);
                                        this->point(p1, mesh, this->_v2);
                                        const js::any p2 = (js::null ? js::null : js::null);
                                        this->point(p2, mesh, this->_v3);
                                        this->_tempLine.set(this->_v2, this->_v3);
                                        this->_tempLine.closestPointToPoint(this->_v1, true, this->_v4);
                                        this->_total += this->_v4.distanceTo(this->_v1);
                        }
            }
    }
}

auto VceConstructor::newPath(js::any point, js::number radius, js::any rotation, TileData mesh, js::number vertexSize) {
    {
            VceUtils::setPathVertices(vertexSize);
            const js::number pathStep = js::number(3);
            for (js::number i = js::number(0); (i < vertexSize); i++) {
                        {
                                        this->setPathPosition(i, radius, rotation, point, mesh);
                                        this->setPathNormal(i, rotation, mesh);
                                        this->_currentPoint += pathStep;
                        }
            }
    }
}

void VceConstructor::linkStart(TileData mesh, js::number vertexSize, LinkPoint linkPoint, js::any position, AxisPartClass partClass) {
    {
            const js::any isStart = linkPoint->first;
            if (isStart) {
                        {
                                        this->newPathOrderData(mesh, vertexSize);
                                        return;
                        }
            }
            const js::any curveClass = AxisPartClass::CIRCLE_CURVE;
            const js::any isCircle1 = linkPoint->axisClass === curveClass;
            const js::any isCircle2 = partClass === curveClass;
            const js::any compatible = (isCircle1 || isCircle2);
            const js::any distance = linkPoint->placement->distanceToSquared(position);
            const bool isLinked = (distance < this->_minLinkDistance);
            if ((!compatible || !isLinked)) {
                        {
                                        this->newPathOrderData(mesh, vertexSize, true, true);
                                        this->newPathOrderData(mesh, vertexSize);
                                        return;
                        }
            }
            this->linkPaths(mesh, vertexSize, true);
    }
}

auto VceConstructor::setPathPosition(js::number id, js::number radius, js::any rotation, js::any point, TileData mesh) {
    {
            const js::any vec = VceUtils::temp::vector;
            vec["copy"](VceUtils::circleCurvePoints[id]);
            vec["multiplyScalar"](radius);
            vec["applyQuaternion"](rotation);
            vec["add"](point);
            const js::any pos = mesh["positionBuffer"];
            const js::any location1 = this->_currentPoint;
            const js::number location2 = (this->_currentPoint + js::number(1));
            const js::number location3 = (this->_currentPoint + js::number(2));
            pos[location1] = vec["x"];
            pos[location2] = vec["y"];
            pos[location3] = vec["z"];
    }
}

void VceConstructor::newWire(Wire wire, js::number radius, TileData mesh, js::number vertexSize, LinkPoint linkPoint) {
    {
            this->fetchWirePoints(wire);
            this->setupWireVectors();
            this->startWire(radius, mesh, vertexSize, linkPoint);
            this->finishWire(radius, mesh, vertexSize, linkPoint);
    }
}

void VceConstructor::newCircleCurve(CircleCurve circleCurve, js::number radius, TileData mesh, js::number vertexSize, LinkPoint linkPoint) {
    {
            const js::any count = VceCasterUtils::circleCurve3Divisions(circleCurve);
            VceUtils::circleCurves = VceUtils::newPaths(circleCurve, count);
            this->newCircleCurveStart(radius, mesh, vertexSize, linkPoint);
            this->newCircleCurveBody(count, radius, mesh, vertexSize);
            this->newCircleCurveFinish(count, radius, mesh, vertexSize, linkPoint);
            this->linkPaths(mesh, vertexSize, true);
    }
}

auto VceConstructor::newPathOrderData(TileData mesh, js::number vertexSize, bool reverse, bool past) {
    {
            const js::number step1 = js::number(1);
            const js::number step2 = js::number(2);
            const js::number count = (vertexSize - js::number(2));
            const js::any index = mesh["indexBuffer"];
            for (js::number i = js::number(0); (i < count); i++) {
                        {
                                        const js::number p = (this->_currentPoint / js::number(3));
                                        const js::any rawOffset = (js::null ? js::null : js::null);
                                        const js::number offset = (vertexSize * rawOffset);
                                        const js::number indexValue1 = (p - offset);
                                        index[this->_currentIndex] = indexValue1;
                                        this->_currentIndex++;
                                        const js::any offset2 = (js::null ? js::null : js::null);
                                        const js::number indexValue2 = (((p + i) + offset2) - offset);
                                        index[this->_currentIndex] = indexValue2;
                                        this->_currentIndex++;
                                        const js::any offset3 = (js::null ? js::null : js::null);
                                        const js::number indexValue3 = (((p + i) + offset3) - offset);
                                        index[this->_currentIndex] = indexValue3;
                                        this->_currentIndex++;
                        }
            }
    }
}

auto VceConstructor::getPathPositions(js::number vertexSize, bool getLinked, TileData mesh) {
    {
            const js::number p1 = ((this->_currentPoint / js::number(3)) - vertexSize);
            const js::any p2 = p1;
            js::number p3 = (p1 - vertexSize);
            if (getLinked) {
                        {
                                        p3 = this->fetchLinkedVertex(p1, mesh, vertexSize);
                        }
            }
            return []() {
                  js::object obj_temp_6;
                  obj_temp_6.set("p3", p3);
                  obj_temp_6.set("p1", p1);
                  obj_temp_6.set("p2", p2);
                  return js::any(obj_temp_6);
                }();
    }
}

void VceConstructor::newAxisPart(Axis axis, js::number id, TileData virtualMesh, js::number radius, js::number vertexSize, LinkPoint linkPoint) {
    {
            const js::any axisPartClass = axis["parts"](id);
            const js::any position = axis["order"](id);
            this->manageAxisPartCreation(axisPartClass, axis, position, radius, virtualMesh, vertexSize, linkPoint);
            linkPoint->first = false;
            linkPoint->last = false;
    }
}

auto VceConstructor::fetchLinkedVertex(js::number selected, TileData mesh, js::number size) {
    {
            this->_closest = Number::MAX_VALUE;
            for (js::number i = js::number(0); (i < size); i++) {
                        {
                                        this->_total = js::number(0);
                                        const js::number limit = (selected + size);
                                        this->findLinkedVertex(selected, limit, mesh, size, i);
                                        const bool closerFound = (this->_total < this->_closest);
                                        if (!closerFound) {
                                                            continue;
                                        }
                                        this->_closest = this->_total;
                                        this->_result = (((selected - size) + i) + js::number(1));
                        }
            }
            return this->_result;
    }
}

auto VceConstructor::setPathNormal(js::number id, js::any rotation, TileData mesh) {
    {
            const js::any vec = VceUtils::temp::vector;
            const js::any currentPoint = VceUtils::circleCurvePoints[id];
            vec["copy"](currentPoint);
            vec["applyQuaternion"](rotation);
            const js::any nor = mesh["normalBuffer"];
            const js::any location1 = this->_currentPoint;
            const js::number location2 = (this->_currentPoint + js::number(1));
            const js::number location3 = (this->_currentPoint + js::number(2));
            nor[location1] = (vec["x"] * normalizationValue);
            nor[location2] = (vec["y"] * normalizationValue);
            nor[location3] = (vec["z"] * normalizationValue);
    }
}

auto VceConstructor::point(js::number selected, TileData virtualMesh, js::any result) {
    {
            const js::any pos = virtualMesh->positionBuffer;
            const js::number ix = (selected * js::number(3));
            const js::number iy = ((selected * js::number(3)) + js::number(1));
            const js::number iz = ((selected * js::number(3)) + js::number(2));
            const js::any x = pos[ix];
            const js::any y = pos[iy];
            const js::any z = pos[iz];
            result->set(x, y, z);
            return result;
    }
}
