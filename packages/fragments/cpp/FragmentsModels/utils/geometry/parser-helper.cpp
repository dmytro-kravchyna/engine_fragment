#include "index_generated.h"
#include "parser-helper.h"

using namespace js;

auto ParserHelper::parseMaterial(Material material) {
    {
            const js::number r = (material["r"]() / js::number(255));
            const js::number g = (material["g"]() / js::number(255));
            const js::number b = (material["b"]() / js::number(255));
            const js::number opacity = (material["a"]() / js::number(255));
            const bool transparent = (material["a"]() < js::number(255));
            const std::shared_ptr<three::Color> color = std::make_shared<three::Color>(r, g, b);
            const js::any renderedFaces = material["renderedFaces"]();
            return []() {
                  js::object obj_temp_0;
                  obj_temp_0.set("color", color);
                  obj_temp_0.set("renderedFaces", renderedFaces);
                  obj_temp_0.set("opacity", opacity);
                  obj_temp_0.set("transparent", transparent);
                  return js::any(obj_temp_0);
                }();
    }
}

auto ParserHelper::parseBox(BoundingBox data, js::any box) {
    {
            this->getBox(data, box, "min"_S);
            this->getBox(data, box, "max"_S);
    }
}

auto ParserHelper::parseTransform(Transform transform, js::any result) {
    {
            this->getVector(transform, "position"_S, this->_doubleVector);
            this->getVector(transform, "xDirection"_S, this->_floatVector);
            this->getVector(transform, "yDirection"_S, this->_floatVector);
            this->computeZVector();
            this->setTransform(result);
            return result;
    }
}

auto ParserHelper::setTransform(js::any result) {
    {
            auto _temp1488 = this->_temp.xDirection;
            const auto xx = _temp1488["x"];
            const auto xy = _temp1488["y"];
            const auto xz = _temp1488["z"];
            auto _temp5675 = this->_temp.yDirection;
            const auto yx = _temp5675["x"];
            const auto yy = _temp5675["y"];
            const auto yz = _temp5675["z"];
            auto _temp5617 = this->_temp.zDirection;
            const auto zx = _temp5617["x"];
            const auto zy = _temp5617["y"];
            const auto zz = _temp5617["z"];
            auto _temp5929 = this->_temp.position;
            const auto ox = _temp5929["x"];
            const auto oy = _temp5929["y"];
            const auto oz = _temp5929["z"];
            result->set(xx, yx, zx, ox, xy, yy, zy, oy, xz, yz, zz, oz, js::number(0), js::number(0), js::number(0), js::number(1));
    }
}

auto ParserHelper::getBox(BoundingBox data, js::any box, js::any point) {
    {
            data->point(this->_floatVector);
            const js::any x = this->_floatVector.x();
            const js::any y = this->_floatVector.y();
            const js::any z = this->_floatVector.z();
            box[point]["x"] = MiscHelper::fixNumber(x);
            box[point]["y"] = MiscHelper::fixNumber(y);
            box[point]["z"] = MiscHelper::fixNumber(z);
    }
}

auto ParserHelper::getVector(Transform transform, js::any name, js::any vector) {
    {
            transform[name](vector);
            const js::any parsed = this->_temp[name];
            const js::any x = vector["x"]();
            const js::any y = vector["y"]();
            const js::any z = vector["z"]();
            parsed["x"] = MiscHelper::fixNumber(x);
            parsed["y"] = MiscHelper::fixNumber(y);
            parsed["z"] = MiscHelper::fixNumber(z);
    }
}

auto ParserHelper::computeZVector() {
    {
            this->_temp.zDirection.crossVectors(this->_temp.xDirection, this->_temp.yDirection);
    }
}
