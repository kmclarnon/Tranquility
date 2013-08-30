#include "common.h"
#include "engine.h"

int main(int argc, char* argv[])
{
    Engine engine = Engine();

    if(engine.init())
    {
        engine.run();
    }

    engine.shutdown();

    return 0;
}