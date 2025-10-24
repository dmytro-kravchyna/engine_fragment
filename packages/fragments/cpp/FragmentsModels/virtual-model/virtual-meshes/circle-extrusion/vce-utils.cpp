#include "index_generated.h"
#include "vce-utils.h"

using namespace js;

auto VceUtils::newPaths(CircleCurve circleCurve, js::number size) {
    {
            const PathData data = VceUtils::newPathData();
            this->fetchCircleCurveData(circleCurve, data);
            this->fetchCircleCurveMids(size, data, circleCurve);
            this->fetchCircleCurveEnds(data, circleCurve);
            this->fetchCircleCurveCuts(data);
            return data->cuts;
    }
}

auto VceUtils::getAxisPartSize(Axis axis, js::number id, js::number vertexSize) {
    {
            const js::any part = axis["parts"](id);
            const js::any order = axis["order"](id);
            const js::any data = VceUtils::getAxisPartData(part, vertexSize, axis, order);
            VceUtils::fetchAxisPartSize(vertexSize, data);
            return this->_axisPartSize;
    }
}

auto VceUtils::vertexLength(js::number radius, js::number factor) {
    {
            const js::any count = js::Math::round((radius * factor));
            const js::any clamped = js::Math::max(count, VceUtils::_minSize);
            return js::Math::min(clamped, VceUtils::_maxSize);
    }
}

auto VceUtils::setPathVertices(js::number vertexSize) {
    {
            const js::any points = this->circleCurvePoints;
            const js::any noPoints = !points;
            const js::any pointsChanged = (points && points.length() !== vertexSize);
            if ((noPoints || pointsChanged)) {
                        {
                                        this->circleCurvePoints = js::array<js::any>{};
                                        for (js::number i = js::number(0); (i < vertexSize); i++) {
                                                            {
                                                                                    const js::number halfCircle = (js::number(2) * js::Math::PI);
                                                                                    const js::number value = (halfCircle * i);
                                                                                    const js::number angle = (value / vertexSize);
                                                                                    const js::any sin = js::Math::sin(angle);
                                                                                    const js::any cos = js::Math::cos(angle);
                                                                                    const std::shared_ptr<three::Vector3> result = std::make_shared<three::Vector3>(sin, cos, js::number(0));
                                                                                    this->circleCurvePoints.push(result);
                                                            }
                                        }
                        }
            }
    }
}

auto VceUtils::fetchCircleCurveEnds(PathData data, CircleCurve circleCurve) {
    {
            data->last.copy(data->first);
            data->last.applyAxisAngle(data->axis, circleCurve->aperture());
            data->last.multiplyScalar(circleCurve->radius());
            data->last.add(data->center);
            data->first.multiplyScalar(circleCurve->radius());
            data->first.add(data->center);
    }
}

auto VceUtils::getAxisPartData(AxisPartClass part, js::number vertexSize, Axis axis, js::number order) {
    {
            const js::any data = []() {
                  js::object obj_temp_0;
                  obj_temp_0.set(js::toString(AxisPartClass::WIRE), this->getAxisPartWireData);
                  obj_temp_0.set(js::toString(AxisPartClass::WIRE_SET), this->getAxisPartWireSetData);
                  obj_temp_0.set(js::toString(AxisPartClass::CIRCLE_CURVE), this->getAxisPartCircleCurveData);
                  return js::any(obj_temp_0);
                }();
            return data->part(axis, order, vertexSize);
    }
}

auto VceUtils::newEmptyAxisPartData() {
    {
            return []() {
                  js::object obj_temp_1;
                  obj_temp_1.set("indices", js::number(0));
                  obj_temp_1.set("points", js::number(0));
                  obj_temp_1.set("faces", js::number(0));
                  obj_temp_1.set("links", js::number(0));
                  return js::any(obj_temp_1);
                }();
    }
}

auto VceUtils::fetchCircleCurveMids(js::number size, PathData data, CircleCurve circleCurve) {
    {
            const js::number count = (size - js::number(2));
            for (js::number i = js::number(0); (i < count); i++) {
                        {
                                        const std::shared_ptr<three::Vector3> newMid = std::make_shared<three::Vector3>();
                                        newMid->copy(data->first);
                                        const js::any aperture = circleCurve->aperture();
                                        const js::number fraction = (size - js::number(1));
                                        const js::number totalAngle = (aperture * (i + js::number(1)));
                                        const js::number angle = (totalAngle / fraction);
                                        newMid->applyAxisAngle(data->axis, angle);
                                        newMid->multiplyScalar(circleCurve->radius());
                                        newMid->add(data->center);
                                        data->mids[i] = newMid;
                        }
            }
    }
}

auto VceUtils::validSize(js::number pointsSize, js::number extraPoints, js::number vertexSize) {
    {
            const js::number totalSize = ((pointsSize + extraPoints) + vertexSize);
            return limitOf2Bytes >= totalSize;
    }
}

auto VceUtils::fetchCircleCurveCuts(PathData data) {
    {
            data->cuts.push(data->first);
            data->cuts.push(/* spread data->mids */);
            data->cuts.push(data->last);
    }
}

auto VceUtils::fetchCircleCurveData(CircleCurve circleCurve, PathData data) {
    {
            const js::any pos = circleCurve->position();
            data->center.set(pos["x"](), pos["y"](), pos["z"]());
            const js::any xDir = circleCurve->xDirection();
            data->axis.set(xDir->x(), xDir->y(), xDir->z());
            const js::any yDir = circleCurve->yDirection();
            data->first.set(yDir->x(), yDir->y(), yDir->z());
    }
}

auto VceUtils::newPathData() {
    {
            return []() {
                  js::object obj_temp_2;
                  obj_temp_2.set("axis", std::make_shared<three::Vector3>());
                  obj_temp_2.set("cuts", js::array<js::any>{});
                  obj_temp_2.set("center", std::make_shared<three::Vector3>());
                  obj_temp_2.set("last", std::make_shared<three::Vector3>());
                  obj_temp_2.set("first", std::make_shared<three::Vector3>());
                  obj_temp_2.set("mids", js::array<js::any>{});
                  return js::any(obj_temp_2);
                }();
    }
}

auto VceUtils::fetchAxisPartSize(js::number vertexSize, AxisPartData data) {
    {
            const js::number indexFactor = (vertexSize - js::number(2));
            const js::number coordsCount = js::number(3);
            const js::number indices = ((data->faces * indexFactor) * coordsCount);
            const js::number links = ((data->links * vertexSize) * this->_wireSize);
            this->_axisPartSize.verticesLength = data->points;
            this->_axisPartSize.indicesLength = ((data->indices + indices) + links);
    }
}
