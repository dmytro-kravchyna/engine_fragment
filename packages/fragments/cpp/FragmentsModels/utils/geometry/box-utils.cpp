#include "index_generated.h"
#include "box-utils.h"

using namespace js;

auto BoxUtils::getWidth(js::any box) {
    {
            box["getSize"](this->_temp.vector);
            if ((this->_temp.vector.x > this->_temp.vector.y)) {
                        {
                                        this->_temp.vector.set(this->_temp.vector.y, this->_temp.vector.x, this->_temp.vector.z);
                        }
            }
            if ((this->_temp.vector.y > this->_temp.vector.z)) {
                        {
                                        this->_temp.vector.set(this->_temp.vector.x, this->_temp.vector.z, this->_temp.vector.y);
                        }
            }
            if ((this->_temp.vector.x > this->_temp.vector.y)) {
                        {
                                        this->_temp.vector.set(this->_temp.vector.y, this->_temp.vector.x, this->_temp.vector.z);
                        }
            }
            return this->_temp.vector.y;
    }
}
