#include "index_generated.h"
#include "virtual-template-controller.h"

using namespace js;

auto VirtualTemplateController::add(js::number code, AnyTileBasicData template) {
    {
            this->_templates.set(code, template_);
    }
}

auto VirtualTemplateController::get(js::number code) {
    {
            const js::any templates = this->_templates.get(code);
            if (!js::array.isArray(templates)) {
                        {
                                        return []() {
                                              js::object obj_temp_0;
                                              return js::any(obj_temp_0);
                                            }();
                        }
            }
            return this->getTemplateSet(templates);
    }
}

auto VirtualTemplateController::getTemplateSet(js::array<TileBasicData> templates) {
    {
            js::array<TileData> result = js::array<js::any>{};
            for (const auto& template_ : templates) {
                        {
                                        const js::any tileData = template_;
                                        const js::any copy = []() {
                                              js::object obj_temp_1;
                                              return js::any(obj_temp_1);
                                            }();
                                        result.push(copy);
                        }
            }
            return result;
    }
}
