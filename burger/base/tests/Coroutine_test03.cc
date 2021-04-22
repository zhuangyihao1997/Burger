#include "burger/base/Log.h"
#include "burger/base/Coroutine.h"

#include <vector>
#include <thread>
#include <algorithm>

using namespace burger;

void runInCo() {
    INFO("run_in_fiber begin");
    Coroutine::SwapOut();
    INFO("run_in_fiber end");
    Coroutine::SwapOut();
}

void testCo() {
    INFO("main begin -1");
    {
        INFO("main begin");
        Coroutine::ptr co = std::make_shared<Coroutine>(runInCo);
        co->swapIn();
        INFO("main after swapIn");
        co->swapIn();
        INFO("main after end");
        co->swapIn();
    }
    INFO("main after end2");
}

int main() {
    LOGGER(); LOG_LEVEL_DEBUG;
    std::vector<std::thread> threadList;   
    for(int i = 0; i < 3; i++) {
        threadList.push_back(std::thread(testCo));
    }
    std::for_each(threadList.begin(), threadList.end(), std::mem_fn(&std::thread::join));
    return 0;
}
