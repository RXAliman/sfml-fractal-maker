#include <time.h>
#include "Application.h"

int main()
{
    srand(time(0));
    Application app;
    while (app.getWindow()->isOpen())
    {
        app.update();
        app.render();
    }
    return 0;
}
