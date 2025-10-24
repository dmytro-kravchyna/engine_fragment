#include "index_generated.h"
#include "data-set.h"

using namespace js;

DataSet::DataSet(std::optional<js::typed::Nullable<Iterable>> iterable) : Set(iterable) {
    {
    }
}

auto DataSet::clear() {
    {
            for (const auto& item : this) {
                        {
                                        this->onBeforeDelete.trigger(item);
                        }
            }
            Set::clear();
            this->onCleared.trigger();
            this->onUpdated.trigger();
    }
}

auto DataSet::add(Args... value) {
    {
            for (const auto& item : value) {
                        {
                                        const js::any existing = this->has(item);
                                        if (existing) {
                                                            continue;
                                        }
                                        const js::any guard = (this->guard.has_value() ? this->guard : [&]() -> auto { return true; });
                                        const js::any isValid = guard(item);
                                        if (!isValid) {
                                                            continue;
                                        }
                                        Set::add(item);
                                        if (!this->onItemAdded) {
                                                            this->onItemAdded = std::make_shared<Event>();
                                        }
                                        this->onItemAdded.trigger(item);
                        }
            }
            if (!this->onUpdated) {
                        this->onUpdated = std::make_shared<Event>();
            }
            this->onUpdated.trigger();
            return this;
    }
}

auto DataSet::delete(T value) {
    {
            const js::any exist = this->has(value);
            if (!exist) {
                        return false;
            }
            this->onBeforeDelete.trigger(value);
            const js::any deleted = Set::delete(value);
            if (deleted) {
                        {
                                        this->onItemDeleted.trigger();
                                        this->onUpdated.trigger();
                        }
            }
            return deleted;
    }
}

auto DataSet::deleteIf(std::function<bool(T)> predicate) {
    {
            for (const auto& v : this) {
                        {
                                        if (predicate(v)) {
                                                            {
                                                                                    this->delete(v);
                                                            }
                                        }
                        }
            }
    }
}

auto DataSet::getIndex(T item) {
    {
            js::number index = js::number(0);
            for (const auto& value : this) {
                        {
                                        if (value === item) {
                                                            return index;
                                        }
                                        index++;
                        }
            }
            return -js::number(1);
    }
}

auto DataSet::dispose() {
    {
            this->clear();
            this->onItemAdded.reset();
            this->onItemDeleted.reset();
            this->onCleared.reset();
            this->onBeforeDelete.reset();
            this->onUpdated.reset();
    }
}
