#include "index_generated.h"
#include "threads-data.h"

using namespace js;

ThreadsData::ThreadsData(js::string threadPath) {
    {
            this->_placeholder = []() {
                  js::object obj_temp_0;
                  return js::any(obj_temp_0);
                }();
            this->_threadPath = threadPath;
    }
}

auto ThreadsData::usePlaceholder(js::string id) {
    {
            this->_modelThread.set(id, this->_placeholder);
    }
}

auto ThreadsData::getAmount(Thread thread) {
    {
            return this->_threadsModelAmount.get(thread);
    }
}

auto ThreadsData::getThread(js::string modelId) {
    {
            return this->_modelThread.get(modelId);
    }
}

auto ThreadsData::getAndCheckThread(js::string id) {
    {
            const js::any thread = this->_modelThread.get(id);
            if (thread === this->_placeholder) {
                        {
                                        throw js::any(js::Error("Fragments: Error fetching thread!"_S));
                        }
            }
            return thread;
    }
}

auto ThreadsData::set(js::string modelId, Thread thread) {
    {
            this->_modelThread.set(modelId, thread);
    }
}

auto ThreadsData::deleteModel(js::string modelId) {
    {
            const js::any modelThread = this->getThreadSafe(modelId);
            const js::any threadModelAmount = this->getAmountSafe(modelThread);
            const js::number newModelAmount = (threadModelAmount - js::number(1));
            this->setAmount(modelThread, newModelAmount);
            this->_modelThread.delete(modelId);
    }
}

auto ThreadsData::getThreadSafe(js::string modelId) {
    {
            const js::any thread = this->getThread(modelId);
            if (!thread) {
                        {
                                        throw js::any(js::Error(("Fragments: Thread for model "_S + js::toString(modelId) + " not found"_S)));
                        }
            }
            return thread;
    }
}

auto ThreadsData::deleteThread(Thread thread) {
    {
            this->_threadsModelAmount.delete(thread);
            this->_threadPort.delete(thread);
            thread["terminate"]();
    }
}

auto ThreadsData::getThreadAmount() {
    {
            return this->_threadsModelAmount.size;
    }
}

auto ThreadsData::balanceThreadLoad(js::any input) {
    {
            auto _temp2617 = this->getLessBusyThread();
            const auto lessBusyThread = _temp2617["lessBusyThread"];
            const auto modelAmount = _temp2617["modelAmount"];
            this->_threadsModelAmount.set(lessBusyThread, (modelAmount + js::number(1)));
            this->_modelThread.set(input["modelId"], lessBusyThread);
            return this->_threadPort.get(lessBusyThread);
    }
}

auto ThreadsData::getAmountSafe(Thread thread) {
    {
            const js::any amount = this->getAmount(thread);
            if (!amount) {
                        {
                                        throw js::any(js::Error(("Fragments: Amount for thread "_S + js::toString(thread) + " not found"_S)));
                        }
            }
            return amount;
    }
}

auto ThreadsData::setPort(Thread thread, MessagePort port) {
    {
            this->_threadPort.set(thread, port);
    }
}

auto ThreadsData::setAmount(Thread thread, js::number amount) {
    {
            this->_threadsModelAmount.set(thread, amount);
    }
}

auto ThreadsData::getPort(Thread thread) {
    {
            return this->_threadPort.get(thread);
    }
}

auto ThreadsData::getLessBusyThread() {
    {
            js::any modelAmount = Number::MAX_VALUE;
            js::any lessBusyThread = this->_threadsModelAmount.keys().next().value;
            for (const auto& js::undefined : this->_threadsModelAmount) {
                        {
                                        if ((amount < modelAmount)) {
                                                            {
                                                                                    modelAmount = amount;
                                                                                    lessBusyThread = thread;
                                                            }
                                        }
                        }
            }
            return []() {
                  js::object obj_temp_1;
                  obj_temp_1.set("lessBusyThread", lessBusyThread);
                  obj_temp_1.set("modelAmount", modelAmount);
                  return js::any(obj_temp_1);
                }();
    }
}
